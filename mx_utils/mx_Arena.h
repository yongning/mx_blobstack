#ifndef _UTILS_ARENA_H_
#define _UTILS_ARENA_H_

#include <vector>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

namespace mx_blobstack {

class Arena {
public:
private:
    char* AllocateFallback(size_t bytes);
    char* AllocateNewBlock(size_t block_size);

    char* m_alloc_ptr_;
    size_t m_alloc_bytes_remaining_;

    std::vector<char*> m_blocks_;

    
};
}


#endif