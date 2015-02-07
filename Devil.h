#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "Enemy.h"
#include "SmallExplosion.h"

//-----------------------------------------------------
// Devil Class									
//-----------------------------------------------------
class Devil : public Enemy
{
public:
	Devil(HitRegion * HitLevel, bool direction);				// Constructor
	virtual ~Devil();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime, DOUBLE2 posHero);
	void Paint(MATRIX3X2 matview);
	void Spawn(int posX,int posY);
	void Hit(int amountOfDamage);

	void Destroy(bool brutally);
	void CollisionDetection();
	void AgressiveAI(DOUBLE2 posHero);

	HitRegion * GetBoltHitRegion();
	void DestroyBolt();

private: 
	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void TickBolt(double deltaTime);
	void PaintBolt(MATRIX3X2 matView);
	void FireBolt();

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static Bitmap * m_BmpEnemyPtr;
	bool m_Agressive;
	bool m_Backward;
	HitRegion * m_HitBoltPtr;
	DOUBLE2 m_PosBolt;
	bool m_Firing;
	bool m_FireDirection;

	Explosion * m_ExplosionPtr;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Devil(const Devil& yRef);									
	Devil& operator=(const Devil& yRef);	
};

 
