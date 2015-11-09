#include "HashMap.hpp"
#include <iostream>



	// Function that produces a hash from a string.  Used in tandem with
	// HashFunction to create hash for a word.
	unsigned int hash(const std::string& word)
	{
		
		int h = 0;
		for (int i = 0; i < word.size(); i++)
		{
			h^=word[i];
		}
		return h;
		
	}


//Default Constructor 
HashMap::HashMap()
	: hasher{hash}, bucketSize{initialBucketCount}, buckets{new Node*[initialBucketCount]}
{
	initNull();
	add("Apple", "55");
	add("Banana", "55");
	add("Orange", "55");
	add("Kiwi", "55");
	add("Strawberry", "55");
	add("Grapefruit", "55");
	add("Grape", "55");
	add("Raspberry", "55");
	add("Durian", "55");
	add("Potato", "55");
	add("Dragonfruit", "55");
	add("Blueberry", "55");
	add("Pinkberries", "55");
	add("Coconut", "55");
	add("Pineapple", "55");
	add("red", "55");
	add("sparkles", "55");
	remove("Strawberry");
	for (int x = 0; x < bucketSize; x++)
	{
		if (buckets[x] == nullptr)
		{
			std::cout <<"Index "<<x+1<<":NullPTR" << std::endl;
		}
		else
		{
			std::cout << "Index " << x+1 << ":" << buckets[x]->key << std::endl;
			Node *temp = buckets[x]->next;
			while (temp != nullptr)
			{	
				std::cout << "Index " << x +1<< ":" << temp->key << std::endl;
				temp = temp->next;
			}

		}

	}
	
}
//Default Constructor with Hash Function
HashMap::HashMap(HashFunction hasher)
	:hasher{hasher}, bucketSize{initialBucketCount}, buckets{new Node*[initialBucketCount]}
{
	initNull();
}
//Copy Constructor 
HashMap::HashMap(const HashMap& hm)
	: hasher{ hm.hasher }, bucketSize{ hm.bucketSize }, buckets{new Node*[hm.bucketSize] }
{
	copyBucket(hm.buckets);

}

HashMap::~HashMap()
{
	deleteBucket();
	delete[] buckets;
}

HashMap & HashMap::operator=(const HashMap & hm)
{
		if (this != &hm)
		{
			deleteBucket();
			hasher = hm.hasher;
			bucketSize = hm.bucketSize;
			buckets = new Node*[hm.bucketSize];
			copyBucket(hm.buckets);
		}
		return *this;
	
}



void HashMap::add(const std::string& key, const std::string& value)
{
	if (contains(key))
		return;
	addElement(key, value);
	
	if (loadFactor() > 0.8)
	{
		int oldSize = bucketSize;
		Node** oldBucket = buckets;
		bucketSize = bucketSize * 2 + 1;
		buckets = new Node*[bucketSize];
		initNull();
		for (int i = 0; i < oldSize; i++)
		{
			//Rehashing
			Node* check = oldBucket[i];
			while (check != nullptr)
			{
				addElement(check->key, check->value);
				check = check->next;
			}
		}

		for (int i = 0; i < oldSize; ++i)
		{
			if (oldBucket[i] != nullptr)
				deleteNode(oldBucket[i]);
		}
		delete[] oldBucket;
	}
	
}



void HashMap::remove(const std::string & key)
{
	if (!contains(key))
	{
		return;
	}
	int index = hasher(key) % bucketSize;
	Node* previous = buckets[index];
	Node* current= previous->next;
	//Handles the case in which the item to remove is the first element in the bucket
	if (previous->key == key)
	{
		buckets[index] = current;
		delete previous;
	}
	else
	{
		while (current->key != key)
		{
			previous = current;
			current = current->next;
		}
		previous->next = current->next;
		delete current;
	}


}

bool HashMap::contains(const std::string & key) const
{
	int index = hasher(key) % bucketSize;
	Node* check = buckets[index];
	while (check != nullptr)
	{
		if (check->key == key)
		{
			return true;
		}
		check = check->next;
	}
	return false;
}

std::string HashMap::value(const std::string & key) const
{
	if (!(contains(key)))
		return "";
	int index = hasher(key) % bucketSize;
	Node* check = buckets[index];
	while (check->key != key)
		check = check->next;
	return check->value;
}

unsigned int HashMap::size() const
{
	int count = 0;
	for (int x = 0; x < bucketSize; x++)
	{
		if (buckets[x] != nullptr)
		{
			count++;
			Node *temp = buckets[x]->next;
			while (temp != nullptr)
			{
				count++;
				temp = temp->next;
			}
		}
	}
	return count;
}

unsigned int HashMap::bucketCount() const
{
	return bucketSize;
}

double HashMap::loadFactor() const
{
	return (double)size() / bucketCount();
}

unsigned int HashMap::maxBucketSize() const
{
	int longest = 0;
	Node* temp;
	for (int x = 0; x < bucketSize; x++)
	{
		int length = 0;
		temp = buckets[x];
		while (temp != nullptr)
		{
			length++;
			temp = temp->next;
		}
		if (length > longest)
			longest = length;
	}
	return longest;
}



void HashMap::initNull()
{
	for (int i = 0; i < bucketSize; i++)
	{
		buckets[i] = nullptr;
	}
}

void HashMap::copyBucket(Node** original)
{
	initNull();
	for (unsigned int i = 0; i < bucketSize; ++i)
	{
		if (original [i] != nullptr)
		{
			Node* copy = original[i];
			buckets[i] = new Node{ copy->key, copy->value, nullptr};
			Node* destination = buckets[i];
			copy = copy->next;
			while (copy != nullptr)
			{
				destination->next = new Node{ copy->key, copy->value, nullptr};
				destination = destination->next;
				copy = copy->next;
			}
		}
	}
}

void HashMap::deleteNode(Node* source)
{

	if (source->next != nullptr)
	{
		deleteNode(source->next);
	}

	delete source;
}


void HashMap::deleteBucket()
{
	for (unsigned int i = 0; i < bucketSize; ++i)
	{
		if (buckets[i] != nullptr)
		{
			deleteNode(buckets[i]);
			buckets[i] = nullptr;
		}
	}
}

void HashMap::addElement(const std::string& key, const std::string& value)
{
	int index = hasher(key) % bucketSize;

	if (buckets[index] == nullptr)
		buckets[index] = new Node{ key, value, nullptr };
	else
	{
		//Handles collisions. If there is a collisions,traverse the linked list until there is a nullptr and stick the element there. 
		Node* check = buckets[index];
		while (check->next != nullptr)
			check = check->next;
		check->next = new Node{ key, value, nullptr };
	}
}

unsigned int HashMap::countNode(const Node* source) const
{
	unsigned int count = 1;
	if (source->next != nullptr)
		count += this->countNode(source->next);

	return count;
}

