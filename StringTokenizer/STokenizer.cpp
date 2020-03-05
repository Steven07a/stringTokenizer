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
	mark_cells(_table, 0, MAX_ROWS, 0, MAX_COLUMNS, -1);

	//row 0 is reserved for the default state it will give us the proper
	//state to go to
	mark_cells(_table, 0, 0, '0', '9', Number);
	mark_cells(_table, 0, 0, ' ', ' ', Space);
	mark_cells(_table, 0, 0, 'A', 'Z', Word);
	mark_cells(_table, 0, 0, 'a', 'z', Word);
	mark_cells(_table, 0, 0, "\"(){}:';[]/,.<>*&^%$#@!_+-=`~?", Symbol);

	//row 1-3 reserved for number 1 pass, 2 neutral, 3 fail
	mark_cells(_table, 1, 3, '0', '9', Number);
	mark_cells(_table, 1, 2, '.', '.', Number + 1);
	mark_cells(_table, 1, 1, 0, 0, 1);
	mark_cells(_table, 2, 2, 0, 0, 0);

	//row 7-9 reserved for words 7 pass, 8 neutral, 9 fail
	mark_cells(_table, 7, 9, 'A', 'Z', Word);
	mark_cells(_table, 7, 9, 'a', 'z', Word);
	mark_cells(_table, 7, 7, 0, 0, 1);
	mark_cells(_table, 8, 8, 0, 0, 0);

	//sets row 10 to space space is always set as a pass state
	mark_cells(_table, 10, 10, ' ', ' ', Space);
	mark_cells(_table, 10, 10, 0, 0, 1);

	//row 4-6 reserved for symbols 4 pass, 5 neutral, 6 fail
	mark_cells(_table, 4, 6, "\"(){}:';[]/,.<>*&^%$#@!_+-=`~?", Symbol);
	mark_cells(_table, 4, 4, 0, 0, 1);
	mark_cells(_table, 5, 5, 0, 0, 0);
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