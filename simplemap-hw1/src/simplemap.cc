#include "simplemap.h"

//Since header file is the header of cc file, 
//I try to omit many declarations here

//template <class K, class V>
//^redefinition of ‘class simplemap_t<K, V>’

//class simplemap_t{
//^You actually don't need to define the class
// a second time just to implement the functions

// Define the two vectors of types K and V
// << use std::vector<K> >>
std::vector<K> k;
std::vector<V> v;

//public:
//^this should be useless

// The constructor should just initialize the vectors to be empty
simplemap::simplemap_t() {
    k = {};
    v = {};
}

// Insert (key, val) if and only if the key is not currently present in
// the map.  Returns true on success, false if the key was
// already present.
bool simplemap::insert(K key, V val) {

    assert("Not Implemented");
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

int main(int argc, char** argv) {

    simplemap_t a = simplemap_t()
        std::cout << a << std::endl;

}