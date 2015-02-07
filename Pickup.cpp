//---------------------------
// Includes
//---------------------------
#include "Pickup.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Pickup::Pickup(int posX, int posY): m_Pos(posX,posY),m_StartPos(posX,posY),m_CurrentAnimationLoop(0),m_Score(0),m_Type(0),m_Alive(true),m_Health(0)
{
	// nothing to create
}

Pickup::Pickup(DOUBLE2 pos): m_Pos(pos),m_StartPos(pos),m_CurrentAnimationLoop(0),m_Score(0),m_Type(0),m_Alive(true),m_Health(0)
{
	// nothing to create
}

Pickup::~Pickup()
{
	delete m_HitPickupPtr;
	m_HitPickupPtr = 0;
}

HitRegion * Pickup::GetHitregion()
{
	return m_HitPickupPtr;
}

int Pickup::GetScore()
{
	return m_Score;
}

int Pickup::GetType()
{
	return m_Type;
}

bool Pickup::GetAlive()
{
	return m_Alive;
}

int Pickup::GetHealth()
{
	return m_Health;
}

void Pickup::SetAlive(bool value)
{
	m_Pos = m_StartPos;
	m_Alive = value;
	m_CurrentAnimationLoop = 0;
}