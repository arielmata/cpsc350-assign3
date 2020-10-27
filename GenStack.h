//template class: header and implementation file - GenStack.h
/*
Full name: Ariel Gutierrez
Student ID: 2318163
Chapman email: arigutierrez@chapman.edu
Course number and section: CPSC 350-01
Assignment or exercise number: Assignment 3

Assignment 3: A C++ program that uses a stack to analyze source code written in
any language and report the location of any mismatched delimiters.
*/

#include <iostream>
#include "EmptyStackException.h"
using namespace std;

template <typename T>
class GenStack{
  private:
    int top;
    int mSize;

    T *myArray;
  public:
    GenStack();
    GenStack(int maxSize);
    ~GenStack();

    void push(T data);
    T pop();
    T peek();

    bool isFull();
    bool isEmpty();
    int getSize();
    void resizeArray();
    void printArray();
};

//implementation of GenStack

//Default constructor with default size 128
template <typename T>
GenStack<T>::GenStack(){
  myArray = new T[128];
  mSize = 128;
  top = -1;
}

//Overloaded constructor with default size maxSize
template <typename T>
GenStack<T>::GenStack(int maxSize){
  myArray = new T[maxSize];
  mSize = maxSize;
  top = -1;
}

//destructor
template <typename T>
GenStack<T>::~GenStack(){
  delete myArray;
}

template <typename T>
void GenStack<T>::push(T data){
  if(isFull()){
    //resize Array
    resizeArray();
  }
  myArray[++top] = data;
}

template <typename T>
T GenStack<T>::pop(){
    if(isEmpty()){
      //throw excepetion
      throw EmptyStackException("Stack is full.");
    }else{
      return myArray[top--];
    }
}

template <typename T>
T GenStack<T>::peek(){
  if(isEmpty()){
    throw EmptyStackException("Stack is full.");
  }else{
    return myArray[top];
  }
}

template <typename T>
bool GenStack<T>::isFull(){
  return (top == mSize - 1);
}

template <typename T>
bool GenStack<T>::isEmpty(){
  return (top == -1);
}

template <typename T>
int GenStack<T>::getSize(){
  return (top + 1);
}

template <typename T>
void GenStack<T>::resizeArray(){
  int mSize = 2*mSize;
  T *newArray = new T[mSize];

  for (int i = 0; i < getSize(); ++i){
    newArray[i] = myArray[i];
  }
  delete[] myArray;
  myArray = newArray;
  delete newArray;
}

template <typename T>
void GenStack<T>::printArray(){
  cout << "S SIZE: " << getSize() << endl;
  cout << "TOP: " << top << endl;

  for(int i = 0; i < mSize; ++i){
    cout << "Q[" << i << "]: " << myArray[i];
    if(i != mSize-1){
      cout << " | ";
    }
  }
  cout << endl;
}
