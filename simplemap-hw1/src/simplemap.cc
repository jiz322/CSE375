#include "simplemap.h"
#include <iostream>
#include <stdio.h>
#include <random>
int main(int argc, char** argv) {

    simplemap_t<char*, int> c = simplemap_t<char*, int> ();
    char j[] = "jordan";
    char j2[] = "jord";
    char j3[] = "jordan";
    char j4[] = "jordan";
    char j5[] = "jordan";
    char j6[] = "jordan";
    char j7[] = "jordan";
    printf ("%d",c.insert(j, 1));
    printf ("%d",c.insert(j2, 11));
    printf ("%d",c.insert(j, 2));
    printf ("%d",c.insert(j4, 4));
    printf ("%d",c.insert(j5, 5));
    printf ("%d",c.insert(j6, 6));
    printf ("%d",c.insert(j7, 7));
    printf ("%d",c.insert(j3, 8));
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
    printf ("%d",(c.values->data())[0]); 
    printf ("%d",c.values->size()); // Result 2
    //Insert test succes!
    //Test Update
    //CANNOT PASS STRING DIRECTLY!!!!!!!!!
    printf ("%d",c.update(j, 666)); 
    printf ("%d",(c.values->data())[6]); 
    printf ("%d",c.update(j3, 888)); 
    printf ("%d",(c.values->data())[6]); 
    //get expected digit 81888, test succes!
    //Test Remove
    printf("test Remove");
    printf ("%d",c.remove(j3)); //should be 1
    printf ("%d",(c.values->data())[6]); //???memory leak?
    //NB
    //Result 888. Do I have to free this memory after its no longer in vector?
    //Feature or Bug?
    //It may not too important since deposit and balance does not call insert/delete
    //I have to change the initiall malloc each time of run though...
    //If I did not implement memory correctlly this time, I promise I will do it next time.
    //TODO: If have time, fix the memory leak issue:)
    //TODO: Relloc memory each time of inseartion, free memory after delete.

    printf ("%d",c.remove(j3)); //should be 0
    printf ("%d",(c.remove(j))); //1
    printf ("%d",(c.values->data())[0]); //11
    printf ("%d",(c.values->data())[1]); //4  
    //Test pair
    printf("test pair");
    printf("%d %d", c.lookup(j2).first, c.lookup(j2).second); //11 1
    printf("%d %d", c.lookup(j6).first, c.lookup(j6).second); //6 1
    printf("%d %d", c.lookup(j).first, c.lookup(j).second);   //0 0

    //Test Int&float
    printf("test Int and float");
    simplemap_t<int, float> b = simplemap_t<int, float> ();
    printf ("%d",b.insert(1, 0.1));
    printf ("%d",b.insert(2, 0.2));
    printf ("%d",b.insert(3, 0.3));
    printf ("%d",b.insert(1, 0.1));
    printf ("%d",b.insert(2, 0.2));
    printf ("%d",b.insert(3, 0.3));
    printf("%d %f", b.lookup(1).first, b.lookup(1).second); //1.1, 1
    printf("%d %f", b.lookup(4).first, b.lookup(4).second); //0 false

    //try lamda
    // This declares a lambda, which can be called just like a function
    auto print_message = [](std::string message) 
    { 
        std::cout << message << "\n"; 
    };

    // Prints "Hello!" 10 times
    for(int i = 0; i < 10; i++) {
        print_message("Hello!"); 
    }
    //Yes!! Lamda works!


    // auto balance = [](){
    //     return "yeyeyeye";
	// };
    // printf("%s", balance());

    //Yes!! Lamda return works!

    // printf("try random");
    // //ramdom generator
    // std::random_device dev;
    // std::mt19937 rng(dev());
    // std::uniform_int_distribution<std::mt19937::result_type> dist10(0,9); // distribution in range [0, 9]
    // std::cout << dist10(rng) << std::endl;
    // std::cout << dist10(rng) << std::endl;
    // std::cout << dist10(rng) << std::endl;
    // std::cout << dist10(rng) << std::endl;
    // std::cout << dist10(rng) << std::endl;
    // std::cout << dist10(rng) << std::endl;
    // std::cout << dist10(rng) << std::endl;
    // std::cout << dist10(rng) << std::endl;
    // std::cout << dist10(rng) << std::endl;
    // //Yes, It is okay.
    // float amount = dist10(rng) + (float)dist10(rng)/10 + (float)dist10(rng)/100;
    // printf("%f", amount); 

    //Test tests.cc
    simplemap_t<int, float> a = simplemap_t<int, float> ();	
    int max_accounts = 10;
    for (int i = 0; i < max_accounts; i++){
        a.insert(i, 10000);
    }
    float sum = 0;
    for (auto i = a.values->begin(); i != a.values->end(); ++i){
        sum = sum + *i;
    }
    printf("%d ", (int)sum);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_max_accounts(0,max_accounts); 
    std::uniform_int_distribution<std::mt19937::result_type> dist10(0,9);
    std::uniform_int_distribution<std::mt19937::result_type> dist100(0,99);
    auto deposit = [&](){
        int random1 = dist_max_accounts(rng);
        int random2 = dist_max_accounts(rng);
        while (random1 == random2){
            random2 = dist_max_accounts(rng);
        }
        
        float amount = 5;
        float balance1 = a.lookup(random1).first;
        float balance2 = a.lookup(random2).first;
        printf("\n");
        printf("random1 : %d \n", random1);
        printf("random2 : %d \n", random2);
        printf("balance1 %d \n", int(balance1));
        printf("balance1 %d \n", int(balance2));
        a.update(random1, balance1+amount);
        a.update(random2, balance2-amount);
        float balance3 = a.lookup(random1).first;
        float balance4 = a.lookup(random2).first;
        printf("balance1after %d \n", int(balance3));
        printf("balance2after %d \n", int(balance4));
    };
    auto balance = [&](){
        float sum = 0;
        for (auto i = a.values->begin(); i != a.values->end(); ++i){
            sum = sum + *i;
        }
        //printf("%d ", (int)sum);
    };
    auto do_work = [&](){
        for (int i = 0; i < 1000; i++){
            if (dist100(rng) < 95){
                deposit();
            }
            else{
                balance();
            }
        }
    };
    do_work();
}