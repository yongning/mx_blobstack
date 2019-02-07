#ifndef _UTILS_LOGGING_H_
#define _UTILS_LOGGING_H_

#include <stdio.h>
#include <stdint.h>
#include <string>
#include "port/Port_stdcxx.h"

namespace mx_blobstack {

class Slice;
class WritableFile;

void AppendNumberTo(std::string* str, uint64_t num);

void AppendEscapedStringTo(std::string* str, const Slice& value);

std::string NumberToString(uint64_t num);

std::string EscapeString(const Slice& value);

bool ConsumeDecimalNumber(Slice* in, uint64_t* val);

}

#endif