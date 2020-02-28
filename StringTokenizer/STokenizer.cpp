#include "STokenizer.h"

STokenizer::STokenizer() {
	_buffer[0] = '\0';
	_pos = 0;
	make_table(_table);
}

STokenizer::STokenizer(char str[]) {
	_pos = 0;
	for (int i = 0; str[i] != NULL; i++) {
		_buffer[i] = str[i];
	}
	make_table(_table);
}

bool STokenizer::done() {
	return (_buffer[_pos] == NULL ? true : false);
}

bool STokenizer::more() {
	return (_buffer[_pos] != NULL ? true : false);
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
			_table[i + 32][j + 32] = Word;
		}
	}
}

bool STokenizer::get_token(int start_state, string& token) {
	int new_state = start_state, pass = -1, count = 0;
	while (new_state == start_state) {
		if (_pos > token.size()) {
			break;
		}
		//sets the state equal to the state we get from the table
		new_state = _table[new_state][token[_pos]];
		if (_table[new_state][0] == Word) {
			pass = _pos;
		}
		_pos++;
	}
	//this helps us keep track of where we ended and gives us the state we ended in
	_pos = pass + 1;
	start_state = new_state;

	while (count <= pass) {
		_buffer[count] = token[count];
		count++;
	}
	return (pass >= 0);
}