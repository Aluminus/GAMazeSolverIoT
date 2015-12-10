#ifndef GASOLVER_H
#define GASOLVER_H

#include "MazeCell.h"
#include <random>
#include <chrono>

class GASolver
{
public:
	struct Coord
	{
		int X;
		int Y;
	};
	Coord _startpos;
	Coord _endPos;
	bool _isSolved;

	MazeCell::CELLSTATE solverBytes[MazeCell::MAZESIZE][MazeCell::MAZESIZE];

	// This is the constructor that crosses two solvers into a new one
	// The solver is initialized to "Free" and the Walls from both parents are added
	// 1% of Free cells are swapped out for FakeWalls
	GASolver(MazeCell::CELLSTATE bytes01[MazeCell::MAZESIZE][MazeCell::MAZESIZE], MazeCell::CELLSTATE bytes02[MazeCell::MAZESIZE][MazeCell::MAZESIZE], Coord startPos, Coord endPos)
		:_startpos(startPos), _endPos(endPos), solved(false)
	{
		// Phase 1: Initialize 
		for (int _Y = 0; _Y < MazeCell::MAZESIZE; _Y++)
		{
			for (int _X = 0; _X < MazeCell::MAZESIZE; _X++)
			{
				solverBytes[_X][_Y] = MazeCell::CELLSTATE::Free;
			}
		}

		// Phase 2: Gather Walls and FakeWalls from the first parent
		for (int _Y = 0; _Y < MazeCell::MAZESIZE; _Y++)
		{
			for (int _X = 0; _X < MazeCell::MAZESIZE; _X++)
			{
				if (bytes01[_X][_Y] == MazeCell::CELLSTATE::Wall)
					solverBytes[_X][_Y] = bytes01[_X][_Y];
				if (bytes01[_X][_Y] == MazeCell::CELLSTATE::FakeWall)
					solverBytes[_X][_Y] = bytes01[_X][_Y];
			}
		}

		// Phase 3: Gather Walls and FakeWalls from the second parent
		for (int _Y = 0; _Y < MazeCell::MAZESIZE; _Y++)
		{
			for (int _X = 0; _X < MazeCell::MAZESIZE; _X++)
			{
				if (bytes02[_X][_Y] == MazeCell::CELLSTATE::Wall)
					solverBytes[_X][_Y] = bytes02[_X][_Y];
				if (bytes02[_X][_Y] == MazeCell::CELLSTATE::FakeWall)
					solverBytes[_X][_Y] = bytes02[_X][_Y];
			}
		}

		// Phase 4: Introduce some chaos! (to escape local minima)
		std::default_random_engine e(std::chrono::system_clock::now().time_since_epoch().count());
		std::bernoulli_distribution rnd(0.1);	
		for (int _Y = 0; _Y < MazeCell::MAZESIZE; _Y++)
		{
			for (int _X = 0; _X < MazeCell::MAZESIZE; _X++)
			{
				if (solverBytes[_X][_Y] != MazeCell::CELLSTATE::Wall)
				{
					if (rnd(e))	// 10% of non-Wall cells will be changed
					{
						if (rnd(e))	// 10% of those will be set to FakeWalls
							solverBytes[_X][_Y] = MazeCell::CELLSTATE::FakeWall;
						else
							solverBytes[_X][_Y] = MazeCell::CELLSTATE::Free;
					}
				}
			}
		}

		// The Start and Finish cells are the same for both bytes01 and bytes02, so it's quicker to set them here
		solverBytes[startPos.X][startPos.Y] = MazeCell::CELLSTATE::Start;
		solverBytes[endPos.X][endPos.Y] = MazeCell::CELLSTATE::Finish;
	}

