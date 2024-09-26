/*========================================================

 XephTools - XESample
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

#ifndef XE_SAMPLE_H
#define XE_SAMPLE_H

#include <algorithm>
#include <ostream>
#include <cstdint>
#include <stdexcept>

#ifndef UINT24_MAX
#define UINT24_MAX 16777215u
#endif //!UINT24_MAX

#ifndef UINT24_MIN
#define UINT24_MIN 0u
#endif //!UINT24_MIN

#ifndef INT24_MAX
#define INT24_MAX 8388607
#endif //!INT24_MAX

#ifndef INT24_MIN
#define INT24_MIN -8388608
#endif //!INT24_MIN

namespace xe
{
    struct Sample8
    {
        int8_t data;

        constexpr Sample8(const int8_t value = 0) : data(value) {}
        constexpr Sample8(const Sample8& other) : data(other.data) {}
        constexpr Sample8(const float& value) : data(static_cast<int8_t>(value* INT8_MAX)) {}
        constexpr Sample8(const int& value) : data(static_cast<int8_t>(value)) {}

        Sample8& operator=(const Sample8& other)
        {
            data = other.data;
            return *this;
        }

        Sample8& operator=(const int8_t value)
        {
            data = value;
            return *this;
        }

        Sample8& operator=(const float value)
        {
            data = static_cast<int8_t>(value * INT8_MAX);
            return *this;
        }

        Sample8 operator+(const Sample8& other) const
        {
            return Sample8(data + other.data);
        }

        Sample8 operator-(const Sample8& other) const
        {
            return Sample8(data - other.data);
        }

        Sample8 operator*(const Sample8& other) const
        {
            return Sample8(data * other.data / INT8_MAX);
        }

        Sample8 operator/(const Sample8& other) const
        {
            if (other.data == 0)
                throw std::runtime_error("Division by zero");

            return Sample8(data / other.data * INT8_MAX);
        }

        Sample8& operator+=(const Sample8& other)
        {
            data += other.data;
            return *this;
        }

        Sample8& operator-=(const Sample8& other)
        {
            data -= other.data;
            return *this;
        }

        Sample8& operator*=(const Sample8& other)
        {
            *this = *this * other;
            return *this;
        }

        Sample8& operator/=(const Sample8& other)
        {
            *this = *this / other;
            return *this;
        }

        bool operator==(const Sample8& other) const
        {
            return data == other.data;
        }

        bool operator!=(const Sample8& other) const
        {
            return data != other.data;
        }

        bool operator<(const Sample8& other) const
        {
            return data < other.data;
        }

        bool operator<=(const Sample8& other) const
        {
            return data <= other.data;
        }

        bool operator>(const Sample8& other) const
        {
            return data > other.data;
        }

        bool operator>=(const Sample8& other) const
        {
            return data >= other.data;
        }

        float ToFloat32() const
        {
            return static_cast<float>(data) / INT8_MAX;
        }

        friend std::ostream& operator<<(std::ostream& os, const Sample8& s)
        {
            os << s.ToFloat32();
            return os;
        }

    };

    struct SampleU8
    {
        uint8_t data;

        constexpr SampleU8(const uint8_t value = 0) : data(value) {}
        constexpr SampleU8(const SampleU8& other) : data(other.data) {}
        constexpr SampleU8(const float& value) : data(static_cast<uint8_t>(value* UINT8_MAX)) {}
        constexpr SampleU8(const int& value) : data(static_cast<uint8_t>(value)) {}

        SampleU8& operator=(const SampleU8& other)
        {
            data = other.data;
            return *this;
        }

        SampleU8& operator=(const uint8_t value)
        {
            data = value;
            return *this;
        }

        SampleU8& operator=(const float value)
        {
            data = static_cast<uint8_t>(value * UINT8_MAX);
            return *this;
        }

        SampleU8 operator+(const SampleU8& other) const
        {
            return SampleU8(data + other.data);
        }

        SampleU8 operator-(const SampleU8& other) const
        {
            return SampleU8(data - other.data);
        }

        SampleU8 operator*(const SampleU8& other) const
        {
            return SampleU8(data * other.data / UINT8_MAX);
        }

        SampleU8 operator/(const SampleU8& other) const
        {
            if (other.data == 0)
                throw std::runtime_error("Division by zero");

            return SampleU8(data / other.data * UINT8_MAX);
        }

        SampleU8& operator+=(const SampleU8& other)
        {
            data += other.data;
            return *this;
        }

        SampleU8& operator-=(const SampleU8& other)
        {
            data -= other.data;
            return *this;
        }

        SampleU8& operator*=(const SampleU8& other)
        {
            *this = *this * other;
            return *this;
        }

        SampleU8& operator/=(const SampleU8& other)
        {
            *this = *this / other;
            return *this;
        }

        bool operator==(const SampleU8& other) const
        {
            return data == other.data;
        }

        bool operator!=(const SampleU8& other) const
        {
            return data != other.data;
        }

        bool operator<(const SampleU8& other) const
        {
            return data < other.data;
        }

        bool operator<=(const SampleU8& other) const
        {
            return data <= other.data;
        }

        bool operator>(const SampleU8& other) const
        {
            return data > other.data;
        }

        bool operator>=(const SampleU8& other) const
        {
            return data >= other.data;
        }

        float ToFloat32() const
        {
            return static_cast<float>(data) / UINT8_MAX;
        }

        friend std::ostream& operator<<(std::ostream& os, const SampleU8& s)
        {
            os << s.ToFloat32();
            return os;
        }

    };

    struct Sample16
    {
        int16_t data;

        constexpr Sample16(const int16_t value = 0) : data(value) {}
        constexpr Sample16(const Sample16& other) : data(other.data) {}
        constexpr Sample16(const float& value) : data(static_cast<int16_t>(value* INT16_MAX)) {}
        constexpr Sample16(const int& value) : data(static_cast<int16_t>(value)) {}

        Sample16& operator=(const Sample16& other)
        {
            data = other.data;
            return *this;
        }

        Sample16& operator=(const int16_t value)
        {
            data = value;
            return *this;
        }

        Sample16& operator=(const float value)
        {
            data = static_cast<int16_t>(value * INT16_MAX);
            return *this;
        }

        Sample16 operator+(const Sample16& other) const
        {
            return Sample16(data + other.data);
        }

        Sample16 operator-(const Sample16& other) const
        {
            return Sample16(data - other.data);
        }

        Sample16 operator*(const Sample16& other) const
        {
            return Sample16(data * other.data / INT16_MAX);
        }

        Sample16 operator/(const Sample16& other) const
        {
            if (other.data == 0)
                throw std::runtime_error("Division by zero");

            return Sample16(data / other.data * INT16_MAX);
        }

        Sample16& operator+=(const Sample16& other)
        {
            data += other.data;
            return *this;
        }

        Sample16& operator-=(const Sample16& other)
        {
            data -= other.data;
            return *this;
        }

        Sample16& operator*=(const Sample16& other)
        {
            *this = *this * other;
            return *this;
        }

        Sample16& operator/=(const Sample16& other)
        {
            *this = *this / other;
            return *this;
        }

        bool operator==(const Sample16& other) const
        {
            return data == other.data;
        }

        bool operator!=(const Sample16& other) const
        {
            return data != other.data;
        }

        bool operator<(const Sample16& other) const
        {
            return data < other.data;
        }

        bool operator<=(const Sample16& other) const
        {
            return data <= other.data;
        }

        bool operator>(const Sample16& other) const
        {
            return data > other.data;
        }

        bool operator>=(const Sample16& other) const
        {
            return data >= other.data;
        }

        float ToFloat32() const
        {
            return static_cast<float>(data) / INT16_MAX;
        }

        friend std::ostream& operator<<(std::ostream& os, const Sample16& s)
        {
            os << s.ToFloat32();
            return os;
        }

    };

    struct SampleU16
    {
        uint16_t data;

        constexpr SampleU16(const uint16_t value = 0) : data(value) {}
        constexpr SampleU16(const SampleU16& other) : data(other.data) {}
        constexpr SampleU16(const float& value) : data(static_cast<uint16_t>(value* UINT16_MAX)) {}
        constexpr SampleU16(const int& value) : data(static_cast<uint16_t>(value)) {}

        SampleU16& operator=(const SampleU16& other)
        {
            data = other.data;
            return *this;
        }

        SampleU16& operator=(const uint16_t value)
        {
            data = value;
            return *this;
        }

        SampleU16& operator=(const float value)
        {
            data = static_cast<uint16_t>(value * UINT16_MAX);
            return *this;
        }

        SampleU16 operator+(const SampleU16& other) const
        {
            return SampleU16(data + other.data);
        }

        SampleU16 operator-(const SampleU16& other) const
        {
            return SampleU16(data - other.data);
        }

        SampleU16 operator*(const SampleU16& other) const
        {
            return SampleU16(data * other.data / UINT16_MAX);
        }

        SampleU16 operator/(const SampleU16& other) const
        {
            if (other.data == 0)
                throw std::runtime_error("Division by zero");

            return SampleU16(data / other.data * UINT16_MAX);
        }

        SampleU16& operator+=(const SampleU16& other)
        {
            data += other.data;
            return *this;
        }

        SampleU16& operator-=(const SampleU16& other)
        {
            data -= other.data;
            return *this;
        }

        SampleU16& operator*=(const SampleU16& other)
        {
            *this = *this * other;
            return *this;
        }

        SampleU16& operator/=(const SampleU16& other)
        {
            *this = *this / other;
            return *this;
        }

        bool operator==(const SampleU16& other) const
        {
            return data == other.data;
        }

        bool operator!=(const SampleU16& other) const
        {
            return data != other.data;
        }

        bool operator<(const SampleU16& other) const
        {
            return data < other.data;
        }

        bool operator<=(const SampleU16& other) const
        {
            return data <= other.data;
        }

        bool operator>(const SampleU16& other) const
        {
            return data > other.data;
        }

        bool operator>=(const SampleU16& other) const
        {
            return data >= other.data;
        }

        float ToFloat32() const
        {
            return static_cast<float>(data) / UINT16_MAX;
        }

        friend std::ostream& operator<<(std::ostream& os, const SampleU16& s)
        {
            os << s.ToFloat32();
            return os;
        }

    };

    // NOTE: Sample24 stores data withing 32-bit container; 32-bit sign bits should be maintained
    struct Sample24
    {
        int32_t data;

        constexpr Sample24(const int32_t value = 0) : data(value) {}
        constexpr Sample24(const Sample24& other) : data(other.data) {}
        constexpr Sample24(const float& value) : data(static_cast<int32_t>(value* INT24_MAX)) {}

        Sample24& operator=(const Sample24& other)
        {
            data = other.data;
            return *this;
        }

        Sample24& operator=(const int32_t value)
        {
            data = value;
            ClampValue();
            return *this;
        }

        Sample24& operator=(const float value)
        {
            data = static_cast<int32_t>(value * INT24_MAX);
            ClampValue();
            return *this;
        }

        Sample24 operator+(const Sample24& other) const
        {
            return Sample24(ClampValue(data + other.data));
        }

        Sample24 operator-(const Sample24& other) const
        {
            return Sample24(ClampValue(data - other.data));
        }

        Sample24 operator*(const Sample24& other) const
        {
            return Sample24(ClampValue(data * other.data / INT24_MAX));
        }

        Sample24 operator/(const Sample24& other) const
        {
            if (other.data == 0)
                throw std::runtime_error("Division by zero");

            return Sample24(ClampValue(data / other.data * INT24_MAX));
        }

        Sample24& operator+=(const Sample24& other)
        {
            data += other.data;
            ClampValue();
            return *this;
        }

        Sample24& operator-=(const Sample24& other)
        {
            data -= other.data;
            ClampValue();
            return *this;
        }

        Sample24& operator*=(const Sample24& other)
        {
            *this = *this * other;
            return *this;
        }

        Sample24& operator/=(const Sample24& other)
        {
            *this = *this / other;
            return *this;
        }

        bool operator==(const Sample24& other) const
        {
            return data == other.data;
        }

        bool operator!=(const Sample24& other) const
        {
            return data != other.data;
        }

        bool operator<(const Sample24& other) const
        {
            return data < other.data;
        }

        bool operator<=(const Sample24& other) const
        {
            return data <= other.data;
        }

        bool operator>(const Sample24& other) const
        {
            return data > other.data;
        }

        bool operator>=(const Sample24& other) const
        {
            return data >= other.data;
        }

        float ToFloat32() const
        {
            return static_cast<float>(data) / INT24_MAX;
        }

        friend std::ostream& operator<<(std::ostream& os, const Sample24& s)
        {
            os << s.ToFloat32();
            return os;
        }

    private:
        void ClampValue()
        {
            data = std::max(std::min(data, INT24_MAX), INT24_MIN);
        }

        static int32_t ClampValue(int32_t value)
        {
            return std::max(std::min(value, INT24_MAX), INT24_MIN);
        }
    };

    // NOTE: SampleU24 stores data withing 32-bit container
    struct SampleU24
    {
        uint32_t data;

        constexpr SampleU24(const uint32_t value = 0) : data(value) {}
        constexpr SampleU24(const SampleU24& other) : data(other.data) {}
        constexpr SampleU24(const float& value) : data(static_cast<uint32_t>(value* UINT24_MAX)) {}

        SampleU24& operator=(const SampleU24& other)
        {
            data = other.data;
            return *this;
        }

        SampleU24& operator=(const uint32_t value)
        {
            data = value;
            ClampValue();
            return *this;
        }

        SampleU24& operator=(const float value)
        {
            data = static_cast<uint32_t>(value * UINT24_MAX);
            ClampValue();
            return *this;
        }

        SampleU24 operator+(const SampleU24& other) const
        {
            return SampleU24(ClampValue(data + other.data));
        }

        SampleU24 operator-(const SampleU24& other) const
        {
            return SampleU24(ClampValue(data - other.data));
        }

        SampleU24 operator*(const SampleU24& other) const
        {
            return SampleU24(ClampValue(data * other.data / UINT24_MAX));
        }

        SampleU24 operator/(const SampleU24& other) const
        {
            if (other.data == 0)
                throw std::runtime_error("Division by zero");

            return SampleU24(ClampValue(data / other.data * UINT24_MAX));
        }

        SampleU24& operator+=(const SampleU24& other)
        {
            data += other.data;
            ClampValue();
            return *this;
        }

        SampleU24& operator-=(const SampleU24& other)
        {
            data -= other.data;
            ClampValue();
            return *this;
        }

        SampleU24& operator*=(const SampleU24& other)
        {
            *this = *this * other;
            return *this;
        }

        SampleU24& operator/=(const SampleU24& other)
        {
            *this = *this / other;
            return *this;
        }

        bool operator==(const SampleU24& other) const
        {
            return data == other.data;
        }

        bool operator!=(const SampleU24& other) const
        {
            return data != other.data;
        }

        bool operator<(const SampleU24& other) const
        {
            return data < other.data;
        }

        bool operator<=(const SampleU24& other) const
        {
            return data <= other.data;
        }

        bool operator>(const SampleU24& other) const
        {
            return data > other.data;
        }

        bool operator>=(const SampleU24& other) const
        {
            return data >= other.data;
        }

        float ToFloat32() const
        {
            return static_cast<float>(data) / UINT24_MAX;
        }

        friend std::ostream& operator<<(std::ostream& os, const SampleU24& s)
        {
            os << s.ToFloat32();
            return os;
        }

    private:
        void ClampValue()
        {
            data = std::max(std::min(data, UINT24_MAX), UINT24_MIN);
        }

        static uint32_t ClampValue(uint32_t value)
        {
            return std::max(std::min(value, UINT24_MAX), UINT24_MIN);
        }
    };

    //Managers and manipipulates a void* of 24-bit signed data. DOES NOT OWN DATA;
    class BufferManager24
    {
    public:
        BufferManager24(void* buffer, size_t sizeItems) : m_buffer(static_cast<uint8_t*>(buffer)), m_size(sizeItems * 3) {}

        Sample24 GetSample(size_t index) const
        {
            if (index * 3 >= m_size)
            {
                throw std::out_of_range("Index out of range");
            }

            int32_t sample = 0;
            sample |= m_buffer[index * 3] << 16;
            sample |= m_buffer[index * 3 + 1] << 8;
            sample |= m_buffer[index * 3 + 2];

            if (sample & 0x800000)
            {
                sample |= 0xFF000000;
            }

            return Sample24(sample);
        }

        void SetSample(size_t index, Sample24 sample)
        {
            if (index * 3 >= m_size)
            {
                throw std::out_of_range("Index out of range");
            }

            m_buffer[index * 3] = (sample.data >> 16) & 0xFF;
            m_buffer[index * 3 + 1] = (sample.data >> 8) & 0xFF;
            m_buffer[index * 3 + 2] = sample.data & 0xFF;
        }

        size_t GetLength() const { return m_size / 3; }
        size_t GetSizeBytes() const { return m_size; }

    private:
        uint8_t* m_buffer;
        size_t m_size;
    };

    //Managers and manipipulates a void* of 24-bit unsigned data. DOES NOT OWN DATA;
    class BufferManagerU24
    {
    public:
        BufferManagerU24(void* buffer, size_t sizeItems) : m_buffer(static_cast<uint8_t*>(buffer)), m_size(sizeItems * 3) {}

        SampleU24 GetSample(size_t index) const
        {
            if (index * 3 >= m_size)
            {
                throw std::out_of_range("Index out of range");
            }

            uint32_t sample = 0;
            sample |= m_buffer[index * 3] << 16;
            sample |= m_buffer[index * 3 + 1] << 8;
            sample |= m_buffer[index * 3 + 2];

            return SampleU24(sample);
        }

        void SetSample(size_t index, SampleU24 sample)
        {
            if (index * 3 >= m_size)
            {
                throw std::out_of_range("Index out of range");
            }

            m_buffer[index * 3] = (sample.data >> 16) & 0xFF;
            m_buffer[index * 3 + 1] = (sample.data >> 8) & 0xFF;
            m_buffer[index * 3 + 2] = sample.data & 0xFF;
        }

        size_t GetLength() const { return m_size / 3; }
        size_t GetSizeBytes() const { return m_size; }

    private:
        uint8_t* m_buffer;
        size_t m_size;
    };
}

#endif //!XE_SAMPLE_H