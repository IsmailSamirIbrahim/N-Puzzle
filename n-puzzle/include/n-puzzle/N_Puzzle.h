#pragma once

#include "n-puzzle/Exports.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace np
{
	constexpr std::size_t WIDTH  = 3;
	constexpr std::size_t HEIGHT = 3;

	enum class Empty_Pos_Kind : std::uint8_t
	{
		NONE,
		CORNER,
		CENTER,
		EDGE
	};

	enum class Direction : std::uint8_t
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
		N_PUZZLE_EXPORT Puzzle(const std::vector<std::vector<std::size_t>>& fPuzzle);
		N_PUZZLE_EXPORT Puzzle(const Puzzle& rhs);
		N_PUZZLE_EXPORT Puzzle& operator=(const Puzzle& rhs);
		N_PUZZLE_EXPORT bool operator==(const Puzzle& rhs);
		N_PUZZLE_EXPORT bool operator>(const Puzzle& rhs);
		N_PUZZLE_EXPORT bool operator<(const Puzzle& rhs);

	private:
		std::string puzzleToString();
		Empty_Pos_Kind emptyPosKind();
		std::pair<std::size_t, std::size_t> emptyPos();
		std::size_t calculateHammingDistance();
		bool movmentIsValid(Direction direction);
		bool isGoal();
		Puzzle move(Direction direction);
	private:
		std::size_t _data[WIDTH][HEIGHT];
		std::string _hashValue;
		Empty_Pos_Kind _emptyPosKind;
		std::size_t _emptyI, _emptyJ;
		std::size_t _fVal, _gVal, _hVal;

	};
} // end namespace np
