#pragma once
#ifndef __NR_IMPORTER_HPP__
#define __NR_IMPORTER_HPP__

#include <string>
#include "asset/Asset.hpp"

namespace NRenderer
{
    using namespace std;
    class Importer
    {
    protected:
        //发生错误时的错误信息
        string lastErrorInfo;
    public:
        //返回一个bool值代表是否导入成功
        virtual bool import(Asset& asset, const string& path) = 0;
        inline
        string getErrorInfo() const {
            return lastErrorInfo;
        }
        Importer()
            : lastErrorInfo         ()
        {}
        virtual ~Importer() = default;
    };
    //可共享智能指针
    SHARE(Importer);
}

#endif