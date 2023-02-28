/*========================================================

 XephTools - BinaryIO
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

#include "XephTools/BinaryIO.h"

xe::BinaryWriter::BinaryWriter()
{
}

xe::BinaryWriter::~BinaryWriter()
{
    Close();
}

void xe::BinaryWriter::Open(std::string file)
{
    _file.open(file);
}

void xe::BinaryWriter::Close()
{
    if (_file.is_open())
        _file.close();
}

bool xe::BinaryWriter::IsOpen()
{
    return _file.is_open();
}

void xe::BinaryWriter::Write(char value)
{
    _file << value;
}

void xe::BinaryWriter::Write(short value)
{
    uint16_t* valPtr = reinterpret_cast<uint16_t*>(&value);
    _buffer.clear();
    _buffer.resize(2);
    _buffer[0] = (char)*valPtr;
    _buffer[1] = (char)(*valPtr >> 8);

    for (size_t i = 0; i < _buffer.size(); ++i)
    {
        _file << _buffer[i];
    }
}

void xe::BinaryWriter::Write(unsigned short value)
{
    uint16_t* valPtr = reinterpret_cast<uint16_t*>(&value);
    _buffer.clear();
    _buffer.resize(2);
    _buffer[0] = (char)*valPtr;
    _buffer[1] = (char)(*valPtr >> 8);

    for (size_t i = 0; i < _buffer.size(); ++i)
    {
        _file << _buffer[i];
    }
}

void xe::BinaryWriter::Write(int value)
{
    uint32_t* valPtr = reinterpret_cast<uint32_t*>(&value);
    _buffer.clear();
    _buffer.resize(4);
    _buffer[0] = (char)*valPtr;
    _buffer[1] = (char)(*valPtr >> 8);
    _buffer[2] = (char)(*valPtr >> 16);
    _buffer[3] = (char)(*valPtr >> 24);

    for (size_t i = 0; i < _buffer.size(); ++i)
    {
        _file << _buffer[i];
    }
}

void xe::BinaryWriter::Write(unsigned value)
{
    uint32_t* valPtr = reinterpret_cast<uint32_t*>(&value);
    _buffer.clear();
    _buffer.resize(4);
    _buffer[0] = (char)*valPtr;
    _buffer[1] = (char)(*valPtr >> 8);
    _buffer[2] = (char)(*valPtr >> 16);
    _buffer[3] = (char)(*valPtr >> 24);

    for (size_t i = 0; i < _buffer.size(); ++i)
    {
        _file << _buffer[i];
    }
}

void xe::BinaryWriter::Write(long value)
{
    uint64_t* valPtr = reinterpret_cast<uint64_t*>(&value);
    _buffer.clear();
    _buffer.resize(8);
    _buffer[0] = (char)*valPtr;
    _buffer[1] = (char)(*valPtr >> 8);
    _buffer[2] = (char)(*valPtr >> 16);
    _buffer[3] = (char)(*valPtr >> 24);
    _buffer[4] = (char)(*valPtr >> 32);
    _buffer[5] = (char)(*valPtr >> 40);
    _buffer[6] = (char)(*valPtr >> 48);
    _buffer[7] = (char)(*valPtr >> 56);

    for (size_t i = 0; i < _buffer.size(); ++i)
    {
        _file << _buffer[i];
    }
}

void xe::BinaryWriter::Write(unsigned long value)
{
    uint64_t* valPtr = reinterpret_cast<uint64_t*>(&value);
    _buffer.clear();
    _buffer.resize(8);
    _buffer[0] = (char)*valPtr;
    _buffer[1] = (char)(*valPtr >> 8);
    _buffer[2] = (char)(*valPtr >> 16);
    _buffer[3] = (char)(*valPtr >> 24);
    _buffer[4] = (char)(*valPtr >> 32);
    _buffer[5] = (char)(*valPtr >> 40);
    _buffer[6] = (char)(*valPtr >> 48);
    _buffer[7] = (char)(*valPtr >> 56);

    for (size_t i = 0; i < _buffer.size(); ++i)
    {
        _file << _buffer[i];
    }
}

void xe::BinaryWriter::Write(float value)
{
    uint32_t* valPtr = reinterpret_cast<uint32_t*>(&value);
    _buffer.clear();
    _buffer.resize(4);
    _buffer[0] = (char)*valPtr;
    _buffer[1] = (char)(*valPtr >> 8);
    _buffer[2] = (char)(*valPtr >> 16);
    _buffer[3] = (char)(*valPtr >> 24);

    for (size_t i = 0; i < _buffer.size(); ++i)
    {
        _file << _buffer[i];
    }
}

void xe::BinaryWriter::Write(double value)
{
    uint64_t* valPtr = reinterpret_cast<uint64_t*>(&value);
    _buffer.clear();
    _buffer.resize(8);
    _buffer[0] = (char)*valPtr;
    _buffer[1] = (char)(*valPtr >> 8);
    _buffer[2] = (char)(*valPtr >> 16);
    _buffer[3] = (char)(*valPtr >> 24);
    _buffer[4] = (char)(*valPtr >> 32);
    _buffer[5] = (char)(*valPtr >> 40);
    _buffer[6] = (char)(*valPtr >> 48);
    _buffer[7] = (char)(*valPtr >> 56);

    for (size_t i = 0; i < _buffer.size(); ++i)
    {
        _file << _buffer[i];
    }
}

void xe::BinaryWriter::Write(std::string value)
{
    for (uint8_t byte : StrLen(value.length()))
    {
        _file << (char)byte;
    }

    for (char& c : value)
    {
        _file << c;
    }
}

void xe::BinaryWriter::Write(const char* value)
{
    Write(std::string(value));
}

std::vector<uint8_t> xe::BinaryWriter::StrLen(size_t length)
{
    std::vector<uint8_t> byteBuffer;
    size_t byteNum = 0;

    while (length > 0)
    {
        size_t valFactor = static_cast<size_t>(powf(128, ++byteNum));
        uint8_t currByte = length % valFactor;
        length /= valFactor;
        if (length > 0)
            currByte += 128;
        byteBuffer.push_back(currByte);
    }

    return byteBuffer;
}


// ==================================================================================

xe::BinaryReader::BinaryReader()
{
}

xe::BinaryReader::~BinaryReader()
{
    Close();
}

void xe::BinaryReader::Open(std::string file)
{
    _file.open(file, std::ios::binary);
    if (!_file.is_open())
    {
        std::ofstream tmpFile;
        tmpFile.open(file);
        tmpFile.close();

        _file.open(file, std::ios::binary);
    }
}

void xe::BinaryReader::Close()
{
    if (_file.is_open())
        _file.close();
}

bool xe::BinaryReader::IsOpen()
{
    return _file.is_open();
}

bool xe::BinaryReader::EndOfFile()
{
    return (_file.eof() || _file.peek() == -1);
}

char xe::BinaryReader::ReadChar()
{
    uint8_t val = 0;
    _buffer.clear();
    _buffer.resize(2);
    size_t length = 2;

    val = _file.get();

    return *(reinterpret_cast<char*>(&val));
}

short xe::BinaryReader::ReadShort()
{
    uint16_t val = 0;
    _buffer.clear();
    _buffer.resize(2);
    size_t length = 2;

    for (size_t i = 0; i < length; ++i)
    {
        val += _file.get() * powf(256, i);
    }

    return *(reinterpret_cast<short*>(&val));
}

unsigned short xe::BinaryReader::ReadUShort()
{
    uint16_t val = 0;
    _buffer.clear();
    _buffer.resize(2);
    size_t length = 2;

    for (size_t i = 0; i < length; ++i)
    {
        val += _file.get() * powf(256, i);
    }

    return *(reinterpret_cast<unsigned short*>(&val));
}

int xe::BinaryReader::ReadInt()
{
    uint32_t val = 0;
    _buffer.clear();
    _buffer.resize(4);
    size_t length = 4;

    for (size_t i = 0; i < length; ++i)
    {
        val += _file.get() * powf(256, i);
    }

    return *(reinterpret_cast<int*>(&val));
}

unsigned xe::BinaryReader::ReadUInt()
{
    uint32_t val = 0;
    _buffer.clear();
    _buffer.resize(4);
    size_t length = 4;

    for (size_t i = 0; i < length; ++i)
    {
        val += _file.get() * powf(256, i);
    }

    return *(reinterpret_cast<unsigned int*>(&val));
}

long xe::BinaryReader::ReadLong()
{
    uint64_t val = 0;
    _buffer.clear();
    _buffer.resize(8);
    size_t length = 8;

    for (size_t i = 0; i < length; ++i)
    {
        val += _file.get() * powf(256, i);
    }

    return *(reinterpret_cast<long*>(&val));
}

unsigned long xe::BinaryReader::ReadULong()
{
    uint64_t val = 0;
    _buffer.clear();
    _buffer.resize(8);
    size_t length = 8;

    for (size_t i = 0; i < length; ++i)
    {
        val += _file.get() * powf(256, i);
    }

    return *(reinterpret_cast<unsigned long*>(&val));
}

float xe::BinaryReader::ReadFloat()
{
    uint32_t val = 0;
    _buffer.clear();
    _buffer.resize(4);
    size_t length = 4;

    for (size_t i = 0; i < length; ++i)
    {
        val += _file.get() * powf(256, i);
    }

    return *(reinterpret_cast<float*>(&val));
}

double xe::BinaryReader::ReadDouble()
{
    uint64_t val = 0;
    _buffer.clear();
    _buffer.resize(8);
    size_t length = 8;

    for (size_t i = 0; i < length; ++i)
    {
        val += _file.get() * powf(256, i);
    }

    return *(reinterpret_cast<double*>(&val));
}

std::string xe::BinaryReader::ReadString()
{
    std::string outStr;
    size_t size = StrLen();

    for (size_t i = 0; i < size; ++i)
    {
        unsigned char c;
        c = _file.get();
        outStr.push_back(c);
    }

    return outStr;
}

size_t xe::BinaryReader::StrLen()
{
    size_t size = 0;
    uint8_t currByte = 0;
    size_t byteNum = 0;

    do
    {
        currByte = _file.get();
        size_t valFactor = static_cast<size_t>(powf(128, byteNum++));

        size += (currByte % 128) * valFactor;

    } while (currByte > 127);

    return size;
}
