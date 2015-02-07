//---------------------------
// Includes
//---------------------------
#include "ScorePickup.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * ScorePickup::m_BmpScorePtr = 0;
ScorePickup::ScorePickup(int posX, int posY,int scoreType):
			Pickup(posX,posY), m_ScoreType(scoreType),m_Shine(false),m_Backward(false)
{
	Construct();
}

ScorePickup::ScorePickup(DOUBLE2 pos,int scoreType):
			Pickup(pos), m_ScoreType(scoreType),m_Shine(false),m_Backward(false)
{
	Construct();
}

ScorePickup::~ScorePickup()
{
	delete m_BmpScorePtr;
	m_BmpScorePtr = 0;
}

void ScorePickup::Construct()
{
	m_Type = SCORETYPE;
	if (m_BmpScorePtr == 0)
	{
		m_BmpScorePtr = new Bitmap("./Resources/Score.png");
		m_BmpScorePtr->SetTransparencyColor(255,0,255);
	}
	
	m_HitPickupPtr = new HitRegion();

	switch (m_ScoreType)
	{
		case 0:
			m_HitPickupPtr->CreateFromRect(m_Pos.x,m_Pos.y+10,32,23);
			m_Score = 100;
		break;

		case 1:
			m_HitPickupPtr->CreateFromRect(m_Pos.x,m_Pos.y+10,32,23);
			m_Score = 250;
		break;
		
		case 2:
			m_HitPickupPtr->CreateFromRect(m_Pos.x,m_Pos.y,32,12);
			m_Score = 500;
		break;

		case 3:
			m_HitPickupPtr->CreateFromRect(m_Pos.x,m_Pos.y,24,32);
			m_Score = 1000;
		break;
		
		default:
			GAME_ENGINE->MessageBox("Wrong Scoretype: Check ScorePickup.cpp paintfucntion");	
	}
	//m_HitPickupPtr->CreateFromRect(m_Pos.x,m_Pos.y,31,31);

}

void ScorePickup::Tick(double deltaTime)
{
	if (m_Alive)
	{
		if (m_Shine == false && rand()% 25 == 0)
		{
			m_Shine = true;
		}
	
		if (m_Shine == true)
		{
			if (m_Backward == false)++m_CurrentAnimationLoop;
			if (m_Backward)--m_CurrentAnimationLoop;
		}

		if (m_CurrentAnimationLoop >= 3)
		{
			m_Backward = true;
			m_CurrentAnimationLoop = 3;
		}

		if (m_CurrentAnimationLoop <= 0)
		{
			m_Shine = false;
			m_Backward = false;
			m_CurrentAnimationLoop = 0;
		}
	}
	else
	{
		if (m_CurrentAnimationLoop >= 17)
		{
			m_CurrentAnimationLoop = 17;
		}
		else
		{
			++m_CurrentAnimationLoop;
		}
	}
}

void ScorePickup::Paint(MATRIX3X2 matView)
{
	MATRIX3X2 matTranslate;
	RECT rect;

	int height = 40;
	int width = 60;

	if (m_Alive == true)
	{
		switch (m_ScoreType)
		{
			case 0:
				rect.top = 0;
				rect.bottom = rect.top + height;
				rect.left = width*m_CurrentAnimationLoop;
				rect.right = rect.left + width;
			break;
		
			case 1:
				rect.top = height;
				rect.bottom = rect.top + height;
				rect.left = width*m_CurrentAnimationLoop;
				rect.right = rect.left + width;
			
			break;
		
			case 2:
				rect.top = height*2;
				rect.bottom = rect.top + height;
				rect.left = 0;
				rect.right = rect.left + width;
			
			break;

			case 3:
				rect.top = height*3;
				rect.bottom = rect.top + height;
				rect.left = 0;
				rect.right = rect.left + width;
			
			break;
		
			default:
				GAME_ENGINE->MessageBox("Wrong Scoretype: Check ScorePickup.cpp paintfucntion");	
		}

		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matTranslate*matView);
		GAME_ENGINE->DrawBitmap(m_BmpScorePtr,0,0,rect);
		
		/*GAME_ENGINE->SetTransformMatrix(matView);
		GAME_ENGINE->SetColor(255,0,0,100);
		GAME_ENGINE->FillHitRegion(m_HitPickupPtr);*/

	}
	else if (m_CurrentAnimationLoop < 17)
	{
		switch (m_ScoreType)
		{
			case 0:
				rect.top = height*2;
				rect.bottom = rect.top + height;
				rect.left = width;
				rect.right = rect.left + width;
			break;
		
			case 1:
				rect.top = height*3;
				rect.bottom = rect.top + height;
				rect.left = width;
				rect.right = rect.left + width;
			
			break;
		
			case 2:
				rect.top = height*2;
				rect.bottom = rect.top + height;
				rect.left = width*2;
				rect.right = rect.left + width;
			
			break;

			case 3:
				rect.top = height*3;
				rect.bottom = rect.top + height;
				rect.left = width*2;
				rect.right = rect.left + width;
			
			break;
		
			default:
				GAME_ENGINE->MessageBox("Wrong Scoretype: Check ScorePickup.cpp paintfucntion");	
		}

		DOUBLE2 pos = m_Pos;

		pos.y-=15;
		pos.y-=m_CurrentAnimationLoop*4;

		matTranslate.SetAsTranslate(pos);
		GAME_ENGINE->SetTransformMatrix(matTranslate*matView);
		GAME_ENGINE->DrawBitmap(m_BmpScorePtr,0,0,rect);
	}
}

void ScorePickup::Destroy(DOUBLE2 posHero)
{
	m_Pos = posHero;
	m_Alive = false;
	m_CurrentAnimationLoop = 0;
}
