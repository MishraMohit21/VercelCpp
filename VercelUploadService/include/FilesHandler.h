#pragma once 
#include <git2.h>
#include <filesystem>
#include <string>
#include <vector>

bool cloneRepository(const std::string& repoUrl, const std::string& outputPath);


std::vector<std::string> getAllFiles(const std::string& filePath);
