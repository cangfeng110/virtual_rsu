#ifndef _TRAFFIC_LIGHT_MESSAGE_
#define _TRAFFIC_LIGHT_MESSAGE_
#include "thirdparty/nlohmann/json.hpp"

#include <fstream>
#include <string>
#include <iostream>

namespace traffic_light {

class LightMessage {
public:
    LightMessage(std::string file);
    bool UpdateMessage(std::string in);
    void set_flag(bool f) {flag_ = f;}
    bool flag_status() { return flag_;}
    std::string GetLightMessage() { return light_message_.dump();}

private:
    nlohmann::json light_message_;
    bool flag_;
};


}// namespace TRAFFIC_LIGHT

#endif