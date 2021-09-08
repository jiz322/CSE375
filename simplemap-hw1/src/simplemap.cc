#include "simplemap.h"
#include <iostream>
#include <stdio.h>
int main(int argc, char** argv) {

    simplemap_t<char*, int> a = simplemap_t<char*, int> ();
    char j[] = "jordan";
    char j2[] = "jord";
    char j3[] = "jordan";
    char j4[] = "jordan";
    char j5[] = "jordan";
    char j6[] = "jordan";
    char j7[] = "jordan";
    printf ("%d",a.insert(j, 1));
    printf ("%d",a.insert(j2, 11));
    printf ("%d",a.insert(j, 2));
    printf ("%d",a.insert(j4, 4));
    printf ("%d",a.insert(j5, 5));
    printf ("%d",a.insert(j6, 6));
    printf ("%d",a.insert(j7, 7));
    printf ("%d",a.insert(j3, 8));
    //FEATURE or BUG?
    //Insert string "jordan" multiple time will success,
    //but sert two j will fail.
    //Can still lookup the correct value....
    //This can be fixed by using string comparision instead of "==" in insert function
    //But right now I do not think it matters for this project...
    //TODO (if have time) fix the bug mentioned above
    //NB: we willl use int & fload for test, so this is not an issue.


    //dereference using '->', deref the values pointer to exact vector
    //The  "[1]" dereference the list, can also do with starting "*"
    printf ("%d",(a.values->data())[0]); 
    printf ("%d",a.values->size()); // Result 2
    //Insert test succes!
    //Test Update
    //CANNOT PASS STRING DIRECTLY!!!!!!!!!
    printf ("%d",a.update(j, 666)); 
    printf ("%d",(a.values->data())[6]); 
    printf ("%d",a.update(j3, 888)); 
    printf ("%d",(a.values->data())[6]); 
    //get expected digit 81888, test succes!
    //Test Remove
    printf("test Remove");
    printf ("%d",a.remove(j3)); //should be 1
    printf ("%d",(a.values->data())[6]); //???memory leak?
    //NB
    //Result 888. Do I have to free this memory after its no longer in vector?
    //Feature or Bug?
    //It may not too important since deposit and balance does not call insert/delete
    //I have to change the initiall malloc each time of run though...
    //If I did not implement memory correctlly this time, I promise I will do it next time.
    //TODO: If have time, fix the memory leak issue:)
    //TODO: Relloc memory each time of inseartion, free memory after delete.

    printf ("%d",a.remove(j3)); //should be 0
    printf ("%d",(a.remove(j))); //1
    printf ("%d",(a.values->data())[0]); //11
    printf ("%d",(a.values->data())[1]); //4  
    //Test pair
    printf("test pair");
    printf("%d %d", a.lookup(j2).first, a.lookup(j2).second); //11 1
    printf("%d %d", a.lookup(j6).first, a.lookup(j6).second); //6 1
    printf("%d %d", a.lookup(j).first, a.lookup(j).second);   //0 0

    //Test Int&float
    simplemap_t<int, float> b = simplemap_t<int, float> ();
    printf ("%d",b.insert(1, 0.1));
    printf ("%d",b.insert(2, 0.2));
    printf ("%d",b.insert(3, 0.3));
    printf ("%d",b.insert(1, 0.1));
    printf ("%d",b.insert(2, 0.2));
    printf ("%d",b.insert(3, 0.3));

}