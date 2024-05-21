// Projekt - Sudoku, ProgrammeringsMetodik - DT047G
// Mathias Hammarström
// Sudoku.h, 14-12-2021, 14-01-2022


#ifndef SUDOKU_H
#define SUDOKU_H

#include "SudokuContainerTypes.h"
#include "SudokuFileHandler.h"


//! Sudoku class, represents a Sudoku state.
class Sudoku {
public:
	//! Default constructor
	Sudoku();
	//! Creates an empty sudoku state with size given.

	//! size argument is the length of a box to avoid getting non-quadratic numbers
	//! Example, a normal 9x9 sudoku has box length of 3. And thus should be given a argument of 3.
	explicit Sudoku(size_t size);

	//! Loads sudoku from file using SudokuFileHandler.

	//! If file format is not recognized the sudoku object resources will be null.
	explicit Sudoku(std::string filename);

	//! Creates a sudoku state using an array as input
	Sudoku(const SudokuCell* begin, size_t size);

	//! Copy constructor
	Sudoku(const Sudoku& rhs);
	//! Move constructor
	Sudoku(Sudoku&& rhs);

	//! Copy assign
	Sudoku& operator=(const Sudoku& rhs);
	//! Move assign
	Sudoku& operator=(Sudoku&& rhs);

	//! Accesses SudokuCell based on index
	SudokuCell& operator[](size_t index);
	//! Accesses SudokuCell based on index
	const SudokuCell& operator[](size_t index) const;
	//! Accesses SudokuCell based on row and column
	SudokuCell& getCell(size_t row, size_t col);
	//! Accesses SudokuCell based on row and column
	const SudokuCell& getCell(size_t row, size_t col) const;

	//! Special container views into Sudokuboard
	//! These containers only point towards an existing Sudoku objects m_board array,
	//! hence should only be used as long as the sudoku object exists.

	//! Returns a SudokuColumn for given column
	SudokuColumn		getColumn(size_t col);
	//! Returns a SudokuColumn for given index
	SudokuColumn		getColumnByIndex(size_t index);
	//! Returns a SudokuRow for given row
	SudokuRow			getRow(size_t row);
	//! Returns a SudokuRow for given index
	SudokuRow			getRowByIndex(size_t index);
	//! Returns a SudokuBox for given box
	SudokuBox			getBox(size_t box);
	//! Returns a SudokuBox for given index
	SudokuBox			getBoxByIndex(size_t index);
	//! Returns a SudokuColumn for given column
	const SudokuColumn	getColumn(size_t col) const;
	//! Returns a SudokuColumn for given index
	const SudokuColumn	getColumnByIndex(size_t index) const;
	//! Returns a SudokuRow for given row
	const SudokuRow		getRow(size_t row) const;
	//! Returns a SudokuRow for given index
	const SudokuRow		getRowByIndex(size_t index) const;
	//! Returns a SudokuBox for given box
	const SudokuBox		getBox(size_t box) const;
	//! Returns a SudokuBox for given index
	const SudokuBox		getBoxByIndex(size_t index) const;

	//! Tries to solve entire sudoku
	bool solve();
	//! Solves only one step
	void stepSolve();

	bool newSolve();
	int newStepSolve();


	//! Get size of sudoku array. ex, a 9x9 sudoku has size 81
	size_t size() const;
	//! Gets size of sudoku length. ex, a 9x9 sudoku has length 9
	size_t length() const;
	//! Gets size of a sudoku box length. ex, a 9x9 sudoku has boxlength 3
	size_t boxLength() const;
	//! Prints sudoku state using std::cout
	void print() const;
	//! Checks if the sudoku is solved
	bool isSolved() const;

	//! Returns the beginning of the array
	SudokuCell* begin();
	//! Returns the beginning of the array
	const SudokuCell* begin() const;
	//! Returns the end of the array
	SudokuCell* end();
	//! Returns the end of the array
	const SudokuCell* end() const;

	//! Compares itself to given Sudoku object.

	//! Compares size then checks if the cell numbers are exactly the same
	bool operator==(const Sudoku& rhs);

	//! Destructor
	~Sudoku();

private:
	//! Array of SudokuCells, this represents the sudoku state
	SudokuCell* m_board;
	//! Size of array
	size_t m_boardSize;

	//! Length of sudoku
	size_t m_length;
	//! Boxlength of sudoku
	size_t m_boxLength;

	//! Contains the set of possible integer for the sudoku
	std::set<int> m_possibleCellNumbers;

private:
	//! Swaps resources with rhs
	void swap(Sudoku& rhs);

	//! Assign each cells possibleNumber set
	void initializeCells();

	//! Try to solve container

	//! Expects container to have begin() and end() member functions and that container contains SudokuCell
	//! Creates a profile of possible integer for a container
	//! And checks if any integer only has one possible cell to exist in, from the perspective of the container
	//! If so then change the cell to that integer even tho the cell can be several other integers from the perspective of the cell 
	template<typename T>
	bool solveContainer(T container);
	//! Solve cell

	//! Looks through each row, column and box for cell integers which it cannot be
	//! And deletes these integers from its possible integer set, if only one integer remains then assign cell.number to that
	bool solveCell(size_t index);

	//! Solve from perspective of row, uses solveContainer(T container)
	bool solveRowPerspective();
	//! Solve from perspective of column, uses solveContainer(T container)
	bool solveColumnPerspective();
	//! Solve from perspective of box, uses solveContainer(T container)
	bool solveBoxPerspective();


	//! Checks if a container is unique, in other words there is no duplicate integers in sight.
	template<typename T>
	bool isContainerUnique(const T& container) const;
	//! Checks if a cell is unique, in other words there is no duplicate integers in sight.
	bool isCellUnique(size_t index) const;

public:
	//! Constant, Normal 9x9 sudoku size
	static constexpr size_t NORMAL_9x9_SIZE = 3;
	//! Constant, Normal 16x16 sudoku size
	static constexpr size_t BIG_16x16_SIZE = 4;
};

#endif SUDOKU_H