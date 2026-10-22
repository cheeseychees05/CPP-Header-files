#ifndef life_hpp
#define life_hpp
#include <string>
#include <vector>
namespace life{
    std::string personal_id_template;
    struct person{
        std::pair<std::string, std::string> name;
        int age = 0;
        std::string sex = "Other";
        std::string personal_id;  
    };
    using nickname = std::string;
    using people = std::vector<std::pair<nickname, person>>;
    std::string student_id_template;
    struct student{
        person info;
        std::string student_id;
        std::string school =  "Unknown";
        int grade_level;
    };
    struct worker{
        person info;
        std::string company;
        std::string type;
        std::string position;
    };
}
#endif