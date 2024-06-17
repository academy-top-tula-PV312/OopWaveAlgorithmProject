#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iomanip>

struct Cell;

using Map = std::vector<std::vector<int>>;
using Path = std::vector<Cell>;
using Fronts = std::array<std::vector<Cell>, 2>;

enum CellType
{
	Start = 0,
	Finish = -3,
	Wall = -2,
	Space = -1
};

struct Cell
{
	int Row;
	int Column;

	friend bool operator==(const Cell& cell1, const Cell& cell2)
	{
		return (cell1.Row == cell2.Row && cell1.Column == cell2.Column);
	}
};

const std::vector<Cell> Offset{ {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

class WaveAlgorithm
{
	Map map;
	Path path;

	Cell start;
	Cell finish;
public:
	const Map& GetMap();
	const Path& GetPath();

	bool MapFromFile(std::string fileName);
	bool MakeWaves();
	void MakePath();

	void Show();
};

