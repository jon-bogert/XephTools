/*========================================================

 XephTools - InputSystem
 Copyright (C) 2022 Jon Bogert (jonbogert@gmail.com)

 This software is provided 'as-is', without any express or implied warranty.
 In no event will the authors be held liable for any damages arising from the use of this software.

 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely,
 subject to the following restrictions:

 1. The origin of this software must not be misrepresented;
	you must not claim that you wrote the original software.
	If you use this software in a product, an acknowledgment
	in the product documentation would be appreciated but is not required.

 2. Altered source versions must be plainly marked as such,
	and must not be misrepresented as being the original software.

 3. This notice may not be removed or altered from any source distribution.

 USAGE NOTES:
  - This Particular unit fo XephTools is meant to be used with SFML: https://www.sfml-dev.org/
  - XInput is required: Add "xinput.lib" to Linker->Additional Dependencies

========================================================*/

#include "XephTools/InputSystem.h"
#include "XephTools/Assert.h"

#include <windows.h>
#include <xinput.h>
#include <vector>
#include <iostream>
#include <string>

xe::InputSystem& xe::InputSystem::Get()
{
	static InputSystem inst;
	return inst;
}

xe::Vector2 xe::InputSystem::MousePosition()
{
	return xe::Vector2(sf::Mouse::getPosition(*Get()._sfWindowRef));
}

float xe::InputSystem::GetMouseSensitivity()
{
	Get().CheckUpdateCall();
	return Get().mouseSensitivity;
}

void xe::InputSystem::SetMouseSensitivity(const float newSensitivity)
{
	Get().CheckUpdateCall();
	Get().mouseSensitivity = newSensitivity;
}

xe::Vector2 xe::InputSystem::GetTriggerPosition(int playerIndex)
{
	XINPUT_STATE state{};
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	XInputGetState(0, &state);
	return { (float)state.Gamepad.bLeftTrigger / 255, (float)state.Gamepad.bRightTrigger / 255 };
}

float xe::InputSystem::DeadZone(const float input)
{
	if (fabs(input) < Get().deadZoneMin)
	{
		return 0.f;
	}
	else if (fabs(input) > Get().deadZoneMax)
	{
		if (input >= 0.f) { return 1.f; }
		else { return -1.f; }
	}
	else
	{
		if (input >= 0.f)
		{
			return (input - Get().deadZoneMin) * (1 / (Get().deadZoneMax - Get().deadZoneMin));
		}
		else
		{
			return (input + Get().deadZoneMin) * (1 / (Get().deadZoneMax - Get().deadZoneMin));
		}
	}
}

void xe::InputSystem::CheckUpdateCall() const
{
	XE_ASSERT(updateCalled, "xe::InputSystem::Update must be first call in Update loop");
}

void xe::InputSystem::InputActions()
{
	for (Callback<Key>& c : keyEvents)
	{
		bool wasDown = c.isDown;
		c.isDown = false;

		if (KeyHold(c.input))
		{
			if (!wasDown && c.pressRelease == Pressed)
			{
				//OnPress()
				c.function();
			}
			c.isDown = true;
		}
		else if (wasDown && c.pressRelease == Released)
		{
			//OnRelease()
			c.function();
		}
	}
	for (Callback<Mouse>& c : mouseEvents)
	{
		bool wasDown = c.isDown;
		c.isDown = false;

		if (MouseHold(c.input))
		{
			if (!wasDown && c.pressRelease == Pressed)
			{
				//OnPress()
				c.function();
			}
			c.isDown = true;
		}
		else if (wasDown && c.pressRelease == Released)
		{
			//OnRelease()
			c.function();
		}
	}
	for (Callback<Button>& c : buttonEvents)
	{
		bool wasDown = c.isDown;
		c.isDown = false;

		if (ButtonHold(c.input))
		{
			if (!wasDown && c.pressRelease == Pressed)
			{
				//OnPress()
				c.function();
			}
			c.isDown = true;
		}
		else if (wasDown && c.pressRelease == Released)
		{
			//OnRelease()
			c.function();
		}
	}
}

