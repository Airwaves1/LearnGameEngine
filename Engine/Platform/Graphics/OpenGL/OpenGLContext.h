#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H

#include "Graphics/GraphicsContext.h"

struct GLFWwindow;

namespace Airwave
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow *windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow *m_WindowHandle;
    };
} // namespace Airwave

#endif // OPENGL_CONTEXT_H