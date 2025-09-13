#include <random>
#include <iostream>
#include <string>
#include <iomanip> // for std::setw
#include <cmath>   // for std::floor
#include <chrono>

float randomFloat()
{
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator(std::random_device{}());
    return distribution(generator);
}

void printProgressBar(int current, int total, int barWidth, std::chrono::steady_clock::time_point startTime)
{
    float progress = float(current) / total;
    int pos = int(barWidth * progress);

    // Calculate elapsed time
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

    std::cout << "\033[s"; // Save cursor position
    std::cout << "\033[999B"; // Move to bottom-most line
    std::cout << "\r[";

    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }

    std::cout << "] " << int(progress * 100.0) << "%";
    std::cout << " (" << current << "/" << total << ")";
    std::cout << " Elapsed: " << elapsed << "s";
    std::cout << std::flush;

    std::cout << "\033[u"; // Restore cursor position
}
