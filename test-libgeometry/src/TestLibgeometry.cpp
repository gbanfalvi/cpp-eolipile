//
//  main.cpp
//  lib-geometry-test
//
//  Created by Gabriel Banfalvi on 09/02/16.
//  Copyright © 2016 clueless. All rights reserved.
//

#include <iostream>
#include <assert.h>

#include "Geometry.hpp"

int main(int argc, const char * argv[]) {

    Point p(2, 3);
    Size s(9, 3);

    Rect r(p, s);

    std::cout << "top left " << r.topLeft().x << " " << r.topLeft().y << std::endl;

    r.rotation = 0.5;

    std::cout << "top left " << r.topLeft().x << " " << r.topLeft().y << std::endl;

    std::cout << "Testing" << std::endl;
    return 0;

}
