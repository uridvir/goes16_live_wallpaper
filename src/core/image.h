#include <vector>

#include "lodepng.h"

//functions meant to be used internally by the image namespace
namespace image_internal
{
  /* This function inserts a raw image, with specified height, width, bitdepth (bytes * 8), x offset and y offset,
   * into another image.
   */
  void insertChunk(std::vector<uint8_t>& out, const std::vector<uint8_t>& in, int width, int height, int bytes,
    int x_offset, int y_offset);
} //namespace image_internal

//functions to be used externally
namespace image
{
  /* Stitches four raw images together into one image, with elements of images being placed (by index) like so:

   0  |  1
  ____|___
      |
   2  |  3
  */
  void stitchFourImages(std::vector<unsigned char>& out, const std::vector<unsigned char>* images,
    int width, int height, int bit_depth);
} //namespace image
