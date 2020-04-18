/*
    Sample of using the Lexer class
    test.txt provided, type "test" in prompt
    Will create output.txt

    Uncomment main to run sample code
*/

#include <list>
#include <vector>
#include <map>
#include "stdlib.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Lexer.h"

std::string get_filename();

// int main(){

//     // Vector of Tokens and Lexemes
//     std::vector<std::pair<std::string, std::string>> lexemeToken;

//     Lexer Lex;

//     Lex.readFile(get_filename());
//     Lex.outputList();

//     lexemeToken = Lex.getList();

//     return true;
// }

std::string get_filename(){
    std::string file_name;
    std::cout << "Please enter a filename to analyze:" << std::endl;
    std::cin >> file_name;
    file_name.append(".txt");
    return file_name;
}