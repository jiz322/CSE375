#include "simplemap.h"
#include <iostream>
int main(int argc, char** argv) {

    simplemap_t<char*, int> a = simplemap_t<char*, int> ();
    a.insert("Jordan", 1);
    a.insert("Jord", 1);
    a.insert("Jordan", 2);
    std::cout << &a.values << std::endl;

}