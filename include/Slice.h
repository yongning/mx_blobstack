#ifndef _INCLUDE_SLICE_H_
#define _INCLUDE_SLICE_H_

#include <assert.h>
#include <stddef.h>
#include <string>
#include <string.h>

namespace mx_blobstack {

class Slice {
public:
    Slice() : m_data_(""), m_size_(0) { }
    Slice(const char* d, size_t n) : m_data_(d), m_size_(n) { }
    Slice(const std::string& s) : m_data_(s.data()), m_size_(s.size()) { }

    Slice(const Slice&) = default;
    Slice& operator=(const Slice&) = default;

    const char* data() const { return m_data_; }

    size_t size() const { return m_size_; };

    bool empty() const { return m_size_ == 0; }

    char operator[](size_t n) const {
        assert(n < size());
        return m_data_[n];
    }

    void clear() { m_data_ = ""; m_size_ = 0; }

    void remove_prefix(size_t n) {
        assert(n <= size());
        m_data_ += n;
        m_size_ -= n;
    }

    std::string ToString() const { return std::string(m_data_, m_size_); }

    int compare(const Slice&b) const;

    bool starts_with(const Slice& x) const {
        return ((m_size_ >= x.size()) &&
            (memcmp(m_data_, x.data(), x.size()) == 0));
    }

private:
    const char* m_data_;
    size_t m_size_;
};

inline bool operator==(const Slice& x, const Slice& y) {
    return ((x.size() == y.size()) &&
        (memcmp(x.data(), y.data(), x.size()) == 0));
}

inline bool operator!=(const Slice&x, const Slice&y) {
    return !(x == y);
}

inline int Slice::compare(const Slice&b) const {
    const size_t min_len = (m_size_ < b.size()) ? m_size_ : b.size();
    int r = memcmp(m_data_, b.data(), min_len);
    if (r == 0) {
        if (m_size_ < b.size()) r = -1;
        else if (m_size_ > b.size()) r = +1;
    }
    return r;
}

}


#endif