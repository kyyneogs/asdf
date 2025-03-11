#ifndef __ASDF_OBJECT_H__
#define __ASDF_OBJECT_H__

#include "asdf/types.h"

namespace asdf {
class Object {
   public:
    Object(ObjectMetadata &);
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

    Object getObject(std::string_view name) const;

    uint64_t size();
    uint8_t *data();
    uint8_t *release();
    void print(bool viewAllAncestor = false);

   private:
    Object(const Object &, ObjectMetadata &, uint64_t, uint64_t);
    Object(const Object &) = delete;
    bool validate(const std::string_view &, DataType, const uint64_t &,
                  uint64_t &, uint64_t &, uint64_t &) const;
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