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
        //mtl�ǲ�������ļ���parseMtl���Խ���mtl�ļ�����������Ϣ���浽asset������
        bool parseMtl(Asset& asset, const string& path, ifstream& file, unordered_map<string, size_t>& mtlMap);
    public:
        //��д��import���������Խ�obj�ļ����뵽�����У�
        //����obj�ļ��еĶ��㣬��������ƽ����Ϣ���������Ҫ������parseMtl���в��ʵĽ���
        virtual bool import(Asset& asset, const string& path) override;
    };
}

#endif