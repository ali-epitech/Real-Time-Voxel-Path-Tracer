#!/usr/bin/env python3
"""
make_scene_gltf.py
Generate scene.bin + scene.gltf for the Cornell-box-like scene you provided.
Outputs:
  - scene.bin  (Float32 positions, tightly packed)
  - scene.gltf (references scene.bin, one bufferView+accessor per primitive,
                materials for Red/Green/White/CeilingLight)
"""

import struct, json, os

# --- Define the triangles exactly as in your C++ scene ---
# Each primitive = 2 triangles = 6 positions (non-indexed)
floor = [
    (-5.0, 0.0, -10.0), (5.0, 0.0, -10.0), (5.0, 0.0, 5.0),
    (-5.0, 0.0, -10.0), (5.0, 0.0, 5.0), (-5.0, 0.0, 5.0)
]

left_wall = [
    (-5.0, 0.0, -10.0), (-5.0, 5.0, -10.0), (-5.0, 5.0, 5.0),
    (-5.0, 0.0, -10.0), (-5.0, 5.0, 5.0), (-5.0, 0.0, 5.0)
]

right_wall = [
    (5.0, 0.0, -10.0), (5.0, 0.0, 5.0), (5.0, 5.0, 5.0),
    (5.0, 0.0, -10.0), (5.0, 5.0, 5.0), (5.0, 5.0, -10.0)
]

ceiling = [
    (-5.0, 5.0, -10.0), (5.0, 5.0, -10.0), (5.0, 5.0, 5.0),
    (-5.0, 5.0, -10.0), (5.0, 5.0, 5.0), (-5.0, 5.0, 5.0)
]

back_wall = [
    (-5.0, 0.0, -10.0), (5.0, 0.0, -10.0), (5.0, 5.0, -10.0),
    (-5.0, 0.0, -10.0), (5.0, 5.0, -10.0), (-5.0, 5.0, -10.0)
]

ceiling_light = [
    (-1.5, 4.9, -4.0), (1.5, 4.9, -4.0), (1.5, 4.9, -7.0),
    (-1.5, 4.9, -4.0), (1.5, 4.9, -7.0), (-1.5, 4.9, -7.0)
]

# Group primitives and their target material indices
# We'll create materials in this order: Red, Green, White, CeilingLight
# Assign primitives to appropriate materials:
# - floor, ceiling, back_wall -> White (material index 2)
# - left_wall -> Red (0)
# - right_wall -> Green (1)
# - ceiling_light -> CeilingLight (3)
primitives = [
    (floor, 2, "Floor"),        # white
    (left_wall, 0, "LeftWall"), # red
    (right_wall, 1, "RightWall"), # green
    (ceiling, 2, "Ceiling"),    # white
    (back_wall, 2, "BackWall"), # white
    (ceiling_light, 3, "CeilingLight") # emissive
]

# Flatten: write each primitive sequentially into scene.bin; create one bufferView+accessor per primitive
float_count = sum(len(p[0]) * 3 for p in primitives)  # not used directly, informational

# Path names
OUT_BIN = "scene.bin"
OUT_GLT = "scene.gltf"

# --- Write binary buffer ---
with open(OUT_BIN, "wb") as bf:
    for prim, _, _ in primitives:
        for (x, y, z) in prim:
            bf.write(struct.pack("<fff", float(x), float(y), float(z)))  # little-endian float32

total_bytes = os.path.getsize(OUT_BIN)
# Sanity: each primitive has 6 vertices * 3 floats * 4 bytes = 72 bytes
# There are 6 primitives => 6 * 72 = 432 bytes total
print(f"Wrote {OUT_BIN} ({total_bytes} bytes)")

# --- Helper: compute min/max for an accessor ---
def compute_min_max(positions):
    xs = [p[0] for p in positions]
    ys = [p[1] for p in positions]
    zs = [p[2] for p in positions]
    return [min(xs), min(ys), min(zs)], [max(xs), max(ys), max(zs)]

# Build glTF JSON
gltf = {
    "asset": {"version": "2.0", "generator": "make_scene_gltf.py"},
    "buffers": [
        {"uri": OUT_BIN, "byteLength": total_bytes}
    ],
    "bufferViews": [],
    "accessors": [],
    "materials": [
        # 0 Red
        {
            "name": "Red",
            "pbrMetallicRoughness": {
                "baseColorFactor": [1.0, 0.0, 0.0, 1.0],
                "metallicFactor": 0.0,
                "roughnessFactor": 1.0
            }
        },
        # 1 Green
        {
            "name": "Green",
            "pbrMetallicRoughness": {
                "baseColorFactor": [0.0, 1.0, 0.0, 1.0],
                "metallicFactor": 0.0,
                "roughnessFactor": 1.0
            }
        },
        # 2 White
        {
            "name": "White",
            "pbrMetallicRoughness": {
                "baseColorFactor": [1.0, 1.0, 1.0, 1.0],
                "metallicFactor": 0.0,
                "roughnessFactor": 1.0
            }
        },
        # 3 CeilingLight (emissive)
        {
            "name": "CeilingLight",
            "pbrMetallicRoughness": {
                "baseColorFactor": [1.0, 1.0, 1.0, 1.0],
                "metallicFactor": 0.0,
                "roughnessFactor": 0.5
            },
            "emissiveFactor": [1.0, 1.0, 1.0]
        }
    ],
    "meshes": [],
    "nodes": [],
    "scenes": [{"nodes": []}],
    "scene": 0
}

# Build bufferViews & accessors; track byte offsets
byte_offset = 0
for i, (prim_positions, mat_idx, mesh_name) in enumerate(primitives):
    # each primitive: positions array of 6 vertices (6 * 3 floats)
    num_vertices = len(prim_positions)  # should be 6
    byte_length = num_vertices * 3 * 4  # floats -> bytes
    # Add bufferView
    bv = {"buffer": 0, "byteOffset": byte_offset, "byteLength": byte_length, "target": 34962}
    bv_index = len(gltf["bufferViews"])
    gltf["bufferViews"].append(bv)
    # Compute min/max
    mn, mx = compute_min_max(prim_positions)
    # Add accessor
    acc = {
        "bufferView": bv_index,
        "byteOffset": 0,
        "componentType": 5126,  # FLOAT
        "count": num_vertices,
        "type": "VEC3",
        "min": mn,
        "max": mx
    }
    acc_index = len(gltf["accessors"])
    gltf["accessors"].append(acc)
    # Add mesh (one primitive per mesh)
    prim = {"attributes": {"POSITION": acc_index}, "mode": 4, "material": mat_idx}
    mesh = {"name": mesh_name, "primitives": [prim]}
    mesh_index = len(gltf["meshes"])
    gltf["meshes"].append(mesh)
    # Add node pointing to mesh
    node = {"mesh": mesh_index, "name": mesh_name + "Node"}
    node_index = len(gltf["nodes"])
    gltf["nodes"].append(node)
    gltf["scenes"][0]["nodes"].append(node_index)

    byte_offset += byte_length

# Final sanity check: declared bufferViews total must equal total_bytes
declared = sum(bv["byteLength"] for bv in gltf["bufferViews"])
if declared != total_bytes:
    print("Warning: declared bufferViews total != actual file size:", declared, total_bytes)

# Write scene.gltf
with open(OUT_GLT, "w", encoding="utf-8") as gf:
    json.dump(gltf, gf, indent=2)
print(f"Wrote {OUT_GLT}")

print("Done. Files created:")
print(" -", OUT_GLT)
print(" -", OUT_BIN)
print("")
print("You can open scene.gltf in a Three.js glTF viewer (or load with Assimp).")
