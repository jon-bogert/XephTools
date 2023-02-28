#include <iostream>
#include <fstream>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <XephTools.h>

class TestClass
{
public:
	sf::CircleShape visual;
	sf::Color colors[2]{ sf::Color::Red, sf::Color::Blue };
	int currColor = 0;
	xe::Vector2 pos = { 10, 10 };

	void ChangeColor()
	{
		currColor = (currColor + 1) % 2;
		visual.setFillColor(colors[currColor]);
	}

	void Start()
	{
		xe::InputSystem::Subscribe(xe::Button::A, xe::Event::Pressed, XE_CALLBACK(TestClass::ChangeColor));

		visual.setRadius(10);
		visual.setOrigin({ 10, 10 });
		visual.setFillColor(colors[currColor]);
	}

	void Update(float deltaTime)
	{
		pos += xe::InputSystem::GetAxis(xe::Axis::LS) * 10.f * deltaTime;
	}

	void Draw(sf::RenderWindow* window)
	{
		visual.setPosition(pos);
		window->draw(visual);
	}

	void Destroy()
	{
		xe::InputSystem::Unsubscribe(xe::Key::Space, xe::Event::Pressed, this);
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	xe::Timer time;

	TestClass class1;

	class1.Start();

	while (window.isOpen())
	{
		xe::InputSystem::Update(&window, time.GetElapsed(), true);

		class1.Update(time.GetElapsed());
		time.Reset();
		if (xe::InputSystem::KeyHold(xe::Key::Backspace))
		{
			class1.Destroy();
		}

		window.clear(sf::Color::Black);
		class1.Draw(&window);
		window.display();

	} 

	return 0;
}