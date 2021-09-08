// CSE 375/475 Assignment #1
// Fall 2021
//
// Description: This file specifies a custom map implemented using two vectors.
// << use templates for creating a map of generic types >>
// One vector is used for storing keys. One vector is used for storing values.
// The expectation is that items in equal positions in the two vectors correlate.
// That is, for all values of i, keys[i] is the key for the item in values[i].
// Keys in the map are not necessarily ordered.
//
// The specification for each function appears as comments.
// Students are responsible for implementing the simple map as specified.

#include <vector>
#include <cassert>
#include <stdlib.h>

template <class K, class V>
class simplemap_t {



  public:
      // Define the two vectors of types K and V
	// << use std::vector<K> >>
    //QUESTION: Is it  okay to make them public?????
    std::vector<K> *keys;
    std::vector<V> *values;

    // The constructor should just initialize the vectors to be empty
    simplemap_t() {
        //Question: should I increase the memory each time of insert?
        //Or should I malloc the whole vector in this constructor.
        //I guess it makes no difference in this project if number of entries keep constant.. but 
        //is these a solution better than another in general?
        //(I guess it's better to increase memory when insert)
        keys = (std::vector<K , std::allocator<K>> *)malloc(100);
        values = (std::vector<V , std::allocator<V>> *)malloc(100);

        //Another student says he uses c++'s map library. Good or bad?
    }


    // Insert (key, val) if and only if the key is not currently present in
    // the map.  Returns true on success, false if the key was
    // already present.
    bool insert(K key, V val) {

        //error: request for member ‘end’ in ‘key’, which is of non-class type ‘char*’
        //error: forbids comparison between pointer and integer (key == *it)
    //    for (std::vector<int>::iterator it = key.begin(); it != key.end(); ++it){
    //        if (key == *it){
    //            return false;
    //        }
    //    }
        for (auto i = keys->begin(); i != keys->end(); ++i)
            if (*i == key)
                return false;
        keys->push_back (key);
        values->push_back (val);
    	
    	return true;

    	// The following is just an example of using C++11 features,
    	// like the 'auto' type and lambda expression
    	/*
        for (auto i = keys->begin(); i != keys->end(); ++i)
            if (*i == key)
                return false;

        // insert the key and value.  Note that indices should, by default, match
        // between these two vectors.
        keys->push_back(key);
        values->push_back(val);
		*/


    }

    // If key is present in the data structure, replace its value with val
    // and return true; if key is not present in the data structure, return
    // false.
    bool update(K key, V val) {
        for (auto i = keys->begin(); i != keys->end(); ++i)
            if (*i == key){
                auto j = values->begin();
                //Compute the location of destination value
                j = j + (i - keys->begin());
                //Replace
                *j = val;
                return true;
            }
        return false;
    }

    // Remove the (key, val) pair if it is present in the data structure.
    // Returns true on success, false if the key was not already present.
    bool remove(K key) {
        for (auto i = keys->begin(); i != keys->end(); ++i)
            if (*i == key){
                auto j = values->begin();
                //Compute the location of destination value
                j = j + (i - keys->begin());
                //Erase
                keys->erase(i);
                values->erase(j);
                return true;
            }
        return false;
    }

    // If key is present in the map, return a pair consisting of
    // the corresponding value and true. Otherwise, return a pair with the
    // boolean entry set to false.
    // Be careful not to share the memory of the map with application threads, you might
    // get unexpected race conditions
    std::pair<V, bool> lookup(K key) {
        assert("Not Implemented");
        //TO DO: the following is a default return value, do not use it!
        return std::make_pair(0, false);
    }

    // Apply a function to each key in the map
    void apply(void (*f)(K, V)) {
    	for (auto i : *keys) {
    		f(i, values->at(i));
    	}
    }
};
