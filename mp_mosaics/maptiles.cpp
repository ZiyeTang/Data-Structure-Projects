/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    
    MosaicCanvas* resCanvas = new MosaicCanvas(theSource.getRows(),theSource.getColumns());

    map<Point<3>, int> dic;

    vector<Point<3>> aveColors;
   
    for(int i = 0; i<(int)(theTiles.size()); i++)
    {
        Point<3> convertedPointed=convertToXYZ(theTiles[i].getAverageColor());
        aveColors.push_back(convertedPointed);
        dic.insert(pair<Point<3>,int>(convertedPointed,i));
    }


    KDTree<3> aveColorTree(aveColors);

    for(int r=0; r<theSource.getRows(); r++)
    {
        for(int c=0; c<theSource.getColumns(); c++)
        {
            Point<3> target=convertToXYZ(theSource.getRegionColor(r, c));
            Point<3> nearestPoint=aveColorTree.findNearestNeighbor(target);
            TileImage* nearestTile=&theTiles[dic[nearestPoint]];
            resCanvas->setTile(r,c, nearestTile);
        }
    }
    return resCanvas;
}

