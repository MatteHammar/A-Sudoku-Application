#include "SudokuPanel.h"


SudokuPanel::SudokuPanel(wxFrame* parent, int panel_id) :
wxPanel(parent, panel_id), m_selectedButtonIndex(-1)
{
	// create exitbutton 
	m_exitButton = new wxButton(this, EXIT_BUTTON_ID, "Exit");
	m_exitButton->SetBackgroundColour(*wxLIGHT_GREY);
	m_exitButton->SetSize(200, 50);
	m_exitButton->SetFont(wxFont(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	m_exitButton->SetPosition(wxPoint(300, 450));

	// create undobutton 
	m_undoButton = new wxButton(this, wxID_ANY, "Undo");
	m_undoButton->SetBackgroundColour(*wxYELLOW);
	m_undoButton->SetSize(200, 50);
	m_undoButton->SetFont(wxFont(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	m_undoButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &SudokuPanel::OnUndoButtonClicked, this);
	m_undoButton->SetPosition(wxPoint(100, 450));

	// create solvebutton 
	m_stepSolveButton = new wxButton(this, wxID_ANY, "Next Step");
	m_stepSolveButton->SetBackgroundColour(*wxYELLOW);
	m_stepSolveButton->SetSize(200, 50);
	m_stepSolveButton->SetFont(wxFont(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	m_stepSolveButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &SudokuPanel::OnStepSolveButtonClicked, this);
	m_stepSolveButton->SetPosition(wxPoint(400, 450));

	// create sudokubox panel
	m_sudokuBox = new wxPanel(parent, wxID_ANY);
	m_sudokuBox->SetSize(parent->GetSize() - wxSize(100, 100));
	m_sudokuBox->Hide();

	// Create an empty sudoku state
	m_sudokuData = Sudoku(Sudoku::NORMAL_9x9_SIZE);
	m_solvedSudoku = m_sudokuData;
	m_solvedSudoku.solve();

	// Creates the array of sudokuButtons
	// and put them into grids
	CreateSudokuGrid();

	// Catch char keyboard clicks
	Bind(wxEVT_CHAR_HOOK, &SudokuPanel::OnKeyboardClicked, this);

	Resize();
	Layout();
}


SudokuPanel::~SudokuPanel()
{
	delete[] m_sudokuButtons;
}



void SudokuPanel::OnSudokuButtonClicked(wxCommandEvent & evt)
{
	if(m_selectedButtonIndex != -1)
		m_sudokuButtons[m_selectedButtonIndex]->SetBackgroundColour(*wxWHITE);

	size_t index = evt.GetId() - SUDOKU_BUTTON_START_ID;
	m_selectedButtonIndex = index;
	m_sudokuButtons[index]->SetBackgroundColour(*wxLIGHT_GREY);
	
	evt.Skip();
}

void SudokuPanel::OnUndoButtonClicked(wxCommandEvent & evt)
{
	if (m_actionStack.empty()) {
		evt.Skip();
		return;
	}

	// Get the most recent action
	auto lastAction = m_actionStack.back();
	int found = 0;

	// Find what the cell number was before that action
	// and set the cell to that number, if no number was found it becomes empty
	// because there was no prior action in that cell
	for (int i = m_actionStack.size() - 2; i >= 0; --i) {
		if (lastAction.first == m_actionStack[i].first) {
			found = m_actionStack[i].second;
			break;
		}
	}
	if (found) 
		m_sudokuButtons[lastAction.first]->SetLabel(std::to_string(found));
	else 
		m_sudokuButtons[lastAction.first]->SetLabel("");

	m_sudokuData[lastAction.first] = found;
	if (m_solvedSudoku[m_selectedButtonIndex] != found)
		m_sudokuButtons[lastAction.first]->SetForegroundColour(*wxRED);
	else
		m_sudokuButtons[lastAction.first]->SetForegroundColour(*wxBLUE);

	// Remove action from stack
	m_actionStack.pop_back();
	evt.Skip();
}

void SudokuPanel::OnStepSolveButtonClicked(wxCommandEvent & evt)
{
	StepSolveSudoku();
	evt.Skip();
}

void SudokuPanel::OnKeyboardClicked(wxKeyEvent & evt)
{
	// Ignore keyboardevents if no sudokubutton is selected
	if (m_selectedButtonIndex == -1) {
		evt.Skip();
		return;
	}

	wxChar c = evt.GetUnicodeKey();
	// If KeyEvent was not a char, ignore
	if (c == WXK_NONE) {
		evt.Skip();
		return;
	}

	wxButton* button = m_sudokuButtons[m_selectedButtonIndex];
	SudokuCell& sudokuCell = m_sudokuData[m_selectedButtonIndex];

	// If trying to change a cell which is "original" also ignore
	if (!sudokuCell.changeable) {
		evt.Skip();
		return;
	}
	// Empty cell
	if (c == WXK_BACK) {
		button->SetLabel("");
		sudokuCell = 0;
	}

	// Checks char for an integer
	else if (c <= '9' && c >= '0') {
		wxString str = "";
		size_t sudokuSize = m_sudokuData.length();

		// Get current number in cell and combine with number clicked
		// Only needed in sudoku grids with more than 9 possible numbers
		str = button->GetLabel();
		str += c;

		// To avoid multiple 0's in a cell
		if (str == "0")
			str = std::to_string(sudokuSize + 1);

		// Check if the combined number is within range
		if (std::stoi(std::string(str.mb_str())) > sudokuSize) {
			if (c == '0') {
				button->SetLabel("");
				sudokuCell = 0;
			}
			else {
				button->SetLabel(c);
				sudokuCell = (c - '0');
			}
		}
		else {
			button->SetLabel(str);
			sudokuCell = std::stoi(std::string(str.mb_str()));
		}

		if (m_solvedSudoku[m_selectedButtonIndex] != sudokuCell && m_solvedSudoku[m_selectedButtonIndex].number != 0)
			button->SetForegroundColour(*wxRED);
		else
			button->SetForegroundColour(*wxBLUE);
				
		if(m_sudokuData.isSolved())
			wxMessageBox("Congratulations! You have solved the sudoku.", "Game is finished", wxOK | wxICON_INFORMATION);
	}

	m_actionStack.push_back(std::make_pair(m_selectedButtonIndex, sudokuCell.number));
	
	evt.Skip();
}

void SudokuPanel::CreateSudokuGrid()
{
	size_t length = m_sudokuData.length();
	size_t boxLength = m_sudokuData.boxLength();

	wxGridSizer* grid = new wxGridSizer(boxLength, boxLength, 0, 0);
	m_sudokuButtons = new wxButton*[length * length];

	for (size_t i = 0; i < length; ++i) {
		wxGridSizer* g = new wxGridSizer(boxLength, boxLength, 0, 0);

		auto box = m_sudokuData.getBox(i);
		for (auto it = box.begin(); it != box.end(); ++it) {
			size_t index = (i / boxLength) * boxLength * length + (i % boxLength) * boxLength + (it - box.begin());
			int id = SUDOKU_BUTTON_START_ID + index;
			m_sudokuButtons[index] = new wxButton(this, id);

			if (*it != 0)
				m_sudokuButtons[index]->SetLabel(std::to_string((*it).number));
			else
				m_sudokuButtons[index]->SetForegroundColour(*wxBLUE);

			m_sudokuButtons[index]->SetBackgroundColour(*wxWHITE);
			m_sudokuButtons[index]->SetFont(wxFont(24, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
			m_sudokuButtons[index]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &SudokuPanel::OnSudokuButtonClicked, this);

			g->Add(m_sudokuButtons[index], 1, wxEXPAND | wxALL, -1);
		}
		grid->Add(g, 1, wxEXPAND | wxALL, 3);
	}
	m_actionStack.clear();

	m_sudokuBox->SetSizer(grid);
	grid->Layout();
	m_sudokuBox->Layout();
	Layout();
}

void SudokuPanel::ReloadSudokuGrid()
{
	for (size_t i = 0; i < m_sudokuData.size(); ++i) {
		auto cell = m_sudokuData[i];

		m_sudokuButtons[i]->SetLabel("");
		
		if (cell != 0) 
			m_sudokuButtons[i]->SetLabel(std::to_string(cell.number));
		
		if(!cell.changeable)
			m_sudokuButtons[i]->SetForegroundColour(*wxBLACK);
		else {
			if(m_sudokuData[i] == m_solvedSudoku[i])
				m_sudokuButtons[i]->SetForegroundColour(*wxBLUE);
			else
				m_sudokuButtons[i]->SetForegroundColour(*wxRED);
		}
	}
}

void SudokuPanel::SolveSudoku()
{
	m_sudokuData.solve();
	ReloadSudokuGrid();
}

void SudokuPanel::StepSolveSudoku()
{
	m_sudokuData.stepSolve();
	ReloadSudokuGrid();
}

void SudokuPanel::Resize()
{
	wxSize frameSize = GetParent()->GetSize();
	int x, y;

	int newSize = std::min(frameSize.GetHeight() - 60, frameSize.GetWidth()) - 10;

	x = (frameSize.GetWidth() - newSize + 100) / 2;
	y = (frameSize.GetHeight() - newSize - 60) / 2;

	SetSize(x, y, newSize, newSize);
	m_sudokuBox->SetSize(x, y, newSize - 100, newSize - 100);

	m_exitButton->SetPosition(wxPoint(newSize / 2 - 150, newSize - 75));
	m_undoButton->SetPosition(wxPoint(newSize / 2 - 375, newSize - 75));
	m_stepSolveButton->SetPosition(wxPoint(newSize / 2 + 75, newSize - 75));

	m_sudokuBox->Layout();
	Layout();
}

void SudokuPanel::OnResize(wxSizeEvent & evt)
{
	Resize();
	
	evt.Skip();
}

void SudokuPanel::LoadSudoku(std::string filename)
{
	m_sudokuData = Sudoku(filename);

	m_sudokuBox->GetSizer()->Clear(true);
	delete m_sudokuButtons;


	m_solvedSudoku = m_sudokuData;
	m_solvedSudoku.solve();
	CreateSudokuGrid();
}
