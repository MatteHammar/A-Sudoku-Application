// Projekt - Sudoku, ProgrammeringsMetodik - DT047G
// Mathias Hammarström
// MainFrame.h, 14-12-2021, 14-01-2022


#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "wx/wx.h"
#include "SudokuPanel.h"
#include "MenuPanel.h"


//! MainFrame is a wxFrame that contains all components used to generate the game.
class MainFrame : public wxFrame {
public:
	//! Constructor
	MainFrame();
	//! Destructor
	~MainFrame();

private:
	//! Panel for handling the actual game
	SudokuPanel* m_sudokuPanel;
	//! Panel for handling the menu
	MenuPanel* m_menuPanel;

	//! Create and bind a SudokuPanel
	void CreateSudokuPanel();
	//! Create and bind a MenuPanel
	void CreateMenuPanel();

	//! Keeps track of which panel is currently showing
	int activePanel;
	//! Hides current panel and shows the other panel
	void SwitchPanels();

	//! Catches resize events and resizes children depending on which panel is active. When switching panels they do not themselves catch the event so we must do it here. Should be changed
	void OnResize(wxSizeEvent &evt);
	//! Handle button clicks depending on which button was clicked
	void OnButtonClicked(wxCommandEvent &evt);
	//! Handle load button clicks by telling SudokuPanel to load the file that was choosen
	void OnLoadButtonClicked(wxCommandEvent &evt);
	//! Exits out of program
	void OnExit(wxCommandEvent &evt);
	//! Shows information about program
	void OnAbout(wxCommandEvent &evt);
};

#endif MAINFRAME_H