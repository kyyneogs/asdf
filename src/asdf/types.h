#ifndef __ASDF_TYPES_H__
#define __ASDF_TYPES_H__

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace asdf {
enum class DataType : uint8_t {
    NA,
    BOOL,
    UINT8,
    INT8,
    UINT16,
    INT16,
    UINT32,
    INT32,
    UINT64,
    INT64,
    FLOAT,
    DOUBLE,
    STRING,
    OBJECT
};

static const std::array<const std::string, 14> typeToStrMap = {
    "na",    "bool",   "uint8", "int8",  "uint16", "int16",  "uint32",
    "int32", "uint64", "int64", "float", "double", "string", "object"};

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
    std::vector<TypeMetadata> typeMetaData;
    std::unordered_map<uint64_t, uint64_t> typeIDMap;
};
}  // namespace asdf

#endif  // __ASDF_TYPES_H__