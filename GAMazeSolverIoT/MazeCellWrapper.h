#include "..\GASolver\MazeCell.h"

// A managed wrapper class for a MazeCell
ref class MazeCellWrapper : public Object
{
public:
	Windows::UI::Color CellBrush()
	{
		switch ((MazeCell::CELLSTATE)GetCellStatus())
		{
		case MazeCell::CELLSTATE::Free:
			return Windows::UI::Colors::Black;
		case MazeCell::CELLSTATE::Valid:
			return Windows::UI::Colors::Violet;
		case MazeCell::CELLSTATE::Start:
			return Windows::UI::Colors::Green;
		case MazeCell::CELLSTATE::Finish:
			return Windows::UI::Colors::Red;
		case MazeCell::CELLSTATE::Wall:
			return Windows::UI::Colors::Gray;
		case MazeCell::CELLSTATE::FakeWall:
			return Windows::UI::Colors::Yellow;
		}
	}

	int GetColumn()
	{
		return cell.GetMatX();
	}
	int GetRow()
	{
		return cell.GetMatY();
	}
	void SetColumn(int col)
	{
		cell.SetMatY(col);
	}
	void SetRow(int row)
	{
		cell.SetMatX(row);
	}
	int GetCellStatus()
	{
		return (int)cell.GetCellStatus();
	}
	void SetCellStatus(int state)
	{
		return cell.SetCellStatus((MazeCell::CELLSTATE)state);
	}
private:
	MazeCell cell;
};