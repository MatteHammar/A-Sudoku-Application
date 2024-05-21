#include "MenuPanel.h"
#include <wx/wfstream.h>


MenuPanel::MenuPanel(wxFrame* parent, int panel_id):
wxPanel(parent, panel_id)
{
	//SetSize(parent->GetSize().GetWidth(), parent->GetSize().GetHeight() - 60);
	m_newgameButton = new wxButton(this, NEWGAME_BUTTON_ID, "New Game");
	m_continueButton = new wxButton(this, CONTINUE_BUTTON_ID, "Continue");
	m_loadButton = new wxButton(this, LOAD_BUTTON_ID, "Load");
	m_optionButton = new wxButton(this, wxID_ANY, "Options");
	m_quitButton = new wxButton(this, QUIT_BUTTON_ID, "Quit");

	wxFont buttonFont(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	m_newgameButton->SetBackgroundColour(*wxLIGHT_GREY);
	m_newgameButton->SetSize(300, 80);
	m_newgameButton->SetFont(buttonFont);

	m_continueButton->SetBackgroundColour(*wxLIGHT_GREY);
	m_continueButton->SetSize(300, 80);
	m_continueButton->SetFont(buttonFont);
	m_continueButton->Disable();

	m_loadButton->SetBackgroundColour(*wxLIGHT_GREY);
	m_loadButton->SetSize(300, 80);
	m_loadButton->SetFont(buttonFont);

	m_optionButton->SetBackgroundColour(*wxLIGHT_GREY);
	m_optionButton->SetSize(300, 80);
	m_optionButton->SetFont(buttonFont);

	m_quitButton->SetBackgroundColour(*wxLIGHT_GREY);
	m_quitButton->SetSize(300, 80);
	m_quitButton->SetFont(buttonFont);

	int x = (parent->GetSize().GetWidth() - 300) / 2;
	int y = (parent->GetSize().GetHeight() - 60 - 80 - 50);

	int padding = 130;

	m_newgameButton->SetPosition(wxPoint(x, y - 4 * padding));
	m_continueButton->SetPosition(wxPoint(x, y - 3 * padding));
	m_loadButton->SetPosition(wxPoint(x, y - 2 * padding));
	m_optionButton->SetPosition(wxPoint(x, y - padding));
	m_quitButton->SetPosition(wxPoint(x, y));

}

MenuPanel::~MenuPanel()
{
}

void MenuPanel::enableContinueButton()
{
	m_continueButton->Enable();
}


void MenuPanel::Resize()
{
	SetSize(GetParent()->GetSize());


	int x = (GetParent()->GetSize().GetWidth() - 300) / 2;
	int y = (GetParent()->GetSize().GetHeight() - 60 - 80 - 50);
	if (y > 1000)
		y = 1000;

	int padding = 130;

	m_newgameButton->SetPosition(wxPoint(x, y - 4 * padding));
	m_continueButton->SetPosition(wxPoint(x, y - 3 * padding));
	m_loadButton->SetPosition(wxPoint(x, y - 2 * padding));
	m_optionButton->SetPosition(wxPoint(x, y - padding));
	m_quitButton->SetPosition(wxPoint(x, y));
	/*
	m_newgameButton->SetPosition(wxPoint(x, m_newgameButton->GetPosition().y));
	m_continueButton->SetPosition(wxPoint(x, m_continueButton->GetPosition().y));
	m_loadButton->SetPosition(wxPoint(x, m_loadButton->GetPosition().y));
	m_optionButton->SetPosition(wxPoint(x, m_optionButton->GetPosition().y));
	m_quitButton->SetPosition(wxPoint(x, m_quitButton->GetPosition().y));*/
	Layout();
}

void MenuPanel::OnResize(wxSizeEvent & evt)
{
	Resize();
	
	evt.Skip();
}
