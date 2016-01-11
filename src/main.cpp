#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "Initiator.hpp"
#include "Mat4.hpp"

int main()
{
	Initiator	init;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 4;

	sf::Window window(sf::VideoMode(init.res_x, init.res_y), "HumanGL", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	init.CalculateEveryMatrix();
	
	std::cout << init.proj_matrix << std::endl;
	std::cout << init.view_matrix << std::endl;
	std::cout << init.trans_matrix << std::endl;
	std::cout << init.scale_matrix << std::endl;

	bool looping = true;
    while (looping)
    {
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                looping = false;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				looping = false;
			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
				init.res_x = event.size.width;
				init.res_y = event.size.height;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.display();
    }

    return 0;
}
