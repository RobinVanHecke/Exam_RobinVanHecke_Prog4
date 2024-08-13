#pragma once

#include <memory>
#include <vector>

#include "GridCell.h"

class Grid final
{
public:
	Grid() = default;

	void AddCell(const glm::vec2& pos, CellType type, int row, int col);
	GridCell* GetCell(const glm::vec2& pos) const;
	GridCell* GetCell(int row, int col);
	GridCell* GetCellCloseType(const glm::vec2& pos, CellType type);

	const std::vector<GridCell*> GetCells() const;

private:
	std::vector<std::unique_ptr<GridCell>> m_pCells;
	const float m_CellLength{ 32.f };
	const float m_Epsilon{ 0.1f };
	const int m_MaxCol{ 9 };

	void CalcGrid();
	bool CheckTopCell(GridCell* pCell, GridCell* pOtherCell);
	bool CheckRightCell(GridCell* pCell, GridCell* pOtherCell, float offset);
};