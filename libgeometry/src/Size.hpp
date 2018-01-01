//
//  Size.hpp
//  lib-geometry
//
//  Created by Gabriel Banfalvi on 09/02/16.
//
//

#ifndef Size_hpp
#define Size_hpp

#include <iostream>

struct Size {
    double width = 0;
    double height = 0;
    
    Size(double width, double height):width(width), height(height){};
    Size():width(0), height(0){};
    Size(const Size& size):width(size.width), height(size.height){};
};

std::ostream &operator<< (std::ostream &os, Size const &size);

#endif /* Size_hpp */
