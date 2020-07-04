#pragma once

#include "n-puzzle/Exports.h"
#include "n-puzzle/N_Puzzle.h"

#include <vector>

namespace np
{
	constexpr static size_t MAX_SIZE = 1024;

	class Priority_Queue
	{
	public:
		Priority_Queue() = default;

		N_PUZZLE_EXPORT bool isEmpty();
		N_PUZZLE_EXPORT size_t size();
		N_PUZZLE_EXPORT Puzzle getMinimum();
		N_PUZZLE_EXPORT Puzzle extractMinimum();
		N_PUZZLE_EXPORT void insert(const Puzzle& puzzle);

	private:
		size_t left(size_t idx);
		size_t right(size_t idx);
		size_t parent(size_t idx);

		void minHeapify(size_t idx);
	private:
		Puzzle _data[MAX_SIZE];
		size_t _size{ -1 };
	};

} //end namespace np