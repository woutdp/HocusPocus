//---------------------------
// Includes
//---------------------------
#include "Hero.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())



//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap* Hero::m_BmpHeroPtr = 0;
int Hero::m_AnimationState = 0;

Hero::Hero(int x, int y, bool direction,HitRegion * hitLevelPtr):m_Pos(x,y),m_Direction(direction),m_HeroVelocity(0,0),m_Gravity(0,880)
	,m_HitVPtr(0), m_HitHPtr(0)
	,m_HitGround(false),m_HitCeiling(false),m_HitLeft(false),m_HitRight(false)
	,m_Jump(false),m_AllowedToJump(true)
	,m_State(0),m_Health(MAXHEALTH),m_Score(0),m_Crystal(0)
	,m_HitLevelPtr(hitLevelPtr)
	,m_Moving(false)
	,m_TimesAllowedToFire(1)
	,m_Firing(false)
	,m_GettingHit(0)
	,m_Alive(true)

{
	if (m_BmpHeroPtr == 0)
	{
		m_BmpHeroPtr = new Bitmap("./Resources/Herosheet.png");
		m_BmpHeroPtr->SetTransparencyColor(255,0,255);
	}

	m_HitVPtr = new HitRegion();
	m_HitVPtr->CreateFromRect(17,6,16,HEIGHT-6); // Verticaal is correct

	m_HitHPtr = new HitRegion();
	m_HitHPtr->CreateFromRect(17,6,16,HEIGHT/2-3);

}

Hero::~Hero()
{
	delete m_BmpHeroPtr;
	m_BmpHeroPtr = 0;

	delete m_HitVPtr;
	m_HitVPtr = 0;

	delete m_HitHPtr;
	m_HitHPtr = 0;

}


void Hero::Tick(double dTime)
{
	if (m_Alive)
	{
		//dTime = 0.052;

		if (m_GettingHit > 0)
		{
			--m_GettingHit;
		}

		CheckKeyInput();

		AllowedToJumptest();

		//Set the maximum velocities
		if (m_HeroVelocity.y > 620 && (m_State == STATEJUMPING || m_State == STATEWALKING)) m_HeroVelocity.y = 620;
		if (m_HeroVelocity.y >= 400) m_State = STATEFALLING;
		if (m_State == STATEFALLING) m_HeroVelocity.y = 620;

	

		//Do the physics
		m_Pos = m_Pos + m_HeroVelocity*dTime;
		m_HeroVelocity = m_HeroVelocity + m_Gravity*dTime;
		//Make sure the position is not a double.
		m_Pos.x = (int)m_Pos.x;
		m_Pos.y = (int)m_Pos.y;


		//adjust the hitregions to the position of the bitmap
		m_HitVPtr->SetPos(m_Pos);
		m_HitHPtr->SetPos(m_Pos);


		//Do the correction + adjust the hitregions again.
		CheckOutsideOfScreen();
		CollisionTestHitRegionDown();
		CollisionTestHitRegionUp();
		m_HitVPtr->SetPos(m_Pos);
		m_HitHPtr->SetPos(m_Pos);

		//Check every side if it touches for the controls.
		CollisionDirectionTest();

		if (m_Moving) ++m_AnimationState;
		else m_AnimationState = 0;
	}
	
}
void Hero::Paint(MATRIX3X2 matview)
{
	if (m_Alive)
	{
		//MAKE VARIABLES
		MATRIX3X2 matTranslate, matCenter, matScale;
		RECT rect;

		//SET BOUNDS RECT
		rect.top = (HEIGHT*2*(m_GettingHit%2));
		rect.bottom = rect.top+HEIGHT;
		rect.left = (WIDTH*(m_AnimationState%7));
		rect.right = rect.left+WIDTH;

		if (m_HitGround == false && m_HeroVelocity.y < 0)
		{
			rect.top = HEIGHT+(HEIGHT*2*(m_GettingHit%2));
			rect.bottom = rect.top+HEIGHT;
			rect.left = 0;
			rect.right = rect.left+WIDTH;
		}

		if (m_HitGround == false && m_HeroVelocity.y >= 0)
		{
			rect.top = HEIGHT+(HEIGHT*2*(m_GettingHit%2));
			rect.bottom = rect.top+HEIGHT;
			rect.left = WIDTH;
			rect.right = rect.left+WIDTH;
		}

		if (m_HitGround == true && m_Moving == false && m_Firing == true)
		{
			rect.top = HEIGHT+(HEIGHT*2*(m_GettingHit%2));
			rect.bottom = rect.top+HEIGHT;
			rect.left = WIDTH*2;
			rect.right = rect.left+WIDTH*2;
		}

		if (m_Direction == true)
		{
			matCenter.SetAsTranslate(-50,0);
			matScale.SetAsScale(-1,1);
		}

		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matTranslate*matview);
		GAME_ENGINE->DrawBitmap(m_BmpHeroPtr,0,0,rect);

		//GAME_ENGINE->SetTransformMatrix(matview);
		//GAME_ENGINE->FillHitRegion(m_HitVPtr);
		//GAME_ENGINE->FillHitRegion(m_HitHPtr);
	
	}
}

