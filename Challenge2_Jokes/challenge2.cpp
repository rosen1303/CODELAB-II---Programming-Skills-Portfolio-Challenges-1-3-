#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <cctype>

// Read valid jokes from the supplied text file called "randomJokes.txt".
std::vector<std::string> loadJokes(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<std::string> jokes;
    std::string line;
  // This will Report an error if the file cannot be opened.
    if (!file)
    {
        std::cerr << "Could not open " << filename << '\n';
        return jokes;
    }
  // Read one joke at a time, with each joke on a separate line.
    while (std::getline(file, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        auto separator = line.find('?');
        if (separator != std::string::npos && separator + 1 < line.size())
            jokes.push_back(line);
    }
    return jokes;
}

int main()
{
    // Load the jokes once, before accepting requests.
    const auto jokes = loadJokes("randomJokes.txt");
    if (jokes.empty())
    {
        std::cerr << "No valid jokes available. Check the text file.\n";
        return 1;
    }

    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<std::size_t> choose(0, jokes.size() - 1);
    std::string input;
    // Set up a random generator and a valid range of joke positions.
    std::cout << "Welcome to Alexa's Joke Program!\n";
    std::cout << "Type Alexa, tell me a joke to request a joke.\n";
    std::cout << "Type quit to exit.\n";

    while (true)
    {
        std::cout << "\nYour request: ";
        if (!std::getline(std::cin, input))
            break;

        // Convert the request to lowercase.
        for (char& letter : input)
            letter = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));

        if (input == "quit")
            break;

        if (input != "alexa, tell me a joke")
        {
            std::cout << "Please type Alexa, tell me a joke or quit.\n";
            continue;
        }

        const std::string& joke = jokes[choose(generator)];
        auto separator = joke.find('?');

        std::cout << "Alexa: " << joke.substr(0, separator + 1) << '\n';
        std::cout << "Press Enter to reveal the punchline...";
        if (!std::getline(std::cin, input))
            break;

        std::cout << "Alexa: " << joke.substr(separator + 1) << '\n';
    }

    std::cout << "Alexa: Goodbye!\n";
    return 0;
}
