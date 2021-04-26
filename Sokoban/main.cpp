#include "Application.h"
#include <iostream>
#include <ostream>

int main(int argc, char* argv[])
{
	Application* App = new Application();
	App->Run();

	delete App;
	App = nullptr;

	std::cout << "Press any key to continue" << std::endl;
	int c = getchar();

	return 0;
}
