//-----------------------------------------------------------------
// Game File
// C++ Source - HocusPocus.cpp - version 2012 v2_10
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "HocusPocus.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// HocusPocus methods																				
//-----------------------------------------------------------------

HocusPocus::HocusPocus():m_HeroPtr(0),m_BmpLevelPtr(0),m_HitLevelPtr(0), m_BmpHudPtr(0), m_BmpBackgroundPtr(0)
					,m_PosCamera(0,0),m_DebugScreenActive(false),m_FillBackgroundEffectCrystal(0)
					,m_GoldKeyPossession(false),m_SilverKeyPossession(false), m_GodMode(false)
					,m_DeathSequence(0),m_PausePrevious(false),m_Pause(false),m_GodModePrevious(false),m_DebugScreenActivePrevious(false)
					,m_Time(0.0),m_CrystalMax(5),m_TreasurePickedUp(0),m_TreasureAmount(0)
{
	// nothing to create
}

HocusPocus::~HocusPocus()																						
{
	delete m_HeroPtr;
	m_HeroPtr = 0;
	
	delete m_BmpLevelPtr;
	m_BmpLevelPtr = 0;

	delete m_HitLevelPtr;
	m_HitLevelPtr = 0;

	delete m_BmpHudPtr;
	m_BmpHudPtr = 0;

	delete m_BmpBackgroundPtr;
	m_BmpBackgroundPtr = 0;

	delete m_BmpKeyPtr;
	m_BmpKeyPtr = 0;

	delete m_ScoreTextPtrPtr;
	m_ScoreTextPtrPtr = 0;

	
	for (int i = 0; i < MAXBOLT; ++i)
	{
		delete m_BoltPtr[i];
		m_BoltPtr[i] = 0;
	}

	for (int i = 0; i < MAXBOLT; ++i)
	{
		delete m_ExplosionPtr[i];
		m_ExplosionPtr[i] = 0;
	}

	for (int i = 0; i < MAXENEMIES; ++i)
	{
		delete m_EnemyPtr[i];
		m_EnemyPtr[i] = 0;
	}

	for (int i = 0; i < MAXSTARS; ++i)
	{
		delete m_StarsPtr[i];
		m_StarsPtr[i] = 0;
	}

	for (int i = 0; i < MAXTRIGGER; ++i)
	{
		delete m_HitTriggerPtr[i];
		m_HitTriggerPtr[i] = 0;
	}

	for (int i = 0; i < MAXPICKUPS; ++i)
	{
		delete m_PickupPtr[i];
		m_PickupPtr[i] = 0;
	}

	for (int i = 0; i < MAXLOCKS; ++i)
	{
		delete m_LockPtr[i];
		m_LockPtr[i] = 0;
	}

	for (int i = 0; i < MAXBLOCKS; ++i)
	{
		delete m_BlockPtr[i];
		m_BlockPtr[i] = 0;
	}

	for (int i = 0; i < MAXLAVA; ++i)
	{
		delete m_LavaPtr[i];
		m_LavaPtr[i] = 0;
	}

	for (int i = 0; i < MAXSWITCHES; ++i)
	{
		delete m_SwitchPtr[i];
		m_SwitchPtr[i] = 0;
	}

	for (int i = 0; i < MAXWIZARDTEXT; ++i)
	{
		delete  m_WizardTextPtr[i];
		m_WizardTextPtr[i] = 0;
	}
}

void HocusPocus::GameInitialize(HINSTANCE hInstance)			
{
	// Set the required values
	AbstractGame::GameInitialize(hInstance);
	GAME_ENGINE->SetTitle("HocusPocus - De Puysseleir Wout - 1DAE2");					
	GAME_ENGINE->RunGameLoop(true);
	
	// Set the optional values
	GAME_ENGINE->SetWidth(640);
	GAME_ENGINE->SetHeight(400);
    GAME_ENGINE->SetFrameRate(19); //framerate is 19-20 (eerder 19)
	GAME_ENGINE->SetTickPaintRatio(1);
	//GAME_ENGINE->SetKeyList(String("QSDZ") + (TCHAR) VK_SPACE);
}

