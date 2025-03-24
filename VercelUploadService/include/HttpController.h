#pragma once

#include <drogon/drogon.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
#include <json/json.h>
#include "UUID.h"


using Callback = std::function<void(const drogon::HttpResponsePtr&)>;



void handleHelloRoute(const drogon::HttpRequestPtr& req, Callback&& callback);
void handleDeployRoute(const drogon::HttpRequestPtr& req, Callback&& callback);

