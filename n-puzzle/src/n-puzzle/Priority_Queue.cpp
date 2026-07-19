#include "n-puzzle/Priority_Queue.h"

#include <utility>

namespace np
{
	bool Priority_Queue::isEmpty()
	{
		return this->_size == static_cast<std::size_t>(-1);
	}

	std::size_t Priority_Queue::size()
	{
		return this->_size;
	}

	Puzzle Priority_Queue::getMinimum()
	{
		return this->_data[0];
	}

	Puzzle Priority_Queue::extractMinimum()
	{
		if (isEmpty())
			return Puzzle{};

		Puzzle min = this->_data[0];

		this->_data[0] = this->_data[this->_size];
		--this->_size;

		if (!isEmpty())
			this->minHeapify(0);

		return min;
	}

	void Priority_Queue::insert(const Puzzle& puzzle)
	{
		++this->_size;
		this->_data[this->_size] = puzzle;

		std::size_t idx = this->_size;

		while (idx > 0 && this->_data[this->parent(idx)] > this->_data[idx])
		{
			std::swap(this->_data[this->parent(idx)], this->_data[idx]);
			idx = this->parent(idx);
		}
	}

	std::size_t Priority_Queue::left(std::size_t idx)
	{
		return idx * 2;
	}

	std::size_t Priority_Queue::right(std::size_t idx)
	{
		return (idx * 2) + 1;
	}

	std::size_t Priority_Queue::parent(std::size_t idx)
	{
		return idx / 2;
	}

	void Priority_Queue::minHeapify(std::size_t idx)
	{
		std::size_t l = left(idx);
		std::size_t r = right(idx);
		std::size_t smallest = idx;

		if (l <= this->_size && (this->_data[l] < this->_data[idx]))
			smallest = l;
		if (r <= this->_size && (this->_data[r] < this->_data[idx]))
			smallest = r;

		if (smallest != idx) {
			std::swap(this->_data[idx], this->_data[smallest]);
			minHeapify(smallest);
		}
	}

} //end namespace np
