#ifndef menutemp
#define menutemp

#include <iostream>
#include <vector>
#include <string>

namespace menu{
    using basic = std::vector<std::string>;
    using with_ingredients = std::vector<std::pair<std::string, std::vector<std::string>>>; 
    namespace make{
        int basic(std::vector<std::string>& menu, const std::string& Title = "Menu", const std::string& Custom_choose = "Enter choice: ")
        {
            std::cout << Title << std::endl;
            int i = 1;
            for(const std::string& menuchoice : menu)
            {
                std::cout << i << ". " << menuchoice << std::endl;
                i++;
            }
            std::cout << Custom_choose;
            int choice;
            std::cin >> choice;
            return choice;
        }
        int with_ingredients(std::vector<std::pair<std::string, std::vector<std::string>>>& menu, const std::string& Title = "Menu", const std::string& Custom_choose = "Enter choice: ")
        {
            std::cout << Title << std::endl;
            int i = 1;
                for(const std::pair<std::string, std::vector<std::string>>& item : menu)
                {
                    std::cout << i << ". " << item.first << " (";
                    int j = 0;
                    for(const std::string& ingredient : item.second)
                    {
                    std::cout << ingredient;
                    if(j == item.second.size() - 1)
                    {
                        continue;
                    }
                    std::cout << ", ";
                    j++;
                }
                std::cout << ')' << '\n';
                i++;
            }
            std::cout << Custom_choose;
            int choice;
            std::cin >> choice;
            return choice;
        }
    }
    namespace title_template{
        std::string a = "Actions";
        std::string b = "What do you do?";
    }
}

#endif