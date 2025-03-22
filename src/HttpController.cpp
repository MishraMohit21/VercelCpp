#include "../include/HttpController.h"
#include "../include/FilesHandler.h"
// #include "HttpController.h"


void handleHelloRoute(const drogon::HttpRequestPtr &req, Callback &&callback)
{
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setBody("Hello, World!");
    callback(resp);

}


void handleDeployRoute(const drogon::HttpRequestPtr& req, Callback&& callback) {
    if (req->getMethod() != drogon::HttpMethod::Post) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k405MethodNotAllowed);
        resp->setBody("Only POST method is allowed");
        callback(resp);
        return;
    }

    std::string repoUrl;
    auto params = req->getParameters();
    if (params.find("url") != params.end()) {
        repoUrl = params["url"];
    } else {
        try {
            auto json = req->getJsonObject();
            if (json && json->isMember("url")) {
                repoUrl = (*json)["url"].asString();
            }
        } catch (...) {
            // Create JSON error response
            Json::Value error;
            error["error"] = "No link provided";
            
            auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
            resp->setStatusCode(drogon::k400BadRequest);
            callback(resp);
            return;
        }
    }

    // Not really needed but for extra safety testing
    if (repoUrl.empty()) {
        // Create JSON error response
        Json::Value error;
        error["error"] = "No link provided";
        
        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
        resp->setStatusCode(drogon::k400BadRequest);
        callback(resp);
        return;
    }

    const std::string id = generateID();
    
    const std::string presentDir = std::filesystem::current_path().string();

    std::string outputDir = presentDir + "/Output/" + id;
    std::filesystem::create_directories("./Output");

    bool cloneSuccess = cloneRepository(repoUrl, outputDir);

    if (!cloneSuccess) {
        
        const git_error* lastError = git_error_last();
        Json::Value error;
        error["error"] = "Failed to clone repository";
        if (lastError) {
            error["details"] = lastError->message;
        }
        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
        resp->setStatusCode(drogon::k500InternalServerError);
        callback(resp);
        return;

    }


    std::vector<std::string> filesList = getAllFiles(outputDir);

    for (auto& file : filesList) {
        std::cout << "[" << file << "]\n"; 
    }

    // Create JSON response
    Json::Value result;
    result["id"] = id;
    result["repoUrl"] = repoUrl;   
    result["Cloned"] = cloneSuccess;  
    
    auto resp = drogon::HttpResponse::newHttpJsonResponse(result);
    callback(resp);
}
