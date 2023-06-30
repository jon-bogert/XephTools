/*========================================================

 XephTools - Event
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

========================================================*/

#ifndef __XE_EVENT_H__
#define __XE_EVENT_H__

#include <functional>
#include <list>

#define XEEventCallback(function) static_cast<void*>(this), std::bind(&function, this)
#define XEEventCallbackPtr(function, ptr) static_cast<void*>(ptr), std::bind(&function, ptr)

namespace xe
{
    class Event
    {
    private:
        struct EventEntry
        {
            void* object;
            std::function<void(void)> function;
        };

        std::list<EventEntry> events;

    public:
        void Subscribe(void* object, std::function<void(void)> function)
        {
            events.push_back({ object, function });
        }

        void UnsubscribeAll(void* object)
        {
            events.remove_if([=](const EventEntry& x) {return object == x.object; });
        }

        void Invoke() {
            for (const auto& event : events)
            {
                event.function();
            }
        }
    };
}

#endif //__XE_EVENT_H__