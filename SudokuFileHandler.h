// Projekt - Sudoku, ProgrammeringsMetodik - DT047G
// Mathias Hammarström
// SudokuFileHandler.h, 14-12-2021, 14-01-2022

#ifndef SUDOKU_FILE_HANDLER_H
#define SUDOKU_FILE_HANDLER_H

#include <string>

//! Class for handling files containing sudokus, and checking / translating them if possible
class SudokuFileHandler
{
public:
	//! Constructor
	SudokuFileHandler();
	//! Destructor
	~SudokuFileHandler();

	//! Reads sudoku from a file

	//! Checks for correct format
	//! Returns a string container each cell integer seperated by a comma
	std::string LoadSudoku(std::string filename);
};

#endif SUDOKU_FILE_HANDLER_H