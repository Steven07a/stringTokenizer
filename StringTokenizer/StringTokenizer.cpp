// StringTokenizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

char* getToken(char c[] , const int ROW, int table[][127]) {
    int state = 0, pos = 0, pass = 0;
    //this is an error?
    char* temp = new char[];
    char* token = new char[];

    while (state != -1) {
        state = table[state][c[pos]];
        if (table[state][0] == 1) {
            pass = pos;
            temp = &c[pass];
        }
    }
    return temp;
}

int main()
{    
    const int ROW = 4, COLUMN = 127;
    int table[ROW][COLUMN];
    char s[] = "aaba";

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            table[i][j] = -1;
        }
    }
    table[0][97] = 1;
    table[1][97] = 1;
    table[1][98] = 2;
    table[2][97] = 3;
    table[3][97] = 3;
    table[0][0] = 0;
    table[1][0] = 1;
    table[2][0] = 0;
    table[3][0] = 1;

    cout << getToken(s,ROW,table) << endl;
    
    

    return 0;

}
