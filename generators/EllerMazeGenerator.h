#include "MazeGeneratorAbstract.h"

class EllerMazeGenerator : MazeGenerator {
    public:
        mazeStruct* generateMaze(int rows, int cols, int seed) override {
            //Initialize the maze
            mazeStruct *maze = new mazeStruct;
            maze->rows = rows;
            maze->cols = cols;

            maze->nodes = new mazeCell*[rows];
            for(int i = 0; i < rows; i++){
                maze->nodes[i] = new mazeCell[cols];
            }

            //Previous Row sets
            int* prevRow = new int[cols];
            //Current Row sets
            int* currRow = new int[cols];
            //Initialize both
            for(int i = 0; i < cols; i++){
                prevRow[i] = 0;
                currRow[i] = 0;
            }

            //Generate the maze starting with the top row
            //Use a two-line array to keep track of sets, then write to the mazeStruct after each row is generated.
            for(int row = 0; row < rows; row++){

            }
        };
};