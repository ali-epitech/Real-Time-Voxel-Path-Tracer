#ifndef IMAGE_H
    #define IMAGE_H

    #include <vector>
    #include <glm/glm.hpp>

    class Image {
        public:
            Image(int width, int height);
            void setPixel(int x, int y, glm::vec3& color);
            void addPixel(int x, int y, glm::vec3& color);
            void savePPM(const std::string& filename);
            unsigned char * getPixels() { return pixels.data(); }
        private:
            int width, height;
            std::vector<unsigned char> pixels; // RGB data
        };

#endif /* IMAGE_H */