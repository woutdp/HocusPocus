//---------------------------
// Includes
//---------------------------
#include "Lock.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Lock::m_BmpLockPtr = 0;

Lock::Lock(DOUBLE2 pos,int type):m_Pos(pos),m_Type(type),m_Alive(true),m_Shine(false)
{
	Construct();
}

Lock::Lock(int posX, int posY,int type): m_Pos(posX,posY),m_Type(type),m_Alive(true),m_Shine(false)
{
	Construct();
}

Lock::~Lock()
{
	delete m_HitLockPtr;
	m_HitLockPtr = 0;

	delete m_BmpLockPtr;
	m_BmpLockPtr = 0;
}

void Lock::Construct()
{
	if (m_BmpLockPtr == 0)
	{
		m_BmpLockPtr =  new Bitmap ("./Resources/Lock.png");
	}

	m_HitLockPtr =  new HitRegion();
	m_HitLockPtr->CreateFromRect(m_Pos.x,m_Pos.y,32,32);
}

void Lock::Tick(double deltaTime)
{
	if (m_Shine)
	{
		m_Shine = false;
	}
	else
	{
		if(rand()%25 == 0) m_Shine = true;
	}
}

void Lock::Paint(MATRIX3X2 matView)
{
	MATRIX3X2 matTranslate;
	RECT rect;

	if (m_Alive)
	{
		rect.top = 32 * m_Type;
		rect.bottom = rect.top +32;
		rect.left = 32 * m_Shine;
		rect.right = rect.left + 32;

		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matTranslate * matView);
		GAME_ENGINE->DrawBitmap(m_BmpLockPtr,0,0,rect);
	}
}

void Lock::Destroy()
{
	m_Alive = false;
}

int Lock::GetType()
{
	return m_Type;
}

bool Lock::GetAlive()
{
	return m_Alive;
}

HitRegion * Lock::GetHitregion()
{
	return m_HitLockPtr;
}

DOUBLE2 Lock::GetPos()
{
	return m_Pos;
}

void Lock::SetAlive(bool value)
{
	m_Alive = value;
}