void HocusPocus::GameStart()
{
	m_BmpLevelPtr = new Bitmap("./Resources/Map.png");
	m_BmpLevelPtr->SetTransparencyColor(255,0,255);

	m_HitLevelPtr = new HitRegion();
	m_HitLevelPtr->CreateFromFile("./Resources/MapCollision.svg");

	m_BmpHudPtr = new Bitmap("./Resources/Hud.png");
	m_BmpHudPtr->SetTransparencyColor(255,0,255);

	m_BmpBackgroundPtr = new Bitmap("./Resources/Background.png");

	m_BmpKeyPtr = new Bitmap("./Resources/KeyPickup.png");
	m_BmpKeyPtr->SetTransparencyColor(255,0,255);


	m_HeroPtr = new Hero(95,858,false, m_HitLevelPtr); //Startpositie is (92,858)

	for (int i = 0; i < MAXBOLT; ++i)
	{
		m_BoltPtr[i] = new Bolt();
	}

	DOUBLE2 pos;
	pos.x = 0;
	pos.y = 0;

	//CREATE SMALLEXPLOTIONS
	for (int i = 0; i < MAXEXPLOSIONS/2; ++i)
	{
		m_ExplosionPtr[i] = new SmallExplosion(pos);
	}

	//CREATE BIGEXPLOTIONS
	for (int i = MAXEXPLOSIONS/2; i < MAXEXPLOSIONS; ++i)
	{
		m_ExplosionPtr[i] = new BigExplosion(pos);
	}

	pos.x = 500;
	pos.y = 750;

	//CREATE STARS
	for (int i = 0; i <  MAXSTARS; ++i)
	{
		m_StarsPtr[i] = new Stars();
	}

	//CREATE TRIGGER
	for (int i = 0; i <  MAXTRIGGER; ++i)
	{
		m_HitTriggerPtr[i] = new HitRegion();
	}

	//CREATE SCORETEXT
	m_ScoreTextPtrPtr = new ScoreText();


	//CREATE WIZARDTEXT
	for (int i = 0; i < MAXWIZARDTEXT; ++i)
	{
		m_WizardTextPtr[i] = new WizardText();
	}

	int j = 0;
	m_WizardTextPtr[j++]->Create("So... another brave apprentice!\nYou'll never make it trough\nthese castle walls alive! Bahaha!",516,736);
	m_WizardTextPtr[j++]->Create("You might find a silver key to\nyour left and up the stairway.\nBut you'll never find the secret\ntreasure room in this castle!",1412,736);
	m_WizardTextPtr[j++]->Create("So you found the secret treasure\nroom. Perhaps I misjudged you.\nYou are still doomed to failure!",5636,864);
	

	//LIST ALL TRIGGER ON THE CORRECT POSITION
	j = 0;
	m_HitTriggerPtr[j++]->CreateFromRect(1066,352,8,192);
	m_HitTriggerPtr[j++]->CreateFromRect(943,846,113,4);
	m_HitTriggerPtr[j++]->CreateFromRect(1472,704,4,96);
	m_HitTriggerPtr[j++]->CreateFromRect(2021,686,3,50);
	m_HitTriggerPtr[j++]->CreateFromRect(1717,580,3,60);
	m_HitTriggerPtr[j++]->CreateFromRect(1922,858,158,3);
	m_HitTriggerPtr[j++]->CreateFromRect(2399,480,3,448);
	m_HitTriggerPtr[j++]->CreateFromRect(3179,96,7,352);
	m_HitTriggerPtr[j++]->CreateFromRect(2240,96,5,224);
	m_HitTriggerPtr[j++]->CreateFromRect(1032,96,7,128);
	m_HitTriggerPtr[j++]->CreateFromRect(4240,800,64,96);

	//CREATE ENEMIES
	j = 0;

	m_EnemyPtr[j++] = new Mushroom(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, true);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, true);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, true);
	//10
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Devil(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Devil(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Devil(m_HitLevelPtr, false);
	
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);

	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, true);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, true);

	//20
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Mushroom(m_HitLevelPtr, false);

	m_EnemyPtr[j++] = new Devil(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Devil(m_HitLevelPtr, false);
	m_EnemyPtr[j++] = new Devil(m_HitLevelPtr, false);

	m_EnemyPtr[j++] = new Devil(m_HitLevelPtr, false);

	m_EnemyPtr[j++] = new Crocodile(m_HitLevelPtr, true);


	//CREATE SWITCHES
	j = 0;

	m_SwitchPtr[j++] = new Switch(3840,800);
	m_SwitchPtr[j++] = new Switch(4576,704);

	//CREATE LAVA
	j = 0;
	
	//SECOND
	m_LavaPtr[j++] = new Lava(3936+j*32,896,1);
	m_LavaPtr[j++] = new Lava(3936+j*32,896,5);
	m_LavaPtr[j++] = new Lava(3936+j*32,896,7);
	m_LavaPtr[j++] = new Lava(3936+j*32,896,2);
	m_LavaPtr[j++] = new Lava(3936+j*32,896,4);
	m_LavaPtr[j++] = new Lava(3936+j*32,896,7);
	m_LavaPtr[j++] = new Lava(3936+j*32,896,3);
	m_LavaPtr[j++] = new Lava(3936+j*32,896,0);
	m_LavaPtr[j++] = new Lava(3936+j*32,896,2);

	//FIRST
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,0);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,4);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,7);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,6);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,4);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,0);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,2);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,5);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,6);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,4);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,6);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,5);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,1);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,6);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,7);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,0);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,4);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,3);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,7);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,2);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,0);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,2);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,3);
	m_LavaPtr[j++] = new Lava(2368+(j-9)*32,896,0);

	//CREATE DISAPPEARING BLOCKS
	j = 0;

	//SILVERLOCK WALLS
	m_BlockPtr[j++] = new Block(1696,864,2,false);
	m_BlockPtr[j++] = new Block(1696,896,2,false);

	//GOLDLOCK WALLS
	m_BlockPtr[j++] = new Block(3584,352,2,false);
	m_BlockPtr[j++] = new Block(3584+32,352,0,false);
	m_BlockPtr[j++] = new Block(3584+32+32,352,1,false);
	m_BlockPtr[j++] = new Block(3584+32+64,352,2,false);
	m_BlockPtr[j++] = new Block(3584+32+64+32,352,2,false);
	m_BlockPtr[j++] = new Block(3584+32+64+32+32,352,0,false);
	m_BlockPtr[j++] = new Block(3584+32+64+32+32+32,352,1,false);
	m_BlockPtr[j++] = new Block(3584+32+64+32+32+64,352,2,false);

	m_BlockPtr[j++] = new Block(3584,416,2,false);
	m_BlockPtr[j++] = new Block(3584+32,416,0,false);
	m_BlockPtr[j++] = new Block(3584+32+32,416,1,false);
	m_BlockPtr[j++] = new Block(3584+32+64,416,2,false);
	m_BlockPtr[j++] = new Block(3584+32+64+32,416,2,false);
	m_BlockPtr[j++] = new Block(3584+32+64+32+32,416,0,false);
	m_BlockPtr[j++] = new Block(3584+32+64+32+32+32,416,1,false);
	m_BlockPtr[j++] = new Block(3584+32+64+32+32+64,416,2,false);

	m_BlockPtr[j++] = new Block(3584,384,0,false);
	m_BlockPtr[j++] = new Block(3584+32,384,1,false);
	//20
	m_BlockPtr[j++] = new Block(3584+32+32,384,0,false);
	m_BlockPtr[j++] = new Block(3584+32+64,384,1,false);
	m_BlockPtr[j++] = new Block(3584+32+64+32,384,0,false);
	m_BlockPtr[j++] = new Block(3584+32+64+32+32,384,1,false);
	m_BlockPtr[j++] = new Block(3584+32+64+32+32+32,384,0,false);
	m_BlockPtr[j++] = new Block(3584+32+64+32+32+64,384,1,false);

	//DESTRUCTABLE
	m_BlockPtr[j++] = new Block(4544,704,5,true);
	m_BlockPtr[j++] = new Block(4576,704,5,true);
	m_BlockPtr[j++] = new Block(4608,704,5,true);
	m_BlockPtr[j++] = new Block(4544,736,5,true);
	m_BlockPtr[j++] = new Block(4576,736,5,true);
	m_BlockPtr[j++] = new Block(4608,736,5,true);
	//32

	//LEFTSWITCH
	m_BlockPtr[j++] = new Block(3520+(j-32)*32,768,0,false);
	m_BlockPtr[j++] = new Block(3520+(j-32)*32,768,1,false);
	m_BlockPtr[j++] = new Block(3520+(j-32)*32,768,0,false);
	m_BlockPtr[j++] = new Block(3520+(j-32)*32,768,1,false);
	m_BlockPtr[j++] = new Block(3520+(j-32)*32,768,0,false);
	m_BlockPtr[j++] = new Block(3520+(j-32)*32,768,1,false);
	m_BlockPtr[j++] = new Block(3520+(j-32)*32,768,0,false);
	m_BlockPtr[j++] = new Block(3520+(j-32)*32,768,1,false);

	m_BlockPtr[j++] = new Block(3520+(j-40)*32,832,0,false);
	m_BlockPtr[j++] = new Block(3520+(j-40)*32,832,1,false);
	m_BlockPtr[j++] = new Block(3520+(j-40)*32,832,0,false);
	m_BlockPtr[j++] = new Block(3520+(j-40)*32,832,1,false);
	m_BlockPtr[j++] = new Block(3520+(j-40)*32,832,0,false);
	m_BlockPtr[j++] = new Block(3520+(j-40)*32,832,1,false);
	m_BlockPtr[j++] = new Block(3520+(j-40)*32,832,0,false);
	m_BlockPtr[j++] = new Block(3520+(j-40)*32,832,1,false);

	m_BlockPtr[j++] = new Block(3520+(j-48)*32,800,4,false);
	m_BlockPtr[j++] = new Block(3520+(j-48)*32,800,0,false);
	m_BlockPtr[j++] = new Block(3520+(j-48)*32,800,1,false);
	m_BlockPtr[j++] = new Block(3520+(j-48)*32,800,0,false);
	m_BlockPtr[j++] = new Block(3520+(j-48)*32,800,1,false);
	m_BlockPtr[j++] = new Block(3520+(j-48)*32,800,0,false);
	m_BlockPtr[j++] = new Block(3520+(j-48)*32,800,1,false);
	m_BlockPtr[j++] = new Block(3520+(j-48)*32,800,4,false);
	//56

	//RIGHTSWITCH
	m_BlockPtr[j++] = new Block(4640+(j-56)*32,704,0,false);
	m_BlockPtr[j++] = new Block(4640+(j-56)*32,704,1,false);
	m_BlockPtr[j++] = new Block(4640+(j-56)*32,704,0,false);
	m_BlockPtr[j++] = new Block(4640+(j-56)*32,704,1,false);
	m_BlockPtr[j++] = new Block(4640+(j-56)*32,704,0,false);
	m_BlockPtr[j++] = new Block(4640+(j-56)*32,704,1,false);
	m_BlockPtr[j++] = new Block(4640+(j-56)*32,704,0,false);
	m_BlockPtr[j++] = new Block(4640+(j-56)*32,704,1,false);
	m_BlockPtr[j++] = new Block(4640+(j-56)*32,704,0,false);
	m_BlockPtr[j++] = new Block(4640+(j-56)*32,704,1,false);
	m_BlockPtr[j++] = new Block(4640+(j-56)*32,704,0,false);
	m_BlockPtr[j++] = new Block(4640+(j-56)*32,704,1,false);
	//68
	m_BlockPtr[j++] = new Block(4640+(j-68)*32,736,3,false);
	m_BlockPtr[j++] = new Block(4640+(j-68)*32,736,0,false);
	m_BlockPtr[j++] = new Block(4640+(j-68)*32,736,1,false);
	m_BlockPtr[j++] = new Block(4640+(j-68)*32,736,0,false);
	m_BlockPtr[j++] = new Block(4640+(j-68)*32,736,1,false);
	m_BlockPtr[j++] = new Block(4640+(j-68)*32,736,0,false);
	m_BlockPtr[j++] = new Block(4640+(j-68)*32,736,1,false);
	m_BlockPtr[j++] = new Block(4640+(j-68)*32,736,0,false);
	m_BlockPtr[j++] = new Block(4640+(j-68)*32,736,1,false);
	m_BlockPtr[j++] = new Block(4640+(j-68)*32,736,0,false);
	m_BlockPtr[j++] = new Block(4640+(j-68)*32,736,1,false);
	m_BlockPtr[j++] = new Block(4640+(j-68)*32,736,3,false);
	//80

	//CREATE PICKUPS
	j = 0;

	//RODE DIAMANT = 0
	//GRIJZE DIAMANT = 1
	//KROON = 2
	//BEKER = 3

	m_PickupPtr[j++] = new ScorePickup(1152,734,1);
	m_PickupPtr[j++] = new ScorePickup(1216,734,1);
	m_PickupPtr[j++] = new ScorePickup(1280,789,2);
	m_PickupPtr[j++] = new ScorePickup(1312,789,2);
	m_PickupPtr[j++] = new ScorePickup(708,896,3);
	m_PickupPtr[j++] = new ScorePickup(773,896,3);

	m_PickupPtr[j++] = new HealthPickup(1250,900);
	m_PickupPtr[j++] = new HealthPickup(1314,900);

	m_PickupPtr[j++] = new CrystalPickup(576,868);
	m_PickupPtr[j++] = new CrystalPickup(1984,836);
	//10
	m_PickupPtr[j++] = new HealthPickup(1730,804);
	m_PickupPtr[j++] = new HealthPickup(1794,804);

	m_PickupPtr[j++] = new KeyPickup(554,518,0);
	m_PickupPtr[j++] = new KeyPickup(1354,294,1);
	m_PickupPtr[j++] = new ExtraShotPickup(864,524);
	m_PickupPtr[j++] = new ScorePickup(1060,512,3);
	m_PickupPtr[j++] = new ScorePickup(676,512,3);

	m_PickupPtr[j++] = new ScorePickup(1760,894,0);
	m_PickupPtr[j++] = new ScorePickup(1824,894,0);
	m_PickupPtr[j++] = new ScorePickup(1888,894,0);
	//20
	m_PickupPtr[j++] = new ScorePickup(1952,894,0);
	m_PickupPtr[j++] = new ScorePickup(2016,894,0);

	m_PickupPtr[j++] = new ScorePickup(1696,606,1);
	m_PickupPtr[j++] = new ScorePickup(1760,606,0);
	
	m_PickupPtr[j++] = new ScorePickup(1824,606,1);
	m_PickupPtr[j++] = new ScorePickup(1888,606,0);
	m_PickupPtr[j++] = new ScorePickup(1952,606,1);

	m_PickupPtr[j++] = new ScorePickup(1728,702,0);
	m_PickupPtr[j++] = new ScorePickup(1792,702,1);
	m_PickupPtr[j++] = new ScorePickup(1856,702,0);
	//30
	m_PickupPtr[j++] = new ScorePickup(1920,702,1);
	m_PickupPtr[j++] = new ScorePickup(1984,702,0);
	m_PickupPtr[j++] = new ScorePickup(2048,702,1);

	m_PickupPtr[j++] = new ScorePickup(1760,510,1);
	m_PickupPtr[j++] = new ScorePickup(1824,510,0);
	m_PickupPtr[j++] = new ScorePickup(1888,510,1);
	m_PickupPtr[j++] = new ScorePickup(1952,510,0);
	m_PickupPtr[j++] = new ScorePickup(2016,510,1);

	m_PickupPtr[j++] = new ScorePickup(3204,864,3);
	m_PickupPtr[j++] = new ScorePickup(3268,864,3);
	//40
	m_PickupPtr[j++] = new ScorePickup(3524,672,3);
	m_PickupPtr[j++] = new CrystalPickup(3040,388);

	m_PickupPtr[j++] = new ScorePickup(2756,416,3);
	m_PickupPtr[j++] = new ScorePickup(2884,416,3);

	m_PickupPtr[j++] = new HealthPickup(2466,420);
	m_PickupPtr[j++] = new HealthPickup(2242,292);
	m_PickupPtr[j++] = new HealthPickup(1730,292);

	m_PickupPtr[j++] = new ScorePickup(1860,288,3);
	m_PickupPtr[j++] = new ScorePickup(2116,288,3);

	m_PickupPtr[j++] = new ScorePickup(1696+(j-49)*64,190,0);
	//50
	m_PickupPtr[j++] = new ScorePickup(1696+(j-49)*64,190,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-49)*64,190,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-49)*64,190,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-49)*64,190,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-49)*64,190,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-49)*64,190,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-49)*64,190,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-49)*64,190,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-49)*64,190,0);

	m_PickupPtr[j++] = new ScorePickup(1696+(j-59)*64,254,0);
	//60
	m_PickupPtr[j++] = new ScorePickup(1696+(j-59)*64,254,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-59)*64,254,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-59)*64,254,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-59)*64,254,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-59)*64,254,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-59)*64,254,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-59)*64,254,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-59)*64,254,0);
	m_PickupPtr[j++] = new ScorePickup(1696+(j-59)*64,254,0);

	m_PickupPtr[j++] = new CrystalPickup(1504,164);
	//70
	m_PickupPtr[j++] = new ScorePickup(1316,192,3);
	m_PickupPtr[j++] = new ScorePickup(1124,192,3);
	m_PickupPtr[j++] = new ScorePickup(932,192,3);
	m_PickupPtr[j++] = new ScorePickup(676,192,3);

	m_PickupPtr[j++] = new ScorePickup(1248,308,2);
	m_PickupPtr[j++] = new ScorePickup(1088,308,2);
	m_PickupPtr[j++] = new ScorePickup(928,308,2);
	m_PickupPtr[j++] = new ScorePickup(768,308,2);
	m_PickupPtr[j++] = new ScorePickup(608,308,2);

	m_PickupPtr[j++] = new ScorePickup(4352,756,2);
	//80
	m_PickupPtr[j++] = new ScorePickup(4416,756,2);
	m_PickupPtr[j++] = new ScorePickup(4480,756,2);

	m_PickupPtr[j++] = new ScorePickup(4288,884,2);
	m_PickupPtr[j++] = new ScorePickup(4352,884,2);
	m_PickupPtr[j++] = new ScorePickup(4416,884,2);

	m_PickupPtr[j++] = new CrystalPickup(4480,836);

	m_PickupPtr[j++] = new ScorePickup(3552,852,2);
	m_PickupPtr[j++] = new ScorePickup(3616,852,2);
	m_PickupPtr[j++] = new ScorePickup(3680,852,2);
	m_PickupPtr[j++] = new ScorePickup(3744,852,2);
	//90

	m_PickupPtr[j++] = new ScorePickup(5216,916,2);
	m_PickupPtr[j++] = new ScorePickup(5280,916,2);
	m_PickupPtr[j++] = new ScorePickup(5344,916,2);
	m_PickupPtr[j++] = new ScorePickup(5408,916,2);
	m_PickupPtr[j++] = new ScorePickup(5472,916,2);
	m_PickupPtr[j++] = new ScorePickup(5536,916,2);

	m_PickupPtr[j++] = new ScorePickup(5312,830,1);
	m_PickupPtr[j++] = new ScorePickup(5440,830,1);

	m_PickupPtr[j++] = new ScorePickup(5248,862,0);
	m_PickupPtr[j++] = new ScorePickup(5376,862,0);
	//100
	m_PickupPtr[j++] = new ScorePickup(5504,862,0);

	//COUNT TREASURE
	for (int i = 0; i < MAXPICKUPS; ++i)
	{
		if (m_PickupPtr[i]->GetType() == 0)
		{
			++m_TreasureAmount;
		}
	}


	//CREATE LOCKS
	//SILVER = 0
	//GOLD = 1
	m_LockPtr[0] = new Lock(1568,864,0);
	m_LockPtr[1] = new Lock (3488,384,1);

	//SETKEYLIST
	GAME_ENGINE->SetKeyList("ABCDEFGHIJKLMNOQRSTUVWXYZ 0123456789");
}

