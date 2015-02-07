#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Hero Class									
//-----------------------------------------------------
class Hero
{
public:
	Hero(int x, int y,bool direction, HitRegion * hitLevelPtr);				// Constructor
	virtual ~Hero();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Paint(MATRIX3X2 matview);
	void PaintHitRegion();
	void Tick(double dTime);
	void CollisionTestHitRegionDown();
	void CollisionTestHitRegionUp();
	void CollisionDirectionTest();
	void AllowedToJumptest();
	void Fire();
	void CheckKeyInput();
	void CheckOutsideOfScreen();
	void Hit(int amount);
	void AddHealth(int amount);
	void AddCrystal(int amount);
	void AddTimesAllowedToFire(int amount);

	void BlockCollision(HitRegion * hitBlock);

	//Gets
	DOUBLE2 GetPos();
	DOUBLE2 GetVelocity();	
	double GetVelocityX();	
	double GetVelocityY();	
	int GetHeight();
	int GetWidth();
	bool GetHitGround();
	bool GetHitCeiling();
	bool GetHitBool(int direction); //ZeroCeiling_OneGround_TwoLeft_ThreeRight
	bool GetAllowedToJump();
	bool GetJump();
	bool GetDirection();
	int GetState();
	DOUBLE2 GetBoltPos();
	bool GettingHit();
	HitRegion * GetHitRegion();
	int GetScore();
	int GetHealth();
	int GetCrystal();
	int GetTimesAllowedToFire();
	bool GetMoving();
	bool GetAlive();
	
	//Sets
	void SetHeroVelocity(DOUBLE2 velocity);
	void SetHeroVelocityX(double x);
	void SetHeroVelocityY(double y);
	void SetPos(DOUBLE2 pos);
	void SetPosX(double x);
	void SetPosY(double y);
	void SetHitGround(bool hitGround);
	void SetHitCeiling(bool hitCeiling);
	void SetHitBool(bool boolHit, int direction); //ZeroCeiling_OneGround_TwoLeft_ThreeRight
	void SetJump(bool setJump);
	void SetDirection(bool rightIsFalse);
	void SetState(int state);
	void SetMoving (bool movement);
	void SetFiring(bool firing);
	void SetScore(int amount);
	void SetHealth(int amount);
	void SetAlive(bool value);
	void ResetStats();
	void SetGettingHit(bool value);



private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static const int HEIGHT = 70;
	static const int WIDTH = 60;
	static const int STATEWALKING = 0;
	static const int STATEJUMPING = 1;
	static const int STATEFALLING = 2;
	static const int DRIGHT = 0;
	static const int DLEFT = 1;
	static const int AMOUNTOFFRAMESINVURN = 20;
	static const int MAXHEALTH = 100;

	static Bitmap * m_BmpHeroPtr;
	static int m_AnimationState;
	int m_State;
	int m_TimesAllowedToFire;
	int m_Health;
	int m_Score;
	int m_Crystal;
	DOUBLE2 m_Pos;
	DOUBLE2 m_HeroVelocity;
	DOUBLE2 m_Gravity;
	HitRegion * m_HitVPtr, * m_HitHPtr;
	bool m_HitGround;
	bool m_HitCeiling;
	bool m_Jump,m_AllowedToJump;
	bool m_HitLeft;
	bool m_HitRight;
	bool m_Direction;
	bool m_Moving;
	bool m_Firing;
	int m_GettingHit;
	bool m_Alive;

	HitRegion * m_HitLevelPtr;


	//Manager * m_Game;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Hero(const Hero& yRef);									
	Hero& operator=(const Hero& yRef);	
};

 
