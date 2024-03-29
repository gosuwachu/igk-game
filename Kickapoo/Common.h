#pragma once

#define WIN32_LEAN_AND_MEAN	
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <d3d9.h>
#include <d3dx9math.h>
#include <dinput.h>

#include <assert.h>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <typeinfo>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <bitset>
#include <fstream>
#include <time.h>
#include <stdarg.h>
#include <locale>
#include <stdlib.h>

#include "../FMOD/inc/fmod.hpp"
#include "../FMOD/inc/fmod_errors.h"
#include "../FastDelegate/FastDelegate.h"
#include "../FastDelegate/FastDelegateBind.h"

using namespace fastdelegate;

#pragma warning(disable: 4996)
using namespace std;

#include "Kickapoo.h"

#include "Singleton.h"
#include "Logger.h"
#include "Resource.h"
#include "Direct3D.h"
#include "Timer.h"
#include "Window.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Renderer.h"
#include "RenderToTexture.h"
#include "Audio.h"
#include "Water.h"
#include "CSprite.h"
#include "../Box2D/Box2D/Box2D.h"
#include "AnimationSequence.h"
//#include "ParticleEmitter.h"
#include "Mouse.h"
#include "Map.h"
#include "Player.h"

class Tower;
class Game;
extern Game* g_Game;

#include "Game.h"
#include "Tower.h"
#include "Missile.h"
#include "Particles.h"

#pragma comment(lib, "../Box2D/Library/box2d.lib")
#pragma comment(lib, "../FMOD/lib/fmodex_vc.lib")
//#include "Physics.h"

extern Game* g_Game;