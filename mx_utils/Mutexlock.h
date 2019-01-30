#ifndef _UTILS_MUTEXLOCK_H_
#define _UTILS_MUTEXLOCK_H_

#include "port/Port_stdcxx.h"

namespace mx_blobstack {

class MutexLock {
public:
    explicit MutexLock(port::Mutex* mu) : m_mu_(mu) {
        this->m_mu_->Lock();
    }

    ~MutexLock() { this->m_mu_->Unlock(); }

    MutexLock(const MutexLock&) = delete;
    MutexLock& operator=(const MutexLock&) = delete;

private:
    port::Mutex* const m_mu_;
};

}

#endif