/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 */

#pragma once

namespace cs225 {
    class HSLAPixel
    {
        public:
            double h;
            double s;
            double l;
            double a;
            HSLAPixel ();
            HSLAPixel (double hue, double saturation, double luminance);
            HSLAPixel (double hue, double saturation, double luminance, double alpha);
    };
}
