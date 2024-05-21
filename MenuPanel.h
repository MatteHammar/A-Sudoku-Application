// Projekt - Sudoku, ProgrammeringsMetodik - DT047G
// Mathias Hammarström
// MenuPanel.h, 14-12-2021, 14-01-2022

#ifndef MENUPANEL_H
#define MENUPANEL_H

#include "wx/wx.h"

//! MenuPanel class is a wxPanel which contains the menu of our application.
class MenuPanel: public wxPanel {
public:
	//! Constructor
	explicit MenuPanel(wxFrame* parent, int panel_id = PANEL_ID);
	//! Destructor
	~MenuPanel();

	//! Enables the continue button, should only be enabled if there exists a valid SudokuPanel to switch to
	void enableContinueButton();

	//! New game button creates an empty Sudoku and switches to it
	wxButton* m_newgameButton;
	//! Switches to current Sudoku game
	wxButton* m_continueButton;
	//! Opens up a file explorer to select a sudoku file
	wxButton* m_loadButton;
	//! Exits program
	wxButton* m_quitButton;

	//! Resizes panel based on parents size
	void Resize();
	//! Resize event catcher, calls resize function to resize
	void OnResize(wxSizeEvent &evt);
private:
	//! Open option, not implemented yet
	wxButton* m_optionButton;

public:
	//! Constant, panel id
	static constexpr int PANEL_ID = 501;
	//! Constant, NewGame button id
	static constexpr int NEWGAME_BUTTON_ID = 600;
	//! Constant, Continue button id
	static constexpr int CONTINUE_BUTTON_ID = 601;
	//! Constant, Load button id
	static constexpr int LOAD_BUTTON_ID = 602;
	//! Constant, Quit button id
	static constexpr int QUIT_BUTTON_ID = 603;
};

#endif MENUPANEL_H