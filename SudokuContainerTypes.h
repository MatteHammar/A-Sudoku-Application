// Projekt - Sudoku, ProgrammeringsMetodik - DT047G
// Mathias Hammarström
// SudokuContainerTypes.h, 14-12-2021, 14-01-2022
// Provides specialized interface for a Sudoku object for easier navigation.
// They are fully dependant on a Sudoku object cause they do not own their own resources, but instead looks into a Sudoku objects resource
// Hence all of these special "containers" can not be created normally, only a Sudoku object can create a valid Row/Column/Box.


#ifndef SUDOKU_CONTAINERS_H
#define SUDOKU_CONTAINERS_H

#include "SudokuIterator.h"


//! SudokuCell represents a cell in a Sudoku array
struct SudokuCell {
	//! The integer which the cell represents
	int number;
	//! Used to create "original" cells which should not be changed
	bool changeable;

	//! Set of possible integers the cell can be
	std::set<int> possible;

	//! Default Constructor
	SudokuCell() : number(0), possible({}), changeable(true) {}
	//! Converting Constructor
	SudokuCell(int n) :number(n), possible({}), changeable(true) {}

	//! Assign operator, copies rhs's number
	void operator=(const int& rhs) { number = rhs; }
	//! Assign operator, converts string to int and copies that
	void operator=(std::string rhs) { number = std::stoi(rhs); }

	//! Compares Cells by looking at the number member
	bool operator==(const SudokuCell& rhs)	const { return number == rhs.number; }
	//! Compares cell to integer by looking at the number member
	bool operator==(const int& rhs)			const { return number == rhs; }
	//! Compares Cells by looking at the number member
	bool operator!=(const SudokuCell& rhs)	const { return number != rhs.number; }
	//! Compares cell to integer by looking at the number member
	bool operator!=(const int& rhs)			const { return number != rhs; }
};

//! Represents a row in a 2d array

//! Does not own its own resource but uses a Sudoku objects array to represent.
struct SudokuRow {
	//! Only a Sudoku object can construct a valid SudokuRow
	friend class Sudoku;

private:
	//! Copies pointer and size to know where to look

	//! Does not copy the cells, only copies the pointer and size
	//! Which means it looks into that pointers memory space.
	SudokuRow(SudokuCell* source, size_t size);

public:
	//! Copy constructor
	SudokuRow(const SudokuRow& rhs);
	//! Move constructor
	SudokuRow(SudokuRow&& rhs);

	//! Copy assign
	SudokuRow& operator=(const SudokuRow& rhs);
	//! Move assign
	SudokuRow& operator=(SudokuRow&& rhs);

	//! Gets the SudokuCell that exists in that index
	SudokuCell& operator[](size_t index);
	//! Gets the SudokuCell that exists in that index
	const SudokuCell& operator[](size_t index) const;

	//! Returns a SudokuRowIterator that points to the beginning of row
	SudokuRowIterator<SudokuCell> begin();
	//! Returns a SudokuRowIterator that points to the end row
	SudokuRowIterator<SudokuCell> end();
	//! Returns a SudokuRowIterator that points to the beginning of row
	SudokuRowIterator<const SudokuCell> begin()	const;
	//! Returns a SudokuRowIterator that points to the end row
	SudokuRowIterator<const SudokuCell> end()	const;

	//! Returns size of row
	size_t size() const;

private:
	//! Beginning pointer
	SudokuCell* m_begin;
	//! End pointer
	SudokuCell* m_end;

private:
	//! Swap resources with rhs
	void swap(SudokuRow& rhs);
};


//! Represents a column in a 2d array with square dimensions, ex. (2x2), (5x5) and so on...
struct SudokuColumn {
	//! Only a Sudoku object can construct a valid SudokuColumn
	friend class Sudoku;

private:
	//! Copies pointer and size to know where to look

	//! Does not copy the cells, only copies the pointer and size
	//! Which means it looks into that pointers memory space.
	SudokuColumn(SudokuCell* source, size_t size);

public:
	//! Copy constructor
	SudokuColumn(const SudokuColumn& rhs);
	//! Move constructor
	SudokuColumn(SudokuColumn&& rhs);

	//! Copy assign
	SudokuColumn& operator=(const SudokuColumn& rhs);
	//! Move assign
	SudokuColumn& operator=(SudokuColumn&& rhs);

	//! Gets the SudokuCell that exists in that index of the column
	SudokuCell& operator[](size_t index);
	//! Gets the SudokuCell that exists in that index of the column
	const SudokuCell& operator[](size_t index) const;

	//! Returns a SudokuColumnIterator that points to the beginning of column
	SudokuColumnIterator<SudokuCell> begin();
	//! Returns a SudokuColumnIterator that points to the end of column
	SudokuColumnIterator<SudokuCell> end();
	//! Returns a SudokuColumnIterator that points to the beginning of column
	SudokuColumnIterator<const SudokuCell> begin()	const;
	//! Returns a SudokuColumnIterator that points to the end of column
	SudokuColumnIterator<const SudokuCell> end()	const;

	//! Returns size of column
	size_t size() const;

private:
	//! Beginning pointer
	SudokuCell* m_begin;
	//! End pointer
	SudokuCell* m_end;
	//! Length of array, used for knowing how far to "jump" in array to next index
	size_t m_size;

private:
	//! Swaps resources with another column
	void swap(SudokuColumn& rhs);
};


//! Represents a box in a 2d array with squared dimensions (4x4, 9x9, 16x16)
struct SudokuBox {
	//! Only a Sudoku object can construct a valid SudokuColumn
	friend class Sudoku;

private:
	//! Copies pointer and size to know where to look

	//! Does not copy the cells, only copies the pointer and size
	//! Which means it looks into that pointers memory space.
	SudokuBox(SudokuCell* source, size_t size);

public:
	//! Copy constructor
	SudokuBox(const SudokuBox& rhs);
	//! Move constructor
	SudokuBox(SudokuBox&& rhs);

	//! Copy assign
	SudokuBox& operator=(const SudokuBox& rhs);
	//! Move assign
	SudokuBox& operator=(SudokuBox&& rhs);

	//! Gets the SudokuCell that exists in that index of the box
	SudokuCell& operator[](size_t index);
	//! Gets the SudokuCell that exists in that index of the box
	const SudokuCell& operator[](size_t index) const;

	//! Returns a SudokuBoxIterator that points to the beginning of column
	SudokuBoxIterator<SudokuCell> begin();
	//! Returns a SudokuBoxIterator that points to the end of column
	SudokuBoxIterator<SudokuCell> end();
	//! Returns a SudokuBoxIterator that points to the beginning of column
	SudokuBoxIterator<const SudokuCell> begin()	const;
	//! Returns a SudokuBoxIterator that points to the end of column
	SudokuBoxIterator<const SudokuCell> end()	const;

	//! Returns size of box
	size_t size() const;

private:
	//! Beginning pointer
	SudokuCell* m_begin;
	//! End pointer
	SudokuCell* m_end;
	//! Size of box
	size_t m_size;

private:
	//! Swaps resource with another box
	void swap(SudokuBox& rhs);
};

#endif SUDOKU_CONTAINERS_H