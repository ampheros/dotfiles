#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "stringM.h"


using namespace std;

struct symbol{
	char *name;
	int value;
	bool bonus;
};

struct reel {
	symbol *s;
};

void sInput(char *filename, symbol *psy, char *a, int c); //read in symbols file to symbol array
void configGeneration(symbol *psy, reel *r); //generate a random config
void printConfig(reel *r); //print the config to screen
void pick(reel *r); //function to print chosen reel & stop data

int main (){
	srand(time(NULL));

	//initialize and allocate symbol array
	symbol *psy;
	psy = new symbol[6];
	
	symbol *psyhome;
	psyhome = psy;
	

	//initialize and allocate reel array
	reel *r;
	r  = new reel[3];		
	//set a reel home pointer
	reel *rhome;
	rhome = r;

	symbol *sptr = (*r).s;
	
	
	char *filename; //used to open user chosen file
	char *a1; //tmp variable for symbol input function
	int c; //tmp variable for symbol function input

	int u; //contains chosen menu option

	//allocate the memory the symbols within the reels
	for(int i =0; i<3; i++){
		(*r).s = new symbol[10];
		r++;	
	}	
	r = rhome;

	//execute menu options with designated numbers
 	do{
                cout << "Slot Machine Simulator" << endl;
                cout << ":::::::::::::::::::::::::::::::::::::::::" << endl;
                cout << " 1. Read in symbols file" << endl;
                cout << " 2. Generate Configuration" << endl;
                cout << " 3. Print config to screen" << endl;
                cout << " 4. Pick a Stop an Reel" << endl;
                cout << " 0. Exit" << endl;
                cout << ":::::::::::::::::::::::::::::::::::::::::" << endl;
                cout << "Enter your selection: ";
                cin >> u;
                cout << endl;
    
                switch(u){
                        case 1:
                                sInput(filename, psy, a1, c);
                                break;
                        case 2:
                                configGeneration(psy, r);
                                break;
                        case 3:
                                printConfig(r); 
				break;
                        case 4:
                                pick(r);
                                break;
                }
        }while (u !=0 );

        cout << "Goodbye" << endl;

	//deallocate the char arrays with symbol array	
	for(int i=0; i<6; i++){
		delete [] (*psy).name;
		psy++;
	}
	//deallocate the symbol array
	psy = psyhome;
	delete [] psy;

	psy = psyhome = NULL;

	//deallocate the char arrays within the symbol array inside the reel array
	for(int i=0; i<10; i++){
		delete [] (*sptr).name;
		sptr++;
	}

	//deallocate the symbol array with the reel array;
	for(int i=0; i<3; i++){
		delete (*r).s;
		r++;
	}
	
	//deallocate the reel array	
	r = rhome;
	delete [] r;
	
	r = rhome = NULL;	
	

return 0;
}

void printConfig(reel *r){
	symbol *sptr = (*r).s; //pointer to symbol array with reel struct

	reel *rhome = r; //home pointer for reel

	cout << " Reel 1 /// Reel 2 /// Reel3 ///" << endl;	

	//loop through each stop
	for(int j =0; j<10; j++){
		cout << "Stop " << (j+1) << ": "; 
		
		//loop through each reel
		for(int i = 0; i < 3; i++){
			//output the data for that stop & reel
			cout << (*sptr).name << " - "
			<< (*sptr).value << " - ";
			if( (*sptr).bonus == 0)
				cout << "False";
			else 
				cout << "True";
		
			r++; //increment the reel
			cout << " ||| ";
		}
		cout << endl;
		r = rhome; //reset reel to base for next stop
		sptr++; //increment to next stop
	}

	sptr = (*r).s; //reset the sptr back to base symbol address

}

void configGeneration(symbol *psy, reel *r){
	int p;
	int k = 0;
	symbol *Opsy = psy;
	reel *rhome = r;
	symbol *sptr = (*r).s;

	for(int i=0; i<10; i++){
	
		for(int j=0; j<3; j++){
			p = rand()%6;
			for(int k =0; k<p; k++){
				psy++;
			
			}
			
		
			int l = stringLength( (*psy).name );
			(*sptr).name = new char[l+1];
			stringCopy( (*sptr).name, (*psy).name);
	
			(*sptr).value = (*psy).value;
			(*sptr).bonus = (*psy).bonus;
		
			psy = Opsy;
			r++;
		}
		r = rhome;
		sptr++;
	}
	r = rhome;
	sptr = (*r).s;
	psy = Opsy;
} 

void sInput(char *filename, symbol *psy, char *a, int c){
	symbol *Opsy = psy; //a home pointer for the symbol struct
	filename = new char[20]; //a temp array to hold filename chosen by user
	a = new char[10]; //temp char array to hold size for dynamic string length

	cout << "Input Filename: ";
	cin >> filename;

	fstream afile;
	afile.open(filename);

	//while the file is open read in every line
	while(afile >> a >> c){
		int l = stringLength(a); //get the string length of the tmp string
		(*psy).name = new char[l+1]; //allocate the length of the string +1 for the null character
		
		//copy over the data from the tmp variables
		stringCopy( (*psy).name, a); 
		(*psy).value = c;
		
		//check to see if the bonus value should be set to true or false
		if(c == 0)
			(*psy).bonus = false;
		else
			(*psy).bonus = true;
		psy++;
	}			

	afile.close();
	psy = Opsy; //set symbol array back to base addresss

	//deallocate the memory for the tmp filename and a arrays
	delete[] filename;
	filename = '\0';
	delete [] a;
	a = '\0';
}

void pick(reel *r){
	reel *rhome = r; //a home pointer for the reel pointer
	int Sreel; //to hold chosen reel
	int Sstop; //will hold chosen stop

	symbol *sptr = (*r).s; //pointer to symbol struct within reel

	//input data from user
	cout << "Pick a Reel (1-3): ";
	cin >> Sreel;
	cout << "Pick a Stop (1-10: ";
	cin >> Sstop;
	cout << endl;
	
	//increment by the chosen number -1 to accomodate for the array starting at 0 and not 1
	for(int i=0; i< (Sreel - 1); i++){
		r++;
	}

	for(int j=0; j < (Sstop - 1); j++){
		sptr++;
	}
	
	//output the chosen data
	cout << "Symbol: " << (*sptr).name << endl;
	cout << "Value: " << (*sptr).value << endl;

	if( (*sptr).bonus == 0)
		cout << "Bonus: False" << endl;
	else
		cout << "Bonus: True" << endl;
	cout << endl;
	
	//set reel struct back to base address
	r = rhome;
}
