#include "queueExecution.h"
#include "queueDictionary.h"
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

enum queue_commands {front_command = 1, empty_command, pop_command, back_command,  push_command };

std::queue <int> q;

using namespace sf;

void queue(std::ifstream & file)
{
    RenderWindow window(VideoMode::getDesktopMode(), "PBL");//, Style::Fullscreen);

    std::string input;
    bool drawCommand=false, frontCommand=false, backCommand=false;
    int result;
    int counter=0;

    while(!file.eof()) {
        std::getline(file, input);
        if (input == "draw();")
            drawCommand = true;
        else
            result = queue_check_command(input);

        switch (result) {
            case front_command: {
                frontCommand=true;
                q.front();
                break;
            }
            case empty_command: {

                q.empty();
                break;
            }
            case pop_command: {
                counter--;
                q.pop();
                break;
            }
            case back_command: {
                backCommand=true;
                q.back();
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
                q.push(value);
                counter++;
            }
        }
    }
    RectangleShape *rectangleShape = new RectangleShape[counter];
    Text *number = new Text[counter];
    Text front;
    Text back;
    int initPointX = window.getSize().x / 2;
    int initPointY = window.getSize().y / 2;

    Font font;
    font.loadFromFile("../font1.ttf");
    for (int i = 0; i <counter; ++i) {
        rectangleShape[i].setFillColor(Color::Red);
        rectangleShape[i].setPosition((initPointX+150*i-300), (initPointY-20));
        rectangleShape[i].setSize(Vector2f(100, 200));

        int c_x, c_y;
        number[i].setString(std::to_string(i+1));
        number[i].setFont(font);
        number[i].setCharacterSize(35);
        number[i].setFillColor(Color::White);
        number[i].setStyle(Text::Bold);

        c_x = rectangleShape[i].getPosition().x+rectangleShape[i].getSize().x/2;
        c_y = rectangleShape[i].getPosition().y+rectangleShape[i].getSize().y/2;
        number[i].setPosition(c_x-5,c_y-5);

    }
    if(frontCommand){
        int temp = q.front();
        front.setString("Front:  " + std::to_string(temp));
        front.setFont(font);
        front.setCharacterSize(35);
        front.setFillColor(Color::White);
        front.setStyle(Text::Bold);

        front.setPosition((initPointX-900),(initPointY+300));
    }
    if(backCommand){
        int temp = q.back();
        back.setString("Back:  " + std::to_string(temp));
        back.setFont(font);
        back.setCharacterSize(35);
        back.setFillColor(Color::White);
        back.setStyle(Text::Bold);

        back.setPosition((initPointX-900),(initPointY+400));
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
                if(frontCommand)
                    window.draw(front);
                if(backCommand)
                    window.draw(back);
            }
        }
        window.display();
    }
}