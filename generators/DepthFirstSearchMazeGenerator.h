#include "MazeGeneratorAbstract.h"

#define NORTH 1
#define WEST 2
#define SOUTH 3
#define EAST 4

//All possible orders that the directions for expansion can be checked
//(Enumerated here to reduce random number generation)
//TODO: replace with something from C++
static constexpr int orders[24][4] = {
{NORTH,WEST,SOUTH,EAST},
{WEST,NORTH,SOUTH,EAST},
{SOUTH,NORTH,WEST,EAST},
{NORTH,SOUTH,WEST,EAST},
{WEST,SOUTH,NORTH,EAST},
{SOUTH,WEST,NORTH,EAST},
{SOUTH,WEST,EAST,NORTH},
{WEST,SOUTH,EAST,NORTH},
{EAST,SOUTH,WEST,NORTH},
{SOUTH,EAST,WEST,NORTH},
{WEST,EAST,SOUTH,NORTH},
{EAST,WEST,SOUTH,NORTH},
{EAST,NORTH,SOUTH,WEST},
{NORTH,EAST,SOUTH,WEST},
{SOUTH,EAST,NORTH,WEST},
{EAST,SOUTH,NORTH,WEST},
{NORTH,SOUTH,EAST,WEST},
{SOUTH,NORTH,EAST,WEST},
{WEST,NORTH,EAST,SOUTH},
{NORTH,WEST,EAST,SOUTH},
{EAST,WEST,NORTH,SOUTH},
{WEST,EAST,NORTH,SOUTH},
{NORTH,EAST,WEST,SOUTH},
{EAST,NORTH,WEST,SOUTH}
};

class DFSMazeGenerator : MazeGenerator {
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

            //Generate the maze
            //Starting node is maze->nodes[0][0]
            //TODO: use seed to seed random number generator
            recursiveCarve(maze, 0, 0, 1);

            //std::cout << "RETURNING GENERATED MAZE \n";

            return maze;
        };
    private:
        // Carves in a direction, or returns if there is no valid direction to carve in.
        void recursiveCarve(mazeStruct* maze, int cellX, int cellY, int depth){
            //Print recursion depth, for curiosity
            //std::cout << "Recursion depth: " << depth << "\n";
            
            //Short circuit, probably will never be run
            if(maze->nodes[cellX][cellY].visited){
                std::cout << "SHORT CIRCUITING DUE TO VISITING AN ALREADY VISITED CELL";
                return;
            }

            //Mark this cell as visited so that it can't be carved to again.
            maze->nodes[cellX][cellY].visited=true;
            
            int visitOrderRow = rand()%24;

            // Check each direction
            for(int i = 0; i < 4; i++){
                if(orders[visitOrderRow][i] == NORTH){
                    // If NORTH cell is within the grid and unvisited
                    if((cellX-1 >= 0 && cellX-1 < maze->rows) && !maze->nodes[cellX-1][cellY].visited){
                        //set path in this cell
                        maze->nodes[cellX][cellY].northPath = true;
                        //set path in future cell
                        maze->nodes[cellX-1][cellY].southPath = true;
                        //call this method for the future cell coordinates
                        recursiveCarve(maze, cellX - 1, cellY, depth+1);
                    }
                }

                if(orders[visitOrderRow][i] == WEST){
                    // If WEST cell is within the grid and unvisited
                    if((cellY-1 >= 0 && cellY-1 < maze->cols) && !maze->nodes[cellX][cellY-1].visited){
                        //set path in this cell
                        maze->nodes[cellX][cellY].westPath = true;
                        //set path in future cell
                        maze->nodes[cellX][cellY-1].eastPath = true;
                        //call this method for the future cell coordinates
                        recursiveCarve(maze, cellX, cellY-1, depth+1);
                    }
                }

                if(orders[visitOrderRow][i] == SOUTH){
                    // If SOUTH cell is within the grid and unvisited
                    if((cellX+1 >= 0 && cellX+1 < maze->rows) && !maze->nodes[cellX+1][cellY].visited){
                        //set path in this cell
                        maze->nodes[cellX][cellY].southPath = true;
                        //set path in future cell
                        maze->nodes[cellX+1][cellY].northPath = true;
                        //call this method for the future cell coordinates
                        recursiveCarve(maze, cellX+1, cellY, depth+1);
                    }
                }

                if(orders[visitOrderRow][i] == EAST){
                    // If EAST cell is within the grid and unvisited
                    if((cellY+1 >= 0 && cellY+1 < maze->cols) && !maze->nodes[cellX][cellY+1].visited){
                        //set path in this cell
                        maze->nodes[cellX][cellY].eastPath = true;
                        //set path in future cell
                        maze->nodes[cellX][cellY+1].westPath = true;
                        //call this method for the future cell coordinates
                        recursiveCarve(maze, cellX, cellY+1, depth+1);
                    }
                }
            }
            
            return;
        }
};