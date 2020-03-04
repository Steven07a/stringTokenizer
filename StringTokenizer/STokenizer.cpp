#include "STokenizer.h"
#include "C:/Users/Steven_Dev/Desktop/CS_Stuff/includes/table.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];


STokenizer::STokenizer() {
	set_string('\0');
	_pos = 0;
	make_table(_table);
}

STokenizer::STokenizer(char str[]) {
	_stringSize = strlen(str);
	_pos = 0;
	set_string(str);
	make_table(_table);
}

void STokenizer::set_table(int sRows, int eRows, int sCol, int eCol, int value) {
	//sets all numbers =  to NUMBER enum
	for (int i = sRows; i < eRows+1; i++) {
		for (int j = sCol; j < eCol+1; j++) {
			_table[i][j] = value;
		}
	}
}

bool STokenizer::done() {
	return (_pos <= _stringSize);
}

bool STokenizer::more() {
	return (_pos <= _stringSize);
}

void STokenizer::set_string(char str[]) {
	_stringSize = strlen(str);
	_pos = 0;
	for (int i = 0; i < MAX_BUFFER; i++) {
		_buffer[i] = 0;
	}
	for (int i = 0; str[i] != NULL; i++) {
		_buffer[i] = str[i];
	}
}

void STokenizer::make_table(int _table[][MAX_COLUMNS]) {
	//sets default value to -1
	//set_table(0, MAX_ROWS, 0, MAX_COLUMNS, -1);
	mark_cells(_table, 0, MAX_ROWS, 0, MAX_COLUMNS, -1);

	//sets all numbers =  to NUMBER enum
	set_table(0, 0, '0', '9', Number);
	set_table(1, 3, '0', '9', Number);
	set_table(1, 2, '.', '.', Number+1);
	set_table(1, 1, 0, 0, 1);
	set_table(2, 2, 0, 0, 0);

	//sets all Alpha  =  to Word enum
	set_table(0, 0, 'A', 'Z', Word);
	set_table(0, 0, 'a', 'z', Word);
	set_table(7, 9, 'A', 'Z', Word);
	set_table(7, 9, 'a', 'z', Word);
	set_table(7, 7, 0, 0, 1);
	set_table(8, 8, 0, 0, 0);

	//sets Spaces to space enum
	set_table(0, 0, ' ', ' ', Space);
	set_table(10, 10, ' ', ' ', Space);
	set_table(10, 10, 0, 0, 1);

	//sets all unknown/symbol  =  to symbol enum
	mark_cells(_table, 0, 0, "\"(){}:';[]/,.<>*&^%$#@!_+-=`~?", Symbol);
	mark_cells(_table, 4, 6, "\"(){}:';[]/,.<>*&^%$#@!_+-=`~?", Symbol);
	mark_cells(_table, 4, 4, 0, 0, 1);
	mark_cells(_table, 5, 5, 0, 0, 0);
	/*set_table(0, 0, 33, 46, Symbol);
	set_table(0, 0, 58, 64, Symbol);
	set_table(0, 0, 91, 96, Symbol);
	set_table(0, 0, 123, 126, Symbol);
	set_table(4, 6, 33, 47, Symbol);
	set_table(4, 6, 58, 64, Symbol);
	set_table(4, 6, 91, 96, Symbol);
	set_table(4, 6, 123, 126, Symbol);
	set_table(4, 4, 0, 0, 1);
	set_table(5, 5, 0, 0, 0);*/
}

bool STokenizer::get_token(int start_state, string& token) {
	start_state = _table[start_state][_buffer[_pos]];
	int new_state = start_state, startingPos = _pos, pass = _pos;
	token.clear();

	while (_table[new_state][0] != -1 && new_state != -1) {
		if (_buffer[_pos] == 0) {
			break;
		}
		new_state = _table[new_state][_buffer[_pos]];
		if (_table[new_state][0] == 1) {
			pass = _pos;
		}
		_pos++;
	}

	_pos = pass + 1;

	while (startingPos < _pos && _buffer[startingPos] > 0) {
		token.push_back(_buffer[startingPos]);
		startingPos++;
	}
	
	return (token != "");
}

STokenizer& operator>>(STokenizer& s, Token& t) {
	string temp = "";
	if (s.get_token(t.type(), temp)) {
		t = Token(temp, s._table[0][temp[0]]);
	}
	return s;
}