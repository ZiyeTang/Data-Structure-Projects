#pragma once

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(Point setCenter, unsigned setSpacing, double setIncrement, double setOriginalHue);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  Point center;
  unsigned spacing;
  double increment;
  double originalHue;
};
