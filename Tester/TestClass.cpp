#include "TestClass.h"
#include "XephTools/InputSystem.h"

void TestClass::Setup()
{
	xe::InputSystem::Subscribe(xe::Key::Space, xe::Event::Pressed, XE_CALLBACK(TestClass::MyFunction));
}

void TestClass::MyFunction()
{
	std::cout << message << std::endl;
}
