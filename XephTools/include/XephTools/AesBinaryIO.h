/*========================================================

 XephTools - AESBinaryIO
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

#ifndef XE_AES_BINARY_IO_H
#define XE_AES_BINARY_IO_H

#include <fstream>
#include <vector>

#include "AesIO.h"

namespace xe
{
	class AESBinaryWriter
	{
		AESWriter _file;
		std::vector<uint8_t> _buffer;

	public:
		AESBinaryWriter(std::vector<uint8_t> key);
		AESBinaryWriter(std::string key);
		~AESBinaryWriter();

		void Open(std::string file);
		void Close();

		bool IsOpen();

		void Write(char value);
		void Write(short value);
		void Write(unsigned short value);
		void Write(int value);
		void Write(unsigned value);
		void Write(long value);
		void Write(unsigned long value);
		void Write(float value);
		void Write(double value);
		void Write(std::string value);
		void Write(const char* value);

	private:
		std::vector<uint8_t> StrLen(size_t length);
	};



	class AESBinaryReader
	{
		AESReader _file;
		std::vector<uint8_t> _buffer;

	public:
		AESBinaryReader(std::vector<uint8_t> key);
		AESBinaryReader(std::string key);
		~AESBinaryReader();

		void Open(std::string file);
		void Close();

		bool IsOpen();
		bool EndOfFile();

		char ReadChar();
		short ReadShort();
		unsigned short ReadUShort();
		int ReadInt();
		unsigned ReadUInt();
		long ReadLong();
		unsigned long ReadULong();
		float ReadFloat();
		double ReadDouble();
		std::string ReadString();

	private:
		size_t StrLen();
	};

}
#endif