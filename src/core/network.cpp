#include "core/network.h"

#include <iostream>

using json = nlohmann::json;

namespace network_internal
{

class NetworkException : public std::exception
{
  const char* what() const noexcept override
  {
    std::string message = "Network exception. If you recieve this exception, the behavior you have encountered is ";
    message +=             "so unexpected that there is no specific exception written for it. It is very likely a ";
    message +=             "bug, and you are encouraged to submit a bug report.";
    return message.c_str();
  }
};

class LibCurlGeneralException : public NetworkException
{
  const char* what() const noexcept override
  {
    std::string message = "The cURL library has failed to run correctly. Try checking your firewall and other ";
    message +=            "network settings, and then try again. If this doesn't resolve the issue, submit a bug ";
    message +=            "report.";
    return message.c_str();
  }
};

class LibCurlInitException : public NetworkException
{
  const char* what() const noexcept override
  {
    std::string message = "The cURL library (an Internet library used by this application) could not start up ";
    message +=            "properly. Try checking your firewall and other network settings, and then try again. If ";
    message +=            "this doesn't resolve the issue, submit a bug report.";
    return message.c_str();
  }
};

class JsonException : public NetworkException
{
  const char* what() const noexcept override
  {
    std::string message = "Something has gone wrong while reading a JSON file from the server. This is almost ";
    message +=            "certainly a bug in the application. Please submit a bug report.";
    return message.c_str();
  }
};

size_t writeCallback(void* contents, size_t size, size_t nmemb, void* buffer)
{
  //This function recieves void pointers, but I need to cast them
  auto castedBuffer = static_cast<std::string*>(buffer);
  auto castedContents = static_cast<char*>(contents);

  //this is the actual size of contents
  size_t realSize = size * nmemb;

  castedBuffer->append(castedContents, realSize);
  return realSize;
} //function writeCallback

} //namespace network_internal

int network::latestTimestamp()
{
  try
  {
    CURL* curl;
    CURLcode res;
    std::string buffer;

    //Because the URL is very long, I have placed it on multiple lines
    std::string jsonURL = "http://rammb-slider.cira.colostate.edu/data/json/goes-16/full_disk/geocolor";
    jsonURL +=            "/latest_times.json";

    curl = curl_easy_init();
    if (curl != nullptr)
    {
      curl_easy_setopt(curl, CURLOPT_URL, jsonURL.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, network_internal::writeCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
      res = curl_easy_perform(curl);
      curl_easy_cleanup(curl);
      if (res != 0)
      {
        std::cerr << "ERROR in latestTimestamp: cURL returned error code " << res << std::endl;
        throw network_internal::LibCurlGeneralException();
      }
    }
    else
    {
      std::cerr << "Error in latestTimestamp: cURL failed init" << std::endl;
      throw network_internal::LibCurlInitException();
    }

    json j = json::parse(buffer);
    return j["timestamps_int"][0].get<int>();
  }
  catch (json::exception& e)
  {
    std::cerr << "Error in latestTimestamp: " << e.what() << std::endl;
    throw network_internal::JsonException();
  }
  catch (std::exception& e)
  {
    std::cerr << "Error in latestTimestamp: " << e.what() << std::endl;
    throw network_internal::NetworkException();
  }
} //function latestTimestamp
