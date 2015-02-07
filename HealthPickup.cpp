//---------------------------
// Includes
//---------------------------
#include "HealthPickup.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * HealthPickup::m_BmpHealthPtr = 0;
HealthPickup::HealthPickup(int posX, int posY):
				Pickup(posX,posY)
{
	Construct();
}

HealthPickup::HealthPickup(DOUBLE2 pos):
				Pickup(pos)
{
	Construct();
}

HealthPickup::~HealthPickup()
{	
	delete m_HitPickupPtr;
	m_HitPickupPtr = 0;

	delete m_BmpHealthPtr;
	m_BmpHealthPtr =0;
}

void HealthPickup::Construct()
{
	m_Health = 10;
	m_Type = HEALTHTYPE;
	if (m_BmpHealthPtr == 0)
	{
		m_BmpHealthPtr = new Bitmap("./Resources/HealthPickup.png");
		m_BmpHealthPtr->SetTransparencyColor(255,0,255);
	}

	m_HitPickupPtr = new HitRegion();
	m_HitPickupPtr->CreateFromRect(m_Pos.x,m_Pos.y,30,28);
}

void HealthPickup::Tick(double deltaTime)
{

}

void HealthPickup::Paint(MATRIX3X2 matView)
{
	if (m_Alive)
	{
		MATRIX3X2 matTranslate;

		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matTranslate*matView);
		GAME_ENGINE->DrawBitmap(m_BmpHealthPtr,0,0);

		/*GAME_ENGINE->SetColor(255,0,0,100);
		GAME_ENGINE->SetTransformMatrix(matView);
		GAME_ENGINE->FillHitRegion(m_HitPickupPtr);*/
	}

}

void HealthPickup::Destroy(DOUBLE2 posHero)
{
	m_Alive = false;
}
