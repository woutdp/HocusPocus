//---------------------------
// Includes
//---------------------------
#include "Enemy.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------

Enemy::Enemy(HitRegion * HitLevel,bool direction): m_Pos(0,0), m_CurrentAnimationStep(0), m_HitEnemyPtr(0)
							,m_Height(0),m_Width(0),m_Direction(direction)
							,m_Alive(false), m_HitLevelPtr(HitLevel), m_GettingHit(0),m_SpawnTime(-1)
{

}

Enemy::~Enemy()
{
	delete m_HitEnemyPtr;
	m_HitEnemyPtr = 0;
}

bool Enemy::GetAlive()
{
	return m_Alive;
}

int Enemy::GetHealth()
{
	return m_Health;
}

int Enemy::GetSpawnTime()
{
	return m_SpawnTime;
}

DOUBLE2 Enemy::GetPos()
{
	return m_Pos;
}

HitRegion * Enemy::GetHitRegion()
{
	return m_HitEnemyPtr;
}

int Enemy::GetType()
{
	return m_Type;
}

void Enemy::SetAlive(bool value)
{
	m_Alive = value;
}