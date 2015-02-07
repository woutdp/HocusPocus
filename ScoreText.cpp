//---------------------------
// Includes
//---------------------------
#include "ScoreText.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * ScoreText::m_BmpScoreTextPtr = 0;
ScoreText::ScoreText():m_Pos(0,0)
{
	if (m_BmpScoreTextPtr == 0)
	{
		m_BmpScoreTextPtr = new Bitmap("./Resources/ScoreText.png");
		m_BmpScoreTextPtr->SetTransparencyColor(255,0,255);
	}
}

ScoreText::~ScoreText()
{
	delete m_BmpScoreTextPtr;
	m_BmpScoreTextPtr = 0;
}

void ScoreText::Tick(double deltaTime)
{

}

void ScoreText::Paint(String input, int posX , int posY,MATRIX3X2 matView, int widthBox)
{
		MATRIX3X2 matTranslate;
		RECT2 r;
		int lengthInput = input.GetLength();

		DOUBLE2 pos(posX,posY);
		pos.x += widthBox/2;
		pos.x -= (lengthInput*16)/2;
		pos.y += 2;

		if (input.CharAt(0) == '1')
		{
			pos.x += 2;
		}

		r.top = 0;
		r.bottom = r.top + HEIGHT;

		for (int i = 0; i < lengthInput; ++i)
		{
			int nextNumber = 16;

			switch (input.CharAt(i))
			{
				case '0':
					r.left = WIDTH*0;
					r.right = r.left + WIDTH;
					break;

				case '1':
					r.left = WIDTH*1;
					r.right = r.left + WIDTH;
					nextNumber = 14;
					break;

				case '2':
					r.left = WIDTH*2;
					r.right = r.left + WIDTH;

					break;

				case '3':
					r.left = WIDTH*3;
					r.right = r.left + WIDTH;

					break;

				case '4':
					r.left = WIDTH*4;
					r.right = r.left + WIDTH;

					break;

				case '5':
					r.left = WIDTH*5;
					r.right = r.left + WIDTH;

					break;

				case '6':
					r.left = WIDTH*6;
					r.right = r.left + WIDTH;

					break;

				case '7':
					r.left = WIDTH*7;
					r.right = r.left + WIDTH;

					break;

				case '8':
					r.left = WIDTH*8;
					r.right = r.left + WIDTH;

					break;

				case '9':
					r.left = WIDTH*9;
					r.right = r.left + WIDTH;

					break;

				case '/':
					r.left = WIDTH*10;
					r.right = r.left + WIDTH;

					break;
			}

			matTranslate.SetAsTranslate(pos);
			GAME_ENGINE->SetTransformMatrix(matTranslate*matView);
			GAME_ENGINE->DrawBitmap(m_BmpScoreTextPtr,0,0,r);

			pos.x+= nextNumber;
		}
	


}