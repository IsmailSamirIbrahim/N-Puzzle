#pragma once

#include "n-puzzle/Exports.h"

#include <string>
#include <vector>
#include <initializer_list>
#include <utility>

namespace np
{
	constexpr size_t WIDTH  = 3;
	constexpr size_t HEIGHT = 3;

	enum class Empty_Pos_Kind : uint8_t
	{
		NONE,
		CORNER,
		CENTER,
		EDGE
	};

	enum class Direction : uint8_t
	{
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	class Puzzle
	{
	public:

		N_PUZZLE_EXPORT Puzzle() = default;
		N_PUZZLE_EXPORT Puzzle(const std::vector<std::vector<size_t>>& fPuzzle);
		N_PUZZLE_EXPORT Puzzle(const Puzzle& rhs);
		N_PUZZLE_EXPORT Puzzle& operator=(const Puzzle& rhs);
		N_PUZZLE_EXPORT bool operator==(const Puzzle& rhs);
		N_PUZZLE_EXPORT bool operator>(const Puzzle& rhs);
		N_PUZZLE_EXPORT bool operator<(const Puzzle& rhs);

	private:
		std::string puzzleToString();
		Empty_Pos_Kind emptyPosKind();
		std::pair<size_t, size_t> emptyPos();
		size_t calculateHammingDistance();
		bool movmentIsValid(Direction direction);
		bool isGoal();
		Puzzle move(Direction direction);
	private:
		size_t _data[WIDTH][HEIGHT];
		std::string _hashValue;
		Empty_Pos_Kind _emptyPosKind;
		size_t _emptyI, _emptyJ;
		size_t _fVal, _gVal, _hVal;

	};
} // end namespace np