//headerfile - EmptyStackException.h
/*
Full name: Ariel Gutierrez
Student ID: 2318163
Chapman email: arigutierrez@chapman.edu
Course number and section: CPSC 350-01
Assignment or exercise number: Assignment 3

Assignment 3: A C++ program that uses a stack to analyze source code written in
any language and report the location of any mismatched delimiters.
*/

#include <stdexcept>
using namespace std;

class EmptyStackException : public runtime_error{
  public:
    EmptyStackException(const char* message) : runtime_error(message){}
};
