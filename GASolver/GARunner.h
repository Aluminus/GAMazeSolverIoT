#ifndef GARUNNER_H
#define GARUNNER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "GASolver.h"
#include <functional>
#include <algorithm>

class GARunner
{
public:
	MazeCell::CELLSTATE sourceMaze[MazeCell::MAZESIZE][MazeCell::MAZESIZE];
	GASolver::Coord _startPos;
	GASolver::Coord _endPos;
	bool bRun = false;
	int epochs = 0, m_maxEpochs = 0, m_maxSolvers = 0;
	std::vector<GASolver> gaList;
	int gaCursor = 0;
	typedef std::function<bool()> ShouldRun;
	ShouldRun ShouldRunCallback;

	GARunner(int maxEpochs, int maxSolvers)
		:m_maxEpochs(maxEpochs), m_maxSolvers(maxSolvers)
	{
		ShouldRunCallback = [](){return true; };
	}

	// Initialize solver pool
	void InitializeSolvers()
	{
		epochs = 0;

		for (int _Y = 0; _Y < MazeCell::MAZESIZE; _Y++)
		{
			for (int _X = 0; _X < MazeCell::MAZESIZE; _X++)
			{
				if (sourceMaze[_X][_Y] == MazeCell::CELLSTATE::Start)
				{
					_startPos.X = _X;
					_startPos.Y = _Y;
				}
				if (sourceMaze[_X][_Y] == MazeCell::CELLSTATE::Finish)
				{
					_endPos.X = _X;
					_endPos.Y = _Y;
				}
			}
		}

		for (int ii = 0; ii < 10; ii++)
		{
			GASolver g = GASolver(sourceMaze);
			gaList.push_back(g);
		}

		gaCursor = 0;
	}

	void UpdateWalls()
	{
		for (auto& solver : gaList)
		{
			for (int _Y = 0; _Y < MazeCell::MAZESIZE; _Y++)
			{
				for (int _X = 0; _X < MazeCell::MAZESIZE; _X++)
				{
					if (sourceMaze[_X][_Y] == MazeCell::CELLSTATE::Wall && solver.solverBytes[_X][_Y] == MazeCell::CELLSTATE::Free)
						solver.solverBytes[_X][_Y] = MazeCell::CELLSTATE::Wall;
					else if (sourceMaze[_X][_Y] == MazeCell::CELLSTATE::Free && solver.solverBytes[_X][_Y] == MazeCell::CELLSTATE::Wall)
						solver.solverBytes[_X][_Y] = MazeCell::CELLSTATE::Free;
				}
			}
		}
	}

	void NextSolver()
	{
		if (gaCursor < gaList.size() - 1)
			++gaCursor;
		else
			gaCursor = 0;
	}

	void PrevSolver()
	{
		if (gaCursor > 0)
			--gaCursor;
		else
			gaCursor = gaList.size() - 1;
	}

	void LoadString(const _TCHAR* buffer)
	{
		std::wstringstream ss(buffer);
		_TCHAR coord1[256];
		_TCHAR coord2[256];
		_TCHAR coord3[256];
		int _X = 0, _Y = 0, _S = 0;
		for (int i = 0; i < MazeCell::MAZESIZE*MazeCell::MAZESIZE; i++)
		{
			ss.getline((_TCHAR*)&coord1, 256, ';');
			ss.getline((_TCHAR*)&coord2, 256, ';');
			ss.getline((_TCHAR*)&coord3, 256, '\r');

			std::wstringstream convert1(coord1);
			convert1 >> _X;
			std::wstringstream convert2(coord2);
			convert2 >> _Y;
			std::wstringstream convert3(coord3);
			convert3 >> _S;

			sourceMaze[_X][_Y] = (MazeCell::CELLSTATE)_S;
		}
	}

