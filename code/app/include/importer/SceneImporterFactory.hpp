#pragma once
#ifndef __NR_SCENE_IMPORTER_FACTORY_HPP__
#define __NR_SCENE_IMPORTER_FACTORY_HPP__

#include <string>
#include <unordered_map>

#include "Importer.hpp"
#include "ScnImporter.hpp"
#include "ObjImporter.hpp"

namespace NRenderer
{
    using namespace std;
    //不同格式的场景导入器
    class SceneImporterFactory
    {
    private:
        //无序映射表，存储文件扩展名和对应的导入器对象
        unordered_map<string, SharedImporter> importerMap;
    public:
        //单例模式，运行期间只能存在一个该类对象
        static SceneImporterFactory& instance() {
            static SceneImporterFactory f;
            return f;
        }
        SceneImporterFactory() {
            //对不同后缀的文件，采用不同的对象进行解析
            importerMap["scn"] = make_shared<ScnImporter>();
            importerMap["obj"] = make_shared<ObjImporter>();
        }
        //根据后缀名返回对应的importer
        SharedImporter importer(const string& ext) {
            auto it = importerMap.find(ext);
            if (it!=importerMap.end()) {
                return it->second;
            }
            return nullptr;
        }
    };
}

#endif