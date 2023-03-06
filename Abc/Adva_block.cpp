#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <cstring>
#include <openssl/sha.h>
#include <vector>
#include "gnuplot_i.hpp"

const uint32_t max_nonce = UINT32_MAX;

uint32_t proof_of_work(const std::string& header, const uint32_t target)
{
    uint32_t nonce = 0;
    unsigned char hash_value[SHA256_DIGEST_LENGTH];
    while (nonce < max_nonce)
    {
        std::string data = header + std::to_string(nonce);
        SHA256(SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash_value), SHA256_DIGEST_LENGTH, hash_value);
        uint32_t hash_num = 0;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        {
            hash_num += hash_value[i];
            hash_num <<= 8;
        }
        if (hash_num < target)
        {
            return nonce;
        }
        ++nonce;
    }
    return max_nonce;
}

int main(int argc, char* argv[])
{
    std::vector<uint32_t> difficulties {5, 10, 15, 20, 25, 30};
    std::vector<double> times;

    for (uint32_t difficulty : difficulties)
    {
        uint32_t target = 1 << (256 - difficulty);
        std::cout << "Difficulty target: " << target << std::endl;

        std::string block_header;
        std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> distribution(0, 25);
        for (int i = 0; i < 50; ++i)
        {
            block_header += ('a' + distribution(rng));
        }
        std::cout << "Header: " << block_header << std::endl;

        auto start_time = std::chrono::system_clock::now();
        uint32_t nonce = proof_of_work(block_header, target);
        auto end_time = std::chrono::system_clock::now();

        if (nonce != max_nonce)
        {
            std::cout << "Nonce: " << nonce << std::endl;
            auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
            double time_in_seconds = elapsed_time.count() / 1000000.0;
            std::cout << "Time: " << time_in_seconds << " seconds" << std::endl;
            times.push_back(time_in_seconds);
        }
        else
        {
            std::cout << "Failed" << std::endl;
        }

        std::cout << std::endl;
    }

    // Plot graph
    Gnuplot gp;
    gp << "set terminal pngcairo\n";
    gp << "set output 'graph.png'\n";
    gp << "set title 'Difficulty vs Time'\n";
    gp << "set xlabel 'Difficulty'\n";
    gp << "set ylabel 'Time (seconds)'\n";
    gp << "plot '-' with linespoints title 'Time'\n";
    for (int i = 0; i < difficulties.size(); i++) {
    std::cout << "Difficulty " << i << ": " << difficulties[i] << std::endl;
    std::cout << "Time " << i << ": " << times[i] << std::endl;
    }
    for (int i = 0; i < difficulties.size(); i++) {
    std::string difficulty_str = std::to_string(difficulties[i]);
    std::string time_str = std::to_string(times[i]);
    gp << time_str << " " << difficulty_str << "\n";
    }
    gp << "e\n";

    return 0;
}
