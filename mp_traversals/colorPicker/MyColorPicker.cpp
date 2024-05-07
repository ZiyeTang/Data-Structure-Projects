#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;


MyColorPicker::MyColorPicker(
  Point setCenter, unsigned setSpacing, double setIncrement, double setOriginalHue)
{
  center = setCenter;
  spacing=setSpacing;
  increment=setIncrement;
  originalHue=setOriginalHue;
}

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) 
{
  /* @todo [Part 3] */
  HSLAPixel pixel(originalHue, 1, 0.5);
  if((x-center.x)%spacing==0 &&(y-center.y)%spacing==0 )
  {
    originalHue+=increment;
  }
  if(originalHue>360)
    originalHue=originalHue-360;
  return pixel;
}
