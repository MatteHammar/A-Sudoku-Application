// Projekt - Sudoku, ProgrammeringsMetodik - DT047G
// Mathias Hammarström
// Application.h, 14-12-2021, 14-01-2022

#ifndef APPLICATION_H
#define APPLICATION_H

#include "wx/wx.h"
#include "MainFrame.h"


//! Application is a wxApp that starts the program and loads MainFrame
class Application : public wxApp {
public:
	//! Constructor
	Application();
	//! Destructor
	~Application();

	//! Function that starts the program
	virtual bool OnInit();

private:
	//! Our MainFrame object which we create and load
	MainFrame* m_frame = nullptr;
};

#endif APPLICATION_H