#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdint>
#include <memory>
#include <vector>

#include "Renderer/Shaders/Shader.h"

namespace Airwave
{

    struct FramebufferSpecification
    {
        uint32_t colorAttachmentCount = 1;
        uint32_t depthAttachmentCount = 1;
        uint32_t stencilAttachmentCount = 0;
        bool enableMSAA = false;

        FramebufferSpecification(uint32_t colorAttachmentCount = 1, uint32_t depthAttachmentCount = 1, uint32_t stencilAttachmentCount = 0, bool enableMSAA = false)
            : colorAttachmentCount(colorAttachmentCount), depthAttachmentCount(depthAttachmentCount), stencilAttachmentCount(stencilAttachmentCount), enableMSAA(enableMSAA)
        {
        }
    };

    class Framebuffer
    {
    public:
        static std::shared_ptr<Framebuffer> Create(uint32_t width = 800, uint32_t height = 600, FramebufferSpecification specification = FramebufferSpecification());
        virtual ~Framebuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual uint32_t GetFramebufferID() const = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;

        // 获取纹理附件的ID
        virtual std::vector<uint32_t> GetColorAttachmentIDs() const = 0;
        virtual uint32_t GetDepthAttachmentID() const = 0;
        virtual uint32_t GetStencilAttachmentID() const = 0;

        // 设置多重采样
        virtual void SetMSAA(bool enable) = 0;

        // 将多重采样的纹理附件转换为普通纹理附件
        virtual void BlitMSAAToDefaultFramebuffer(const uint32_t resolveFramebufferID) const = 0;

        //读取像素，获取单点颜色
        virtual uint32_t ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

        // 渲染到全屏四边形上
        virtual void RenderToFullScreenQuad(std::shared_ptr<Shader> shader) = 0;

    protected:
        uint32_t m_Width;
        uint32_t m_Height;
        FramebufferSpecification m_Specification;
        
        // 全屏帧缓冲 
        std::shared_ptr<Framebuffer> m_FullScreenFramebuffer;
    };
}

#endif // FRAMEBUFFER_H