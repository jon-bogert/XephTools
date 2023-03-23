#include <iostream>
#include <fstream>
#include <filesystem>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "box2d/box2d.h"

#include <XephTools.h>

#include "TestClass.h"

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
	xe::Timer time;

	TestClass tc;
	tc.Setup();
	float a = 0.1f;
	float b = 0.2f;
	float result = a + b;

	while (window.isOpen())
	{
		xe::InputSystem::Update(&window, time.DeltaTime());


	}
	return 0;
}