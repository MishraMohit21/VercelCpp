#pragma once

#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <json/json.h>

Aws::SDKOptions awsOptions;
Aws::S3::S3Client* s3Client = nullptr;
std::string s3BucketName = "vercelbutbetter";

void setupAws();
bool loadAwsCredentials(std::string& accessKeyId, std::string& secretAccessKey, std::string& endpoint);
std::string uploadFileToS3(const std::string& fileName, const std::string& localPath);
