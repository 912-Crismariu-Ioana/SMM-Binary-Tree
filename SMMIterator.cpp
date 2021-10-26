#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->stack = new int[this->map.uniqueKeys];
	this->stack_index = -1;
	this->index_in_da = 0;
	int current = this->map.tree->root;
	while(current != -1)
	{
		this->stack_index++;
		this->stack[this->stack_index] = current;
		current = this->map.tree->left[current];
	}
	if (this->stack_index == -1)
		this->currentPosition = -1;
	else
		this->currentPosition = this->stack[this->stack_index];
}
// Best Case: Theta(1) when the root of the tree holds the element having the smallest key
// Worst Case: Theta(number of keys) when the elements were added in descending order (the tree is degenerate)
// Total Complexity: O(number of keys)

void SMMIterator::first(){
	delete[] this->stack;
	this->stack = new int[this->map.uniqueKeys];
	this->stack_index = -1;
	this->index_in_da = 0;
	int current = this->map.tree->root;
	while (current != -1)
	{
		this->stack_index++;
		this->stack[this->stack_index] = current;
		current = this->map.tree->left[current];
	}
	if (this->stack_index == -1)
		this->currentPosition = -1;
	else
		this->currentPosition = this->stack[this->stack_index];
}
// Best Case: Theta(1) when the root of the tree holds the element having the smallest key
// Worst Case: Theta(number of keys) when the elements were added in descending order (the tree is degenerate)
// Total Complexity: O(number of keys)


void SMMIterator::next(){
	if (this->currentPosition == -1)
		throw exception();
	index_in_da++;
	// We haven't finished traversing the array of values for the current key
	if (this->map.tree->elements[this->currentPosition].nrValues > this->index_in_da)
	{
		return;
	}
	// We reached the end of the array of values for the current key, set a new current key
	this->index_in_da = 0;
	int current = this->stack[this->stack_index];
	this->stack_index--;
	// Test if we can go right
	if (this->map.tree->right[current] != -1)
	{
		current = this->map.tree->right[current];
		while (current != -1)
		{
			this->stack_index++;
			this->stack[this->stack_index] = current;
			current = this->map.tree->left[current];
		}
	}
	// The iterator is no longer valid
	if (this->stack_index == -1)
		this->currentPosition = -1;
	else
		this->currentPosition = this->stack[this->stack_index];
}
// Best Case: Theta(1) when fetching the next element from the array of values for a specific key
// Worst Case: Theta(number of keys) when the tree is degenerate
// Total complexity: O(number of keys)

bool SMMIterator::valid() const{
	if (this->currentPosition != -1)
		return true;
	return false;
}
// Complexity: Theta(1)

TElem SMMIterator::getCurrent() const{
	if (this->currentPosition == -1)
		throw exception();
	TElem elem;
	elem.first = this->map.tree->elements[this->currentPosition].key;
	elem.second = this->map.tree->elements[this->currentPosition].values[this->index_in_da];
	return elem;
}
// Complexity: Theta(1)


