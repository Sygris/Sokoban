#pragma once

#if _DEBUG
#include "MemoryManager.h"
#endif // DEBUG


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