void xe::InputSystem::Update(sf::RenderWindow* sfWindow, float deltaTime, bool escapeToClose)
{
	Get()._sfWindowRef = sfWindow;
	Get().deltaTime = deltaTime;
	Get().updateCalled = true;

	sf::Event winEvent;
	while (sfWindow->pollEvent(winEvent))
	{
		if (winEvent.type == sf::Event::Closed || (escapeToClose && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
			sfWindow->close();
	}
	Get().mouseScrollDelta = winEvent.mouseWheelScroll.delta;
	Get().InputActions();
}

float xe::InputSystem::KeyAxis1D(const Key pos, const Key neg)
{
	Get().CheckUpdateCall();
	float target{};
	std::string axisId{};
	//get AxisID
	axisId.append(std::to_string((int)pos));
	axisId.append(std::to_string((int)neg));

	//Find initial direcrions
	if (KeyHold(pos) && !KeyHold(neg))
		target = 1;
	else if (!KeyHold(pos) && KeyHold(neg))
		target = -1;

	//check exist in buffer
	bool inBuffer{};
	int index{};

	for (std::pair<std::string, float> entry : Get().keyAxis1DBuffer)
	{
		if (entry.first == axisId)
		{
			inBuffer = true;
			break;
		}
		else index++;
	}

	//Check to destroy
	if (inBuffer && target == 0 && Get().keyAxis1DBuffer[index].second == 0)
	{
		Get().keyAxis1DBuffer.erase(Get().keyAxis1DBuffer.begin() + index);
	}
	//Buffer needs to exist
	else
	{
		float axisThrowDT = Get().axisThrow * Get().deltaTime;
		//Create buffer if doesn't exist
		if (!inBuffer)
			Get().keyAxis1DBuffer.push_back({ axisId, 0.f });

		//Apply Throw
		if ((Get().keyAxis1DBuffer[index].second < target) && (Get().keyAxis1DBuffer[index].second + axisThrowDT < target))
		{
			Get().keyAxis1DBuffer[index].second += axisThrowDT;
		}
		else if ((Get().keyAxis1DBuffer[index].second > target) && (Get().keyAxis1DBuffer[index].second - axisThrowDT > target))
		{
			Get().keyAxis1DBuffer[index].second -= axisThrowDT;
		}
		else if (((Get().keyAxis1DBuffer[index].second < target) && (Get().keyAxis1DBuffer[index].second + axisThrowDT >= target))
			|| ((Get().keyAxis1DBuffer[index].second > target) && (Get().keyAxis1DBuffer[index].second - axisThrowDT <= target)))
		{
			Get().keyAxis1DBuffer[index].second = target;
		}

		return Get().keyAxis1DBuffer[index].second;
	}

	return 0.f;
}

xe::Vector2 xe::InputSystem::KeyAxis2D(const Key posX, const Key negX, const Key posY, const Key negY)
{
	Get().CheckUpdateCall();
	xe::Vector2 target{};
	std::string axisId{};
	//get AxisID
	axisId.append(std::to_string((int)posX));
	axisId.append(std::to_string((int)negX));
	axisId.append(std::to_string((int)posY));
	axisId.append(std::to_string((int)negY));

	//Find initial direcrions
	if (KeyHold(posX) && !KeyHold(negX))
		target.x = 1;
	else if (!KeyHold(posX) && KeyHold(negX))
		target.x = -1;

	if (KeyHold(posY) && !KeyHold(negY))
		target.y = 1;
	else if (!KeyHold(posY) && KeyHold(negY))
		target.y = -1;

	if (target.x != 0 && target.y != 0)
	{
		target.x = sqrtf(0.5f) * target.x;
		target.y = sqrtf(0.5f) * target.y;
	}

	//check exist in buffer
	bool inBuffer{};
	int index{};

	for (std::pair<std::string, xe::Vector2> entry : Get().keyAxis2DBuffer) //* xe:Vector2 -> xe::Vector2
	{
		if (entry.first == axisId)
		{
			inBuffer = true;
			break;
		}
		else index++;
	}

	//Check to destroy
	if (inBuffer && target.x == 0 && target.y == 0
		&& Get().keyAxis2DBuffer[index].second.x == 0
		&& Get().keyAxis2DBuffer[index].second.y == 0)
	{
		Get().keyAxis2DBuffer.erase(Get().keyAxis2DBuffer.begin() + index);
	}
	//Buffer needs to exist
	else
	{
		float axisThrowDT = Get().axisThrow * Get().deltaTime; //* Time::DeltaTime() -> deltaTime
		//Create buffer if doesn't exist
		if (!inBuffer)
			Get().keyAxis2DBuffer.push_back({ axisId, xe::Vector2() }); //* xe:Vector2 -> xe::Vector2

		//Apply Throw
		if ((Get().keyAxis2DBuffer[index].second.x < target.x) && (Get().keyAxis2DBuffer[index].second.x + axisThrowDT < target.x))
		{
			Get().keyAxis2DBuffer[index].second.x += axisThrowDT;
		}
		else if ((Get().keyAxis2DBuffer[index].second.x > target.x) && (Get().keyAxis2DBuffer[index].second.x - axisThrowDT > target.x))
		{
			Get().keyAxis2DBuffer[index].second.x -= axisThrowDT;
		}
		else if (((Get().keyAxis2DBuffer[index].second.x < target.x) && (Get().keyAxis2DBuffer[index].second.x + axisThrowDT >= target.x))
			|| ((Get().keyAxis2DBuffer[index].second.x > target.x) && (Get().keyAxis2DBuffer[index].second.x - axisThrowDT <= target.x)))
		{
			Get().keyAxis2DBuffer[index].second.x = target.x;
		}

		if ((Get().keyAxis2DBuffer[index].second.y < target.y) && (Get().keyAxis2DBuffer[index].second.y + axisThrowDT < target.y))
		{
			Get().keyAxis2DBuffer[index].second.y += axisThrowDT;
		}
		else if ((Get().keyAxis2DBuffer[index].second.y > target.y) && (Get().keyAxis2DBuffer[index].second.y - axisThrowDT > target.y))
		{
			Get().keyAxis2DBuffer[index].second.y -= axisThrowDT;
		}
		else if (((Get().keyAxis2DBuffer[index].second.y < target.y) && (Get().keyAxis2DBuffer[index].second.y + axisThrowDT >= target.y))
			|| ((Get().keyAxis2DBuffer[index].second.y > target.y) && (Get().keyAxis2DBuffer[index].second.y - axisThrowDT <= target.y)))
		{
			Get().keyAxis2DBuffer[index].second.y = target.y;
		}

		return Get().keyAxis2DBuffer[index].second;
	}

	return xe::Vector2();
}

void xe::InputSystem::Subscribe(const Key key, const Event pressRelease, std::function<void(void)> callback, void* objPtr, int playerNum)
{
	Get().keyEvents.push_back({ key, pressRelease, callback, objPtr, playerNum, false });
}

void xe::InputSystem::Subscribe(const Mouse mouse, const Event pressRelease, std::function<void(void)> callback, void* objPtr, int playerNum)
{
	Get().mouseEvents.push_back({ mouse, pressRelease, callback, objPtr, playerNum, false });
}

void xe::InputSystem::Subscribe(const Button button, const Event pressRelease, std::function<void(void)> callback, void* objPtr, int playerNum)
{
	Get().buttonEvents.push_back({ button, pressRelease, callback, objPtr, playerNum, false });
}

void xe::InputSystem::Unsubscribe(const Key key, const Event pressRelease, void* objPtr, int playerNum)
{
	Callback cb = { key, pressRelease, std::function<void(void)>(), objPtr, playerNum };
	auto it = std::find(Get().keyEvents.begin(), Get().keyEvents.end(), cb);
	if (it != Get().keyEvents.end())
	{
		Get().keyEvents.erase(it);
		return;
	}
}

void xe::InputSystem::Unsubscribe(const Mouse mouse, const Event pressRelease, void* objPtr, int playerNum)
{
	Callback cb = { mouse, pressRelease, std::function<void(void)>(), objPtr, playerNum };
	auto it = std::find(Get().mouseEvents.begin(), Get().mouseEvents.end(), cb);
	if (it != Get().mouseEvents.end())
	{
		Get().mouseEvents.erase(it);
		return;
	}
}

void xe::InputSystem::Unsubscribe(const Button button, const Event pressRelease, void* objPtr, int playerNum)
{
	Callback cb = { button, pressRelease, std::function<void(void)>(), objPtr, playerNum };
	auto it = std::find(Get().buttonEvents.begin(), Get().buttonEvents.end(), cb);
	if (it != Get().buttonEvents.end())
	{
		Get().buttonEvents.erase(it);
		return;
	}
}

bool xe::InputSystem::KeyHold(const Key key)
{
	Get().CheckUpdateCall();
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}

xe::Vector2 xe::InputSystem::GetAxis(Axis axis, int playerIndex)
{
	Get().CheckUpdateCall();
	xe::Vector2 result{};//* xe:Vector2 -> sf::Vector2f

	switch (axis)
	{
	case Axis::LS:
		result.x = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::X) / 100.f);
		result.y = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::Y) / -100.f);
		break;
	case Axis::RS:
		result.x = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::U) / 100.f);
		result.y = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::V) / -100.f);
		break;
	case Axis::DPad:
		result.x = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::PovX) / 100.f);
		result.y = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::PovY) / 100.f);
		break;
	case Axis::Trig:
		//result = { GetTriggerPosition(playerIndex).LT, GetTriggerPosition(playerIndex).RT };
		result = GetTriggerPosition(playerIndex); //* changed from above
		break;
	}

	return result;
}

