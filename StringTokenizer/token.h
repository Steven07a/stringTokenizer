#ifndef token_H_
#define token_H_
#include <iostream>
#include <string>
using namespace std;

enum Type { Number, Symbol, Word, Space, Garbage };

class Token
{
public:
    Token();
    Token(string str, int type);
    friend ostream& operator <<(ostream& outs, const Token& t);
    int type();
    string type_string();
    string token_str();
private:
    string _token;
    int _type;
};

#endif // !token_H_

