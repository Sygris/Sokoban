#pragma once

#include "Renderer.h"

class Application
{
public:
	Application();
	~Application();

	void Run();
	void Destroy();

private:
	Renderer* m_renderer{ nullptr };
};

