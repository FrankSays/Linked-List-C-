/* 
* singly link list implementation 
* LL.h
*/

#ifndef LL_H
#define LL_H

#include <new>
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;


//Node class of the linked list class
template <typename T>
class Node 
{
public: 
	T info; 
	Node<T> *next;

	Node(T info, Node<T> *nPtr = NULL) { this->info = info, next = nPtr; }
};

//Linked list class
template <typename T>
class LL
{
private:
	int count;
	Node<T> *head;
	Node<T> *tail;

public:
	LL(); 
	~LL();
	
	//mutator functions to changed the contents of the linked list
	void insert_rear(T);
	void insert(int insertindex, T);
	void insert_front(T);
	void erase(int eraseindex);
	void erase_rear();
	void erase_front();

	//accessor functions that return contents of the linked list
	T& operator[](int index);
	T& front();
	T& back();
	T& at(int index);
	int size() const;
		
};

//empty linked list constructor
template <typename T>
LL<T>::LL()
{
	head = NULL;
	tail = head;
	count = 0;
};
//END linked list empty constructor

//Linked list destructor
template <typename T>
LL<T>::~LL()
{
	if (head == NULL)
	{
		cout << "\tList is already empty.\n";
	}
	else
	{
		cout << "\tRemoving all " << count << " nodes from the list.\n";
		Node<T> *current = head;
		int deleteCount = 0;
		while (current != NULL)
		{
			head = head->next;
			delete current;
			deleteCount++;
			count--;
			current = head;

		}
		cout << "\t" << deleteCount << " nodes were deallocated and removed from the list.\n";
	}

}; //END linked list destructor

//size member function
template <typename T>
int LL<T>::size() const
{
	return count;

};//END size member function



//at member function
template <typename T>
T& LL<T>::at(int index)
{
	if (index < 0 || index >= this->size())
	{
		cout << "The index is out of range, the program quit out of the at() function and will continue in main() and return the information of head ";
		return head->info;
	}
	else
	{
		Node<T> *current = head;
		int currentCount = 0;
		while (currentCount != index)
		{
			current = current->next;
			currentCount++;
		}
		return current->info;
	}
	
}; //END at member function

//insert_rear member function
template <typename T>
void LL<T>::insert_rear(T insertinfo)
{
	Node<T> *addme = new Node<T>(insertinfo);
	if (head == NULL)
	{
		head = addme;
		addme->next = NULL;
		tail = addme;
	}
	else if (count == 1)
	{
		head->next = addme;
		addme->next = NULL;
		tail = addme;
	}
	else
	{
		tail->next = addme;
		addme->next = NULL;
		tail = addme;
	}
	count++;
}; //END insert_rear


//insert_front member function
template <typename T>
void LL<T>::insert_front(T insertinfo)
{
	Node<T> *addme = new Node<T>(insertinfo);
	if (head == NULL)
	{
		head = addme;
		tail = addme;
		addme->next = NULL;
	}
	else
	{
		addme->next = head;
		head = addme;

	}
	count++;
}; //END insert_front

//insert member function with index parameter
template <typename T>
void LL<T>::insert(int insertindex, T insertinfo)
{
	
	Node<T> *addme = new Node<T>(insertinfo);
	if (insertindex < 0 || insertindex >= this->size())
	{
		cout << "The index entered is out of scope!";
	}
	else if (head == NULL)
		{
			head = addme;
			tail = addme;
			addme->next = NULL;
			count++;
		}
	else if (insertindex == 0)
	{
		addme->next = head;
		head = addme;
		count++;
	}
	else
	{			
			Node<T> *current = head;
			Node<T> *trail = head;
			int currentcount = 0;
			while (currentcount != insertindex)
			{
				current = current->next;
				if (currentcount > 0)
				{
					trail = trail->next;
				}
					currentcount++;
			}
			trail->next = addme;
			addme->next = current;
			count++;
		}

}; //END insert 


//Erase member function
template <typename T>
void LL<T>::erase(int eraseindex)
{
	if (eraseindex < 0 || eraseindex > this->size())
	{
		cout << "The index entered is out of scope!";
	}
	else if (head == NULL)
	{
		cout << "The Link List is empty. Nothing to remove\n";
	}
	else 
	{
		Node<T> *current = head;
		Node<T> *trail = head;
		int currentcount = 0;
		while (currentcount != eraseindex)
		{
			current = current->next;
			if (currentcount > 0)
			{
				trail = trail->next;
			}
			currentcount++;
		}
		trail->next = current->next;
		delete current;
		count--;
	}

};//END erase member function

//erase_rear member function
template <typename T>
void LL<T>::erase_rear()
{
	Node<T> *current = head;
	if (head == NULL)
	{
		cout << "The Link List is empty. Nothing to remove\n";
	}
	else if (head == tail)
	{
		delete head;
		head = NULL;
		tail = NULL;
		count = 0;
	}
	else
	{
		while (current->next != tail)
		{
			current = current->next;
		}

		delete tail;
		tail = current;
		tail->next = NULL;
		count--;
	}


};//END erase_rear

//erase_front member function
template <typename T>
void LL<T>::erase_front()
{
	Node<T> *current = head;
	if (head == NULL)
	{
		cout << "The Link List is empty. Nothing to remove\n";
	}
	else if (head == tail)
	{
		delete head;
		head = NULL;
		tail = NULL;
		count = 0;
	}
	else
	{
		head = current->next;
		delete current;
		count--;
	}

};//END erase_front

//operator[] overloader
template <typename T>
T& LL<T>::operator[](int index)
{
	return at(index);

};//END Operator[] overloader

//front() member function
template <typename T>
T& LL<T>::front() 
{
	return head->info;
};//END Front

//back() member function
template <typename T>
T& LL<T>::back()
{
	return tail->info;
};//END back member function







#endif