//void HocusPocus::GameEnd()
//{
//	// Insert the code that needs to be executed at the closing of the game
//}
//
//void HocusPocus::GameActivate()
//{
//	// Insert the code that needs to be executed when the game window becomes active
//
//	/* Example:
//	GAME_ENGINE->SetSleep(false);
//	*/
//}
//
//void HocusPocus::GameDeactivate()
//{
//	// Insert the code that needs to be executed when the game window becomes inactive
//
//	/* Voorbeeld:
//	GAME_ENGINE->SetSleep(true);
//	*/
//}
//
//void HocusPocus::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
//{	
//	// Insert the code that needs to be executed when the game registers a mouse button action
//
//	/* Example:
//	if (isLeft == true && isDown == true) // is it a left mouse click?
//	{	
//		if ( x > 261 && x < 261 + 117 ) // check if click lies within x coordinates of choice
//		{
//			if ( y > 182 && y < 182 + 33 ) // check if click also lies within y coordinates of choice
//			{
//				GAME_ENGINE->MessageBox("Clicked.");
//			}
//		}
//	}
//	*/
//}
//
//void HocusPocus::MouseMove(int x, int y, WPARAM wParam)
//{	
//	// Insert the code that needs to be executed when the mouse pointer moves across the game window
//
//	/* Example:
//	if ( x > 261 && x < 261 + 117 ) // check if mouse position is within x coordinates of choice
//	{
//		if ( y > 182 && y < 182 + 33 ) // check if mouse position also is within y coordinates of choice
//		{
//			GAME_ENGINE->MessageBox("Da mouse wuz here.");
//		}
//	}
//	*/
//
//}

