#include <asdf/object.h>
#include <asdf/schema.h>

#include <include/constexpr_xxhash3.hpp>
#include <iostream>


int main(int, char**) {
    // asdf::ObjectMetadata pkg2;
    // pkg2.typeMetaData.emplace_back();

    // pkg2.name = "sub-packet";
    // pkg2.typeMetaData[0].type = asdf::DataType::FLOAT;
    // pkg2.typeMetaData[0].name = "hello";
    // pkg2.typeMetaData[0].size = 4;
    // pkg2.typeMetaData[0].offset = 0;
    // pkg2.size = 4;

    // pkg2.typeIDMap.insert({XXH3_64bits_const("hello"), 0});

    // asdf::ObjectMetadata pkg;
    // for (int i = 0; i < 3; ++i) pkg.typeMetaData.emplace_back();

    // pkg.name = "packet";
    // pkg.typeMetaData[0].type = asdf::DataType::UINT8;
    // pkg.typeMetaData[0].name = "fuck you";
    // pkg.typeMetaData[0].size = 1;
    // pkg.typeMetaData[0].offset = 0;

    // pkg.typeMetaData[1].type = asdf::DataType::OBJECT;
    // pkg.typeMetaData[1].name = "pkg";
    // pkg.typeMetaData[1].size = 4;
    // pkg.typeMetaData[1].offset = 21;
    // pkg.typeMetaData[1].ref = &pkg2;

    // pkg.typeMetaData[2].type = asdf::DataType::STRING;
    // pkg.typeMetaData[2].name = "Hellll";
    // pkg.typeMetaData[2].size = 20;
    // pkg.typeMetaData[2].offset = 1;

    // pkg.typeIDMap.insert({XXH3_64bits_const("fuck you"), 0});
    // pkg.typeIDMap.insert({XXH3_64bits_const("pkg"), 1});
    // pkg.typeIDMap.insert({XXH3_64bits_const("Hellll"), 2});

    // pkg.size = 25;

    // asdf::Object obj(pkg);

    // obj.setString("Hellll", "Hello world! asdfeffsadferrqwerwfdasfeqwer");
    // obj.setU8("fuck you", 3);

    // auto t = obj.getObject("pkg");
    // t.setF32("hello", 10.56);

    // std::cout << t.getF32("hello");

    asdf::Schema schema;
    schema.include("../schema/something.json");
    // schema.include("../types.schema.json");

    auto obj = schema.createObject("data_k01");
    // obj.setString("name", "hello");
    obj.setU8("isValid", 20);
    obj.setString("name", "strrser");

    auto nestObj = obj.getObject("nest");

    nestObj.setI32("hello", 24531);

    obj.print();
    nestObj.print();
}
