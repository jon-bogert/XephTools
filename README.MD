# XephTools - Readme

## Description

XephTools is a collection of easy-to-use tools for common tasks.

## Modules

### AppData
Easy access to the windows roaming appdata directory (`%APPDATA%\Roaming`). Access available via `_APPDATA_` Macro.

NOTE: link to `shell32` system library required.

### Assert
An assert template providing file and line information. Provides `XE_ASSERT(condition, message)` macro.

### Benchmark
Scope base benchmarking for `chrome://tracing` debug tool (built into Google Chrome). To use, create a `xe::Benchmark` instance in your entry point and call `xe::Benchmark::Get().BeginSession` and `xe::Benchmark::Get().EndSession` at the beginning and end. of your program. Then call `XEBenchmarkFunction` at the top of each function you want to benchmark. You can allso call `XEBenchmarkScope(name)` if you want to benchmark a scope that is not a function. To see data, open the resulting json file in `chrome://tracing`
```cpp
// Example
#include <XephTools/Benchmark.h>

void NewFrame()
{
    XEBenchmarkFunction;

    // Do Something;
    return true;
}

int main()
{
    xe::Benchmark::Get().BeginSession("My App");

    bool isOpen = true;
    while(isOpen)
    {
        isOpen = NewFrame();
    }

    xe::Benchmark::Get().EndSession();
    return 0;
}
```

### Binary Reader/Writer
Read and write binary data. Compatible with the DotNET Binary Reader and Writer.

### Clipboard
Easily copy string or binary data to the Windows clipboard via `xe::CopyToClipboard`.

### Command Stack
A command system that allows for undo and redo. Main methods are `xe::CommandStack::PushAndExecute`, `xe::CommandStack::Undo` and `xe::CommandStack::Redo`.

### EntryPoint
Dynamic entry point for your app while encapsulating arguments into a `std::vector<std::string>`. The system will use `main` if `_CONSOLE` is defined and `WinMain` if not. Also will use `wmain` or `wWinMain` if `XE_USE_WIDE_ENTRY` is defined. This can be handy if you want the debug version of your app to be a console app and release to be a windowed app.
```cpp
// Example
#include <XephTools/EntryPoint.h>

int MyEntry(std::vector<std::string> args)
{
    return 0;
}

SetEntryPoint(MyEntry) // This will define main or WinMain
```

### Event

Easy-to-use event that can have multiple callbacks subscribed to it. Subscribe provides a 32-bit uinsigned integar ID that can be stored and used to unsubscribe. Template based context included for flexible parameter usage.
```cpp
#include <XephTools/Event.h>
#include <iostream>

xe::Event g_event;

class MyClass
{
public:
    void SetValue(int val)
    {
        m_val = val;
    }

    void Setup()
    {
        m_callbackID = g_event.Subscribe([&](){ Execute(); });
    }

    void Shutdown()
    {
        g_event.Unsubscribe(m_callbackID);
    }

private:
    void Execute()
    {
        std::cout << "My value is: " << m_val << std::endl;
    }

    int m_val = 0;
    xe::FuncID m_callbackID = 0;
};

int main()
{
    MyClass classes[3];
    for (int i = 0; i < 3; ++i)
    {
        classes[i].Setup();
        classes[i].SetValue(i);
    }

    g_event.Invoke();

    for (int i = 0; i < 3; ++i)
    {
        classes[i].Shutdown();
    }

    return 0;
}
```

### File Browser
Access to various file and folder browsers. Allows for file extention specifications. All Methods return empty paths if cancelled.

### Generic Pointer (generic_ptr.h)
Generic pointer combines the conviniences of a `std::unique_ptr` and `void*`. Destructors are automatically called while also not having to specify types within header files. Perfect for creating wrappers for libaries that hide their internal libarary headers while also maintaining safe memory management techniques. Use `xe::generic_ptr::as<T>()` for clean casting to a reference of that type and `xe::generic_ptr::get<T>()` to get a raw pointer of that type.
```cpp
// Example header file

#include <XephTools/generic_ptr.h>
// SFML Header is NOT included here and sf::RenderWindow is not declared as to hide all SFML types

#include <string>

class WindowManager
{
public:
    void Setup(uint32_t width, uint32_t height, std::string title);
    void Update();

private:
    xe::generic_ptr m_window;
};
```
```cpp
// Example source file
#include "WindowManager.h" // The example header
#include <SFML/Graphics.hpp>

void WindowManager::Setup(uint32_t width, uint32_t height, std::string title)
{
    m_window.make<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Type::Close); // Create instance with constructor values.
}

void WindowManager::Update()
{
    // Standard SFML Update loop
    sf::RenderWindow& window = m_window.as<sf::RenderWindow>(); // Cleaner than *((sf::RenderWidow*)m_window) or *reinterpret_cast<sf::RenderWindow*>(m_window)
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.clear();
    window.display();
}
```

### Math
Just a math library. Provides type conversions to SFML types if headers are included above this one.

### Random
Provides uint32_t random values as well as ranges for ints and floats.

### Timer
Easy to use timer.

### XESample
Useful for dealing with various sample sizes. Provides implementation for signed and unsined 8-bit, 16-bit and most importantly, 24-bit samples.