//void HocusPocus::CheckKeyboard()
//{	
//	// Here you can check if a key of choice is held down
//	// Is executed once per frame 
//
//}

void HocusPocus::KeyPressed(TCHAR cKey)
{	
	m_Pause = false;
}

void HocusPocus::GameTick(double deltaTime)
{
	//ADD TIME
	m_Time += deltaTime;

	//CHECK INPUTS
	if (GAME_ENGINE->IsKeyDown(VK_ESCAPE))
	{
		GAME_ENGINE->QuitGame();
	}

	if (GAME_ENGINE->IsKeyDown('R'))
	{
		ResetGame(false);
	}

	if (GAME_ENGINE->IsKeyDown('G') && m_GodModePrevious == false)
	{
		m_GodModePrevious = true;
		m_GodMode = !m_GodMode;
	}
	else if (GAME_ENGINE->IsKeyDown('G') == false)
	{
		m_GodModePrevious = false;
	}

	if (GAME_ENGINE->IsKeyDown('B') && m_DebugScreenActivePrevious == false)
	{
		m_DebugScreenActivePrevious = true;
		m_DebugScreenActive = !m_DebugScreenActive;
	}
	else if(GAME_ENGINE->IsKeyDown('B') == false)
	{
		m_DebugScreenActivePrevious = false;
	}

	if (GAME_ENGINE->IsKeyDown('P') && m_PausePrevious == false)
	{
		m_PausePrevious = true;
		m_Pause = !m_Pause;
	}
	else if (GAME_ENGINE->IsKeyDown('P') == false)
	{
		m_PausePrevious = false;
	}

	DisactivatePause();

	//TICK WIZARDTEXT
	for (int i = 0; i < MAXWIZARDTEXT; ++i)
	{
		m_WizardTextPtr[i]->Tick(deltaTime,m_HeroPtr);
	}

	CheckPauseWizards();

	if (m_Pause == false)
	{
		AllowedToFire();
		//CHECK INPUT FOR BOLT
		if (GAME_ENGINE->IsKeyDown(VK_MENU) && AllowedToFire() == true)
		{
			m_FireClick = true;
		
			for (int i = 0; i < m_HeroPtr->GetTimesAllowedToFire();++i)
			{
				if (m_BoltPtr[i]->GetFiring() == false)
				{
					m_BoltPtr[i]->Fire(m_HeroPtr->GetPos(),m_HeroPtr->GetDirection());
					i = m_HeroPtr->GetTimesAllowedToFire()-1;
				}
			}
		}

		//TICK PICKUPS
		for (int i = 0; i < MAXPICKUPS;++i)
		{
			m_PickupPtr[i]->Tick(deltaTime);
		}

		//TICK HERO
		if (m_GodMode == false)	
		{
			m_HeroPtr->Tick(deltaTime);
		}
		else
		{
			DOUBLE2 pos = m_HeroPtr->GetPos();
			if (GAME_ENGINE->IsKeyDown(VK_RIGHT)) pos.x += 64;
			if (GAME_ENGINE->IsKeyDown(VK_LEFT)) pos.x -= 64;
			if (GAME_ENGINE->IsKeyDown(VK_UP)) pos.y -= 64;
			if (GAME_ENGINE->IsKeyDown(VK_DOWN)) pos.y += 64;
			m_HeroPtr->SetPos(pos);
		}
		//TICK BOLTS
		for (int i = 0; i < MAXBOLT;++i)
		{
			m_BoltPtr[i]->Tick(deltaTime,m_HeroPtr);
		}

		//TICK EXPLOSIONS
		for (int i = 0; i < MAXEXPLOSIONS; ++i)
		{
			m_ExplosionPtr[i]->Tick(deltaTime);
		}

		//TICK ENEMIES
		for (int i = 0; i < MAXENEMIES; ++i)
		{
			m_EnemyPtr[i]->Tick(deltaTime, m_HeroPtr->GetPos());
		}

		//TICK STARS
		for (int i = 0; i < MAXSTARS; ++i)
		{
			m_StarsPtr[i]->Tick(deltaTime);
		}

		//TICK LOCKS
		for (int i = 0; i < MAXLOCKS; ++i)
		{
			m_LockPtr[i]->Tick(deltaTime);
		}

		//TICK DISAPPEARING BLOCKS
		for (int i = 0; i <  MAXBLOCKS; ++i)
		{
			m_BlockPtr[i]->Tick(deltaTime);
		}

		//TICK LAVA
		for (int i = 0; i <  MAXLAVA; ++i)
		{
			m_LavaPtr[i]->Tick(deltaTime);
		}

		//TICK SWICTH
		for (int i = 0; i <  MAXSWITCHES; ++i)
		{
			m_SwitchPtr[i]->Tick(m_HeroPtr->GetHitRegion(), deltaTime);
		}

		DestroyWalls();

		//CHECK COLLISION FOR ALL OBJECTS
		CollisionAll();

		//CHECK DEATH
		CheckDeath();

		//CHECK WIN
		CheckWin();

		//DO EFFECTS
		CreateStarSpawnBox();

		//CAMERAFOLLOW
		CameraFollow();

	}

}

