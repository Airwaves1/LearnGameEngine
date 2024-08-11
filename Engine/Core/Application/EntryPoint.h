#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "Application.h"

#ifdef AW_PLATFORM_WINDOWS || AW_PLATFORM_LINUX || AW_PLATFORM_MACOS

extern Airwave::Application* Airwave::CreateApplication();

int main(int argc, char** argv)
{
    // LOG_INFO("Airwave Engine Log System Initialized");
    auto app = Airwave::CreateApplication();

    app->Run();
 
    delete app;

    return 0;
}
#endif // AW_PLATFORM_WINDOWS


#endif // ENTRYPOINT_H