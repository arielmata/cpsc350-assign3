//implementation file - assign3.cpp
/*
Full name: Ariel Gutierrez
Student ID: 2318163
Chapman email: arigutierrez@chapman.edu
Course number and section: CPSC 350-01
Assignment or exercise number: Assignment 3

Assignment 3: A C++ program that uses a stack to analyze source code written in
any language and report the location of any mismatched delimiters.
*/

#include "assign3.h"

//default constructor
SyntaxChecker::SyntaxChecker(){
  myStack = new GenStack<char>;
  lineCount = 1;
}

//destructor
SyntaxChecker::~SyntaxChecker(){
  //delete the pointer to the stack
  delete myStack;
}

//SyntaxChecker: checks the syntax, returns -1 if syntax is fine, otherwise
//returns line number where the syntax error occurs
int SyntaxChecker::checkSyntax(ifstream& ifs){
  string line;
  bool breakWhile = false; //breakWhile = true if there is a syntax error while file doesn't end
  while(getline(ifs,line)){
    //check for opening brace or closing brace
    for(int i = 0; i < line.length(); ++i){
      if(line[i] == '(' || line[i] == '{' || line[i] == '['){
        //found opening delimiter, so push it to the stack
        myStack->push(line[i]);
      }else if(line[i] == ')' || line[i] == '}' || line[i] == ']'){
        //found closing delimiter
        try{
          if(expectedDelim() != line[i]){
            //closing delimiter is not the delimter we expected
            cout << "Line " << lineCount << ": expected " << expectedDelim() <<
              " and found " << line[i] << endl;
            breakWhile = true;
            break;
          }else{
            //closing delimiter is what we expected, so we remove the opening
            //delimiter from the stack
            myStack->pop();
          }
        }catch(const EmptyStackException& e){
          //This means that stack is empty so it is missing opening delimiter
          cout << "Line " << lineCount << ": expected " << expectedDelim(line[i])
            << endl;
          breakWhile = true;
          break;
        }
      }
    }
    if(breakWhile)
      break; //there is an syntax error in line so break from while loop.
    ++lineCount;
  }

  if(myStack->isEmpty() && !breakWhile){
    //reached end of file and stack is empty, and no error found so
    //Syntax in the file is correct
    lineCount = -1;
    cout << "Reached end of file. The delimiter syntax is correct. " << endl;
    cout << endl;
  }else if(!myStack->isEmpty() && !breakWhile){
    //reached end of file but stack is not empty, so there is a missing
    //closing delimiter
    cout << "Reached end of file: missing " << expectedDelim() << endl;
  }
  return lineCount;
}

//expectedDelim(): returns the expected closing delimiter
char SyntaxChecker::expectedDelim(){
  char expect;

  if(myStack->peek() == '('){
    expect = ')';
  }else if(myStack->peek() == '{'){
    expect = '}';
  }else if (myStack->peek() == '['){
    expect = ']';
  }

  return expect;
}


//expectedDelim(char delim) - overloaded: returns the expected opening delimiter
char SyntaxChecker::expectedDelim(char delim){
  char expect;

  if(delim == ')'){
    expect = '(';
  }else if(delim == '}'){
    expect = '{';
  }else if(delim == ']'){
    expect = '[';
  }

  return expect;
}
