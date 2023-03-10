Some modules are to be used with SFML (https://www.sfml-dev.org/)
	if planning on using, include SFML headers above XephTools.h or these modules will be disabled
	if planning on using, Add "xinput.lib" to Linker->Input->Additional Dependencies
	
DESCRIPTIONS:

AesBinaryIO
	- Reader and Writer for binary files that are encrypted with 128 bit Advanced Encryption Standard (AES)
	
AesIO
	- Reader and Writer for formatted text files that are encrypted with 128 bit Advanced Encryption Standard (AES)
	
Assert
	- Custom Assert that allows for a condition and message that is triggered on "false" (call XE_ASSERT(condition, message))
	
BinaryIO
	- Reader amd Writer for binary files (non-encrypted)
	
InputSystem (Only available when including SFML in project)
	- Replacement input system for SFML (https://www.sfml-dev.org/)
	- Improved Key/Button enumerators
	- Subscribe and unsubscribe functions to press and release events
	- Uses XInput for better gamepad trigger values (remember to add "xinput.lib")

Math
	- Math Library that implicitly converts to SFML Data types (if SFML is in project)
	
SaveFile
	- Save file system for games;
	- SaveFile loads and stores data that can be get or set by an object.
	- Internal data is stored in file when .Save() is called
	- Save as Text, TextEncrypted, Binary, or BinaryEncrypted file types
	
Timer
	- Timer for when sf::Clock is not available, with a few extra features;
	- .DeltaTime() gets seconds elapsed and restarts timer
	- .FPS() gets 1/elapsed and restarts timer
	
AppData
	- Provides Macro std::string for "%APPDATA%"
	- _APPDATA_ -> "C:\\Users\\<name>\\AppData\\Roaming"
	- APPDATA_PATH = _APPDATA_
	- _APPDATA_CSTR_ -> Gets path as const char*
	
INSTALLATION (VS 20XX):
	1. if using SFML, install as prefered.
	2. Add "lib" and "include" folders to project directory
	3. In Project Settings:
		a) Add "include" to C/C++->General->Additional Include Directories
		b) Add "lib" to Linker->General->Additional Library Directoies
		c) Add "xephtools.lib" to Linker->Input->Additional Dependencies
		c) Add "Shell32.lib" to Linker->Input->Additional Dependencies
		d) if planning to use SFML, add "xinput.lib" to Linker->Input->Additional Dependencies as well
	4. Add #include "XephTools.h" to your scripts