#include <iostream>
#include <vector>
#include <string>

int main() {
    // Create an empty vector of strings
    std::vector<std::string> items;

    // Append items to the vector using push_back
    items.push_back("eggs");
    items.push_back("milk");
    items.push_back("sugar");
    items.push_back("chocolate");
    items.push_back("flour");

    // Print the vector
    for (const auto& item : items) {
        std::cout << item << std::endl;
    }

    return 0;
}
