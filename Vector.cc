// Implementation of the templated Vector class
// SONALI GOVINDALURI

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "String.h"

#include "Vector.h"

using namespace std;

// Default constructor
template <typename T>
Vector<T>::Vector() {
	elements = NULL;
	count = 0;
	reserved = 0;
}


// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& rhs) {
	count = rhs.count;
	reserved = rhs.reserved;

	elements = (T*)malloc(reserved* sizeof(T));
	for(int i =0; i<count; i++) {
		new(&elements[i])T(rhs.elements[i]);
	}
}


// Assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs) {
	//Check if it is pointing to itself, and return if it is true
	if(this==&rhs)
		return *this;

	//Check if current elements are null
	//If not, free memory, call the destructor on current elements
	if(elements!=NULL){
		for(int i=0; i<count; i++){
			elements[i].~T();
		}
		free(elements);
	}
    
	//Copy new variables and allocate new memory 
	//call in-place new to create new objects
	count = rhs.count;
	reserved = rhs.reserved;
	elements = (T*)malloc(reserved *sizeof(T));
	for(int i =0; i<count; i++) {
		new(&elements[i])T(rhs.elements[i]);
	}
}


// Other constructors
template <typename T>
Vector<T>::Vector(size_t nReserved) { // Initialize with reserved memory
	elements = (T*)malloc(nReserved* sizeof(T));
	count = 0;
	reserved = nReserved;
}


template <typename T>
Vector<T>::Vector(size_t n, const T& t) { // Initialize with "n" copies of "t"
	count = n;
	reserved = n;
	elements = (T*)malloc(count * sizeof(T));

	for(int i=0; i<count; i++) {
		new(&elements[i])T(t);
	}
}


template <typename T>
void Vector<T>::Reserve(size_t n) { // Reserve extra memory
	this->reserved = n;
	elements = (T*)malloc(n* sizeof(T));
}


// Destructor
template <typename T>
Vector<T>::~Vector() {
	if(elements) {
		for(int i = 0; i < count; i++){
		      elements[i].~T();
		    }
		    free(elements);
	}
	reserved = 0;
	count = 0;
}


// Add and access front and back
template <typename T>
void Vector<T>::Push_Back(const T& rhs) {
	if(count == reserved) {
	  reserved = reserved + 1;
	  T* tempVec = (T*)malloc(reserved * sizeof(T));
	  count = count + 1;

        for(int i = 0; i < (count-1); i++) {
	    new(&tempVec[i])T(elements[i]);
	    elements[i].~T();
	  }
    new(tempVec+(count-1))T(rhs);
    free(elements);
    elements = tempVec;
	}
    else {
	  count++;
	  new(&elements[count-1])T(rhs);
	}
}	 


template <typename T>
void Vector<T>::Push_Front(const T& rhs) {
	if(count == reserved) {
		reserved = reserved + 1;
	    T* tempVec = (T*)malloc(reserved * sizeof(T));
	    count = count + 1;
 		
 		for(int i=1; i<count; i++) {
 			new(&tempVec[i])T(elements[i-1]);
 			elements[i-1].~T();
 		}

 		new(tempVec)T(rhs);
 		free(elements);
 		elements = tempVec;
 	}

 	else {
 		for(int i =count; i>count; i--) {
 			new(&elements[i])T(elements[i-1]);
 			elements[i-1].~T();
 		}
 		new(elements)T(rhs);
 		count++;
 	}
}


template <typename T>
void Vector<T>::Pop_Back) { // Remove last element
	if(count!=0) {
		count = count - 1;
		elements[count].~T();
	}
}


// Remove first element
template <typename T>
void Vector<T>::Pop_Front() {
    // Only if elements are not empty
	if(count != 0) {
   		T* tempVec = (T*)malloc(reserved * sizeof(T));
        
    	for(int i = 1; i < count; i++) {
    		new(&tempVec[i-1])T(elements[i]);
      		elements[i].~T();
    	}
        elements[0].~T();
    	free(elements);
		elements = tempVec;
    	count = count - 1;
  	}
}


// Element Access
template <typename T>
T& Vector<T>::Front() const {
	return elements[0];
}

