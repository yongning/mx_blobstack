#ifndef _INCLUDE_ENV_H_
#define _INCLUDE_ENV_H_

#include <stdarg.h>
#include <stdint.h>
#include <string>
#include <vector>
#include "Status.h"

namespace mx_blobstack {

class FileLock;
class Logger;
class RandomAccessFile;
class SequentialFile;
class Slice;
class WritableFile;

class Env {
public:
    Env() = default;

    Env(const Env&) = delete;
    Env& operator==(const Env&) = delete;

    virtual ~Env();

    static Env* Default();

    virtual Status NewSequentialFile(const std::string& fname,
                        SequentialFile** result) = 0;

    virtual Status NewRandomAccessFile(const std::string& fname,
                        RandomAccessFile** result) = 0;

    
};

}


#endif