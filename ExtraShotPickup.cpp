//---------------------------
// Includes
//---------------------------
#include "ExtraShotPickup.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * ExtraShotPickup::m_BmpExtraShotPtr = 0;

ExtraShotPickup::ExtraShotPickup(int posX, int posY):
				Pickup(posX,posY), m_Shine(false)
{
	Construct();
}

ExtraShotPickup::ExtraShotPickup(DOUBLE2 pos):
				Pickup(pos), m_Shine(false)
{
	Construct();
}

ExtraShotPickup::~ExtraShotPickup()
{
	delete m_BmpExtraShotPtr;
	m_BmpExtraShotPtr = 0;

}

void ExtraShotPickup::Construct()
{
	m_Type = EXTRASHOT;
	
	if (m_BmpExtraShotPtr == 0)
	{
		m_BmpExtraShotPtr = new Bitmap("./Resources/ExtraShotPickup.png");
		m_BmpExtraShotPtr->SetTransparencyColor(255,0,255);
	}

	m_HitPickupPtr = new HitRegion();
	m_HitPickupPtr->CreateFromRect(m_Pos.x,m_Pos.y,32,8);

}

void ExtraShotPickup::Tick(double deltaTime)
{
	if (m_Shine == true)
	{
		m_Shine = false;
	}
	else
	{
		if(rand()%35 == 0)
		{
			m_Shine = true;
		}
	}
}

void ExtraShotPickup::Paint(MATRIX3X2 matView)
{
	MATRIX3X2 matTranslate;
	RECT rect;

	if(m_Alive)
	{
		
		rect.top = 0;
		rect.bottom = rect.top+8;
		rect.left = 32*m_Shine;
		rect.right = rect.left+32;

		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matTranslate*matView);
		GAME_ENGINE->DrawBitmap(m_BmpExtraShotPtr,0,0,rect);

	}
}

void ExtraShotPickup::Destroy(DOUBLE2 posHero)
{
	m_Alive = false;
}

