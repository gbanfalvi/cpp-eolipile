//
// Created by Gabriel Banfalvi on 04/02/16.
//

#ifndef EOLIPILE_SIZE_H
#define EOLIPILE_SIZE_H

struct Size {
    double width = 0;
    double height = 0;

    Size(double width, double height):width(width), height(height){};
    Size():width(0), height(0){};
    Size(const Size& size):width(size.width), height(size.height){};
};

#endif //EOLIPILE_SIZE_H
