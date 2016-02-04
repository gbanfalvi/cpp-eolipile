//
// Created by Gabriel Banfalvi on 01/02/16.
//

#include "SpacehashTest.h"

int main() {

    println("Checking Approximate Equals");

    println("Checking Point");

    println("Checking Point - Constructors");

    println("Checking Point - Distance");

    println("Checking Size");

    println("Checking Size - Constructor");

    println("Checking Line");

    println("Checking Line - Constructors");

    println("Checking Line - Inverse");

    println("Checking Line - Normal");

    println("Checking Line - Projection");

    println("Checking Line - Value");

    println("Checking IntersectAndDistance");

    println("Checking IntersectAndDistance - Constructors");

    return 0;

    /*

    SpaceRect m(-50, 50, 100, 100, -M_PI_4);
    printCenter("m", m);

    SpaceRect a(m.topLeft().x - 50,         m.topLeft().y + 50,         100, 100, -M_PI_4);
    SpaceRect b(m.topRight().x - 50,        m.topRight().y + 50,        100, 100, -M_PI_4);
    SpaceRect c(m.bottomRight().x - 50,     m.bottomRight().y + 50,     100, 100, -M_PI_4);

    printCenter("a", a);
    printCenter("b", b);
    printCenter("c", c);

    checkInstersect("a-b", a, b);
    checkInstersect("a-c", a, c);
    checkInstersect("a-m", a, m);

    checkInstersect("b-a", b, a);
    checkInstersect("b-c", b, c);
    checkInstersect("b-m", b, m);

    checkInstersect("c-a", c, a);
    checkInstersect("c-b", c, b);
    checkInstersect("c-m", c, m);

    checkInstersect("m-a", m, a);
    checkInstersect("m-b", m, b);
    checkInstersect("m-c", m, c);

     */

}