/*========================================================

 XephTools - Random
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

#ifndef __XE_RANDOM_H__
#define __XE_RANDOM_H__

#include <chrono>
#include <stdint.h>
#include <assert.h>

namespace xe
{
	class Random
	{
		uint32_t _seed = 0;
		uint32_t _mult;
		uint32_t _incr;
		uint32_t _mod = UINT32_MAX;

		Random()
		{
			std::chrono::system_clock::time_point currTime = std::chrono::system_clock::now();
			_seed = static_cast<uint32_t>(currTime.time_since_epoch().count());
			_mult = _seed ^ (_seed << 13) ^ (_seed >> 16) ^ (_seed << 5);
			_incr = _seed ^ (_seed << 2) ^ (_seed >> 10) ^ (_seed << 4);
		}

		static Random& Inst()
		{
			static Random inst;
			return inst;
		}

	public:
		static uint32_t Get()
		{
			Random& inst = Inst();
			inst._seed = (inst._mult * inst._seed + inst._incr) % inst._mod;
			return inst._seed;
		}
		static uint32_t GetLast()
		{
			return Inst()._seed;
		}
		static uint32_t NewSeed()
		{
			Random& inst = Inst();
			std::chrono::system_clock::time_point currTime = std::chrono::system_clock::now();
			inst._seed = static_cast<uint32_t>(currTime.time_since_epoch().count());
			inst._mult = inst._seed ^ (inst._seed << 13) ^ (inst._seed >> 16) ^ (inst._seed << 5);
			inst._incr = inst._seed ^ (inst._seed << 2) ^ (inst._seed >> 10) ^ (inst._seed << 4);
			return inst._seed;
		}

		static int Range(const int min, const int max)
		{
			assert(min <= max); // Minimum value must be greater than Maximum
			uint32_t num = Inst().Get();
			return num & (max - min) + min;
		}
		static int Range(const int min, const int max, const uint16_t incr)
		{
			assert(min <= max); // Minimum value must be greater than Maximum
			assert(incr > 0); // Increment value must not be zero
			return Range(min / incr, max / incr) * incr;
		}

		static float RangeFloat(float min, float max, float incr)
		{
			assert(min <= max); // Minimum value must be greater than Maximum
			assert(incr != 0.f); // Increment value must not be zero
			uint32_t num = Inst().Get();

			float scaledValue = static_cast<float>(num) / UINT32_MAX;
			float range = max - min;

			return min + std::round(scaledValue * range / incr) * incr;
		}
	};
}

#endif // __XE_RANDOM_H__
