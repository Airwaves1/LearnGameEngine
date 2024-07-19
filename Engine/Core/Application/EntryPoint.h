#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#ifdef AW_PLATFORM_WINDOWS

extern Airawve::Application* Airawve::CreateApplication();

int main(int argc, char** argv)
{
    // Airawve::Log::Init();
    auto app = Airawve::CreateApplication();
    app->Run();
    delete app;

    return 0;
}
#endif // AW_PLATFORM_WINDOWS


#endif // ENTRYPOINT_H