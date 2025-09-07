#ifndef RENDERER_H
    #define RENDERER_H
    #include "Image.h"

    class Renderer {
        public:
            Renderer(int width, int height);
            void render();                   // Fills the image with colors
            void saveOutput(const std::string& filename);
        private:
            int width, height;
            Image image;                     // The canvas we paint on
        };

#endif /* RENDERER_H */