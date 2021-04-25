#include "Lexer.h"
#include <iostream>
#include <string>

#define DATA_STRUCTURE_SIZE 4
#define ALGORITHM_SIZE 3
#define COMMAND_WITH_VALUE_SIZE 4
#define COMMAND_WITH_NOT_VALUE_SIZE 5
#define KEY_WORD_SIZE 2

using namespace std;

string INITIAL_COMMAND = "create";
string FINAL_COMMAND = "draw";
string DATA_STRUCTURE[] = {"binaryTree","graph","stack","queue"};
string ALGORITHM[] = {"inorder","preorder","postorder"};
string COMMAND_WITH_VALUE[] = {"add", "delete",
                               "find", "push"};
string COMMAND_WITH_NOT_VALUE[]={"pop","front","back","empty","top"};
string KEY_WORD[] = {"node", "tree"};

int open_brack,closed_brack;
bool inital_command=false;

struct Token{
    string initial_command="";
    string final_command="";
    string data_structure="";
    string algorithm="";
    struct command{
        string type="";
        string value="";
    }c;
    string key_word="";
    struct value{
        string type="";
        string value="";
    }v;
    struct separator{
        string name="";
        string value="";
    }s;
};

Token token;
Token Output(Token token){
    if(!token.initial_command.empty()) {
        cout << "   INITIAL COMMAND_WITH_VALUE:   \"" << token.initial_command << "\"" << endl;
        token.initial_command = "";
    }
    if(!token.final_command.empty()) {
        cout << "   FINAL COMMAND_WITH_VALUE:   \"" << token.final_command << "\"" << endl;
        token.final_command = "";
    }
    if(!token.data_structure.empty()) {
        cout << "   DATA STRUCTURE:   \"" << token.data_structure << "\"" << endl;
        token.data_structure = "";
    }
    if(!token.c.type.empty()) {
        cout<<"   COMMAND:  {"<<endl;
        cout<<"       COMMAND TYPE:   \""<<token.c.type<<"\""<<endl;
        if(token.c.type=="COMMAND_WITH_NOT_VALUE")
            cout<<"       VALUE IS NOT NECESSARY!"<<endl;
        else
            cout<<"       VALUE:   \""<<token.c.value<<"\""<<endl;
        cout<<"               }"<<endl;
        token.c.value="";
        token.c.type="";
    }
    if(!token.key_word.empty()){
        cout<<"   KEY WORD:   \""<<token.key_word<<"\""<<endl;
        token.key_word="";
    }
    if(!token.algorithm.empty()) {
        cout << "   ALGORITHM:   \"" << token.algorithm << "\"" << endl;
        token.algorithm="";
    }
    if(!token.s.value.empty()){
        cout<<"   SEPARATOR:  {"<<endl;
        cout<<"       SEPARATOR NAME:   \""<<token.s.name<<"\""<<endl;
        cout<<"       SEPARATOR VALUE:   \""<<token.s.value<<"\""<<endl;
        cout<<"               }"<<endl;

        token.s.value="";
        token.s.name="";
    }
    if(!token.v.value.empty()){
        cout<<"    VALUE:  {"<<endl;
        cout<<"        VALUE TYPE:   \""<<token.v.type<<"\""<<endl;
        cout<<"        VALUE:   \""<<token.v.value<<"\""<<endl;
        cout<<"               }"<<endl;

        token.v.value="";
        token.v.type="";
    }
    return token;
}
bool Tokenizer(string*& temp, bool open_bracket){
    if(open_bracket){
        for (int i = 0; i < temp->size(); ++i) {
            if(temp[i]==".")
                token.v.type="DOUBLE";
        }
        token.v.type="INT";
        token.v.value=*temp;
        token = Output(token);
        return true;
    }

    if(*temp==INITIAL_COMMAND) {
        token.initial_command = "create";
        token = Output(token);
        inital_command = true;
        return true;
    }
    if(*temp==FINAL_COMMAND) {

        token.final_command = "draw";
        token = Output(token);

        return true;
    }

    for (int i = 0; i < DATA_STRUCTURE_SIZE; ++i) {
        if(*temp==DATA_STRUCTURE[i]) {
            token.data_structure = DATA_STRUCTURE[i];
            token = Output(token);
            return true;
        }
    }

    for (int i = 0; i < ALGORITHM_SIZE; ++i) {
        if(*temp==ALGORITHM[i]) {
            token.algorithm = ALGORITHM[i];
            token = Output(token);
            return true;
        }
    }
    for (int i = 0; i < COMMAND_WITH_VALUE_SIZE; ++i) {
        if(*temp == COMMAND_WITH_VALUE[i]) {
            token.c.type = "COMMAND_WITH_VALUE";
            token.c.value = COMMAND_WITH_VALUE[i];
            token = Output(token);
            return true;
        }
    }

    for (int i = 0; i < COMMAND_WITH_NOT_VALUE_SIZE; ++i) {
        if(*temp == COMMAND_WITH_NOT_VALUE[i]) {
            token.c.type = "COMMAND_WITH_NOT_VALUE";
            token.c.value = COMMAND_WITH_NOT_VALUE[i];
            token = Output(token);
            return true;
        }
    }

    for (int i = 0; i < KEY_WORD_SIZE; ++i) {
        if(*temp==KEY_WORD[i]){
            token.key_word = KEY_WORD[i];
            token = Output(token);
            return true;
        }
    }
    return false;
}

void Tokenizer_info(string*& temp, bool open_bracket){
    if(!Tokenizer(*&temp, open_bracket))
        token.c.type = "UNKNOWN COMMAND";
    token = Output(token);
    *temp="";
}

int Lexer(string input) {
    string temp;
    string* ptemp = &temp;
    bool open_bracket = false;
    cout<<"{"<<endl;
    for (int i = 0; i < input.size(); ++i) {
        switch (input[i]) {
            case (';'): {
                if (!temp.empty())
                    Tokenizer_info(ptemp, open_bracket);
                token.s.name = "SEPARATOR";
                token.s.value = ";";
                token = Output(token);
                break;
            }
            case ('_'): {
                if (!temp.empty())
                    Tokenizer_info(ptemp, open_bracket);
                token.s.name = "UNDERLINE";
                token.s.value = "_";
                token = Output(token);
                break;
            }
            case ('('): {
                if (!temp.empty())
                    Tokenizer_info(ptemp, open_bracket);
                token.s.name = "OPENED BRACKET";
                token.s.value="(";
                open_bracket = true;
                token = Output(token);
                open_brack++;
                break;
            }
            case (')'): {
                if (!temp.empty())
                    Tokenizer_info(ptemp, open_bracket);
                open_bracket = false;
                token.s.name = "CLOSED BRACKET";
                token.s.value = ")";
                token = Output(token);
                closed_brack++;
                break;
            }
            case (','):{
                if (!temp.empty())
                    Tokenizer_info(ptemp, open_bracket);
                token.s.name = "COMA";
                token.s.value = ",";
                token = Output(token);
                break;
            }
            default: {
                temp.push_back(input[i]);
                break;
            }
        }
    }
    cout<<" },"<<endl;
    cout<<endl;
}
