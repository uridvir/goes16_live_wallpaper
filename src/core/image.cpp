#include "image.h"

inline void image_internal::insertChunk(std::vector<uint8_t>& out, const std::vector<uint8_t>& in, int width,
  int height, int bytes, int x_offset, int y_offset)
{
  /* For the purposes of iterating through the image and copying, we need to account for the bitdepth in the
   * dimensions of the vector.
   */
  const int actual_width = width * bytes;
  const int actual_x_offset = x_offset * bytes;

  //Iterate through every byte of the input image
  for (int x = 0; x < actual_width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      /* Inserts the input image into the output image, byte by byte. To account for the x and y offset, we need to
       * substitute x for x + actual_x_offset and do the same for y and the y offset. Because we are addressing a
       * single-dimensional vector, we can't use multi-dimensional access operators. To account for this, we treat the
       * image like a flattened array.
       */
      out[(y + y_offset) * actual_width * 2 + x + actual_x_offset] = in[y * actual_width + x];
    }
  }
} //function insertChunk

void image::stitchFourImages(std::vector<unsigned char>& out, const std::vector<uint8_t>* images, int width,
  int height, int bit_depth)
{
  //Since the insertChunk function takes the bitdepth in bytes, we do a conversion:
  const int bytes = bit_depth / 8;

  //Initialize the output as an empty vector with the right capacity for the compound image
  out = std::vector<uint8_t>(4 * width * height * bytes);

  //Insert the top-left image
  image_internal::insertChunk(out, images[0], width, height, bytes, 0, 0);
  //Insert the top-right image
  image_internal::insertChunk(out, images[1], width, height, bytes, width, 0);
  //Insert the bootom-left image
  image_internal::insertChunk(out, images[2], width, height, bytes, 0, height);
  //Insert the bottom-right image
  image_internal::insertChunk(out, images[3], width, height, bytes, width, height);
} //function stitchFourImages
