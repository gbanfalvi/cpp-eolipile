//
// Created by Gabriel Banfalvi on 2018-01-01.
//

#ifndef PR_PLATFORMER_TESTLIBGEOMETRY_H
#define PR_PLATFORMER_TESTLIBGEOMETRY_H

#include <iostream>

// https://stackoverflow.com/a/27375675
template <typename Arg, typename... Args>
void printCout(Arg&& arg, Args&&... args) {
    std::cout << std::forward<Arg>(arg);
    using expander = int[];
    (void)expander{0, (void(std::cout << std::forward<Args>(args)),0)...};
    std::cout << std::endl;
}


#endif //PR_PLATFORMER_TESTLIBGEOMETRY_H
