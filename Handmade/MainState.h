#ifndef MAIN_STATE_H
#define MAIN_STATE_H

/*==============================================================================================#
|                                                                                               |
| All code has been written by Karsten Vermeulen as part of the 'Handmade' game engine, for the |
| purposes of educating other fellow programmers, programming students and anyone else wishing  |
| to learn about game development, C++ and OOP. The engine, class design and overall structure  |
| is by no means perfect and there is certainly room for improvement. Feel free to use, copy,   |
| break, update and do as you wish with this code - it is there, free, for all!                 |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|																								|
| If you like 'Handmade', and wish to show your support, if you have any questions about the    |
| project, or if you just want to reach out, please find me on the following channels:          |
|																						        |
| Web: http://www.karstenvermeulen.com														    |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'MainState' source files last updated in April 2020   							            |
#==============================================================================================*/

#include <vector>
#include "Axes2D.h"
#include "Axes3D.h"
#include "Circle.h"
#include "Cuboid.h"
#include "Element.h"
#include "FPSCamera.h"
#include "GameObject.h"
#include "GameState.h"
#include "Grid2D.h"
#include "Grid3D.h"
#include "HUD.h"
#include "Quad.h"
#include "Sphere.h"
#include "UICamera.h"

class MainState : public GameState
{

public:

	MainState(Game* game, GameState* state);
	virtual ~MainState() {}

public:

	virtual bool OnEnter();
	virtual bool Update(int deltaTime);
	virtual bool Draw();
	virtual void OnExit();

private:

	bool m_isTabPressed;
	bool m_isMouseVisible;

	HUD* m_HUD;
	Axes2D* m_axes2D;
	Axes3D* m_axes3D;
	Grid2D* m_grid2D;
	Grid3D* m_grid3D;

	UICamera* m_UICam;
	FPSCamera* m_mainCam;

	std::vector<GameObject*> m_gameObjects;

};

#endif