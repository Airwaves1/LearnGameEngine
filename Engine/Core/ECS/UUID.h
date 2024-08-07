#ifndef UUID_H
#define UUID_H

/*
 * UUID（通用唯一识别码 
 *  UUID 通常表示为 16 字节( 128位 )的二进制数据，可以用 32 位十六进制字符串表示，
 *  例如 "123e4567-e89b-12d3-a456-426614174000"
 */

#include <string>
#include <array>

namespace Airwave
{

    class UUID
    {
    public:
        UUID();

        // 生成 UUID
        static UUID Generate();

        // 将 UUID 转换为字符串
        std::string ToString() const;

        // 比较两个 UUID 是否相等
        bool operator==(const UUID &other) const;
        bool operator!=(const UUID &other) const;
        bool operator<(const UUID &other) const;

    private:
        std::array<uint8_t, 16> m_UUID;

        static std::array<uint8_t, 16> GenerateUUID();
    };

}

#endif // !UUID_H