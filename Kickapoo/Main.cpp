
#include "Common.h"
#include "Kickapoo.h"

void onLostDevice();

Font* mousePosition;
Game* g_Game;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	g_Window()->initApplication( "Anty Defense", 50*BLOCK_SIZE, 35*BLOCK_SIZE, hInstance, false );
	g_Direct3D()->initDirect3D(32, false);
	g_Renderer()->create();
	g_Input()->init(hInstance, false);
	g_Audio()->create();
	g_Mouse()->create();

	int width = g_Window()->getWidth();
	int height = g_Window()->getHeight();



	RECT rect = {0, 0, width, 100};

	mousePosition = new Font();
	mousePosition->create("Verdana", 20, 0, false, &rect);
	mousePosition->setTextColor(D3DCOLOR_RGBA(255, 0, 0, 255));

	

	HRESULT hr;
	g_Direct3D()->enableAlphaBlending(true);

	RenderToTexture texture;
	texture.init(width, height);

	//Water water;
	//water.create(0, 0, width, height, 20);

	g_Game = new Game();
	g_Game->create();

	while( !g_Window()->isDone() ) 
	{			
		g_Window()->updateApplication();

		if(g_Window()->keyDown(VK_ESCAPE))
			g_Window()->exitApplication();

		g_Timer()->update();
		g_Audio()->update();
		g_Mouse()->update();
		g_Input()->update();
		//g_World()->update(g_Timer()->getFrameTime());
		AnimationSequence::updateAll(g_Timer()->getFrameTime());
		g_Game->update();
		//water.update();

		getDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);			
		getDevice()->BeginScene();		

		texture.beginRenderToTexture();

		g_Renderer()->setIdentity();
		g_Game->draw();
		g_Mouse()->drawCursor();

		mousePosition->write("fps: %0.1f\nmouse position: (%0.1f, %0.1f)", 
			g_Timer()->getFPS(), g_Mouse()->getX(), g_Mouse()->getY());
	
		texture.endRenderToTexture();
		getDevice()->SetTexture(0, *texture.getTexture());
		g_Renderer()->drawRect(0, 0, width, height);
	//	water.setTexture(texture.getTexture());
	//	water.render();

		//int width = width / 2;
		//int height = height / 2;
		//texture.draw(0, 0, width, height);
		//texture.draw(width, 0, width, height);
		//texture.draw(0, height, width, height);
		//texture.draw(width, height, width, height);

		getDevice()->EndScene();
		hr = getDevice()->Present(NULL, NULL, NULL, NULL);

		// obsluga utraty urzadzenia
		if(hr == D3DERR_DEVICELOST) {
			onLostDevice();
		}
	}

	// zwolnienie nie zwolnionych zasobow
	Texture::releaseResources();
	Font::releaseResources();
	AnimationSequence::releaseAll();

	g_Renderer()->release();
	g_Audio()->release();
	g_Direct3D()->releaseDirect3D();
	g_Window()->shutdownApplication();
	return 0;
}

void onLostDevice()
{
	Font::onLostDevice();
	//g_Renderer()->onLostDevice();
	g_Direct3D()->onLostDevice();

	g_Direct3D()->restoreDevice();

	g_Direct3D()->onResetDevice();
	//g_Renderer()->onResetDevice();
	Font::onResetDevice();

	g_Direct3D()->setDefaultSettings();
}