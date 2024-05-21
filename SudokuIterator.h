// Projekt - Sudoku, ProgrammeringsMetodik - DT047G
// Mathias Hammarström
// SudokuIterator.h, 14-12-2021, 14-01-2022
/**
 * SudokuIterator class.Iterators that behaves like a forward iterator in a specialized container
 *
 * SudokuRowIterator is practically a normal forward iterator, moves forward incrementally with no trickery behind the scenes.

 * SudokuColumnIterator behaves like a normal forward iterator (from outside perspective) by moving incrementally, however there is trickery behind the scenes.
 * Treats an array like a 2d array. As it "jump" rows as it increments.
 
 * SudokuBoxIterator also behaves like a normal forward iterator from the outside. It can also "jump around" in a container when moving incrementally.
 * Also treats an array like a 2d array, it needs an array that is or has a subarray that can be converted to a square array with quadratic dimensions. 
 * Which means both the height and length of the converted array/subarray must be the same, while the height/length is a quadratic integer (4, 9, 16...)
 * Because it assumes that the subarray that is walks is a perfect square root of the full array.
 * So if the full array represents a 16x16 square, then SudokuBoxIterators assumes that it walks in a 4x4 square.
 *
 */


#ifndef SUDOKU_ITERATOR_H
#define SUDOKU_ITERATOR_H

#include <math.h>
#include <set>
#include <iterator>
#include <string>

//! SudokuRowIterator is a forward_iterator.
template<typename T>
class SudokuRowIterator : public std::iterator<std::forward_iterator_tag, T, std::ptrdiff_t, T*, T&> {
public:
	//! No Default constructor
	SudokuRowIterator() = delete;
	//! Constructor that copies the pointer and size
	explicit SudokuRowIterator(T* source, size_t size) : m_ptr(source), m_size(size) {}

	//! Copy constructor
	SudokuRowIterator(const SudokuRowIterator& rhs) : SudokuRowIterator(rhs.m_ptr, rhs.m_size) {}
	//! Move constructor
	SudokuRowIterator(SudokuRowIterator&& rhs) : m_ptr(nullptr), m_size(0) {
		swap(rhs);
	}

	//! Copy assign
	SudokuRowIterator& operator=(const SudokuRowIterator& rhs) {
		SudokuRowIterator copy = rhs;
		swap(copy);
		return *this;
	}
	//! Move assign
	SudokuRowIterator& operator=(SudokuRowIterator&& rhs) {
		swap(rhs);
		return *this;
	}

	//! Pre Increment
	SudokuRowIterator& operator++() {
		++m_ptr;
		return *this;
	}
	//! Post Increment
	SudokuRowIterator& operator++(int) {
		SudokuRowIterator copy = *this;
		++m_ptr;
		return copy;
	}

	//! Difference operator, calculates difference between its own ptr and it.ptr
	std::ptrdiff_t operator-(const SudokuRowIterator& it) const {
		return std::distance(it.m_ptr, m_ptr);
	}

	//! Compares pointer with it
	bool operator!=(const SudokuRowIterator& it) const {
		return m_ptr != it.m_ptr;
	}
	//! Compares pointer with it
	bool operator==(const SudokuRowIterator& it) const {
		return m_ptr == it.m_ptr;
	}

	//! Return whatever the pointer is looking at
	T& operator*() {
		return *m_ptr;
	}

private:
	//! Pointer used to traverse
	T* m_ptr;
	//! Length of row
	size_t m_size;

private:
	//! Swaps resources with another SudokuRowIterator
	void swap(SudokuRowIterator& rhs) {
		std::swap(m_ptr, rhs.m_ptr);
		std::swap(m_size, rhs.m_size);
	}
};

//! SudokuColumnIterator behaves like a normal forward iterator (from outside perspective) by moving incrementally, however there is trickery behind the scenes.

//! Treats an array like a 2d array.As it "jump" rows as it increments.
template<typename T>
class SudokuColumnIterator : public std::iterator<std::forward_iterator_tag, T, std::ptrdiff_t, T*, T&> {
public:
	//! No Default constructor
	SudokuColumnIterator() = delete;
	//! Constructor that copies the pointer and size
	SudokuColumnIterator(T* source, size_t size) :m_ptr(source), m_size(size) {}

	//! Copy constructor
	SudokuColumnIterator(const SudokuColumnIterator& rhs) :SudokuColumnIterator(rhs.m_ptr, rhs.m_size) {}
	//! Move constructor
	SudokuColumnIterator(SudokuColumnIterator&& rhs) :m_ptr(nullptr), m_size(0) {
		swap(rhs);
	}

	//! Copy assign
	SudokuColumnIterator& operator=(const SudokuColumnIterator& rhs) {
		SudokuColumnIterator temp = rhs;
		swap(temp);
		return *this;
	}
	//! Move assign
	SudokuColumnIterator& operator=(SudokuColumnIterator&& rhs) {
		swap(rhs);
		return *this;
	}

	//! Pre Increment

	//! Jumps the length of array to the next row.
	SudokuColumnIterator& operator++() {
		m_ptr += m_size;
		return *this;
	}
	//! Post Increment

