#include "stackDictionary.h"
#include <iostream>
#include <string>

using namespace std;

bool stack_check_semicolon(string input){
    int last_elem = input.size()-1;
    if(input[last_elem]!=';'){
        cout<<"Semicolon was missed"<<endl;
        return false;
    }
    return true;
}

bool stack_check_brackets(string input){
    int open_brack=0,closed_brack=0;
    for (int i = 0; i < input.size(); ++i) {
        if(input[i]=='(')
            open_brack++;
        if(input[i]==')')
            closed_brack++;
    }
    if(open_brack==0)  {
        cout<<"Open bracket is missing"<<endl;
        return false;
    }else if(closed_brack==0){
        cout<<"Closed bracket is missing"<<endl;
        return false;
    }
    else if(open_brack>1) {
        cout<<"To many open brackets"<<endl;
        return false;
    } else if (closed_brack>1){
        cout<<"To many closed brackets"<<endl;
        return false;
    }
    return true;
}

bool stack_check_if_isVariable(string input) {
    bool is_variable = false;
    string temp="";
    string non_variables[] = {"pop", "top", "empty"};
    string variables[] = {"push"};

    for (int i = 0; i < input.size();) {
        while (input[i]!='('){
            temp.push_back(input[i]);
            i++;
        }
        break;
    }
    for (int i = 0; i < 1; ++i) {
        if (temp == variables[i])
            is_variable = true;
    }
    if (is_variable) {
        for (int i = 0; i < input.size(); ++i) {
            if (input[i] == '(')
                if (input[i + 1] == ')') {
                    cout << "You need a value" << endl;
                    return false;
                }
            continue;
        }
    }else{
        for (int i = 0; i < input.size(); ++i) {
            if(input[i]=='(')
                if(input[i+1]!=')'){
                    cout<<"Value is unnecessary"<<endl;
                    return false;
                }
            continue;
        }
    }
    return true;
}

bool stack_check_correctWriting(string input, string command){
    for (int i = 0; i < input.size();) {
        while (input[i]!='('){
            if(input[i]!=command[i]){
                return false;
            }
            i++;
        }
        break;
    }
    return true;
}

int stack_check_command(string input){
    if(!stack_check_semicolon(input))
        return false;
    if(!stack_check_brackets(input))
        return false;
    if(!stack_check_if_isVariable(input))
        return false;
    if(input[0]=='p') {
        if (input[1] == '0') {
            if (!stack_check_correctWriting(input, "pop"))
                return false;
            return 3;
        }
        if(input[1]=='u'){
            if(!stack_check_correctWriting(input,"push"))
                return false;

            return 4;
        }
    }
    if(input[0]=='e'){
        if(!stack_check_correctWriting(input,"empty")){
            return false;
        } else
            return 2;
    }
    if(input[0]=='t'){
        if(!stack_check_correctWriting(input,"top")){
            return false;
        } else
            return 1;
    }

}