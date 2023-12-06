#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

// parse string, concatenate first and last digit of input
auto concatenate_first_and_last_digit(std::string &input) -> std::string {
    std::regex pattern("(?=((one)|(two)|(three)|(four)|(five)|(six)|(seven)|("
                       "eight)|(nine)|(\\d)))");

    auto numbers_begin =
        std::sregex_iterator(input.begin(), input.end(), pattern);
    auto numbers_end = std::sregex_iterator();

    std::string first_number{};
    std::string second_number{};

    std::smatch first_match = *numbers_begin;
    first_number = first_match.str(1);
    auto count = std::distance(numbers_begin, numbers_end);

    for (int i = 0; i < count - 1; ++i) {
        numbers_begin++;
    }

    std::smatch second_match = *numbers_begin;
    second_number = second_match.str(1);

    return (first_number.size() > 1 ? mapped_strings.at(first_number)
                                    : first_number) +
           (second_number.size() > 1 ? mapped_strings.at(second_number)
                                     : second_number);
}

// input data
std::vector<std::string> in{
    "two1nine",         "eightwothree", "abcone2threexyz", "xtwone3four",
    "4nineeightseven2", "zoneight234",  "7pqrstsixteen"};

auto main() -> int {
    auto sum = std::transform_reduce(
        in.begin(), in.end(), 0, std::plus{}, [](std::string &line) {
            return stoi(concatenate_first_and_last_digit(line));
        });

    std::cout << "sum: " << sum;

    return 0;
}