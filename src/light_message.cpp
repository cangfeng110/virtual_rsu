#include "light_message.h"

using namespace traffic_light;

LightMessage::LightMessage(std::string file) : file_name_(file) {};

std::string LightMessage::ReadMessage() {
    fs_.open(file_name_, std::fstream::in);
    nlohmann::json js;
    if (fs_.is_open()) {
        fs_ >> js;
    }
    return js.dump();
}

bool LightMessage::UpdateMessage(std::string in) {
    fs_.open(file_name_, std::fstream::in);
    nlohmann::json old_message;
    if (fs_.is_open()) {
        fs_ >> old_message ;
    nlohmann::json
}