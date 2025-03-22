#include "../include/HttpController.h"

Aws::SDKOptions awsOptions;
Aws::S3::S3Client* s3Client = nullptr;
std::string s3BucketName = "vercelbutbetter";


int main() {

    setupAws(); 

    drogon::app().registerHandler("/hello",
        [](const drogon::HttpRequestPtr& req,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
            handleHelloRoute(req, std::move(callback));
        });

    drogon::app().registerHandler("/deploy",
        [](const drogon::HttpRequestPtr& req, Callback&& callback) {
            handleDeployRoute(req, std::move(callback));
        }, {drogon::Post});

    // Start the server on port 3000
    drogon::app().addListener("0.0.0.0", 3000).run();

    return 0;
}