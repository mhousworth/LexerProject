#include "Lexer.h"
#include "stdlib.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Lexer::Lexer(){

    generateKeywords();
    generateStateTable(stateTable);
}

Lexer::~Lexer(){}

// Parses Tokens from a text file
void Lexer::readFile(std::string f_n){

    char ch;
    filename = f_n;
    std::fstream fin(filename, std::fstream::in);
    std::string token;

    while (fin >> std::noskipws >> ch) {
        // std::cout << ch << std::endl;

        // Get character
        input = checkChar(ch);
        // Saves previous state
        oldState = currentState;
        // Get next state based on the state table
        currentState = stateTable[oldState][input];
        
        // ----------------------
        // State transition logic

        // If in a comment block
        if((currentState == 5) && (oldState == 5)){
            // Make no change, do not save characters
            continue;
        }
        // If starting a comment block
        else if((currentState == 5) && (oldState != 5)){
            // If we have a non-empty string, evaluate the token type
            if (token.length() != 0){
                recordToken(token, oldState);
                // Clear token
                token = "";
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
        // States 2, 3, and 4 are building to the token
        else if (currentState==2 || currentState==3 || currentState==4){
            token.push_back(ch);
        }
        // Returning to initial state
        else if (currentState==1){
            // Handle float error
            if(input == 4 && oldState == 0){
                    token.push_back(ch);
                    continue;
            }
            // If token is not empty
            if(token.length() != 0){
                recordToken(token, oldState);
                // Clear token
                token = "";
            }

            // Match input to store or throwout character that cause state change
            // If seperator
            if(input == 2 || input == 4){
                // If whitespace
                if(ch == ' ' || ch == '\n')
                    continue;
                
                std::string charToken = "";
                charToken.push_back(ch);
                tokenTypeList.push_back(std::pair<std::string, std::string>(charToken, "seperator"));
            }
            // If operator
            else if(input == 3){
                std::string charToken = "";
                charToken.push_back(ch);
                tokenTypeList.push_back(std::pair<std::string, std::string>(charToken, "operator"));
            }
        }
        else if(currentState == 0){
            token.push_back(ch);          
        }
      
    }
    //Get last token
    if(token.length() != 0){
        recordToken(token, oldState);
        // Clear token
        token = "";
    }
}

void Lexer::outputList(){
    std::ofstream fout;
    fout.open("output.txt");

    //Print out results, can be changed to a file output
    char output[256];
    sprintf(output, "%-16s %16s \n", "Token", "Lexeme");
    fout << output;
    sprintf(output, "%s \n", "----------------------------------");
    fout << output;

    for (int i=0; i != tokenTypeList.size(); i++){
        const char* s1 = tokenTypeList[i].first.c_str();
        const char* s2 = tokenTypeList[i].second.c_str();
        sprintf(output, "%-16s %16s \n", s2, s1);
        fout << output;
    }
}

std::vector<std::pair<std::string, std::string>> Lexer::getList(){
    return tokenTypeList;
}

// Generates Keywords Map
void Lexer::generateKeywords(){

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
void Lexer::generateStateTable(unsigned int arr[6][6]){
    // Set 0 state, Error
    arr[0][0] = 0; //Alpha
    arr[0][1] = 0; //Digit
    arr[0][2] = 1; //Seper
    arr[0][3] = 1; //Oper
    arr[0][4] = 1; //Period
    arr[0][5] = 5; //Bang/Comment

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

// Returns True if character is in the seperator list
bool Lexer::isSep(char c){
    for (int i=0; i<12; i++)
        if (c == sep[i])
            return true;

    return false;
}

// Returns True if the character is in the operator list
bool Lexer::isOpr(char c){
    for (int i=0; i<8; i++)
        if (c == opr[i])
            return true;

    return false;
}

// Check if string is a keyword
bool Lexer::isKey(std::string s){

    if (s.length() <= 8) {
        for (int i = 0; i < keywordsMap[s.length()].size(); i++){
            if (s == keywordsMap[s.length()][i]){
                return true;
            }
        }
    }
    return false;
}

void Lexer::recordToken(std::string token, unsigned int state){

    std::pair<std::string, std::string> tokenPair;
    tokenPair.first = token;

    // Check old state
    // If state 2, check if its a keyword
    if (oldState == 2){
        // If so, record as such
        if(isKey(token)){
            tokenPair.second = "keyword";
        }
        // Else, record as identifier
        else{
            tokenPair.second = "identifier";
        }
    }
    // If state 3, record as an integer
    else if(oldState == 3){
        tokenPair.second = "integer";
    }
    // If state 4, record as a float/double
    else if(oldState == 4){
        tokenPair.second = "float";
    }
    else if (oldState == 0){
        tokenPair.second = "Error Input";
    }

    //Push back the tokenPair
    tokenTypeList.push_back(tokenPair);
}

// Returns input for state table according to character type
unsigned int Lexer::checkChar (char uno){
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
    return 0;
}