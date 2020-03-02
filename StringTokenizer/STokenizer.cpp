#include "STokenizer.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer() {
	_buffer[MAX_BUFFER] = { '\0' };
	_pos = 0;
	make_table(_table);
}

STokenizer::STokenizer(char str[]) {
	_buffer[MAX_BUFFER] = { '\0' };
	_pos = 0;
	set_string(str);
	make_table(_table);
}

bool STokenizer::done() {
	return (_buffer[_pos] > 0 ? true : false);
}

bool STokenizer::more() {
	return (_buffer[_pos] > 0 ? true : false);
}

void STokenizer::set_string(char str[]) {
	for (int i = 0; str[i] != NULL; i++) {
		_buffer[i] = str[i];
	}
}

void STokenizer::make_table(int _table[][MAX_COLUMNS]) {
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 0; j < MAX_COLUMNS; j++) {
			_table[i][j] = -1;
		}
	}
	//sets all numbers =  to NUMBER enum
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 48; j < 58; j++) {
			_table[i][j] = Number;
		}
	}

	//sets all Alpha  =  to Word enum
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 65; j < 91; j++) {
			_table[i][j] = Word;
			_table[i][j + 32] = Word;
		}
	}

	//sets Spaces to space enum
	for (int i = 0; i < MAX_ROWS; i++) {
		_table[i][32] = Space;
	}

	//sets all unknown/symbol  =  to symbol enum
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 33; j < 48; j++) {
			_table[i][j] = Symbol;
		}
	}
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 58; j < 65; j++) {
			_table[i][j] = Symbol;
		}
	}
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 123; j < 127; j++) {
			_table[i][j] = Symbol;
		}
	}


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
	return (token != "");
}

STokenizer& operator>>(STokenizer& s, Token& t) {
	string temp = "";
	if (s.get_token(t.type(), temp)) {
		t = Token(temp, s._table[0][temp[0]]);
	}
	return s;
}