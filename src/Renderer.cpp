#include <string>
#include "Renderer.h"
#include "Image.h"

Renderer::Renderer(int width, int height)
{
    this->width = width;
    this->height = height;
    this->image = Image(width, height);
}

void Renderer::render()
{
    float u = 0, v = 0;
    unsigned char r = 0, g = 0, b = 0;
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            u = float(x) / this->width;
            v = float(y) / this->height;
            r = static_cast<unsigned char>(u * 255);
            g = static_cast<unsigned char>(v * 255);
            b = 255;
            this->image.setPixel(x, y, r, g, b);
        }
    }
}

void Renderer::saveOutput(const std::string& filename)
{
    this->image.savePPM(filename);
}