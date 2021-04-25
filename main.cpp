#include <fstream>
#include <string>
#include <iostream>
#include "Lexer/Lexer.h"
#include "EnteryPreparations/EnteryDictionary.h"
#include "Stack/stackExecution.h"
#include "Queue/queueExecution.h"
#include "Graph/GraphParsing.h"
#include "BinaryTree/JointDSA.h"

enum dataStructures {stack_data = 1, queue_data, graph_data, binary_data };
using namespace std;
int main() {
    //Lexer part

    std::string input, path = "C:\\Users\\Jeka\\CLionProjects\\LFPC\\InputSamples\\binaryTree.txt";
    int result;
    std::ifstream file1;
    file1.open(path);
    std::cout<<"["<<std::endl;
    while (!file1.eof()) {
        getline(file1,input);
        result = Lexer(input);
    }
    std::cout<<"]"<<std::endl;
    file1.close();

    ifstream file2;
    file2.open(path);
    getline(file2,input);
    result = dataStrucutreCheck(input);
    switch (result){
        case stack_data: {
           stack(file2);
            break;
        }
        case queue_data:{
            queue(file2);
            break;
        }
        case graph_data:{
            graph(file2);
            break;
        }
        case binary_data:{
            BinaryTreeStart(file2);
            break;
        }
    }

    file2.close();
    return 0;
}