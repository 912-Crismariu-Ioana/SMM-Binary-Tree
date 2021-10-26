#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

typedef struct
{
    TKey key;
    TValue* values;
    int capacity;
    int nrValues;

} LA;

typedef struct {
    LA* elements;
    int* left;
    int* right;
    int* parent;
    int capacity;
    int root;
    int firstEmpty;

} BST;


class SortedMultiMap {
	friend class SMMIterator;
    private:
        BST* tree;
        int nrElements;
        int uniqueKeys;
        Relation r;
        void resizeSingleElement(int currentPosition);
        void resize();
        int minimum(int position) const;
        int maximum(int position) const;
        bool remove_value(int position, TValue value);
        void inOrder(vector<TKey>& keySet, int position) const;
    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    //returns a vector with all the keys from the SortedMultiMap 
    vector<TKey> keySet() const;


    // destructor
    ~SortedMultiMap();
};
