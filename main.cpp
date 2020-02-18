#include <list>
#include <vector>
#include <map>
#include "stdlib.h"
#include <string>
#include "fstream"
#include <iostream>
#include <sstream>


void generateKeywords();
void generateStateTable(unsigned int arr[6][6]);

bool isSep(char c);
bool isOpr(char c);
bool isKey(std::string s);

unsigned int checkChar (char uno);

std::string get_filename(std::string filename);
void readFile(std::string filename);


// Arrays for seperators and operator
const char sep[11] = {'\'', '(', ')', '{', '}', '[', ']', ',', ':', ';', ' '};
const char opr[8] = {'*', '+', '-', '=', '/', '>', '<', '%'};

//
unsigned int input;
unsigned int oldState;
unsigned int currentState;

// Create State Table
unsigned int stateTable[6][6];

// Map of vectors of keywords
// Key: wordlength
std::map<int, std::vector<std::string>> keywordsMap;

// Vector of Tokens
std::vector<std::pair<std::string, std::string>> tokenTypeVector;

int main(){

    // List of Pairs of Tokens and Types
    std::list<std::pair<std::string, std::string>> tokenList;

    generateKeywords();
    generateStateTable(stateTable);

    std::string hold;  
    readFile(get_filename(hold));


    return true;
}

std::string get_filename(std::string name){
    std::string file_name;
    std::cout <<" Please enter a filename to lexically analyze:" << std::endl;
    std::cin >> file_name;
    file_name.append(".txt");
    return file_name;
}

void readFile(std::string filename){

    char ch;
    std::fstream fin(filename, std::fstream::in);
    std::string token;

    while (fin >> std::noskipws >> ch) {
        std::cout << ch << std::endl;
        input = checkChar(ch);
        currentState = stateTable[oldState][input];
        
        // If in a comment block
        if((currentState == 5) && (oldState == 5)){
            // Make no change, do not save characters
            continue;
        }
        // If starting a comment block
        else if((currentState == 5) && (oldState != 5)){
            // If we have a non-empty string, evaluate the token type
            if (token.length != 0){
                // Check old state
                // If state 2, check if its a keyword
                    // If so, record as such
                    // Else, record as identifier

                // If state 3, record as an integer

                // If state 4, record as a float/double
            }
            else{
                // Nothing to record
                continue;
            }
        }
        // End of comment block
        else if((currentState == 1) && (oldState == 5)){
            // Nothing to record
            continue;
        }

        //if state 
        if (currentState==oldState){
            token.push_back(ch);
        }
        else if (currentState==2 || currentState==3||currentState==4){
            token.push_back(ch);
        }
        // Returning to initial state
        else if (currentState==1){
            // Check old state
            // If state 2, check if its a keyword
                // If so, record as such
                // Else, record as identifier

            // If state 3, record as an integer

            // If state 4, record as a float/double

            // If from state 1, check character "checkChar()"
                // record as seperator or operator
        }
    }      
}

// Check if string is a keyword
bool isKey(std::string s){

    if (s.length() <= 7) {
        for (int i = 0; i < keywordsMap[s.length()].size(); i++){
            if (s == keywordsMap[s.length()][i]){
                return true;
            }
        }
    }
}

// Generates Keywords Map
void generateKeywords(){

    std::ifstream ifs;
    ifs.open("keywords.txt", std::ifstream::in);

    for(int i = 1; !ifs.eof(); i++){

        // Buffer for line of input
        std::string line;
        std::getline(ifs, line);

        // Stream to read string
        std::istringstream stm(line);

        // Buffer for keyword
        std::string word;

        // Push each keyword into vector
        while (std::getline(stm, word, ' ')){
            keywordsMap[i].push_back(word);
        }
    }
}

//Creates State Table
void generateStateTable(unsigned int arr[6][6]){
    // Set 0 state
    for (int i=0; i<6; i++)
        arr[0][i] = 0;

    // State 1, Initial
    arr[1][0] = 2; //Alpha
    arr[1][1] = 3; //Digit
    arr[1][2] = 1; //Seper
    arr[1][3] = 1; //Oper
    arr[1][4] = 4; //Period
    arr[1][5] = 5; //Bang/Comment

    // State 2, Identifier/Keyword
    arr[2][0] = 2; //Alpha
    arr[2][1] = 2; //Digit
    arr[2][2] = 1; //Seper
    arr[2][3] = 1; //Oper
    arr[2][4] = 1; //Period
    arr[2][5] = 5; //Bang/Comment

    // State 3, Integer
    arr[3][0] = 0; //Alpha
    arr[3][1] = 3; //Digit
    arr[3][2] = 1; //Seper
    arr[3][3] = 1; //Oper
    arr[3][4] = 4; //Period
    arr[3][5] = 5; //Bang/Comment

    // State 4, Float/Double
    arr[4][0] = 0; //Alpha
    arr[4][1] = 4; //Digit
    arr[4][2] = 1; //Seper
    arr[4][3] = 1; //Oper
    arr[4][4] = 0; //Period
    arr[4][5] = 5; //Bang/Comment

    // State 5, Comment
    arr[5][0] = 5; //Alpha
    arr[5][1] = 5; //Digit
    arr[5][2] = 5; //Seper
    arr[5][3] = 5; //Oper
    arr[5][4] = 5; //Period
    arr[5][5] = 1; //Bang/Comment

}


//By-Character Parsing Function
// void charParse(std::string input){
//     std::string token = "";
//     char c = '\0';

//     // Stream to read string
//     std::istringstream stm(input);

//     // For each character in the string
    
// }

// Returns True if character is in the seperator list
bool isSep(char c){
    for (int i=0; i<11; i++)
        if (c == sep[i])
            return true;

    return false;
}

// Returns True if the character is in the operator list
bool isOpr(char c){
    for (int i=0; i<8; i++)
        if (c == opr[i])
            return true;

    return false;
}

// Returns input for state table according to character type
unsigned int checkChar (char uno){
    if (isalpha(uno)){
        return 0;
    }
    else  if (isdigit(uno)){
        return 1;
    }
    else  if (isSep(uno)){
        return 2;
    }
    else if (isOpr(uno)){
        return 3;
    }
    else if (uno == '.'){
        return 4;
    }
    else if (uno == '!'){
        return 5;
    }
}