void HocusPocus::GamePaint(RECT rect)
{
	//CREATE MATRICES
	MATRIX3X2 matTranslate,matView,matIdentity, matCenter,matScale,matBackgroundTranslate;

	//CREATE CAMERAMATRIX
	matTranslate.SetAsTranslate(m_PosCamera);
	matView = matTranslate.Inverse();

	//CREATE AN IDENTITY TO SET HUD AND DEBUGSCREEN
	matIdentity.SetAsIdentity();

	//DRAW SCROLLING BACKGROUND
	DOUBLE2 posCamera = m_PosCamera; 
	posCamera.x = posCamera.x / 2;
	matBackgroundTranslate.SetAsTranslate(posCamera);


	GAME_ENGINE->SetTransformMatrix(matBackgroundTranslate*matView);
	GAME_ENGINE->DrawBitmap(m_BmpBackgroundPtr,0,0);
	GAME_ENGINE->DrawBitmap(m_BmpBackgroundPtr,640,0);
	GAME_ENGINE->DrawBitmap(m_BmpBackgroundPtr,640*2,0);
	GAME_ENGINE->DrawBitmap(m_BmpBackgroundPtr,640*3,0);
	GAME_ENGINE->DrawBitmap(m_BmpBackgroundPtr,640*4,0);

	//DRAW BITMAP
	GAME_ENGINE->SetTransformMatrix(matView);
	GAME_ENGINE->DrawBitmap(m_BmpLevelPtr,0,0);

	//DRAW HITREGION
	//GAME_ENGINE->SetColor(255,0,0,100);
	//GAME_ENGINE->FillHitRegion(m_HitLevelPtr);

	//DRAWTRIGGER
	/*GAME_ENGINE->SetColor(0,255,0,100);
	for (int i = 0; i < MAXTRIGGER ; ++i)
	{
		GAME_ENGINE->FillHitRegion(m_HitTriggerPtr[i]);
	}*/

	GAME_ENGINE->SetColor(255,0,0,100);

	//PAINT SWICTH
	for (int i = 0; i < MAXSWITCHES; ++i)
	{
		m_SwitchPtr[i]->Paint(matView);
	}

	//DRAW ALL PICKUPS
	for (int i = 0; i < MAXPICKUPS; ++i)
	{
		m_PickupPtr[i]->Paint(matView);
	}

	//PAINT DISAPPEARING BLOCKS
	for (int i = 0; i <  MAXBLOCKS; ++i)
	{
		m_BlockPtr[i]->Paint(matView);
	}

	//PAINT BOLT
	for (int i = 0; i < MAXBOLT;++i)
	{
		m_BoltPtr[i]->Paint(matView);
	}

	//PAINT EXPLOSIONS
	for (int i = 0; i < MAXEXPLOSIONS; ++i)
	{
		m_ExplosionPtr[i]->Paint(matView);
	}

	//PAINT STARS
	for (int i = 0; i < MAXSTARS; ++i)
	{
		m_StarsPtr[i]->Paint(matView);
	}

	//PAINT LOCKS
	for (int i = 0; i < MAXLOCKS; ++i)
	{
		m_LockPtr[i]->Paint(matView);
	}

	//PAINT ENEMIES
	for (int i = 0; i < MAXENEMIES; ++i)
	{
		m_EnemyPtr[i]->Paint(matView);
	}

	//PAINT LAVA
	for (int i = 0; i < MAXLAVA; ++i)
	{
		m_LavaPtr[i]->Paint(matView);
	}
	
	//FILL BACKGROUND FOR CRYSTAL EFFECT
	if (m_FillBackgroundEffectCrystal > 0)
	{
		switch (m_FillBackgroundEffectCrystal)
		{
			case 8:
				GAME_ENGINE->DrawSolidBackground(69,0,0);
				break;

			case 7:
				GAME_ENGINE->DrawSolidBackground(255,0,0);
				break;

			case 6:
				GAME_ENGINE->DrawSolidBackground(227,0,0);
				break;

			case 5:
				GAME_ENGINE->DrawSolidBackground(203,0,0);
				break;

			case 4:
				GAME_ENGINE->DrawSolidBackground(174,0,0);
				break;

			case 3:
				GAME_ENGINE->DrawSolidBackground(150,0,0);
				break;

			case 2:
				GAME_ENGINE->DrawSolidBackground(121,0,0);
				break;

			case 1:
				GAME_ENGINE->DrawSolidBackground(97,0,0);
				break;

			case 0:

				break;
		}
		--m_FillBackgroundEffectCrystal;
	}



	//PAINT HERO
	m_HeroPtr->Paint(matView);

	//PAINT WIZARDTEXT
	for (int i = 0; i < MAXWIZARDTEXT; ++i)
	{
		m_WizardTextPtr[i]->Paint(matView);
	}

	//GAME_ENGINE->DrawCoordinateSystem(50);
	GAME_ENGINE->SetTransformMatrix(matIdentity);
	
	//PAINT STATISTICS +HUD
	GAME_ENGINE->DrawBitmap(m_BmpHudPtr,0,GAME_ENGINE->GetHeight()-m_BmpHudPtr->GetHeight());
	PaintHudStatistics(matIdentity);

	//PAINT DEATHRECTANGLE
	GAME_ENGINE->SetTransformMatrix(matIdentity);
	if (m_DeathSequence <= 11 && m_HeroPtr->GetAlive() == false && m_DeathSequence != 0)
	{
		GAME_ENGINE->SetColor(0,0,0,255 - m_DeathSequence*20);
		GAME_ENGINE->FillRect(0,0,GAME_ENGINE->GetWidth(),GAME_ENGINE->GetHeight());
	}
	

	if (m_DebugScreenActive)
	{
		DOUBLE2 tempVelocity = m_HeroPtr->GetVelocity();
		DOUBLE2 posH = m_HeroPtr->GetPos();
		GAME_ENGINE->SetColor(0,0,0);
		GAME_ENGINE->FillRect(0,0,150,190);
		GAME_ENGINE->SetColor(255,0,0);
		GAME_ENGINE->DrawString(String ("y = ") + tempVelocity.y,10,10);
		GAME_ENGINE->DrawString(String ("Ceiling = ") + m_HeroPtr->GetHitBool(0),10,30);
		GAME_ENGINE->DrawString(String ("Ground = ") + m_HeroPtr->GetHitBool(1),10,40);
		GAME_ENGINE->DrawString(String ("Left = ") + m_HeroPtr->GetHitBool(2),10,50);
		GAME_ENGINE->DrawString(String ("Right = ") + m_HeroPtr->GetHitBool(3),10,60);
		GAME_ENGINE->DrawString(String ("State = ") + m_HeroPtr->GetState(),10,80);
		GAME_ENGINE->DrawString(String ("Allowed to jump = ") + m_HeroPtr->GetAllowedToJump(),10,100);
		GAME_ENGINE->DrawString(String ("jump = ") + m_HeroPtr->GetJump(),10,110);
		GAME_ENGINE->DrawString(String ("") + posH.ToString(),10,120);
		GAME_ENGINE->DrawString(String("") + m_HeroPtr->GetScore(),10,130);
		GAME_ENGINE->DrawString(String("") + m_HeroPtr->GetHealth(),10,140);
		GAME_ENGINE->DrawString(String("") + m_HeroPtr->GetCrystal(),10,150);
		GAME_ENGINE->DrawString(String("") + m_FillBackgroundEffectCrystal,10,160);
		GAME_ENGINE->DrawString(String("") + (int)m_Time,10,170);
	}

}

