/*========================================================

 XephTools - Binary Reader
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

#ifndef XE_BINARYREADER_H
#define XE_BINARYREADER_H

#include <filesystem>
#include <fstream>
#include <string>
#include <type_traits>

namespace xe
{
	class BinaryReader
	{
	public:
		enum class SeekMode
		{
			Beginning,
			Cursor,
			End,
		};

		BinaryReader() = default;
		BinaryReader(const std::filesystem::path& path) { Open(path); }

		~BinaryReader() { Close(); }

		BinaryReader(const BinaryReader& other) = delete;
		BinaryReader operator=(const BinaryReader& other) = delete;
		BinaryReader(BinaryReader&& other)
		{
			m_file = std::move(other.m_file);
			m_size = std::move(other.m_size);
		}
		BinaryReader& operator=(BinaryReader&& other)
		{
			m_file = std::move(other.m_file);
			m_size = std::move(other.m_size);
			return *this;
		}

		bool Open(const std::filesystem::path& path)
		{
			if (IsOpen())
				throw (std::exception("File is already open."));

			m_file.open(path, std::ios::binary | std::ios::ate);
			if (!m_file.is_open())
				return false;

			m_size = m_file.tellg();
			m_file.seekg(0, std::ios::beg);
			return true;
		}
		void Close()
		{
			if (!IsOpen())
				return;

			m_file.close();
			m_size = 0;
		}
		bool IsOpen() const
		{
			return m_file.is_open();
		}

		void Seek(size_t pos, SeekMode from = SeekMode::Beginning)
		{
			m_file.seekg(pos, static_cast<int>(from));
		}
		size_t Tell()
		{
			return m_file.tellg();
		}

		bool EoF()
		{
			return (!IsOpen() || m_file.eof() || m_file.peek() == -1);
		}
		bool Empty() const
		{
			return (m_size == 0);
		}
		size_t Size() const
		{
			return m_size;
		}

		size_t GetSizeValue()
		{
			size_t result = 0;
			size_t shift = 0;
			uint8_t byte;

			do
			{
				if (!m_file.read(reinterpret_cast<char*>(&byte), 1))
					return 0;

				result |= static_cast<size_t>(byte & 0x7F) << shift;
				shift += 7;

				if (shift >= sizeof(size_t) * 8)
					return 0;
				
			} while (byte & 0x80);
			return result;
		}

		// String
		template <typename T>
		typename std::enable_if_t<std::is_base_of_v<std::string, T>, T>
			GetValue(size_t size = 0)
		{
			if (size == 0)
				size = GetSizeValue();

			std::string result;
			result.resize(size + 1);
			m_file.read(reinterpret_cast<char*>(result.data()), size);
			result[size] = '\0';
			return result;
		}

		template <typename T>
		typename std::enable_if_t<std::is_base_of_v<std::string, T>, void>
			GetValue(T& buffer, size_t size = 0)
		{
			if (size == 0)
				size = GetSizeValue();

			buffer.resize(size + 1);
			m_file.read(reinterpret_cast<char*>(buffer.data()), size);
			buffer[size] = '\0';
		}

		// Byte Buffer
		template <typename T>
		typename std::enable_if_t<std::is_base_of_v<std::vector<uint8_t>, T>, T>
			GetValue(size_t size = 0)
		{
			if (size == 0)
				size = GetSizeValue();

			std::vector<uint8_t> result;
			result.resize(size);
			m_file.read(reinterpret_cast<char*>(result.data()), size);
			return result;
		}

		template <typename T>
		typename std::enable_if_t<std::is_base_of_v<std::vector<uint8_t>, T>, void>
			GetValue(T& buffer, size_t size = 0)
		{
			if (size == 0)
				size = GetSizeValue();

			buffer.resize(size);
			m_file.read(reinterpret_cast<char*>(buffer.data()), size);
		}

		// Default overloads
		template <typename T>
		typename std::enable_if_t<!std::is_base_of_v<std::string, T> &&
			!std::is_base_of_v<std::vector<uint8_t>, T>, T>
			GetValue()
		{
			T result{};
			m_file.read(reinterpret_cast<char*>(&result), sizeof(T));
			return result;
		}

		template <typename T>
		typename std::enable_if_t<!std::is_base_of_v<std::string, T> &&
			!std::is_base_of_v<std::vector<uint8_t>, T>, void>
			GetValue(T& buffer)
		{
			m_file.read(reinterpret_cast<char*>(&buffer), sizeof(T));
		}

	private:
		std::ifstream m_file;
		size_t m_size;
	};
}

#endif // !XE_BINARYREADER_H