// #include "ImGui/ImGuiLayer.h"
// #include "Utils/Common.h"

// #include "Application/Application.h"

// #include "imgui.h"
// #include "backends/imgui_impl_opengl3.h"
// #include "backends/imgui_impl_glfw.h"

// #include <glad/glad.h>
// #include <glfw/glfw3.h>

// namespace Airwave
// {

//     ImGuiLayer::ImGuiLayer()
//         : Layer("ImGuiLayer")
//     {
//     }

//     ImGuiLayer::~ImGuiLayer()
//     {
//     }

//     void ImGuiLayer::OnAttach()
//     {
//         IMGUI_CHECKVERSION();
//         ImGui::CreateContext();
//         ImGui::StyleColorsDark();

//         ImGuiIO &io = ImGui::GetIO();
//         io.ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;
//         io.ConfigFlags |= ImGuiBackendFlags_HasSetMousePos;

//         ImGui_ImplOpenGL3_Init("#version 460");
//     }

//     void ImGuiLayer::OnDetach()
//     {
//     }

//     void ImGuiLayer::OnImGuiRender()
//     {
//     }

//     void ImGuiLayer::OnEvent(Event &)
//     {
//     }

//     void ImGuiLayer::Begin()
//     {
//         ImGuiIO &io = ImGui::GetIO();
//         Application &app = Application::Get();
//         io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

//         float time = (float)glfwGetTime();
//         io.DeltaTime = m_Time > 0.0 ? (float)(time - m_Time) : 1.0f / 60.0f;
//         m_Time = time;

//         ImGui_ImplOpenGL3_NewFrame();
//         ImGui::NewFrame();

//         static bool show = true;
//         ImGui::ShowDemoWindow(&show);

//         ImGui::Render();
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//     }

//     void ImGuiLayer::End()
//     {
//     }

// }