	void Load(const _TCHAR* filename)
	{
		std::ifstream ifs{ filename, std::ifstream::in | std::ifstream::binary };
		std::streamsize length = 0;
		char* buffer = nullptr;

		if (ifs)
		{
			// get length of file:
			ifs.seekg(0, ifs.end);
			length = ifs.tellg();
			ifs.seekg(0, ifs.beg);

			// allocate memory (assume less than 2GB):
			buffer = new char[(unsigned int)length];

			// read data as a block:
			ifs.read(buffer, length);
			if (!ifs.good()) // Problem officer?
			{
				if (ifs.eof())
					std::cout << "End of file before expected end";
				if (ifs.fail())
					std::cout << "Logical failure on input file stream";
				if (ifs.bad())
					std::cout << "Read failure on input file stream";
				return;
			}
			std::cout << "Stream is good, processing " << filename << "..." << std::endl;
			std::string file = buffer;
			std::stringstream ss(file);

			std::string coord1, coord2, coord3;
			int _X = 0, _Y = 0, _S = 0;
			for (int i = 0; i < MazeCell::MAZESIZE*MazeCell::MAZESIZE; i++)
			{
				std::getline(ss, coord1, ';');
				std::getline(ss, coord2, ';');
				std::getline(ss, coord3, '\r');

				std::stringstream convert1(coord1);
				convert1 >> _X;
				std::stringstream convert2(coord2);
				convert2 >> _Y;
				std::stringstream convert3(coord3);
				convert3 >> _S;

				sourceMaze[_X][_Y] = (MazeCell::CELLSTATE)_S;
			}
		}
	}

	void Print(int solverIndex)
	{
		for (int _Y = 0; _Y < MazeCell::MAZESIZE; _Y++)
		{
			for (int _X = 0; _X < MazeCell::MAZESIZE; _X++)
			{
				int val = 0;
				if (solverIndex < 0)
					val = (int)sourceMaze[_X][_Y];
				else
					val = (int)gaList[solverIndex].solverBytes[_X][_Y];
				if (val < 0)
				{
					std::cout << "Horribly broken, printing cancelled" << std::endl;
				}
				else
					std::cout << val;
			}
			std::cout << std::endl;
		}
	}

	void Run()
	{
		bRun = true;
		while (ShouldRunCallback())
		{
			RunEpoch();
		}
	}

	void RunEpoch()
	{
		// Sorting before crossing ensures that the two best solvers are crossed with each other
		Sort();

		// Remove the two worst solvers from the list
		if (gaList.size() > 2)
		{
			auto worst = --gaList.end();
			if (!worst->isSolved() || gaList.size() == m_maxSolvers)
				gaList.erase(worst);
			worst = --gaList.end();
			if (!worst->isSolved() || gaList.size() == m_maxSolvers)
				gaList.erase(worst);
		}

		// Cross the two best solvers with each other and put the offspring back in the list
		std::vector<GASolver> bestMazes;
		for (auto& ga : gaList)
		{
			if (ga.isSolved())
			{
				int steps = ga.Steps();
				bestMazes.push_back(ga);
			}
		}

		if (bestMazes.size() >= 2 && gaList.size() < m_maxSolvers)
		{
			GASolver sample01 = GASolver(bestMazes[0].solverBytes, bestMazes[1].solverBytes, _startPos, _endPos);
			GASolver sample02 = GASolver(bestMazes[1].solverBytes, bestMazes[0].solverBytes, _startPos, _endPos);
			gaList.push_back(sample01);
			gaList.push_back(sample02);
		}

		epochs += 1;
		if (epochs == m_maxEpochs)
		{
			Print(0);
			ShouldRunCallback = [](){return false; };
		}
	}

	void Sort()
	{
		std::sort(std::begin(gaList), std::end(gaList), [&](GASolver& left, GASolver& right) ->bool
		{
			if (left.isSolved() && right.isSolved())
				return left.Steps() < right.Steps(); 
			else if (left.isSolved())
				return right.Steps() < left.Steps();
		});
	}

	void Reset()
	{
		gaList.clear();
	}
};

#endif