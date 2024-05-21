#include "MainFrame.h"
#include <wx/wfstream.h>



MainFrame::MainFrame() :
wxFrame(nullptr, wxID_ANY, "My Title", wxPoint(30, 30), wxSize(800, 800))
{
	wxMenu* menuFile = new wxMenu();
	menuFile->Append(wxID_EXIT);

	wxMenu* menuHelp = new wxMenu();
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_SIZE, &MainFrame::OnResize, this);
	
	CreateMenuPanel();

	SetBackgroundColour(*wxWHITE);
	SetMinClientSize(wxSize(800, 800));
	Center();
}


MainFrame::~MainFrame()
{
}


void MainFrame::CreateSudokuPanel()
{
	m_sudokuPanel = new SudokuPanel(this, SudokuPanel::PANEL_ID);
	m_sudokuPanel->SetBackgroundColour(*wxWHITE);
	m_sudokuPanel->m_exitButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnButtonClicked, this);
	m_menuPanel->enableContinueButton();
	Layout();
}

void MainFrame::CreateMenuPanel()
{
	m_menuPanel = new MenuPanel(this);
	m_menuPanel->SetBackgroundColour(*wxWHITE);

	m_menuPanel->m_newgameButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnButtonClicked, this);
	m_menuPanel->m_continueButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnButtonClicked, this);
	m_menuPanel->m_loadButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnLoadButtonClicked, this);
	m_menuPanel->m_quitButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnButtonClicked, this);
	activePanel = MenuPanel::PANEL_ID;
	Layout();
}

void MainFrame::SwitchPanels()
{
	switch (activePanel) {
	case MenuPanel::PANEL_ID:
		if (m_sudokuPanel) {
			m_menuPanel->Hide();
			m_sudokuPanel->Show();
			m_sudokuPanel->Resize();
		}
		Layout();
		break;

	case SudokuPanel::PANEL_ID:
		if (m_sudokuPanel)
			m_sudokuPanel->Hide();
		m_menuPanel->Show();
		m_menuPanel->Resize();
		Layout();
		break;

	default:
		m_menuPanel->Show();
		m_menuPanel->Resize();
		Layout();
	}
}


void MainFrame::OnResize(wxSizeEvent & evt)
{
	switch (activePanel) {
	case MenuPanel::PANEL_ID:
		m_menuPanel->OnResize(evt);
		break;

	case SudokuPanel::PANEL_ID:
		m_sudokuPanel->OnResize(evt);
		break;
	}
	evt.Skip();
}

void MainFrame::OnButtonClicked(wxCommandEvent & evt)
{
	switch (evt.GetId()) {
	case MenuPanel::NEWGAME_BUTTON_ID:
		m_menuPanel->Hide();
		CreateSudokuPanel();
		activePanel = SudokuPanel::PANEL_ID;
		break;

	case MenuPanel::CONTINUE_BUTTON_ID:
		SwitchPanels();
		activePanel = SudokuPanel::PANEL_ID;
		break;

	case MenuPanel::QUIT_BUTTON_ID:
		Close(true);
		break;

	case SudokuPanel::EXIT_BUTTON_ID:
		SwitchPanels();
		activePanel = MenuPanel::PANEL_ID;
		break;
	}
	
	evt.Skip();
}

void MainFrame::OnLoadButtonClicked(wxCommandEvent & evt)
{
	wxFileDialog openFileDialog(this, _("Open txt file"), "", "",
		"txt files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	// proceed loading the file chosen by the user;
	// this can be done with e.g. wxWidgets input streams:
	wxFileInputStream input_stream(openFileDialog.GetPath());
	if (!input_stream.IsOk())
	{
		wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
		return;
	}
	if (!m_sudokuPanel) {
		CreateSudokuPanel();
	}
	m_sudokuPanel->LoadSudoku(std::string(openFileDialog.GetPath().mb_str()));
	SwitchPanels();
	activePanel = SudokuPanel::PANEL_ID;
}

void MainFrame::OnExit(wxCommandEvent & evt)
{
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent & evt)
{
	wxMessageBox("This is about", "About hello", wxOK | wxICON_INFORMATION);
	evt.Skip();
}