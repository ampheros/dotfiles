#include "symbolClass.h"

using namespace std;

void sInput(symbol *masterReel); //will read in symbol file to array
void printReel(symbol *masterReel, int size); //will print out the chosen symbol array
void configGenerate(symbol *masterReel, symbol *currentReel); //generate a random config
void chooseStop(symbol *currentReel); // choose a stop and print out its data to screen

int main(){
	symbol *masterReel = new symbol[6]; //array for symbol file data
	symbol *masterhome = masterReel;
	
	symbol *currentReel = new symbol[10]; //array for symbol config array
	symbol *currenthome = currentReel;
	
	int u; //int for menu options


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
                                sInput(masterReel); 
				//printMaster(masterReel, 6);
                                break;
                        case 2:
				configGenerate(masterReel, currentReel);                             
                                break;
                        case 3:
				printReel(currentReel, 10); 
                                break;
                        case 4:
				chooseStop(currentReel);                           
                                break;
                }
        }while (u !=0 );
	
	//deallocate symbol data array
	for(int i =0; i<6; i++){
		(*masterReel).~symbol();
		masterReel++;
	}
	masterReel = masterhome;
	delete [] masterReel;
	
	//deallocate config array 
	for(int i=0; i<6; i++){
		(*currentReel).~symbol();
		currentReel++;
	}
	currentReel = currenthome;
	delete [] currentReel;
return 0;
}


void chooseStop(symbol *currentReel){
	int wStop; //to hold chosen stop number
	symbol *currenthome = currentReel; //home pointer for symbol array
	
	//ask for and store chosen stop number
	cout << "Choose a stop (1-10): ";
	cin >> wStop;
	cout << endl;	
	
	//increment the reel -1 to get to the specified stop(1-10)
	for(int i=0; i < (wStop -1); i++)
		currentReel++;
	//output the data
	cout << "Stop " << wStop << " Data: " << endl;	
	(*currentReel).print();
	cout << endl << endl;
	
	//reset symbol array back to home
	currentReel = currenthome;
}

void sInput(symbol *masterReel){
	int c; //hold the int from symbol file
	symbol *reelhome = masterReel; //symbol home pointer

	//temp char array for filename and later for exact sizing of symbol char array
	char *a = new char[20]; 
	char *ahome = a;

	cout << "Input Filename: ";
	cin >> a;

	fstream afile;
	afile.open(a);
	//reset to be used for array sizing
	a = ahome;
	delete [] a;
	a = new char[10];
	
	//read in file until end of lines
	while(afile >> a >> c){
		int l = stringLength(a);
		(*masterReel).nameinit(l+1); //allocate the same amount of characters as "a" + null into the symbol array
		(*masterReel).nameInput(a); //copy a into symbol name array
		(*masterReel).setValue(c); //copy symbol file value to the array
		//check for bonus value
		if(c == 0)
			(*masterReel).setBonus(false);
		else
			(*masterReel).setBonus(true);
		
		masterReel++;
	}
	
	afile.close();
	masterReel = reelhome; //reset symbol array

	//deallocate the memory used for temp char array
	a = ahome;
	delete [] a;
	a = '\0';
}

void printReel(symbol *masterReel, int size){
	symbol *reelhome = masterReel; //symbol home pointer
	
	//user chooses how many array elements to print out with "size" parameter
	for(int i =0; i< size; i++){
		(*masterReel).print(); //print out the symbol data
		cout << endl;
		masterReel++; //go to next element symbol in array
	}
	cout << endl;
	masterReel = reelhome; //reset symbol pointer
}

void configGenerate(symbol *masterReel, symbol *currentReel){
	int p; // will hold randomly generated number
	symbol *masterhome = masterReel; //symbol home pointer
	symbol *currenthome = currentReel; //symbol home pointer for the config array used by program
	
	//temp char array for exact sizing
	char *a = new char[10];
	char *ahome = a;

	int vtmp; //temp value to hold random symbol value
	bool btemp; //temp value to hold random bonus value
	
	//loop through all 10 stops
	for(int i = 0; i<10; i++){
		p = rand()%6; //generate random #
		
		//increment the symbol data array by the random number generated
		for(int j = 0; j<p; j++)
			masterReel++;
		
		//copy symbol data array's name to temp array
		stringCopy(a, (*masterReel).getName() );
		
		int l = stringLength(a); //get the length
		
		(*currentReel).nameinit(l+1); //allocate enough memory
		
		//copy over the name to the config array
		(*currentReel).nameInput( (*masterReel).getName() );
		
		//copy the value to the config array
		vtmp = (*masterReel).getValue();	
		(*currentReel).setValue(vtmp);
		
		//copy the bonus to the config array
		btemp = (*masterReel).getBonus();
		(*currentReel).setBonus(btemp);
		
		masterReel = masterhome; //reset symbol data array
		currentReel++;	//increment the config array
	}
	currentReel = currenthome; //reset the config array
	
	//deallocate the memory for temp char "a"
	a = ahome;
	delete [] a;	
	a = '\0';
}


