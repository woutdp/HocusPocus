//-----------------------------------------------------------------
// Game File
// C++ Header - HocusPocus.h - version 2012 v2_10
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"	
#include "GameEngine.h"
#include "AbstractGame.h"

#include "Hero.h"

#include "Bolt.h"

#include "Explosion.h"
#include "SmallExplosion.h"
#include "BigExplosion.h"

#include "Enemy.h"
#include "Mushroom.h"
#include "Crocodile.h"
#include "Devil.h"

#include "Stars.h"

#include "Pickup.h"
#include "ScorePickup.h"
#include "HealthPickup.h"
#include "CrystalPickup.h"
#include "KeyPickup.h"
#include "ExtraShotPickup.h"

#include "Lock.h"

#include "Block.h"

#include "Lava.h"

#include "Switch.h"

#include "ScoreText.h"

#include "WizardText.h"

//-----------------------------------------------------------------
// HocusPocus Class																
//-----------------------------------------------------------------
class HocusPocus : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	HocusPocus();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~HocusPocus();

	//---------------------------
	// General Methods
	//---------------------------

	void GameInitialize(HINSTANCE hInstance);
	void GameStart();				
	//void GameEnd();
	//void GameActivate();
	//void GameDeactivate();
	//void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam);
	//void MouseMove(int x, int y, WPARAM wParam);
	//void CheckKeyboard();
	void KeyPressed(TCHAR cKey);
	void GameTick(double deltaTime);
	void GamePaint(RECT rect);
	HitRegion * GetLevelHitRegion();

	//void CallAction(Caller* callerPtr);

	// -------------------------
	// Member functions
	// -------------------------



private:
	// -------------------------
	// Member functions
	// -------------------------
	void CameraFollow();
	bool AllowedToFire();

	//COLLISIONFUNCTIONS
	bool CollisionDetection(HitRegion * hitr1, HitRegion * hitr2);
	void CollisionBoltWallAndScreen();
	void CollisionBoltEnemy();
	void CollisionHeroEnemy();
	void CollisionHeroTrigger();
	void CollisionHeroPickups();
	void CollisionHeroLocks();
	void CollisionHeroBlock();
	bool CollisionBoltBlock();
	void CollisionHeroLava();
	void CollisionHeroEnemyBolt();

	void CollisionAll();

	//REST
	void PaintHudStatistics(MATRIX3X2 matview);

	bool CreateSmallExplosion(DOUBLE2 pos);
	bool CreateBigExplosion(DOUBLE2 pos);
	bool CreateStar(DOUBLE2 pos, bool colour);

	void CreateStarSpawnBox();

	void DestroyWalls();

	void CheckDeath();

	void CheckWin();

	bool CheckPauseWizards();
	void DisactivatePause();

	void ResetGame(bool resetHeroPos);

	// -------------------------
	// Datamembers
	// -------------------------
	static const int MAXBOLT = 2;
	static const int MAXEXPLOSIONS = 20;
	static const int MAXENEMIES = 28;
	static const int MAXSTARS = 80;
	static const int MAXTRIGGER = 11;
	static const int MAXPICKUPS = 101;
	static const int MAXLOCKS = 2;
	static const int MAXBLOCKS = 80;
	static const int MAXLAVA = 33;
	static const int MAXSWITCHES = 2;
	static const int MAXWIZARDTEXT = 3;

	Hero * m_HeroPtr;
	Bitmap * m_BmpLevelPtr;
	Bitmap * m_BmpHudPtr;
	Bitmap * m_BmpBackgroundPtr;
	Bitmap * m_BmpKeyPtr;
		
	Bolt * m_BoltPtr[MAXBOLT];
	HitRegion * m_HitLevelPtr;
	HitRegion * m_HitTriggerPtr[MAXTRIGGER];
	Explosion * m_ExplosionPtr[MAXEXPLOSIONS];
	Enemy * m_EnemyPtr[MAXENEMIES];
	Stars * m_StarsPtr[MAXSTARS];
	Pickup * m_PickupPtr[MAXPICKUPS];
	Lock * m_LockPtr[MAXLOCKS];
	Block * m_BlockPtr[MAXBLOCKS];
	Lava * m_LavaPtr[MAXLAVA];
	Switch * m_SwitchPtr[MAXSWITCHES];
	ScoreText * m_ScoreTextPtrPtr;
	WizardText * m_WizardTextPtr[MAXWIZARDTEXT];

	DOUBLE2 m_PosCamera;
	bool m_FireClick;

	bool m_GoldKeyPossession;
	bool m_SilverKeyPossession;

	bool m_DebugScreenActive;
	bool m_DebugScreenActivePrevious;

	bool m_GodMode;
	bool m_GodModePrevious;

	bool m_Pause;
	bool m_PausePrevious;

	double m_Time;

	int m_DeathSequence;

	int m_FillBackgroundEffectCrystal;

	int m_CrystalMax;

	int m_TreasurePickedUp;
	int m_TreasureAmount;
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	HocusPocus(const HocusPocus& tRef);
	HocusPocus& operator=(const HocusPocus& tRef);
};
