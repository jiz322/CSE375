// CSE 375/475 Assignment #1
// Fall 2021
//
// Description: This file implements a function 'run_custom_tests' that should be able to use
// the configuration information to drive tests that evaluate the correctness
// and performance of the map_t object.

#include <iostream>
#include <ctime>
#include "config_t.h"
#include "tests.h"
#include "simplemap.h"
#include <stdio.h>
#include <random>
#include <thread>
#include <mutex>
#include <shared_mutex> 
#include <chrono>
#include <future>
#include <unistd.h>
	//stopwatch. Returns time in seconds
	//slass time copied from:
	//https://stackoverflow.com/questions/38977879/how-can-i-measure-the-execution-time-of-one-thread
	class timer {
	public:
		std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
		timer() : lastTime(std::chrono::high_resolution_clock::now()) {}
		inline double elapsed() {
			std::chrono::time_point<std::chrono::high_resolution_clock> thisTime=std::chrono::high_resolution_clock::now();
			double deltaTime = std::chrono::duration<double>(thisTime-lastTime).count();
			lastTime = thisTime;
			return deltaTime;
		}
	};
	void printer(int k, float v) {
			std::cout<<"<"<<k<<","<<v<<">"<< std::endl;
	}

	void run_custom_tests(config_t& cfg) { 
		std::shared_timed_mutex mutex1_;	// 10 lock evenly divide total number  of keys
        std::shared_timed_mutex mutex2_;	
		std::shared_timed_mutex mutex3_;
        std::shared_timed_mutex mutex4_;	
		std::shared_timed_mutex mutex5_;
        std::shared_timed_mutex mutex6_;	
		std::shared_timed_mutex mutex7_;
        std::shared_timed_mutex mutex8_;	
		std::shared_timed_mutex mutex9_;
        std::shared_timed_mutex mutex10_;		
		// Step 1
		// Define a simplemap_t of types <int,float>
		// this map represents a collection of bank accounts:
		// each account has a unique ID of type int;
		// each account has an amount of fund of type float.
   		simplemap_t<int, float> map = simplemap_t<int, float> ();	

        // Step 4
        // NB: Step 4  is over here since I want to use this function to initialize
		// Define a function "balance" that sums the amount of all the
		// bank accounts in the map. In order to have a consistent result,
		// the execution of this function should happen atomically:
		// no other deposit operations should interleave.
		auto balance = [&](){
			//printf("balance\n");
			std::shared_lock lock1(mutex1_);
			std::shared_lock lock2(mutex2_);
			std::shared_lock lock3(mutex3_);
            std::shared_lock lock4(mutex4_);
			std::shared_lock lock5(mutex5_);
			std::shared_lock lock6(mutex6_);
            std::shared_lock lock7(mutex7_);
			std::shared_lock lock8(mutex8_);
			std::shared_lock lock9(mutex9_);
            std::shared_lock lock10(mutex10_);
			double sum = 0;
			for (auto i = map.values->begin(); i != map.values->end(); ++i){
				sum = sum + *i;
			}
			//printf("%f", sum);
			return sum;
		};
		// Step 2
		// Populate the entire map with the 'insert' function
		// Initialize the map in a way the sum of the amounts of
		// all the accounts in the map is 100000
		// Jordan: "Let's have 10 accounts each 10000.00 bucks"
		int max_accounts = cfg.key_max;
		for (int i = 0; i < max_accounts - 1; i++){
			map.insert(i, 90000/max_accounts);
		}
        map.insert(max_accounts-1, 100000.0 - balance());
		// Step 3
		// Define a function "deposit" that selects two random bank accounts
		// and an amount. This amount is subtracted from the amount
		// of the first account and summed to the amount of the second
		// account. In practice, give two accounts B1 and B2, and a value V,
		// the function performs B1-=V and B2+=V.
		// The execution of the whole function should happen atomically:
		// no operation should happen on B1 and B2 (or on the whole map?)
		// while the function executes.

		//ramdom generator
    	std::random_device dev;
    	std::mt19937 rng(dev());
		// for select accounts to deposit
    	std::uniform_int_distribution<std::mt19937::result_type> dist_max_accounts(0,max_accounts-1); 
		// for  deposit amount
		std::uniform_int_distribution<std::mt19937::result_type> dist10(0,9);
		// for do work
		std::uniform_int_distribution<std::mt19937::result_type> dist100(0,99);
		//First Try of lambda function here
		auto deposit = [&](){
			int random1 = dist_max_accounts(rng);
			int random2 = dist_max_accounts(rng);
			//random1 and ramdom2 have to be different
			while (random1 == random2){
				random2 = dist_max_accounts(rng);
			}
			// amount is integer 0 - 9
			// I tried float using
			// float amount = dist10(rng) + 0.1*dist10(rng) + 0.01*dist10(rng);
			//I did not get expect resullt, I get a lot of expected result -1
			//I seems float lose accuracy. 
			//It should be 202 knowledge but I forgot...
			// How to fix it? (I guess I do not have time to fix it before Friday)
			float amount = dist100(rng);
			//printf("here\n");
			std::unique_lock<std::shared_timed_mutex> ulock1(mutex1_, std::defer_lock);
			std::unique_lock<std::shared_timed_mutex> ulock2(mutex2_, std::defer_lock);
			std::unique_lock<std::shared_timed_mutex> ulock3(mutex3_, std::defer_lock);
            std::unique_lock<std::shared_timed_mutex> ulock4(mutex4_, std::defer_lock);
            std::unique_lock<std::shared_timed_mutex> ulock5(mutex5_, std::defer_lock);
            std::unique_lock<std::shared_timed_mutex> ulock6(mutex6_, std::defer_lock);
            std::unique_lock<std::shared_timed_mutex> ulock7(mutex7_, std::defer_lock);
            std::unique_lock<std::shared_timed_mutex> ulock8(mutex8_, std::defer_lock);
            std::unique_lock<std::shared_timed_mutex> ulock9(mutex9_, std::defer_lock);
            std::unique_lock<std::shared_timed_mutex> ulock10(mutex10_, std::defer_lock);

            if (random1 < cfg.key_max/10 
                || random2 < cfg.key_max/10){
				while (!ulock1.try_lock());
				
			}
			if ((random1 >= cfg.key_max/10 && random1 < cfg.key_max/10*2)
                || (random2 >= cfg.key_max/10 && random2 < cfg.key_max/10*2)){
                while (!ulock2.try_lock());
			}
            if ((random1 >= cfg.key_max/10*2 && random1 < cfg.key_max/10*3)
                || (random2 >= cfg.key_max/10*2 && random2 < cfg.key_max/10*3)){
				int flag = 1; //While loop indicator
				while (!ulock3.try_lock());
			}
            if ((random1 >= cfg.key_max/10*3 && random1 < cfg.key_max/10*4)
                || (random2 >= cfg.key_max/10*3 && random2 < cfg.key_max/10*4)){
				while (!ulock4.try_lock());
			}
            if ((random1 >= cfg.key_max/10*4 && random1 < cfg.key_max/10*5)
                || (random2 >= cfg.key_max/10*4 && random2 < cfg.key_max/10*5)){
				int flag = 1; //While loop indicator
				while (!ulock5.try_lock());
			}
            if ((random1 >= cfg.key_max/10*5 && random1 < cfg.key_max/10*6)
                || (random2 >= cfg.key_max/10*5 && random2 < cfg.key_max/10*6)){
				while (!ulock6.try_lock());
			}
            if ((random1 >= cfg.key_max/10*6 && random1 < cfg.key_max/10*7)
                || (random2 >= cfg.key_max/10*6 && random2 < cfg.key_max/10*7)){
				while (!ulock7.try_lock());
			}
            if ((random1 >= cfg.key_max/10*7 && random1 < cfg.key_max/10*8)
                || (random2 >= cfg.key_max/10*7 && random2 < cfg.key_max/10*8)){
				while (!ulock8.try_lock());
			}
            if ((random1 >= cfg.key_max/10*8 && random1 < cfg.key_max/10*9)
                || (random2 >= cfg.key_max/10*8 && random2 < cfg.key_max/10*9)){
				while (!ulock9.try_lock());
			}
			if ((random1 >= cfg.key_max/10*9)
                || (random2 >= cfg.key_max/10*9)){ 
				while (!ulock10.try_lock());
			}

			float balance1 = map.lookup(random1).first;
			map.update(random1, balance1+amount);
			float balance2 = map.lookup(random2).first;
			map.update(random2, balance2-amount);
			
		};

		// Step 5
		// Define a function 'do_work', which has a for-loop that
		// iterates for config_t.iters times. In each iteration,
		// the function 'deposit' should be called with 95% of the probability;
		// otherwise (the rest 5%) the function 'balance' should be called.
		// TODO DOWN HERE
		// The function 'do_work' should measure 'exec_time_i', which is the
		// time needed to perform the entire for-loop. This time will be shared with
		// the main thread once the thread executing the 'do_work' joins its execution
		// with the main thread.

		auto do_work = [&](){
			timer stopwatch;
			for (int i = 0; i < cfg.iters; i++){
				if (dist100(rng) < 95){
					deposit();
				}
				else{
					balance();
				}
			}
			//std::this_thread::sleep_for(std::chrono::milliseconds(100));
			printf("\nTime costed %f\n", stopwatch.elapsed());
			
		};
		// Step 6
		// The evaluation should be performed in the following way:
		// - the main thread creates #threads threads (as defined in config_t)
		//   << use std:threds >>
		// - each thread executes the function 'do_work' until completion
		// - the (main) spawning thread waits for all the threads to be executed
		//   << use std::thread::join() >>
		//	 and collect all the 'exec_time_i' from each joining thread
		//   << consider using std::future for retireving 'exec_time_i' after the thread finishes its do_work>>
		// - once all the threads have joined, the function "balance" must be called

		// Make sure evey invocation of the "balance" function returns 100000.

		//Create a vector of threads
		std::vector<std::thread> threads;
		for (int i = 0; i < cfg.threads; i++){
			threads.push_back(std::thread(do_work));
		}
		for (auto &th : threads){
			th.join();
			printf("\nThe balance after join is %f\n", balance());
		}
		// Step 7
		// Now configure your application to perform the SAME TOTAL amount
		// of iterations just executed, but all done by a single thread.
		// Measure the time to perform them and compare with the time
		// previously collected.
		// Which conclusion can you draw?
		// Which optimization can you do to the single-threaded execution in
		// order to improve its performance?
		timer stopwatch2;
		for (int i = 0; i < cfg.threads; i++){
			do_work();
		}
		printf("\nSingle thread Time costed %f\n", stopwatch2.elapsed());
		// Step 8
		// Remove all the items in the map by leveraging the 'remove' function of the map
		// Destroy all the allocated resources (if any)
		// Execution terminates.
		// If you reach this stage happy, then you did a good job!
		for (auto &key : *map.keys){
			map.remove(key);
		}
		free(map.keys);
		free(map.values);
		// Final step: Produce plot
    // I expect each submission to include at least one plot in which
    // the x-axis is the concurrent threads used {1;2;4;8}
    // the y-axis is the application execution time.
    // The performance at 1 thread must be the sequential
    // application without synchronization primitives

    // You might need the following function to print the entire map.
    // Attention if you use it while multiple threads are operating
    
	//map.apply(printer);

	}

void test_driver(config_t &cfg) {
	run_custom_tests(cfg);
}
