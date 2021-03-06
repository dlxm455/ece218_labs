#include <iostream>
#include "Mstring.h"

Mstring :: Mstring() {
	str = NULL;
	length = 0;
}

Mstring :: ~Mstring() {
	if (str) delete[] str;
	str = NULL;
	length = 0;
}

void Mstring :: setString(char * s, int len) {
	if (str) delete[] str;
	str = new char[len];
	bcopy(s, str, len); // deep copy of given char arr 
	length = len;
}

void Mstring :: setString(Mstring &s) {
	if (str) delete[] str;
	int len = s.length;
	str = new char[len];
	bcopy(s.str, str, len); // deep copy from another Mstring str
	length = len;
}

char* Mstring :: getString() {
	int len = length;
	char * new_str = new char[len];
	bcopy(str, new_str, len); // deep copy of the internal str
	return new_str;
}

char Mstring :: charAt(int loc) {
	char c = str[loc];
	return c;
}

int Mstring :: append(char *s, int len) {
	int new_len = length + len;
	if (length != new_len) { //append string not empty
		char * new_str = new char[new_len];
		bcopy(str, new_str, length); // deep copy of internal str
		bcopy(s, new_str+length, len); // deep copy of given char array
		if (str) delete[] str;
		str = new_str;
		new_str = NULL;
		length = new_len;
	}
	return length;
}

int Mstring :: append(Mstring &s) {
	int new_len = length + s.length;
	if (length != new_len) { //append string not empty 
		char * new_str = new char[new_len];
		bcopy(str, new_str, length); // deep copy of internal str
		bcopy(s.str, new_str+length, s.length); // deep copy from another Mstring str 
		if (str) delete[] str;
		str = new_str;
		new_str = NULL;
		length = new_len;
	}
	return length;
}



// Facilitate find substring
bool Mstring::compareStartInd(int ind, Mstring &s) {
	for (int i = 0; i < s.length; i++) {
		if (str[ind+i] != s.str[i]) return false;
	}
	return true;
}
	
/*
bool Mstring :: findAndReplace(Mstring &s, Mstring &r) {

	char * new_str = NULL;
	int capacity = length;
	int new_length = 0;
	int i = 0;
	int copy_start = 0;
	while (i <= length - s.length) {
		if (compareFromInd(i, s)) {
				// create a new array with the same siddze of the original one
				if (new_str == NULL) new_str = new char[capacity];
				int new_length2 = new_length + i - copy_start + r.length;
				if (capacity < new_length2) { 
					// need to expand
					capacity *= 2;
					char * new_str2 = new char[capacity];
					bcopy(new_str, new_str2, new_length);
					delete[] new_str;
					new_str = new_str2;
					new_str2 = NULL;
				}
				
				bcopy(str+copy_start, new_str+new_length, i - copy_start);
				new_length += i - copy_start; // update new_length
				i += s.length; // update i
				copy_start = i; // update copy_start
				bcopy(r.str, new_str+new_length, r.length);
				new_length += r.length; // update new_length again
		}
		else i++;
	}
	
	if (i == length && new_length == 0) 
		return false; // not find
	
	if (i < length) { // not reach end, need last copy
		bcopy(str+copy_start, new_str+new_length, length - copy_start);
		new_length += length - copy_start;
	}

	delete[] str;
	str = new_str;
	new_str = NULL;
	length = new_length;

	return true;

}
*/

// only replace the first one if occurs
bool Mstring :: findAndReplace(Mstring &s, Mstring &r) {
	if (length < s.length) return false;	
	for (int i = 0; i <= length - s.length; i++) {
		if (compareStartInd(i,s)) { 
			int new_length = length - s.length + r.length;
			char * new_str = new char[new_length];
			bcopy(str, new_str, i); // deep copy of str from beginning to before substring
			bcopy(r.str, new_str + i, r.length); // deep copy of replaced string
			bcopy(str + i + s.length, new_str + i + r.length, length - i - s.length);
			// deep copy of str from after substring to end.

			if (str) delete[] str;
			str = new_str;
			new_str = NULL; // for safe
			length = new_length;
			return true;
		}
	}
	return false;
			
}

// if given character is uppercase change it to lowercase
char lowercase(char c) {
	char ret = c;
	if ( ret >= 'A' && ret <= 'Z')
		ret = ret+'a'-'A';
	return ret;
}

int Mstring :: compareToIgnoreCase(Mstring &s) {
		// define empty string > non empty string
		if (length == 0 && s.length != 0) return 1;
		if (length == 0 && s.length == 0) return 0;
		if (length != 0 && s.length == 0) return -1;

		int l1, l2;
		int min_len = (length < s.length) ? length : s.length;
		for (int i = 0; i < min_len; i++) {
			l1 = lowercase(str[i]); 
			l2 = lowercase(s.str[i]);	
			if (l1 > l2) return 1; // internal str is greater
			else if (l1 < l2) return -1;
		}
		if (length == s.length) return 0;
		else if (length < s.length) return -1;
		else return 1;
		
}


ostream &Mstring :: print(ostream &out) {
	if (length == 0) out << "empty string " << endl;	
	// out << "length: " << length << endl;
	for (int i = 0; i < length; i++) {
		out << str[i];
		if (i == length -1) out << endl;
	}
	return out;
}	



