#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <Windows.h>
#include <tuple>
#include <algorithm>
#include <typeinfo>
#include <conio.h>

using namespace std;
void populateGrid();
void displayGrid();
vector<vector<int>> spawnPeice(vector<vector<vector<char>>> chosenPeice);
vector<vector<int>> movePieceDown(vector<vector<int>> peicesCoords, bool alreadySpawned);
vector<vector<vector<char>>> selectRandomPeice();
bool canMoveDown(vector<vector<int>> peicesCoords, char peiceLetter);

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
    displayGrid();
    cout << getch();
    vector<vector<vector<char>>> chosenPeice = selectRandomPeice();
    vector<vector<int>> spawnedPeice = spawnPeice(chosenPeice);
    vector<vector<int>> newLocation = movePieceDown(spawnedPeice, true);
for(int i = 0 ; i < 7; i++){
    chosenPeice = selectRandomPeice();
    spawnedPeice = spawnPeice(chosenPeice);
    newLocation = movePieceDown(spawnedPeice, true);
}

    

    displayGrid();
//    bool reachedBottom = false;
//    while(reachedBottom == false){
        


//    }
}


void displayGrid(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            cout << grid[i][j] << " ";
        }
    cout << endl;
}
cout << endl;

cout.flush();
Sleep(500);
system("CLS");
}

vector<vector<vector<char>>> selectRandomPeice(){
    srand((unsigned)time(NULL));
    int random = rand() % 7;
    
    vector<vector<vector<char>>> possiblePeices[] = {tBar, line, zig, zag, rightL, leftL, square};

    return possiblePeices[random];
}

vector<vector<int>> spawnPeice(vector<vector<vector<char>>> chosenPeice){
    vector<vector<int>> peicesCoords;

    for(int i = chosenPeice[0].size() - 1; i > -1; i--){
        int start = 3;
        bool foundMoreLetter = false;

        for(int j = 0 ; j < chosenPeice[0][i].size() ; j++){
            if(chosenPeice[0][i][j] != '*'){
                grid[0][start] = chosenPeice[0][i][j];
                vector<int> coord = {0, start};
                peicesCoords.push_back(coord);

                foundMoreLetter = true;
            }  
            start++;
        }
        //After displaying grid move all peices down of current piece
        if(peicesCoords.size() != 0 && foundMoreLetter){
            vector<vector<int>> newCoords = movePieceDown(peicesCoords, false);
            peicesCoords = newCoords;
        }
        

    }
    return peicesCoords;
}

vector<vector<int>> movePieceDown(vector<vector<int>> peicesCoords, bool alreadySpawned){

    char peiceLetter = grid[peicesCoords[0][0]][peicesCoords[0][1]];

    for(int i = 0 ; i < peicesCoords.size(); i++){
        grid[peicesCoords[i][0]][peicesCoords[i][1]] = '*';
        peicesCoords[i][0]++;
        grid[peicesCoords[i][0]][peicesCoords[i][1]] = peiceLetter;
        
        
    }

    if(alreadySpawned && canMoveDown(peicesCoords, peiceLetter)){

        displayGrid();

        for(int i = 0 ; i < peicesCoords.size(); i ++){
            cout << peicesCoords[i][0] << " " << peicesCoords[i][1] << endl;       
        }

        movePieceDown(peicesCoords, alreadySpawned);
    }
    return peicesCoords;
}

bool canMoveDown(vector<vector<int>> peicesCoords, char peiceLetter){
    for(int i = 0 ; i < peicesCoords.size(); i++){
        if(peicesCoords[i][0]+1 > 19){
            cout << "Reached bottom";
            return false;
        }
        char toCheckBelow = grid[peicesCoords[i][0]+1][peicesCoords[i][1]];
        
        if(toCheckBelow != '*' && toCheckBelow != peiceLetter){
            cout << "BELOW STOPPEd";
                return false;
        }
    }
    return true;
}
