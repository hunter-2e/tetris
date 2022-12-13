#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <Windows.h>

using namespace std;
void populateGrid();
void displayGrid();
void spawnPeice(vector<vector<vector<char>>> chosenPeice);
vector<vector<vector<char>>> selectRandomPeice();

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
                 {{{'G','G'}, 
                  {'G', 'G'}},

                  {{'G','G'}, 
                  {'G', 'G'}}};

int main(void){
    vector<vector<vector<char>>> chosenPeice = selectRandomPeice();

    displayGrid();

    spawnPeice(chosenPeice);

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
}

vector<vector<vector<char>>> selectRandomPeice(){
    srand((unsigned)time(NULL));
    int random = rand() % 7;
    
    vector<vector<vector<char>>> possiblePeices[] = {tBar, line, zig, zag, rightL, leftL, square};

    return possiblePeices[random];
}

void spawnPeice(vector<vector<vector<char>>> chosenPeice){
    vector<tuple<int,int>> peicesCoords;

    for(int i = chosenPeice[0].size() - 1; i > -1; i--){
        int start = 3;
        for(int j = 0 ; j < chosenPeice[0][i].size() ; j++){
            if(chosenPeice[0][i][j] != '*'){
                grid[0][start] = chosenPeice[0][i][j];
                peicesCoords.emplace_back((0, start));
            }  
            Sleep(100);

            displayGrid();

            start++;
        }
        cout << endl;
        
    }
}


