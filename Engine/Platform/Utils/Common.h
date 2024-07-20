#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <sstream>

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
    #define AIRWAVE_CORE_ASSERT(x, ...) if(!x) { LOG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }
#else
    #define AIRWAVE_ASSERT(x, ...)
    #define AIRWAVE_CORE_ASSERT(x, ...)
#endif // AW_ENABLE_ASSERTS

#endif //COMMON_H