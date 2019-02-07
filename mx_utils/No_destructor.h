#ifndef _UTILS_NO_DESTRUCTOR_H_
#define _UTILS_NO_DESTRUCTOR_H_

#include <type_traits>
#include <utility>

namespace mx_blobstack {

template<typename InstanceType>
class NoDestructor {
public:
    template<typename... ConstructorArgTypes>
    explicit NoDestructor(ConstructorArgType&&... constructor_args) {
     //   static_assert(sizeof(m_instance_storage_) >= sizeof(InstanceType),
     //                   "instance_storage_ is not large enough to hold the instance");
     //   static_assert(alignof(decltype(m_instance_storage_)) >= alignof(InstanceType),
     //                   "instance_storage_ does not meet the instance's alignment requirement");
        new(&m_instance_storage_) InstanceType(
            std::forward<ConstructorArgTypes>(constructor_args)...);
    }

    ~NoDestructor() = default;

    NoDestructor(const NoDestructor&) = delete;
    NoDestructor& operator=(const NoDestructor&) = delete;

    InstanceType* get() {
        return reinterpret_cast<InstanceType*>(&m_instance_storage_);
    }

private:
    typename std::aligned_storage<sizeof(InstanceType), alignof(InstanceType)>::type m_instance_storage_;
};

}

#endif