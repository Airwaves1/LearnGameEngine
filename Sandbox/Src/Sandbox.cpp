#include <AirwaveEngine.h>
class Sandbox : public Airawve::Application
{
public:
    Sandbox()
    {
    }

    ~Sandbox()
    {
    }
};

Airawve::Application* Airawve::CreateApplication()
{
    return new Sandbox();
}