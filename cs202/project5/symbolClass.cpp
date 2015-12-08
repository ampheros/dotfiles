#include "symbolClass.h"

//constructor
symbol::symbol(){
	name = NULL;
	value = 0;
	bonus = false;
}

//destructor
symbol::~symbol(){
	delete [] name;
	name = NULL;
	value = 0;
	bonus = false;
}

//set the value
void symbol::setValue(int a){
	value = a;
}

//get the value
int symbol::getValue(){
	return value;
}

//set the bonus
void symbol::setBonus(bool a){
	bonus = a; 
}

//get the bonus
bool symbol::getBonus(){
	return bonus;
}

//allocate the memory for name by the amount "l"
void symbol::nameinit(int l){
	name = new char[l];
}

//copy a string to name
void symbol::nameInput(char *a){
	stringCopy(name, a);
}

//get the address of the first element in the name array
char* symbol::getName(){
	return name;
}

//print out the data for this element
void symbol::print(){
	cout << name << ", " << value << ", ";
	if(bonus == 0)
		cout << "false";
	else
		cout << "true";
}
