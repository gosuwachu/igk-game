
#include "Common.h"
#include "Kickapoo.h"

void onLostDevice();

Font mousePosition;
Game* g_Game;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	g_Window()->initApplication( "IGK Framework", 1024, 768, hInstance, false );
	g_Direct3D()->initDirect3D(32, false);
	g_Renderer()->create();
	g_Input()->init(hInstance, false);
	g_Audio()->create();
	g_Mouse()->create();

	g_Game = new Game();
	g_Game->create();

	HRESULT hr;
	g_Direct3D()->enableAlphaBlending(true);

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
		g_Game->update();

		getDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);			
		getDevice()->BeginScene();		

		g_Renderer()->setIdentity();
		g_Game->draw();
		g_Mouse()->drawCursor();

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