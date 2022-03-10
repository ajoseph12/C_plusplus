
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <string_view>

static bool containsWord(std::string_view str)
{
    return (str.find("nuts") != std::string_view::npos);
}

int main()
{
    const std::array<std::string_view, 4> arr = { "apple", "banana", "walnut", "lemon" };
    const auto found = { std::find_if(arr.begin(), arr.end(),
                                        [](std::string_view str)
                                        {
                                            return (str.find("nuts") != std::string_view::npos);
                                        }
    containsWord) };

    if (found == arr.end())
    {
        std::cout << "No nuts\n";
    }
    else
    {
        std::cout << "Found " << *found << "\n";
    }
    return 0;
}
