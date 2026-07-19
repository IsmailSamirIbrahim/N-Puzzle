#include "n-puzzle/N_Puzzle.h"

#include <utility>

namespace np
{
	Puzzle::Puzzle(const std::vector<std::vector<std::size_t>>& fPuzzle)
	{
		for (std::size_t i = 0; i < HEIGHT; ++i)
			for (std::size_t j = 0; j < WIDTH; ++j)
				this->_data[i][j] = fPuzzle[i][j];

		this->_hashValue = puzzleToString();
		this->_emptyPosKind = emptyPosKind();
		auto pair = emptyPos();
		this->_emptyI = pair.first;
		this->_emptyJ = pair.second;
		this->_gVal = 0;
		this->_hVal = calculateHammingDistance();
		this->_fVal = this->_gVal + this->_hVal;
	}

	Puzzle::Puzzle(const Puzzle& rhs)
	{
		for (std::size_t i = 0; i < HEIGHT; ++i)
			for (std::size_t j = 0; j < WIDTH; ++j)
				this->_data[i][j] = rhs._data[i][j];

		this->_hashValue = rhs._hashValue;
		this->_emptyPosKind = rhs._emptyPosKind;
		this->_emptyI = rhs._emptyI;
		this->_emptyJ = rhs._emptyJ;
		this->_gVal = rhs._gVal;
		this->_hVal = rhs._hVal;
		this->_fVal = rhs._fVal;
	}

	Puzzle& Puzzle::operator=(const Puzzle& rhs)
	{
		for (std::size_t i = 0; i < HEIGHT; ++i)
			for (std::size_t j = 0; j < WIDTH; ++j)
				this->_data[i][j] = rhs._data[i][j];

		this->_hashValue = rhs._hashValue;
		this->_emptyPosKind = rhs._emptyPosKind;
		this->_emptyI = rhs._emptyI;
		this->_emptyJ = rhs._emptyJ;
		this->_gVal = rhs._gVal;
		this->_hVal = rhs._hVal;
		this->_fVal = rhs._fVal;

		return *this;
	}

	bool Puzzle::operator==(const Puzzle& rhs)
	{
		return this->_hashValue == rhs._hashValue;
	}

	bool Puzzle::operator>(const Puzzle& rhs)
	{
		return this->_fVal > rhs._fVal;
	}

	bool Puzzle::operator<(const Puzzle& rhs)
	{
		return this->_fVal < rhs._fVal;
	}


	// private functions

	std::string Puzzle::puzzleToString()
	{
		std::string result = "";
		for (std::size_t i = 0; i < HEIGHT; ++i)
			for (std::size_t j = 0; j < WIDTH; ++j)
				result += std::to_string(this->_data[i][j]);
		
		return result;
	}

	Empty_Pos_Kind Puzzle::emptyPosKind()
	{
		Empty_Pos_Kind result = Empty_Pos_Kind::NONE;

		for (std::size_t i = 0; i < HEIGHT; ++i)
		{
			for (std::size_t j = 0; j < WIDTH; ++j)
			{
				if (this->_data[i][j] == 0)
				{
					if ((i == 0 || i == HEIGHT - 1) && (j == 0 || j == WIDTH - 1))
					{
						result = Empty_Pos_Kind::CORNER;
						goto end;
					}
					else if (i == HEIGHT / 2 && j == WIDTH / 2)
					{
						result = Empty_Pos_Kind::CENTER;
						goto end;
					}
					else
					{
						result = Empty_Pos_Kind::EDGE;
						goto end;
					}
				}
			}
		}

	end:
		return result;
	}

	std::pair<std::size_t, std::size_t> Puzzle::emptyPos()
	{
		std::pair<std::size_t, std::size_t> result{};

		for (std::size_t i = 0; i < HEIGHT; ++i)
		{
			for (std::size_t j = 0; j < WIDTH; ++j)
			{
				if (this->_data[i][j] == 0)
				{
					result.first = i;
					result.second = j;
					goto end;
				}
			}
		}

	end:
		return result;
	}

