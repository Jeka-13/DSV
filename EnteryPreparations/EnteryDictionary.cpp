#include "EnteryDictionary.h"
#include <string>
#include <iostream>

using namespace std;

bool semicolon_check(string input){
    int last_elem = input.size()-1;
    if(input[last_elem]!=';'){
        cout<<"Semicolon is missing"<<endl;
        return false;
    }
    return true;
}

bool brackets_check(string input){
    int open_brack=0, closed_brack=0;
    for (int i = 0; i < input.size(); ++i) {
        if(input[i]=='(') {
            open_brack++;
            if(input[i+1]!=')') {
                cout<<"Unnecessary value"<<endl;
                return false;
            }
        }
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

bool lexical_check(string input){
    string general_command = "create", temp="";
    for (int i = 0; i < input.length(); ++i) {
        while(input[i]!='_'){
            temp.push_back(input[i]);
            i++;
        }
        break;
    }
    if(temp!=general_command){
        cout<<"Wrong entry command"<<endl;
        return false;
    }
    return true;
}

bool underline_check(char underline){
    if(underline != '_'){
        cout<<"Underline missed"<<endl;
        return false;
    }
    return true;
}


bool check_if_dataStructure(string input, string data){
    for (int i = 7, j=0; i < input.size(); ++i) {
        while (input[i]!='('){
            if(input[i]!=data[j]) {
                cout<<"Wrong data structure"<<endl;
                return false;
            }
            i++; j++;
        }
        break;
    }
    return true;
}

int dataStrucutreCheck(string input){
    if(!semicolon_check(input))
        return false;
    if(!brackets_check(input))
        return false;
    if (!lexical_check(input))
        return false;
    else if (!underline_check(input[6]))
        return false;
    else if(input[7]=='b'){
        if(!check_if_dataStructure(input,"binaryTree"))
            return false;
        return 4;
    } else if(input[7]=='g'){
        if(!check_if_dataStructure(input,"graph"))
            return false;
        return 3;
    } else if (input[7]=='q'){
        if(!check_if_dataStructure(input,"queue"))
            return false;
        return 2;
    } else if(input[7]=='s'){
        if(!check_if_dataStructure(input,"stack"))
            return false;
        return 1;
    }
}