//---------------------------
// Includes
//---------------------------
#include "Mushroom.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------

Bitmap* Mushroom::m_BmpEnemyPtr = 0;

Mushroom::Mushroom(HitRegion * HitLevel, bool direction): 
		Enemy(HitLevel,direction),m_Agressive(false)
{
	m_HitEnemyPtr = new HitRegion();
	m_HitEnemyPtr->CreateFromRect(0,0,15,46);

	if (m_BmpEnemyPtr == 0)
	{
		m_BmpEnemyPtr = new Bitmap("./Resources/Mushroom.png");
		m_BmpEnemyPtr->SetTransparencyColor(255,0,255);
	}

	m_Height = 50;
	m_Width = 60;

	m_Health = 5;

	m_Alive = false;

	m_Direction = direction;

	m_Type = 0;
}

Mushroom::~Mushroom()
{
	delete m_HitEnemyPtr;
	m_HitEnemyPtr = 0;

	delete m_BmpEnemyPtr;
	m_BmpEnemyPtr = 0;
}

void Mushroom::Tick(double deltaTime, DOUBLE2 posHero)
{

	/*//Set the maximum velocities
	if (m_HeroVelocity.y > 400 && (m_State == STATEJUMPING || m_State == STATEWALKING)) m_HeroVelocity.y = 400;
	if (m_State == STATEFALLING) m_HeroVelocity.y = 620;
	

	//Do the physics
	m_Pos = m_Pos + m_HeroVelocity*dTime;
	m_HeroVelocity = m_HeroVelocity + m_Gravity*dTime;
	//Make sure the position is not a double.
	m_Pos.x = (int)m_Pos.x;
	m_Pos.y = (int)m_Pos.y;*/


	//adjust the hitregions to the position of the bitmap
	
	++m_CurrentAnimationStep;
	--m_GettingHit;
	if (m_SpawnTime > 0)
	{
		--m_SpawnTime;
	}

	AgressiveAI(posHero);

	if (m_GettingHit <= 0)
	{
		m_GettingHit = 0;
	}

	if (m_SpawnTime == 0)
	{
		m_SpawnTime = 0;
		m_Alive = true;
	}
	else
	{
		m_Alive = false;
	}


	CollisionDetection();


	if (m_Health <= 0)
	{
		m_Alive = false;
	}

	if (m_Alive)
	{
		if (m_Direction)
		{
			if (m_Agressive)
			{
				m_Pos.x -=8;
			}
			else
			{
				m_Pos.x -=4;
			}
		}
		else
		{
			if (m_Agressive)
			{
				m_Pos.x +=8;
			}
			else
			{
				m_Pos.x +=4;
			}
		}
	}

	m_HitEnemyPtr->SetPos(m_Pos.x+20,m_Pos.y+4);	
	
}


void Mushroom::Paint(MATRIX3X2 matview)
{
	MATRIX3X2 matTranslate,matView,matIdentity, matCenter,matScale;
	matView = matview;
	RECT rect;

	if (m_Alive)
	{
		//SET BOUNDS RECT
		rect.top = 0 +(m_Height*2*(m_GettingHit%2));
		rect.bottom = rect.top+m_Height;
		rect.left = (m_Width*(((int)(m_CurrentAnimationStep/2)%4)));
		rect.right = rect.left+m_Width;

		if (m_Agressive == true)
		{
			rect.top = m_Height +(m_Height*2*(m_GettingHit%2));
			rect.bottom = rect.top+m_Height;
			rect.left = (m_Width*(m_CurrentAnimationStep%4));
			rect.right = rect.left+m_Width;
		}
		
		matCenter.SetAsTranslate(-m_Width/2,0);

		if (m_Direction == true)
		{
			matScale.SetAsScale(-1,1);
		}

		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matCenter.Inverse()*matTranslate*matView);
		GAME_ENGINE->DrawBitmap(m_BmpEnemyPtr,0,0,rect);

		/*GAME_ENGINE->SetTransformMatrix(matView);
		GAME_ENGINE->SetColor(255,0,0,100);
		GAME_ENGINE->FillHitRegion(m_HitEnemyPtr);*/
	}
}

void Mushroom::Spawn(int posX,int posY)
{
	m_Health = 5;
	m_Pos.x = posX;
	m_Pos.y = posY;
	m_Alive = false;
	//m_Direction = false;
	m_SpawnTime = 20;
}

void Mushroom::Hit(int amountOfDamage)
{
	m_GettingHit = 10;
	--m_Health;
}


void Mushroom::Destroy(bool brutally)
{
	m_Alive = false;
	m_Pos.x = 0;
	m_Pos.y = 0;
}

void Mushroom::CollisionDetection()
{
	RECT2 rect = m_HitEnemyPtr->GetBounds();
	

	if (m_Direction  == false && (m_HitLevelPtr->HitTest(rect.right+1,rect.top)|| m_HitLevelPtr->HitTest(rect.right+2,rect.bottom) == false  || m_HitLevelPtr->HitTest(rect.right+1,rect.bottom-1)))
	{
		m_Direction = !m_Direction;
	}

	if (m_Direction  == true && (m_HitLevelPtr->HitTest(rect.left-1,rect.top)|| m_HitLevelPtr->HitTest(rect.left-1,rect.bottom) == false  || m_HitLevelPtr->HitTest(rect.left-1,rect.bottom-1)))
	{
		m_Direction = !m_Direction;
	}
}

void Mushroom::AgressiveAI(DOUBLE2 posHero)
{
	if (posHero.y+20 == m_Pos.y && rand()%30 == 0 && -350 < posHero.x - m_Pos.x && 350 > posHero.x - m_Pos.x )
	{
		m_Agressive = true;

		if (posHero.x <= m_Pos.x)
		{
			m_Direction = true;
		}
		else
		{
			m_Direction = false;
		}

	}
	else
	{
		if (rand()%70 == 0)
		{
			m_Agressive = false;
		}
	}
}

HitRegion * Mushroom::GetBoltHitRegion()
{
	return 0;
}

void Mushroom::DestroyBolt()
{

}