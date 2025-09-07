#ifndef IMAGE_H
    #define IMAGE_H
    #include <vector>

    class Image {
        public:
            Image() = default;
            Image(int width, int height);
            void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
            void savePPM(const std::string& filename);
        private:
            int width, height;
            std::vector<unsigned char> pixels; // RGB data
        };

#endif /* IMAGE_H */