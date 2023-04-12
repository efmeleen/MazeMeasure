// Maze generators and the abstract class they're based on
#include "generators/MazeGeneratorAbstract.h"
#include "generators/DepthFirstSearchMazeGenerator.h"
#include "generators/EllerMazeGenerator.h"

//Prints maze to terminal using special characters and spaces
void visualizeMaze(mazeStruct* maze){
    // Initialize display matrix to be all walls
    int displayRows = maze->rows*2 + 1;
    int displayCols = maze->cols*2 + 1;
    int **display = new int*[displayRows];
    for(int i = 0; i < displayRows; i++){
        display[i] = new int[displayCols];
        for(int j = 0; j < displayCols; j++){
            display[i][j] = 1;
        }
    }

    //CARVE OUT MAZE FROM INITIALIZED DISPLAY ARRAY
    for(int row = 0; row<maze->rows; row++){
        for(int col = 0; col<maze->cols; col++){
            //center
            display[row*2 + 1][col*2 + 1] = 0;

            //north
            if(maze->nodes[row][col].northPath){display[row*2][col*2+1] = 0;}

            //west
            if(maze->nodes[row][col].westPath){display[row*2+1][col*2] = 0;}

            //south
            if(maze->nodes[row][col].southPath){display[row*2+2][col*2+1] = 0;}

            //east
            if(maze->nodes[row][col].eastPath){display[row*2+1][col*2+2] = 0;}
        }
    }

    for(int i = 0; i < displayRows; i++){
        for(int j = 0; j < displayCols; j++){
            if(display[i][j] == 1){
                std::cout << (char) 219 << (char) 219;
            }else {
                std::cout << "  ";
            }
        }
        std::cout << "\n";
    }
}

int main(){
    int rows;
    int cols;
    std::cout << "How many rows? ";
    std::cin >> rows;
    std::cout << "How many columns? ";
    std::cin >> cols;

    if(!std::cin.good()){
        std::cout << "You did not enter integers.";
        return 0;
    }

    // DEPTH FIRST SEARCH MAZE
    DFSMazeGenerator* dfsGenerator = new DFSMazeGenerator;
    mazeStruct *dfsMaze = dfsGenerator->generateMaze(rows, cols, 10);
    visualizeMaze(dfsMaze);

    // ELLER'S ALGORITHM MAZE
    EllerMazeGenerator* ellerGenerator = new EllerMazeGenerator;
    mazeStruct *ellerMaze = ellerGenerator->generateMaze(rows, cols, 10);
    visualizeMaze(ellerMaze);

    return 0;
}