// Element Access
template <typename T>
T& Vector<T>::Back() const {
	int last = count -1;
	return elements[last];
}

template <typename T>
const T& Vector<T>::operator[](size_t i) const { // const element access
	if(i<0 || i>=count) {
		cout<<"Invalid index"<<endl;
		abort();
	}
	return elements[i];
}

//nonconst element access
template <typename T>
T& Vector<T>::operator[](size_t i) {
	if(i<0 || i>=count) {
		cout<<"Invalid index"<<endl;
		abort();
	}
	return elements[i];
}


template <typename T>
size_t Vector<T>::Size() const {
	return count;
}

template <typename T>
bool Vector<T>::Empty() const {
	if(count == 0)
		return true;
	else
		return false;
}


// Implement clear
template <typename T>
void Vector<T>::Clear {
	for(int i =0; i<count; i++) {
		elements[i].~T();
	}
	count = 0;
}


// Iterator access functions
template <typename T>
VectorIterator<T> Vector<T>::Begin() const {
  return VectorIterator<T>(elements);
}


template <typename T>
VectorIterator<T> Vector<T>::End() const {
	return VectorIterator<T>(elements+count);
}


// Erase and insert
template <typename T>
void Vector<T>::Erase(const VectorIterator<T>& it) {
	bool flag = false;
	int pos;

	for(int i = 0; i < count; i++) {
		if((&elements[i]) == it.current) {
			pos = i;
			flag = true;
			break;
		}
	}

	if(flag==true) {
		for(int i = pos; i < count - 1; i++) {
			elements[i].~T();
			new(&elements[i])T(elements[i+1]);
		}	
	}
	count=count-1;
}

template <typename T>
void Vector<T>::Insert(const T& rhs, const VectorIterator<T>& it) {
	int pos;
	bool flag = false;

	for(int i=0; i< count; i++) {
		if((&elements[i]) == it.current) {
			flag = true;
			pos = i;
			break;
		}
	}
	
	if(flag==true) {
		//if count = reserved, create new tempVec of size reserved+1
		if(count==reserved) {
			reserved = reserved+1;
			T* tempVec = (T*)malloc(reserved *sizeof(T));

			//copy all elements left of pos to tempVec
			for(int i = 0; i< pos; i++) {
				new(&tempVec[i])T(elements[i]);
				elements[i].~T();
			}

			//copy rhs to pos
			new(tempVec+pos)T(rhs);

			//Copy all elements right of pos to tempVec
			for(int i  = count; i>pos; i--) {
				new(&tempVec[i])T(elements[i-1]);
				elements[i-1].~T();
			}
			count++;
			free(elements);

			//copy data back from tempVec
			elements = tempVec;
		}

		else {
			//Shift right elements to right of pos by 1
			for(int i = count; i>pos; i--)
			{
				new(&elements[i])T(elements[i-1]);
				elements[i-1].~T();
			}
			//copy new element in pos
			elements[pos].~T();
			new(&elements[pos])T(rhs);
			count++;
		}
	}
	cout<<"Insert complete"<<endl;
}


// Implement the iterators

// Constructors
template <typename T>
VectorIterator<T>::VectorIterator() {
	current = NULL;
}

template <typename T>
VectorIterator<T>::VectorIterator(T* c) {
	current = c;
}


// Copy constructor
template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator<T>& rhs) {
	current = rhs.current;
}


// Iterator defeferencing operator
template <typename T>
T& VectorIterator<T>::operator*() const {
	return *current;
}


// Prefix increment
template <typename T>
VectorIterator<T>  VectorIterator<T>::operator++ {
	current = current + 1;
	return *this;
}

// Postfix increment
template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int) {
	VectorIterator<T> old = *this;
	current = current + 1;
	return old;
}


// Comparison operators
template <typename T>
bool VectorIterator<T>::operator !=(const VectorIterator<T>& rhs) const {
	if(current!=rhs.current)
		return true;
	else
		return false;
	
}


template <typename T>
bool VectorIterator<T>::operator ==(const VectorIterator<T>& rhs) const {
	if(current == rhs.current)
		return true;
	else
		return false;
}




