#include "asdf/schema.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <filesystem>
#include <iostream>
#include <queue>

#include "include/constexpr_xxhash3.hpp"

namespace pt = boost::property_tree;
namespace fs = std::filesystem;
using constexpr_xxh3::XXH3_64bits_const;

namespace asdf {

static ObjectMetadata exceptionMetaData;
struct ParseParameterData {
  uint64_t hash;
  ObjectMetadata::TypeMetadata metadata;
};

DataType getType(const std::string& type);
size_t getSize(DataType type);

Schema::Schema() {}

void Schema::include(std::string_view name) {
  do {
    if (!fs::exists(name)) {
      std::cout << "[ASDF] schema include error: invalidate file or "
                   "folder path >>> "
                << name << "<<<\n";
      fatalErrorException();
      break;
    }

    if (fs::is_regular_file(name)) {
      if (name.ends_with("json")) {
        includeFromFile(name);
      } else {
        std::cout << "[ASDF] schema include error: invalidate file type >>>"
                  << name << "<<<\n";
        fatalErrorException();
        break;
      }
    } else {
      includeFromPath(name);
    }
  } while (0);
}

Object Schema::createObject(std::string_view name) {
  uint64_t objectNameHash = XXH3_64bits_const(name);
  auto findItr = objectMetadataNameMap.find(objectNameHash);

  if (findItr == objectMetadataNameMap.end()) {
    std::cout << "[ASDF] object create error: cannot find object name >>> "
              << name << " <<<\n";
    fatalErrorException();
  }

  return (findItr != objectMetadataNameMap.end()) ? Object(findItr->second)
                                                  : Object(exceptionMetaData);
}

bool Schema::includeFromFile(std::string_view filename) {
  pt::ptree root;
  pt::read_json(filename.data(), root);

  do {
    auto validSchema = root.find("ASDFSchema");
    if (validSchema == root.not_found()) {
      std::cout << "[ASDF] schema include error from " << filename
                << "\n       invalidate json format, missing tag ... >>> tag: "
                   "ASDFSchema <<<\n";
      fatalErrorException();
      break;
    }

    auto objectBundleTree = root.find("object");
    if (objectBundleTree == root.not_found()) {
      std::cout << "[ASDF] schema include error from " << filename
                << "\n       missing tag ... >>> tag: object <<<\n";
      fatalErrorException();
      break;
    }

    for (auto& objectTree : objectBundleTree->second) {
      auto objectNameTree = objectTree.second.find("name");
      auto objectIDTree = objectTree.second.find("id");
      auto parameterBundleTree = objectTree.second.find("parameter");
      std::queue<ParseParameterData> parserQue;

      if (objectNameTree == objectTree.second.not_found()) {
        std::cout << "[ASDF] schema include error from " << filename
                  << "\n       missing tag ... >>> tag : object::name < < <\n ";
        fatalErrorException();
        break;
      }

      auto objectNameStr = objectNameTree->second.get_value<std::string>();
      if (objectIDTree == objectTree.second.not_found()) {
        std::cout << "[ASDF] schema include error from " << filename
                  << "\n       missing tag ... object: " << objectNameStr
                  << ", >>> tag: object::id <<<\n";
        fatalErrorException();
        break;
      }

      auto objectID = objectIDTree->second.get_value<uint64_t>();
      if (parameterBundleTree == objectTree.second.not_found()) {
        std::cout << "[ASDF] schema include error from " << filename
                  << "\n       missing tag ... object: " << objectNameStr
                  << ", >>> tag: object::parameter <<<\n";
        fatalErrorException();
        break;
      }

      uint64_t parameterOffset = 0;
      uint64_t parameterNameMaxSize = 0;
      uint64_t objectSize = 0;
      for (auto& parameterTree : parameterBundleTree->second) {
        auto parameterNameTree = parameterTree.second.find("name");
        auto parameterTypeTree = parameterTree.second.find("type");

        if (parameterNameTree == parameterTree.second.not_found()) {
          std::cout << "[ASDF] schema include error from " << filename
                    << "\n       missing tag ... object: " << objectNameStr
                    << ", >>> tag: parameter::name <<<\n";
          fatalErrorException();
          break;
        }

        auto parameterNameStr =
            parameterNameTree->second.get_value<std::string>();

        if (parameterTypeTree == parameterTree.second.not_found()) {
          std::cout << "[ASDF] schema include error from " << filename
                    << "\n       missing tag ... object: " << objectNameStr
                    << ", parameter: " << parameterNameStr
                    << ", >>> tag: parameter::type <<<\n";
          fatalErrorException();
          break;
        }

        auto parameterTypeStr =
            parameterTypeTree->second.get_value<std::string>();
        auto parameterType = getType(parameterTypeStr);

        if (parameterType == DataType::NA) {
          std::cout << "[ASDF] schema include error from " << filename
                    << "\n       unsupported type ... object: " << objectNameStr
                    << ", parameter: " << parameterNameStr
                    << ", >>> type: " << parameterTypeStr
                    << " <<<\n"
                       "[ASDF] allowed types are as follows: \n"
                       "       int8, int16, int32, int64, "
                       "uint8, uint16, uint32, uint64, "
                       "float32, float64, string, object\n";
          fatalErrorException();
          break;
        }

        uint64_t parameterSize = 0;
        ObjectMetadata* parameterRef = nullptr;
        if (parameterType == DataType::STRING) {
          auto stringSizeTree = parameterTree.second.find("size");
          if (stringSizeTree == parameterTree.second.not_found()) {
            std::cout << "[ASDF] schema include error from " << filename
                      << "\n       missing tag ... object: " << objectNameStr
                      << ", parameter: " << parameterNameStr
                      << ", type: " << parameterTypeStr
                      << ", >>> tag: parameter::size <<<\n";
            fatalErrorException();
            break;
          }
          parameterSize = stringSizeTree->second.get_value<uint64_t>();
        } else if (parameterType == DataType::OBJECT) {
          auto refTree = parameterTree.second.find("ref");
          if (refTree == parameterTree.second.not_found()) {
            std::cout << "[ASDF] schema include error from " << filename
                      << "\n       missing tag ... object: " << objectNameStr
                      << ", parameter: " << parameterNameStr
                      << ", type: " << parameterTypeStr
                      << ", >>> tag: parameter::ref <<<\n";
            fatalErrorException();
            break;
          }

          auto refStr = refTree->second.get_value<std::string>();
          uint64_t refHash = XXH3_64bits_const(refStr);
          auto refItr = objectMetadataNameMap.find(refHash);

          if (refItr == objectMetadataNameMap.end()) {
            std::cout << "[ASDF] schema include error from " << filename
                      << "\n       cannot find reference ... object: "
                      << objectNameStr << ", parameter: " << parameterNameStr
                      << ", type: " << parameterTypeStr
                      << ", >>> ref: " << refStr << " <<<\n";
            fatalErrorException();
            break;
          }

          parameterRef = &refItr->second;
          parameterSize = refItr->second.size;
        } else {
          parameterSize = getSize(parameterType);
        }

        ParseParameterData parseParameterData = {};
        uint64_t parameterNameHash = XXH3_64bits_const(parameterNameStr);

        parseParameterData.metadata.name = parameterNameStr;
        parseParameterData.metadata.type = parameterType;
        parseParameterData.metadata.size = parameterSize;
        parseParameterData.metadata.ref = parameterRef;
        parseParameterData.metadata.offset = parameterOffset;
        parseParameterData.hash = parameterNameHash;
        parserQue.push(parseParameterData);

        parameterOffset += parameterSize;
        objectSize += parameterSize;
        parameterNameMaxSize = parameterNameMaxSize > parameterNameStr.size()
                                   ? parameterNameMaxSize
                                   : parameterNameStr.size();
      }

      uint64_t objectNameHash = XXH3_64bits_const(objectNameStr);
      ObjectMetadata objectMetaData = {};
      objectMetaData.typeMetaData.reserve(parserQue.size());

      objectMetaData.name = objectNameStr;
      objectMetaData.size = objectSize;
      objectMetaData.maxTypeNameSize = parameterNameMaxSize;

      for (int cnt = 0; !parserQue.empty(); ++cnt) {
        objectMetaData.typeMetaData.push_back(parserQue.front().metadata);
        objectMetaData.typeIDMap.insert({parserQue.front().hash, cnt});
        parserQue.pop();
      }

      objectMetadataNameMap.insert({objectNameHash, objectMetaData});
    }
    std::cout << "[ASDF] schema include succes: " << filename << "\n";
  } while (0);

  return true;
}

bool Schema::includeFromPath(std::string_view pathname) {
  for (const auto& entry : fs::directory_iterator(pathname)) {
    if (entry.is_regular_file() && entry.path().extension() == ".json") {
      includeFromFile(entry.path().string());
    }
  }

  return true;
}

DataType getType(const std::string& type) {
  const static std::unordered_map<std::string_view, DataType> typeStrMap = {
      {"int8", DataType::INT8},       {"int16", DataType::INT16},
      {"int32", DataType::INT32},     {"int64", DataType::INT64},
      {"uint8", DataType::UINT8},     {"uint16", DataType::UINT16},
      {"uint32", DataType::UINT32},   {"uint64", DataType::UINT64},
      {"float32", DataType::FLOAT32}, {"float64", DataType::FLOAT64},
      {"string", DataType::STRING},   {"object", DataType::OBJECT}};

  DataType type_ = DataType::NA;
  if (auto it = typeStrMap.find(type); it != typeStrMap.end()) {
    type_ = it->second;
  }

  return type_;
}

size_t getSize(DataType type) {
  size_t size = 0;

  switch (type) {
    case DataType::NA:
    case DataType::STRING:
    case DataType::OBJECT:
      break;
    case DataType::INT8:
    case DataType::UINT8:
      size = sizeof(uint8_t);
      break;
    case DataType::INT16:
    case DataType::UINT16:
      size = sizeof(uint16_t);
      break;
    case DataType::INT32:
    case DataType::UINT32:
    case DataType::FLOAT32:
      size = sizeof(uint32_t);
      break;
    case DataType::INT64:
    case DataType::UINT64:
    case DataType::FLOAT64:
      size = sizeof(uint64_t);
      break;
  }
  return size;
}

}  // namespace asdf