#include <iostream>
using namespace std;
template <typename Key, typename Info>
class Ring {

	struct Node {
		Key		id;
		Info	data;
		Node*	prev;
		Node*	next;
	};
	Node* any;
	int counter;
public:
	class iterator
	{
		Node* element;
	public:
		iterator(){ 
		element = NULL; 
		}
		~iterator() {
		}
		iterator(Node* copyElement){
			element = copyElement;
		}
		iterator(const iterator& copy){ 
		element = copy.element; 
		*this = copy;
		}
		iterator& operator=(const iterator& copy){ 
		element = copy.element; 
		return *this; 
		}
		bool operator==(const iterator& compare){ 
		return element == compare.element; 
		}
		bool operator!=(const iterator& compare){ 
		return element != compare.element; 
		}
		iterator operator-(const unsigned int howmany){
			iterator this1 = *this;
			for (int i = 0; i<howmany; i++)
				this1--;
			return this1;
		}
		iterator& operator--()
		{
			if (element != NULL)
			{
				element = element->prev;
			}
			return *this;
		}
		
		
		
		iterator operator+(const unsigned int howmany)
		{
			iterator this1 = *this;
			for (int i = 0; i<howmany; i++)
				this1++;
			return this1;
		}
		
		iterator& operator++()
		{
			if (element != NULL){
				element = element->next;
			}
			return *this;
		}
		const Node& operator*() { return *element; }
		const Node* operator->() { return element; }
		Key getKey() const { return element->id; }
		Info getInfo() const { return element->data; }
	};
	Ring()
	{
		any = NULL;
		counter = 0;
	}
	Ring(const Ring<Key, Info>& Copy)
	{
		any = NULL;
		counter = 0;
		*this = Copy;
	}
	~Ring()
	{
		removeAll();
	}
	
	iterator begining() const
	{
		
		return iterator(any);
	}
	iterator ending() const
	{
	
		return iterator(any->prev);
	}
	int sizeOfRing() const
	{
		return counter;
	}
	
	void removeAll()
	{
		Node* temp;
		if (any == NULL)
		{
			return;
		}
		any->prev->next = NULL;
		if (any != NULL)
			while (any != NULL)
			{
				temp = any;
				any = any->next;
				delete temp;
			}
		counter = 0;
	}
	bool addPrevious(const Key&key, const Info& info)
	{
		Node* newNode = new Node();
		newNode->id = key;
		newNode->data = info;

		if (any == NULL){
			newNode->next = newNode;
			newNode->prev = newNode;
			any = newNode;
			counter++;
			return true;
		}
		else{
			newNode->prev = any;
			newNode->next = any->next;
			any->next->prev = newNode;
			any->next = newNode;
			counter++;
			return true;
		}
		return false;
	}
		bool addNext(const Key&key, const Info& info)
	{
		Node* newNode = new Node();
		newNode->id = key;
		newNode->data = info;

		if (any == NULL)
		{
			newNode->next = newNode;
			newNode->prev = newNode;
			any = newNode;
			counter++;
			return true;
		}
		else
		{
			newNode->next = any;
			newNode->prev = any->prev;
			any->prev->next = newNode;
			any->prev = newNode;
			counter++;
			return true;
		}
		return false;
	}
	
