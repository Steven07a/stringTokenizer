/*
 * Author: Steven Herrera
 * Project: String Tokenizer
 * Purpose: Takes in a string which then gets us all useable tokens
 *              a token being either one word or number 
 *              ex: "it was a token 1.23"
 *              the tokens would be: "it" " " "was" " " "a" "token" " " "1.23"
 * Notes: code cannot identify non english characters 
 *
 */

#include <iostream>
#include <iomanip>
#include "STokenizer.h"
#include "token.h"

using namespace std;

int main()
{    
    char s[] = "it was the night of october 17th. pi was still 3.14.בביי@#$י";
    Token t;
    STokenizer stk(s);

    cout << "original input: " << s << endl << endl;
    cout << "----------Tokenized----------\n";
    stk >> t;
    while (stk.more()) {
        cout << setw(10) << t.type_string() << setw(10) << t << endl;
        t = Token();
        stk >> t;
    }


    return 0;
}
