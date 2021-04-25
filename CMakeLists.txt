cmake_minimum_required(VERSION 3.15)
project(LFPC)

set(CMAKE_CXX_STANDARD 20)

add_executable(LFPC main.cpp Stack/stackDictionary.cpp Stack/stackDictionary.h Stack/stackExecution.cpp Stack/stackExecution.h Lexer/Lexer.cpp Lexer/Lexer.h Queue/queueDictionary.cpp Queue/queueDictionary.h Queue/queueExecution.cpp Queue/queueExecution.h EnteryPreparations/EnteryDictionary.cpp EnteryPreparations/EnteryDictionary.h Graph/GraphParsing.cpp Graph/GraphParsing.h Graph/edge.cpp Graph/graph.cpp Graph/maxflow_stepper_calculator.cpp Graph/node.cpp Graph/residual_edge.cpp Graph/residual_graph.cpp Graph/residual_node.cpp Graph/include/graph.h Graph/include/maxflow_stepper_calculator.h Graph/include/residual_graph.h Graph/include/edge.h Graph/include/residual_edge.h Graph/include/node.h Graph/include/residual_node.h BinaryTree/BinaryTree.cpp BinaryTree/BinaryTree.h BinaryTree/readFile.cpp BinaryTree/readFile.h BinaryTree/stdafx.cpp BinaryTree/stdafx.h BinaryTree/targetver.h BinaryTree/JointDSA.cpp BinaryTree/JointDSA.h)

include_directories(headers  C:/SFML/include)

set(SFML_ROOT C:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(LFPC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
