#include <cassert>
#include "laser.hpp"

auto main() -> int {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    assert(input);
    assert(output);

    vector<node> path;
    output << laser(input, back_inserter(path));
    for (const auto &n : path) {
        output << endl << n;
    }

    input.close();
    output.close();
    return 0;
}