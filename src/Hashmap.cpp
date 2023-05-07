#include "Hashmap.hpp"
#include <string>
#include <stdexcept>
#include <iostream>
#include <functional>

hashmap::~hashmap() {
    for (int i = 0; i < current_array_size; i++) {
        hash_node* current = table[i];
        while (current != nullptr) {
            hash_node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] table;
}


hashmap::hashmap() :
	current_array_size(4), //initial array size, array size track
	minimum_array_size(4), //const, array size lower bound

	current_num_elements(0), //element count tracker

	multiplier(31), //const, prime multiplier for hashing function
	nullchar('\0'), //const, null char for find();
	load_factor(0.7) //const, load factor
{
	table = new hash_node*[current_array_size];
	//dynamically allocate array of hash node pointers
	for(int i = 0; i < current_array_size; i++)
	{
		table[i] = nullptr;
	}
}

void hashmap::print() const {
    std::cout << std::endl;
    for (int i = 0; i < current_array_size; i++) {
        std::cout << "Bucket " << i << ": ";
        hash_node* current = table[i];
        while (current != nullptr) {
            std::cout << current->data->name;
            current = current->next;
        }
        std::cout << std::endl;
    }
}


int hashmap::hasher(const std::string name) const
{
	int n = 1;
    int hash = 0;

    for (char c : name) {
        hash += n * (int) tolower(c);
        n *= multiplier;
    }
    return hash;
}

//resize_if_necessary determines of the hash_node* array has exceeded
//a predefined load factor, and if so, transfers the map elements to
//a new array that is double the size
void hashmap::resize_if_necessary()
{
	bool need_to_resize = false;
	int new_array_size = 0;
	hash_node** new_table;

	if((this->current_num_elements / this->current_array_size) > this->load_factor)
	{
		//if array load exceeds factor
		//enable reallocation loop
		//set new_array size
		need_to_resize = true;
		new_array_size = this->current_array_size * 2;

	}
	else if ((this->current_num_elements / this->current_array_size) < (this->load_factor / 2) && (this->current_array_size > this->minimum_array_size))
	{
		//if array load deceeds half of factor
		//(current / limit) < 0.35 utilization)
		//enable reallocation loop
		//set new_array size as half of current
		need_to_resize = true;
		new_array_size = this->current_array_size / 2;
	}
	if(need_to_resize)
	{
	//dynamically allocate new hash table
		new_table = new hash_node*[new_array_size];
		for(int i = 0; i < new_array_size; i++)
		{
			new_table[i] = 0;
		}


		for (int i = 0; i < current_array_size; i++)
		{
		    	//set a temp node to current bucket head
			hash_node* node = table[i];

			//enter bucket if not empty
		   	while (node != nullptr)
			{

				//save next node of current head
				hash_node* next = node->next;

				// Compute the new index
				int new_index =
			hasher(node->data.name) % new_array_size;


			    // Insert the element into new bucket
			    // by pushing current element at index
			    // down the linked list
			    if (new_table[new_index] == nullptr) {
				// set head of new linked list
				new_table[new_index] = node;
				node->next = nullptr;
			    } else {
				// append to existing linked list
				node->next = new_table[new_index];
				new_table[new_index] = node;
			    }
				//move to next node in old bucket
				//until nullptr is reached and
				//while loop terminates
				node = next;
			}
		}


		// Deallocate the old array of hash node pointers
		delete[] table;

		// change current table pointer to new table
		this->table = new_table;

		//change table size
		this->current_array_size = new_array_size;

	}
}

int hashmap::bucket_count() const
{
	int count = 0;
	for(int i = 0; i < current_array_size; i++)
	{
		if(table[i] != nullptr)
		{
			count++;
		}
	}
	return count;

}

int hashmap::element_count() const
{
	return this->current_num_elements;
}

// adds a new element to the hash map
void hashmap::insert(Waypoint* data)
{
	resize_if_necessary();

	int new_index = hasher(data->name) % current_array_size;

	hash_node* new_node = new hash_node;
    	new_node->data = data;

	if(table[new_index] == nullptr)
	{
		table[new_index] = new_node;
	}
	else
	{
		//append new element to front of bucket list
		new_node->next = table[new_index];
		table[new_index] = new_node;

	}

	this->current_num_elements++;
}

// finds the Waypoint with a given name
Waypoint* hashmap::find(std::string name) const {
    int index = hasher(name) % current_array_size;
    hash_node* current = table[index];
    while (current != nullptr)
    {
        if (current->data->name == name)
        {
            return current->data;
        }
    	else
    	{
            current = current->next;
    	}
    }
    return nullchar; // failed to find char
}