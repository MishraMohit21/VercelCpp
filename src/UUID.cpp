#include "../include/UUID.h"

std::string generateID() {
    const std::string superset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    const int length = 5;
    
    // Seed the generator with current time plus a random device
    auto now = std::chrono::high_resolution_clock::now();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(
        now.time_since_epoch()).count();
    
    std::random_device rd;
    std::mt19937 gen(rd() ^ static_cast<unsigned int>(nanos));
    std::uniform_int_distribution<> distrib(0, superset.length() - 1);
    
    std::string id = "";
    for (int i = 0; i < length; i++) {
        id += superset[distrib(gen)];
    }
    
    return id;
}