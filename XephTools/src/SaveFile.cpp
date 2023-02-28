/*========================================================

 XephTools - SaveFile
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

#include "XephTools/SaveFile.h"
#include "XephTools/Assert.h"
#include "XephTools/Math.h"
#include <iostream>
#include <sstream>

#include "XephTools/AesBinaryIO.h"
#include "XephTools/BinaryIO.h"

xe::SaveFile::SaveFile(std::string fileName, FileFormat fileFormat, std::string key)
	: _fileName(fileName), _fileFormat(fileFormat), _key(key)
{
	Reload();
}


void xe::SaveFile::Save()
{
	switch (_fileFormat)
	{
	case FileFormat::Text:
		SaveText();
		break;
	case FileFormat::TextEncrypted:
		SaveTextEncrypted();
		break;
	case FileFormat::Binary:
		SaveBinary();
		break;
	case FileFormat::BinaryEncrypted:
		SaveBinaryEncrypted();
		break;
	}
}

void xe::SaveFile::Remove(std::string key)
{
	if (!_data.contains(key))
	{
		std::cout << "xe::SaveFile did not contain value with key: " << key << std::endl;
		return;
	}

	_data.erase(key);
}

void xe::SaveFile::Reload()
{
	_data.clear();
	switch (_fileFormat)
	{
	case FileFormat::Text:
		LoadText();
		break;
	case FileFormat::TextEncrypted:
		LoadTextEncrypted();
		break;
	case FileFormat::Binary:
		LoadBinary();
		break;
	case FileFormat::BinaryEncrypted:
		LoadBinaryEncrypted();
		break;
	}
}

int xe::SaveFile::GetInt(std::string key) const
{
	if (!_data.contains(key))
	{
		std::cout << "xe::SaveFile did not contain value with key: " << key << std::endl;
		return 0;
	}
	if (_data.at(key).type != Info::Type::String)
	{
		std::cout << "xe::SaveFile value with key: " << key << " is not of type int" << std::endl;
		return 0;
	}
	int ret = 0;
	try
	{
		ret = std::stoi(_data.at(key).data);
	}
	catch (std::exception e)
	{
		std::cout << "xe::SaveFile could not convert: " << _data.at(key).data << "to type int" << std::endl;
	}
	return ret;
}

float xe::SaveFile::GetFloat(std::string key) const
{
	if (!_data.contains(key))
	{
		std::cout << "xe::SaveFile did not contain value with key: " << key << std::endl;
		return 0.f;
	}
	if (_data.at(key).type != Info::Type::String)
	{
		std::cout << "xe::SaveFile value with key: " << key << " is not of type float" << std::endl;
		return 0.f;
	}

	float ret = 0.f;
	try
	{
		ret = std::stof(_data.at(key).data);
	}
	catch (std::exception e)
	{
		std::cout << "xe::SaveFile could not convert: " << _data.at(key).data << "to type float" << std::endl;
	}
	return ret;
}

bool xe::SaveFile::GetBool(std::string key) const
{
	if (!_data.contains(key))
	{
		std::cout << "xe::SaveFile did not contain value with key: " << key << std::endl;
		return false;
	}
	if (_data.at(key).type != Info::Type::Bool)
	{
		std::cout << "xe::SaveFile value with key: " << key << " is not of type string" << std::endl;
		return false;
	}
	std::string data = _data.at(key).data;
	return (data == "true" || data == "True" || data == "TRUE");
}

std::string xe::SaveFile::GetString(std::string key) const
{
	if (!_data.contains(key))
	{
		std::cout << "xe::SaveFile did not contain value with key: " << key << std::endl;
		return std::string();
	}
	if (_data.at(key).type != Info::Type::String)
	{
		std::cout << "xe::SaveFile value with key: " << key << " is not of type string" << std::endl;
		return std::string();
	}

	return _data.at(key).data;
}

xe::Vector2 xe::SaveFile::GetVector2(std::string key) const
{
	if (!_data.contains(key))
	{
		std::cout << "xe::SaveFile did not contain value with key: " << key << std::endl;
		return xe::Vector2();
	}
	if (_data.at(key).type != Info::Type::Vector2)
	{
		std::cout << "xe::SaveFile value with key: " << key << " is not of type string" << std::endl;
		return xe::Vector2();
	}
	std::stringstream dataStream; 
	std::string dataStr;
	xe::Vector2 data;

	try
	{
		dataStream << _data.at(key).data;
		std::getline(dataStream, dataStr, ' ');
		data.x = std::stof(dataStr);
		std::getline(dataStream, dataStr, ' ');
		data.y = std::stof(dataStr);
	}
	catch (std::exception e)
	{
		std::cout << "xe::SaveFile could not convert: " << _data.at(key).data << "to type Vector2" << std::endl;
	}
	return data;
}

void xe::SaveFile::SetInt(std::string key, const int& val)
{
	Info info;
	info.type = Info::Type::Int;
	info.data = std::to_string(val);
	_data.insert_or_assign(key, info);
}

void xe::SaveFile::SetFloat(std::string key, const float& val)
{
	Info info;
	info.type = Info::Type::Float;
	info.data = std::to_string(val);
	_data.insert_or_assign(key, info);
}

void xe::SaveFile::SetBool(std::string key, const bool& val)
{
	Info info;
	info.type = Info::Type::Bool;
	info.data = (val) ? "true" : "false";
	_data.insert_or_assign(key, info);
}

void xe::SaveFile::SetString(std::string key, const std::string& val)
{
	Info info;
	info.type = Info::Type::String;
	info.data = val;
	_data.insert_or_assign(key, info);
}

void xe::SaveFile::SetVector2(std::string key, const xe::Vector2& val)
{
	Info info;
	info.type = Info::Type::Vector2;
	info.data = std::to_string(val.x) + " " + std::to_string(val.y);
	_data.insert_or_assign(key, info);
}

void xe::SaveFile::SaveText()
{
	std::ofstream file;
	file.open(_fileName);
	XE_ASSERT(file.is_open(), "Could not open/create write file: " + _fileName);

	for (auto it = _data.begin(); it != _data.end(); ++it)
	{
		switch (it->second.type)
		{
		case Info::Type::Int:
			file << "[INT]";
			break;
		case Info::Type::Float:
			file << "[FLT]";
			break;
		case Info::Type::Bool:
			file << "[BOOL]";
			break;
		case Info::Type::String:
			file << "[STR]";
			break;
		case Info::Type::Vector2:
			file << "[VEC2]";
			break;
		}
		file << it->first << "=" << it->second.data << std::endl;
	}

	file.close();
}


void xe::SaveFile::SaveTextEncrypted()
{
	if (_key == "")
	{
		std::cout << "Key must be at assigned" << std::endl;
		return;
	}
	xe::AESWriter file(_key);
	file.Open(_fileName);

	for (auto it = _data.begin(); it != _data.end(); ++it)
	{
		switch (it->second.type)
		{
		case Info::Type::Int:
			file.Write("[INT]");
			break;
		case Info::Type::Float:
			file.Write("[FLT]");
			break;
		case Info::Type::Bool:
			file.Write("[BOOL]");
			break;
		case Info::Type::String:
			file.Write("[STR]");
			break;
		case Info::Type::Vector2:
			file.Write("[VEC2]");
			break;
		}
		file.WriteLine(it->first + "=" + it->second.data);
	}

	file.Close();
}

void xe::SaveFile::SaveBinary()
{
	xe::BinaryWriter file;
	file.Open(_fileName);

	for (auto it = _data.begin(); it != _data.end(); ++it)
	{
		switch (it->second.type)
		{
		case Info::Type::Int:
			file.Write("INT");
			break;
		case Info::Type::Float:
			file.Write("FLT");
			break;
		case Info::Type::Bool:
			file.Write("BOOL");
			break;
		case Info::Type::String:
			file.Write("STR");
			break;
		case Info::Type::Vector2:
			file.Write("VEC2");
			break;
		}
		file.Write(it->first);
		file.Write(it->second.data);
	}

	file.Close();
}

void xe::SaveFile::SaveBinaryEncrypted()
{
	if (_key == "")
	{
		std::cout << "Key must be at assigned" << std::endl;
		return;
	}
	xe::AESBinaryWriter file(_key);
	file.Open(_fileName);

	for (auto it = _data.begin(); it != _data.end(); ++it)
	{
		switch (it->second.type)
		{
		case Info::Type::Int:
			file.Write("INT");
			break;
		case Info::Type::Float:
			file.Write("FLT");
			break;
		case Info::Type::Bool:
			file.Write("BOOL");
			break;
		case Info::Type::String:
			file.Write("STR");
			break;
		case Info::Type::Vector2:
			file.Write("VEC2");
			break;
		}
		file.Write(it->first);
		file.Write(it->second.data);
	}

	file.Close();
}

void xe::SaveFile::LoadText()
{
	std::ifstream file;
	file.open(_fileName);
	if (!file.is_open())
	{
		std::cout << "Could not open file: " << _fileName << ". Creating new file..." << std::endl;
		Save();
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (line.length() > 0)
		{
			Info info;
			std::string key;
			size_t i = 0;
			size_t start = 0;
			for (; i < line.length(); ++i)
			{
				if (line[i] == ']')
				{
					++i;
					break;
				}
			}
			std::string type = line.substr(0, i);
			if (type == "[INT]") info.type = Info::Type::Int;
			else if (type == "[FLT]") info.type = Info::Type::Float;
			else if (line == "[BOOL]") info.type = Info::Type::Bool;
			else if (type == "[STR]") info.type = Info::Type::String;
			else if (type == "[VEC2]") info.type = Info::Type::Vector2;

			start = i;
			for (; i < line.length(); ++i)
			{
				if (line[i] == '=')
					break;
			}
			key = line.substr(start, i - start);
			info.data = line.substr(i + 1);

			_data.insert({ key, info });
			}
		}

	file.close();
}

void xe::SaveFile::LoadTextEncrypted()
{
	xe::AESReader file(_key);
	file.Open(_fileName);

	std::string line;
	while (file.ReadLine(line))
	{
		if (line.length() > 0)
		{
			Info info;
			std::string key;
			size_t i = 0;
			size_t start = 0;
			for (; i < line.length(); ++i)
			{
				if (line[i] == ']')
				{
					++i;
					break;
				}
			}
			std::string type = line.substr(0, i);
			if (type == "[INT]") info.type = Info::Type::Int;
			else if (type == "[FLT]") info.type = Info::Type::Float;
			else if (line == "[BOOL]") info.type = Info::Type::Bool;
			else if (type == "[STR]") info.type = Info::Type::String;
			else if (type == "[VEC2]") info.type = Info::Type::Vector2;

			start = i;
			for (; i < line.length(); ++i)
			{
				if (line[i] == '=')
					break;
			}
			key = line.substr(start, i - start);
			info.data = line.substr(i + 1);

			_data.insert({ key, info });
		}
	}

	file.Close();
}

void xe::SaveFile::LoadBinary()
{
	xe::BinaryReader file;
	file.Open(_fileName);
	if (!file.IsOpen())
	{
		std::cout << "Could not open file: " << _fileName << ". Creating new file..." << std::endl;
		Save();
		return;
	}

	std::string line;
	while (!file.EndOfFile())
	{
		line = file.ReadString();
		Info info;
		std::string key;
		if (line == "INT") info.type = Info::Type::Int;
		else if (line == "FLT") info.type = Info::Type::Float;
		else if (line == "BOOL") info.type = Info::Type::Bool;
		else if (line == "STR") info.type = Info::Type::String;
		else if (line == "VEC2") info.type = Info::Type::Vector2;

		key = file.ReadString();
		info.data = file.ReadString();
		_data.insert({ key, info});
	}

	file.Close();
}

void xe::SaveFile::LoadBinaryEncrypted()
{
	xe::AESBinaryReader file(_key);
	file.Open(_fileName);
	if (!file.IsOpen())
	{
		std::cout << "Could not open file: " << _fileName << ". Creating new file..." << std::endl;
		Save();
		return;
	}

	std::string line;
	while (!file.EndOfFile())
	{
		line = file.ReadString();
		Info info;
		std::string key;
		if (line == "INT") info.type = Info::Type::Int;
		else if (line == "FLT") info.type = Info::Type::Float;
		else if (line == "BOOL") info.type = Info::Type::Bool;
		else if (line == "STR") info.type = Info::Type::String;
		else if (line == "VEC2") info.type = Info::Type::Vector2;

		key = file.ReadString();
		info.data = file.ReadString();
		_data.insert({ key, info });
	}

	file.Close();
}
