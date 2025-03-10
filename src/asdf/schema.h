#ifndef __ASDF_SCHEMA_H__
#define __ASDF_SCHEMA_H__

#include "asdf/object.h"

namespace asdf {
class Schema {
   public:
    Schema();

    void include(std::string_view filename);
    Object createObject(std::string_view name);

   private:
    bool includeFromFile(std::string_view filename);
    bool includeFromPath(std::string_view pathname);

    std::unordered_map<uint64_t, ObjectMetadata> objectMetadataNameMap;
    std::unordered_map<uint64_t, std::reference_wrapper<ObjectMetadata>> objectMetadataIDMap;
};
}  // namespace asdf

#endif  // __ASDF_SCHEMA_H__