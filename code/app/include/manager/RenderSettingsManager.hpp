#pragma once
#ifndef __NR_RENDER_SETTINGS_MANAGER_HPP__
#define __NR_RENDER_SETTINGS_MANAGER_HPP__

#include "scene/Camera.hpp"

namespace NRenderer
{
    //������Ⱦ����
    struct RenderSettings
    {
        //���ߣ���
        unsigned int width;
        unsigned int height;
        unsigned int depth;

        //������
        unsigned int samplesPerPixel;
        RenderSettings()
            : width             (500)
            , height            (500)
            , depth             (4)
            , samplesPerPixel   (16)
        {}
    };

    //����������
    struct AmbientSettings
    {
        //�̶���ɫ��ʹ������
        enum Type
        {
            CONSTANT, ENVIROMENT_MAP
        };
        //����������ͣ�
        Type type = Type::CONSTANT;
        //��ɫ
        RGB ambient = {0, 0, 0};
        //��ͼ
        Handle mapTexture = {};
    };
    //�������
    struct RenderSettingsManager
    {
        //ͳһ�����������Ⱦ���ã�����������
        Camera camera = {};
        RenderSettings renderSettings = {};
        AmbientSettings ambientSettings = {};
    };
    
}

#endif