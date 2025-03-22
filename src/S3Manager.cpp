#include "../include/S3Manager.h"

void setupAws() 
{
    Aws::InitAPI(awsOptions);
    
    // Load AWS credentials
    std::string accessKeyId, secretAccessKey, endpoint;
    if (loadAwsCredentials(accessKeyId, secretAccessKey, endpoint)) {
        // Create AWS client configuration
        Aws::Client::ClientConfiguration clientConfig;
        if (!endpoint.empty()) {
            clientConfig.endpointOverride = endpoint;
        }
        
        // Create credentials object
        auto credentials = Aws::MakeShared<Aws::Auth::SimpleAWSCredentialsProvider>(
            "S3Credentials", accessKeyId, secretAccessKey);
        
        // Create S3 client
        s3Client = new Aws::S3::S3Client(credentials, clientConfig);
        
        std::cout << "AWS credentials loaded successfully" << std::endl;
    } else {
        std::cerr << "Failed to load AWS credentials, S3 upload functionality will be disabled" << std::endl;
    }
}

bool loadAwsCredentials(std::string& accessKeyId, std::string& secretAccessKey, std::string& endpoint) {
    try {
        std::ifstream configFile("./config/keys.json");
        if (!configFile.is_open()) {
            std::cerr << "Failed to open config file" << std::endl;
            return false;
        }
        
        Json::Value root;
        configFile >> root;
        
        accessKeyId = root["accessKeyId"].asString();
        secretAccessKey = root["secretAccessKey"].asString();
        endpoint = root["endpoint"].asString();
        
        return !accessKeyId.empty() && !secretAccessKey.empty();
    } catch (const std::exception& e) {
        std::cerr << "Error loading credentials: " << e.what() << std::endl;
        return false;
    }
}

// Function to upload a file to S3
std::string uploadFileToS3(const std::string& fileName, const std::string& localPath) {
    if (!s3Client) {
        return "";
    }
    
    try {
        // Read file content
        Aws::String filePath(localPath.c_str());
        std::shared_ptr<Aws::IOStream> fileContent = 
            Aws::MakeShared<Aws::FStream>("S3Upload", 
                                         filePath.c_str(), 
                                         std::ios_base::in | std::ios_base::binary);
        
        if (!fileContent->good()) {
            std::cerr << "Error opening file: " << localPath << std::endl;
            return "";
        }

        // Create upload request
        Aws::S3::Model::PutObjectRequest putObjectRequest;
        putObjectRequest.SetBucket(s3BucketName);
        putObjectRequest.SetKey(fileName);
        putObjectRequest.SetBody(fileContent);

        // Upload file to S3
        auto putObjectOutcome = s3Client->PutObject(putObjectRequest);
        
        if (putObjectOutcome.IsSuccess()) {
            // Construct the URL for the uploaded file
            std::string location = "https://" + s3BucketName + ".s3.amazonaws.com/" + fileName;
            return location;
        } else {
            std::cerr << "Error uploading file: " 
                      << putObjectOutcome.GetError().GetExceptionName() << " - " 
                      << putObjectOutcome.GetError().GetMessage() << std::endl;
            return "";
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception during file upload: " << e.what() << std::endl;
        return "";
    }
}
