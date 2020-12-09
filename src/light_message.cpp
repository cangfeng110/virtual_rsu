#include "light_message.h"

using namespace traffic_light;

LightMessage::LightMessage(std::string file) {
    std::ifstream read_file(file);
    if (read_file.is_open()) {
        read_file >> light_message_;
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
                int dir = light["dir"];
                int status = light["state"];
                for (auto& pre_light : pre_lights) {
                    if (pre_light["id"] == id) {
                        for (auto& pre_status : pre_light["status"]) {
                            if (pre_status["dir"] == dir) {
                                pre_status["state"] = status;
                                std::cout << "change light id:" << id << " dir:" << dir << " state:" << pre_status["state"] << std::endl;
                            }
                        }
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