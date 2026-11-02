#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>
#include <stdexcept>

// Ask for a valid distance in miles.
double getDistance()
{
    std::string input;
    double distance;
    char extra;

    while (true)
    {
        std::cout << "Enter distance travelled in miles: ";
        if (!std::getline(std::cin, input))
            throw std::runtime_error("Input ended.");
        std::istringstream stream(input);
        if (stream >> distance && !(stream >> extra)
            && std::isfinite(distance) && distance >= 0)
            return distance;
        std::cout << "Please enter a number of zero or more.\n";
    }
}

// Return 1 for petrol or 2 for diesel.
int getFuelType()
{
    std::string input;
    while (true)
    {
        std::cout << "Select fuel type (1 = Petrol, 2 = Diesel): ";
        if (!std::getline(std::cin, input))
            throw std::runtime_error("Input ended.");
        if (input == "1" || input == "2")
            return input == "1" ? 1 : 2;
        std::cout << "Please enter 1 or 2.\n";
    }
}

// Use the fuel consumption and emission factors from the brief.
double calculateEmissions(double distance, int fuelType)
{
    const double litresPer100Miles = 9.66;
    const double emissionFactor = (fuelType == 1) ? 2.31 : 2.68;
    return (distance / 100.0) * litresPer100Miles * emissionFactor;
}

int main()
{
    try
    {
        std::cout << "Car Journey CO2 Calculator\n";
        double distance = getDistance();
        int fuelType = getFuelType();
        double emissions = calculateEmissions(distance, fuelType);
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Estimated CO2 emissions: " << emissions << " kg\n";
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}