#include <cstddef>
#include <iostream>
#include <vector>

#include <n-puzzle/N_Puzzle.h>

int main()
{
	std::vector<std::vector<std::size_t>> puzzle(3, std::vector<std::size_t>(3, 0));

	auto obj = np::Puzzle(puzzle);
	static_cast<void>(obj);

	std::cout << "Hello, World!" << std::endl;
	return 0;
}
