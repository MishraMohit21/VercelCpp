#include "../include/HttpController.h"




int main() {


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



