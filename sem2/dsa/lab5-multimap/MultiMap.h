#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;

private:
	//TODO - Representation
	//multimap represented using hashtable with separate chaining with unique keys stored in dynamic arrays

	struct Node {
		TKey key;
		TValue* values;
		int valueCount;
		int valueCapacity;
		Node* next;
		Node(TKey k, TValue v) : key(k), next(nullptr) {
			values = new TValue[4];
			values[0] = v;
			valueCount = 1;
			valueCapacity = 4;
		};

		~Node() {
			delete[] values;
		};

		void resize() {
			valueCapacity *= 2;
			TValue* newValues = new TValue[valueCapacity];
			for (int i = 0; i < valueCount; ++i) {
				newValues[i] = values[i];
			}
			delete[] values;
			values = newValues;
		}

		void addValue(TValue v) {
			if (valueCount >= valueCapacity) {
				resize();
			}
			values[valueCount++] = v;
		}
	};

	Node** table;
	int capacity;
	int numberOfElements;

	int hashFunction(TKey key) const {
		return abs(key) % capacity;
	}

	void rehash() {
		int oldCapacity = capacity;
		capacity *= 2;
		Node** newTable = new Node * [capacity] {};
		for (int i = 0; i < oldCapacity; ++i) {
			Node* current = table[i];
			while (current) {
				int index = hashFunction(current->key);
				Node* newNode = current->next;
				current->next = newTable[index];
				newTable[index] = current;
				current = newNode;
			}
		}
		delete[] table;
		table = newTable;
	}

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//adds all pairs from m, whose key is not in the MultiMap already
	//returns the number of added pairs
	int addIfNotPresent(MultiMap& m);

	//descturctor
	~MultiMap();


};

