#ifndef _INCLUDE_VERSION_SET_H_
#define _INCLUDE_VERSION_SET_H_

#include <map>
#include <set>
#include <vector>

namespace mx_blobstack {

namespace log { class Writer; }

class Compaction;
class Iterator;
class MemTable;
class TableBuilder;
class TableCache;
class Version;
class VersionSet;
class WritableFile;

class Version {
public:
    void AddIterators(const ReadOptions&, std::vector<Iterator*>* iters);
    
};

}



#endif