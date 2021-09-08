#include "simplemap.h"
#include <iostream>
#include <stdio.h>
int main(int argc, char** argv) {

    simplemap_t<char*, int> a = simplemap_t<char*, int> ();
    char j[] = "jordan";
    char j2[] = "jord";
    a.insert(j, 1);
    a.insert(j2, 1);
    a.insert(j, 2);
    printf ("%d",*a.values);

}