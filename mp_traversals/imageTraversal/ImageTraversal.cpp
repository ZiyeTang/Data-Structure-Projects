#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

bool ImageTraversal::withinTol(double tolerance,const HSLAPixel & p1, const HSLAPixel & p2)
{
  return calculateDelta(p1,p2)<tolerance;
}

ImageTraversal::Iterator::~Iterator()
{
  if(traversal!=NULL)
  {
    /*delete traversal;*/
    traversal=NULL;
  }
} 

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() 
{
  /** @todo [Part 1] */
  traversal=NULL;
}


ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point start)
{
  this->start=start;
  this->traversal=traversal;
  current=start;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() 
{
  /** @todo [Part 1] */
  if(!traversal->empty()) 
  {
    Point toAdd = traversal->pop();			
    unsigned x=toAdd.x;
    unsigned y=toAdd.y;
    double tolerance=traversal->tolerance;

    if((x+1)>=0&& (x+1) <traversal->png.width())
    {
      traversal->add(Point(x+1,y));
    }
    if((y+1)>=0&&(y+1) <traversal->png.height())
    {
      traversal->add(Point(x,y+1));
    }
    if((x-1)>=0&&(x-1) <traversal->png.width())
    {
      traversal->add(Point(x-1,y));
    }
    if((y-1)>=0&&(y-1) <traversal->png.height())
    {
      traversal->add(Point(x,y-1));
    }

    Point temp=traversal->peek();
    unsigned x2=temp.x;
    unsigned y2=temp.y;
    while(!traversal->empty() && (traversal->visited[x2][y2]||!traversal->withinTol(tolerance,traversal->png.getPixel(x2,y2),traversal->png.getPixel(start.x,start.y))))
    {
      traversal->pop();
      temp=traversal->peek();
      x2=temp.x;
      y2=temp.y;
    }
    current=temp;
    traversal->visited[current.x][current.y]=true;
  }	
  else 
  {
    traversal=NULL;
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) 
{
  /** @todo [Part 1] */
  bool thisEmpty = false; 
  bool otherEmpty = false;

  if (traversal == NULL) { thisEmpty = true; }
  if (other.traversal == NULL) { otherEmpty = true; }
  if (!thisEmpty)  { thisEmpty = traversal->empty(); }
  if (!otherEmpty) { otherEmpty = other.traversal->empty(); }
  if (thisEmpty && otherEmpty) return false; 
  else if ((!thisEmpty)&&(!otherEmpty)) return (traversal != other.traversal); 
  else return true; 
}

