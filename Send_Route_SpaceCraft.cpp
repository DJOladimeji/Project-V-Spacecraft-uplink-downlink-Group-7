
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <curl/curl.h>

using json = nlohmann::json;
using namespace std;

// Callback function to write response data from cURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) 
{
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

void sendJsonPacketToUri(const std::string& jsonPacket) {
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        // Parse the JSON packet
        json packetData = json::parse(jsonPacket);

        // Extract the URI from the JSON packet
        std::string uri = packetData["URI"];

        if (!uri.empty()) {
            // Set the cURL options
            curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, NULL);  // Optional headers
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPacket.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonPacket.length());

            // Response data will be stored in this string
            std::string response_data;

            // Set the callback function to handle the response
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

            // Perform the cURL POST request
            res = curl_easy_perform(curl);

            // Check for errors
            if (res != CURLE_OK) {
                std::cerr << "cURL failed: " << curl_easy_strerror(res) << std::endl;
            }
            else {
                std::cout << "Packet sent successfully to " << uri << std::endl;
                std::cout << "Response: " << response_data << std::endl;
            }

            // Clean up cURL
            curl_easy_cleanup(curl);
        }
        else {
            std::cerr << "URI not found in the JSON packet." << std::endl;
        }
    }
    else {
        std::cerr << "cURL initialization failed." << std::endl;
    }
}


