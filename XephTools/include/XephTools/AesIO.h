/*========================================================

 XephTools - AESIO
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

#ifndef XE_AES_IO_H
#define XE_AES_IO_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <assert.h>

namespace xe
{
	class AESWriter
	{
		std::ofstream _file;
		std::stringstream _buffer;
		std::vector<unsigned char> _key;

		void Save();
	public:
		AESWriter(std::vector<unsigned char> key);
		AESWriter(std::string key);
		~AESWriter();

		void Open(std::string file);
		void Close();
		bool IsOpen();

		template <class T>
		void Write(const T& val);
		template <class T>
		void WriteLine(const T& val);
	};
	template<class T>
	inline void AESWriter::Write(const T& val)
	{
		assert(_file.is_open());
		_buffer << val;
	}
	template<class T>
	inline void AESWriter::WriteLine(const T& val)
	{
		assert(_file.is_open());
		_buffer << val << std::endl;
	}


	//==================================================================

	class AESReader
	{
		std::ifstream _file;
		std::stringstream _buffer;
		std::vector<unsigned char> _key;
		bool _binaryMode = false;
		std::vector<uint8_t> _byteBuffer;
		size_t _byteCur = 0;

		void Load();

	public:
		AESReader(std::vector<unsigned char> key);
		AESReader(std::string key);
		~AESReader();

		void Open(std::string file, bool binaryMode = false);
		void Close();
		bool IsOpen();

		bool ReadLine(std::string& out_line);
		bool ReadNext(unsigned char& out_char);
		bool EndOfFile();
		std::string ReadAll();
	};
}

#endif // XE_AES_READ_WRITE_H
