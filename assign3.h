// header file - assign3.h
/*
Full name: Ariel Gutierrez
Student ID: 2318163
Chapman email: arigutierrez@chapman.edu
Course number and section: CPSC 350-01
Assignment or exercise number: Assignment 3

Assignment 3: A C++ program that uses a stack to analyze source code written in
any language and report the location of any mismatched delimiters.
*/

#include "GenStack.h"
#include <iostream> //input and output
#include <fstream> //read and open files
using namespace std;


class SyntaxChecker{
  private:
    GenStack<char> *myStack; //holds opening delimiters {,(,[
    int lineCount; //line number of file being analyzed
  public:
    SyntaxChecker(); //default constructor
    ~SyntaxChecker(); //destructor

    int checkSyntax(ifstream& ifs); //checks the syntax, returns -1 if syntax is fine, o.w. returns line number

    char expectedDelim(); //returns the closing delimiter that was expected
    char expectedDelim(char delim); //returns the opening delimiter that was expected
};
