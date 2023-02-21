#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Solver.hpp"
#include "Renderer.hpp"

using namespace std;

int main()
{
    // Setup window
    int window_width = 800;
    int window_height = 800;


    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Verlet Integration!!");


    // setup vars for whole program
    Solver solver;
    Renderer renderer{ window };
    sf::Vector2f middle_constraint = { static_cast<float> (window_width / 2), static_cast<float> (window_height / 2) };
    float object_spawn_rate = .01;
    int object_max = 2;

    // add constraint to solver
    solver.setConstraint(middle_constraint, static_cast<float> (window_height / 2));



    vector<sf::Time> frames_in_second_vector;

    sf::Clock clock;

    sf::Time prevtime = clock.getElapsedTime();

    while (window.isOpen())
    {
        while (clock.getElapsedTime().asMilliseconds() - 00 < prevtime.asMilliseconds())
        {

        }
        prevtime = clock.getElapsedTime();
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Equal) {
                        auto constraint = solver.getConstraint();
                        solver.setConstraint({ constraint.x, constraint.y }, constraint.z - 3);
                    }
                    if (event.key.code == sf::Keyboard::Hyphen) {
                        auto constraint = solver.getConstraint();
                        solver.setConstraint({ constraint.x, constraint.y }, constraint.z + 3);
                    }

                    break;
                default:
                    break;
            }
            
        }

        while (clock.getElapsedTime().asSeconds() > solver.getObjectCount() * object_spawn_rate && solver.getObjectCount() < object_max) {
            auto& object = solver.makeObject(middle_constraint - sf::Vector2f(200.f + (rand() % 10), 100.f), 20);
            object.color = {static_cast<sf::Uint8> ( 100),static_cast<sf::Uint8> ( 100), static_cast<sf::Uint8> (( rand() % 2) * 255) };
            
        }

        frames_in_second_vector.emplace_back(clock.getElapsedTime());

        vector<sf::Time> temp_frames_vector;
        for (sf::Time time : frames_in_second_vector) { 
            if ((clock.getElapsedTime() - time).asSeconds() < 1) {
                temp_frames_vector.emplace_back(time);
            }
        }
        frames_in_second_vector = temp_frames_vector;
        
        cout << "Frames in last second: " << frames_in_second_vector.size() << endl;

        solver.update();
        window.clear(sf::Color::White);
        renderer.render(solver);
        window.display();
    }

    return 0;
}