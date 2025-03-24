#include <cstdlib>
#include <string>
#include <iostream>
#include <filesystem>
#include <future>

std::future<bool> uploadFileViaNode(const std::string& id) {
    return std::async(std::launch::async, [id]() {
        std::string command = "node ./node/upload-bridge.js \"" + id + "\"";
        int result = system(command.c_str());
        return (result == 0); // Returns true if successful
    });
}

// Asynchronous function to download via Node.js
std::future<bool> downloadViaNode(const std::string& prefix) {
    return std::async(std::launch::async, [prefix]() {
        std::string command = "node ./node/download-bridge.js \"" + prefix + "\"";
        int result = system(command.c_str());
        return (result == 0); // Returns true if successful
    });
}

namespace fs = std::filesystem;

std::future<void> buildProject(const std::string& id) {

    return std::async(std::launch::async, [id]() {
        std::string projectPath = fs::absolute("output/" + id).string();
        std::string command = "cd " + projectPath + " && npm install && npm run build";

        std::cout << "Executing: " << command << std::endl;
        int result = std::system(command.c_str());

        if (result != 0) {
            std::cerr << "Error executing build command!" << std::endl;
        } else {
            std::cout << "Build completed successfully." << std::endl;
        }
    });

}