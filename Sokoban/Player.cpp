#include "Player.h"

#include "TextureManager.h"
#include "Map.h"
#include "Input.h"
#include "Timer.h"
#include "Block.h"
#include "CollisionHandler.h"

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
	SDL_Rect copy; /*= m_colliderBody.GetBox();
	SDL_RenderDrawRect(m_renderer, &copy);*/

	copy = m_colliderLeft.GetBox();
	SDL_RenderDrawRect(m_renderer, &copy);

	copy = m_colliderRight.GetBox();
	SDL_RenderDrawRect(m_renderer, &copy);

	copy = m_colliderTop.GetBox();
	SDL_RenderDrawRect(m_renderer, &copy);

	copy = m_colliderDown.GetBox();
	SDL_RenderDrawRect(m_renderer, &copy);
#endif // _DEBUG

	SDL_RenderCopy(m_renderer, m_texture, &m_srcRect, &m_dstRect);
}

#pragma region Animation Functions

void Player::Animate(PlayerStates state)
{
	int sizeX, sizeY;

	SDL_QueryTexture(m_texture, NULL, NULL, &sizeX, &sizeY);

	UpdateBoxColliders();

	m_srcRect.x = m_srcRect.w * (int)((SDL_GetTicks() / m_animationSpeed) % (sizeX / (int)m_size.x));
	m_srcRect.y = m_size.y * state;
}
#pragma endregion

#pragma region Movement Functions
void Player::Up()
{
	bool canMove = false;

	int y = m_colliderBody.GetBox().y - (m_velocity.y * Timer::GetInstance()->GetDeltaTime());
	int boxCollisionY = y - m_colliderBody.GetBox().y + m_colliderTop.GetBox().y;

	SDL_Rect temp = { m_colliderTop.GetBox().x, boxCollisionY, m_colliderTop.GetBox().w, m_colliderTop.GetBox().h };

	if (!m_map->IsWall(m_colliderBody.GetBox().x, y) && !m_map->IsWall(m_colliderBody.GetBox().x + (m_colliderBody.GetBox().w - 1), y))
	{
		for (Block* block : Block::BlockList)
		{
			if (CollisionHandler::AABB(block->GetRect(), temp))
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

	int y = m_colliderBody.GetBox().y + (m_velocity.y * Timer::GetInstance()->GetDeltaTime());
	int boxCollisionY = m_colliderDown.GetBox().y + (m_velocity.y * Timer::GetInstance()->GetDeltaTime());

	SDL_Rect temp = { m_colliderDown.GetBox().x, boxCollisionY, m_colliderDown.GetBox().w, m_colliderDown.GetBox().h };

	if (!m_map->IsWall(m_colliderBody.GetBox().x, y + (m_colliderBody.GetBox().h - 1)) &&
		!m_map->IsWall(m_colliderBody.GetBox().x + (m_colliderBody.GetBox().w - 1), y + (m_colliderBody.GetBox().h - 1)))
	{
		for (Block* block : Block::BlockList)
		{
			if (CollisionHandler::AABB(block->GetRect(), temp))
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

	int x = m_colliderBody.GetBox().x + (m_velocity.x * Timer::GetInstance()->GetDeltaTime());
	int boxCollisionX = x - m_colliderBody.GetBox().x + m_colliderRight.GetBox().x;

	SDL_Rect temp = { boxCollisionX, m_colliderRight.GetBox().y, m_colliderRight.GetBox().w, m_colliderRight.GetBox().h };

	if (!m_map->IsWall(x + (m_colliderBody.GetBox().w - 1), m_colliderBody.GetBox().y) &&
		!m_map->IsWall(x + (m_colliderBody.GetBox().w - 1), m_colliderBody.GetBox().y + (m_colliderBody.GetBox().h - 1)))
	{
		for (Block* block : Block::BlockList)
		{
			if (CollisionHandler::AABB(block->GetRect(), temp))
			{
				block->Move(m_velocity.x, m_position.y);
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

	int x = m_colliderBody.GetBox().x - (m_velocity.x * Timer::GetInstance()->GetDeltaTime());
	int boxCollisionX = x - m_colliderBody.GetBox().x + m_colliderLeft.GetBox().x;

	SDL_Rect temp = { boxCollisionX, m_colliderLeft.GetBox().y, m_colliderLeft.GetBox().w, m_colliderLeft.GetBox().h };

	if (!m_map->IsWall(x, m_colliderBody.GetBox().y) &&
		!m_map->IsWall(x, m_colliderBody.GetBox().y + (m_colliderBody.GetBox().h - 1)))
	{
		for (Block* block : Block::BlockList)
		{
			if (CollisionHandler::AABB(block->GetRect(), temp))
			{
				block->Move(-m_velocity.x, m_velocity.y);
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
#pragma endregion

#pragma region Colliders 
void Player::UpdateBoxColliders()
{
	// Updates the Collider position to the entire visible body of the player
	m_colliderBody.SetBox((int)(m_position.x), (int)(m_position.y), (int)(m_size.x), (int)(m_size.y));
	m_colliderBody.SetBuffer(-4, -4, 8, 9); // Sets the buffer (how much to subtract from the collider) of the collider 

	// Updates the Collider position to the middle left of the player
	m_colliderLeft.SetBox((int)(m_position.x), (int)(m_position.y + m_size.y / 4), (int)(m_size.x / 2), (int)(m_size.y / 2));
	m_colliderLeft.SetBuffer(-4, -4, 8, 9);

	// Updates the Collider position to the middle right of the player
	m_colliderRight.SetBox((int)(m_position.x + m_size.x / 2), (int)(m_position.y + m_size.y / 4), (int)(m_size.x / 2), (int)(m_size.y / 2));
	m_colliderRight.SetBuffer(-4, -4, 8, 9);

	// Updates the Collider position to the down middle of the player
	m_colliderDown.SetBox((int)(m_position.x + m_size.x / 4), (int)(m_position.y + m_size.y / 1.3), (int)(m_size.x / 2), (int)(m_size.y / 4));
	m_colliderDown.SetBuffer(-4, -4, 8, 9);

	// Updates the Collider position to the top middle of the player
	m_colliderTop.SetBox((int)(m_position.x + m_size.x / 6), (int)(m_position.y), (int)(m_size.x / 1.5), (int)(m_size.y / 2));
	m_colliderTop.SetBuffer(-4, -4, 8, 9);
}
#pragma endregion

