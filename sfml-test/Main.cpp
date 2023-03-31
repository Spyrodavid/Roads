#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

# define M_PIl          3.141592653589793238462643383279502884L /* pi */

using namespace std;

float rand_float01() {
    return (rand() * 1.f) / RAND_MAX;
}

int main()
{
    // Setup window
    int window_width = 800;
    int window_height = 800;

    int mouseX = 0;
    int mouseY = 0;


    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Verlet Integration!!");


    sf::Vector2f position(window_width / 2, window_height / 2);
    float radius = 5.f;
    srand(time(0));


    window.clear(sf::Color::Black);

    int iterations = 1000;
    int iterations_max = iterations;
    

    while (iterations > 0) {

        float percent = (position.y / (window_height + radius));
        float percent_pow = pow(percent, 4);
        int color_percent = 50 + percent_pow * 205;


       /* sf::CircleShape constraint_shape(radius);
        constraint_shape.setOrigin(radius, radius);
        constraint_shape.setFillColor(sf::Color(255 * (1.f * iterations / iterations_max), color_percent * .93, color_percent));
        constraint_shape.setPosition(position.x, position.y);
        constraint_shape.setPointCount(50);
        window.draw(constraint_shape);*/


        sf::Vertex line[2] =
        {
            sf::Vertex(sf::Vector2f(position.x, position.y))
        };

        

        // Move
        float angle = (M_PIl / 2) + (((rand() % 3) / 3.f) * M_PIl) * 2;
        //cout << angle << endl;
        position.y += sin(angle) * 20;
        position.x += cos(angle) * 20;

        line[1] = sf::Vertex(sf::Vector2f(position.x, position.y));

        window.draw(line, 2, sf::Lines);

        iterations--;
    }

    window.display();



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

                case sf::Event::MouseMoved:
                   
                    mouseX = event.mouseMove.x;
                    mouseY = event.mouseMove.y;
                    break;

                default:
                    break;
            }
            
        }

  

        frames_in_second_vector.emplace_back(clock.getElapsedTime());

        vector<sf::Time> temp_frames_vector;
        for (sf::Time time : frames_in_second_vector) { 
            if ((clock.getElapsedTime() - time).asSeconds() < 1) {
                temp_frames_vector.emplace_back(time);
            }
        }
        frames_in_second_vector = temp_frames_vector;
        
        std::cout << "Frames in last second: " << frames_in_second_vector.size() << endl;


        

        

        //window.display();
    }

    return 0;
}

