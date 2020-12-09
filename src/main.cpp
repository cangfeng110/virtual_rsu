#include "light_message.h"
#include "callback.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>

#include "mqtt/async_client.h"
using namespace traffic_light;

const std::string SERVER_ADDRESS("tcp://localhost:1883");
const std::string CLIENT_ID("RSU");

const std::string SUB_TOPIC("/mqtt_backend/+/traffic_light_status");

const std::string PUB_TOPIC("/mqtt_backend/traffic_light_status");

int main() {
    mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);

    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);

    std::string file_name;
    std::cout << "please input light message file name:";
    std::cin >> file_name;
    LightMessage light_message(file_name);

    traffic_light::callback cb(client, connOpts, light_message, SUB_TOPIC);
    client.set_callback(cb);

    try {
        std::cout << "Connecting to MQTT server..." << std::flush;
        client.connect(connOpts, nullptr, cb);
        std::cout << "this is test" << std::endl;
    } catch (const mqtt::exception&) {
        std::cerr << "\nERROR: Unable to connect to MQTT server: '"
			<< SERVER_ADDRESS << "'" << std::endl;
		return 1;
    }

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (!light_message.flag_status())
            continue;
        std::string send_message = light_message.GetLightMessage();
        client.publish(PUB_TOPIC, send_message.c_str(), send_message.length(), 1, false);

    }
    return 0;
}