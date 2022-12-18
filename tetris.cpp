#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
//#include <Windows.h>
#include <tuple>
#include <algorithm>
//#include <conio.h>
#include <future>
#include <thread>
#include <unistd.h>
#include <ncurses.h>
//#include <boost/thread.hpp>

using namespace std;
void displayGrid();
vector<vector<int>> spawnpiece(vector<vector<vector<char>>> chosenpiece);
vector<vector<int>> movePieceDown(vector<vector<int>> piecesCoords, bool alreadySpawned);
vector<vector<vector<char>>> selectRandompiece();
vector<vector<int>> controller(char pieceLetter, char pressed, vector<vector<int>> piecesCoords);
bool canMoveDown(vector<vector<int>> piecesCoords, char pieceLetter);

enum gridSize { height = 20, width = 10 };

vector<char> row(width, '*');
vector<vector<char>> grid(height, row);



vector<vector<vector<char>>> rightL = {
    {{'*','*','A'},            
    {'A', 'A', 'A'},
    {'*', '*', '*'}},

    {{'*','A','*'},            
    {'*', 'A', '*'},
    {'*', 'A', 'A'}},

    {{'*','*','*'},            
    {'A', 'A', 'A'},
    {'A', '*', '*'}},

    {{'A','A','*'},            
    {'*', 'A', '*'},
    {'*', 'A', '*'}}
};

vector<vector<vector<char>>> leftL = {
    {{'C','*','*'},            
    {'C', 'C', 'C'},
    {'*', '*', '*'}},

    {{'*','C','C'},            
    {'*', 'C', '*'},
    {'*', 'C', '*'}},

    {{'*','*','*'},            
    {'C', 'C', 'C'},
    {'*', '*', 'C'}},

    {{'*','C','*'},            
    {'*', 'C', '*'},
    {'C', 'C', '*'}}
};

vector<vector<vector<char>>> zig = {
    {{'D','D','*'},            
    {'*', 'D', 'D'},
    {'*', '*', '*'}},

    {{'*','*','D'},            
    {'*', 'D', 'D'},
    {'*', 'D', '*'}},

    {{'*','*','*'},            
    {'D', 'D', '*'},
    {'*', 'D', 'D'}},

    {{'*','D','*'},            
    {'D', 'D', '*'},
    {'D', '*', '*'}}
};

vector<vector<vector<char>>> zag = {
    {{'*','E','E'}, 
    {'E', 'E', '*'},
    {'*', '*', '*'}},

    {{'*','E','*'},            
    {'*', 'E', 'E'},
    {'*', '*', 'E'}},

    {{'*','*','*'},            
    {'*', 'E', 'E'},
    {'E', 'E', '*'}},

    {{'E','*','*'},            
    {'E', 'E', '*'},
    {'*', 'E', '*'}}
};

vector<vector<vector<char>>> tBar = {
    {{'*','F','*'}, 
    {'F', 'F', 'F'},
    {'*', '*', '*'}},

    {{'*','F','*'}, 
    {'*', 'F', 'F'},
    {'*', 'F', '*'}},

    {{'*','*','*'}, 
    {'F', 'F', 'F'},
    {'*', 'F', '*'}},

    {{'*','*','*'}, 
    {'F', 'F', 'F'},
    {'*', 'F', '*'}}
};


vector<vector<vector<char>>> line = {
    {{'*', '*','*','*', '*'}, 
    {'*', '*', '*', '*', '*'},
    {'*', 'G', 'G', 'G', 'G'},
    {'*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*'}},

    {{'*', '*','*','*', '*'}, 
    {'*', '*', 'G', '*', '*'},
    {'*', '*', 'G', '*', '*'},
    {'*', '*', 'G', '*', '*'},
    {'*', '*', 'G', '*', '*'}},

    {{'*', '*','*','*', '*'}, 
    {'*', '*', '*', '*', '*'},
    {'G', 'G', 'G', 'G', '*'},
    {'*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*'}},

    {{'*', '*','G','*', '*'}, 
    {'*', '*', 'G', '*', '*'},
    {'*', '*', 'G', '*', '*'},
    {'*', '*', 'G', '*', '*'},
    {'*', '*', '*', '*', '*'}},
};

