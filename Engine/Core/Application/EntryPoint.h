#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#ifdef AW_PLATFORM_WINDOWS

extern Airawve::Application* Airawve::CreateApplication();

int main(int argc, char** argv)
{
    Airwave::Log::Init();
    LOG_INFO("Airwave Engine Log System Initialized");
    auto app = Airawve::CreateApplication();
    app->Run();
    delete app;

    return 0;
}
#endif // AW_PLATFORM_WINDOWS


#endif // ENTRYPOINT_H