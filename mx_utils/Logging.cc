#include "mx_utils/Logging.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include "Env.h"
#include "Slice.h"

namespace mx_blobstack {

void AppendNumberTo(std::string* str, uint64_t num) {
    char buf[30];
    snprintf(buf, sizeof(buf), "%llu", (unsigned long long)num);
    str->append(buf);
}

void AppendEscapedStringTo(std::string* str, const Slice& value) {
    for (size_t i = 0; i < value.size(); i++) {
        char c = value[i];
        if (c >= ' ' && c <= '~') {
            str->push_back(c);
        } else {
            char buf[10];
            snprintf(buf, sizeof(buf), "\\x%02x", static_cast<unsigned int>(c) & 0xff);
            str->append(buf);
        }
    }
}

std::string NumberToString(uint64_t num) {
    std::string r;
    AppendNumberTo(&r, num);
    return r;
}

std::string EscapeString(const Slice& value) {
    std::string r;
    AppendEscapedStringTo(&r, value);
    return r;
}

bool ConsumeDecimalNumber(Slice* in, uint64_t* val) {
    constexpr const uint64_t kMaxUint64 = std::numeric_limits<uint64_t>::max();
    constexpr const char kLastDigitOfMaxUint64 = '0' + static_cast<char>(kMaxUint64 % 10);

    uint64_t value = 0;

    const unsigned char* start = reinterpret_cast<const unsigned char*>(in->data());

    const unsigned char* end = start + in->size();
    const unsigned char* current = start;
    for ( ; current != end; ++current) {
        const unsigned char ch = *current;
        if (ch < '0' || ch > '9') {
            break;

        if (value > kMaxUint64 /10 || 
            (value == kMaxUint64 /10 && ch > kLastDigitOfMaxUint64)) {
                return false;
            }

            value = (value * 10) + (ch - '0');
        }

        *val = value;
        const size_t digits_consumed = current - start;
        in->remove_prefix(digits_consumed);
        return digits_consumed != 0;
    }

}


}