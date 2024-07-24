#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "Base/Layer.h"
#include "Event/Event.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

namespace Airwave
{

    class ImGuiLayer : public Layer
    {

    public:
        ImGuiLayer();
        ~ImGuiLayer();

		void OnAttach() override; //当layer添加到layer stack的时候会调用此函数，相当于Init函数
		void OnDetach() override; //当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
		void OnImGuiRender(float deltaTime) override; //当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
		void OnEvent(Event&) override;

        void Begin();
        void End();

    private:

    private:
        float m_Time = 0.0f;

    };

}

#endif // IMGUI_LAYER_H