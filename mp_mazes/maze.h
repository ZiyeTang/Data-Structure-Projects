/* Your code here! */
#pragma once
#include <ostream>
#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
using namespace std;
using namespace cs225;

class SquareMaze
{
    public:
        struct Grid
        {
            bool rightW;
            bool downW;
            Grid(bool setRightW, bool setDownW)
            { 
                rightW = setRightW;
                downW = setDownW;
            }
        };

        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG* drawMaze() const;
        PNG* drawMazeWithSolution();

    private:
        DisjointSets dsets;
        vector<vector<Grid>> maze;

        void randomlyRemoveWall(int width, int height);
        bool isolated(int x, int y);
};
