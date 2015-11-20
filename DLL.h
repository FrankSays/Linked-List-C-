/* 
* DLL.H is the header file for Doubly Linked list called DLL
*/

#ifndef DLL_H
#define DLL_H

#include <new>
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::bad_alloc;


//Node class of the doubly linked list class
template <typename T>
class DNode 
{
public: 
	T info; 
	DNode<T> *previous;
	DNode<T> *next;
	
	DNode() { previous = NULL, next = NULL; };
	DNode(T info, DNode<T> *pPtr = NULL, DNode<T> *nPtr = NULL) { this->info = info, previous = pPtr, next = nPtr; }
};

//Doubly Linked list class with sentinel node
template <typename T>
class DLL
{
private:
	int count;
	DNode<T> *sentinel;

public:
	DLL(); 
	~DLL();
	
	//mutator functions to changed the contents of the linked list
	void insert_rear(T);
	void insert(int insertindex, T);
	void insert_front(T);
	void erase(int eraseindex);
	void erase_rear();
	void erase_front();
	void clear();

	//accessor functions that return contents of the linked list
	T& operator[](int index);
	T& front();
	T& back();
	T& at(int index);
	int size() const;

		
};

//empty linked list constructor
template <typename T>
DLL<T>::DLL()
{
	sentinel = new DNode<T>;
	sentinel->previous = sentinel;
	sentinel->next = sentinel;
	count = 0;
}//END linked list empty constructor

//Clear() function for the DLL
template <typename T>
void DLL<T>::clear()
{
	if (sentinel->next == sentinel)
	{
		cout << "\tList is already empty.\n";
	}
	else
	{
		cout << "\tRemoving all " << count << " nodes from the list.\n";
		DNode<T> *current = sentinel->next;
		int deleteCount = 0;
		while (current != sentinel)
		{
			sentinel->next = sentinel->next->next;
			delete current;
			deleteCount++;
			count--;
			current = sentinel->next;

		}
		cout << "\t" << deleteCount << " nodes were deallocated and removed from the list.\n";
	}

}
 
 //Linked list destructor
template <typename T>
DLL<T>::~DLL()
{
	clear();

} //END Doubly linked list destructor

//size member function
template <typename T>
int DLL<T>::size() const
{
	return count;

}//END size member function



//at member function
template <typename T>
T& DLL<T>::at(int index)
{
	try
	{
		if (index < 0 || index >= this->size())
		{
			string err = "The index is out of range, the program quit out of the at() function and will continue in main()";
			throw err;
		}
		DNode<T> *current = sentinel->next;
		int currentCount = 0;
		while (currentCount != index)
		{
			current = current->next;
			currentCount++;
		}
		return current->info;
	}
	catch (string err)
	{
		throw err;
	}
	
} //END at member function


//insert_rear member function
template <typename T>
void DLL<T>::insert_rear(T insertinfo)
{
	try
	{
		
		DNode<T> *addme = new DNode<T>(insertinfo);
		if (sentinel->next == sentinel) //sentinel points to self meaning its an empty list
		{
			sentinel->next = addme;
			addme->next = sentinel;
			addme->previous = sentinel;
			sentinel->previous = addme;
		}
		else
		{
			sentinel->previous->next = addme;
			addme->next = sentinel;
			addme->previous = sentinel->previous;
			sentinel->previous = addme;
		}
		count++;
	}
	catch (bad_alloc bA)
	{
		cout << "Error occured during the insert_rear() function\n";
		cout << bA.what() << endl;
		throw bA;
	}
	catch (...)
	{
		throw;
	}

} //END insert_rear


//insert_front member function
template <typename T>
void DLL<T>::insert_front(T insertinfo)
{
	
	try
	{
		DNode<T> *addme = new DNode<T>(insertinfo);
		if (sentinel->next == sentinel) //sentinel points to self meaning its an empty list
		{
			sentinel->next = addme;
			addme->previous = sentinel;
			sentinel->previous = addme;
			addme->next = sentinel;
		}
		else
		{
			addme->next = sentinel->next;
			addme->previous = sentinel;
			sentinel->next->previous = addme;
			sentinel->next = addme;
		}
		count++;
	}
		catch (bad_alloc bA)
		{
			cout << "Error occured during the copytolist() function\n";
			cout << bA.what() << endl;
			throw bA;
		}
		catch (...)
		{
			throw;
		}
} //END insert_front

//insert member function with index parameter
template <typename T>
void DLL<T>::insert(int insertindex, T insertinfo)
{
	try
	{
		DNode<T> *addme = new DNode<T>(insertinfo);
		if (insertindex < 0 || insertindex >= this->size())
		{
			string err = "The index entered is out of scope!";
			throw err;
		}
		if (sentinel->next == sentinel || insertindex == 0)
		{
			insert_front(insertinfo);
		}
		else
		{
			DNode<T> *current = sentinel->next;
			int currentcount = 0;
			while (currentcount != insertindex)
			{
				current = current->next;
				currentcount++;
			}
			current->next->previous = addme;
			addme->previous = current->previous;
			current->previous = addme;
			addme->next = current;
			count++;
		}
	}
	catch (string err)
	{ 
		//cout << err << endl;
		throw err;
	}
	catch (...)
	{
		throw;
	}
} //END insert 


//Erase member function
template <typename T>
void DLL<T>::erase(int eraseindex)
{
	try
	{
		if (eraseindex < 0 || eraseindex > this->size())
		{
			string err = "The index entered is out of scope!";
			throw err;
		}
		if (sentinel->next == sentinel)
		{
			cout << "The Link List is empty. Nothing to remove\n";
		}
		else
		{
			DNode<T> *current = sentinel->next;
			int currentcount = 0;
			while (currentcount != eraseindex)
			{
				current = current->next;
				currentcount++;
			}
			current->previous->next = current->next;
			current->next->previous = current->previous;
			delete current;
			count--;
		}
	}
	catch (string err)
	{
		//cout << err << endl;
		throw err;
	}
	catch (...)
	{
		throw;
	}

} //END erase member function

//erase_rear member function
template <typename T>
void DLL<T>::erase_rear()
{
	try
	{
		if (sentinel->next == sentinel)
		{
			string err "The Link List is empty. Nothing to remove\n";
			throw err;
		}
			DNode<T> *current = sentinel->previous;
			sentinel->previous = current->previous;
			current->previous->next = current->next;
			delete current;
			count--;
	}
	catch (string err)
	{
		cout << err << endl;
		throw err;
	}
	catch (...)
	{
		throw;
	}

}//END erase_rear

//erase_front member function
template <typename T>
void DLL<T>::erase_front()
{
	
	try
	{
		if (sentinel->next == sentinel)
		{
			string err = "The Link List is empty. Nothing to remove\n";
			throw err;
		}
		DNode<T> *current = sentinel->next;
		sentinel->next = current->next;
		current->next->previous = current->previous;
		delete current;
		count--;
	}
	catch (string err)
	{
		cout << err << endl;
		throw err;
	}
	catch (...)
	{
		throw;
	}

}//END erase_front

//operator[] overloader
template <typename T>
T& DLL<T>::operator[](int index)
{
	return at(index);

}//END Operator[] overloader

//front() member function
template <typename T>
T& DLL<T>::front() 
{
	return sentinel->next;
}//END Front

//back() member function
template <typename T>
T& DLL<T>::back()
{
	return sentinel->previous;
}//END back member function

#endif
