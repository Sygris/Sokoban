#include "Player.h"

#include "TextureManager.h"
#include "Map.h"
#include "Input.h"
#include "Timer.h"

Player::Player(SDL_Renderer* renderer, const std::string& filename, Vector2D position, Vector2D size, Vector2D velocity, Input* input, Audio* audio, Map* map, int playerID)
	: GameObject(renderer, filename, position, size), m_velocity{ velocity }, m_input{ input }, m_sounds{ audio }, m_map{ map }, m_playerID{ playerID }
{
}

Player::~Player()
{
}

void Player::HandleEvents()
{
	if (m_input->IsControllerButtonPressed(static_cast<Controllers>(m_playerID), SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
		m_input->IsControllerButtonHeld(static_cast<Controllers>(m_playerID), SDL_CONTROLLER_BUTTON_DPAD_LEFT))
	{
		Left();
	}
	else if (m_input->IsControllerButtonPressed(static_cast<Controllers>(m_playerID), SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ||
		m_input->IsControllerButtonHeld(static_cast<Controllers>(m_playerID), SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		Right();
	}
	else if (m_input->IsControllerButtonPressed(static_cast<Controllers>(m_playerID), SDL_CONTROLLER_BUTTON_DPAD_UP) ||
		m_input->IsControllerButtonHeld(static_cast<Controllers>(m_playerID), SDL_CONTROLLER_BUTTON_DPAD_UP))
	{
		Up();
	}
	else if (m_input->IsControllerButtonPressed(static_cast<Controllers>(m_playerID), SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
		m_input->IsControllerButtonHeld(static_cast<Controllers>(m_playerID), SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		Down();
	}
	else
	{
		m_currentState = IDLE;
	}
}

void Player::Update()
{
	switch (m_currentState)
	{
	case IDLE:
		Animate(IDLE);
		break;
	case UP:
		Animate(UP);
		break;
	case RIGHT:
		Animate(RIGHT);
		break;
	case DOWN:
		Animate(DOWN);
		break;
	case LEFT:
		Animate(LEFT);
		break;
	default:
		break;
	}

	m_dstRect.x = (int)m_position.x;
	m_dstRect.y = (int)m_position.y;
}

void Player::Draw()
{
	SDL_RenderCopy(m_renderer, m_texture, &m_srcRect, &m_dstRect);
}

#pragma region Animation Functions

void Player::Animate(PlayerStates state)
{
	int sizeX, sizeY;

	SDL_QueryTexture(m_texture, NULL, NULL, &sizeX, &sizeY);

	m_srcRect.x = m_srcRect.w * (int)((SDL_GetTicks() / m_animationSpeed) % (sizeX / (int)m_size.x));
	m_srcRect.y = m_size.y * state;
}
#pragma endregion


#pragma region Movement Functions
void Player::Up()
{
	int y = m_position.y - (m_velocity.y * Timer::GetInstance()->GetDeltaTime());

	if (!m_map->IsWall(m_position.x, y) && !m_map->IsWall(m_position.x + (m_size.x - 1), y))
	{
		m_position.y = y;
		m_currentState = UP;
	}
}

void Player::Down()
{
	int y = m_position.y + (m_velocity.y * Timer::GetInstance()->GetDeltaTime());

	if (!m_map->IsWall(m_position.x, y + (m_size.y - 1)) && !m_map->IsWall(m_position.x + (m_size.x - 1), y + (m_size.y - 1)))
	{
		m_position.y = y;
		m_currentState = DOWN;
	}
}

void Player::Right()
{
	float x = m_position.x + (m_velocity.x * Timer::GetInstance()->GetDeltaTime());

	if (!m_map->IsWall(x + (m_size.x - 1), m_position.y) && !m_map->IsWall(x + (m_size.x - 1), m_position.y + m_size.y - 1))
	{
		m_position.x = x;
		m_currentState = RIGHT;
	}
}

void Player::Left()
{
	int x = m_position.x - (m_velocity.x * Timer::GetInstance()->GetDeltaTime());

	if (!m_map->IsWall(x, m_position.y) && !m_map->IsWall(x, m_position.y + (m_size.y - 1)))
	{
		m_position.x = x;
		m_currentState = LEFT;
	}
}
#pragma endregion
