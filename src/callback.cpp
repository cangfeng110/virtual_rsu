#include "callback.h"
using namespace traffic_light;
callback::callback(mqtt::async_client& cli, mqtt::connect_options& connOpts,
                    LightMessage& lt_m, std::string topic)
            : nretry_(0),
            cli_(cli),
            connOpts_(connOpts),
            light_messages_(lt_m),
            topic_(topic) {}

void callback::reconnect() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    try {
        cli_.connect(connOpts_, nullptr, *this);
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        exit(1);
    }
}

	// Re-connection failure
void callback::on_failure(const mqtt::token& tok) {
    std::cout << "Connection attempt failed" << std::endl;
    if (++nretry_ > N_RETRY_ATTEMPTS)
        exit(1);
    reconnect();
}


// (Re)connection success
void callback::connected(const std::string& cause) {
    std::cout << "\nConnection success" << std::endl;
    std::cout << "\nSubscribing to topic '" << topic_ << "'\n"
                << "\nPress Q<Enter> to quit\n" << std::endl;

    cli_.subscribe(topic_, 0);
    light_messages_.set_flag(true);
}

// Callback for when the connection is lost.
// This will initiate the attempt to manually reconnect.
void callback::connection_lost(const std::string& cause) {
    std::cout << "\nConnection lost" << std::endl;
    if (!cause.empty())
        std::cout << "\tcause: " << cause << std::endl;

    std::cout << "Reconnecting..." << std::endl;
    nretry_ = 0;
    reconnect();
}

// Callback for when a message arrives.
void callback::message_arrived(mqtt::const_message_ptr msg) {
    std::cout << "Message arrived" << std::endl;
    std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
    std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;
    light_messages_.UpdateMessage(msg->to_string());
}

void callback::on_success(const mqtt::token& tok) {
		std::cout << "Subscription success";
		if (tok.get_message_id() != 0)
			std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
		auto top = tok.get_topics();
		if (top && !top->empty())
			std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
		std::cout << std::endl;
}

void callback::delivery_complete(mqtt::delivery_token_ptr tok) {
		std::cout << "\tDelivery complete for token: "
			      << (tok ? tok->get_message_id() : -1) << std::endl;
}