//
//  Size.cpp
//  lib-geometry
//
//  Created by Gabriel Banfalvi on 09/02/16.
//
//

#include "Size.hpp"

std::ostream &operator<< (std::ostream &os, Size const &size) {
    os << "Size <Width:" << size.width << " Height:" << size.height << ">";
    return os;
}