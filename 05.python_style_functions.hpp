#ifndef python_style_functions_hpp
#define python_style_functions_hpp
#include <iostream>
#include <string>
#include <vector>
#include <any>
namespace python{
    void print(std::any input){
        if (const auto* value = std::any_cast<std::string>(&input)) {
            std::cout << *value;
        } else if (const auto* value = std::any_cast<const char*>(&input)) {
            std::cout << *value;
        } else if (const auto* value = std::any_cast<char>(&input)) {
            std::cout << *value;
        } else if (const auto* value = std::any_cast<bool>(&input)) {
            std::cout << (*value ? "true" : "false");
        } else if (const auto* value = std::any_cast<int>(&input)) {
            std::cout << *value;
        } else if (const auto* value = std::any_cast<long>(&input)) {
            std::cout << *value;
        } else if (const auto* value = std::any_cast<long long>(&input)) {
            std::cout << *value;
        } else if (const auto* value = std::any_cast<unsigned>(&input)) {
            std::cout << *value;
        } else if (const auto* value = std::any_cast<float>(&input)) {
            std::cout << *value;
        } else if (const auto* value = std::any_cast<double>(&input)) {
            std::cout << *value;
        } else {
            std::cout << "<unsupported std::any type>";
        }
        std::cout << std::endl;
    }
    std::string input(const std::string& prompt){
        std::cout << prompt;
        std::string user_input;
        std::getline(std::cin, user_input);
        return user_input;
    }
    using str = std::string;
    int len(std::vector<std::any> v){
        return v.size();
    }
    int len(const std::string& s){
        return s.length();
    }
    std::string upper(const std::string& s){
        std::string result = s;
        for (char& c : result) {
            c = std::toupper(c);
        }
        return result;
    }
    std::string lower(const std::string& s){
        std::string result = s;
        for (char& c : result) {
            c = std::tolower(c);
        }
        return result;
    }
    std::string capitalize(const std::string& s){
        if (s.empty()) return s;
        std::string result = s;
        result[0] = std::toupper(result[0]);
        for (size_t i = 1; i < result.length(); ++i) {
            result[i] = std::tolower(result[i]);
        }
        return result;
    }
    std::string title(const std::string& s){
        std::string result = s;
        bool new_word = true;
        for (char& c : result) {
            if (std::isspace(c)) {
                new_word = true;
            } else if (new_word) {
                c = std::toupper(c);
                new_word = false;
            } else {
                c = std::tolower(c);
            }
        }
        return result;
    }
}
#endif

