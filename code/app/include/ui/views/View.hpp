#pragma once
#ifndef __NR_VIEW_HPP__
#define __NR_VIEW_HPP__

#include "ui/UIContext.hpp"
#include "manager/Manager.hpp"
#include "geometry/vec.hpp"
#include "imgui.h"

namespace NRenderer
{
    class View
    {
    protected:
        //大小与位置
        Vec2 position;
        Vec2 size;

        //UI上下文和manager
        UIContext& uiContext;
        Manager& manager;

        //是否被禁用，是否可见，是否能够改变大小
        bool disable;
        bool visible;
        bool resizable;

        ImGuiWindowFlags windowFlag = 0;

        virtual void drawSetup();
        virtual void drawFinish();

        virtual void drawPosAndSize();

        virtual void drawBeginWindow() = 0;
        virtual void drawEndWindow();

        virtual void draw() = 0;

        void makeHelper(const char* desc);
    public:
        View(const Vec2& position, const Vec2& size, UIContext& uiContext, Manager& manager);
        View(const View&) = delete;
        
        void display();
        
        inline
        void setVisibility(bool flag) {
            visible = flag;
        }
        inline
        void setDisable(bool flag) {
            disable = flag;
        }
        inline
        void setResizable(bool flag) {
            resizable = flag;
        }
    };
} // namespace NRenderer


#endif