// Projekt - Sudoku, ProgrammeringsMetodik - DT047G
// Mathias Hammarström
// SudokuContainerTypes.h, 14-12-2021, 13-01-2022
// Provides specialized interface for a Sudoku object, implementation

#include "SudokuContainerTypes.h"
#include <algorithm>


SudokuRow::SudokuRow(SudokuCell * source, size_t size) : m_begin(source), m_end(source + size)
{
}

SudokuRow::SudokuRow(const SudokuRow & rhs) : SudokuRow(rhs.m_begin, rhs.size())
{
}

SudokuRow::SudokuRow(SudokuRow && rhs) : m_begin(nullptr), m_end(nullptr)
{
	swap(rhs);
}

SudokuRow& SudokuRow::operator=(const SudokuRow & rhs)
{
	SudokuRow copy = rhs;
	swap(copy);
	return *this;
}

SudokuRow& SudokuRow::operator=(SudokuRow && rhs)
{
	swap(rhs);
	return *this;
}

SudokuCell& SudokuRow::operator[](size_t index)
{
	return *(m_begin + index);
}

const SudokuCell & SudokuRow::operator[](size_t index) const
{
	return *(m_begin + index);
}

size_t SudokuRow::size() const
{
	return m_end - m_begin;
}

SudokuRowIterator<SudokuCell> SudokuRow::begin()
{
	return SudokuRowIterator<SudokuCell>(m_begin, (m_end - m_begin));
}

SudokuRowIterator<SudokuCell> SudokuRow::end()
{
	return SudokuRowIterator<SudokuCell>(m_end, (m_end - m_begin));
}

SudokuRowIterator<const SudokuCell> SudokuRow::begin() const
{
	return SudokuRowIterator<const SudokuCell>(m_begin, (m_end - m_begin));
}

SudokuRowIterator<const SudokuCell> SudokuRow::end() const
{
	return SudokuRowIterator<const SudokuCell>(m_end, (m_end - m_begin));
}

void SudokuRow::swap(SudokuRow & rhs)
{
	std::swap(m_begin, rhs.m_begin);
	std::swap(m_end, rhs.m_end);
}


SudokuColumn::SudokuColumn(SudokuCell * source, size_t size) : m_begin(source), m_end(source + size * size), m_size(size)
{
}

SudokuColumn::SudokuColumn(const SudokuColumn & rhs) : SudokuColumn(rhs.m_begin, rhs.m_size)
{
}

SudokuColumn::SudokuColumn(SudokuColumn && rhs) : m_begin(nullptr), m_end(nullptr), m_size(0)
{
	swap(rhs);
}

SudokuColumn & SudokuColumn::operator=(const SudokuColumn & rhs)
{
	SudokuColumn copy = rhs;
	swap(copy);
	return *this;
}

SudokuColumn & SudokuColumn::operator=(SudokuColumn && rhs)
{
	swap(rhs);
	return *this;
}

SudokuCell & SudokuColumn::operator[](size_t index)
{
	return *(m_begin + index * m_size);
}

const SudokuCell & SudokuColumn::operator[](size_t index) const
{
	return *(m_begin + index * m_size);
}

size_t SudokuColumn::size() const
{
	return m_size;
}

SudokuColumnIterator<SudokuCell> SudokuColumn::begin()
{
	return SudokuColumnIterator<SudokuCell>(m_begin, m_size);
}

SudokuColumnIterator<SudokuCell> SudokuColumn::end()
{
	return SudokuColumnIterator<SudokuCell>(m_end, m_size);
}

SudokuColumnIterator<const SudokuCell> SudokuColumn::begin() const
{
	return SudokuColumnIterator<const SudokuCell>(m_begin, m_size);
}

SudokuColumnIterator<const SudokuCell> SudokuColumn::end() const
{
	return SudokuColumnIterator<const SudokuCell>(m_end, m_size);
}

void SudokuColumn::swap(SudokuColumn & rhs)
{
	std::swap(m_begin, rhs.m_begin);
	std::swap(m_end, rhs.m_end);
	std::swap(m_size, rhs.m_size);
}

SudokuBox::SudokuBox(SudokuCell * source, size_t size) : m_begin(source), m_end(source + ((int)sqrt(size) - 1) * size + size), m_size(size)
{
}

SudokuBox::SudokuBox(const SudokuBox & rhs) : SudokuBox(rhs.m_begin, rhs.m_size)
{
}

SudokuBox::SudokuBox(SudokuBox && rhs) : m_begin(nullptr), m_end(nullptr), m_size(0)
{
	swap(rhs);
}

SudokuBox & SudokuBox::operator=(const SudokuBox & rhs)
{
	SudokuBox copy = rhs;
	swap(copy);
	return *this;
}

SudokuBox & SudokuBox::operator=(SudokuBox && rhs)
{
	swap(rhs);
	return *this;
}

SudokuCell & SudokuBox::operator[](size_t index)
{
	int boxLength = sqrt(m_size);
	return *(m_begin + (index % boxLength) + (index / boxLength) * m_size);
}

const SudokuCell & SudokuBox::operator[](size_t index) const
{
	int boxLength = sqrt(m_size);
	return *(m_begin + (index % boxLength) + (index / boxLength) * m_size);
}

size_t SudokuBox::size() const
{
	return m_size;
}

SudokuBoxIterator<SudokuCell> SudokuBox::begin()
{
	return SudokuBoxIterator<SudokuCell>(m_begin, m_size);
}

SudokuBoxIterator<SudokuCell> SudokuBox::end()
{
	return SudokuBoxIterator<SudokuCell>(m_end, m_size);
}

SudokuBoxIterator<const SudokuCell> SudokuBox::begin() const
{
	return SudokuBoxIterator<const SudokuCell>(m_begin, m_size);
}

SudokuBoxIterator<const SudokuCell> SudokuBox::end() const
{
	return SudokuBoxIterator<const SudokuCell>(m_end, m_size);
}

void SudokuBox::swap(SudokuBox & rhs)
{
	std::swap(m_begin, rhs.m_begin);
	std::swap(m_end, rhs.m_end);
	std::swap(m_size, rhs.m_size);
}
