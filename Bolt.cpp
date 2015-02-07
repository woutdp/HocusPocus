//---------------------------
// Includes
//---------------------------
#include "Bolt.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Bolt::m_BmpBoltPtr = 0;
int Bolt::m_AllowedToFire = 2;
int Bolt::m_AmountInAir = 0;

Bolt::Bolt():m_Pos(0,0),m_Firing(false),m_Direction(false),m_HitBoltPtr(0)
{
	if (m_BmpBoltPtr == 0)
	{
		m_BmpBoltPtr = new Bitmap("./Resources/Bolt.png");
		m_BmpBoltPtr->SetTransparencyColor(255,0,255);
	}

	m_HitBoltPtr = new HitRegion();
	m_HitBoltPtr->CreateFromRect(0,0,32,3);

	for (int i = 0; i <MAXSPARKLES;++i)
	{
		m_SparklesPtr[i] = new Sparkles();
	}
	

}

Bolt::~Bolt()
{
	delete m_BmpBoltPtr;
	m_BmpBoltPtr = 0;

	for (int i = 0; i <MAXSPARKLES;++i)
	{
		delete m_SparklesPtr[i];
		m_SparklesPtr[i] = 0;
	}
}

void Bolt::Tick(double deltaTime, Hero * hero)
{
	if (m_Firing == true)
	{
		if (m_Direction == true)
		{
			if (hero->GetMoving())
			{
				m_Pos.x -= 48;
			}
			else
			{
				m_Pos.x -= 32;
			}
			
			m_HitBoltPtr->SetPos(m_Pos.x-2,m_Pos.y);
		}
		else if (m_Direction == false)
		{
			if (hero->GetMoving())
			{
				m_Pos.x += 48;
			}
			else
			{
				m_Pos.x += 32;
			}
			m_HitBoltPtr->SetPos(m_Pos);
		}
		CreateSparkles(m_Pos);
	}

	for (int i = 0; i <MAXSPARKLES;++i)
	{
		m_SparklesPtr[i]->Tick(deltaTime);
	}
}

void Bolt::Paint(MATRIX3X2 matview)
{
	if(m_Firing == true)
	{
		//MAKE MATRICES
		MATRIX3X2 matTranslate,matView,matIdentity, matCenter,matScale;
		matView = matview;

		//MAKE RECT
		RECT rect;
		rect.left = 0;
		rect.right = rect.left + 40;
		rect.top = 0;
		rect.bottom = rect.top + 40;

		//SET MIRROR+OFFSET IF OTHER DIRECTION
		if (m_Direction == true)
		{
			matCenter.SetAsTranslate(-30,0);
			matScale.SetAsScale(-1,1);
		}

		//SET TRANSFORMMATRIX
		
		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matTranslate*matView);

		//DRAW BITMAP
		GAME_ENGINE->DrawBitmap(m_BmpBoltPtr,0,0,rect);

		//DRAW HITREGION
		/*GAME_ENGINE->SetTransformMatrix(matView);
		GAME_ENGINE->SetColor(255,0,0,100);
		GAME_ENGINE->FillHitRegion(m_HitBoltPtr);*/
		
	}

	for (int i = 0; i <MAXSPARKLES;++i)
	{
		m_SparklesPtr[i]->Paint(matview);
	}

}

void Bolt::Fire(DOUBLE2 pos,bool direction)
{
	if (m_AmountInAir < m_AllowedToFire)
	{
		++m_AmountInAir;
		m_Direction = direction;
		m_Firing = true;

		m_Pos.x = pos.x+20;
		m_Pos.y = pos.y+32;
	}
}

void Bolt::Destroy()
{
	m_Firing = false;
	--m_AmountInAir;
}

bool Bolt::CreateSparkles(DOUBLE2 pos)
{
	for (int i = 0; i <MAXSPARKLES;++i)
	{
		if (m_SparklesPtr[i]->GetAlive() == false)
		{
			m_SparklesPtr[i]->Spawn(pos);
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////
///////////////GETS///////////////////////
//////////////////////////////////////////
DOUBLE2 Bolt::GetPos()
{
	return m_Pos;
}

bool Bolt::GetFiring()
{
	return m_Firing;
}

HitRegion * Bolt::GetHitRegion()
{
	return m_HitBoltPtr;
}

//////////////////////////////////////////
///////////////SETS///////////////////////
//////////////////////////////////////////

void Bolt::SetAllowedToFire(int amount)
{
	m_AllowedToFire = amount;
}

void Bolt::PlusOneAllowedToFire()
{
	m_AllowedToFire += 1;
}