#include "asdf/object.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "asdf/types.h"
#include "include/constexpr_xxhash3.hpp"

using constexpr_xxh3::XXH3_64bits_const;

static uint64_t unusedU64;

namespace asdf {
void fatalErrorException() {
#ifdef ASDF_USE_ABORT
    abort();
#endif
}

static ObjectMetadata exceptionMetaData = {};

inline std::string dtypeToString(const DataType &type) {
    return typeToStrMap[static_cast<int>(type)];
}

Object::Object(ObjectMetadata &schema)
    : isAlive_(isAncestor_), metadata_(schema), anchestor_(*this) {
    uint64_t buffSize = this->metadata_.size / sizeof(AlignBuff);
    if (this->metadata_.size % sizeof(AlignBuff) > 0) buffSize += 1;

    isAncestor_ = true;
    buff_ = new AlignBuff[buffSize];
    memset(buff_, 0, sizeof(AlignBuff) * buffSize);
    size_ = schema.size;
    offset_ = 0;
    id_ = 0;
}

Object::Object(const Object &other, ObjectMetadata &schema, uint64_t offset,
               uint64_t size)
    : isAlive_(other.isAlive_),
      buff_(other.buff_),
      metadata_(schema),
      anchestor_(other.anchestor_) {
    isAncestor_ = false;
    offset_ = offset;
    size_ = size;
    buff_ = other.buff_;
    id_ = 0;
}

Object::~Object() {
    if (isAncestor_) {
        isAncestor_ = false;
    }
}

uint8_t Object::getU8(std::string_view name) const {
    uint8_t value = 0;
    uint64_t offset;
    if (validate(name, DataType::UINT8, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(&value, buff_->byte + offset, sizeof(value));
    }

    return value;
}

uint16_t Object::getU16(std::string_view name) const {
    uint16_t value = 0;
    uint64_t offset;
    if (validate(name, DataType::UINT16, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(&value, buff_->byte + offset, sizeof(value));
    }

    return value;
}

uint32_t Object::getU32(std::string_view name) const {
    uint32_t value = 0;
    uint64_t offset;
    if (validate(name, DataType::UINT32, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(&value, buff_->byte + offset, sizeof(value));
    }

    return value;
}

uint64_t Object::getU64(std::string_view name) const {
    uint64_t value = 0;
    uint64_t offset;
    if (validate(name, DataType::UINT64, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(&value, buff_->byte + offset, sizeof(value));
    }

    return value;
}

int8_t Object::getI8(std::string_view name) const {
    int8_t value = 0;
    uint64_t offset;
    if (validate(name, DataType::INT8, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(&value, buff_->byte + offset, sizeof(value));
    }

    return value;
}

int16_t Object::getI16(std::string_view name) const {
    int16_t value = 0;
    uint64_t offset;
    if (validate(name, DataType::INT16, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(&value, buff_->byte + offset, sizeof(value));
    }

    return value;
}

int32_t Object::getI32(std::string_view name) const {
    int32_t value = 0;
    uint64_t offset;
    if (validate(name, DataType::INT32, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(&value, buff_->byte + offset, sizeof(value));
    }

    return value;
}

int64_t Object::getI64(std::string_view name) const {
    int64_t value = 0;
    uint64_t offset;
    if (validate(name, DataType::INT64, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(&value, buff_->byte + offset, sizeof(value));
    }

    return value;
}

float Object::getF32(std::string_view name) const {
    float value = 0.0;
    uint64_t offset;
    if (validate(name, DataType::FLOAT32, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(&value, buff_->byte + offset, sizeof(value));
    }

    return value;
}

double Object::getF64(std::string_view name) const {
    double value = 0.0f;
    uint64_t offset;
    if (validate(name, DataType::FLOAT64, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(&value, buff_->byte + offset, sizeof(value));
    }

    return value;
}

Object Object::getObject(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t size = 0;
    uint64_t index = 0;
    ObjectMetadata *metadata = &exceptionMetaData;
    if (validate(name, DataType::OBJECT, XXH3_64bits_const(name), offset, size,
                 index, unusedU64)) {
        metadata = metadata_.typeMetaData[index].ref;
    }
    return Object(*this, *metadata, offset, size);  // RVO
}

std::string Object::getString(std::string_view name) const {
    std::string value;
    uint64_t offset;
    uint64_t size;

    if (validate(name, DataType::STRING, XXH3_64bits_const(name), offset, size,
                 unusedU64, unusedU64)) {
        value.resize(size);
        memcpy(value.data(), buff_->byte + offset, size);
        value.resize(std::strlen(value.c_str()));
    }

    return value;
}

void Object::setU8(std::string_view name, const uint8_t &value) const {
    uint64_t offset;

    if (validate(name, DataType::UINT8, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(buff_->byte + offset, &value, sizeof(value));
    }
}

void Object::setU16(std::string_view name, const uint16_t &value) const {
    uint64_t offset;

    if (validate(name, DataType::UINT16, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(buff_->byte + offset, &value, sizeof(value));
    }
}

void Object::setU32(std::string_view name, const uint32_t &value) const {
    uint64_t offset;

    if (validate(name, DataType::UINT32, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(buff_->byte + offset, &value, sizeof(value));
    }
}

void Object::setU64(std::string_view name, const uint64_t &value) const {
    uint64_t offset;

    if (validate(name, DataType::UINT64, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(buff_->byte + offset, &value, sizeof(value));
    }
}

void Object::setI8(std::string_view name, const int8_t &value) const {
    uint64_t offset;

    if (validate(name, DataType::INT8, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(buff_->byte + offset, &value, sizeof(value));
    }
}

void Object::setI16(std::string_view name, const int16_t &value) const {
    uint64_t offset;

    if (validate(name, DataType::INT16, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(buff_->byte + offset, &value, sizeof(value));
    }
}

void Object::setI32(std::string_view name, const int32_t &value) const {
    uint64_t offset;

    if (validate(name, DataType::INT32, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(buff_->byte + offset, &value, sizeof(value));
    }
}

void Object::setI64(std::string_view name, const int64_t &value) const {
    uint64_t offset;

    if (validate(name, DataType::INT64, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(buff_->byte + offset, &value, sizeof(value));
    }
}

void Object::setF32(std::string_view name, const float &value) const {
    uint64_t offset;

    if (validate(name, DataType::FLOAT32, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(buff_->byte + offset, &value, sizeof(value));
    }
}

void Object::setF64(std::string_view name, const double &value) const {
    uint64_t offset;

    if (validate(name, DataType::FLOAT64, XXH3_64bits_const(name), offset,
                 unusedU64, unusedU64, unusedU64)) {
        memcpy(buff_->byte + offset, &value, sizeof(value));
    }
}

void Object::setString(std::string_view name, const std::string &value) const {
    uint64_t offset;
    uint64_t size;

    if (validate(name, DataType::STRING, XXH3_64bits_const(name), offset, size,
                 unusedU64, unusedU64)) {
        memcpy(buff_->byte + offset, value.c_str(),
               value.size() > size ? size : value.size());
        if (size > value.size()) {
            memset(buff_->byte + offset + value.size(), 0, size - value.size());
        }
    }
}

ArrayU8 Object::getArrayU8(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t count = 0;
    validate(name, DataType::UINT8, XXH3_64bits_const(name), offset, unusedU64,
             unusedU64, count, true);
    return ArrayU8(buff_, offset, count);
}

ArrayU16 Object::getArrayU16(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t count = 0;
    validate(name, DataType::UINT16, XXH3_64bits_const(name), offset, unusedU64,
             unusedU64, count, true);
    return ArrayU16(buff_, offset, count);
}

ArrayU32 Object::getArrayU32(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t count = 0;
    validate(name, DataType::UINT32, XXH3_64bits_const(name), offset, unusedU64,
             unusedU64, count, true);
    return ArrayU32(buff_, offset, count);
}

ArrayU64 Object::getArrayU64(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t count = 0;
    validate(name, DataType::UINT64, XXH3_64bits_const(name), offset, unusedU64,
             unusedU64, count, true);
    return ArrayU64(buff_, offset, count);
}

ArrayI8 Object::getArrayI8(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t count = 0;
    validate(name, DataType::INT8, XXH3_64bits_const(name), offset, unusedU64,
             unusedU64, count, true);
    return ArrayI8(buff_, offset, count);
}

ArrayI16 Object::getArrayI16(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t count = 0;
    validate(name, DataType::INT16, XXH3_64bits_const(name), offset, unusedU64,
             unusedU64, count, true);
    return ArrayI16(buff_, offset, count);
}

ArrayI32 Object::getArrayI32(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t count = 0;
    validate(name, DataType::INT32, XXH3_64bits_const(name), offset, unusedU64,
             unusedU64, count, true);
    return ArrayI32(buff_, offset, count);
}

ArrayI64 Object::getArrayI64(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t count = 0;
    validate(name, DataType::INT64, XXH3_64bits_const(name), offset, unusedU64,
             unusedU64, count, true);
    return ArrayI64(buff_, offset, count);
}

ArrayF32 Object::getArrayF32(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t count = 0;
    validate(name, DataType::FLOAT32, XXH3_64bits_const(name), offset, unusedU64,
             unusedU64, count, true);
    return ArrayF32(buff_, offset, count);
}

ArrayF64 Object::getArrayF64(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t count = 0;
    validate(name, DataType::FLOAT64, XXH3_64bits_const(name), offset, unusedU64,
             unusedU64, count, true);
    return ArrayF64(buff_, offset, count);
}

ArrayString Object::getArrayString(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t count = 0;
    uint64_t size = 0;
    validate(name, DataType::STRING, XXH3_64bits_const(name), offset, size,
             unusedU64, count, true);
    return ArrayString(buff_, offset, count, size);
}

ArrayObject Object::getArrayObject(std::string_view name) const {
    uint64_t offset = 0;
    uint64_t count = 0;
    uint64_t index = 0;
    ObjectMetadata *metadata = &exceptionMetaData;
    if (validate(name, DataType::OBJECT, XXH3_64bits_const(name), offset, unusedU64,
                 index, unusedU64, true)) {
        metadata = metadata_.typeMetaData[index].ref;
    }
    return ArrayObject(*this, *metadata, offset, count);
}

uint64_t Object::size() { return anchestor_.size_; }

uint8_t *Object::data() { return buff_->byte; }

uint8_t *Object::release() {
    anchestor_.isAncestor_ = false;
    return buff_->byte;
}

void Object::print(bool viewAllAncestor) {
    std::stringstream s;

    if (viewAllAncestor) {
        anchestor_.print();
    } else {
        s << ":: object: " << metadata_.name << ", ID: unused"
          << ", offset: " << offset_ << ", size: " << size_ << " ::";
        print(s);
        std::cout << s.rdbuf() << "\n";
    }
}

void Object::print(std::stringstream &s, const std::string &prefix) const {
    for (int i = 0; i < metadata_.typeMetaData.size(); ++i) {
        union {
            uint8_t u8;
            uint16_t u16;
            uint32_t u32;
            uint64_t u64;
            int8_t i8;
            int16_t i16;
            int32_t i32;
            int64_t i64;
            float f32;
            double f64;
        } temp = {};
        auto &itr = metadata_.typeMetaData[i];
        std::string str;
        std::string new_prefix;

        bool isLast = (i == metadata_.typeMetaData.size() - 1);

        s << "\n";

        s << prefix;
        if (isLast) {
            s << "└─ parameter: ";
        } else {
            s << "├─ parameter: ";
        }

#ifdef ASDF_USE_PRETTY_PRINT
        s << std::left << std::setw(metadata_.maxTypeNameSize + 2) << (itr.name)
          << std::setw(15) << ("type: " + dtypeToString(itr.type))
          << std::setw(12)
          << ("offset: " + std::to_string(itr.offset + offset_))
          << "size: " << itr.size << "  ";
#else
        s << (itr.name) << (", type: " + dtypeToString(itr.type))
          << (", offset: " + std::to_string(itr.offset + offset_))
          << ", size: " << itr.size << ", ";

#endif
        switch (itr.type) {
            case DataType::UINT8:
                if (!itr.isArray) {
                    memcpy(&temp, buff_->byte + offset_ + itr.offset,
                           sizeof(uint8_t));
                    s << "value: " << temp.u64;
                }
                break;
            case DataType::UINT16:
                if (!itr.isArray) {
                    memcpy(&temp, buff_->byte + offset_ + itr.offset,
                           sizeof(uint16_t));
                    s << "value: " << temp.u64;
                }
                break;
            case DataType::UINT32:
                if (!itr.isArray) {
                    memcpy(&temp, buff_->byte + offset_ + itr.offset,
                           sizeof(uint32_t));
                    s << "value: " << temp.u64;
                }
                break;
            case DataType::UINT64:
                if (!itr.isArray) {
                    memcpy(&temp, buff_->byte + offset_ + itr.offset,
                           sizeof(uint64_t));
                    s << "value: " << temp.u64;
                }
                break;
            case DataType::INT8:
                if (!itr.isArray) {
                    memcpy(&temp, buff_->byte + offset_ + itr.offset,
                           sizeof(int8_t));
                    s << "value: " << temp.i64;
                }
                break;
            case DataType::INT16:
                if (!itr.isArray) {
                    memcpy(&temp, buff_->byte + offset_ + itr.offset,
                           sizeof(int16_t));
                    s << "value: " << temp.i64;
                }
                break;
            case DataType::INT32:
                if (!itr.isArray) {
                    memcpy(&temp, buff_->byte + offset_ + itr.offset,
                           sizeof(int32_t));
                    s << "value: " << temp.i64;
                }
                break;
            case DataType::INT64:
                if (!itr.isArray) {
                    memcpy(&temp, buff_->byte + offset_ + itr.offset,
                           sizeof(int64_t));
                    s << "value: " << temp.i64;
                }
                break;
            case DataType::FLOAT32:
                if (!itr.isArray) {
                    memcpy(&temp, buff_->byte + offset_ + itr.offset,
                           sizeof(float));
                    s << "value: " << temp.f32;
                }
                break;
            case DataType::FLOAT64:
                if (!itr.isArray) {
                    memcpy(&temp, buff_->byte + offset_ + itr.offset,
                           sizeof(double));
                    s << "value: " << temp.f64;
                }
                break;
            case DataType::NA:
                break;
            case DataType::STRING:
                if (!itr.isArray) {
                    str.resize(itr.size);
                    memcpy(str.data(), buff_->byte + offset_ + itr.offset,
                           itr.size);
                    s << "value: " << str;
                }
                break;
            case DataType::OBJECT: {
                if (!itr.isArray) {
                    s << "ref: " << itr.ref->name;
                    new_prefix = prefix + (isLast ? "   " : "│  ");
                    auto object =
                        Object(*this, *itr.ref, offset_ + itr.offset, itr.size);
                    object.print(s, new_prefix);
                }
            } break;
        }

        if (itr.isArray) {
            s << " [array size: " << itr.count << "]";
            if (itr.count > 0) {
                s << "\n";
                s << prefix;
                if (isLast) {
                    s << "   ";
                } else {
                    s << "│  ";
                }
                s << "└─ values: [";
                
                for (uint64_t j = 0; j < itr.count; ++j) {
                    if (j > 0) s << ", ";
                    
                    switch (itr.type) {
                        case DataType::UINT8:
                            memcpy(&temp, buff_->byte + offset_ + itr.offset + j * sizeof(uint8_t), sizeof(uint8_t));
                            s << temp.u64;
                            break;
                        case DataType::UINT16:
                            memcpy(&temp, buff_->byte + offset_ + itr.offset + j * sizeof(uint16_t), sizeof(uint16_t));
                            s << temp.u64;
                            break;
                        case DataType::UINT32:
                            memcpy(&temp, buff_->byte + offset_ + itr.offset + j * sizeof(uint32_t), sizeof(uint32_t));
                            s << temp.u64;
                            break;
                        case DataType::UINT64:
                            memcpy(&temp, buff_->byte + offset_ + itr.offset + j * sizeof(uint64_t), sizeof(uint64_t));
                            s << temp.u64;
                            break;
                        case DataType::INT8:
                            memcpy(&temp, buff_->byte + offset_ + itr.offset + j * sizeof(int8_t), sizeof(int8_t));
                            s << temp.i64;
                            break;
                        case DataType::INT16:
                            memcpy(&temp, buff_->byte + offset_ + itr.offset + j * sizeof(int16_t), sizeof(int16_t));
                            s << temp.i64;
                            break;
                        case DataType::INT32:
                            memcpy(&temp, buff_->byte + offset_ + itr.offset + j * sizeof(int32_t), sizeof(int32_t));
                            s << temp.i64;
                            break;
                        case DataType::INT64:
                            memcpy(&temp, buff_->byte + offset_ + itr.offset + j * sizeof(int64_t), sizeof(int64_t));
                            s << temp.i64;
                            break;
                        case DataType::FLOAT32:
                            memcpy(&temp, buff_->byte + offset_ + itr.offset + j * sizeof(float), sizeof(float));
                            s << temp.f32;
                            break;
                        case DataType::FLOAT64:
                            memcpy(&temp, buff_->byte + offset_ + itr.offset + j * sizeof(double), sizeof(double));
                            s << temp.f64;
                            break;
                        case DataType::STRING: {
                            std::string arrayStr;
                            arrayStr.resize(itr.size / itr.count);
                            memcpy(arrayStr.data(), buff_->byte + offset_ + itr.offset + j * (itr.size / itr.count), itr.size / itr.count);
                            s << "\"" << arrayStr << "\"";
                            break;
                        }
                        case DataType::OBJECT: {
                            s << "object at index " << j;
                            new_prefix = prefix + (isLast ? "   " : "│  ");
                            auto object = Object(*this, *itr.ref, offset_ + itr.offset + j * itr.size, itr.size);
                            object.print(s, new_prefix);
                            break;
                        }
                        default:
                            break;
                    }
                }
                s << "]";
            }
        }
    }
}

bool Object::validate(const std::string_view &name, DataType type,
                      const uint64_t &hash, uint64_t &offset, uint64_t &size,
                      uint64_t &index, uint64_t &count, bool isArray) const {
    bool success = false;

    do {
        auto it = metadata_.typeIDMap.find(hash);
        if (it == metadata_.typeIDMap.end()) {
            std::stringstream s;
            s << "[ASDF] object error: parameter name mismatch...  package: "
              << metadata_.name << ", cannot find >>> parameter: " << name
              << " <<<\n";
            std::cerr << s.str();
            break;
        }

        auto typeMetadata = metadata_.typeMetaData[it->second];

        if (typeMetadata.type != type) {
            std::stringstream s;
            s << "[ASDF] object error: parameter type mismatch...  package: "
              << metadata_.name << ", parameter: " << name
              << ", >>> requested type: " << dtypeToString(type)
              << ", actual type: " << dtypeToString(typeMetadata.type)
              << " <<<\n";
            std::cerr << s.str();
            break;
        }

        if (isArray != typeMetadata.isArray) {
            std::stringstream s;
            s << "[ASDF] object error: parameter array mismatch...  package: "
              << metadata_.name << ", parameter: " << name
              << ", type: " << dtypeToString(type);

            if (typeMetadata.isArray) {
                s << ", expected array type, but requested non-array type\n";
            } else {
                s << ", expected non-array type, but requested array type\n";
            }
            std::cerr << s.str();
            break;
        }

        offset = typeMetadata.offset + offset_;
        size = typeMetadata.size;
        index = it->second;
        count = typeMetadata.count;
        success = true;
    } while (0);

    if (!success) fatalErrorException();

    return success;
}

}  // namespace asdf
