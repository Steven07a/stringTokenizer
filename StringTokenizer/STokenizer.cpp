#include "STokenizer.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer() {
	_buffer[MAX_BUFFER] = { '\0' };
	_pos = 0;
	make_table(_table);
}

STokenizer::STokenizer(char str[]) {
	_stringSize = strlen(str);
	_buffer[MAX_BUFFER] = { '\0' };
	_pos = 0;
	set_string(str);
	make_table(_table);
}

void STokenizer::set_table(int start, int end, int value) {
	//sets all numbers =  to NUMBER enum
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = start; j < end+1; j++) {
			_table[i][j] = value;
		}
	}
}

bool STokenizer::done() {
	return (_buffer[_pos] > 0 ? true : false);
}

bool STokenizer::more() {
	return (_pos <= _stringSize+1);
}

void STokenizer::set_string(char str[]) {
	for (int i = 0; str[i] != NULL; i++) {
		_buffer[i] = str[i];
	}
}

void STokenizer::make_table(int _table[][MAX_COLUMNS]) {
	//sets default value to -1
	set_table(0, MAX_COLUMNS, -1);

	//sets all numbers =  to NUMBER enum
	set_table(48, 57, Number);

	//sets all Alpha  =  to Word enum
	set_table(65, 90, Word);
	set_table(97, 123, Word);

	//sets Spaces to space enum
	set_table(32, 32, Space);

	//sets all unknown/symbol  =  to symbol enum
	set_table(33, 47, Symbol);
	set_table(58, 64, Symbol);
	set_table(91, 96, Symbol);
	set_table(123, 126, Symbol);
}

bool STokenizer::get_token(int start_state, string& token) {
	start_state = _table[start_state][_buffer[_pos]];
	int new_state = start_state, startingPos = _pos;
	token.clear();
	while (new_state == start_state) {
		//sets the state equal to the state we get from the table
		if (_buffer[_pos] > 0) {
			new_state = _table[new_state][_buffer[_pos]];
		} else {
			new_state = -1;
		}

		if (new_state == start_state) {
			_pos++;
		} else if (new_state == Symbol && _table[new_state][_buffer[_pos + 1]] == Number 
			&& _buffer[_pos + 1] > 0) {
			new_state = Number;
			_pos++;
		}
	}

	while (startingPos < _pos) {
		token.push_back(_buffer[startingPos]);
		startingPos++;
	}
	if (new_state == -1) {
		_pos++;
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