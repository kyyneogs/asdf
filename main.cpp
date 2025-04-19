#include <asdf/object.h>
#include <asdf/schema.h>
#include <iostream>

#include "asdf/schema.h"

#ifdef _WIN32
#include <Windows.h>
#endif

int main(int, char**) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    asdf::Schema schema;
    schema.include("../schema/something.json");

    auto obj = schema.createObject("data_k02");
    auto k = obj.getObject("m_k01");

    // k.setString("name", "Hello world");

    obj.print();
}
