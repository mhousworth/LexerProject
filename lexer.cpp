#include <iostream>
#include <string>
#include<sstream>
#include <fstream>
#include <istream>
#include <cctype>

using namespace std;


//PROTOTYPES
string get_filename(string filename);
void lex_token(string filename);
void readFile(string filename);
void initialParse(string token);
void numberParse(string token);
void letterParse(string token);
unsigned int charLexer (char uno);

/*
STATES
1- Reading
0- Error
2- White Space
3- Comment
4- Keyword 
5- identifier



*/


//DATA
unsigned int input;
unsigned int oldState;
unsigned int currentState;

unsigned int stateTable [20] [20];




int main(){
    string hold;  
    readFile(get_filename(hold));

}



// FUNCTION DECLARATIONS
string get_filename(string name){
    string file_name;
    cout <<" Please enter a filename to lexically analyze:" << endl;
    cin >> file_name;
    file_name.append(".txt");
    return file_name;

}

void readFile(string filename){


    char ch;
    fstream fin(filename, fstream::in);
    string token;
    while (fin >> noskipws >> ch) {
        cout << ch << endl;
        input = charLexer(ch);
        currentState = stateTable [oldState][input];
        
        //if state 
        if (currentState==oldState){
            token.push_back(ch);

        }
    }      
}

/*
void lex_token(string token){
    char ch;
    ifstream fin(file_name);
    while (fin >> noskipws >> ch) {
        
        cout << ch << endl; // Or whatever
    }
}
*/


//this is the initial parse function that will take in a token and then branch off to corresponding function based on whether the first element is a char int etc
void initialParse(string token){
    if (isdigit(token.at(0))){
        numberParse(token);
    }
    else if (isalpha(token.at(0))){
        letterParse(token);
    }
}

    


void numberParse(string token){
    for (int i=0;i< (token.length());i++){
        if (isdigit(token.at(i))){
            cout << token.at(i) << "is number" << endl;
        }

    }
}

void letterParse(string token){
    for (int i=0;i< (token.length());i++){
        if (isalpha(token.at(i))){
            cout << token.at(i) << "is letter" << endl;
        }

    }
}

int tokenParse(string token){
    for (int i=0;i < (token.length());i++){
         charLexer(token.at(i));
    }
}

unsigned int charLexer (char uno){
    if (isalpha(uno)){
        return 1;
        }
    else  if (isdigit(uno)){
        return 2;
    }
    else  if (uno=='!'){
        //comment
        return 5;
    }
    // insert logic for operators
    else if (uno == '+'){

    }
    else if (ispunct(uno)){

    }
}


