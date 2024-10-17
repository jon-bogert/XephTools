/*========================================================

 XephTools - Binary Writer
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

 Note:
  - 'const char*' will not work properly. Wrap in std::string constructor.

========================================================*/

#ifndef XE_BINARYWRITER_H
#define XE_BINARYWRITER_H

#include <filesystem>
#include <fstream>
#include <string>
#include <type_traits>

namespace xe
{
	class BinaryWriter
	{
	public:
		BinaryWriter() = default;
		BinaryWriter(const std::filesystem::path& path, bool truncate = true) { Open(path, truncate); }

		~BinaryWriter() { Close(); }

		BinaryWriter(const BinaryWriter& other) = delete;
		BinaryWriter operator=(const BinaryWriter& other) = delete;
		BinaryWriter(BinaryWriter&& other) noexcept
		{
			m_file = std::move(other.m_file);
		}
		BinaryWriter& operator=(BinaryWriter&& other) noexcept
		{
			m_file = std::move(other.m_file);
			return *this;
		}

		bool Open(const std::filesystem::path& path, bool truncate = true)
		{
			if (IsOpen())
				throw (std::exception("File is already open."));

			int doTrunk = (truncate) ? std::ios::trunc : 0;

			m_file.open(path, std::ios::binary | doTrunk);
			if (!m_file.is_open())
				return false;

			return true;
		}
		void Close()
		{
			if (!IsOpen())
				return;

			m_file.close();
		}
		bool IsOpen() const
		{
			return m_file.is_open();
		}

		void WriteSizeValue(size_t size)
		{
			do
			{
				uint8_t byte = size & 0x7F;
				size >>= 7;

				if (size > 0)
				{
					byte |= 0x80;
				}

				m_file.write(reinterpret_cast<char*>(&byte), 1);
			} while (size > 0);
		}

		// String
		template <typename T>
		typename std::enable_if_t<std::is_base_of_v<std::string, T>, void>
			WriteValue(const T& value, size_t size = 0)
		{
			if (size == 0)
			{
				size = value.length();
				WriteSizeValue(size);
			}

			m_file.write(reinterpret_cast<const char*>(value.c_str()), size);
		}

		// Byte Buffer
		template <typename T>
		typename std::enable_if_t<std::is_base_of_v<std::vector<uint8_t>, T>, void>
			WriteValue(const T& value, size_t size = 0)
		{
			if (size == 0)
			{
				size = value.size();
				WriteSizeValue(size);
			}

			m_file.write(reinterpret_cast<const char*>(value.data()), size);
		}

		template <typename T>
		typename std::enable_if_t<!std::is_base_of_v<std::string, T> &&
			!std::is_base_of_v<std::vector<uint8_t>, T>, void>
			WriteValue(const T& value)
		{
			m_file.write(reinterpret_cast<const char*>(&value), sizeof(T));
		}

	private:
		std::ofstream m_file;
	};
}

#endif // !XE_BINARYWRITER_H