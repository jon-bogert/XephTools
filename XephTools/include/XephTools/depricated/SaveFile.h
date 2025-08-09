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

#ifndef XE_SAVE_FILE_H
#define XE_SAVE_FILE_H

#include <fstream>
#include <string>
#include <unordered_map>

#include "XephTools/AesIO.h"

namespace xe
{
	enum class FileFormat { Text, Binary, Json, TextEncrypted, BinaryEncrypted };

	struct Vector2;
	class SaveFile
	{
		struct Info
		{
			enum class Type { Int, Float, Bool, String, Vector2};
			std::string data;
			Type type;
		};

		std::string _fileName = "";
		std::unordered_map<std::string, Info> _data;
		FileFormat _fileFormat = FileFormat::Text;
		std::string _key = "";

	public:
		SaveFile(std::string fileName, FileFormat fileFormat = FileFormat::Text, std::string key = "");

		void Save();
		void Remove(std::string key);
		void Reload();

		//Getters
		int GetInt(std::string key) const;
		float GetFloat(std::string key) const;
		bool GetBool(std::string key) const;
		std::string GetString(std::string key) const;
		xe::Vector2 GetVector2(std::string key) const;

		//Setters
		void SetInt(std::string key, const int& val);
		void SetFloat(std::string key, const float& val);
		void SetBool(std::string key, const bool& val);
		void SetString(std::string key, const std::string& val);
		void SetVector2(std::string key, const xe::Vector2& val);

	private:
		void SaveText();
		void SaveTextEncrypted();
		void SaveBinary();
		void SaveBinaryEncrypted();
		void SaveJson();

		void LoadText();
		void LoadTextEncrypted();
		void LoadBinary();
		void LoadBinaryEncrypted();
		void LoadJson();
	};
}
#endif // XE_SAVE_FILE_H