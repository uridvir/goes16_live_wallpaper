#include <vector>

#include "lodepng.h"
#include "curl/curl.h"
#include "json.hpp"

//functions meant to be used internally by the core library
namespace image_internal
{
  /* This function inserts a raw image, with specified height, width, bitdepth (bytes * 8), x offset and y offset, 
   * into another image.
   */
  void insertChunk(std::vector<uint8_t>& out, const std::vector<uint8_t>& in, int width, int height, int bytes,
    int x_offset, int y_offset);
} //namespace image_internal

//functions to be used externally by the app or anyone using my core library
namespace image
{
  std::vector<unsigned char>& fetchImageFromServer();

  /* Stitches four raw images together into one image, with elements of images being placed (by index) like so:

   0  |  1
  ____|___
      |
   2  |  3
  */
  void stitchFourImages(std::vector<unsigned char>& out, const std::vector<unsigned char>* images,
    int width, int height, int bit_depth);
} //namespace image