void Hero::CollisionTestHitRegionDown()
{
	RECT2 buffer; //Creates buffer for hitcollision
	buffer = m_HitVPtr->GetBounds(); //Sets bounds in buffer
	
	//Hittest+correction
	if (m_HitLevelPtr->HitTest(buffer.left+1,buffer.bottom) || m_HitLevelPtr->HitTest(buffer.right-1,buffer.bottom))
	{			
		//Applies correction 
		RECT2 correction = m_HitVPtr->CollisionTest(m_HitLevelPtr);
		m_Pos.y -= (correction.bottom)-(correction.top);

		m_HeroVelocity.y = 0;
	}
}
void Hero::CollisionTestHitRegionUp()
{
	RECT2 buffer; //Creates buffer for hitcollision
	buffer = m_HitVPtr->GetBounds(); //Sets bounds in buffer
	
	//Hittest+correction
	if ((m_HitLevelPtr->HitTest(buffer.left+1,buffer.top) || m_HitLevelPtr->HitTest(buffer.right-1,buffer.top)) && m_HitGround == false)
	{			
		//Applies correction 
		RECT2 correction = m_HitVPtr->CollisionTest(m_HitLevelPtr);
		m_Pos.y += (correction.bottom)-(correction.top);
	}

}

////////////////RECHECK THIS FUCNTION IF YOU HAVE ENOUGH TIME FOR SIMPLIFICATION//////////////////////////////////////
////////////////RECHECK THIS FUCNTION IF YOU HAVE ENOUGH TIME FOR SIMPLIFICATION//////////////////////////////////////
////////////////RECHECK THIS FUCNTION IF YOU HAVE ENOUGH TIME FOR SIMPLIFICATION//////////////////////////////////////
void Hero::CollisionDirectionTest()
{
	RECT2 bufferV, bufferH; //Creates buffer for hitcollision
	bufferV = m_HitVPtr->GetBounds(); //Sets bounds in buffer
	bufferH = m_HitHPtr->GetBounds(); //Sets boudns in buffer

	//Set all directions false
	m_HitCeiling = false;
	m_HitGround = false;
	m_HitLeft = false;
	m_HitRight = false;

	//Check the states and adjust
	if (m_HitLevelPtr->HitTest(bufferV.left+1,bufferV.bottom+1) || m_HitLevelPtr->HitTest(bufferV.right-1,bufferV.bottom+1)) m_State = STATEWALKING;
	if ((m_HitLevelPtr->HitTest(bufferV.left+1,bufferV.top) || m_HitLevelPtr->HitTest(bufferV.right-1,bufferV.top)) && m_State != STATEWALKING && m_HeroVelocity.y <=-100) m_State = STATEFALLING;
	//Check ground and ceiling
	if (m_HitLevelPtr->HitTest(bufferV.left+1,bufferV.top) || m_HitLevelPtr->HitTest(bufferV.right-1,bufferV.top)) m_HitCeiling = true;  //werkt
	if (m_HitLevelPtr->HitTest(bufferV.left+1,bufferV.bottom) || m_HitLevelPtr->HitTest(bufferV.right-1,bufferV.bottom)) m_HitGround = true; //werkt

	switch (m_State)
	{
		case STATEWALKING:
			//Left
			if (m_HitLevelPtr->HitTest(bufferH.left,bufferH.top+1) || m_HitLevelPtr->HitTest(bufferH.left,bufferH.bottom)) m_HitLeft = true; //exceptions needed
			if (m_HitLevelPtr->HitTest(bufferH.left-1,bufferH.top-1) == false && m_HitLevelPtr->HitTest(bufferH.left,bufferH.bottom) == true && m_HitLevelPtr->HitTest(bufferV.left,bufferV.bottom) == true) m_HitLeft = false;
			if (m_HitLevelPtr->HitTest(bufferH.left-1,bufferH.top-1) == true && m_HitLevelPtr->HitTest(bufferV.left-1,bufferV.bottom-1) == true && m_HitCeiling == false) m_HitLeft = true;
			if (m_HitLevelPtr->HitTest(bufferH.left-1,bufferH.top+1) == true) m_HitLeft = true;
			//Right
			if (m_HitLevelPtr->HitTest(bufferH.right,bufferH.top+1) || m_HitLevelPtr->HitTest(bufferH.right,bufferH.bottom)) m_HitRight = true; // exceptions needed
			if (m_HitLevelPtr->HitTest(bufferH.right+1,bufferH.top-1) == false && m_HitLevelPtr->HitTest(bufferH.right,bufferH.bottom) == true && m_HitLevelPtr->HitTest(bufferV.right,bufferV.bottom) == true ) m_HitRight = false;
			if (m_HitLevelPtr->HitTest(bufferH.right+1,bufferH.top-1) == true && m_HitLevelPtr->HitTest(bufferV.right+1,bufferV.bottom-1) == true && m_HitCeiling == false) m_HitRight = true;
			if (m_HitLevelPtr->HitTest(bufferH.right+1,bufferH.top+1) == true) m_HitRight = true;
			break;

		case STATEJUMPING:
			//Left
			if ((m_HitLevelPtr->HitTest(bufferH.left,bufferH.top+1) || m_HitLevelPtr->HitTest(bufferH.left,bufferH.bottom) || m_HitLevelPtr->HitTest(bufferV.left,bufferV.bottom-1)) && m_HitGround == false ) m_HitLeft = true; //exceptions needed
			//Right
			if ((m_HitLevelPtr->HitTest(bufferH.right,bufferH.top+1) || m_HitLevelPtr->HitTest(bufferH.right,bufferH.bottom) || m_HitLevelPtr->HitTest(bufferV.right,bufferV.bottom-1)) && m_HitGround == false ) m_HitRight = true; // exceptions needed
			break;

		case STATEFALLING:
			//Left
			if (m_HitLevelPtr->HitTest(bufferH.left,bufferH.top+1) || m_HitLevelPtr->HitTest(bufferH.left,bufferH.bottom) || m_HitLevelPtr->HitTest(bufferV.left,bufferV.bottom-1)) m_HitLeft = true; //exceptions needed
			//Right
			if (m_HitLevelPtr->HitTest(bufferH.right,bufferH.top+1) || m_HitLevelPtr->HitTest(bufferH.right,bufferH.bottom) || m_HitLevelPtr->HitTest(bufferV.right,bufferV.bottom-1)) m_HitRight = true; // exceptions needed

			break;

		default:
			GAME_ENGINE->MessageBox("Geen geldige m_State. Check Directiontest.");
			
	}

	if (m_HitGround == false && m_State != STATEJUMPING) m_State = STATEFALLING;

}

