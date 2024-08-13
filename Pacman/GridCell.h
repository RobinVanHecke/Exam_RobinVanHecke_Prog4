#pragma once
#include <glm/vec2.hpp>

enum class CellType
{
	FloorShort, FloorLong,
	Ladder,
	Plate,
	EmptyShort, EmptyLong,
	UpShort, UpLong,
	DownShort, DownLong,
	BothShort, BothLong
};

struct GridCell
{
	GridCell(const glm::vec2& pos, const CellType type, const int row, const int col ):
	m_Pos(pos),
	m_Type(type),
	m_Row(row),
	m_Col(col){}

	~GridCell()
	{
		delete pTop; pTop = nullptr;
		delete pBottom; pBottom = nullptr;
		delete pRight; pRight = nullptr;
		delete pLeft; pLeft = nullptr;
	}

	glm::vec2 m_Pos{};
	CellType m_Type{};
	int m_Row{}, m_Col{};

	GridCell* pTop{ nullptr };
	GridCell* pBottom{ nullptr };
	GridCell* pRight{ nullptr };
	GridCell* pLeft{ nullptr };

};
