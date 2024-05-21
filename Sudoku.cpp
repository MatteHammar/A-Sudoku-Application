// Projekt - Sudoku, ProgrammeringsMetodik - DT047G
// Mathias Hammarström
// Sudoku.cpp, 14-12-2021, 13-01-2022
// Sudoku class, 

#include "Sudoku.h"

#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

Sudoku::Sudoku() : m_board(nullptr), m_length(0), m_boardSize(0), m_boxLength(0)
{
}

Sudoku::Sudoku(size_t size) : m_board(new SudokuCell[size*size*size*size]), m_length(size*size), m_boardSize(size*size*size*size), m_boxLength(size)
{
}

Sudoku::Sudoku(std::string filename) : Sudoku()
{
	SudokuFileHandler reader;
	std::string sudokuString = reader.LoadSudoku(filename);
	if (sudokuString.empty()) {
		std::cout << "File format not recognize\n";
		return;
	}

	// Converts list of strings to vector of integers
	std::string stringNumber = "";
	std::vector<int> vec;
	for (auto it = sudokuString.begin(); it != sudokuString.end(); ++it) {
		if (*it == ',') {
			vec.push_back(std::stoi(stringNumber));
			stringNumber = "";
		}
		else {
			stringNumber += *it;
		}
	}

	// Set member variables
	m_length = sqrt(vec.size());
	m_boxLength = sqrt(m_length);
	m_boardSize = vec.size();
	m_board = new SudokuCell[m_boardSize];

	// Copy vector of integers to member array
	std::transform(vec.begin(), vec.end(), m_board, [](const int& n) { return n; });

	// Initilize cells
	initializeCells();
}

Sudoku::Sudoku(const SudokuCell * begin, size_t size) : Sudoku(sqrt(size))
{
	std::copy(begin, begin + size * size, m_board);
	initializeCells();
}

Sudoku::Sudoku(const Sudoku & rhs) : Sudoku(rhs.m_board, rhs.m_length)
{
}

Sudoku::Sudoku(Sudoku && rhs) : Sudoku()
{
	swap(rhs);
}

Sudoku & Sudoku::operator=(const Sudoku & rhs)
{
	Sudoku copy = rhs;

	swap(copy);
	return *this;
}

Sudoku & Sudoku::operator=(Sudoku && rhs)
{
	swap(rhs);
	return *this;
}

SudokuCell & Sudoku::operator[](size_t index)
{
	return m_board[index];
}

const SudokuCell & Sudoku::operator[](size_t index) const
{
	return m_board[index];
}

SudokuCell & Sudoku::getCell(size_t row, size_t col)
{
	return m_board[row * 9 + col];
}

const SudokuCell & Sudoku::getCell(size_t row, size_t col) const
{
	return m_board[row * 9 + col];
}

SudokuColumn Sudoku::getColumn(size_t col)
{
	return SudokuColumn(&m_board[col], m_length);
}

const SudokuColumn Sudoku::getColumn(size_t col) const
{
	return SudokuColumn(&m_board[col], m_length);
}

const SudokuColumn Sudoku::getColumnByIndex(size_t index) const
{
	return SudokuColumn(&m_board[index % m_length], m_length);
}

const SudokuRow Sudoku::getRow(size_t row) const
{
	return SudokuRow(&m_board[row * m_length], m_length);
}

const SudokuRow Sudoku::getRowByIndex(size_t index) const
{
	return getRow(index / m_length);
}

const SudokuBox Sudoku::getBox(size_t box) const
{
	return SudokuBox(&m_board[((box / m_boxLength) * m_length + (box % m_boxLength)) * m_boxLength], m_length);
}

const SudokuBox Sudoku::getBoxByIndex(size_t index) const
{
	return getBox((index / m_length) / m_boxLength * m_boxLength + (index % m_length) / m_boxLength);
}

SudokuColumn Sudoku::getColumnByIndex(size_t index)
{
	return SudokuColumn(&m_board[index % m_length], m_length);
}