void Hero::AllowedToJumptest()
{
	

	if (m_Jump == true && m_AllowedToJump == true && m_State != STATEJUMPING )
	{
		m_AllowedToJump = false;
	}

	if (m_Jump == true && m_HitGround == true)
	{
		m_AllowedToJump = false;
	}

	if (m_Jump == false)
	{
		m_AllowedToJump = true;
	}
	
}

void Hero::CheckKeyInput()
{
	m_Moving = false;


	if(GAME_ENGINE->IsKeyDown(VK_LEFT) && m_HitLeft == false)  //LEFT
	{
		m_Pos.x -= 16;
		m_Direction = true;
		m_Moving = true;
	}
			
	if(GAME_ENGINE->IsKeyDown(VK_RIGHT) && m_HitRight == false) //RIGHT
	{

		m_Pos.x += 16;
		m_Direction = false;
		m_Moving = true;
	}

	if(GAME_ENGINE->IsKeyDown(VK_LEFT) && GAME_ENGINE->IsKeyDown(VK_RIGHT)) m_Moving = false;

	
	m_Jump = false;

	if (GAME_ENGINE->IsKeyDown(VK_CONTROL)) m_Jump = true;

	if (GAME_ENGINE->IsKeyDown(VK_CONTROL) && m_HitGround == true && m_HitCeiling == false && m_AllowedToJump == true)
	{
		m_HeroVelocity.y = (-380);
		m_State = 1;
	}


	if (GAME_ENGINE->IsKeyDown(VK_MENU))
	{
		m_Firing = true;
	}
	else
	{
		m_Firing = false;
	}
}

