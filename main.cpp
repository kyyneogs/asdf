#include <asdf/object.h>
#include <asdf/schema.h>

#include <include/constexpr_xxhash3.hpp>

#ifdef _WIN32
#include <Windows.h>
#endif

int main(int, char**) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    asdf::Schema schema;
    schema.include("../schema/something.json");

    auto obj = schema.createObject("data_k01");
    obj.setU8("isValid", 20);
    obj.setString("name", "asdfefsadfefsfasfe");

    auto nestObj = obj.getObject("nest");

    nestObj.setI32("hello", 24531);

    obj.print();
    nestObj.print();
}
