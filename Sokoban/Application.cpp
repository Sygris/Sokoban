#include "Application.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::Run()
{
	m_renderer = new Renderer();

	if (m_renderer)
	{
		Uint8 r = 255, g = 0, b = 0, a = 255;

		m_renderer->SetDisplayColour(r, g, b, a);
		m_renderer->Update();
		m_renderer->Delay(5000);

		m_renderer->Destroy();
		Destroy();
	}
}

void Application::Destroy()
{
	delete m_renderer;
	m_renderer = nullptr;
}
