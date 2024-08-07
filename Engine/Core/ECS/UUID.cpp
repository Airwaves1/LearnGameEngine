#include "UUID.h"
#include <random>
#include <iomanip>
#include <sstream>

namespace Airwave
{
    UUID::UUID() : m_UUID(GenerateUUID()) {}

    UUID UUID::Generate()
    {
        return UUID();
    }

    std::string UUID::ToString() const
    {
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        for (size_t i = 0; i < m_UUID.size(); ++i)
        {
            if (i == 4 || i == 6 || i == 8 || i == 10)
                ss << '-';
            ss << std::setw(2) << static_cast<int>(m_UUID[i]);
        }
        return ss.str();
    }

    bool UUID::operator==(const UUID &other) const
    {
        return m_UUID == other.m_UUID;
    }

    bool UUID::operator!=(const UUID &other) const
    {
        return !(*this == other);
    }

    bool UUID::operator<(const UUID &other) const
    {
        return m_UUID < other.m_UUID;
    }

    std::array<uint8_t, 16> UUID::GenerateUUID()
    {
        std::array<uint8_t, 16> uuid;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 255);

        for (auto &byte : uuid)
            byte = static_cast<uint8_t>(dis(gen));

        // 设置版本号为 4（随机生成）
        uuid[6] = (uuid[6] & 0x0F) | 0x40;
        // 设置变种号为 1
        uuid[8] = (uuid[8] & 0x3F) | 0x80;

        return uuid;
    }
}
