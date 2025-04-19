#ifndef __ASDF_ARRAY_H__
#define __ASDF_ARRAY_H__

#include <cstdint>

#include "asdf/types.h"

namespace asdf {
class Object;
class ArrayU8 {
   public:
    ArrayU8(AlignBuff*, uint32_t, uint32_t);

    uint8_t get(uint64_t index);
    void set(uint64_t index, uint8_t value);

   private:
    ArrayU8(const ArrayU8&) = delete;
    AlignBuff* buff_;
    uint32_t offset_;
    uint32_t count_;
};

class ArrayU16 {
   public:
    ArrayU16(AlignBuff*, uint32_t, uint32_t);

    uint16_t get(uint64_t index);
    void set(uint64_t index, uint16_t value);

   private:
    ArrayU16(const ArrayU16&) = delete;
    AlignBuff* buff_;
    uint32_t offset_;
    uint32_t count_;
};

class ArrayU32 {
   public:
    ArrayU32(AlignBuff*, uint32_t, uint32_t);

    uint32_t get(uint64_t index);
    void set(uint64_t index, uint32_t value);

   private:
    ArrayU32(const ArrayU32&) = delete;
    AlignBuff* buff_;
    uint32_t offset_;
    uint32_t count_;
};

class ArrayU64 {
   public:
    ArrayU64(AlignBuff*, uint32_t, uint32_t);

    uint64_t get(uint64_t index);
    void set(uint64_t index, uint64_t value);

   private:
    ArrayU64(const ArrayU64&) = delete;
    AlignBuff* buff_;
    uint32_t offset_;
    uint32_t count_;
};

class ArrayI8 {
   public:
    ArrayI8(AlignBuff*, uint32_t, uint32_t);

    int8_t get(uint64_t index);
    void set(uint64_t index, int8_t value);

   private:
    ArrayI8(const ArrayI8&) = delete;
    AlignBuff* buff_;
    uint32_t offset_;
    uint32_t count_;
};

class ArrayI16 {
   public:
    ArrayI16(AlignBuff*, uint32_t, uint32_t);

    int16_t get(uint64_t index);
    void set(uint64_t index, int16_t value);

   private:
    ArrayI16(const ArrayI16&) = delete;
    AlignBuff* buff_;
    uint32_t offset_;
    uint32_t count_;
};

class ArrayI32 {
   public:
    ArrayI32(AlignBuff*, uint32_t, uint32_t);

    int32_t get(uint64_t index);
    void set(uint64_t index, int32_t value);

   private:
    ArrayI32(const ArrayI32&) = delete;
    AlignBuff* buff_;
    uint32_t offset_;
    uint32_t count_;
};

class ArrayI64 {
   public:
    ArrayI64(AlignBuff*, uint32_t, uint32_t);

    int64_t get(uint64_t index);
    void set(uint64_t index, int64_t value);

   private:
    ArrayI64(const ArrayI64&) = delete;
    AlignBuff* buff_;
    uint32_t offset_;
    uint32_t count_;
};

class ArrayF32 {
   public:
    ArrayF32(AlignBuff*, uint32_t, uint32_t);

    float get(uint64_t index);
    void set(uint64_t index, float value);

   private:
    ArrayF32(const ArrayF32&) = delete;
    AlignBuff* buff_;
    uint32_t offset_;
    uint32_t count_;
};

class ArrayF64 {
   public:
    ArrayF64(AlignBuff*, uint32_t, uint32_t);

    double get(uint64_t index);
    void set(uint64_t index, double value);

   private:
    ArrayF64(const ArrayF64&) = delete;
    AlignBuff* buff_;
    uint32_t offset_;
    uint32_t count_;
};

class ArrayString {
   public:
    ArrayString(AlignBuff*, uint32_t, uint32_t, uint32_t);

    std::string get(uint64_t index);
    void set(uint64_t index, const std::string& value);

   private:
    ArrayString(const ArrayString&) = delete;
    AlignBuff* buff_;
    uint32_t offset_;
    uint32_t count_;
    uint32_t size_;
};

class ArrayObject {
   public:
    ArrayObject(const Object&, ObjectMetadata&, uint32_t, uint32_t);

    Object get(uint64_t index);

   private:
    ArrayObject(const ArrayObject&) = delete;
    ObjectMetadata& metadata_;
    const Object& object_;
    uint32_t offset_;
    uint32_t count_;
};
}  // namespace asdf

#endif  // __ASDF_ARRAY_H__
