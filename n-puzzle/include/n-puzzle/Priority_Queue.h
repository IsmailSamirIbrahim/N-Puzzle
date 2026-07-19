#pragma once

#include "n-puzzle/Exports.h"
#include "n-puzzle/N_Puzzle.h"

#include <cstddef>

namespace np
{
	constexpr static std::size_t MAX_SIZE = 1024;

	class Priority_Queue
	{
	public:
		Priority_Queue() = default;

		N_PUZZLE_EXPORT bool isEmpty();
		N_PUZZLE_EXPORT std::size_t size();
		N_PUZZLE_EXPORT Puzzle getMinimum();
		N_PUZZLE_EXPORT Puzzle extractMinimum();
		N_PUZZLE_EXPORT void insert(const Puzzle& puzzle);

	private:
		std::size_t left(std::size_t idx);
		std::size_t right(std::size_t idx);
		std::size_t parent(std::size_t idx);

		void minHeapify(std::size_t idx);
	private:
		Puzzle _data[MAX_SIZE];
		std::size_t _size{ static_cast<std::size_t>(-1) };
	};

} //end namespace np
