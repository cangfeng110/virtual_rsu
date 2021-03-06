#include "light_message.h"

#include <cstdlib>

using namespace traffic_light;

LightMessage::LightMessage(std::string file) {
    std::ifstream read_file(file);
    if (read_file.is_open()) {
        std::cout << "read traffic_light_status.json success" << std::endl;
        read_file >> light_message_;
    } else {
        std::cout << "read traffic_light_status.json failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    read_file.close();
};

bool LightMessage::UpdateMessage(std::string in) {
    try{
        auto& pre_lights = light_message_["params"]["lights"];
        nlohmann::json js_in = nlohmann::json::parse(in);
        auto& params = js_in["params"];
        if (params.find("lights") != params.end()) {
            auto& lights = params["lights"];
            for (auto& light : lights) {
                int id = light["id"];
                int status = light["state"];
                int dir = light["dir"];
                for (auto& pre_light : pre_lights) {
                    if (pre_light["id"] == id) {
                        pre_light["status"]["state"] = status;
                        std::cout << "change light id:" << id << " dir:" << dir << " state:" << pre_light["status"]["state"]  << std::endl;
                    }
                }
            }
            return true;
        } else
            return false;
    } catch (nlohmann::json::exception& exc) {
        std::cout << exc.what() << std::endl;
        return false;
    }
}

std::string LightMessage::GetLightMessage() {
    // auto& params = light_message_["params"];
    // if (params.empty())
    //     return std::string("light status empty");
    // params["attached_map"] = map_id;
    return light_message_.dump();
}