#include <iostream>

class String{
	public:
		String(int = 10);
		String(const char*);
		String(const String &);
		~String();
		int getLength() const;
		bool empty() const;
		bool clear();
		String& operator=(const String &);
		char operator[](int) const;
		friend bool operator+(String&&, const String&);
		friend istream& operator >> (istream&, String&);
		friend ostream& operator << (ostream&, String&);
		
	private:
		int bufferSize;
		char *buffer;

};
