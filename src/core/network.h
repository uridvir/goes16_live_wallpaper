#include "curl/curl.h"
#include "json.hpp"

namespace network_internal
{
  //Exception thrown in case of failure
  class NetworkException;
}

//networking functions pertaining to downloading images from the Colorado State server
namespace network
{
  //checks the latest_times.json file on the server and returns the latest timestamp as an integer
  int latestTimestamp();

  //string representation of a timestamp
  struct DecodedTimestamp;

  DecodedTimestamp decodeTimestamp(const int timestamp);

  //fetches the four quarters of the image from the server, based on the timestamp
  void fetchImages(std::vector<std::vector<unsigned char>>& out, int& width, int& height, const int timestamp);
} //namespace network
