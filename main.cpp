#include <iostream>
#include <cmath>
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


using namespace std;

extern  "C" void compute_newton(int width, int height, int n, int max_iter, float epsilon, int* root_indices, int* iterations);

int main(int argc, char* argv[]) {
    int n = 5; // default
    if (argc > 1) {
        n = atoi(argv[1]);
        if (n < 2) n = 2;
    }
    int width = 1000;
    int height = 1000;
    int max_iter = 200;
    float epsilon = 1e-4f;

    vector<int> root_indices(width * height);
    vector<int> iterations(width * height);

    compute_newton(width, height, n, max_iter, epsilon, root_indices.data(), iterations.data());

    
    // generate the image
    vector<unsigned char> image(width * height *3);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            int idx = j*width + i;
            int root = root_indices[idx];
            int iter = iterations[idx];

            // no convergence
            if (root == -1) {
                image[3*idx + 0] = 0;
                image[3*idx + 1] = 0;
                image[3*idx + 2] = 0;
                continue;
            }
            
            float hue = root / (float) n;
            float saturation = 1.0f;
            float brightness = expf(-0.1f * iter) + 0.1f;
            brightness = max(0.05f, std::min(brightness, 1.0f));


            float h = hue * 6.0f;
            int hi = (int)h % 6;
            float f = h - hi;
            float p = brightness * (1.0f - saturation);
            float q = brightness * (1.0f - f * saturation);
            float t = brightness * (1.0f - (1.0f - f) * saturation);

            float r, g, b;
            switch (hi) {
                case 0: r = brightness; g = t; b = p; break;
                case 1: r = q; g = brightness; b = p; break;
                case 2: r = p; g = brightness; b = t; break;
                case 3: r = p; g = q; b = brightness; break;
                case 4: r = t; g = p; b = brightness; break;
                default: r = brightness; g = p; b = q; break;
            }

            image[3*idx + 0] = (unsigned char)(255 * r);
            image[3*idx + 1] = (unsigned char)(255 * g);
            image[3*idx + 2] = (unsigned char)(255 * b);
        }
    }

    stbi_write_png("newton.png", width, height, 3, image.data(), width*3);

    return 0;

}