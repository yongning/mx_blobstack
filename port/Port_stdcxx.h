#ifndef _PORT_PORT_STDCXX_H_
#define _PORT_PORT_STDCXX_H_

#include <stddef.h>
#include <stdint.h>
#include <cassert>
#include <condition_variable>;
#include <mutex>
#include <string>

namespace mx_blobstack {
namespace port {

class CondVar;

class Mutex {
public:
    Mutex() = default;
    ~Mutex() = default;

    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;

    void Lock() { m_mu_.lock(); }
    void Unlock() { m_mu_.unlock(); }
    void AssertHeld () {}

private:
    friend CondVar;
    std::mutex m_mu_;
};

class CondVar {
public:
    explicit CondVar(Mutex* mu) : m_mu_(mu) { assert(mu != nullptr); }
    ~CondVar() = default;

    CondVar(const CondVar&) = delete;
    CondVar& operator=(const CondVar&) = delete;

    void Wait() {
        std::unique_lock<std::mutex> lock(m_mu_->m_mu_, std::adopt_lock);
        m_cv_.wait(lock);
        lock.release();
    }
    void Signal() { m_cv_.notify_one(); }
    void SignalAll() {m_cv_.notify_all(); }
private:
    std::condition_variable m_cv_;
    Mutex* const m_mu_;
};


}
}

#endif