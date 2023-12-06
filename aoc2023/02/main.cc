#include <iostream>

import input;
import part_one;
// import part_two;

int main() {
  std::cout << "Sum of all valid games: "
            << part_one::calculate_games(input::day02) << '\n';
}