	bool addAfter(const Key&key, const Info& info, const Key& nodeafter)
	{
		Node* temp = any;
		Node* newNode = new Node();
		newNode->id = key;
		newNode->data = info;
		if (any == NULL)
		{
			return false;
		}
		while (temp)
		{
			if (temp->id == nodeafter){
				newNode->next = temp->next;
				newNode->prev = temp;
				temp->next->prev = newNode;
				temp->next = newNode;
				counter++;
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	
	void printList()
	{
		Node* temp = any;
		int counter2 = counter;
		if (temp == NULL){
			cout << "List is empty" << endl;
			return;
		}
		do{
		cout << temp->data << endl;
		temp = temp->next;
		counter2--;
		} while(counter2 > 0);
	}
	
	void remove(const Key&k, bool every)
	{
		int size1;
		size1 = sizeOfRing();
		Node* temp = any;
		Node* temp2;

		while (any->id == k){
			temp2 = temp;
			temp->prev->next = temp2->next;
			temp->next->prev = temp2-> prev;
			any = temp->next;
			counter--;
			delete temp2;
			if (every == false)
				return;
		}


		while (size1 > 0)
		{
			if (every == true)
			{
				if (temp->id == k)
				{
					temp2 = temp;
					temp->prev->next = temp2->next;
					temp->next->prev = temp2->prev;
					temp = temp->next;
					delete temp2;
					counter--;
					size1--;
				}
				temp = temp->next;
			}
			else
				if (temp->id == k)
				{
					temp2 = temp;
					temp->prev->next = temp2->next;
					temp->next->prev = temp2->prev;
					temp = temp->next;
					delete temp2;
					counter--;
					size1--;
					return;
				}
			temp = temp->next;
			size1--;
			}	
	}
	Ring<Key, Info>& operator=(const Ring<Key, Info>& copyRing)
	{if (&copyRing == this)
			return *this;
		int sizeOfRing = copyRing.sizeOfRing();
		removeAll();
		Node* current = copyRing.any;
	
		while (sizeOfRing > 0){
			addNext(current->id, current->data);
			current = current->next;
			sizeOfRing--;
		}
		return *this;
	}
	friend Ring<Key, Info>& operator-(const Ring<Key, Info>& firstring, const Ring<Key, Info>& secondring)
	{
		bool exists = false;
		int sizeOfRing = firstring.sizeOfRing();
		Ring<Key, Info> *newRing = new Ring<Key, Info>;
		Ring<Key, Info>::iterator it1 = firstring.begining();
		Ring<Key, Info>::iterator it2 = secondring.begining();
		while (sizeOfRing > 0)
		{
			it2 = secondring.begining();
			do
			{
				if (it1->id==it2->id)
				{
					exists = true;
				}
				if (exists == true)
				{
					
					break;
				}
				++it2;

			} while (secondring.begining() != it2);
			if (exists == false)
			{
				newRing->addNext(it1.getKey(), it1.getInfo());
			}
			else
			{
				exists = false;
			}
			sizeOfRing--;
			++it1;
		}
		return *newRing;
	}
	friend Ring<Key, Info>& operator+(const Ring<Key, Info>& firstring, const Ring<Key, Info>& secondring)
	{
		
			Ring<Key, Info> *newRing=new Ring<Key,Info>;
			Ring<Key, Info>::iterator it1 = firstring.begining();
			Ring<Key, Info>::iterator it2 = secondring.begining();
			do
			{
				newRing->addNext(it1.getKey(), it1.getInfo());
				++it1;
			} while (firstring.begining()!=it1);

			do
			{
				newRing->addNext(it2.getKey(), it2.getInfo());
				++it2;
			} while (it2 != secondring.begining());
			return *newRing;
		}
	
	friend ostream& operator << (ostream &o, const Ring<Key, Info>& s)
	{
		if (s.any == NULL)
			return o;
		Node* temp = s.any;
		do 
		{
			o << temp->data << endl;
			temp = temp->next;
		} while (temp != s.any);
		return o;
	}
};
template <typename Key, typename Info>
Ring<Key, Info> produce(const Ring<Key, Info>& r1, int start1, int steps1, bool dir1, const Ring<Key, Info>& r2, 
int start2, int steps2, bool dir2, int num, bool dir_out)
{
	int r1_size = r1.sizeOfRing();
	int r2_size = r2.sizeOfRing();
	Ring<Key, Info> r3;
	typename Ring<Key, Info>::iterator it1 = r1.begining();
	typename Ring<Key, Info>::iterator it2 = r2.begining();
	int wherestart1 = start1 % r1_size;
	int wherestart2 = start2 % r2_size;

	for (int i = 0; i < wherestart1; i++)
	{
		if (dir1 == 0){
			--it1;
		}
		else{
			++it1;
		}
		
	}
	for (int i = 0; i < wherestart2; i++)
	{
		if (dir2 == 0)
		{
			--it2;
		}
		else
		{
			++it2;
		}

	}
	
	while (num > 0)
	{
		if (dir_out == 1){
			for (int i = 0; i < steps1; i++){
				r3.addNext(it1.getKey(), it1.getInfo());
				if (dir1 == 0){
					--it1;
				}
				else{
					++it1;
				}
			}
			for (int i = 0; i < steps2; i++){
				r3.addNext(it2.getKey(), it2.getInfo());
				if (dir2 == 0){
					--it2;
				}
				else{
					++it2;
				}
			}
			num--;
		}

		else{
			for (int i = 0; i < steps1; i++){
				r3.addPrevious(it1.getKey(), it1.getInfo());
				if (dir1 == 0){
				--it1;
				}
				else{
				++it1;
				}
			}
			
			for (int i = 0; i < steps2; i++){
				r3.addPrevious(it2.getKey(), it2.getInfo());
				if (dir2 == 0){
				--it2;
				}
				else{
					++it2;
				}
			}
				num--;
		}
	}
	return r3;
}

int main()
{
	Ring<int, float> ring1;
	ring1.addNext(10, 1.1);
	ring1.addNext(3, 9.99);
	ring1.addAfter(100, 5.66,3);
	ring1.addAfter(36, 63, 100);
	ring1.addNext(3, 555);
	cout<<"first ring with print function:"<<endl;
	ring1.printList();
	cout<<"first ring with << operator:"<<endl;
	cout<<ring1;
	Ring<int,float>ring2;
	ring2.addNext(5, 0.15);
	ring2.addAfter(12, 13.3, 5);
	ring2.addAfter(255845, 89.123456, 12);
	ring2.addNext(999, 33.3333333);
	cout<<"second ring:"<<endl;
	cout<<ring2<<endl;
	Ring<int,float>ringoperators;
	ringoperators=ring1+ring2;
	cout<<"+"<<endl;
	ringoperators.printList();
	cout<<endl;
	ring1.addNext(5, 0.15);
	ring1.addNext(999, 33.3333333);
	ringoperators=ring1-ring2;
	cout<<"-"<<endl;
	cout<<ringoperators<<endl;
	ring1.addNext(8, 4.1);
	ring1.addNext(4, 6.99);
	ring1.addAfter(23, 8.16,4);
	ring2.addNext(10, 10.10);
	ring2.addNext(11, 11.11);
	Ring<int,float>ringproduce=produce(ring1, 1, 3, false, ring2, 0, 5, false, 3, true);
	cout<<"produce:"<<endl;
	ringproduce.printList();
}
