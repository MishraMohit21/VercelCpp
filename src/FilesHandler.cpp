#include <iostream>

#include "../include/FilesHandler.h"

bool cloneRepository(const std::string& repoUrl, const std::string& outputPath) {
    // Initialize libgit2
    git_libgit2_init();
    
    // Clone the repository
    git_repository* repo = nullptr;
    int error = git_clone(&repo, repoUrl.c_str(), outputPath.c_str(), nullptr);
    
    // Free resources and shutdown libgit2
    if (repo) {
        git_repository_free(repo);
    }
    git_libgit2_shutdown();
    
    

    // Return true if successful, false otherwise
    return error == 0;
}

std::vector<std::string> getAllFiles(const std::string& filePath)
{
    std::vector<std::string> response;
    
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(filePath)) {
            if (std::filesystem::is_regular_file(entry)) {
                response.push_back(entry.path().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    
    return response;
}