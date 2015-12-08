#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "stringM.h"

using namespace std;

class symbol{
	public:
		symbol();
		~symbol();
		//functions for value
		void setValue(int);
		int getValue();
		
		//functions for bonus
		void setBonus(bool);
		bool getBonus();
		
		//functions for name
		void nameinit(int);
		void nameInput(char *a);
		char *getName();

		//print function
		void print();
	private:
		char *name;
		int value;
		bool bonus;
};
