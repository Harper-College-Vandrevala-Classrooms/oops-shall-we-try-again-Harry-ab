#include <iostream>
#include <string>
#include <vector>
#include <limits>

template <typename T>
T get_valid_input(const std::string &prompt, bool (*validation_func)(T), const std::string &error_message = "Invalid input, try again.") {
    T user_input;

    while (true) {
        std::cout << prompt;
        std::cin >> user_input;

        
        if (std::cin.good() && validation_func(user_input)) {
            return user_input;
        }

        // Print error message if input is invalid
        std::cout << error_message << std::endl;

        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string get_valid_input(const std::string &prompt, bool (*validation_func)(const std::string&), const std::string &error_message = "Invalid input, try again.") {
    std::string user_input;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, user_input);

        if (validation_func(user_input)) {
            return user_input;
        }

        // Print error message if input is invalid
        std::cout << error_message << std::endl;
    }
}

// Validation function for non-negative numbers
bool is_non_negative(int value) {
    return value >= 0;
}

// Validation function for a range between -1 and +1 (for correlation coefficient)
bool is_valid_correlation(double value) {
    return value >= -1.0 && value <= 1.0;
}

bool is_valid_choice(const std::string &value) {
    std::vector<std::string> valid_choices = {"A", "B", "C"};
    return std::find(valid_choices.begin(), valid_choices.end(), value) != valid_choices.end();
}

int main() {
    int age = get_valid_input<int>("Enter your age: ", is_non_negative, "Age must be a non-negative number.");
    std::cout << "You entered age: " << age << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //Asking for a correlation coefficient between -1 and +1
    double correlation = get_valid_input<double>("Enter a correlation coefficient (-1 to +1): ", is_valid_correlation, 
                                                 "Value must be between -1 and +1.");
    std::cout << "You entered correlation coefficient: " << correlation << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string choice = get_valid_input("Choose A, B, or C: ", is_valid_choice, 
                                         "Please choose a valid option: A, B, or C.");
    std::cout << "You selected: " << choice << std::endl;

    return 0;
}