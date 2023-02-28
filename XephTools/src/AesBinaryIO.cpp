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

#include "XephTools/AesBinaryIO.h"

xe::AESBinaryWriter::AESBinaryWriter(std::vector<uint8_t> key)
    : _file(AESWriter(key))
{
}

xe::AESBinaryWriter::AESBinaryWriter(std::string key)
    : _file(AESWriter(key))
{
}

xe::AESBinaryWriter::~AESBinaryWriter()
{
    Close();
}

void xe::AESBinaryWriter::Open(std::string file)
{
    _file.Open(file);
}

void xe::AESBinaryWriter::Close()
{
    if (_file.IsOpen())
        _file.Close();
}

bool xe::AESBinaryWriter::IsOpen()
{
    return _file.IsOpen();
}

void xe::AESBinaryWriter::Write(char value)
{
    _file.Write(value);
}

void xe::AESBinaryWriter::Write(short value)
{
    uint16_t* valPtr = reinterpret_cast<uint16_t*>(&value);
    _buffer.clear();
    _buffer.resize(2);
    _buffer[0] = (char)*valPtr;
    _buffer[1] = (char)(*valPtr >> 8);

    for (size_t i = 0; i < _buffer.size(); ++i)
    {
        _file.Write(_buffer[i]);
    }
}

void xe::AESBinaryWriter::Write(unsigned short value)
{
    uint16_t* valPtr = reinterpret_cast<uint16_t*>(&value);
    _buffer.clear();
    _buffer.resize(2);
    _buffer[0] = (char)*valPtr;
    _buffer[1] = (char)(*valPtr >> 8);

    for (size_t i = 0; i < _buffer.size(); ++i)
    {
        _file.Write(_buffer[i]);
    }
}

void xe::AESBinaryWriter::Write(int value)
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
        _file.Write(_buffer[i]);
    }
}

void xe::AESBinaryWriter::Write(unsigned value)
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
        _file.Write(_buffer[i]);
    }
}

void xe::AESBinaryWriter::Write(long value)
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
        _file.Write(_buffer[i]);
    }
}

void xe::AESBinaryWriter::Write(unsigned long value)
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
        _file.Write(_buffer[i]);
    }
}

void xe::AESBinaryWriter::Write(float value)
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
        _file.Write(_buffer[i]);
    }
}

void xe::AESBinaryWriter::Write(double value)
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
        _file.Write(_buffer[i]);
    }
}

void xe::AESBinaryWriter::Write(std::string value)
{
    for (uint8_t byte : StrLen(value.length()))
    {
        _file.Write((char)byte);
    }

    for (char& c : value)
    {
        _file.Write(c);
    }
}

void xe::AESBinaryWriter::Write(const char* value)
{
    Write(std::string(value));
}

std::vector<uint8_t> xe::AESBinaryWriter::StrLen(size_t length)
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

xe::AESBinaryReader::AESBinaryReader(std::vector<uint8_t> key)
    : _file(AESReader(key))
{
}

xe::AESBinaryReader::AESBinaryReader(std::string key)
    : _file(AESReader(key))
{
}

xe::AESBinaryReader::~AESBinaryReader()
{
    Close();
}

void xe::AESBinaryReader::Open(std::string file)
{
    _file.Open(file, true);
    if (!_file.IsOpen())
    {
        std::ofstream tmpFile;
        tmpFile.open(file);
        tmpFile.close();

        _file.Open(file, true);
    }
}

void xe::AESBinaryReader::Close()
{
    if (_file.IsOpen())
        _file.Close();
}

bool xe::AESBinaryReader::IsOpen()
{
    return _file.IsOpen();
}

bool xe::AESBinaryReader::EndOfFile()
{
    return _file.EndOfFile();
}

char xe::AESBinaryReader::ReadChar()
{
    uint8_t val = 0;
    _buffer.clear();
    _buffer.resize(2);
    size_t length = 2;

    _file.ReadNext(val);

    return *(reinterpret_cast<char*>(&val));
}