bool xe::InputSystem::ButtonHold(const Button button, const int playerIndex)
{
	Get().CheckUpdateCall();
	if (button <= Button::RS_Press)
	{
		return sf::Joystick::isButtonPressed(playerIndex, (int)button);
	}

	switch (button)
	{
	case Button::LT:
		return (GetAxis(Axis::Trig, playerIndex).x > 0);
		break;
	case Button::RT:
		return (GetAxis(Axis::Trig, playerIndex).y > 0);
		break;

	case Button::LS_Up:
		return (GetAxis(Axis::LS, playerIndex).y > 0);
		break;
	case Button::LS_Down:
		return (GetAxis(Axis::LS, playerIndex).y < 0);
		break;
	case Button::LS_Left:
		return (GetAxis(Axis::LS, playerIndex).x < 0);
		break;
	case Button::LS_Right:
		return (GetAxis(Axis::LS, playerIndex).x > 0);
		break;

	case Button::RS_Up:
		return (GetAxis(Axis::RS, playerIndex).y > 0);
		break;
	case Button::RS_Down:
		return (GetAxis(Axis::RS, playerIndex).y < 0);
		break;
	case Button::RS_Left:
		return (GetAxis(Axis::RS, playerIndex).x < 0);
		break;
	case Button::RS_Right:
		return (GetAxis(Axis::RS, playerIndex).x > 0);
		break;

	case Button::DPad_Up:
		return (GetAxis(Axis::DPad, playerIndex).y > 0);
		break;
	case Button::DPad_Down:
		return (GetAxis(Axis::DPad, playerIndex).y < 0);
		break;
	case Button::DPad_Left:
		return (GetAxis(Axis::DPad, playerIndex).x < 0);
		break;
	case Button::DPad_Right:
		return (GetAxis(Axis::DPad, playerIndex).x > 0);
		break;
	}
	return false;
}

bool xe::InputSystem::MouseHold(const Mouse mouseButton)
{
	Get().CheckUpdateCall();
	return sf::Mouse::isButtonPressed((sf::Mouse::Button)mouseButton);
}

int xe::InputSystem::MouseScroll()
{
	return Get().mouseScrollDelta;
}

xe::Vector2 xe::InputSystem::MouseDelta()
{
	return xe::Vector2();
}
