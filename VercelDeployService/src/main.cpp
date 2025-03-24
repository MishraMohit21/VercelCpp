#include <iostream>
#include <hiredis/hiredis.h>
#include "../include/aws.h"



int main() 
{


    redisContext* context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err) {
        std::cerr << "Redis connection error: " << (context ? context->errstr : "Unknown error") << std::endl;
        return 1;
    }

    std::cout << "Waiting for jobs..." << std::endl;
    while (true) {
        redisReply* reply = (redisReply*)redisCommand(context, "BRPOP build-queue 0");

        if (reply && reply->type == REDIS_REPLY_ARRAY && reply->elements == 2) 
        {
            std::string id = reply->element[1]->str;
            std::cout << "Processing id: " << id << std::endl;
            freeReplyObject(reply);
            
            std::string prefix = "Output/" + id; 
            downloadViaNode(prefix);

            buildProject(id);

            uploadFileViaNode(id);
        } 
        else 
        {
            std::cerr << "BRPOP failed or queue empty!" << std::endl;
            freeReplyObject(reply);
            break;
        }

    }




    redisFree(context);



}