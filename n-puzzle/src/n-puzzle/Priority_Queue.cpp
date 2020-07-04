#include "n-puzzle/Priority_Queue.h"

namespace np
{
	bool Priority_Queue::isEmpty()
	{
		return this->_size == -1;
	}

	size_t Priority_Queue::size()
	{
		return this->_size;
	}

	Puzzle Priority_Queue::getMinimum()
	{
		return this->_data[0];
	}

	Puzzle Priority_Queue::extractMinimum()
	{
		if (this->_size == -1)
			return Puzzle{};

		Puzzle min = this->_data[0];

		this->_data.erase(this->_data.begin());
		--this->_size;

		this->minHeapify(0);

		return min;
	}

	void Priority_Queue::insert(const Puzzle& puzzle)
	{
		this->_data[this->_size] = val;
		++this->_size;

		size_t idx = this->_size - 1;

		while (idx > 0 && this->_data[this->parent(idx)] > this->_data[idx])
		{
			std::swap(this->_data[this->parent(idx)], this->_data[idx]);
			idx = this->parent(idx);
		}
	}

	size_t Priority_Queue::left(size_t idx)
	{
		return idx * 2;
	}

	size_t Priority_Queue::right(size_t idx)
	{
		return (idx * 2) + 1;
	}

	size_t Priority_Queue::parent(size_t idx)
	{
		return floor(idx / 2);
	}

	void Priority_Queue::minHeapify(size_t idx)
	{
		size_t l = left(idx);
		size_t r = left(idx);
		size_t smallest = idx;

		if (l <= this->_size && (this->_data[l] < this->_data[idx]))
			smallest = l;
		if (r <= this->_size && (this->_data[r] < this->_data[idx]))
			smallest = r;

		if (smallest != idx) {
			swap(this->_data[idx], this->_data[smallest]);
			minHeapify(smallest);
		}
	}

} //end namespace np