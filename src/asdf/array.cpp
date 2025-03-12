#include "asdf/array.h"

#include "asdf/object.h"
#include "asdf/types.h"

namespace asdf {
namespace array {
static ObjectMetadata exceptionMetaData = {};

ArrayU8::ArrayU8(AlignBuff* buff, uint32_t offset, uint32_t count) {
    buff_ = buff;
    offset_ = offset;
    count_ = count;
}

uint8_t ArrayU8::get(uint64_t index) {
    uint8_t value = 0;
    if (index < count_) {
        memcpy(&value, buff_->byte + offset_ + sizeof(uint8_t) * index,
               sizeof(uint8_t));
    }
    return value;
}

void ArrayU8::set(uint64_t index, uint8_t value) {
    if (index < count_) {
        memcpy(buff_->byte + offset_ + sizeof(uint8_t) * index, &value,
               sizeof(uint8_t));
    }
}

ArrayU16::ArrayU16(AlignBuff* buff, uint32_t offset, uint32_t count) {
    buff_ = buff;
    offset_ = offset;
    count_ = count;
}

uint16_t ArrayU16::get(uint64_t index) {
    uint16_t value = 0;
    if (index < count_) {
        memcpy(&value, buff_->byte + offset_ + sizeof(uint16_t) * index,
               sizeof(uint16_t));
    }
    return value;
}

void ArrayU16::set(uint64_t index, uint16_t value) {
    if (index < count_) {
        memcpy(buff_->byte + offset_ + sizeof(uint16_t) * index, &value,
               sizeof(uint16_t));
    }
}

ArrayU32::ArrayU32(AlignBuff* buff, uint32_t offset, uint32_t count) {
    buff_ = buff;
    offset_ = offset;
    count_ = count;
}

uint32_t ArrayU32::get(uint64_t index) {
    uint32_t value = 0;
    if (index < count_) {
        memcpy(&value, buff_->byte + offset_ + sizeof(uint32_t) * index,
               sizeof(uint32_t));
    }
    return value;
}

void ArrayU32::set(uint64_t index, uint32_t value) {
    if (index < count_) {
        memcpy(buff_->byte + offset_ + sizeof(uint32_t) * index, &value,
               sizeof(uint32_t));
    }
}

ArrayU64::ArrayU64(AlignBuff* buff, uint32_t offset, uint32_t count) {
    buff_ = buff;
    offset_ = offset;
    count_ = count;
}

uint64_t ArrayU64::get(uint64_t index) {
    uint64_t value = 0;
    if (index < count_) {
        memcpy(&value, buff_->byte + offset_ + sizeof(uint64_t) * index,
               sizeof(uint64_t));
    }
    return value;
}

void ArrayU64::set(uint64_t index, uint64_t value) {
    if (index < count_) {
        memcpy(buff_->byte + offset_ + sizeof(uint64_t) * index, &value,
               sizeof(uint64_t));
    }
}

ArrayI8::ArrayI8(AlignBuff* buff, uint32_t offset, uint32_t count) {
    buff_ = buff;
    offset_ = offset;
    count_ = count;
}

int8_t ArrayI8::get(uint64_t index) {
    int8_t value = 0;
    if (index < count_) {
        memcpy(&value, buff_->byte + offset_ + sizeof(int8_t) * index,
               sizeof(int8_t));
    }
    return value;
}

void ArrayI8::set(uint64_t index, int8_t value) {
    if (index < count_) {
        memcpy(buff_->byte + offset_ + sizeof(int8_t) * index, &value,
               sizeof(int8_t));
    }
}

ArrayI16::ArrayI16(AlignBuff* buff, uint32_t offset, uint32_t count) {
    buff_ = buff;
    offset_ = offset;
    count_ = count;
}

int16_t ArrayI16::get(uint64_t index) {
    int16_t value = 0;
    if (index < count_) {
        memcpy(&value, buff_->byte + offset_ + sizeof(int16_t) * index,
               sizeof(int16_t));
    }
    return value;
}

void ArrayI16::set(uint64_t index, int16_t value) {
    if (index < count_) {
        memcpy(buff_->byte + offset_ + sizeof(int16_t) * index, &value,
               sizeof(int16_t));
    }
}

ArrayI32::ArrayI32(AlignBuff* buff, uint32_t offset, uint32_t count) {
    buff_ = buff;
    offset_ = offset;
    count_ = count;
}

int32_t ArrayI32::get(uint64_t index) {
    int32_t value = 0;
    if (index < count_) {
        memcpy(&value, buff_->byte + offset_ + sizeof(int32_t) * index,
               sizeof(int32_t));
    }
    return value;
}

void ArrayI32::set(uint64_t index, int32_t value) {
    if (index < count_) {
        memcpy(buff_->byte + offset_ + sizeof(int32_t) * index, &value,
               sizeof(int32_t));
    }
}

ArrayI64::ArrayI64(AlignBuff* buff, uint32_t offset, uint32_t count) {
    buff_ = buff;
    offset_ = offset;
    count_ = count;
}

int64_t ArrayI64::get(uint64_t index) {
    int64_t value = 0;
    if (index < count_) {
        memcpy(&value, buff_->byte + offset_ + sizeof(int64_t) * index,
               sizeof(int64_t));
    }
    return value;
}

void ArrayI64::set(uint64_t index, int64_t value) {
    if (index < count_) {
        memcpy(buff_->byte + offset_ + sizeof(int64_t) * index, &value,
               sizeof(int64_t));
    }
}

ArrayF32::ArrayF32(AlignBuff* buff, uint32_t offset, uint32_t count) {
    buff_ = buff;
    offset_ = offset;
    count_ = count;
}

float ArrayF32::get(uint64_t index) {
    float value = 0;
    if (index < count_) {
        memcpy(&value, buff_->byte + offset_ + sizeof(float) * index,
               sizeof(float));
    }
    return value;
}

void ArrayF32::set(uint64_t index, float value) {
    if (index < count_) {
        memcpy(buff_->byte + offset_ + sizeof(float) * index, &value,
               sizeof(float));
    }
}

ArrayF64::ArrayF64(AlignBuff* buff, uint32_t offset, uint32_t count) {
    buff_ = buff;
    offset_ = offset;
    count_ = count;
}

double ArrayF64::get(uint64_t index) {
    double value = 0;
    if (index < count_) {
        memcpy(&value, buff_->byte + offset_ + sizeof(double) * index,
               sizeof(double));
    }
    return value;
}

void ArrayF64::set(uint64_t index, double value) {
    if (index < count_) {
        memcpy(buff_->byte + offset_ + sizeof(double) * index, &value,
               sizeof(double));
    }
}

ArrayString::ArrayString(AlignBuff* buff, uint32_t offset, uint32_t count) {
    buff_ = buff;
    offset_ = offset;
    count_ = count;
}

std::string ArrayString::get(uint64_t index) {
    std::string value;
    if (index < count_) {
        value.resize(size_);
        memcpy(value.data(), buff_->byte + offset_ + size_ * index, size_);
        value.resize(std::strlen(value.c_str()));
    }
    return value;
}

void ArrayString::set(uint64_t index, const std::string& value) {
    if (index < count_) {
        memcpy(buff_->byte + offset_ + size_ * index, value.c_str(),
               value.size() > size_ ? size_ : value.size());
        if (size_ > value.size()) {
            memset(buff_->byte + offset_ + size_ * index + value.size(), 0,
                   size_ - value.size());
        }
    }
}

ArrayObject::ArrayObject(const Object& object, ObjectMetadata& metadata,
                         uint32_t offset, uint32_t count)
    : metadata_(metadata), object_(object) {
    offset_ = offset;
    count_ = count;
}

Object ArrayObject::get(uint64_t index) {
    uint32_t offset = offset_;
    uint32_t size = metadata_.size;
    if (index < count_) offset += size * index;

    return Object(object_, metadata_, offset, size);
}
}  // namespace array
}  // namespace asdf