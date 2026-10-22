#ifndef dex_hpp
#define dex_hpp

#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
using dexkeeper = std::vector<std::pair<std::string, std::pair<int, int>>>;
class dex;

namespace add{
    void dexchar(dex& target, const std::string& name, int hp, int atk);
    void hp(dex& target, const std::string& name, int hp);
    void atk(dex& target, const std::string& name, int atk);
}
namespace subtract{
    void dexchar(dex& target, const std::string& name);
    void hp(dex& target, const std::string& name, int hp);
    void atk(dex& target, const std::string& name, int atk);
}
namespace multiply{
    void hp(dex& target, const std::string& name, int hp);
    void atk(dex& target, const std::string& name, int atk);
}
namespace change{
    void name(dex& target, const std::string& name, const std::string& newname);
    void hp(dex& target, const std::string& name, int hp);
    void atk(dex& target, const std::string& name, int atk);
}
namespace show{
    std::pair<std::string, std::pair<int, int>> dexchar(dex& target, const std::string& type, int index = 0, const std::string& name = "");
    std::vector<std::pair<std::string, std::pair<int, int>>> dexchars(dex& target);
}
int totaldexchars(dex& target);
class dex{
protected:
    dexholder chars;

    friend void add::dexchar(dex&, const std::string&, int, int);
    friend void add::hp(dex&, const std::string&, int);
    friend void add::atk(dex&, const std::string&, int);

    friend void subtract::dexchar(dex&, const std::string&);
    friend void subtract::hp(dex&, const std::string&, int);
    friend void subtract::atk(dex&, const std::string&, int);
    
    friend void multiply::hp(dex&, const std::string&, int);
    friend void multiply::atk(dex&, const std::string&, int);

    friend void change::name(dex&, const std::string&, const std::string&);
    friend void change::hp(dex&, const std::string&, int);
    friend void change::atk(dex&, const std::string&, int);
    
    friend std::pair<std::string, std::pair<int, int>> show::dexchar(dex&, const std::string&, int, const std::string&);
    friend std::vector<std::pair<std::string, std::pair<int, int>>> show::dexchars(dex&);

    friend int totaldexchars(dex&);
};
namespace add{
    inline void dexchar(dex& target, const std::string& name, int hp, int atk){
        target.chars.push_back({name, {hp, atk}});
    }
    inline void hp(dex& target, const std::string& name, int hp){
        target.chars[std::find_if(target.chars.begin(), target.chars.end(), [&](const auto& p){ return p.first == name; }) - target.chars.begin()].second.first += hp;
    }
    inline void atk(dex& target, const std::string& name, int atk){
        target.chars[std::find_if(target.chars.begin(), target.chars.end(), [&](const auto& p){ return p.first == name; }) - target.chars.begin()].second.second += atk;
    }
}
namespace subtract{
    inline void dexchar(dex& target, const std::string& name){
        target.chars.erase(
            std::remove_if(target.chars.begin(), target.chars.end(),
                [&](const auto& p){ return p.first == name; }),
            target.chars.end());
    }
    inline void hp(dex& target, const std::string& name, int hp){
        target.chars[std::find_if(target.chars.begin(), target.chars.end(), [&](const auto& p){ return p.first == name; }) - target.chars.begin()].second.first -= hp;
    }
    inline void atk(dex& target, const std::string& name, int atk){
        target.chars[std::find_if(target.chars.begin(), target.chars.end(), [&](const auto& p){ return p.first == name; }) - target.chars.begin()].second.second -= atk;
    }
}
namespace multiply{
    inline void hp(dex& target, const std::string& name, int hp){
        target.chars[std::find_if(target.chars.begin(), target.chars.end(), [&](const auto& p){ return p.first == name; }) - target.chars.begin()].second.first *= hp;
    }
    inline void atk(dex& target, const std::string& name, int atk){
        target.chars[std::find_if(target.chars.begin(), target.chars.end(), [&](const auto& p){ return p.first == name; }) - target.chars.begin()].second.second *= atk;
    }
}
namespace change{
    inline void name(dex& target, const std::string& name, const std::string& newname){
        target.chars[std::find_if(target.chars.begin(), target.chars.end(), [&](const auto& p){ return p.first == name; }) - target.chars.begin()].first = newname;
    }
    inline void hp(dex& target, const std::string& name, int hp){
        target.chars[std::find_if(target.chars.begin(), target.chars.end(), [&](const auto& p){ return p.first == name; }) - target.chars.begin()].second.first = hp;
    }
    inline void atk(dex& target, const std::string& name, int atk){
        target.chars[std::find_if(target.chars.begin(), target.chars.end(), [&](const auto& p){ return p.first == name; }) - target.chars.begin()].second.second = atk;
    }
}
namespace show{
    inline std::pair<std::string, std::pair<int, int>> dexchar(dex& target, const std::string& type, int index, const std::string& name){
        if(type == "index"){
            return target.chars[index];
        }
        else if(type == "name"){
            return target.chars[std::find_if(target.chars.begin(), target.chars.end(), [&](const auto& p){ return p.first == name; }) - target.chars.begin()];
        }
        throw std::invalid_argument("Invalid showtype");
    }
    inline std::vector<std::pair<std::string, std::pair<int, int>>> dexchars(dex& target){
        return target.chars;
    }
}
int totaldexchars(dex& target){
    target.chars.size()
}
#endif
