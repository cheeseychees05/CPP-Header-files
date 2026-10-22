#ifndef trio_hpp
#define trio_hpp
#include <vector>
#include <any>
namespace std{
    template <typename a, typename b, typename c>
    struct trio{
        a first;
        b second;
        c third;
    };
    template <typename t, typename u>
    using duo = pair<t, u>;
}
#endif