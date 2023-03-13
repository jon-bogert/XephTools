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

#ifndef XE_INPUT_SYSTEM_H
#define XE_INPUT_SYSTEM_H

#define XE_USING_SFML
#include "Math.h"

#include <functional>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#define XE_CALLBACK(function) std::bind(&function, this), static_cast<void*>(this) // function must be in format "ClassName::FuncName"
#define XE_CALLBACK_PTR(function, ptr) std::bind(&function, ptr), static_cast<void*>(ptr) // function must be in format "ClassName::FuncName"

namespace xe
{
    enum Event { None, Pressed, Released };

    enum class Key // NOTE: Can Typecast to sf::Keyboard::Key
    {
        Unkwn = -1,
        A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
        Escape, LCtrl, LShift, LAlt, LWin, RCtrl, RShift, RAlt, RWin,
        Menu, LBracket, RBracket, Semicolon, Comma, Period, Quote, ForwardSlash, Backslash,
        Tilde, Equal, Dash, Space, Enter, Backspace, Tab,
        PageUp, PageDown, End, Home, Insert, Delete,
        NumAdd, NumMinus, NumMultiply, NumDivide,
        Left, Right, Up, Down,
        Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
        Pause
    };
    enum class Mouse // NOTE Can Typecast sf::Mouse
    {
        Left, Right, Middle, Button4, Button5
    };
    enum class Button // NOTE does NOT Typecast
    {
        A, B, X, Y, LB, RB, Select, Start, LS_Press, RS_Press, LT, RT,
        LS_Up, LS_Down, LS_Left, LS_Right,
        RS_Up, RS_Down, RS_Left, RS_Right,
        DPad_Up, DPad_Down, DPad_Left, DPad_Right
    };
    enum class Axis
    {
        LS, RS, DPad, Trig
    };
	class InputSystem
	{
		InputSystem() {}
		static InputSystem& Get();

        bool updateCalled = true;

        template<typename T>
        struct Callback
        {
            T input;
            Event pressRelease;
            std::function<void(void)> function;
            void* objPtr;
            int playerNum = 0;
            bool isDown = false;

            bool operator==(const Callback& other) { return (input == other.input && pressRelease == other.pressRelease && objPtr == other.objPtr && playerNum == other.playerNum); }
        };
        uint32_t nextEventID = 1;
        std::vector<Callback<Key>> keyEvents;
        std::vector<Callback<Mouse>> mouseEvents;
        std::vector<Callback<Button>> buttonEvents;
		std::vector<std::pair<std::string, xe::Vector2>> keyAxis2DBuffer;
		std::vector<std::pair<std::string, float >> keyAxis1DBuffer;
		float axisThrow = 15.f;
		bool init = true;

		//* removed struct XE_CONTROLLER_TRIG
		float deadZoneMin = 0.3f;
		float deadZoneMax = 1.f;

		xe::Vector2 mousePosPrev = { 0,0 };
		float mouseSensitivity = 1.f;
        int mouseScrollDelta = 0;

        float deltaTime = 1.f;
        sf::RenderWindow* _sfWindowRef = nullptr;

	public:
        static void Update(sf::RenderWindow* sfWindow, float deltaTime, bool escapeToClose = false); // NOTE: Call Update before any other Update in your Loop

        static float KeyAxis1D(const Key pos, const Key neg);
        static xe::Vector2 KeyAxis2D(const Key posX, const Key negX, const Key posY, const Key negY);

        //Recommended: Only Subscribe to one key action per object
        //Use -> (xe::Key, xe::Event, XE_CALLBACK(ClassName::FuncName))
        static void Subscribe(const Key key, const Event pressRelease, std::function<void(void)> callback, void* objPtr, int playerNum = 0);
        static void Subscribe(const Mouse mouse, const Event pressRelease, std::function<void(void)> callback, void* objPtr, int playerNum = 0);
        static void Subscribe(const Button button, const Event pressRelease, std::function<void(void)> callback, void* objPtr, int playerNum = 0);
        //Unscubscribes all of the same action on object
        static void Unsubscribe(const Key key, const Event pressRelease, void* objPtr, int playerNum = 0);
        static void Unsubscribe(const Mouse mouse, const Event pressRelease, void* objPtr, int playerNum = 0);
        static void Unsubscribe(const Button button, const Event pressRelease, void* objPtr, int playerNum = 0);

        static bool KeyHold(const Key key);

        static xe::Vector2 GetAxis(Axis axis, int playerIndex = 0); // For triggers-> X is LT, Y is RT (0.->1. only)
        static bool ButtonHold(const Button button, const int playerIndex = 0);

        static bool MouseHold(const Mouse mouseButton);
        static int MouseScroll();
        static xe::Vector2 MouseDelta();
        static xe::Vector2 MousePosition();
        static float GetMouseSensitivity();
        static void SetMouseSensitivity(const float newSensitivity);

    private:
        static xe::Vector2 GetTriggerPosition(int playerIndex);
        static float DeadZone(const float input);
        void CheckUpdateCall() const;

        void InputActions();
	};
}

#endif // XE_INPUT_SYSTEM_H
