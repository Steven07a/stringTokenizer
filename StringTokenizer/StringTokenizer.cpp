// StringTokenizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include "STokenizer.h"
#include "token.h"

using namespace std;

int main()
{    
    char s[] = " hol� como estas";
    Token t;
    STokenizer stk(s);

    stk >> t;
    while (stk.more()) {
        cout << setw(10) << t.type_string() << setw(10) << t << endl;

        t = Token();
        stk >> t;
    }


    return 0;
}