	std::size_t Puzzle::calculateHammingDistance()
	{
		std::size_t result = 0;

		for (std::size_t i = 0; i < HEIGHT; ++i)
		{
			for (std::size_t j = 0; j < WIDTH; ++j)
			{
				if (this->_data[i][j] != 0 && this->_data[i][j] != i * WIDTH + j + 1)
					++result;
			}
		}

		return result;
	}

	bool Puzzle::movmentIsValid(Direction direction)
	{
		if (this->_emptyPosKind == Empty_Pos_Kind::CENTER)
		{
			return true;
		}
		else if (this->_emptyPosKind == Empty_Pos_Kind::CORNER)
		{
			if (this->_emptyI == 0 && this->_emptyJ == 0 && (direction == Direction::RIGHT || direction == Direction::DOWN))
				return true;
			else if (this->_emptyI == HEIGHT - 1 && this->_emptyJ == 0 && (direction == Direction::RIGHT || direction == Direction::UP))
				return true;
			else if (this->_emptyI == 0 && this->_emptyJ == WIDTH - 1 && (direction == Direction::LEFT || direction == Direction::DOWN))
				return true;
			else if (this->_emptyI == HEIGHT - 1 && this->_emptyJ == WIDTH - 1 && (direction == Direction::LEFT || direction == Direction::UP))
				return true;
		}
		else
		{
			if (this->_emptyI == 0 && (direction == Direction::LEFT || direction == Direction::RIGHT || direction == Direction::DOWN))
				return true;
			else if (this->_emptyJ == 0 && (direction == Direction::UP || direction == Direction::DOWN || direction == Direction::RIGHT))
				return true;
			else if (this->_emptyI == HEIGHT - 1 && (direction == Direction::LEFT || direction == Direction::RIGHT || direction == Direction::UP))
				return true;
			else if (this->_emptyJ == WIDTH - 1 && (direction == Direction::UP || direction == Direction::DOWN || direction == Direction::LEFT))
				return true;
		}
		return false;
	}

	bool Puzzle::isGoal()
	{
		for (std::size_t i = 0; i < HEIGHT; ++i)
		{
			for (std::size_t j = 0; j < WIDTH; ++j)
			{
				if (this->_data[i][j] != 0 && this->_data[i][j] != i * WIDTH + j + 1)
					return false;
			}
		}
		return true;
	}

	Puzzle Puzzle::move(Direction direction)
	{
		Puzzle obj = *this;

		if (movmentIsValid(direction))
		{
			if (direction == Direction::UP)
			{
				std::swap(obj._data[obj._emptyI][obj._emptyJ], obj._data[obj._emptyI - 1][obj._emptyJ]);
				--obj._emptyI;
				++obj._gVal;
				obj._hashValue = obj.puzzleToString();
			}
			else if (direction == Direction::DOWN)
			{
				std::swap(obj._data[obj._emptyI][obj._emptyJ], obj._data[obj._emptyI + 1][obj._emptyJ]);
				++obj._emptyI;
				++obj._gVal;
				obj._hashValue = obj.puzzleToString();
			}
			else if (direction == Direction::LEFT)
			{
				std::swap(obj._data[obj._emptyI][obj._emptyJ], obj._data[obj._emptyI][obj._emptyJ - 1]);
				--obj._emptyJ;
				++obj._gVal;
				obj._hashValue = obj.puzzleToString();
			}
			else if (direction == Direction::RIGHT)
			{
				std::swap(obj._data[obj._emptyI][obj._emptyJ], obj._data[obj._emptyI][obj._emptyJ + 1]);
				++obj._emptyJ;
				++obj._gVal;
				obj._hashValue = obj.puzzleToString();
			}
		}
		return obj;
	}

} // end namespace np
