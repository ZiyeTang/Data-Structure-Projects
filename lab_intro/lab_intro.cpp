/**
 * @file lab_intro.cpp
 * Implementations of image manipulation functions.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "lab_intro.h"

using cs225::HSLAPixel;
using cs225::PNG;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) 
{
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned int x = 0; x < image.width(); x++) {
    for (unsigned int y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) 
{
  double dist;
  for (unsigned int x = 0; x < image.width(); x++) 
  {
      for (unsigned int y = 0; y < image.height(); y++) 
      {
        dist = sqrt((x-centerX)*(x-centerX)+(y-centerY)*(y-centerY));
        HSLAPixel & pixel = image.getPixel(x, y);
        if(dist >= 160)
        {
          pixel.l = 0.2 * pixel.l;
        }
        else
          pixel.l = pixel.l * (1.0 - dist * 0.005);
      }
  }
  return image;  
}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) 
{

  for (unsigned int x = 0; x < image.width(); x++) 
  {
      for (unsigned int y = 0; y < image.height(); y++) 
      {
        HSLAPixel & pixel = image.getPixel(x, y);
        if(pixel.h > 113.5 && pixel.h < 293.5)
        {
          pixel.h = 216;
        }
        else
        {
          pixel.h = 11;
        }
      }
  }

  return image;
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs to be averaged together.
* @param secondImage The second of the two PNGs to be averaged together.
*
* @return The watermarked image.
*/

PNG watermark(PNG firstImage, PNG secondImage) 
{
  unsigned int commonWidth = secondImage.width();
  if (firstImage.width() < secondImage.width())
  {
    commonWidth = firstImage.width();
  }
  
  unsigned int commonHeight = secondImage.height();
  if (firstImage.height() < secondImage.height())
  {
    commonHeight= firstImage.height();
  }
  
  for (unsigned int x = 0; x < commonWidth; x++) 
  {
      for (unsigned int y = 0; y < commonHeight; y++) 
      {
        HSLAPixel & pixel1 = firstImage.getPixel(x, y);
        HSLAPixel & pixel2 = secondImage.getPixel(x, y);
        if(pixel2.l == 1.0)
        {
          pixel1.l+=0.2;
          if(pixel1.l > 1)
          {
            pixel1.l = 1;
          }
        }
      }
  }

  return firstImage;
}
