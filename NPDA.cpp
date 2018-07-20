/*DFA Automata Project 1
	DFA.cpp

	Defines the functions created in DFA.h

	Created by: Randi Tinney
	Date last modified: 19 March 2018
*/
#include "NPDA.h"
#include <algorithm>
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <iostream>
#include <iterator>
#include <tuple>

using namespace std;

//Constructor
NPDA::NPDA(void)
{
}

//deconstructor
NPDA::~NPDA(void)
{
}

/* addState(string state)

	Adds a state to the vector<string> states
*/
void NPDA::addState(string state)
{
	states.push_back(state);
}

/* addToAlphabet(string symbol)

	Adds a new symbol to the vector<string> alphabet
*/
void NPDA::addToAlphabet(string symbol)
{
	alphabet.push_back(symbol);
}

/* addTransition(string src, string symbol, string dest)

	Adds a new transition to the map<pair<string, string>, string> transitions
	where the pair is created by the source state and symbol and the mapped to
	value is the destination state
*/
void NPDA::addTransition(string src, string symbol, char stackSymbol, string dest, string replaceStackChars)
{
	tuple<string, string, char> temp3Tuple(src, symbol, stackSymbol);
	pair<string, string> tempPair(dest, replaceStackChars);

	//temp = make_pair(src, symbol);

	transitions.insert(make_pair(temp3Tuple, tempPair));
}

/* reset()

	Resets the NPDA back to the initialState
*/
void NPDA::reset()
{
	currentState = initialState;
}

/* addFinalState(string state)

	Adds a final state the vector<string> finalStates
*/
void NPDA::addFinalState(string state)
{
	finalStates.push_back(state);
}

/*display()

	Displays the created NPDA to the console screen
*/
void NPDA::display()
{
	cout << "----------NPDA----------" << endl;
	cout << "<states>" << endl;
	for(int i = 0; i < states.size(); i++)
		cout << states[i] << " ";

	cout << endl;

	cout << "<alphabet>" << endl;

	for(int j = 0; j < alphabet.size(); j++)
		cout << alphabet[j] << " ";

	cout << endl;

	cout << "<transition>" << endl;

	for(std::map<tuple<string, string, char>, pair<string, string>::iterator k = transitions.begin(); k != transitions.end(); k++)
		cout << "(" << k->first.first << ", " << k->first.second << ", " << k->first.third << ") -> (" << k->second.first << ", " << k->second.second << ")" endl;

	cout << "<initial state>" << endl;

	cout << initialState << endl;
	
	cout << "<stack start>" << endl;
	
	cout << stack.begin() << endl;

	cout << "<final states>" << endl;

	for(int n = 0; n < finalStates.size(); n++)
		cout << finalStates[n] << " ";

	cout << endl;

	cout << "-------------------------" << endl;
}

void NPDA::addToStack(char symbl)
{
	stack.insert(stack.begin(), symbol);
}

/* isValid(string symbol)

	Returns true if the symbol is an element of the alphabet;
	Returns false if it isn't
*/
bool NPDA::isValid(string symbol)
{
	if(find(alphabet.begin(), alphabet.end(), symbol) != alphabet.end())
		return true;
	else
		return false;
}

void NPDA::outputStack()
{
	for(char s: stack)
	{
		cout << s;
	}
}

/* getCurrentState()

	Returns the currentState of the NPDA
*/
string NPDA::getCurrentState()
{
	return currentState;
}

char NPDA::getCurrentStackTop()
{
	return stack.front();
}

/* goToWith(string symbol)

	Sets the current state based on the value gotten
	from the mapping of the current state and the given symbol
*/
void NPDA::goToWith(string symbol, char stackTopSymbol)
{	
	tuple<string, string, char> tempTuple (currentState, symbol, stackTopSymbol);

	std::map<pair<string, string>, string>::iterator it = transitions.find(temp);
	
	string destination = it->second.first;
	
	string stackString = it->second.second;
	
	char stackSymbols[stack.length() + 1];
	
	strncpy(stackSymbols, stackString.c_str(), sizeof(stackSymbols));

	stack.erase(stack.begin());
	
	stack.insert(stack.begin(), stackSymbols, stackSymbols.length());
	
	currentState = destination;
}

/* isFinalState(string state)

	Returns true if the given state is a final state;
	Returns false if it isn't
*/
bool NPDA::isFinalState(string state)
{
	if(find(finalStates.begin(), finalStates.end(), state) != finalStates.end())
		return true;
	else
		return false;
}
