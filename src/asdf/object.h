#ifndef __ASDF_OBJECT_H__
#define __ASDF_OBJECT_H__

#include "asdf/types.h"
#include "asdf/array.h"

namespace asdf {
class Object {
   public:
    Object(ObjectMetadata &);
    Object(const Object &, ObjectMetadata &, uint64_t, uint64_t);
    ~Object();

    uint8_t  getU8(std::string_view name) const;
    uint16_t getU16(std::string_view name) const;
    uint32_t getU32(std::string_view name) const;
    uint64_t getU64(std::string_view name) const;
    int8_t   getI8(std::string_view name) const;
    int16_t  getI16(std::string_view name) const;
    int32_t  getI32(std::string_view name) const;
    int64_t  getI64(std::string_view name) const;
    float    getF32(std::string_view name) const;
    double   getF64(std::string_view name) const;
    std::string getString(std::string_view name) const;
    Object   getObject(std::string_view name) const;

    void setU8(std::string_view name, const uint8_t &value) const;
    void setU16(std::string_view name, const uint16_t &value) const;
    void setU32(std::string_view name, const uint32_t &value) const;
    void setU64(std::string_view name, const uint64_t &value) const;
    void setI8(std::string_view name, const int8_t &value) const;
    void setI16(std::string_view name, const int16_t &value) const;
    void setI32(std::string_view name, const int32_t &value) const;
    void setI64(std::string_view name, const int64_t &value) const;
    void setF32(std::string_view name, const float &value) const;
    void setF64(std::string_view name, const double &value) const;
    void setString(std::string_view name, const std::string &value) const;

    ArrayU8  getArrayU8(std::string_view name) const;
    ArrayU16 getArrayU16(std::string_view name) const;
    ArrayU32 getArrayU32(std::string_view name) const;
    ArrayU64 getArrayU64(std::string_view name) const;
    ArrayI8  getArrayI8(std::string_view name) const;
    ArrayI16 getArrayI16(std::string_view name) const;
    ArrayI32 getArrayI32(std::string_view name) const;
    ArrayI64 getArrayI64(std::string_view name) const;
    ArrayF32 getArrayF32(std::string_view name) const;
    ArrayF64 getArrayF64(std::string_view name) const;
    ArrayString getArrayString(std::string_view name) const;
    ArrayObject getArrayObject(std::string_view name) const;

    uint64_t size();
    uint8_t *data();
    uint8_t *release();
    void print(bool viewAllAncestor = false);

   private:
    Object(const Object &) = delete;
    bool validate(const std::string_view &, DataType, const uint64_t &,
                  uint64_t &, uint64_t &, uint64_t &, uint64_t &,
                  bool = false) const;
    void print(std::stringstream &, const std::string & = "") const;

    uint64_t id_;
    uint64_t size_;
    uint64_t offset_;
    bool isAncestor_;
    const bool &isAlive_;
    AlignBuff *buff_;
    ObjectMetadata &metadata_;
    Object &anchestor_;
};

void fatalErrorException();
}  // namespace asdf

#endif  // __ASDF_OBJECT_H__