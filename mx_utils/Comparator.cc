#include <algorithm>
#include <cstdint>
#include <string>

#include "Comparator.h"
#include "Slice.h"
#include "mx_utils/logging.h"
#include "mx_utils/no_destructor.h"

namespace mx_blobstack {

Comparator::~Comparator() {}

namespace {
    
class BytewiseComparatorImpl : public Comparator {
public:
    BytewiseComparatorImpl() {}
    
    virtual const char* Name() const {
        return "mx_blobstack.BytewiseComparator";
    }

    virtual int Compare(const Slice& a, const Slice& b) const {
        return a.compare(b);
    }

    virtual void FindShortestSeparator(std::string* start, const Slice& limit) const {
        size_t min_length = std::min(start->size(), limit.size());
        size_t diff_index = 0;
        while ((diff_index < min_length) && 
            ((*start)[diff_index] == limit[diff_index])) {
                diff_index++;
            }
        
        if (diff_index >= min_length) {

        }
    }
}
}
}