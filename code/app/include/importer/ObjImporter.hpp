#pragma once
#ifndef __OBJ_IMPORTER_HPP__
#define __OBJ_IMPORTER_HPP__

#include "Importer.hpp"
#include <map>

#include <unordered_map>

namespace NRenderer
{
    using namespace std;
    class ObjImporter: public Importer
    {
    private:
        //mtl是材质相关文件，parseMtl可以解析mtl文件并将材质信息保存到asset对象中
        bool parseMtl(Asset& asset, const string& path, ifstream& file, unordered_map<string, size_t>& mtlMap);
    public:
        //重写了import函数，可以将obj文件导入到场景中，
        //解析obj文件中的顶点，法向量，平面信息，如果有需要，调用parseMtl进行材质的解析
        virtual bool import(Asset& asset, const string& path) override;
    };
}

#endif