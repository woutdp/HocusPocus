#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Enemy Class									
//-----------------------------------------------------
class Enemy
{
public:
	Enemy(HitRegion * HitLevel,bool direction);				// Constructor
	virtual ~Enemy();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	virtual void Tick(double deltaTime, DOUBLE2 posHero) = 0;
	virtual void Paint(MATRIX3X2 matview) = 0;
	virtual void Spawn(int posX,int posY) = 0;
	virtual void Hit(int amountOfDamage) = 0;
	
	HitRegion * GetHitRegion();
	bool GetAlive();
	int GetHealth();
	int GetSpawnTime();
	DOUBLE2 GetPos();
	int GetType();

	void SetAlive(bool value);

	virtual void Destroy(bool brutally) = 0;
	virtual void CollisionDetection() = 0;
	virtual HitRegion * GetBoltHitRegion() = 0;
	virtual void DestroyBolt() = 0;


protected:

	HitRegion * m_HitLevelPtr;
	DOUBLE2 m_Pos;
	HitRegion * m_HitEnemyPtr;
	int m_CurrentAnimationStep;
	int m_Height,m_Width;
	bool m_Direction;
	bool m_Alive;
	int m_GettingHit;
	int m_SpawnTime;
	int m_Health;
	int m_Type;

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------


	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Enemy(const Enemy& yRef);									
	Enemy& operator=(const Enemy& yRef);	
};

 
