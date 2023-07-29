/*========================================================

 XephTools
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
 - Some modules are to be used with SFML (https://www.sfml-dev.org/)
	- if planning on using, include SFML headers above XephTools.h or these modules will be disabled
	- if planning on using, Add "xinput.lib" to Linker->Additional Dependencies

========================================================*/

#ifndef XE_XEPH_TOOLS_H
#define XE_XEPH_TOOLS_H

//Checking if SFML is included
#ifdef SFML_SYSTEM_HPP
#ifdef SFML_SFML_WINDOW_HPP
#ifdef SFML_GRAPHICS_HPP

#define XE_USING_SFML

#endif // SFML_GRAPHICS_HPP
#endif // SFML_SFML_WINDOW_HPP
#endif // SFML_SYSTEM_HPP

#ifdef BOX2D_H
#define XE_USING_BOX2D
#endif // BOX2D_H

// Header Only
#include "XephTools/Assert.h"
#include "XephTools/BinaryReader.h"
#include "XephTools/BinaryWriter.h"
#include "XephTools/Timer.h"
#include "XephTools/Random.h"
#include "XephTools/AppData.h"
#include "XephTools/Event.h"


// Header & CPP
#include "XephTools/Math.h"
#include "XephTools/SaveFile.h"

//SFML LIBRARY DEPENDANT
#ifdef XE_USING_SFML
#include "XephTools/InputSystem.h"
#endif

#endif // XE_XEPH_TOOLS_H