//void HocusPocus::CallAction(Caller* callerPtr)
//{
//	// Insert the code that needs to be executed when a Caller has to perform an action
//}


void HocusPocus::CameraFollow()
{
	DOUBLE2 tempPos = m_HeroPtr->GetPos();

	
	if (m_GodMode == false)
	{
		m_PosCamera.x =  tempPos.x - GAME_ENGINE->GetWidth()/2-27 + m_HeroPtr->GetWidth()/2;
	
		if (m_HeroPtr->GetState() == 0)
		{
			m_PosCamera.y =  tempPos.y - GAME_ENGINE->GetHeight()/2+11 + m_HeroPtr->GetHeight()/2;
		}

		if (tempPos.y >= m_PosCamera.y + 160)
		{
			m_PosCamera.y = tempPos.y - 160;
		}

	
		//EXCEPTIONS (e.g. OUTSIDE OF GAME LEFT OR DOWN)
		//EXCEPTION LEFT
		if (m_PosCamera.x < 0)
		{
			m_PosCamera.x = 0;
		}

		//EXCEPTION DOWN
		if (m_PosCamera.y > m_BmpLevelPtr->GetHeight() - GAME_ENGINE->GetHeight()+ m_BmpHudPtr->GetHeight())
		{
			m_PosCamera.y = m_BmpLevelPtr->GetHeight() - GAME_ENGINE->GetHeight()+ m_BmpHudPtr->GetHeight();
		}
	}
	else
	{
		m_PosCamera.x =  tempPos.x - GAME_ENGINE->GetWidth()/2-10 + m_HeroPtr->GetWidth()/2;
		m_PosCamera.y =  tempPos.y - GAME_ENGINE->GetHeight()/2+11 + m_HeroPtr->GetHeight()/2;
	
	}
}

bool HocusPocus::AllowedToFire()
{
	if (m_HeroPtr->GetAlive() == false)
	{
		return false;
	}

	if (GAME_ENGINE->IsKeyDown(VK_MENU) == false)
	{
		m_FireClick = false;
	}
	
	if (m_FireClick == true)
	{
		return false;
	}

	return true;
}

bool HocusPocus::CollisionDetection(HitRegion * hitr1, HitRegion * hitr2)
{
	if (hitr1->HitTest(hitr2) == true)
	{
		return true;
	}

	return false;
}

void HocusPocus::CollisionBoltEnemy()
{
	DOUBLE2 pos;
	for (int i = 0; i < MAXBOLT; ++i)
	{
		for (int j = 0; j <MAXENEMIES; ++j)
		{
			pos = m_BoltPtr[i]->GetPos();
			if (m_BoltPtr[i]->GetFiring() == true)
			{
				if (CollisionDetection(m_EnemyPtr[j]->GetHitRegion(), m_BoltPtr[i]->GetHitRegion()) && m_EnemyPtr[j]->GetAlive() == true)
				{
					m_BoltPtr[i]->Destroy();
					m_EnemyPtr[j]->Hit(1);
					if (m_EnemyPtr[j]->GetHealth() <= 0)
					{
						CreateBigExplosion(m_BoltPtr[i]->GetPos());
						m_EnemyPtr[j]->Destroy(true);

					}
					else
					{
						CreateSmallExplosion(m_BoltPtr[i]->GetPos());
					}
				}
			}
		}
	}
}

void HocusPocus::CollisionBoltWallAndScreen()
{
	DOUBLE2 pos;
	for (int i = 0; i < MAXBOLT; ++i)
	{
		pos = m_BoltPtr[i]->GetPos();
		if (m_BoltPtr[i]->GetFiring() == true)
		{
			if (CollisionDetection(m_HitLevelPtr, m_BoltPtr[i]->GetHitRegion()) || pos.x > m_BmpLevelPtr->GetWidth())
			{
				m_BoltPtr[i]->Destroy();
				CreateSmallExplosion(m_BoltPtr[i]->GetPos());
			}

			if (pos.x < -64)
			{
				m_BoltPtr[i]->Destroy();
			}

			if (pos.x < m_PosCamera.x-32)
			{
				m_BoltPtr[i]->Destroy();
			}
			else if (pos.x > m_PosCamera.x+GAME_ENGINE->GetWidth()+32)
			{
				m_BoltPtr[i]->Destroy();
			}
		}
	}
}

void HocusPocus::CollisionHeroEnemy()
{
	DOUBLE2 pos;
	
	if (m_HeroPtr->GettingHit() == false)
	{
		for (int i = 0; i < MAXENEMIES; ++i)
		{
			if (CollisionDetection(m_HeroPtr->GetHitRegion(), m_EnemyPtr[i]->GetHitRegion()) && m_EnemyPtr[i]->GetAlive())
			{
				m_HeroPtr->Hit(12);
			}
		}
	}
}

void HocusPocus::CollisionHeroTrigger()
{
	DOUBLE2 pos;

	
	for (int i = 0; i < MAXTRIGGER; ++i)
	{
		if (CollisionDetection(m_HeroPtr->GetHitRegion(), m_HitTriggerPtr[i]))
		{
			switch (i) 
			{
				case 0: 
					m_EnemyPtr[0]->Spawn(676,494);
					m_EnemyPtr[1]->Spawn(744,496);
					m_EnemyPtr[2]->Spawn(808,496);
					m_EnemyPtr[3]->Spawn(872,496);
					break;

				case 1: 
					m_EnemyPtr[4]->Spawn(680,880);
					m_EnemyPtr[5]->Spawn(744,880);
					m_EnemyPtr[6]->Spawn(808,880);
					break;

				case 2: 
					m_EnemyPtr[7]->Spawn(1824,688);
					m_EnemyPtr[8]->Spawn(1888,688);
					m_EnemyPtr[9]->Spawn(1952,688);
					break;

				case 3: 
					m_EnemyPtr[10]->Spawn(1736,592);
					m_EnemyPtr[11]->Spawn(1800,592);
					m_EnemyPtr[12]->Spawn(1864,592);
					break;

				case 4: 
					m_EnemyPtr[13]->Spawn(1842,394);
					m_EnemyPtr[14]->Spawn(1970,394);
					m_EnemyPtr[15]->Spawn(1888,450);
					break;

				case 5: 
					m_EnemyPtr[16]->Spawn(1736,880);
					m_EnemyPtr[17]->Spawn(1800,880);
					break;

				case 6: 
					m_EnemyPtr[18]->Spawn(2816,784);
					m_EnemyPtr[19]->Spawn(2976,784);
					break;

				case 7: 
					m_EnemyPtr[20]->Spawn(2664,400);
					m_EnemyPtr[21]->Spawn(2792,400);
					m_EnemyPtr[22]->Spawn(2914,398);
					break;

				case 8: 
					m_EnemyPtr[23]->Spawn(1842,138);
					m_EnemyPtr[24]->Spawn(2002,138);
					m_EnemyPtr[25]->Spawn(2162,138);
					break;

				case 9: 
					m_EnemyPtr[26]->Spawn(818,138);
					break;

				case 10: 
					m_EnemyPtr[27]->Spawn(4448,848);
					break;

				//default: 
			}
			m_HitTriggerPtr[i]->CreateFromRect(0,0,0,0);
		}
	}
}

