#include <cstdlib>
#include <memory>
#include <iostream>
#include <drogon/drogon.h>

#include "LRUCache.hpp"

using namespace drogon;

typedef std::function<void(const HttpResponsePtr &)> Callback;

class std::shared_ptr<LRUCache> cache;
 
//////////GET////////////////////////////////////////////////////////////////////////////////
void indexHandler(const HttpRequestPtr &request, Callback &&callback, const std::string& key) {
    Json::Value jsonBody;

    int cacheValue = cache->get(std::atoi(key.c_str()));

    jsonBody["response"] = cacheValue;

    auto response = HttpResponse::newHttpJsonResponse(jsonBody);
    callback(response);
}

////////POST/////////////////////////////////////////////////////////////////////////////////
void nameHandler(const HttpRequestPtr &request, Callback &&callback) {
    auto requestBody = request->getJsonObject();
    Json::Value jsonBody;

    if (requestBody == nullptr ||
        (!requestBody->isMember("key") || !requestBody->isMember("value"))) {

        jsonBody["success"]  = "false";
        jsonBody["error"]  = "Invalid request";
        auto response = HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(HttpStatusCode::k400BadRequest);

        callback(response);
        return;
    }

    int key  = requestBody->get("key", -1).asInt();
    int value = requestBody->get("value", -1).asInt();
    
    cache->put(key, value);

    jsonBody["success"]  = "true";
    auto response = HttpResponse::newHttpJsonResponse(jsonBody);
    callback(response);
}

///////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    if(argc <  3) {
        std::cout << "USAGE: ichaika_rest <threads_count> <capacity>" << std::endl;
        return 0;
    }

    uint thrds = atoi(argv[1] );
    uint capacity = atoi(argv[2] );
     
    cache = std::make_shared<LRUCache>(capacity);

    //   "address": "0.0.0.0",
    //   "port": 8091,
    //    addListener("0.0.0.0", 8091)
    app().loadConfigFile("../config.json")
        .registerHandler("/lrucache?key={key}", &indexHandler, {Get})
        .registerHandler("/lrucache", &nameHandler, {Post}).setThreadNum(thrds)
        .run();

    return EXIT_SUCCESS;
}
