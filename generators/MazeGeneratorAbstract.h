// Include guard so that this header is only loaded once
#ifndef _ABSTRACT_MAZE_GENERATOR_
#define _ABSTRACT_MAZE_GENERATOR_

#include <stdlib.h>
#include <iostream>

struct mazeCell{
    bool northPath = false;
    bool southPath = false;
    bool eastPath = false;
    bool westPath = false;
    bool visited = false; //has this cell been visited yet
};

struct mazeStruct{
    int rows;
    int cols;
    mazeCell** nodes; //Pointer to head of maze with specified width and height (in nodes)
};

class MazeGenerator {
    //TODO: Add a constructor?
    public:
        virtual mazeStruct* generateMaze(int rows, int cols, int seed) = 0;
};

#endif //end include guard