short xe::AESBinaryReader::ReadShort()
{
    uint16_t val = 0;
    _buffer.clear();
    _buffer.resize(2);
    size_t length = 2;

    for (size_t i = 0; i < length; ++i)
    {
        unsigned char currVal;
        _file.ReadNext(currVal);
        val += currVal * powf(256, i);
    }

    return *(reinterpret_cast<short*>(&val));
}

unsigned short xe::AESBinaryReader::ReadUShort()
{
    uint16_t val = 0;
    _buffer.clear();
    _buffer.resize(2);
    size_t length = 2;

    for (size_t i = 0; i < length; ++i)
    {
        unsigned char currVal;
        _file.ReadNext(currVal);
        val += currVal * powf(256, i);
    }

    return *(reinterpret_cast<unsigned short*>(&val));
}

int xe::AESBinaryReader::ReadInt()
{
    uint32_t val = 0;
    _buffer.clear();
    _buffer.resize(4);
    size_t length = 4;

    for (size_t i = 0; i < length; ++i)
    {
        unsigned char currVal;
        _file.ReadNext(currVal);
        val += currVal * powf(256, i);
    }

    return *(reinterpret_cast<int*>(&val));
}

unsigned xe::AESBinaryReader::ReadUInt()
{
    uint32_t val = 0;
    _buffer.clear();
    _buffer.resize(4);
    size_t length = 4;

    for (size_t i = 0; i < length; ++i)
    {
        unsigned char currVal;
        _file.ReadNext(currVal);
        val += currVal * powf(256, i);
    }

    return *(reinterpret_cast<unsigned int*>(&val));
}

long xe::AESBinaryReader::ReadLong()
{
    uint64_t val = 0;
    _buffer.clear();
    _buffer.resize(8);
    size_t length = 8;

    for (size_t i = 0; i < length; ++i)
    {
        unsigned char currVal;
        _file.ReadNext(currVal);
        val += currVal * powf(256, i);
    }

    return *(reinterpret_cast<long*>(&val));
}

unsigned long xe::AESBinaryReader::ReadULong()
{
    uint64_t val = 0;
    _buffer.clear();
    _buffer.resize(8);
    size_t length = 8;

    for (size_t i = 0; i < length; ++i)
    {
        unsigned char currVal;
        _file.ReadNext(currVal);
        val += currVal * powf(256, i);
    }

    return *(reinterpret_cast<unsigned long*>(&val));
}

float xe::AESBinaryReader::ReadFloat()
{
    uint32_t val = 0;
    _buffer.clear();
    _buffer.resize(4);
    size_t length = 4;

    for (size_t i = 0; i < length; ++i)
    {
        unsigned char currVal;
        _file.ReadNext(currVal);
        val += currVal * powf(256, i);
    }

    return *(reinterpret_cast<float*>(&val));
}

double xe::AESBinaryReader::ReadDouble()
{
    uint64_t val = 0;
    _buffer.clear();
    _buffer.resize(8);
    size_t length = 8;

    for (size_t i = 0; i < length; ++i)
    {
        unsigned char currVal;
        _file.ReadNext(currVal);
        val += currVal * powf(256, i);
    }

    return *(reinterpret_cast<double*>(&val));
}

std::string xe::AESBinaryReader::ReadString()
{
    std::string outStr;
    size_t size = StrLen();

    for (size_t i = 0; i < size; ++i)
    {
        unsigned char c;
        _file.ReadNext(c);
        outStr.push_back(c);
    }

    return outStr;
}

size_t xe::AESBinaryReader::StrLen()
{
    size_t size = 0;
    unsigned char currByte = 0;
    size_t byteNum = 0;

    do
    {
        _file.ReadNext(currByte);
        size_t valFactor = static_cast<size_t>(powf(128, byteNum++));

        size += (currByte % 128) * valFactor;

    } while (currByte > 127);

    return size;
}
