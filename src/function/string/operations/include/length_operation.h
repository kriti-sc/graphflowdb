#pragma once

#include <cassert>
#include <cstring>

#include "src/common/types/include/gf_string.h"

using namespace std;
using namespace graphflow::common;

namespace graphflow {
namespace function {
namespace operation {

struct Length {
    static inline void operation(gf_string_t& input, int64_t& result) { result = input.len; }
};

} // namespace operation
} // namespace function
} // namespace graphflow
