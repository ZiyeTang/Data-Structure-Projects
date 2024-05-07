#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile)
{
  // TODO: Part 2
  cs225::PNG png;
  png.readFromFile(inputFile);
  cs225::PNG result(png.width(), png.height());

  for(unsigned x = 0; x < png.width(); x++)
  {
    for(unsigned y = 0; y < png.height(); y++)
    {
      result.getPixel(x, y) = png.getPixel(png.width() - x-1, png.height() - y-1);
    }
  }
  result.writeToFile(outputFile);

}

cs225::PNG myArt(unsigned int width, unsigned int height) 
{
  cs225::PNG png(width, height);
  // TODO: Part 3
  for(unsigned int x = 0; x < width; x++)
  {
    for(unsigned int y = 0; y <height; y++)
    {
      cs225::HSLAPixel & pixel = png.getPixel(x, y);
      pixel.h = (14*x+12*y)%360 ;

      pixel.l = 0.5;
      pixel.s = 1;
      pixel.a = 1;
      
      
    }
  }
  return png;
}
