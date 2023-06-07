#pragma once
#ifndef __NR_COMPONENT_MANAGER_HPP__
#define __NR_COMPONENT_MANAGER_HPP__

#include <Windows.h>
#include <vector>
#include <chrono>
#include <thread>

#include "component/RenderComponent.hpp"
#include "server/Server.hpp"

namespace NRenderer
{
    using namespace std;
    class DLL_EXPORT ComponentManager
    {
    public:
        //插件的状态：空闲，准备就绪，运行中，运行完成
        enum class State
        {
            IDLING,
            READY,
            RUNNING,
            FINISH
        };
    private:
        //当前插件的状态
        State state;
        //已经加载的动态链接库
        vector<HMODULE> loadedDlls;
        //插件的信息
        ComponentInfo activeComponent;
        //上次开始执行时间和上次结束执行时间
        chrono::system_clock::time_point lastStartTime;
        chrono::system_clock::time_point lastEndTime;
        thread t;
    public:
        ComponentManager();
        ~ComponentManager();

        //加载指定路径下的动态链接库，获取其中的组件信息
        void init(const string& dllPath);
        
        ComponentInfo getActiveComponentInfo() const;
        
        template<typename Interface, typename ...Args>

        //执行某一插件
        void exec(const ComponentInfo& componentInfo, Args... args) {
            //创建对应类型的组件实例
            auto component = getServer().componentFactory.createComponent<Interface>(componentInfo.type, componentInfo.name);
            activeComponent = componentInfo;
            this->state = State::READY;
            //调用新的线程，执行组件的exec函数
            try {
                t = thread(&Interface::exec,
                    component, 
                    [this]() -> void {
                        this->state = State::RUNNING;
                        this->lastStartTime = chrono::system_clock::now();
                    },
                    [this]() -> void {
                        this->state = State::FINISH;
                        this->lastEndTime = chrono::system_clock::now();
                    },
                    std::forward<Args>(args)...);
                    t.detach();
            }
            catch(const exception& e) {
                cerr<<"Unexpected termination"<<endl;
                cerr<<e.what()<<endl;
            }
        }
    
        void finish();

        State getState() const;

        chrono::duration<double> getLastExecTime() const;
    };
} // namespace NRenderer


#endif