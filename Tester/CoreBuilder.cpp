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
	//sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
	//xe::Timer time;

	//TestClass tc;
	//tc.Setup();
	//float a = 0.1f;
	//float b = 0.2f;
	//float result = a + b;

	//while (window.isOpen())
	//{
	//	xe::InputSystem::Update(&window, time.DeltaTime());


	//}
	xe::SaveFile save("testfile.json", xe::FileFormat::Json);
	//save.SetVector2("position", xe::Vector2(3.14159f, 420.69f));
	//save.SetInt("lives", 5);
	//save.SetFloat("health", 98.6f);
	//save.SetBool("isCool", true);
	//save.SetString("username", "Xepherin");
	//save.Save();
	std::cout << save.GetInt("lives") << std::endl;
	std::cout << save.GetFloat("health") << std::endl;
	std::cout << save.GetString("username") << std::endl;
	std::cout << save.GetVector2("position") << std::endl;
	std::cout << (save.GetBool("isCool") ? "TRUE" : "FALSE") << std::endl;

	std::cout << _APPDATA_;

	return 0;
}