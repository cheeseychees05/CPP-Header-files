#ifndef stlplushpp
#define stlplushpp

#include <array>
#include <vector>
//#include <pair> (pair is in utility/vector)
#include <tuple>
#include "06.trio.hpp"

#include <list>
#include <initializer_list>
#include <forward_list>

#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <flat_set>
#include <flat_map>

#include <stack>
#include <queue>
#include <deque>

namespace stl{
    namespace container{
        template <typename a>
        using array = std::array<a>;
        template <typename a>
        using list = std::list<a>;
        template <typename a>
        using forward_list = std::forward_list<a>;
        template <typename a>
        using initializer_list = std::initializer_list<a>;
        template <typename a>
        using vector = std::vector<a>;
        template <typename a, typename b>
        using pair = std::pair<a, b>;
        template <typename a, typename b>
        using duo = std::duo<a, b>;
        template <typename a, typename b, typename c>
        using trio = std::trio<a, b, c>;
        template <typename... types>
        using tuple = std::tuple<types...>;
        template <typename a>
        using set = std::set<a>;
        template <typename a>
        using unordered_set = std::unordered_set<a>;
        template <typename a>
        using multiset = std::multiset<a>;
        template <typename a>
        using unordered_multiset = std::unordered_multiset<a>;
        template <typename a>
        using flat_set = std::flat_set<a>;
        template <typename a, typename b>
        using map = std::map<a, b>;
        template <typename a, typename b>
        using unordered_map = std::unordered_map<a, b>;
        template <typename a, typename b>
        using multimap = std::multimap<a, b>;
        template <typename a, typename b>
        using unordered_multimap = std::unordered_multimap<a, b>;
        template <typename a, typename b>
        using flat_map = std::flat_map<a, b>;
        template <typename a>
        using stack = std::stack<a>;
        template <typename a>
        using queue = std::queue<a>;
        template <typename a>
        using priority_queue = std::priority_queue<a>;
        template <typename a>
        using deque = std::deque<a>;
    }
}

#endif