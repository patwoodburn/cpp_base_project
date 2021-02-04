#include <iostream>
#include <algorithm>
#include <array>
#include <functional>
#include <cstdlib>

#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>

#include "utils.h"
#include "inputparser.h"

#include "mqtt/async_client.h"

const std::string SERVER_ADDRESS	{ "tcp://localhost:1883" };
const std::string CLIENT_ID		{ "paho_cpp_async_consume" };
const std::string TOPIC 			{ "hello" };

const int QOS = 1;

int main(int argc, char* argv[]) {
   std::cout << "cat";
   std::string config_file = "/etc/some_test/some_test.ini";
   InputParser input(argc, argv);

   std::cout << "Hello, world!" << std::endl;

   if (input.cmdOptionExists("--help")) {
      std::cout << "help menue";
   }

   if (input.cmdOptionExists("-f")){
      config_file = input.getCmdOption("-f");
   }
   std::cout << "load config:" << config_file << std::endl;
   std::array<int, 10> s = {5, 1, 3, 4, 2, 9, 8, 6, 0, 7};
   std::array<int, 10> s2;
   std::copy(s.begin(), s.end(), s2.begin());
   BubbleSort(s2.begin(), s2.end());
   for (const auto &n: s) {
      std::cout << n << ' ';
   }
   std::cout << std::endl;
   for (const auto &n: s2) {
      std::cout << n << ' ';
   }
   std::cout << std::endl;
   auto result = std::find(s.begin(), s.end(), 2);
   std::cout << result - s.begin();
   std::cout << std::endl;

   std::array<int, 10> s3;
   CopySort(s.begin(), s.end(), s3.begin(), BubbleSort);
   for(const auto &n: s3) {
            std::cout << n << ' ';
   }
   std::cout << std::endl;

   // InputParser input(argc, argv);
   //  if(input.cmdOptionExists("-h")){
   //      // Do stuff
   //  }
   //  const std::string &filename = input.getCmdOption("-f");
   //  if (!filename.empty()){
   //      // Do interesting things ...
   //  }


   mqtt::async_client cli(SERVER_ADDRESS, CLIENT_ID);
   std::cout << "hello \n";

   auto connOpts = mqtt::connect_options_builder()
		.clean_session(false)
		.finalize();

	try {
		// Start consumer before connecting to make sure to not miss messages

		cli.start_consuming();

		// Connect to the server

		std::cout << "Connecting to the MQTT server..." << std::flush;
		auto tok = cli.connect(connOpts);

		// Getting the connect response will block waiting for the
		// connection to complete.
		auto rsp = tok->get_connect_response();

		// If there is no session present, then we need to subscribe, but if
		// there is a session, then the server remembers us and our
		// subscriptions.
		if (!rsp.is_session_present())
			cli.subscribe(TOPIC, QOS)->wait();

		std::cout << "OK" << std::endl;

		// Consume messages
		// This just exits if the client is disconnected.
		// (See some other examples for auto or manual reconnect)

		std::cout << "Waiting for messages on topic: '" << TOPIC << "'" << std::endl;

		while (true) {
			auto msg = cli.consume_message();
			if (!msg) break;
			std::cout << msg->get_topic() << ": " << msg->to_string() << std::endl;
		}

		// If we're here, the client was almost certainly disconnected.
		// But we check, just to make sure.

		if (cli.is_connected()) {
			std::cout << "\nShutting down and disconnecting from the MQTT server..." << std::flush;
			cli.unsubscribe(TOPIC)->wait();
			cli.stop_consuming();
			cli.disconnect()->wait();
			std::cout << "OK" << std::endl;
		}
		else {
			std::cout << "\nClient was disconnected" << std::endl;
		}
	}
	catch (const mqtt::exception& exc) {
		std::cerr << "\n  " << exc << std::endl;
		return 1;
	}

   return 0;
}