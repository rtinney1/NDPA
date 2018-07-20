/* NDPA Automata Project 1
	main.cpp

	Uses the functions defined in NDPA.h to create a NDPA from a text file
	entered by the user. The user will enter the name of the file on the
	command line when running the program. The program will then create
	a NDPA and show the created NDPA once done. Then, the user will be prompted
	to enter a string and the program will return the path it took based
	on the defined transitions. The string will be reported as ACCEPTED if
	the last state is a final state or REJECTED if the last state is not a final
	state. The processing will also stop if a symbol entered is not in the reported
	alphabet

	Created by: Randi Tinney
	Date last modified: 19 March 2018
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <vector>
#include "NPDA.h"

using namespace std;

ifstream inFile;

/* check()
Will check the input of the file name. Will return true if the file is able
to be opened, and false if not.
*/
bool check (ifstream& inFile)
{
	if(!inFile)
		return false;
	else
		return true;
}

/* create(ifstream& inFile)

	Creates the NPDA with the given file.
	The file must be in the proper order as defined in the lab handout for it to work.
*/
void create(NPDA& npda, ifstream& file)
{
	string tempIn;
	string src;
	string symbol;
	char stackSymbol;
	string dest;
	string stackToReplace;

	//char ki;

	inFile >> tempIn; //get "states" tag
	inFile >> tempIn; //get first state

	while(tempIn.find("alphabet") == std::string::npos)
	{
		npda.addState(tempIn);
		inFile >> tempIn;
	}
	
	//tempIn = "alphabet" tag
	inFile >> tempIn; //get first alphabet symbol
	
	while(tempIn.find("stack alphabet") == std::string::npos)
	{
		npda.addToAlphabet(tempIn);
		inFile >> tempIn;
	}
	
	//tempIn = "stack alphabet" tag
	inFile >> stackSymbol; //get first stack alphabet symbol

	while(tempIn.find("transitions") == std::string::npos)
	{
		npda.addToStackAlphabet(stackSymbol);
		inFile >> stackSymbol;
	}

	inFile >> src;

	while(src.find("initial") == std::string::npos)
	{
		inFile >> symbol >> stackSymbol >> dest >> stackToReplace >> ws;

		npda.addTransition(src, symbol, stackSymbol, dest, stackToReplace);

		inFile >> src;
	}

	//src = "<initial " tag
	inFile >> tempIn; //skip states>
	inFile >> tempIn; //get initial state

	npda.initialState = tempIn; //set Initial state
	npda.reset(); //make sure NPDA starts at initial state

	inFile >> tempIn; //get "stack start" tag
	inFile >> stackSymbol;//get stack symbol
	
	npda.addToStack(stackSymbol);
	
	inFile >> tempIn; //get "<final " tag
	inFile >> tempIn; //get "states>" tage

	while(!inFile.eof())
	{
		inFile >> tempIn; //get final states
		npda.addFinalState(tempIn);
	}
}

int main(int argc, char* argv[])
{
	NPDA npda;
	string toProcess;
	string currentState;
	char stackTop;
	string sym;
	bool failed;

	if(argc == 1) //only one argument means the user failed to give a file
		cout << "usage: <prog_name> <file_name>" << endl;
	else
	{

		inFile.open(argv[1]);

		if(check(inFile))//check to see if the file is readable
		{
			create(npda, inFile); //create the NPDA

			npda.display(); //display created NPDA

			while(true)
			{
				npda.reset();//ensures the NPDA starts at the initial state
				cout << "Enter a string to process (Ctrl^C to end):";
				getline(cin, toProcess);

				failed = false;//boolean is used to see if there is a symbol entered
								//that was not part of the alphabet

				currentState = npda.getCurrentState();//get current state

				cout << "(" << currentState << ", " << toProcess << ", " << npda.getCurrentStackTop() << ")" << endl;//output current state (initial state)

				for (int i = 0; i < toProcess.length(); i++)
				{
					sym = toProcess[i]; //get char from string
					if(npda.isValid(sym))//checks to see if the symbol is an element of the alphabet
					{
						stackTop = npda.getCurrentStackTop();
						npda.goToWith(sym, stackTop); //changes the current state based on the transition from the previous current
											//state and the symbol recieved
						currentState = npda.getCurrentState();//get new current state
						toProcess.erase(toProcess.begin());
						
						cout << "|- (" << currentState << ", " << toProcess << ", ";
						
						npda.outputStack();
						
						cout << ")" << endl;
					}
					else//char was not an element of the alphabet
					{
						cout << " (Invalid symbol " << sym << ")";
						failed = true;
						break;//exit for loop
					}
		  		}

		  		if(!failed)
		  		{
		  			if(npda.isFinalState(currentState))//checks to see if the string passed or not
		  				cout << " : ACCEPTED" << endl;
					else
						cout << " : REJECTED" << endl;
				}
				else
					cout << " : REJECTED" << endl;//for when a symbol isn't in the alphabet
			}
		}
		else
			cout << "Automata file could not be opened!" << endl;
	}

	return 0;
}
