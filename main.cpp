//
//  main.cpp
//  sudokusolver
//
//  Created by Andy Kuang on 1/1/18.
//  Copyright © 2018 Andy Kuang. All rights reserved.
//

#include <stack>
#include <iostream>
using namespace std;

const int magicNumber = 9;

void parsePuzzle(string origPuzzle, char parsedPuzzle[magicNumber][magicNumber]){
    int i = 0;
    int j = 0;
    for (int k = 0; k < origPuzzle.length(); k++){
        if (j >= magicNumber){
            i++;
            j = 0;
        }
        parsedPuzzle[i][j] = origPuzzle[k];
        j++;
    }
}

void printPuzzle(char puzzle[magicNumber][magicNumber]){
    for (int i = 0; i < magicNumber; i++){
        if ((i+3)%3 == 0)
            cout << " ------------" << endl;
        cout << "|";
        for (int j = 0; j < magicNumber; j++){
            cout << puzzle[i][j];
            if ((j+1)%3 == 0)
                cout << "|";
        }
        cout << endl;
    }
}

bool checkRow(char puzzle[magicNumber][magicNumber], int rowNumber, int numberToCheck){
    for (int i = 0; i < magicNumber; i++){
        if (puzzle[rowNumber][i] == ('0' + numberToCheck))
            return false;
    }
    return true;
}
 
bool checkColumn(char puzzle[magicNumber][magicNumber], int columnNumber, int numberToCheck){
    for (int i = 0; i < magicNumber; i++){
        if (puzzle[i][columnNumber] == ('0' + numberToCheck))
            return false;
    }
    return true;
}
 
bool checkBox(char puzzle[magicNumber][magicNumber], int x, int y, int numberToCheck){
    int startX = x - x%3;
    int startY = y - y%3;
    for (int i = startX; i < startX+3; i++){
        for (int j = startY; j < startY + 3; j++){
            if (puzzle[i][j] == ('0' + numberToCheck))
                return false;
        }
    }
    return true;
}
 
bool checkCell(char puzzle[magicNumber][magicNumber], int x, int y, int numberToCheck){
    return checkRow(puzzle, x, numberToCheck) &&
        checkColumn(puzzle, y, numberToCheck) &&
        checkBox(puzzle, x, y, numberToCheck);
}

void solvePuzzle(char puzzle[magicNumber][magicNumber]){
    int x = 0;
    int y = 0;
    int numToFill = 1;
    stack<int> filledCellsX;
    stack<int> filledCellsY;
    stack<int> filledNumbers;
    while (x < magicNumber){
        if (y >= magicNumber){
            x++;
            y = 0;
            continue;
        }
        if (puzzle[x][y] != '0'){
            y++;
            continue;
        }
        if (numToFill > magicNumber){
            x = filledCellsX.top();
            filledCellsX.pop();
            y = filledCellsY.top();
            filledCellsY.pop();
            numToFill = filledNumbers.top() + 1;
            filledNumbers.pop();
            puzzle[x][y] = '0';
            continue;
        }
        
        if (checkCell(puzzle,x,y,numToFill) == true){
            puzzle[x][y] = '0' + numToFill;
            filledCellsX.push(x);
            filledCellsY.push(y);
            filledNumbers.push(numToFill);
            numToFill = 1;
            y++;
        }
        else
            numToFill++;
    }
 }

int main(int argc, const char * argv[]) {
    char sudokuPuzzle[magicNumber][magicNumber];
    string inputString = "";
    cout << "Please type in the sudoku puzzle you would like solved. Fill in blanks with a 0, and don't use any spaces." << endl;
    cin >> inputString;
    parsePuzzle(inputString, sudokuPuzzle);
    printPuzzle(sudokuPuzzle);
    solvePuzzle(sudokuPuzzle);
    cout << "\nThis is the final solution." << endl;
    printPuzzle(sudokuPuzzle);
    return 0;
}