vector<vector<vector<char>>> square = 
                 {{{'H','H'}, 
                  {'H', 'H'}},

                  {{'H','H'}, 
                  {'H', 'H'}}};

int main(void){
    initscr();
    start_color();

    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(4, COLOR_CYAN, COLOR_CYAN);
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(6, COLOR_WHITE, COLOR_WHITE);
    init_pair(7, COLOR_BLUE, COLOR_BLUE);

    nodelay(stdscr, true);
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    displayGrid();

    

    while(1){
        vector<vector<vector<char>>> chosenpiece = selectRandompiece();
        vector<vector<int>> spawnedpiece = spawnpiece(chosenpiece);
        vector<vector<int>> newLocation = movePieceDown(spawnedpiece, true);

        for(int x = 0; x < height; x++){
            if(find(grid[x].begin(), grid[x].end(), '*') == grid[x].end()){
                for(int y = 0; y < width; y++){
                    grid[x][y] = '*';
                }
                displayGrid();
            }
            
        }
    }
    displayGrid();
    endwin();
    }
  

    



void displayGrid(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int color;

            switch(grid[i][j]){
                case 'A':
                    color = 1;
                    break;
                case 'C':
                    color = 2;
                    break;
                case 'D':
                    color = 3;
                    break;
                case 'E':
                    color = 4;
                    break;
                case 'F':
                    color = 5;
                    break;
                case 'G':
                    color = 7;
                    break;
                case 'H':
                    color = 4;
                    break;
                default:
                    color = 6;
                    break;
            }
            attron(COLOR_PAIR(color));
            mvprintw(i, j*3, "   ");
            attroff(COLOR_PAIR(color));
        }
    mvprintw(i, (width)*3, "\n");
}
refresh();
usleep(100000);
}

vector<vector<vector<char>>> selectRandompiece(){
    srand((unsigned)time(NULL));
    int random = rand() % 7;
    
    vector<vector<vector<char>>> possiblepieces[] = {tBar, line, zig, zag, rightL, leftL, square};

    return possiblepieces[random];
}

vector<vector<int>> spawnpiece(vector<vector<vector<char>>> chosenpiece){
    
    vector<vector<int>> piecesCoords;

    for(int i = chosenpiece[0].size() - 1; i > -1; i--){
        int start = 3;
        bool foundMoreLetter = false;

        for(int j = 0 ; j < chosenpiece[0][i].size() ; j++){
            if(chosenpiece[0][i][j] != '*'){
                if(grid[0][start] != '*'){
                    exit(1);
                }
                grid[0][start] = chosenpiece[0][i][j];
                vector<int> coord = {0, start};
                piecesCoords.push_back(coord);

                foundMoreLetter = true;
            }  
            start++;
        }
        //After displaying grid move all pieces down of current piece
        if(piecesCoords.size() != 0 && foundMoreLetter && canMoveDown(piecesCoords, grid[piecesCoords[0][0]][piecesCoords[0][1]])){
            displayGrid();
            vector<vector<int>> newCoords = movePieceDown(piecesCoords, false);
            piecesCoords = newCoords;
        }
        

    }
    return piecesCoords;
}

vector<vector<int>> movePieceDown(vector<vector<int>> piecesCoords, bool alreadySpawned){
    char pieceLetter = grid[piecesCoords[0][0]][piecesCoords[0][1]];

    if(alreadySpawned){
         piecesCoords = controller(pieceLetter, getch(), piecesCoords);
    }
   
    for(int i = 0 ; i < piecesCoords.size(); i++){
        grid[piecesCoords[i][0]][piecesCoords[i][1]] = '*';        
    }
    for(int i = 0 ; i < piecesCoords.size(); i++){
        piecesCoords[i][0]++;
        grid[piecesCoords[i][0]][piecesCoords[i][1]] = pieceLetter;      
    }
            

    if(alreadySpawned && canMoveDown(piecesCoords, pieceLetter)){

        displayGrid();
        movePieceDown(piecesCoords, alreadySpawned);
    }
    return piecesCoords;
}

