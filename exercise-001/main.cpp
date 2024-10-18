#include <fmt/chrono.h>
#include <fmt/format.h>

#include <vector> /* Provides std::vector*/
#include <random>

#include "CLI/CLI.hpp"
#include "config.h"

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    auto counter{20}; /* set a default of 20*/
    CLI::App app{PROJECT_NAME}; /* create an instance of an App with the variable name app*/
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE)); /* Add a command line option -c or 
        --count and fill the variable counter */
        app.add_option("-c,--count", counter, "How many items to insert"); // Adding option counter
        app.parse(argc, argv);

    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());
    fmt::print("Value of argc, {}!\n", argc);
    fmt::print("Value of argv[0], {}!\n", argv[0]);
    fmt::print("Value of argv[2], {}!\n", argv[2]); /* possible nullpointer exception at 3 */

    fmt::print("The value of counter {}!\n", counter);

    std::vector<unsigned int> values{23, 54, 66};
    fmt::print("Elements in values, {}!\n", values.size());
    values.push_back(42);
    values.push_back(13);
    values.push_back(7364);
    fmt::print("Elements in values, {}!\n", values.size());

    for(int i = 0; i < values.size();i++){
        fmt::print("Value of element {} in values: {}!\n", i, values[i]);
    }
    for(const unsigned int & i : values) { // access by const reference
        fmt::print("Value of element {} in values: {}!\n", i, values[i]);
    }

    fmt::print("Value of none existing element 10: {}!\n", values[10]);
    //fmt::print("Value of none existing element 10 element with at(): {}!\n", values.at(10));

    // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 1 and 100
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 100);
    int rand_value = uniform_dist(e1);

    fmt::print("Random number between 1 and 100: {}!\n", rand_value);

    std::vector<unsigned int> numbers;
    for(int i = 0; i< counter; i++) {
        numbers.push_back(uniform_dist(e1));
    }

    for(const unsigned int & value : numbers) { //range based for loop (const unsigned int reference with name 'value' to every member of the vector numbers)
        fmt::print("Value of element {} in numbers!\n", value);
    }

    return 0; /* exit gracefully*/
}
