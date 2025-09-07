#include <iostream>
#include "Renderer.h"

int main() {
    Renderer renderer(800, 600);
    renderer.render();
    renderer.saveOutput("output.ppm");
    std::cout << "Done! Open output.ppm." << std::endl;
    return 0;
}
