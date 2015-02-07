#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "Enemy.h"
//-----------------------------------------------------
// Mushroom Class									
//-----------------------------------------------------
class Mushroom : public Enemy
{
public:
	Mushroom(HitRegion * HitLevel, bool direction);				// Constructor
	virtual ~Mushroom();		// Destructor

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
	// Datamembers								
	//-------------------------------------------------
	static Bitmap * m_BmpEnemyPtr;
	bool m_Agressive;
	
	

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Mushroom(const Mushroom& yRef);									
	Mushroom& operator=(const Mushroom& yRef);	
};

 