SudokuRow Sudoku::getRow(size_t row)
{
	return SudokuRow(&m_board[row * m_length], m_length);
}

SudokuRow Sudoku::getRowByIndex(size_t index)
{
	return getRow(index / m_length);
}

SudokuBox Sudoku::getBox(size_t box)
{
	return SudokuBox(&m_board[((box / m_boxLength) * m_length + (box % m_boxLength)) * m_boxLength], m_length);
}

SudokuBox Sudoku::getBoxByIndex(size_t index)
{
	return getBox((index / m_length) / m_boxLength * m_boxLength + (index % m_length) / m_boxLength);
}

bool Sudoku::solve()
{
	bool stuck = true;
	while (!isSolved()) {
		while (solveRowPerspective())
			stuck = false;
		while (solveColumnPerspective())
			stuck = false;
		while (solveBoxPerspective())
			stuck = false;

		if (stuck)
			return false;

		stuck = true;
	}
	return true;
}

void Sudoku::stepSolve()
{
	if (solveRowPerspective())
		return;
	if (solveColumnPerspective())
		return;
	if (solveBoxPerspective())
		return;
}

bool Sudoku::newSolve()
{
	return false;
}

int Sudoku::newStepSolve()
{
	int counter = 0;
	for (size_t i = 0; i < size(); ++i) {
		if (solveCell(i))
			return i;
	}

	int found;
	std::map<int, size_t> profile;
	for (auto e : m_possibleCellNumbers)
		profile[e] = 0;


	auto row = getRow(counter);
	auto rowProfile = profile;
	size_t i = 0;
	for (; row.size(); i++) {
		++rowProfile[row[i].number];
	}
	for (auto e : rowProfile) {
		if (e.second == 1) {

		}
	}
}

bool Sudoku::isSolved() const
{
	// Check if a cell is empty (0)
	if (end() != std::find_if(begin(), end(), [](const SudokuCell& cell) { return cell.number == 0; }))
		return false;

	for (size_t i = 0; i < length(); ++i) {
		const auto row = getRow(i);
		const auto col = getColumn(i);
		const auto box = getBox(i);

		if (!isContainerUnique(row))
			return false;

		if (!isContainerUnique(col))
			return false;

		if (!isContainerUnique(box))
			return false;
	}

	return true;
}

size_t Sudoku::size() const
{
	return m_boardSize;
}

size_t Sudoku::length() const
{
	return m_length;
}

size_t Sudoku::boxLength() const
{
	return m_boxLength;
}

SudokuCell * Sudoku::begin()
{
	return m_board;
}

const SudokuCell * Sudoku::begin() const
{
	return m_board;
}

SudokuCell * Sudoku::end()
{
	return m_board + m_boardSize;
}

const SudokuCell * Sudoku::end() const
{
	return m_board + m_boardSize;
}

bool Sudoku::operator==(const Sudoku & rhs)
{
	if (size() != rhs.size())
		return false;

	for (size_t i = 0; i < size(); ++i) {
		if ((*this)[i] != rhs[i])
			return false;
	}
	return true;
}

void Sudoku::print() const
{
	for (int i = 0; i < m_length; i++) {
		for (int j = 0; j < m_length; j++) {
			std::cout << m_board[j + i * m_length].number << ", ";
		}
		std::cout << "\n";
	}
}

Sudoku::~Sudoku()
{
	delete[] m_board;
}

void Sudoku::swap(Sudoku & rhs)
{
	std::swap(m_board, rhs.m_board);
	std::swap(m_length, rhs.m_length);
	std::swap(m_boardSize, rhs.m_boardSize);
	std::swap(m_boxLength, rhs.m_boxLength);
	std::swap(m_possibleCellNumbers, rhs.m_possibleCellNumbers);
}

