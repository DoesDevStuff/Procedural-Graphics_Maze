#include "pch.h"
#include "Input.h"


Input::Input()
{
}

Input::~Input()
{
}

void Input::Initialise(HWND window)
{
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouse->SetWindow(window);
	m_quitApp = false;

	m_GameInput.forward					= false;
	m_GameInput.back					= false;
	m_GameInput.right					= false;
	m_GameInput.left					= false;
	m_GameInput.rotRight				= false;
	m_GameInput.rotLeft					= false;

	m_GameInput.isMiniMapEnabled		= false;
	m_GameInput.bloom					= false;
}

void Input::Update()
{
	auto kb = m_keyboard->GetState();	//updates the basic keyboard state
	m_KeyboardTracker.Update(kb);		//updates the more feature filled state. Press / release etc. 
	auto mouse = m_mouse->GetState();   //updates the basic mouse state
	m_MouseTracker.Update(mouse);		//updates the more advanced mouse state. 

	if (kb.Escape)// check has escape been pressed.  if so, quit out. 
	{
		m_quitApp = true;
	}

	//A key
	if (kb.A)	m_GameInput.left = true;
	else		m_GameInput.left = false;
	
	//D key
	if (kb.D)	m_GameInput.right = true;
	else		m_GameInput.right = false;

	//W key
	if (kb.W)	m_GameInput.forward	 = true;
	else		m_GameInput.forward = false;

	//S key
	if (kb.S)	m_GameInput.back = true;
	else		m_GameInput.back = false;

	/*
	*UP AND DOWN     // not sure I want it
	* 
	* hooks needed for it.. do logic same as last sem project ?
	* will need to maybe limit up motion
	* down need to go till floor, collison again TvT
	* 
	* Mouse rotate ?? IDK (not today me's problem)
	* 
	if (kb.LeftShift) m_GameInput.up = true;
	else m_GameInput.up = false;

	if (kb.LeftControl) m_GameInput.down = true;
	else m_GameInput.down = false;

	*/



	//space
	if (kb.Space) m_GameInput.generate = true;
	else		m_GameInput.generate = false;

	//X  bug, it works but terrain is freezing on build need to check why later
	if (kb.X) m_GameInput.midpoint = true;
	else	  m_GameInput.midpoint = false;

	// Z	Smoothens // this works fine so I do not know why midpoint is freesing things yet. It worked fine before
	if (m_KeyboardTracker.IsKeyPressed(DirectX::Keyboard::Z)) m_GameInput.smoothen = true;
	else      m_GameInput.smoothen = false;

	//N		 New cellular automata
	if (m_KeyboardTracker.IsKeyPressed(DirectX::Keyboard::N)) m_GameInput.cellularAutomata = true;
	else      m_GameInput.cellularAutomata = false;

	//B		Blurs (similar to bloom)
	if (m_KeyboardTracker.IsKeyPressed(DirectX::Keyboard::B)) m_GameInput.bloom = true;
	else      m_GameInput.bloom = false;

	//M		Minimap
	if (m_KeyboardTracker.IsKeyPressed(DirectX::Keyboard::V)) m_GameInput.isMiniMapEnabled = true;
	else      m_GameInput.isMiniMapEnabled = false;
}

bool Input::Quit()
{
	return m_quitApp;
}

InputCommands Input::getGameInput()
{
	return m_GameInput;
}
