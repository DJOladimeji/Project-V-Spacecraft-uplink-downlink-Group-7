#define CROW_MAIN  

#include "crow_all.h"  
#include <iostream>
#include <string>
#include <vector>
#include "string.h" 
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
using namespace crow;

#include "Buffer.h"

int main() {
	cout << "======================================================" << endl;
	cout << "Welcome to the space Spacecrafts Uplink/Downlink" << endl;
	cout << "======================================================" << endl;

	//create a read from file object 

	//the read from file object will call a methods to read the IP address from file

	//start counter 

	//write the different Route to recieve 
	//inside the routes will call the different class/functions that it needs to to handle the message 

	//example 
	crow::SimpleApp app;

	//recieve packets from the uplink/downlink in the ground 
	CROW_ROUTE(app, "/UD_Ground_Receive").methods(HTTPMethod::Post, HTTPMethod::Get, HTTPMethod::Put)
		([](const crow::request& req, crow::response& res) {
		string post = "POST";
		string method = method_name(req.method);

		int resultPost = post.compare(method);

		if (resultPost == 0) {
			crow::json::rvalue json_data = crow::json::load(req.body);
			//auto x = crow::json::load(req.body); 

			//check time

			//if of time reponsed with 503

			//else

			if (!json_data) {
				ostringstream contents;
				res.code = 400;
				res.write(contents.str());
			}

			//create a veriy_path object
			//call a method in the object and send it the json_data to verify path

			ostringstream contents;
			res.code = 200;
			res.write(contents.str());
		}
		else {
			ostringstream contents;
			res.code = 400;
			res.write(contents.str());
		}
		res.end();
			});

	//recieve Packets from the C&DH
	CROW_ROUTE(app, "/C&DH_Receive").methods(HTTPMethod::Post, HTTPMethod::Get, HTTPMethod::Put)
		([](const crow::request& req, crow::response& res) {
		string post = "POST";
		string method = method_name(req.method);

		int resultPost = post.compare(method);

		if (resultPost == 0) {
			crow::json::rvalue json_data = crow::json::load(req.body);

			//check time

			//if of time put in buffer
			/*Buffer buffer;
			buffer.add_to_Buffer(json_data);
			*/

			//else

			if (!json_data) {
				ostringstream contents;
				res.code = 400;
				res.write(contents.str());
			}

			//create a send_Route_Ground object 
			//call a method in the object and send it the json_data to ground

			ostringstream contents;
			res.code = 200;
			res.write(contents.str());
		}
		else {
			ostringstream contents;
			res.code = 400;
			res.write(contents.str());
		}
		res.end();
			});

	//revieve packets from C&DH
	//if out of time send to buffer and respond with 200



	app.port(23500).multithreaded().run();
	return 1;
}

