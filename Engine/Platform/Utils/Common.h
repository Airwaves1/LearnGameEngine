#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <sstream>
#include <cstdint>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>

#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <filesystem>

#include "Utils/Log.h"

#ifdef AW_PLATFORM_WINDOWS
#include <Windows.h>
#endif // AW_PLATFORM_WINDOWS


#ifdef AW_ENABLE_ASSERTS
    #define AIRWAVE_ASSERT(x, ...) if(!x) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }
#else
    #define AIRWAVE_ASSERT(x, ...)
#endif // AW_ENABLE_ASSERTS


#define BIND_EVENT_FN(fn) std::bind(&fn, this, ::std::placeholders::_1)

#endif //COMMON_H