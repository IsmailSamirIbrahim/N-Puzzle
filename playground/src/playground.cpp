#include <iostream>

#include <n-puzzle/N_Puzzle.h>
#include <vector>

int main()
{
	std::vector<std::vector<size_t>> puzzle(3, std::vector<size_t>(3, 0));

	auto obj = np::Puzzle(puzzle);

	std::cout << "Hello, World!" << std::endl;
	return 0;
}