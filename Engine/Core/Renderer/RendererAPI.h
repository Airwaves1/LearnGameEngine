#ifndef RENDERERAPI_H
#define RENDERERAPI_H

#include "Utils/Common.h"
#include <glm/glm.hpp>
#include "Renderer/VertexArray.h"

namespace Airwave
{
    class RendererAPI
    {
    public:
        enum class APIType
        {
            None = 0,
            OpenGL = 1
        };

    public:
        // 把相关代码抽象成以下三个接口，放在RenderAPI类里, 这些都是抽象接口, 具体会通过创建一个与平台相关的子类的
        // RendererAPI的静态对象, 比如OpenGLRenderer, 然后把RenderCommand作为一个Wrapper, 将其接口暴露出来
        virtual void Init() const = 0;
        virtual void Clear() const = 0;
        virtual void SetClearColor(const glm::vec4 &) const = 0;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray> &, uint32_t count) const = 0; // count为0则绘制整个IndexBuffer

        virtual void OnViewportResize(uint32_t width, uint32_t height) const = 0;

        inline static APIType GetAPIType() { return s_CurType; }
        inline static void SetAPIType(APIType type) { s_CurType = type; }

    private:
        static APIType s_CurType;
    };

} // namespace Airwave

#endif // RENDERERAPI_H