void Sudoku::initializeCells()
{
	// Initilize set of possible numbers
	for (size_t i = 0; i < m_length; ++i) {
		m_possibleCellNumbers.insert(i + 1);
	}
	// Assign possible set to empty cells
	// Also sets original cells
	for (auto it = begin(); it != end(); ++it) {
		if ((*it).number == 0) {
			(*it).possible = m_possibleCellNumbers;
			(*it).changeable = true;
		}
		else
			(*it).changeable = false;
	}
}

template<typename T>
bool Sudoku::solveContainer(T container)
{
	std::map<int, size_t> containerProfile;
	for (auto e : m_possibleCellNumbers) {
		containerProfile[e] = 0;
	}

	int found = 0;

	for (auto it = container.begin(); it != container.end(); ++it) {

		if ((*it).number != 0)
			continue;
		for (auto e : (*it).possible) {
			++containerProfile[e];
		}
	}

	for (auto e : containerProfile) {
		if (e.second == 1) {
			found = e.first;
			break;
		}
	}
	if (found) {
		for (auto it = container.begin(); it != container.end(); ++it) {
			if ((*it).number != 0)
				continue;

			if ((*it).possible.count(found) == 1) {
				(*it).number = found;
				(*it).possible = { found };
				return true;
			}
		}
	}

	return false;
}

bool Sudoku::solveCell(size_t index) {
	auto row = getRowByIndex(index);
	auto col = getColumnByIndex(index);
	auto box = getBoxByIndex(index);

	auto& cell = (*this)[index];
	if (cell != 0)
		return false;

	for (auto it = row.begin(); it != row.end(); ++it) {
		cell.possible.erase((*it).number);
	}

	for (auto it = col.begin(); it != col.end(); ++it) {
		cell.possible.erase((*it).number);
	}

	for (auto it = box.begin(); it != box.end(); ++it) {
		cell.possible.erase((*it).number);
	}

	if (cell.possible.size() == 1) {
		cell = *operator[](index).possible.begin();
		return true;
	}

	return false;
}

bool Sudoku::solveRowPerspective()
{
	for (size_t j = 0; j < length(); ++j) {
		for (size_t i = 0; i < size(); ++i) {
			if (solveCell(i))
				return true;
		}
		if (solveContainer(getRow(j)))
			return true;
	}
	return false;
}

bool Sudoku::solveColumnPerspective()
{
	for (size_t j = 0; j < length(); ++j) {
		for (size_t i = 0; i < size(); ++i) {
			if (solveCell(i))
				return true;
		}
		if (solveContainer(getColumn(j)))
			return true;
	}
	return false;
}

bool Sudoku::solveBoxPerspective()
{
	for (size_t j = 0; j < length(); ++j) {
		for (size_t i = 0; i < size(); ++i) {
			if (solveCell(i))
				return true;
		}
		if (solveContainer(getBox(j)))
			return true;
	}
	return false;
}

bool Sudoku::isCellUnique(size_t index) const {
	auto cell = (*this)[index];
	if (cell.number == 0)
		return false;

	const auto row = getRowByIndex(index);
	const auto col = getColumnByIndex(index);
	const auto box = getBoxByIndex(index);

	auto isCellDuplicate = [cell](const SudokuCell& rhs) {
		return cell == rhs;
	};

	if (row.end() != std::find_if(row.begin(), row.end(), isCellDuplicate))
		return false;

	if (col.end() != std::find_if(col.begin(), col.end(), isCellDuplicate))
		return false;

	if (box.end() != std::find_if(box.begin(), box.end(), isCellDuplicate))
		return false;

	return true;
}

template<typename T>
bool Sudoku::isContainerUnique(const T& container) const {
	std::map<int, size_t> map;
	for (auto e : m_possibleCellNumbers) {
		map[e] = 0;
	}

	for (auto it = container.begin(); it != container.end(); ++it) {
		++map[(*it).number];
	}
	for (auto e : map) {
		if (e.second != 1)
			return false;
	}

	return true;
}
