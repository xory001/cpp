#pragma once

#define JSON_NOEXCEPTION
#define JSON_ASSERT(x) do { (void)(x); } while (0)

#include <iostream>
#include "nlohmann_json/json.hpp"

using njson = nlohmann::json;

namespace njsonHelper
{
    bool HasKey( njson& j, const std::string& key );
    njson* GetValue( njson& j, const std::string& key );
    bool HasNestedKey( njson& j, const std::vector<std::string>& keys );
    njson* GetNestedValue( njson& j, const std::vector<std::string>& keys );

    /* example
  
    json j;
    j["name"] = "Alice";
    j["age"] = 25;

    std::string invalidJson = j.dump();
    json parsedJson = json::parse(invalidJson, nullptr, false);
    if (parsedJson.is_discarded()) {
        std::cout << "Parsing failed, got discarded object\n";
    }

    std::string validJson = R"({"id": 123})";
    json validParsed = json::parse(validJson, nullptr, false);
    json* typePtr = getValue(validParsed, "type");
    if (typePtr) {
        std::cout << "Type: " << *typePtr << "\n";
    } else {
        std::cout << "Type not found (nullptr)\n";
    }
    */

    inline bool HasKey( njson& j, const std::string& key ) 
    {
        return j.is_object() && j.contains( key );
    }

    inline njson* GetValue( njson& j, const std::string& key )
    {
        if ( j.is_object() && j.contains( key ) ) 
        {
            return &j[key];
        }
        return nullptr;
    }

    // ("user.info.name"£©
    inline bool HasNestedKey( njson& j, const std::vector<std::string>& keys )
    {
        njson* current = &j;
        for ( const auto& key : keys ) 
        {
            if ( !current->is_object() || !current->contains( key ) ) 
            {
                return false;
            }
            current = &( *current )[key];
        }
        return true;
    }

    inline njson* GetNestedValue( njson& j, const std::vector<std::string>& keys ) 
    {
        njson* current = &j;
        for ( const auto& key : keys ) 
        {
            if ( !current->is_object() || !current->contains( key ) ) 
            {
                return nullptr;
            }
            current = &( *current )[key];
        }
        return current;
    }
}
