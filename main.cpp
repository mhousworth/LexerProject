#include <list>
#include <vector>
#include <map>
#include "stdlib.h"
#include <string>
#include "fstream"
#include <iostream>
#include <sstream>


void generateKeywords();
void charParse(std::string input);

//Initial Parsing Function
void parse(std::string input){

}

// Arrays for seperators and operator
const char sep[11] = {'\'', '(', ')', '{', '}', '[', ']', ',', '.', ':', ';'};
const char opr[8] = {'*', '+', '-', '=', '/', '>', '<', '%'};

// Map of vectors of keywords
// Key: wordlength
std::map<int, std::vector<std::string>> keywordsMap;

int main(){

    // List of Pairs of Tokens and Types
    std::list<std::pair<std::string, std::string>> tokenList;

    generateKeywords();

    // Define State Table
    int st[20][5];


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
bool checkKeyword(std::string input){

    if (input.length() <= 7) {
        for (int i = 0; i < keywordsMap[input.length()].size(); i++){

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

//By-Character Parsing Function
void charParse(std::string input){
    std::string token = "";
    char c = NULL;

    // Stream to read string
    std::istringstream stm(input);

    // For each character in the string
    
}