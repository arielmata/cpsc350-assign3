//main file - main.cpp
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

int main(int argc, char** argv){
  if(argc < 2){
    //No command line arguments were given
    cout << endl;
    cout << "No source code file was given. Please try again." << endl;
    cout << "Exiting Program." << endl;
    return 0;
  }else if(argc > 2){
    //More than one command line argument was given
    cout << endl;
    cout << "More than one file was given. Please try again." << endl;
    cout << "Exiting Program." << endl;
    return 0;
  }else if(argc == 2){
    //One command line argument was given
    string fileName = argv[1];
    ifstream infile;
    infile.open(fileName);
      if(infile.fail()){
        //Can't open the file
        cout << endl;
        cout << "The given file is not accessible." << endl;
        cout << "Exiting program." << endl;
        infile.close();
        return 0;
      }else{
        //Can open file
        while(true){
          //isAsking = false if there is error in command line argument file,
          //or if user doesn't want to analyze another file
          bool isAsking = true;
          SyntaxChecker *sc = new SyntaxChecker();
          int lineNum = sc->checkSyntax(infile); //Run program to check syntax
          infile.close(); //close the file when done
          delete sc; //delete pointer

          if (lineNum > 0){
            //there is an error in the syntax
            isAsking = false;
            break;
          }

          while(isAsking){
            cout << "Do you want to analyze another file? (y/n) " << endl;
            string userInput;
            cin >> userInput;

            for(int i = 0; i < userInput.length(); ++i){
              userInput = tolower(userInput[i]); //make user input lowercase
            }
            if(userInput == "y" || userInput == "yes"){
              //user wants to analyze another file
              while(true){
                cout << "What is the name of the file you want to analyze? " << endl;
                cin >> fileName;

                infile.open(fileName);
                  if(infile.fail()){
                    //can't open the file
                    cout << "The given file is not accessible. Try again." << endl;
                    cout << endl;
                  }else{
                    //Gives file that can be opened
                    isAsking = false;
                    break;
                  }
              }
            }else if(userInput == "n" || userInput == "no"){
              //user doesn't want to analyze another file
              isAsking = false;
              return 0;
            }else{
              //user didn't put a valid response
              cout << "Invalid Input. Try again. " << endl;
            }
          }
        }
      }
  }
  return 0;
}
