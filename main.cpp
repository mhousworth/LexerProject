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

unsigned int charLexer (char uno);

//Initial Parsing Function
void parse(std::string input);

// Arrays for seperators and operator
const char sep[10] = {'\'', '(', ')', '{', '}', '[', ']', ',', ':', ';'};
const char opr[8] = {'*', '+', '-', '=', '/', '>', '<', '%'};

// Map of vectors of keywords
// Key: wordlength
std::map<int, std::vector<std::string>> keywordsMap;

int main(){

    // List of Pairs of Tokens and Types
    std::list<std::pair<std::string, std::string>> tokenList;

    // Create State Table
    unsigned int st[6][6];

    generateKeywords();
    generateStateTable(st);

    // Input handler
    
    //While loop for input
        //Send unparsed token to parsing function


    // Check character
        // Letter
        // Digit
        // Separators
        // Switch case for Operators
        // Comments

    return true;
}

// Check if string is a keyword
bool isKey(std::string s){

    if (s.length() <= 7) {
        for (int i = 0; i < keywordsMap[s.length()].size(); i++){
            if (s == keywordsMap[s.length()][i])
                return true;
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
void charParse(std::string input){
    std::string token = "";
    char c = '\0';

    // Stream to read string
    std::istringstream stm(input);

    // For each character in the string
    
}

// Returns True if character is in the seperator list
bool isSep(char c){
    for (int i=0; i<10; i++)
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