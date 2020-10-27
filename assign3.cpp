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

SyntaxChecker::SyntaxChecker(){
  myStack = new GenStack<char>;
  lineCount = 1;
}

SyntaxChecker::~SyntaxChecker(){
  //delete the elements in the stack and the instance of it
  delete myStack;
}

//checks the syntax, returns -1 if syntax is fine, o.w. returns line number
//where error occurs
int SyntaxChecker::checkSyntax(ifstream& ifs){
  string line;
  char want;
  bool breakWhile = false;
  while(getline(ifs,line)){
    //check for opening brace or closing brace
    for(int i = 0; i < line.length(); ++i){
      if(line[i] == '(' || line[i] == '{' || line[i] == '['){
        myStack->push(line[i]);
      }else if(line[i] == ')' || line[i] == '}' || line[i] == ']'){
        if(expectedDelim() != line[i]){
          cout << "Line " << lineCount << ": expected " << expectedDelim() <<
            " and found " << line[i] << endl;
          breakWhile = true;
          break;
        }else{
          try{
            myStack->pop();
          }catch(const EmptyStackException& e){
            cout << "Line " << lineCount << ": expected " << expectedDelim(line[i])
              << endl;
            breakWhile = true;
          }
        }
      }
    }
    if(breakWhile){
      break;
    }
    ++lineCount;
  }

  if(myStack->isEmpty() && !breakWhile){
    lineCount = -1;
    cout << "Reached end of file. The delimiter syntax is correct. " << endl;
    cout << endl;
  }else if(!myStack->isEmpty() && !breakWhile){
    cout << "Reached end of file: missing " << expectedDelim() << endl;
  }
  return lineCount;
}

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
