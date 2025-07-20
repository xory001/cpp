#ifndef __BASE_KITS_H__
#define __BASE_KITS_H__

#include <cstdint>
#include <chrono>
#include <string>

namespace BaseKits
{
    // timestamp
    int64_t getTimestampNanosecond();
    int64_t getTimestampMillisecond();
    int64_t getTimestampSecond();

    // character
    std::string toUpperCase(const std::string& str);

}

#endif


