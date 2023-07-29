Some modules are to be used with SFML (https://www.sfml-dev.org/)
	if planning on using, include SFML headers above XephTools.h or these modules will be disabled
	if planning on using, Add "xinput.lib" to Linker->Input->Additional Dependencies
	
DESCRIPTIONS:
	
Assert
	- Custom Assert that allows for a condition and message that is triggered on "false" (call XE_ASSERT(condition, message))
	
BinaryReader/BinaryWriter
	- Reader amd Writer for binary files (non-encrypted)
	
InputSystem (Only available when including SFML in project)
	- Replacement input system for SFML (https://www.sfml-dev.org/)
	- Improved Key/Button enumerators
	- Subscribe and unsubscribe functions to press and release events
	- Uses XInput for better gamepad trigger values

Math
	- Math Library that implicitly converts to SFML Data types (if SFML is in project)
	
SaveFile
	- Save file system for games;
	- SaveFile loads and stores data that can be get or set by an object.
	- Internal data is stored in file when .Save() is called
	- Save as Text, TextEncrypted, Json, Binary, or BinaryEncrypted file types
	
Timer
	- Timer for when sf::Clock is not available, with a few extra features;
	- .DeltaTime() gets seconds elapsed and restarts timer
	- .FPS() gets 1/elapsed and restarts timer
	
AppData
	- Provides Macro std::string for "%APPDATA%"
	- "_APPDATA_" -> "C:\\Users\\<name>\\AppData\\Roaming"
	- "APPDATA_PATH" = "_APPDATA_"
	- "_APPDATA_CSTR_" -> Gets path as const char*
	- Link "Shell32.lib" if using as header-only
