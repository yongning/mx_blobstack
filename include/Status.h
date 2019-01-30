#ifndef _INCLUDE_STATUS_H_
#define _INCLUDE_STATUS_H_

#include <algorithm>
#include <string>
#include "Slice.h"

namespace mx_blobstack {

class Status {
public:
    Status() : m_state_(nullptr) { }
    ~Status() { delete[] m_state_; }
private:
    // Ok status has a null m_state_. Otherwise, m_state is a new[] array
    // of the following form:
    // m_state_[0...3] == lenght of message
    // m_state_[4] == code
    // m_state_[5] == message
    const char* m_state_;

    enum Code {
        kOk = 0,
        kNotFound = 1,
        kCorruption = 2,
        kNotSupported = 3,
        kInvalidArgument = 4,
        kIOError = 5
    };

    Code code() const {
        return (m_state_ == nullptr) ? kOk : static_cast<Code>(m_state_[4]);
    }

    Status(Code code, const Slice& msg, const Slice& msg2);
    static const char* CopyState(const char* s);

};

}

#endif