#include "gtest/gtest.h"
#include "core/image.h"

namespace
{

//print out raw images for testing
inline void printImage(const std::vector<uint8_t>& input, int width, int height, int bytes)
{
  //go through every pixel in a raster pattern
  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      //print pixel
      std::printf("(%d", input[y * width * bytes + x * bytes]);
      for (int i = 1; i < bytes; i++)
      {
        std::printf(", %d", input[y * width * bytes + x * bytes + i]);
      }
      std::printf(") ");
    }
    std::printf("\n");
  }
}

/*
 * The NOLINT tag is only necessary on the following test-cases because clang-tidy is needlessly pedantic. It threw
 * (at least) three separate warnings each unit test declaration and I didn't wan't to patch up a compile warning that
 * I didn't cause. Google, if you're reading this, please make your libraries lint without warnings, or at least
 * compile a list of warnings I must disable to get a clean lint.
 */

//test chunk insert function
TEST(Image, ChunkInsert) //NOLINT
{
  //dimensions of subimages
  const int width = 2;
  const int height = 2;

  //specified bitdepth
  const int bit_depth = 24;

  //convert the bitdepth to a number of bytes
  const int bytes = bit_depth / 8;

  //red square to be inserted
  const std::vector<uint8_t> redSquare = { 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0 };

  //top-left corner insert test
  {
    std::vector<uint8_t> output = std::vector<uint8_t>(4 * width * height * bytes);
    std::vector<uint8_t> expected =
    {
      255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0,
      255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    image_internal::insertChunk(output, redSquare, width, height, bytes, 0, 0);
    std::printf("Top left corner insert:\n");
    printImage(output, width * 2, height * 2, bytes);
    std::printf("\n");
    EXPECT_TRUE(output == expected) << "Top left corner insert doesn't match";
  }

  //top-right corner insert test
  {
    std::vector<uint8_t> output = std::vector<uint8_t>(4 * width * height * bytes);
    std::vector<uint8_t> expected =
    {
      0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0,
      0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    image_internal::insertChunk(output, redSquare, width, height, bytes, width, 0);
    std::printf("Top right corner insert:\n");
    printImage(output, width * 2, height * 2, bytes);
    std::printf("\n");
    EXPECT_TRUE(output == expected) << "Top right corner insert doesn't match";
  }

  //bottom-left corner insert test
  {
    std::vector<uint8_t> output = std::vector<uint8_t>(4 * width * height * bytes);
    std::vector<uint8_t> expected =
    {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0,
      255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0
    };
    image_internal::insertChunk(output, redSquare, width, height, bytes, 0, height);
    std::printf("Bottom left corner insert:\n");
    printImage(output, width * 2, height * 2, bytes);
    std::printf("\n");
    EXPECT_TRUE(output == expected) << "Bottom left corner insert doesn't match";
  }

  //bottom-right corner insert test
  {
    std::vector<uint8_t> output = std::vector<uint8_t>(4 * width * height * bytes);
    std::vector<uint8_t> expected =
    {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0,
      0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0
    };
    image_internal::insertChunk(output, redSquare, width, height, bytes, width, height);
    std::printf("Bottom right corner insert:\n");
    printImage(output, width * 2, height * 2, bytes);
    std::printf("\n");
    EXPECT_TRUE(output == expected) << "Bottom right corner insert doesn't match";
  }
}

//test image stitching function
TEST(Image, StitchFourImages) //NOLINT
{

  //dimensions of subimages
  const int width = 2;
  const int height = 2;

  //red, white, and blue squares with dimensions of 2x2 each and bitdpeth of 24
  const std::vector<uint8_t> redSquare = { 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0 };
  const std::vector<uint8_t> whiteSquare = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
  const std::vector<uint8_t> blueSquare = { 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255 };

  //specified bitdepth
  const int bit_depth = 24;

  //input to function of squares in specified order
  const std::vector<uint8_t> input[] = { redSquare, whiteSquare, blueSquare, whiteSquare };
  //expected result
  const std::vector<uint8_t> expectedResult =
  {
    255, 0, 0, 255, 0, 0, 255, 255, 255, 255, 255, 255,
    255, 0, 0, 255, 0, 0, 255, 255, 255, 255, 255, 255,
    0, 0, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255,
    0, 0, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255
  };

  //run stitching function
  std::vector<uint8_t> output;
  image::stitchFourImages(output, input, width, height, bit_depth);

  /* Make sure that sizes match before performing additional tests, otherwise a mismatch could lead to out-of-bounds
  element access and segmentation faults, not a good outcome for a unit test. */
  auto message = new char[100];
  std::sprintf(message, "output has size %d, but should have size %d!", output.size(), expectedResult.size());
  //If this assertion fails, a 100-byte memory leak is the least of my concerns
  ASSERT_EQ(expectedResult.size(), output.size()) << message; //NOLINT
  delete[] message;

  //convert the bitdepth to a number of bytes
  const int bytes = bit_depth / 8;

  //debugging output
  std::printf("Stitch test:\n");
  printImage(output, width * 2, height * 2, bytes);
  std::printf("\n");

  //now that the sizes have been checked, compare the vectors by pixel (3 elements when bitdepth is 24)
  for (int y = 0; y < height * 2; y++)
  {
    for (int x = 0; x < width * 2; x++)
    {
      //get the real index, accounting for the bitdepth
      const int i = y * width * 2 * bytes + x * bytes;
      //make sure that each pixel is the color that is expected
      for (int j = 0; j < bytes; j++)
      {
        auto message = new char[100];
        std::sprintf(message, "[%d, %d]: channel %d has value %d, should be %d", x + 1, y + 1, j + 1, output[i + j],
          expectedResult[i + j]);
        EXPECT_EQ(output[i + j], expectedResult[i + j]) << message;
      }
    }
  }
}

} //namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