void Hero::CheckOutsideOfScreen()
{
	if (m_Pos.x < -1)
	{
		m_Pos.x = -1;
	}
}

void Hero::Hit(int amount)
{
	m_Health-= amount;
	m_GettingHit = AMOUNTOFFRAMESINVURN;
}

void Hero::AddHealth(int amount)
{
	m_Health += amount;

	if (m_Health > MAXHEALTH)
	{
		m_Health = MAXHEALTH;
	}
}

void Hero::AddCrystal(int amount)
{
	m_Crystal += amount;
}

void Hero::AddTimesAllowedToFire(int amount)
{
	m_TimesAllowedToFire += amount;
}

void Hero::BlockCollision(HitRegion * hitBlock)
{
	RECT2 bufferH,bufferV;
	bufferV = m_HitVPtr->GetBounds();
	bufferH = m_HitHPtr->GetBounds();

	if (hitBlock->HitTest(bufferH.right+1,bufferH.bottom-1) || hitBlock->HitTest(bufferH.right+1,bufferH.top+1))
	{			
		m_HitRight = true;
	}
	
	if (hitBlock->HitTest(bufferH.left-1,bufferH.bottom-1) || hitBlock->HitTest(bufferH.left-1,bufferH.top+1))
	{			
		m_HitLeft = true;
	}

	if (hitBlock->HitTest(bufferV.right-1,bufferV.bottom-1) || hitBlock->HitTest(bufferV.left+1,bufferV.bottom))
	{			
		RECT2 correction = m_HitVPtr->CollisionTest(hitBlock);
		m_Pos.y -= (correction.bottom)-(correction.top);

		m_HeroVelocity.y = 0;

		m_HitGround = true;
		m_State = STATEWALKING;
	}
	
	m_HitVPtr->SetPos(m_Pos);
	m_HitHPtr->SetPos(m_Pos);
}

//////////////////////////////////////////
///////////////GETS///////////////////////
//////////////////////////////////////////

DOUBLE2 Hero::GetPos()
{
	return m_Pos;
}