void HocusPocus::CollisionHeroPickups()
{
	for (int i = 0; i < MAXPICKUPS; ++i)
	{
		if (CollisionDetection(m_HeroPtr->GetHitRegion(), m_PickupPtr[i]->GetHitregion()) && m_PickupPtr[i]->GetAlive() == true)
		{
			if (m_PickupPtr[i]->GetType() == 1 && m_HeroPtr->GetHealth() >= 100) //CHECK IF HEALTH IS ABOVE 100
			{

			}
			else if (m_PickupPtr[i]->GetType() == 2) //CRYSTAL
			{
				m_PickupPtr[i]->Destroy(m_HeroPtr->GetPos());
				m_HeroPtr->AddCrystal(1);
				m_FillBackgroundEffectCrystal = 8;
			}
			else if (m_PickupPtr[i]->GetType() == 3 ||	m_PickupPtr[i]->GetType() == 4) //KEYS
			{
				m_PickupPtr[i]->Destroy(m_HeroPtr->GetPos());
				if (m_PickupPtr[i]->GetType() == 3) m_SilverKeyPossession = true;
				if (m_PickupPtr[i]->GetType() == 4) m_GoldKeyPossession =true;
			}
			else if(m_PickupPtr[i]->GetType() == 5) //EXTRASHOT
			{
				m_HeroPtr->AddTimesAllowedToFire(1);
				m_PickupPtr[i]->Destroy(m_HeroPtr->GetPos());
			}
			else //TREASURE
			{
				m_PickupPtr[i]->Destroy(m_HeroPtr->GetPos());
				m_HeroPtr->AddHealth(m_PickupPtr[i]->GetHealth());
				m_HeroPtr->SetScore(m_PickupPtr[i]->GetScore());
				if (m_PickupPtr[i]->GetType() == 0)
				{
					++m_TreasurePickedUp;
				}
			}
		}
	}
}

void HocusPocus::CollisionHeroLocks()
{
	if (m_LockPtr[0]->GetHitregion()->HitTest(m_HeroPtr->GetHitRegion()) && m_LockPtr[0]->GetAlive() == true && m_SilverKeyPossession == true)
	{
		m_LockPtr[0]->Destroy();
		m_SilverKeyPossession = false;

		if (rand()%2 == 0)
		{
			CreateStar(m_LockPtr[0]->GetPos(), false);
		}
		else
		{
			CreateStar(m_LockPtr[0]->GetPos(), true);
		}
	}


	if (m_LockPtr[1]->GetHitregion()->HitTest(m_HeroPtr->GetHitRegion()) && m_LockPtr[1]->GetAlive() == true && m_GoldKeyPossession == true)
	{
		m_LockPtr[1]->Destroy();
		m_GoldKeyPossession = false;

		if (rand()%2 == 0)
		{
			CreateStar(m_LockPtr[1]->GetPos(), false);
		}
		else
		{
			CreateStar(m_LockPtr[1]->GetPos(), true);
		}
	}
}

void HocusPocus::CollisionHeroBlock()
{
	for (int i = 0; i <MAXBLOCKS; ++i)
	{
		if (m_BlockPtr[i]->GetAlive()) m_HeroPtr->BlockCollision(m_BlockPtr[i]->GetHitregion());
	}
}

bool HocusPocus::CollisionBoltBlock()
{
	for (int i = 0; i <MAXBOLT; ++i)
	{	
		for (int j = 0; j <MAXBLOCKS; ++j)
		{
			if (m_BlockPtr[j]->GetAlive() && m_BoltPtr[i]->GetFiring() == true)
			{

				RECT2 tempHit = m_BoltPtr[i]->GetHitRegion()->GetBounds();
				tempHit.bottom = tempHit.bottom + 8;

				HitRegion tempHitRegion;
				tempHitRegion.CreateFromRect(tempHit.left,tempHit.top,tempHit.right-tempHit.left,tempHit.bottom-tempHit.top);

				if (tempHitRegion.HitTest(m_BlockPtr[j]->GetHitregion()) && m_BlockPtr[j]->GetDestructable()== false)
				{
					m_BoltPtr[i]->Destroy();
					DOUBLE2 pos = m_BlockPtr[j]->GetPos();
					pos.x += 16;
					pos.y += 16;
					CreateSmallExplosion(pos);
					return true;
				}

				if (tempHitRegion.HitTest(m_BlockPtr[j]->GetHitregion()) && m_BlockPtr[j]->GetDestructable())
				{
					m_BlockPtr[j]->Destroy(0);
					m_BoltPtr[i]->Destroy();
					return true;
				}
				
			}
		}
	}

	return false;
}

void HocusPocus::CollisionHeroLava()
{
	for (int i = 0; i < MAXLAVA; ++i)
	{
		if (m_LavaPtr[i]->GetHitRegion()->HitTest(m_HeroPtr->GetHitRegion())&& m_HeroPtr->GettingHit() == false)
		{
			m_HeroPtr->Hit(12);
		}
	}
}

void HocusPocus::CollisionHeroEnemyBolt()
{
	for (int i = 0; i < MAXENEMIES; ++i)
	{
		if (m_EnemyPtr[i]->GetType() == 1 || m_EnemyPtr[i]->GetType() == 2)
		{
			if (m_EnemyPtr[i]->GetBoltHitRegion()->HitTest(m_HeroPtr->GetHitRegion()) && m_HeroPtr->GettingHit() == false)
			{
				m_EnemyPtr[i]->DestroyBolt();
				m_HeroPtr->Hit(12);
			}
		}
	}
}

void HocusPocus::CollisionAll()
{
	CollisionHeroTrigger();
	CollisionHeroEnemy();
	CollisionBoltEnemy();
	CollisionBoltWallAndScreen();
	CollisionHeroPickups();
	CollisionHeroLocks();
	CollisionHeroBlock();
	CollisionBoltBlock();
	CollisionHeroLava();
	CollisionHeroEnemyBolt();
}

void HocusPocus::DestroyWalls()
{
	if (m_LockPtr[0]->GetAlive() == false)
	{

		m_BlockPtr[0]->Destroy((rand()%3)*2);
		m_BlockPtr[1]->Destroy((rand()%3)*2);
	}

	if (m_LockPtr[1]->GetAlive() == false)
	{
		for (int i = 2; i < 26; ++i)
		{
			m_BlockPtr[i]->Destroy((rand()%9)*2);
		}
	}

	if (m_SwitchPtr[0]->GetOn())
	{
		for (int i = 32; i < 56; ++i)
		{
			m_BlockPtr[i]->Destroy((rand()%9)*2);
		}
	}

	if (m_SwitchPtr[1]->GetOn())
	{
		for (int i = 56; i < 80; ++i)
		{
			m_BlockPtr[i]->Destroy((rand()%9)*2);
		}
	}
}

void HocusPocus::CheckDeath()
{
	if (m_HeroPtr->GetHealth() <= 0 && m_HeroPtr->GetAlive() == true)
	{
		m_HeroPtr->SetHealth(0);
		m_HeroPtr->SetAlive(false);
		m_DeathSequence = 90;
	}

	if(m_DeathSequence != 0)
	{
		--m_DeathSequence;

		if (m_DeathSequence > 20)
		{
			DOUBLE2 pos = m_HeroPtr->GetPos();

			if (rand()%10)
			{
				pos.x += rand()%30;
				pos.y += rand()%60;
				CreateSmallExplosion(pos);
			}
			else if (rand()%15)
			{
				pos.x += rand()%30;
				pos.y += rand()%30;
				CreateBigExplosion(pos);
			}

			pos = m_HeroPtr->GetPos();

			if (rand()%3 == 0)
			{
				pos.x += rand()%30;
				pos.y += rand()%40;
				if (rand()%2 == 0)
				{
					CreateStar(pos, false);
				}
				else
				{
					CreateStar(pos, true);
				}
			}
		}

		if (m_DeathSequence == 0)
		{
			ResetGame(true);
		}
	}
}

