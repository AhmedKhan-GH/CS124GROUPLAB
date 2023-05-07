#ifndef HASHMAP_HPP
#define HASHMAP_HPP
#include "Waypoint.hpp"
#include <string>


class Hashmap
{
public:

	~Hashmap();
    Hashmap(); //constructor to set consts

    void insert(Waypoint* data);
    // adds a new element to the hash map

    Waypoint* find(std::string name) const;
    // finds the Waypoint that has a given name

    int hasher(const std::string name) const;
	void resize_if_necessary();
    int bucket_count() const;
    int element_count() const;
    void print() const;
private:

	// Node for sheparate chaining
	struct hash_node
	{
		Waypoint* data;
		//pair of char, and cipher string key-value pairs
		hash_node* next = nullptr;
		//hash node is a linked list element
	};


	const double load_factor;
	const int minimum_array_size;
	int current_array_size;
	int current_num_elements;
	const char nullchar;
	const int multiplier;
	hash_node** table;
};

#endif //HASHMAP_HPP
