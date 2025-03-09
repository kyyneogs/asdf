#ifndef __ASDF_SCHEMA_H__
#define __ASDF_SCHEMA_H__

#include "asdf/object.h"

namespace asdf {
class Schema {
   public:
    Object createObject(std::string_view name) const;

   private:
};
}  // namespace asdf

#endif  // __ASDF_SCHEMA_H__