int Hero::GetHeight()
{
	return HEIGHT;
}

int Hero::GetWidth()
{
	return WIDTH;
}

DOUBLE2 Hero::GetVelocity()
{
	return m_HeroVelocity;
}

double Hero::GetVelocityX()
{
	return m_HeroVelocity.x;
}

double Hero::GetVelocityY()
{
	return m_HeroVelocity.y;
}

bool Hero::GetHitBool(int direction)
{
	switch (direction)
	{
	case 0:	//Ceiling
		return m_HitCeiling;
		 break;
	case 1: //Ground
		return m_HitGround;
		 break;
	case 2: //Left
		return m_HitLeft;
		 break;
	case 3: //Right
		return m_HitRight;
		 break;
	default:
		return false;
		GAME_ENGINE->MessageBox("Function GetHitBool in Class Hero received unexpected parameter (direction must be an integer between 0 and 3");
	}
}

bool Hero::GetAllowedToJump()
{
	return m_AllowedToJump;
}

bool Hero::GetJump()
{
	return m_Jump;
}

bool Hero::GetDirection()
{
	return m_Direction;
}


int Hero::GetState()
{
	return m_State;
}

bool Hero::GettingHit()
{
	if (m_GettingHit <=0)
	{
		return false;
	}

	return true;
}

HitRegion * Hero::GetHitRegion()
{
	return m_HitVPtr;
}

int Hero::GetScore()
{
	return m_Score;
}

int Hero::GetHealth()
{
	return m_Health;
}

int Hero::GetCrystal()
{
	return m_Crystal;
}

int Hero::GetTimesAllowedToFire()
{
	return m_TimesAllowedToFire;
}

bool Hero::GetMoving()
{
	return m_Moving;
}

bool Hero::GetAlive()
{
	return m_Alive;
}

//////////////////////////////////////////
///////////////SETS///////////////////////
//////////////////////////////////////////

void Hero::SetHitBool(bool boolHit, int direction)
{
	switch (direction)
	{
		case 0:	//Ceiling
			m_HitCeiling = boolHit;
			 break;
		case 1: //Ground
			m_HitGround = boolHit;
			 break;
		case 2: //Left
			m_HitLeft = boolHit;
			 break;
		case 3: //Right
			m_HitRight= boolHit;
			 break;
		default:
			GAME_ENGINE->MessageBox("Function SetHitBool in Class Hero received unexpected parameter (direction must be an integer between 0 and 3");
	}

}

void Hero::SetJump(bool setJump)
{
	m_Jump = setJump;
}

void Hero::SetHeroVelocity(DOUBLE2 velocity)
{
	m_HeroVelocity = velocity;
}

void Hero::SetHeroVelocityX(double x)
{
	m_HeroVelocity.x = x;
}

void Hero::SetHeroVelocityY(double y)
{
	m_HeroVelocity.y = y;
}

void Hero::SetPos(DOUBLE2 pos)
{
	m_Pos = pos;
}

void Hero::SetPosX(double x)
{
	m_Pos.x = x;
}

void Hero::SetPosY(double y)
{
	m_Pos.y = y;
}

void Hero::SetDirection(bool rightIsFalse)
{
	m_Direction = rightIsFalse;
}

void Hero::SetState(int state)
{
	m_State = state;
}

void Hero::SetMoving (bool movement)
{
	m_Moving = movement;
}

void Hero::SetFiring(bool firing)
{
	m_Firing = firing;
}

void Hero::SetScore(int amount)
{
	m_Score += amount;
}

void Hero::SetHealth(int amount)
{
	m_Health = amount;
}

void Hero::SetAlive(bool value)	
{
	m_Alive = value;
}

void Hero::ResetStats()
{
	m_Crystal = 0;
	m_Health = 100;
	m_Score = 0;
}

void Hero::SetGettingHit(bool value)
{
	m_GettingHit = value;
}