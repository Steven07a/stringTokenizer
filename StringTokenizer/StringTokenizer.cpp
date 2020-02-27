// StringTokenizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

bool getToken(char c[] , const int ROW, int table[][127], char*& position, int &currentState, char*& token, const int BUFFER) {
    int state = 0, pos = 0, pass = -1, count = 0;

    while (state != -1) {
        if (pos > BUFFER) {
            break;
        }
        //sets the state equal to the state we get from the table
        state = table[state][c[pos]];
        if (table[state][0] == 1) {
            pass = pos;
        }
        pos++;
    }
    //this helps us keep track of where we ended and gives us the state we ended in
    position = &c[pass+1];
    currentState = state;

    //here we create a new char array give it a size of pass which is the position of the last passing variable plus 2
    //we give it a plus 2 because the char needs an ending char '/0' otherwise it will print gibberish
    char* temp = new char[pass+2] {NULL};

    while (count <= pass) {
        temp[count] = c[count];
        count++;
    }
    token = temp;
    return (pass >= 0);
}

int main()
{    
    const int ROW = 4, COLUMN = 127, BUFFER = 17;
    int table[ROW][COLUMN], state = 0;
    char ch[] = "aaaaaaaabcaaaaaaa";
    char* position = ch;
    char* token;

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

    if (getToken(ch, ROW, table, position, state, token, BUFFER)) {
        cout << "token: " << token << endl;
    }

    return 0;

}
