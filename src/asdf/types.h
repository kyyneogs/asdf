#ifndef __ASDF_TYPES_H__
#define __ASDF_TYPES_H__

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>

namespace asdf {
enum class DataType : uint8_t {
    NA,
    UINT8,
    INT8,
    UINT16,
    INT16,
    UINT32,
    INT32,
    UINT64,
    INT64,
    FLOAT32,
    FLOAT64,
    STRING,
    OBJECT
};

constexpr std::array<const char *, 13> typeToStrMap = {
    "na",    "uint8", "int8",  "uint16", "int16",  "uint32",
    "int32", "uint64", "int64", "float32", "float64", "string", "object"};

union AlignBuff {
    uint8_t byte[8];
    uint16_t word[4];
    uint32_t dword[2];
    uint64_t qword;
};

struct ObjectMetadata {
    struct TypeMetadata {
        std::string name;
        ObjectMetadata* ref;
        uint32_t offset;
        uint32_t count;
        uint32_t size;
        DataType type;
        bool isArray;
    };

    std::string name;
    uint32_t size;
    uint32_t maxTypeNameSize;
    std::vector<TypeMetadata> typeMetaData;
    std::unordered_map<uint64_t, uint64_t> typeIDMap;
};
}  // namespace asdf

#endif  // __ASDF_TYPES_H__