#include "MenuState.h"
#include "PlayState.h"

#include "../Util/MessageHandler.h"

#include "../Input.h"
#include "../Audio.h"

#include <iostream>

MenuState MenuState::s_menuState;

void MenuState::Init()
{
	m_input = new Input();

	Util::MessageHandler message;

	if (!m_input->IsControllerInitialised())
	{
		message.ShowMessage(Util::messageType::CONTROLLER_WARNING);
	}
}

void MenuState::Clean()
{
	delete m_input;
	m_input = nullptr;
}

void MenuState::Pause()
{
	std::cout << __FUNCTION__ << std::endl;
}

void MenuState::Resume()
{
	std::cout << __FUNCTION__ << std::endl;
}

void MenuState::HandleEvents(Application* application)
{
	m_input->Update();

	if (m_input->IsButtonPressed(B))
	{
		application->Quit();
	}
	else if (m_input->IsButtonPressed(A))
	{
		application->ChangeState(PlayState::Instance());
	}
	else if (m_input->IsButtonPressed(Y))
	{
		application->m_sounds->PlaySFX(0, 0, 0);
	}
	else if (m_input->IsButtonPressed(X))
	{
		application->m_sounds->FadeMusicTrack(1, 1, 200);
	}
}

void MenuState::Update(Application* application)
{
	application->GetRenderer()->SetDisplayColour(255, 0, 0, 0);
}

void MenuState::Draw(Application* application)
{
	application->GetRenderer()->Update();
}

MenuState::MenuState()
{
}