void HocusPocus::CheckWin()
{	
	if (m_HeroPtr->GetCrystal() >= m_CrystalMax)
	{
		GAME_ENGINE->MessageBox(String("Castle complete - congratulations! \n \nResults for Level 1 \n \n \nTreasures found: ") 
										+ m_TreasurePickedUp + "  Treasures available: " + m_TreasureAmount + 
										"\nYou did it in " + m_Time);
		ResetGame(true);
	}
}

void HocusPocus::PaintHudStatistics(MATRIX3X2 matview)
{
	RECT rectGold, rectSilver;

	rectSilver.top = 0;
	rectSilver.bottom = rectSilver.top + 22;
	rectSilver.left = 0;
	rectSilver.right = rectSilver.left +12;

	rectGold.top = 0;
	rectGold.bottom = rectGold.top + 22;
	rectGold.left = 12;
	rectGold.right = rectGold.left +12;

	if (m_SilverKeyPossession == true && m_GoldKeyPossession == true)
	{
		GAME_ENGINE->DrawBitmap(m_BmpKeyPtr,426,360,rectSilver);
		GAME_ENGINE->DrawBitmap(m_BmpKeyPtr,442,360,rectGold);
	}

	if (m_SilverKeyPossession == true && m_GoldKeyPossession == false)
	{
		GAME_ENGINE->DrawBitmap(m_BmpKeyPtr,434,360,rectSilver);
	}

	if (m_SilverKeyPossession == false && m_GoldKeyPossession == true)
	{
		GAME_ENGINE->DrawBitmap(m_BmpKeyPtr,434,360,rectGold);
	}

	m_ScoreTextPtrPtr->Paint(String("")+m_HeroPtr->GetScore(),24,360,matview,112);
	m_ScoreTextPtrPtr->Paint(String("")+m_HeroPtr->GetHealth(),176,360,matview,48);
	m_ScoreTextPtrPtr->Paint(String("")+m_HeroPtr->GetCrystal() + "/" + "5",310,360,matview,52);
	m_ScoreTextPtrPtr->Paint(String("1"),588,360,matview,20);
}

bool HocusPocus::CreateSmallExplosion(DOUBLE2 pos)
{
	for (int i = 0; i < MAXEXPLOSIONS/2; ++i)
	{
		if (m_ExplosionPtr[i]->GetRunning() == false)
		{
			m_ExplosionPtr[i]->Start(pos);
			return true;
		}
	}
	return false;
}

bool HocusPocus::CreateBigExplosion(DOUBLE2 pos)
{
	for (int i = MAXEXPLOSIONS/2; i < MAXEXPLOSIONS; ++i)
	{
		if (m_ExplosionPtr[i]->GetRunning() == false)
		{
			m_ExplosionPtr[i]->Start(pos);
			return true;
		}
	}
	return false;
}

bool HocusPocus::CreateStar(DOUBLE2 pos, bool colour)
{
	for (int i = 0 ; i < MAXSTARS; ++i)
	{
		if (m_StarsPtr[i]->GetShine() == false)
		{
			if (colour == false) //BROWN
			{
				m_StarsPtr[i]->SpawnBrownStar(pos);
			}
			else if (colour == true) //SILVER
			{
				m_StarsPtr[i]->SpawnSilverStar(pos);
			}
			return true;
		}
	}
	return false;
}

void HocusPocus::CreateStarSpawnBox()
{
	DOUBLE2 pos;

	for (int i = 0; i < MAXENEMIES; ++i)
	{
		if(m_EnemyPtr[i]->GetSpawnTime() > 0)
		{
			pos = m_EnemyPtr[i]->GetPos();

			if (rand()%4 == 0)
			{
				pos.x += 20 + rand()%30;
				pos.y += rand()%30;
				if (rand()%2 == 0)
				{
					CreateStar(pos, false);
				}
				else
				{
					CreateStar(pos, true);
				}
			}
		}
	}
}


bool HocusPocus::CheckPauseWizards()
{
	for (int i = 0; i < MAXWIZARDTEXT;++i)
	{
		if (m_WizardTextPtr[i]->GetActive() == true)
		{
			m_Pause = true;
			return true;
		}
	}

	return false;
}


void HocusPocus::DisactivatePause()
{
	bool UpIsPressed = false;
	for (int i = 0; i < MAXWIZARDTEXT;++i)
	{
		if (m_WizardTextPtr[i]->GetActivePressed() == true)
		{
			UpIsPressed = true;	
		}
	}

	if ((GAME_ENGINE->IsKeyDown(VK_LEFT)
		||GAME_ENGINE->IsKeyDown(VK_RIGHT)
		||GAME_ENGINE->IsKeyDown(VK_UP)
		||GAME_ENGINE->IsKeyDown(VK_DOWN)
		||GAME_ENGINE->IsKeyDown(VK_CONTROL)) && UpIsPressed == false)
	{
		for (int i = 0; i < MAXWIZARDTEXT;++i)
		{
			m_WizardTextPtr[i]->SetActive(false);
		}

		m_Pause = false;
	}
}

void HocusPocus::ResetGame(bool resetHeroPos)
{

	if (resetHeroPos)
	{
		DOUBLE2 pos;
		pos.x =95;
		pos.y =858;
		m_HeroPtr->SetPos(pos);
		m_HeroPtr->SetDirection(false);
		m_HeroPtr->SetAlive(true);
		m_HeroPtr->SetGettingHit(false);
	}

	m_HeroPtr->ResetStats();

	int j = 0;

	m_HitTriggerPtr[j++]->CreateFromRect(1066,352,8,192);
	m_HitTriggerPtr[j++]->CreateFromRect(943,846,113,4);
	m_HitTriggerPtr[j++]->CreateFromRect(1472,704,4,96);
	m_HitTriggerPtr[j++]->CreateFromRect(2021,686,3,50);
	m_HitTriggerPtr[j++]->CreateFromRect(1717,580,3,60);
	m_HitTriggerPtr[j++]->CreateFromRect(1922,858,158,3);
	m_HitTriggerPtr[j++]->CreateFromRect(2399,480,3,448);
	m_HitTriggerPtr[j++]->CreateFromRect(3179,96,7,352);
	m_HitTriggerPtr[j++]->CreateFromRect(2240,96,5,224);
	m_HitTriggerPtr[j++]->CreateFromRect(1032,96,7,128);
	m_HitTriggerPtr[j++]->CreateFromRect(4240,800,64,96);


	for (int i = 0; i < MAXBLOCKS;++i)
	{
		m_BlockPtr[i]->SetAlive(true);
	}

	for (int i = 0; i < MAXPICKUPS;++i)
	{
		m_PickupPtr[i]->SetAlive(true);
	}

	for (int i = 0; i < MAXLOCKS;++i)
	{
		m_LockPtr[i]->SetAlive(true);
	}

	for (int i = 0; i < MAXENEMIES;++i)
	{
		m_EnemyPtr[i]->Destroy(false);
		m_EnemyPtr[i]->DestroyBolt();
	}

	for (int i = 0; i < MAXSWITCHES;++i)
	{
		m_SwitchPtr[i]->Reset();
	}

	m_GoldKeyPossession = false;
	m_SilverKeyPossession = false;

	m_TreasurePickedUp = 0;

	m_Time = 0;

}