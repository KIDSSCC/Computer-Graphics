#pragma once
#ifndef __NR_MANAGER_HPP__
#define __NR_MANAGER_HPP__

#include "AssetManager.hpp"
#include "RenderSettingsManager.hpp"
#include "ComponentManager.hpp"

namespace NRenderer
{
    //具体包含AssetManager，RenderSettingsManager，ComponentManager
    //提供一个统一的访问入口
    class Manager
    {
    public:
        AssetManager assetManager;
        RenderSettingsManager renderSettingsManager;
        ComponentManager componentManager;
        Manager();
        ~Manager() = default;
    };
} // namespace NRenderer


#endif