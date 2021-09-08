#include "simplemap.h"
#include <iostream>
#include <stdio.h>
int main(int argc, char** argv) {

    simplemap_t<char*, int> a = simplemap_t<char*, int> ();
    char j[] = "jordan";
    char j2[] = "jord";
    char j3[] = "jordan";
    a.insert(j, 1);
    a.insert(j2, 11);
    a.insert(j, 2);
    //dereference using '->', deref the values pointer to exact vector
    //The  "[1]" dereference the list, can also do with starting "*"
    printf ("%d",(a.values->data())[0]); // Result 11
    printf ("%d",a.values->size()); // Result 2
    //CANNOT PASS STRING DIRECTLY!!!!!!!!!
    printf ("%d",a.update(j, 666)); 
    printf ("%d",(a.values->data())[0]); // Result 11
    printf ("%d",a.update(j3, 666)); 

}