bool canMoveDown(vector<vector<int>> piecesCoords, char pieceLetter){
    for(int i = 0 ; i < piecesCoords.size(); i++){
        if(piecesCoords[i][0]+1 > 19){
            return false;
        }
        char toCheckBelowEmpty = grid[piecesCoords[i][0]+1][piecesCoords[i][1]];
        vector<int> toCheckBelowSame = {piecesCoords[i][0]+1, piecesCoords[i][1]};

        if(toCheckBelowEmpty != '*' && find(piecesCoords.begin(), piecesCoords.end(), toCheckBelowSame) == piecesCoords.end()){
                return false;
        }
    }
    return true;
}

vector<vector<int>> controller(char pieceLetter, char pressed, vector<vector<int>> piecesCoords){

    vector<vector<int>> rotatedCoords;
    int originX = piecesCoords[1][0];
    int originY = piecesCoords[1][1];
    vector<int> rotated;

    switch(pressed){
    case 'a':
        for(int i = 0 ; i < piecesCoords.size(); i++){
            if(piecesCoords[i][1]-1 < 0 || (grid[piecesCoords[i][0]][piecesCoords[i][1]-1] != '*' && grid[piecesCoords[i][0]][piecesCoords[i][1]-1] != pieceLetter)){
                return piecesCoords;
            }
        }

        for(int i = 0 ; i < piecesCoords.size(); i++){
            grid[piecesCoords[i][0]][piecesCoords[i][1]] = '*';
            piecesCoords[i][1]--;
            grid[piecesCoords[i][0]][piecesCoords[i][1]] = pieceLetter;
        }
        return piecesCoords;
    case 'w':
        if(pieceLetter == 'H'){
            return piecesCoords;
        }

        else if(pieceLetter == 'D'){
            originX = piecesCoords[0][0];
            originY = piecesCoords[0][1];
        }

        for(int i = 0 ; i < piecesCoords.size(); i++){
            rotated = {piecesCoords[i][0] - originX, piecesCoords[i][1] - originY};
            
            int tempX = -rotated[0];
            rotated[0] = rotated[1];
            rotated[1] = tempX;
            rotated[0] += originX;
            rotated[1] += originY;
            
            if(rotated[0] > 19 || rotated[1] > 9 || rotated[1] < 0){
                exit(1);
            }
            
            rotatedCoords.push_back(rotated);
        }

        for(int j = 0 ; j < piecesCoords.size(); j++){
            grid[piecesCoords[j][0]][piecesCoords[j][1]] = '*';
            piecesCoords[j] = rotatedCoords[j];
            grid[piecesCoords[j][0]][piecesCoords[j][1]] = pieceLetter;
        }
        return piecesCoords;
    case 'd':
        for(int i = 0 ; i < piecesCoords.size(); i++){
            if(piecesCoords[i][1]+1 > 9 || (grid[piecesCoords[i][0]][piecesCoords[i][1]+1] != '*' && grid[piecesCoords[i][0]][piecesCoords[i][1]+1] != pieceLetter)){
                return piecesCoords;
            }
        }

        for(int i = 0 ; i < piecesCoords.size(); i++){
            grid[piecesCoords[i][0]][piecesCoords[i][1]] = '*';
            piecesCoords[i][1]++;
            grid[piecesCoords[i][0]][piecesCoords[i][1]] = pieceLetter;
        }
        return piecesCoords;
    case 's':
        if(!canMoveDown(piecesCoords, pieceLetter)){
            return piecesCoords;
        }

        for(int i = 0 ; i < piecesCoords.size(); i++){
            if(piecesCoords[i][0]+1 > 19){
                return piecesCoords;
            }
        }

        for(int i = 0 ; i < piecesCoords.size(); i++){
            grid[piecesCoords[i][0]][piecesCoords[i][1]] = '*';
            piecesCoords[i][0]++;
            grid[piecesCoords[i][0]][piecesCoords[i][1]] = pieceLetter;
        }
        return piecesCoords;
    default:
        displayGrid();
        return piecesCoords;

}
}