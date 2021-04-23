#include "Player.h"

#include "TextureManager.h"
#include "Map.h"
#include "Input.h"
#include "Timer.h"
#include "Block.h"

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
#if _DEBUG
	SDL_Rect m_copy = m_boxCollider2D.GetBox();
	SDL_RenderDrawRect(m_renderer, &m_copy);
#endif // _DEBUG

	SDL_RenderCopy(m_renderer, m_texture, &m_srcRect, &m_dstRect);
}

#pragma region Animation Functions

void Player::Animate(PlayerStates state)
{
	int sizeX, sizeY;

	SDL_QueryTexture(m_texture, NULL, NULL, &sizeX, &sizeY);

	m_boxCollider2D.SetBox(m_position.x, m_position.y, m_size.x, m_size.y); // Updates the Collider position 
	m_boxCollider2D.SetBuffer(-4, -4, 8, 9); // Sets the buffer (how much to subtract from the collider) of the collider 

	m_srcRect.x = m_srcRect.w * (int)((SDL_GetTicks() / m_animationSpeed) % (sizeX / (int)m_size.x));
	m_srcRect.y = m_size.y * state;
}
#pragma endregion


#pragma region Movement Functions
void Player::Up()
{
	bool canMove = false;

	int y = m_boxCollider2D.GetBox().y - (m_velocity.y * Timer::GetInstance()->GetDeltaTime());

	if (!m_map->IsWall(m_boxCollider2D.GetBox().x, y) && !m_map->IsWall(m_boxCollider2D.GetBox().x + (m_boxCollider2D.GetBox().w - 1), y))
	{
		for (Block* block : Block::BlockList)
		{
			if (block->GetPosition().x <= m_boxCollider2D.GetBox().x + (m_boxCollider2D.GetBox().w - 1) &&
				block->GetPosition().x + (m_boxCollider2D.GetBox().w - 1) >= m_boxCollider2D.GetBox().x &&
				block->GetPosition().y <= y + (m_boxCollider2D.GetBox().h - 1) &&
				block->GetPosition().y + (m_boxCollider2D.GetBox().h - 1) >= y)
			{
				block->Move(0, -m_velocity.y);
				canMove = false;
				break;
			}

			canMove = true;
		}
	}

	if (canMove)
	{
		m_position.y -= m_velocity.y * Timer::GetInstance()->GetDeltaTime();
		m_currentState = UP;
	}
}

void Player::Down()
{
	bool canMove = false;

	int y = m_boxCollider2D.GetBox().y + (m_velocity.y * Timer::GetInstance()->GetDeltaTime());

	if (!m_map->IsWall(m_boxCollider2D.GetBox().x, y + (m_boxCollider2D.GetBox().h -1)) &&
		!m_map->IsWall(m_boxCollider2D.GetBox().x + (m_boxCollider2D.GetBox().w - 1), y + (m_boxCollider2D.GetBox().h - 1)))
	{
		for (Block* block : Block::BlockList)
		{
			if (block->GetPosition().x <= m_boxCollider2D.GetBox().x + (m_boxCollider2D.GetBox().w - 1) &&
				block->GetPosition().x + (m_boxCollider2D.GetBox().w - 1) >= m_boxCollider2D.GetBox().x &&
				block->GetPosition().y <= y + (m_boxCollider2D.GetBox().h - 1) &&
				block->GetPosition().y + (m_boxCollider2D.GetBox().h - 1) >= y)
			{
				block->Move(0, m_velocity.y);
				canMove = false;
				break;
			}

			canMove = true;
		}
	}

	if (canMove)
	{
		m_position.y += m_velocity.y * Timer::GetInstance()->GetDeltaTime();
		m_currentState = DOWN;
	}
}

void Player::Right()
{
	bool canMove = false;

	float x = m_boxCollider2D.GetBox().x + (m_velocity.x * Timer::GetInstance()->GetDeltaTime());

	if (!m_map->IsWall(x + (m_boxCollider2D.GetBox().w - 1), m_boxCollider2D.GetBox().y) &&
		!m_map->IsWall(x + (m_boxCollider2D.GetBox().w - 1), m_boxCollider2D.GetBox().y + (m_boxCollider2D.GetBox().h - 1)))
	{
		for (Block* block : Block::BlockList)
		{
			if (block->GetPosition().x <= x + (m_boxCollider2D.GetBox().w - 1) &&
				block->GetPosition().x + (m_boxCollider2D.GetBox().w - 1) >= x &&
				block->GetPosition().y <= m_boxCollider2D.GetBox().y + (m_boxCollider2D.GetBox().h - 1) &&
				block->GetPosition().y + (m_boxCollider2D.GetBox().h - 1) >= m_boxCollider2D.GetBox().y)
			{
				block->Move(m_velocity.x, 0);
				canMove = false;
				break;
			}

			canMove = true;
		}
	}

	if (canMove)
	{
		m_position.x += m_velocity.x * Timer::GetInstance()->GetDeltaTime();
		m_currentState = RIGHT;
	}
}

void Player::Left()
{
	bool canMove = false;

	int x = m_boxCollider2D.GetBox().x - (m_velocity.x * Timer::GetInstance()->GetDeltaTime());

	if (!m_map->IsWall(x, m_boxCollider2D.GetBox().y) &&
		!m_map->IsWall(x, m_boxCollider2D.GetBox().y + (m_boxCollider2D.GetBox().h - 1)))
	{
		for (Block* block : Block::BlockList)
		{
			if (block->GetPosition().x <= x + (m_boxCollider2D.GetBox().w - 1) &&
				block->GetPosition().x + (m_boxCollider2D.GetBox().w - 1) >= x &&
				block->GetPosition().y <= m_boxCollider2D.GetBox().y + (m_boxCollider2D.GetBox().h - 1) &&
				block->GetPosition().y + (m_boxCollider2D.GetBox().h - 1) >= m_boxCollider2D.GetBox().y)
			{
				block->Move(-m_velocity.x, 0);
				canMove = false;
				break;
			}

			canMove = true;
		}
	}

	if (canMove)
	{
		m_position.x -= m_velocity.x * Timer::GetInstance()->GetDeltaTime();
		m_currentState = LEFT;
	}
}
bool Player::CheckCollisionWithBlocks()
{
	return true;
}
#pragma endregion
