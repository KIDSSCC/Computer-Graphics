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
        //�����״̬�����У�׼�������������У��������
        enum class State
        {
            IDLING,
            READY,
            RUNNING,
            FINISH
        };
    private:
        //��ǰ�����״̬
        State state;
        //�Ѿ����صĶ�̬���ӿ�
        vector<HMODULE> loadedDlls;
        //�������Ϣ
        ComponentInfo activeComponent;
        //�ϴο�ʼִ��ʱ����ϴν���ִ��ʱ��
        chrono::system_clock::time_point lastStartTime;
        chrono::system_clock::time_point lastEndTime;
        thread t;
    public:
        ComponentManager();
        ~ComponentManager();

        //����ָ��·���µĶ�̬���ӿ⣬��ȡ���е������Ϣ
        void init(const string& dllPath);
        
        ComponentInfo getActiveComponentInfo() const;
        
        template<typename Interface, typename ...Args>

        //ִ��ĳһ���
        void exec(const ComponentInfo& componentInfo, Args... args) {
            //������Ӧ���͵����ʵ��
            auto component = getServer().componentFactory.createComponent<Interface>(componentInfo.type, componentInfo.name);
            activeComponent = componentInfo;
            this->state = State::READY;
            //�����µ��̣߳�ִ�������exec����
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