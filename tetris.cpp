#include <stdio.h>
#include <iostream>

using namespace std;
void populateGrid();
void displayGrid();

char grid[20][10];

char rightL[2][3] = {{'*','*','A'}, 
                    {'A', 'A', 'A'}};

char leftL[2][3] = {{'B','*','*'}, 
                    {'B', 'B', 'B'}};

char zig[2][3] = {{'C','C','*'}, 
                  {'*', 'C', 'C'}};

char zag[2][3] = {{'*','D','D'}, 
                  {'D', 'D', '*'}};

char line[4] = {'E','E','E', 'E'};

char tBar[2][3] = {{'*','F','*'}, 
                  {'F', 'F', 'F'}};

char square[2][2] = {{'G','G'}, 
                  {'G', 'G'}};
//system("cls");

int main(void){
    populateGrid();
    displayGrid();

}

void populateGrid(){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
        grid[i][j] = '*';
    }
}
}

void displayGrid(){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            cout << grid[i][j] << " ";
        }
    cout << endl;
}
}

