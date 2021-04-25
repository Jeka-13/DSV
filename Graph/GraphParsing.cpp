#include "GraphParsing.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

#include "include/maxflow_stepper_calculator.h"

#ifdef _WIN32
#define SEP "\\"
#else
#define SEP "/"
#endif

#define RADIUS_OFFSET 50
#define h 15
#define w 13
#define dist 20

#define PATH "input.txt"
#define TEXT_QUANTITY 6
#define GRAY 211,211,211

using namespace sf;

void graph(std::ifstream & file) {
    RenderWindow mainWindow(VideoMode::getDesktopMode(), "PBL");//, Style::Fullscreen);
    std::string path = "C:\\Users\\Jeka\\CLionProjects\\LFPC\\Graph\\input.txt";
    std::ifstream input(path);
    Graph input_graph = Graph::read_from_file(path);
    int N, M, D, W, source = -1, sink = -1, delay = 10000, click_1 = 0, click_2 = 0, iterations = 1, clickHolder = 1, clicktodelete = 0;

    bool menuOpen = 0, maxFlowStart = 1, way = 0;

    input >> N >> M >> D >> W;

    bool *edgeColor = new bool[M]{false};

    std::vector<std::pair<int, int>> edges;
    std::vector<int> weights;

    MaxflowStepperCalculator *maxflow_calculator;

    Font font;
    Text text[TEXT_QUANTITY];

    font.loadFromFile("../font1.ttf");
    for (int i = 0; i < TEXT_QUANTITY; i++) {
        text[i].setFont(font);
        text[i].setCharacterSize(30);
        text[i].setFillColor(Color::Black);
        text[i].setStyle(Text::Bold);
    }

    text[0].setString("Tap on a node to mark it as a source node of transport network");
    text[0].setPosition(300, 0);
    text[1].setString("Tap on a node to mark is as a sink node of transport network");
    text[1].setPosition(300, 0);
    text[2].setString("To continue - tap at any point");
    text[2].setPosition(300, 0);
    text[3].setString("");
    text[3].setPosition(15, 900);
    text[4].setString("");
    text[4].setPosition(15, 940);
    text[5].setString("");
    text[5].setPosition(15, 1000);


    Texture button_1, button_2, background;


    button_1.loadFromFile("C:\\Users\\Jeka\\CLionProjects\\LFPC\\Graph\\button 1.jpg");
    Sprite button_file;
    button_file.setTexture(button_1);

    button_2.loadFromFile("C:\\Users\\Jeka\\CLionProjects\\LFPC\\Graph\\button 2.jpg");
    Sprite button_import;
    button_import.setTexture(button_2);
    button_import.setPosition(20, 40);

    Sprite background_s;
    background.loadFromFile("C:\\Users\\Jeka\\CLionProjects\\LFPC\\Graph\\background.jpg");
    background_s.setTexture(background);

    button_file.setPosition(20, 0);

    int radius = mainWindow.getSize().y / 2 - RADIUS_OFFSET;
    int initPointX = mainWindow.getSize().x / 2;
    int initPointY = mainWindow.getSize().y / 2;

    CircleShape *vertices = new CircleShape[N];
    VertexArray *graphedges = new VertexArray[M];
    VertexArray *strelka = new VertexArray[M];

    Text *weight = new Text[M];


    Text *number = new Text[N];
    for (int i = 0; i < N; i++) {
        int c_x, c_y;

        number[i].setString(std::to_string(i));
        number[i].setFont(font);
        number[i].setCharacterSize(25);
        number[i].setFillColor(Color::Black);
        number[i].setStyle(Text::Bold);

        vertices[i].setRadius(20);
        vertices[i].setFillColor(Color::White);
        vertices[i].setOutlineThickness(6.f);
        vertices[i].setOutlineColor(Color::Black);
        vertices[i].setOrigin(vertices[i].getRadius() / 2, vertices[i].getRadius() / 2);

        c_x = radius * cos(2 * M_PI * i / N) + initPointX;
        c_y = radius * sin(2 * M_PI * i / N) + initPointY;
        vertices[i].setPosition(c_x, c_y);
        number[i].setPosition(c_x + 2, c_y - 8);
    }

    for (int i = 0; i < M; i++) {
        int x, y;
        input >> x >> y;
        edges.push_back(std::make_pair(x, y));


        graphedges[i].setPrimitiveType(LineStrip);
        graphedges[i].resize(2);

        for (int g = 0; g < 2; g++)
            graphedges[i][g].color = Color::Black;


        graphedges[i][0].position = vertices[edges[i].first].getPosition();
        graphedges[i][1].position = vertices[edges[i].second].getPosition();

        strelka[i].setPrimitiveType(TriangleStrip);
        strelka[i].resize(3);

        for (int g = 0; g < 3; g++)
            strelka[i][g].color = Color::Black;

        if (W) {
            int c;
            input >> c;

            weights.push_back(c);
            weight[i].setString(std::to_string(weights[i]));
            weight[i].setFont(font);
            weight[i].setCharacterSize(25);
            weight[i].setFillColor(Color::Black);
            weight[i].setStyle(Text::Bold);
            Vector2f edgeVector(graphedges[i][1].position.x - graphedges[i][0].position.x,
                                graphedges[i][1].position.y - graphedges[i][0].position.y);
            Vector2f edin_per((edgeVector.x == 0 ? 1 : -edgeVector.y / edgeVector.x), 1);
            Vector2f summa((graphedges[i][1].position.x + graphedges[i][0].position.x) / 2,
                           (graphedges[i][1].position.y + graphedges[i][0].position.y) / 2);
            weight[i].setPosition(edin_per.x + summa.x, edin_per.y + summa.y);
        }

        if (D) {
            float module = sqrt((graphedges[i][1].position.x - graphedges[i][0].position.x) *
                                (graphedges[i][1].position.x - graphedges[i][0].position.x)
                                + (graphedges[i][1].position.y - graphedges[i][0].position.y) *
                                  (graphedges[i][1].position.y - graphedges[i][0].position.y));
            Vector2f edgeVector(graphedges[i][1].position.x - graphedges[i][0].position.x,
                                graphedges[i][1].position.y - graphedges[i][0].position.y);
            Vector2f edin(edgeVector.x / module, edgeVector.y / module);
            strelka[i][0].position = graphedges[i][1].position - Vector2f(edin.x * dist, edin.y * dist);
            Vector2f ORA(strelka[i][0].position - Vector2f(edin.x * h, edin.y * h));
            Vector2f edin_per((edgeVector.x == 0 ? 1 : -edgeVector.y / edgeVector.x), 1);
            strelka[i][1].position = ORA + Vector2f(edin_per.x * w, (edgeVector.x == 0 ? 0 : edin_per.y * w));
            strelka[i][2].position = ORA - Vector2f(edin_per.x * w, (edgeVector.x == 0 ? 0 : edin_per.y * w));
        }
    }

    while (mainWindow.isOpen()) {
        sf::Event event;
        while (mainWindow.pollEvent(event))
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                mainWindow.close();
        delay++;

        if (button_file.getGlobalBounds().contains(
                Vector2f(Mouse::getPosition(mainWindow).x, Mouse::getPosition(mainWindow).y))) {
            button_file.setColor(Color(GRAY));
            if (Mouse::isButtonPressed(Mouse::Left) && delay > 200) {
                menuOpen = !menuOpen;
                delay = 0;
            }
        } else button_file.setColor(Color::White);

        if (button_import.getGlobalBounds().contains(
                Vector2f(Mouse::getPosition(mainWindow).x, Mouse::getPosition(mainWindow).y))) {
            button_import.setColor(Color(GRAY));
            if (Mouse::isButtonPressed(Mouse::Left) && delay > 200) {
                maxFlowStart = 1;
                delay = 0;
            }
        } else button_import.setColor(Color::White);

        for (int i = 0; i < M; i++) {
            if (strelka[i].getBounds().contains(
                    Vector2f(Mouse::getPosition(mainWindow).x, Mouse::getPosition(mainWindow).y)))
                for (int g = 0; g < 2; g++)strelka[i][g].color = Color(GRAY);
            else
                for (int g = 0; g < 2; g++)strelka[i][g].color = Color::Black;
        }

        if (sink == -1) {
            for (int i = 0; i < N; i++) {
                if (vertices[i].getGlobalBounds().contains(
                        Vector2f(Mouse::getPosition(mainWindow).x, Mouse::getPosition(mainWindow).y))) {
                    vertices[i].setFillColor(Color(GRAY));
                    if (Mouse::isButtonPressed(Mouse::Left) && delay > 200) {
                        if (source == -1)source = i;
                        else if (i != source) {
                            sink = i;
                            maxflow_calculator = new MaxflowStepperCalculator(input_graph, source, sink);
                        }
                        delay = 0;
                    }
                } else vertices[i].setFillColor(Color::White);
                if (i == source) vertices[i].setFillColor(Color(169, 169, 169));
                else if (i == sink) vertices[i].setFillColor(Color(105, 105, 105));
            }
        }
        if (sink != -1 && Mouse::isButtonPressed(Mouse::Left) && delay > 200) {
            clicktodelete++;
            if (!maxflow_calculator->finished()) {
                auto result = maxflow_calculator->do_step();
//                bottleneckSum+=result.bottleneck_value;
                text[3].setString("Found a path with bottleneck value = " + std::to_string(result.bottleneck_value));
                text[5].setString(
                        "Current maxflow value: " + std::to_string(maxflow_calculator->get_current_maximum_flow()));
                std::string buffer = "[";
                for (int i = 0; i < M; i++)
                    edgeColor[i] = 0;
                for (int i = 0; i < (int) result.augmented_path_nodes.size(); i++) {
                    for (int j = 0; j < M; j++) {
                        if (edgeColor[j] == true)continue;
                        if (result.augmented_path_nodes[i] == edges[j].first &&
                            result.augmented_path_nodes[i + 1] == edges[j].second) {
                            edgeColor[j] = 1;
                        }
                    }

                    if (i > 0)
                        buffer += ' ';
                    buffer += std::to_string(result.augmented_path_nodes[i]);
                }
                buffer += ']';
                text[4].setString(buffer);
            }
            iterations++;
            delay = 0;
        }
        mainWindow.clear(Color::White);
        if (!maxFlowStart) {
            mainWindow.draw(button_file);
            if (menuOpen == 1)mainWindow.draw(button_import);
        } else {
            for (int i = 0; i < M; i++) {
                for (int g = 0; g < 2; g++)
                    graphedges[i][g].color = edgeColor[i] ? Color::Black : Color(GRAY);
                mainWindow.draw(graphedges[i]);
                if (W)mainWindow.draw(weight[i]);
                if (D)mainWindow.draw(strelka[i]);
            }
            for (int i = 0; i < N; i++) {
                mainWindow.draw(vertices[i]);
                mainWindow.draw(number[i]);
            }

            mainWindow.draw(text[0]);
            if (source != -1) {
                text[0].setString("");
                mainWindow.draw(text[1]);
            }
            if (sink != -1) {
                text[1].setString("");
                for (int i = 0; i < M; i++) {
                    for (int g = 0; g < 3; g++) {
                        strelka[i][g].color = Color(GRAY);
                    }
                }
                mainWindow.draw(text[2]);
                mainWindow.draw(text[3]);
                mainWindow.draw(text[4]);
                mainWindow.draw(text[5]);
                if (clicktodelete == 3) {
                    text[3].setString("");
                    text[4].setString("");
                }
            }
        }
        mainWindow.display();
    }
}