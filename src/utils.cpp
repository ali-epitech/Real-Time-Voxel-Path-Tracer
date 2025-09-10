#include <random>

float randomFloat()
{
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator(std::random_device{}());
    return distribution(generator);
}
