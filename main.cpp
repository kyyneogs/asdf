#include <asdf/object.h>
#include <asdf/schema.h>
#include <iostream>

#include <include/constexpr_xxhash3.hpp>
#include "asdf/types.h"
#include "src/asdf/array.h"

#ifdef _WIN32
#include <Windows.h>
#endif

int main(int, char**) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    asdf::AlignBuff buff[4];

    asdf::array::ArrayI8 arr(buff, 0, sizeof(asdf::AlignBuff) * 4);

    arr.set(0, 123);

    std::cout << (int)arr.get(0);
    // asdf::Schema schema;
    // schema.include("../schema/something.json");

    // auto obj = schema.createObject("data_k01");
    // obj.setU8("isValid", 20);
    // obj.setString("name", "asdfefsadfefsfasfe");

    // auto nestObj = obj.getObject("nest");

    // nestObj.setI32("hello", 24531);

    // obj.print();
    // nestObj.print();
}
