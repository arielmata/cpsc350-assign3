//main file - main.cpp
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

#include "assign3.h"

int main(int argc, char** argv){
  if(argc < 2){
    cout << endl;
    cout << "No source code file was given. Please try again." << endl;
    cout << "Exiting Program." << endl;
    return 0;
  }else if(argc > 2){
    cout << endl;
    cout << "More than one file was given. Please try again." << endl;
    cout << "Exiting Program." << endl;
    return 0;
  }else if(argc == 2){
    string fileName = argv[1];
    ifstream infile;
    infile.open(fileName);
      if(infile.fail()){
        cout << endl;
        cout << "The given file is not accessible." << endl;
        cout << "Exiting program." << endl;
        infile.close();
        return 0;
      }else{
        bool stillAnalyzing = true;
        while(stillAnalyzing){
          bool isAsking = true;
          SyntaxChecker *sc = new SyntaxChecker();
          int lineNum = sc->checkSyntax(infile);
          infile.close();
          delete sc;

          if (lineNum > 0){
            isAsking = false; //there is an error in the syntax
            break;
          }

          while(isAsking){
            cout << "Do you want to analyze another file? (y,n) " << endl;
            string userInput;
            cin >> userInput;

            for(int i = 0; i < userInput.length(); ++i){
              userInput = tolower(userInput[i]);
            }
            if(userInput == "y" || userInput == "yes"){
              while(true){
                cout << "What is the name of the file you want to analyze? " << endl;
                cin >> fileName;

                infile.open(fileName);
                  if(infile.fail()){
                    cout << "The given file is not accessible. Try again." << endl;
                    cout << endl;
                  }else{
                    isAsking = false;
                    break;
                  }
              }
            }else if(userInput == "n" || userInput == "no"){
              isAsking = false;
              return 0;
            }else{
              cout << "Invalid Input. " << endl;
            }
          }
        }
      }
  }
  return 0;
}
