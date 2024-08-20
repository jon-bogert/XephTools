/*========================================================

 XephTools - Event
 Copyright (C) 2024 Jon Bogert (jonbogert@gmail.com)

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

#ifndef XE_EVENT_H
#define XE_EVENT_H

#include <cstdint>
#include <functional>
#include <random>
#include <type_traits>
#include <unordered_map>

namespace xe
{
	using FuncID = uint32_t;

	template <typename Context = void, typename Enable = void>
	class Event;

	template <typename Context>
	class Event<typename Context, typename std::enable_if_t<std::is_void_v<Context>>>
	{
	public:

		FuncID Subscribe(const std::function<void(Context)>& callback)
		{
			FuncID id = NewID();
			m_callbacks[id] = callback;
			return id;
		}

		bool Unsubscribe(const FuncID id)
		{
			if (!Contains(id))
				return false;
			m_callbacks.erase(id);
			return true;
		}

		void Invoke() const
		{
			for (const auto& cb : m_callbacks)
			{
				cb.second();
			}
		}

		bool Contains(const FuncID id) const
		{
			return m_callbacks.find(id) != m_callbacks.end();
		}
		
		void Clear()
		{
			m_callbacks.clear();
		}

		size_t Size() const
		{
			return m_callbacks.size();
		}

	private:
		FuncID NewID() const
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<uint32_t> dis(0, UINT32_MAX);
			return dis(gen);
		}

		std::unordered_map<FuncID, std::function<void(Context)>> m_callbacks;

	};

	template <typename Context>
	class Event<typename Context, typename std::enable_if_t<!std::is_void_v<Context>>>
	{
	public:

		FuncID Subscribe(const std::function<void(Context)>& callback)
		{
			FuncID id = NewID();
			m_callbacks[id] = callback;
			return id;
		}

		bool Unsubscribe(const FuncID id)
		{
			if (!Contains(id))
				return false;
			m_callbacks.erase(id);
			return true;
		}

		void Invoke(const Context& ctx) const
		{
			for (const auto& cb : m_callbacks)
			{
				cb.second(ctx);
			}
		}

		bool Contains(const FuncID id) const
		{
			return m_callbacks.find(id) != m_callbacks.end();
		}

		void Clear()
		{
			m_callbacks.clear();
		}

		size_t Size() const
		{
			return m_callbacks.size();
		}

	private:
		FuncID NewID() const
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<uint32_t> dis(0, UINT32_MAX);
			return dis(gen);
		}

		std::unordered_map<FuncID, std::function<void(Context)>> m_callbacks;
	};
}

#endif //!XE_EVENT_H