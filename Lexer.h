#include <string>
#include <map>
#include <vector>

class Lexer{

public:
    Lexer();
    ~Lexer();

    void readFile(std::string filename);
    void outputList();
    std::vector<std::pair<std::string, std::string>> getList();

private:
    // Arrays for seperators and operator
    const char sep[12] = {'\'', '(', ')', '{', '}', '[', ']', ',', ':', ';', ' ', '\n'};
    const char opr[8] = {'*', '+', '-', '=', '/', '>', '<', '%'};

    //
    unsigned int input = 0;
    unsigned int oldState = 1;
    unsigned int currentState = 1;
    std::string filename = "";

    // Create State Table
    unsigned int stateTable[6][6];

    // Map of vectors of keywords
    // Key: wordlength
    std::map<int, std::vector<std::string>> keywordsMap;

    // Vector of Tokens and Lexemes
    std::vector<std::pair<std::string, std::string>> tokenTypeList;

    // Functions

    void generateKeywords();
    void generateStateTable(unsigned int arr[6][6]);

    bool isSep(char c);
    bool isOpr(char c);
    bool isKey(std::string s);

    unsigned int checkChar(char uno);

    void recordToken(std::string, unsigned int);   
};