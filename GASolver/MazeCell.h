#ifndef MAZECELL_H
#define MAZECELL_H

#include <string>

class MazeCell
{
public:
	enum class CELLSTATE : int
	{
		Free,
		Wall,
		Start,
		Finish,
		Valid,	// Valid means visited, verified as passable, and connected to Start
		FakeWall
	};
	CELLSTATE _STATUS;
	int _MATX;
	int _MATY;
	static const int MAZESIZE = 20;
	static const int MAZESIDE = 15;

	CELLSTATE GetCellStatus()
	{
		return _STATUS;
	}

	void SetCellStatus(CELLSTATE value)
	{
		_STATUS = value;
	}

	int GetMatX()
	{
		return _MATX;
	}
	
	void SetMatX(int value)
	{
		_MATX = value;
	}

	int GetMatY()
	{
		return _MATY;
	}

	void SetMatY(int value)
	{
		_MATY = value;
	}

	std::string StringMatrix()
	{
		std::string out;
		out += _MATX;
		out += ";";
		out += _MATY;
		return out;
	}
};

#endif