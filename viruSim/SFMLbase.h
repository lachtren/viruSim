#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "opengl32.lib")
#ifdef _DEBUG
#pragma comment(lib, "sfml-system-s-d.lib")
#pragma comment(lib, "sfml-window-s-d.lib")
#pragma comment(lib, "sfml-graphics-s-d.lib")
#else
#pragma comment(lib, "sfml-system-s.lib")
#pragma comment(lib, "sfml-window-s.lib")
#pragma comment(lib, "sfml-graphics-s.lib")
#endif
