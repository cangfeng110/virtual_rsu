#ifndef _TRAFFIC_LIGHT_MESSAGE_
#define _TRAFFIC_LIGHT_MESSAGE_
#include "nlohmann/json.hpp"

#include<fstream>
#include <string>
#include <iostream>

namespace traffic_light {

class LightMessage {
public:
    LightMessage(std::string file);
    bool UpdateMessage(std::string in);
    std::string ReadMessage();

private:
    std::string file_name_;
    std::fstream fs_;
};


}// namespace TRAFFIC_LIGHT

#endif