	GASolver(MazeCell::CELLSTATE sourceBytes[MazeCell::MAZESIZE][MazeCell::MAZESIZE])
		:solved(false)
	{
		std::default_random_engine e(std::chrono::system_clock::now().time_since_epoch().count());
		std::bernoulli_distribution rnd(0.01);
		for (int _Y = 0; _Y < MazeCell::MAZESIZE; _Y++)
		{
			for (int _X = 0; _X < MazeCell::MAZESIZE; _X++)
			{
				if (sourceBytes[_X][_Y] == MazeCell::CELLSTATE::Start)
				{
					_startpos.X = _X;
					_startpos.Y = _Y;
				}
				if (sourceBytes[_X][_Y] == MazeCell::CELLSTATE::Finish)
				{
					_endPos.X = _X;
					_endPos.Y = _Y;
				}
				if (sourceBytes[_X][_Y] == MazeCell::CELLSTATE::Free)
				{
					if (rnd(e))
						solverBytes[_X][_Y] = MazeCell::CELLSTATE::FakeWall;
					else
						solverBytes[_X][_Y] = MazeCell::CELLSTATE::Free;
				}
				else
					solverBytes[_X][_Y] = sourceBytes[_X][ _Y];
			}
		}
	}

	Coord StartPos()
	{
		return _startpos;
	}

	Coord EndPos()
	{
		return _endPos;
	}

	int Steps()
	{
		int _steps = 0;
		for (int _Y = 0; _Y < MazeCell::MAZESIZE; _Y++)
		{
			for (int _X = 0; _X < MazeCell::MAZESIZE; _X++)
			{
				if (solverBytes[_X][_Y] == MazeCell::CELLSTATE::Valid)
					++_steps;
			}
		}
		return _steps;
	}

	bool isSolved()
	{
		if (solved)
			return solved;
		else
			return Solve(_startpos.X, _startpos.Y);
	}

private:
	bool solved;
	// Recursively solve each location, looking for open spaces, marking them as Valid along the way
	bool Solve(int _X, int _Y)
	{
		// The Finish cell will be reclassified as Valid, once a path has been found from Start to Finish
		if (solverBytes[_endPos.X][_endPos.Y] == MazeCell::CELLSTATE::Valid)
		{
			if (!solved)
				solved = true;
			return true;
		}

		if (solverBytes[_X + 1][_Y] == MazeCell::CELLSTATE::Free || solverBytes[_X + 1][_Y] == MazeCell::CELLSTATE::Start || solverBytes[_X + 1][_Y] == MazeCell::CELLSTATE::Finish)
		{
			solverBytes[_X + 1][_Y] = MazeCell::CELLSTATE::Valid;
			if (Solve(_X + 1, _Y))
				return true;
		}

		if (solverBytes[_X - 1][_Y] == MazeCell::CELLSTATE::Free || solverBytes[_X - 1][_Y] == MazeCell::CELLSTATE::Start || solverBytes[_X - 1][_Y] == MazeCell::CELLSTATE::Finish)
		{
			solverBytes[_X - 1][_Y] = MazeCell::CELLSTATE::Valid;
			if (Solve(_X - 1, _Y))
				return true;
		}

		if (solverBytes[_X][_Y + 1] == MazeCell::CELLSTATE::Free || solverBytes[_X][_Y + 1] == MazeCell::CELLSTATE::Start || solverBytes[_X][_Y + 1] == MazeCell::CELLSTATE::Finish)
		{
			solverBytes[_X][_Y + 1] = MazeCell::CELLSTATE::Valid;
			if (Solve(_X, _Y + 1))
				return true;
		}

		if (solverBytes[_X][_Y - 1] == MazeCell::CELLSTATE::Free || solverBytes[_X][_Y - 1] == MazeCell::CELLSTATE::Start || solverBytes[_X][_Y - 1] == MazeCell::CELLSTATE::Finish)
		{
			solverBytes[_X][_Y - 1] = MazeCell::CELLSTATE::Valid;
			if (Solve(_X, _Y - 1))
				return true;
		}

		return false;
	}
};

#endif