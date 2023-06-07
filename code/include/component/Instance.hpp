#pragma once
#ifndef __NR_INSTANCE_HPP__
#define __NR_INSTANCE_HPP__

#include <memory>
#include "common/macros.hpp"

namespace NRenderer
{
    using namespace std;
    //使派生类能够创建自己的智能指针
    struct DLL_EXPORT Instance: public enable_shared_from_this<Instance>
    {
        virtual ~Instance() = default;
    };
    //类型别名
    using SharedInstance = shared_ptr<Instance>;
}

#endif