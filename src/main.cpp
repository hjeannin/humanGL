#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "Initiator.hpp"
#include "Mat4.hpp"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 4;
	sf::Window window(sf::VideoMode(1920, 1080), "HumanGL", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	std::cout << "OpenGL version = " << settings.majorVersion << "." << settings.minorVersion << std::endl;

	Initiator	init;

	std::cout << init << std::endl;
	
	Mat4<GLfloat>	random_mat4;

	std::cout << random_mat4 << std::endl;

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
				glViewport(0, 0, event.size.width, event.size.height);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.display();
    }

    return 0;
}
