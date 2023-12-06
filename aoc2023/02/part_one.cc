module;

#include <algorithm>
#include <charconv>
#include <numeric>
#include <ranges>
#include <string_view>

using namespace std::literals;
namespace ranges = std::ranges;

export module part_one;

export namespace part_one {

struct Balls {
    int red{};
    int green{};
    int blue{};

    Balls operator+(const Balls &rhs) {
        red += rhs.red;
        green += rhs.green;
        blue += rhs.blue;
        return *this;
    }
};

int64_t calculate_games(std::string_view in) {

    auto count_balls = [&](auto &&balls) {
        std::string_view in{balls};

        Balls counter{};

        for (auto color : {"red"sv, "green"sv, "blue"sv}) {
            if (in.npos == in.find(color)) {
                continue;
            }

            int ball_count{};
            std::from_chars(in.data(), in.end(), ball_count);

            if (color == "red"sv) {
                counter.red += ball_count;
            } else if (color == "green"sv) {
                counter.green += ball_count;
            } else if (color == "blue"sv) {
                counter.blue += ball_count;
            }
        }

        return counter;
    };

    auto count_balls_in_sets = [&](auto &&set) {
        std::string_view in{set};
        auto balls = in | ranges::views::split(", "sv);
        Balls limit{12, 13, 14};

        auto sum = std::transform_reduce(balls.begin(), balls.end(), Balls{},
                                         std::plus{}, count_balls);

        return sum.red <= limit.red && sum.green <= limit.green &&
               sum.blue <= limit.blue;
    };

    auto check_balls_in_sets = [&](auto &&game) {
        std::string_view in{game};
        int game_index{};

        if (in.empty()) {
            return game_index;
        }

        auto index{in.find_first_of(": "sv) + 2};
        std::from_chars(in.data(), in.data() + index, game_index);

        auto sets = in.substr(index) | ranges::views::split("; "sv);

        return ranges::all_of(sets, count_balls_in_sets) ? game_index : 0;
    };

    auto games = in | ranges::views::split("Game "sv);

    return std::transform_reduce(games.begin(), games.end(), 0, std::plus{},
                                 check_balls_in_sets);
}

} // namespace part_one
