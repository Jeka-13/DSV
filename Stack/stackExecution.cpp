#include "stackExecution.h"
#include "stackDictionary.h"
#include <stack>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>


using namespace sf;

enum stack_commands {top_command=1, empty_command, pop_command, push_command};

std::stack<int> s;

void stack(std::ifstream & file){
    RenderWindow window(VideoMode::getDesktopMode(), "PBL"); //Style::Fullscreen);

    std::string input;
    bool drawCommand=false,topCommand=false;
    int counter=0;
    int result;

    while (!file.eof()) {
        std::getline(file, input);
        if (input == "draw();")
            drawCommand = true;
        else
            result = stack_check_command(input);

        switch (result) {
            case top_command: {
                s.top();
                topCommand=true;
                break;
            }
            case empty_command: {
                s.empty();
                break;
            }
            case pop_command: {
                s.pop();
                counter--;
            }
            case push_command: {
                char temp[256] = " ";
                for (int i = 0, j = 0; i < input.length(); ++i) {
                    if (input[i] == '(') {
                        ++i;
                        while (input[i] != ')') {
                            temp[j] = input[i];
                            ++i;
                            ++j;
                        }
                    }
                }
                int value = atoi(temp);
                s.push(value);
                counter++;
                break;
            }
        }
    }

    RectangleShape *rectangleShape = new RectangleShape[counter];
    Text *number = new Text[counter];
    Text top;
    int initPointX = window.getSize().x / 2;
    int initPointY = window.getSize().y / 2;

    Font font;
    font.loadFromFile("../font1.ttf");
    for (int i = 0; i <counter; ++i) {
        rectangleShape[i].setFillColor(Color::Red);
        rectangleShape[i].setPosition((initPointX-20), (initPointY+150*i/1.35-500));
        rectangleShape[i].setSize(Vector2f(200, 100));

        int c_x, c_y;
        number[i].setString(std::to_string(i+1));
        number[i].setFont(font);
        number[i].setCharacterSize(35);
        number[i].setFillColor(Color::White);
        number[i].setStyle(Text::Bold);

        c_x = rectangleShape[i].getPosition().x+rectangleShape[i].getSize().x/2;
        c_y = rectangleShape[i].getPosition().y+rectangleShape[i].getSize().y/2;
        number[i].setPosition(c_x-5,c_y-7);

    }
    if(topCommand){
        int temp = s.top();
        top.setString("Top:  " + std::to_string(temp));
        top.setFont(font);
        top.setCharacterSize(35);
        top.setFillColor(Color::White);
        top.setStyle(Text::Bold);

        top.setPosition((initPointX-900),(initPointY+300));
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        if(drawCommand) {
            for (int i = 0; i < counter; ++i) {
                window.draw(rectangleShape[i]);
                window.draw(number[i]);
                window.draw(top);
            }
        }
        window.display();
    }
}