#include "String.h"

String::Strin(int j){
	bufferSize = j;
	buffer = new char[bufferSize];
	buffer[0] = '\0';
}

String::String(const char *m){
	char *mCopy = m;
	int length = 0;
	while(*m != '\0'){
		m++;
		length++;
	}
	m = mCopy;
	bufferSize = length +1;
	buffer = new char[bufferSize];
	char *bufferCopy = buffer;
	while(*m != '\0'){
		*buffer = *m;
		m++;
		buffer++;
	}
	*buffer = '\0';
	buffer = bufferCopy;
	m = mCopy;
	delete [] mCopy;
}

String::String(const String &s){
	bufferSize = s.bufferSize;
	for(int i = 0; i < bufferSize; i++){
		buffer[i] = s.buffer[i];
	}
	buffer[bufferSize] = '\0';
}

String::~String(){
	bufferSize = 0;
	delete [] buffer;
	buffer = NULL;
}

int String::getLength(){
	int length = 0;
	char *bufferCopy = buffer;
	while(*bufferCopy != '\0'){
		bufferCopy++;
		length++;
	}
	return length;
}

bool String::empty() const{
	if(buffer[0] == '\0')
		return true;
	else
		return false;
}	

bool String::clear(){
	if(!empty()){
		buffer[0] = '\0';	
		return true;
	}
	else
		return false;
}

String& String::operator=(const String &s){
	if(this != &s){
		if(bufferSize != s.bufferSize)
			bufferSize = s.bufferSize;
		delete [] buffer;
		buffer = new char[bufferSize];
		int i = 0;
		while(s.buffer[i] != '\0'){
			buffer[i] = s.buffer[i];
			i++;
		}
		buffer[bufferSize] = '\0';
	}
	return *this;
}	

bool operator+(String &s, const String &s2){
	if(s2.buffer[0] != '\0' && s.buffer[0] != '\0'){
		char * sc = new char[s.bufferSize + s2.bufferSize +1];
		for(int i = 0; i<=s.getLength(); i++)
			sc[i] = s.buffer[i];
		for(int i = 0; i<=s2.getLength(); i++)
			sc[s.getLength() + i] = s2.buffer[i];
		delete [] s.buffer;
		s.buffersize += s2.bufferSize;
		s.buffer = new char[s.bufferSize];
		for(int i=0; i<s.bufferSize; i++)
			s.buffer[i] = sc[i]
		s.buffer[s.buffeSize] = '\0';
		delete [] sc;
		return true;
	}	
	else
		return false;
}

istream& operator >>(istream &k, string &s){
	int temp = 0;
	char * ctemp = new char[30];
	k >> ctemp;
	char *ctemphome = ctemp;
	while(*ctemp != '\0'){
		temp++;
		ctemp++;
	}
	ctemp = ctemphome;
	s.bufferSize = temp +1;
	delete [] s.buffer;
	s.buffer = new char[bufferSize];
	for(int i =0; i<=s.bufferSize; i++)
		s.buffer[i] = ctemp[i];
	delete [] ctemp;
	delete ctemphome;
	return k;
}

ostream& oerator<<(ostream &os, String &s){
	os << s.bufferSize << " " << s.buffer;
	return os;
}

char String::operator[](int i)const{
	if(i < 0 || i > bufferSize)
		return '\0';
	else
		char m;
		m = buffer[i];
		return m;
}
