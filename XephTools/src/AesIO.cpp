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

#include "XephTools/AesIO.h"
#include "external/AES.h"

std::vector<unsigned char> ParseStrKey(std::string keyStr)
{
    assert(keyStr.length() == 32);
    std::vector<unsigned char> key;
    for (size_t i = 0; i < keyStr.length(); i += 2)
    {
        uint8_t currByte = 0x0;
        switch (keyStr[i])
        {
        case '0':
            currByte = 0x00;
            break;
        case '1':
            currByte = 0x10;
            break;
        case '2':
            currByte = 0x20;
            break;
        case '3':
            currByte = 0x30;
            break;
        case '4':
            currByte = 0x40;
            break;
        case '5':
            currByte = 0x50;
            break;
        case '6':
            currByte = 0x60;
            break;
        case '7':
            currByte = 0x70;
            break;
        case '8':
            currByte = 0x80;
            break;
        case '9':
            currByte = 0x90;
            break;
        case 'a':
        case 'A':
            currByte = 0xa0;
            break;
        case 'b':
        case 'B':
            currByte = 0xb0;
            break;
        case 'c':
        case 'C':
            currByte = 0xc0;
            break;
        case 'd':
        case 'D':
            currByte = 0xd0;
            break;
        case 'e':
        case 'E':
            currByte = 0xe0;
            break;
        case 'f':
        case 'F':
            currByte = 0xf0;
            break;
        }
        switch (keyStr[i + 1])
        {
        case '0':
            currByte += 0x00;
            break;
        case '1':
            currByte += 0x01;
            break;
        case '2':
            currByte += 0x02;
            break;
        case '3':
            currByte += 0x03;
            break;
        case '4':
            currByte += 0x04;
            break;
        case '5':
            currByte += 0x05;
            break;
        case '6':
            currByte += 0x06;
            break;
        case '7':
            currByte += 0x07;
            break;
        case '8':
            currByte += 0x08;
            break;
        case '9':
            currByte += 0x09;
            break;
        case 'a':
        case 'A':
            currByte += 0x0a;
            break;
        case 'b':
        case 'B':
            currByte += 0x0b;
            break;
        case 'c':
        case 'C':
            currByte += 0x0c;
            break;
        case 'd':
        case 'D':
            currByte += 0x0d;
            break;
        case 'e':
        case 'E':
            currByte += 0x0e;
            break;
        case 'f':
        case 'F':
            currByte += 0x0f;
            break;
        }

        key.push_back(currByte);
    }
    return key;
}

void xe::AESWriter::Save()
{
	std::string bufferStr = _buffer.str();
	std::vector<unsigned char> bufferVect;
	if (bufferStr.length() % 16 != 0)
	{
		bufferStr.resize(bufferStr.length() + (16 - (bufferStr.length() % 16)), 0);
	}
	for (char& c : bufferStr)
	{
		bufferVect.push_back(c);
	}

	AES aes(AESKeyLength::AES_128);
	std::vector<unsigned char> encrypted = aes.EncryptECB(bufferVect, _key);

	for (unsigned char& c : encrypted)
		_file << c;
}

xe::AESWriter::AESWriter(std::vector<unsigned char> key)
	: _key(key)
{
}

xe::AESWriter::AESWriter(std::string key)
{
    _key = ParseStrKey(key);
}

xe::AESWriter::~AESWriter()
{
	Close();
}

void xe::AESWriter::Open(std::string file)
{
	_file.open(file);
	assert(_file.is_open());
}

void xe::AESWriter::Close()
{
	if (_file.is_open())
	{
		Save();
		_file.close();
	}
}

bool xe::AESWriter::IsOpen()
{
    return _file.is_open();
}

void xe::AESReader::Load()
{
	std::vector<unsigned char> encrypted;
	std::string line;
	while (std::getline(_file, line))
	{
		for (char& c : line)
			encrypted.push_back(c);
		encrypted.push_back('\n');
	}
	if (!encrypted.empty())encrypted.pop_back();

	AES aes(AESKeyLength::AES_128);
	std::vector<unsigned char> decrypted = aes.DecryptECB(encrypted, _key);

    while (!decrypted.empty() && decrypted.back() == '\0')
        decrypted.pop_back();

    if (_binaryMode)
    {
        _byteBuffer = decrypted;
    }

	for (unsigned char& c : decrypted)
	{
		_buffer << c;
	}
}

xe::AESReader::AESReader(std::vector<unsigned char> key)
	: _key(key)
{
}

xe::AESReader::AESReader(std::string key)
{
    _key = ParseStrKey(key);
}

xe::AESReader::~AESReader()
{
	Close();
}

void xe::AESReader::Open(std::string file, bool binaryMode)
{
    _binaryMode = binaryMode;
	(binaryMode) ? _file.open(file, std::ios::binary) : _file.open(file);
    if (!_file.is_open())
    {
        std::ofstream create;
        create.open(file);
        create.close();
        (binaryMode) ? _file.open(file, std::ios::binary) : _file.open(file);
        assert(_file.is_open());
        return;
    }

	Load();
}

void xe::AESReader::Close()
{
	if (_file.is_open())
		_file.close();
}

bool xe::AESReader::IsOpen()
{
    return _file.is_open();
}

bool xe::AESReader::ReadLine(std::string& out_line)
{
    assert(_file.is_open());
    if (_buffer.eof() || _binaryMode)
        return false;

    std::getline(_buffer, out_line, '\n');
    return true;
}

bool xe::AESReader::ReadNext(unsigned char& out_char)
{
    assert(_file.is_open());

    if (_binaryMode)
    {
        if (_byteCur >= _byteBuffer.size())
            return false;
        out_char = _byteBuffer[_byteCur++];
        return true;
    }

    if (_buffer.eof())
        return false;
    out_char = _file.get();
    return true;
}

bool xe::AESReader::EndOfFile()
{
    assert(_file.is_open());

    return (_binaryMode) ? _byteCur >= _byteBuffer.size() : (_buffer.eof() || _buffer.peek() == -1);
}

std::string xe::AESReader::ReadAll()
{
    assert(_file.is_open());
    return _buffer.str();
}
