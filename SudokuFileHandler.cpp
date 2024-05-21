#include "SudokuFileHandler.h"
#include <fstream>
#include <algorithm>



SudokuFileHandler::SudokuFileHandler()
{
}


SudokuFileHandler::~SudokuFileHandler()
{
}

std::string SudokuFileHandler::LoadSudoku(std::string filename)
{
	std::ifstream reader(filename);
	std::string line;
	std::string s = "";
	char delimiter;



	int rowCounter = 0;
	int cellCounter = 0;
	if (reader.is_open()) {
		while (getline(reader, line)) {
			// Find and set delimiter
			for (auto it = line.begin(); it != line.end(); ++it) {
				if ((*it) > '9' || (*it) < '0') {
					delimiter = *it;
					break;
				}
			}
			auto isCharAllowed = [delimiter](const char& c) {

				if ((c > '9' || c < '0') && c != delimiter)
					return false;

				return true;
			};
			// Look for unallowed characters
			if (line.end() != std::find_if_not(line.begin(), line.end(), isCharAllowed))
				return "";

			for (auto it = line.begin(); it != line.end(); ++it) {
				if (*it == delimiter) {
					s += ',';
					++cellCounter;
				}
				else 
					s += *it;
				
			}
			++rowCounter;
		}
		reader.close();
	}

	if ((rowCounter * rowCounter) != cellCounter)
		return "";

	return s;
}
