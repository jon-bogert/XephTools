#ifndef __XE_BINARYREADER_H__
#define __XE_BINARYREADER_H__

#include <fstream>

namespace xe
{
    class BinaryReader
    {
    private:
        std::ifstream _file;

        uint8_t ReadByte()
        {
            uint8_t value;
            _file.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;
        }

    public:
        BinaryReader() = default;
        BinaryReader(const std::string& filePath)
            : _file(filePath, std::ios::binary)
        {
            if (!_file)
            {
                throw std::runtime_error("Failed to open file.");
            }
        }

        ~BinaryReader()
        {
            Close();
        }

        BinaryReader(const BinaryReader& other) = delete;
        BinaryReader(const BinaryReader&& other) = delete;
        BinaryReader& operator=(BinaryReader& other) = delete;
        BinaryReader& operator=(BinaryReader&& other) = delete;

        size_t ReadSize()
        {
            size_t count = 0;
            size_t shift = 0;
            uint8_t bytePart;

            do
            {
                if (shift == 5 * 7)
                {
                    throw std::runtime_error("Format exception: 7-bit encoded int is invalid.");
                }

                bytePart = ReadByte();
                count |= static_cast<size_t>((bytePart & 0x7F)) << shift;
                shift += 7;

            } while (bytePart >= 0x80);

            return count;
        }

        int8_t ReadInt8()
        {
            int8_t value;
            _file.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;
        }

        int16_t ReadInt16()
        {
            int16_t value;
            _file.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;
        }

        int32_t ReadInt32()
        {
            int32_t value;
            _file.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;
        }

        int64_t ReadInt64()
        {
            int64_t value;
            _file.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;
        }

        uint8_t ReadUInt8()
        {
            uint8_t value;
            _file.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;
        }

        uint16_t ReadUInt16()
        {
            uint16_t value;
            _file.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;
        }

        uint32_t ReadUInt32()
        {
            uint32_t value;
            _file.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;
        }

        uint64_t ReadUInt64()
        {
            uint64_t value;
            _file.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;
        }

        float ReadFloat()
        {
            float value;
            _file.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;
        }

        double ReadDouble()
        {
            double value;
            _file.read(reinterpret_cast<char*>(&value), sizeof(value));
            return value;
        }

        std::string ReadString()
        {
            size_t length = ReadSize();
            std::string value(length, '\0');
            _file.read(&value[0], length);
            return value;
        }

        bool IsOpen()
        {
            return _file.is_open();
        }

        void Open(const char* filename)
        {
            Close();
            _file.open(filename, std::ios::binary);
            if (!_file)
            {
                throw std::runtime_error("Failed to open file.");
            }
        }

        void Close()
        {
            if (_file.is_open())
                _file.close();
        }

        bool EoF()
        {
            return _file.eof();
        }

        int Peek()
        {
            return _file.peek();
        }
    };
}

#endif // __XE_BINARYREADER_H__