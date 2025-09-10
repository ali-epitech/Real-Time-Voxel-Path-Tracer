#include <iostream>
#include <fstream>
#include "Image.h"

Image::Image(int width, int height)
{
    this->width = width;
    this->height = height;
    this->pixels.resize(width * height * 3, 0); // initialize all pixels to black
}

void Image::setPixel(int x, int y, glm::vec3& color)
{
    int index = (y * this->width + x) * 3; // flat index
    this->pixels[index] = static_cast<unsigned char>(color.r * 255);
    this->pixels[index + 1] = static_cast<unsigned char>(color.g * 255);
    this->pixels[index + 2] = static_cast<unsigned char>(color.b * 255);
}

void Image::savePPM(const std::string& filename)
{
    std::fstream fd;
    fd.open(filename, std::ios::out);
    if (!fd) {
        std::cout << "Error while creating the file";
    } else {
        std::cout << "File created successfully";
        fd << "P6\n";
        fd << this->width << " " << this->height << "\n";
        fd << "255\n";
        fd.write(reinterpret_cast <char*> (pixels.data()), pixels.size());
        fd.close();
    }
}