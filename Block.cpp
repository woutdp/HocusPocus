//---------------------------
// Includes
//---------------------------
#include "Block.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Block::m_BmpBlockPtr = 0;

Block::Block(int posX, int posY, int type, bool destructableBolt):m_Pos(posX,posY),m_Type(type),
					m_Destructable(destructableBolt), m_Alive(true),m_InitiateDeath(false),m_TimeUntilDeath(1)
{
	m_HitBlockPtr = new HitRegion();
	m_HitBlockPtr->CreateFromRect(0,0,32,32);


	if (m_BmpBlockPtr == 0)
	{
		m_BmpBlockPtr = new Bitmap("./Resources/Block.png");
		m_BmpBlockPtr->SetTransparencyColor(255,0,255);
	}

	m_StarPtr = new Stars();
}

Block::~Block()
{
	delete m_BmpBlockPtr;
	m_BmpBlockPtr = 0;

	delete m_HitBlockPtr;
	m_HitBlockPtr = 0;

	delete m_StarPtr;
	m_StarPtr = 0;
}

void Block::Tick(double deltaTime)
{
	if (m_InitiateDeath && m_Alive)
	{
		--m_TimeUntilDeath;
	}

	if (m_TimeUntilDeath <= 0 && m_Alive)
	{
		m_Alive = false;
		if (rand()%2 == 1)
		{
			m_StarPtr->SpawnBrownStar(m_Pos);
		}
		else
		{
			m_StarPtr->SpawnSilverStar(m_Pos);
		}
	}
	m_StarPtr->Tick(deltaTime);

	m_HitBlockPtr->SetPos(m_Pos);
}

void Block::Paint(MATRIX3X2 matView)
{
	if(m_Alive)
	{
		MATRIX3X2 matTranslate,matIdentity;
		RECT r;

		r.top = 0;
		r.bottom = 32;
		r.left = m_Type*32;
		r.right = r.left + 32;

		matIdentity.SetAsIdentity();

		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matTranslate * matView);
		GAME_ENGINE->DrawBitmap(m_BmpBlockPtr,0,0,r);

		/*GAME_ENGINE->SetTransformMatrix(matView);
		GAME_ENGINE->SetColor(255,0,0,100);
		GAME_ENGINE->FillHitRegion(m_HitBlockPtr);*/
	}

	m_StarPtr->Paint(matView);
}


void Block::Destroy(int timeUntilDeath)
{
	if (m_InitiateDeath == false)
	{
		m_TimeUntilDeath = timeUntilDeath;
		m_InitiateDeath = true;
	}

}

bool Block::GetDestructable()
{
	return m_Destructable;
}


bool Block::InitiateDeath()
{
	return m_InitiateDeath;
}

HitRegion * Block::GetHitregion()
{
	return m_HitBlockPtr;
}

bool Block::GetAlive()
{
	return m_Alive;
}

DOUBLE2 Block::GetPos()
{
	return m_Pos;
}

void Block::SetAlive(bool value)
{
	m_Alive = value;
	m_InitiateDeath = false;
	m_TimeUntilDeath = 1;
}