	//! Jumps the length of array to the next row.
	SudokuColumnIterator& operator++(int) {
		SudokuColumnIterator copy = *this;
		m_ptr += m_size;
		return copy;
	}

	//! Difference operator, calculates difference between its own ptr and it.ptr
	std::ptrdiff_t operator-(const SudokuColumnIterator& it) const {
		return std::distance(it.m_ptr, m_ptr);
	}

	//! Compares pointer with it
	bool operator!=(const SudokuColumnIterator& it) const {
		return it.m_ptr != m_ptr;
	}
	//! Compares pointer with it
	bool operator==(const SudokuColumnIterator& it) const {
		return it.m_ptr == m_ptr;
	}

	//! Return whatever the pointer is looking at
	T& operator*() {
		return *m_ptr;
	}

private:
	//! Pointer used to traverse
	T* m_ptr;
	//! Length of row in original array, as it needs to know how far to jump
	size_t m_size;

private:
	//! Swaps resources with another SudokuColumnIterator
	void swap(SudokuColumnIterator& rhs) {
		std::swap(m_ptr, rhs.m_ptr);
		std::swap(m_size, rhs.m_size);
	}
};

//! SudokuBoxIterator behaves like a normal forward iterator from the outside. It does however "jump around" in an array when moving incrementally.

//! Treats an array like a 2d array, it needs an array that is or has a subarray that can be converted to a square array with quadratic dimensions.
//! Which means both the height and length of the converted array / subarray must be the same, while the height / length is a quadratic integer(4, 9, 16...)
//! Because it assumes that the subarray that is walks is a perfect square root of the full array.
//! So if the full array represents a 16x16 square, then SudokuBoxIterators assumes that it walks in a 4x4 square.
template<typename T>
class SudokuBoxIterator : public std::iterator<std::forward_iterator_tag, T, std::ptrdiff_t, T*, T&> {
public:
	//! No Default constructor
	SudokuBoxIterator() = delete;
	//! Constructor that copies the pointer and size
	SudokuBoxIterator(T* source, size_t size) :m_ptr(source), m_size(size), m_boxlength(sqrt(size)), m_stepsTravelled(0) {}

	//! Copy constructor
	SudokuBoxIterator(const SudokuBoxIterator& rhs) :SudokuBoxIterator(rhs.m_ptr, rhs.m_size) {}
	//! Move constructor
	SudokuBoxIterator(SudokuBoxIterator&& rhs) :m_ptr(nullptr), m_size(0), m_boxlength(0), m_stepsTravelled(0) {
		swap(rhs);
	}

	//! Copy assign
	SudokuBoxIterator& operator=(const SudokuBoxIterator& rhs) {
		SudokuBoxIterator copy = rhs;
		swap(copy);
		return *this;
	}
	//! Move assign
	SudokuBoxIterator& operator=(SudokuBoxIterator&& rhs) {
		swap(rhs);
		return *this;
	}

	//! Pre Increment

	//! If at the edge of box jump to the next index in array that exist in the box
	SudokuBoxIterator& operator++() {
		// If at edge of box "jump" to next row
		// else walk normally
		if (atEdgeOfBox())
			m_ptr += m_size - (m_boxlength - 1);
		else
			++m_ptr;

		++m_stepsTravelled;
		return *this;
	}
	//! Post Increment

	//! If at the edge of box jump to the next index in array that exist in the box
	SudokuBoxIterator& operator++(int) {
		SudokuBoxIterator copy = *this;

		// If at edge of box "jump" to next row
		// else walk normally
		++this;
		return copy;
	}

	//! Difference operator, calculates difference between its own ptr and it.ptr
	std::ptrdiff_t operator-(const SudokuBoxIterator& it) const {
		return std::distance(it.m_ptr, m_ptr);
	}

	//! Compares pointer with it
	bool operator!=(const SudokuBoxIterator& it) const {
		return it.m_ptr != m_ptr;
	}
	//! Compares pointer with it
	bool operator==(const SudokuBoxIterator& it) const {
		return it.m_ptr == m_ptr;
	}

	//! Return whatever the pointer is looking at
	T& operator*() {
		return *m_ptr;
	}

private:
	//! Pointer used to traverse
	T* m_ptr;
	//! size of box
	size_t m_size;

	//! length of box, ex. 3x3 box has length 3
	size_t m_boxlength;
	//! Keeps track of many steps have been traversed to know when to jump
	size_t m_stepsTravelled;

private:
	//! Swaps resources with another SudokuColumnIterator
	void swap(SudokuBoxIterator& rhs) {
		std::swap(m_ptr, rhs.m_ptr);
		std::swap(m_size, rhs.m_size);
		std::swap(m_boxlength, rhs.m_boxlength);
		std::swap(m_stepsTravelled, rhs.m_stepsTravelled);
	}

	//! Checks if we are at the edge of box
	bool atEdgeOfBox() const {
		return (m_stepsTravelled % m_boxlength == m_boxlength - 1);
	}
};

#endif SUDOKU_ITERATOR_H