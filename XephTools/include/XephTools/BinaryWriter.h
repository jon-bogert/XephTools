#ifndef __XE_BINARYWRITER_H__
#define __XE_BINARYWRITER_H__

#include <fstream>

namespace xe
{
    class BinaryWriter
    {
    private:
        std::ofstream _file;

        void WriteByte(uint8_t value)
        {
            _file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

    public:
        BinaryWriter() = default;
        BinaryWriter(const std::string& filePath)
            : _file(filePath, std::ios::binary) {
            if (!_file)
            {
                throw std::runtime_error("Failed to open file.");
            }
        }

        ~BinaryWriter() {
            Close();
        }

        BinaryWriter(const BinaryWriter& other) = delete;
        BinaryWriter(const BinaryWriter&& other) = delete;
        BinaryWriter& operator=(BinaryWriter& other) = delete;
        BinaryWriter& operator=(BinaryWriter&& other) = delete;

        void WriteSize(size_t value)
        {
            size_t unsignedValue = static_cast<size_t>(value);
            while (unsignedValue >= 0x80)
            {
                WriteByte(static_cast<uint8_t>(unsignedValue | 0x80));
                unsignedValue >>= 7;
            }
            WriteByte(static_cast<uint8_t>(unsignedValue));
        }

        void Write(const int8_t value)
        {
            _file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        void Write(const int16_t value)
        {
            _file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        void Write(const int32_t value)
        {
            _file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        void Write(const int64_t value)
        {
            _file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        void Write(const uint8_t value)
        {
            _file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        void Write(const uint16_t value)
        {
            _file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        void Write(const uint32_t value)
        {
            _file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        void Write(const uint64_t value)
        {
            _file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        void Write(const float value)
        {
            _file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        void Write(const double value)
        {
            _file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        void Write(const char* value, size_t size) {
            WriteSize(size);
            _file.write(value, size);
        }

        void Write(const std::string& value) {
            WriteSize(value.size());
            _file.write(value.c_str(), value.size());
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
            {
                _file.close();
            }
        }
    };
}

#endif // __XE_BINARYWRITER_H__