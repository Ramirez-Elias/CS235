/***********************************************************************
 * Header:
 *    Array
 * Summary:
 *    This class contains the notion of an array: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       array             : similar to std::array
 *       array :: iterator : an iterator through the array
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <cassert>  // because I am paranoid
#include <stack>
 // a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

	/************************************************
	 * STACK
	 * A class that holds stuff
	 ***********************************************/
	template <class T>
	class stack
	{
	public:
		// Default constructor
		stack() :data(NULL), numElements(0), num(0) { };

		// Non Default Constructor
		stack(int num)           throw (const char *);

		//copy constructor
		stack(const stack & rhs)        throw (const char *);

		//Destructor
		~stack() { if (num) delete[] data; }

		//Vector Assign
		stack& operator = (const stack & rhs) throw (const char *);

		// standard container interfaces
		// size
		int  size()     const { return numElements; }


		//added Capacity
		int  capacity() const { return num; }

		// empty
		bool  empty() const { return numElements == 0; }

		// clear
		void clear() { numElements = 0; }

		//push
		void push(const T &rhs);

		//pop
		void pop();

		//top
		T top();

		// specific interfaces
		// what would happen if I passed -1 or something greater than num?
		T & operator [] (int index)       throw (const char *)
		{
			return data[index];
		}
		const T & operator [] (int index) const throw (const char *)
		{
			return data[index];
		}

		// the various iterator interfaces
		class iterator;
		iterator begin() { return iterator(data); }
		iterator end();

		// the various const_iterator interfaces
		class const_iterator;
		const_iterator cbegin() const { return const_iterator(data); }
		const_iterator cend() const;

		// a debug utility to display the 
		// this gets compiled to nothing if NDEBUG is defined
		void display() const;

	private:
		T * data;              // dynamically allocated  of T
		int num;               // both the capacity and the number of elements
		int numElements;
		void resize(int &num);
	};


	/**********************************************
	 * STACK:: NON-DEFAULT CONSTRUCTOR
	 * Preallocate the stack to "capacity"
	 **********************************************/
	template <class T>
	stack <T> ::stack(int num) throw (const char *)
	{
		assert(num >= 0);

		// do nothing if there is nothing to do.
		if (num == 0)
		{
			this->num = this->numElements = 0;
			this->data = NULL;
			return;
		}

		// attempt to allocate
		try
		{
			data = new T[num];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate buffer for stack";
		}


		// copy over the stuff
		this->num = num;
		this->numElements = 0;

	}

	/*******************************************
	 * STACK::  COPY CONSTRUCTOR
	 *******************************************/
	template <class T>
	stack <T> ::stack(const stack<T> & rhs) throw (const char *)
	{
		assert(rhs.num >= 0);

		// do nothing if there is nothing to do
		if (rhs.num == 0)
		{
			num = numElements = 0;
			data = NULL;
			return;
		}

		// attempt to allocate
		try
		{
			data = new T[rhs.num];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate buffer";
		}

		// copy over the capacity
		assert(rhs.numElements >= 0 && rhs.numElements <= rhs.num);
		num = rhs.num;
		numElements = rhs.numElements;
		for (int i = 0; i < numElements; i++)
			data[i] = rhs.data[i];
	}


	/*******************************************
	 * STACK :: Assignment
	 *******************************************/
	template <class T>
	stack <T> & stack <T> :: operator = (const stack <T> & rhs)
		throw (const char *)
	{

		// attempt to allocate
		try
		{
			data = new T[rhs.num];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate buffer";
		}


		// copy over the capacity
		assert(rhs.numElements >= 0 && rhs.numElements <= rhs.num);
		num = rhs.num;
		numElements = rhs.numElements;
		for (int i = 0; i < numElements; i++)
			data[i] = rhs.data[i];

		return *this;
	}

	/*******************************************
	* VECTOR :: PUSH
	*******************************************/
	template<class T>
	void stack<T>::push(const T & rhs)
	{

		if (numElements == num)
		{
			resize(num);
		}

		data[numElements++] = rhs;


	}


	/**********************************************
	* stack: RESIZE
	* Increase Vector capacity
	**********************************************/
	template<class T>
	void stack<T>::resize(int &num)
	{
		stack <T> data_holder(num);


		for (int i = 0; i < numElements; ++i)
		{
			data_holder[i] = data[i];
		}
		delete[] data;

		if (num == 0)
		{
			num = num + 1;
		}

		num = num * 2;
		data = new T[num];



		for (int i = 0; i < numElements; ++i)
		{
			data[i] = data_holder[i];
		}


	}


	/*******************************************
	* STACK:: POP
	*******************************************/
	template<class T>
	void stack<T>::pop()
	{
		if (!empty())
		{
			--numElements;
		}
	}



	/*******************************************
	* STACK:: TOP
	*******************************************/
	template<class T>
	T stack<T>::top()
	{
		if (!empty())
		{
			return data[size() - 1];
		}

		else
		{
			throw "ERROR: Unable to reference the element from an empty Stack";
		}
		
	}


	/********************************************
	 * ARRAY : DISPLAY
	 * A debug utility to display the contents of the array
	 *******************************************/
	template <class T>
	void stack <T> ::display() const
	{
#ifndef NDEBUG
		std::cerr << "array<T>::display()\n";
		std::cerr << "\tnum = " << num << "\n";
		for (int i = 0; i < num; i++)
			std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
	}



	/**************************************************
	 * STACK ITERATOR
	 * An iterator through array
	 *************************************************/
	template <class T>
	class stack <T> ::iterator
	{
	public:
		// defaul constructors
		iterator() : p(NULL) {              }

		//
		iterator(T * p) : p(p) {              }
		//
		iterator(const iterator & rhs) { *this = rhs; }

		//asignment
		iterator & operator = (const iterator & rhs)
		{
			this->p = rhs.p;
			return *this;
		}

		// equals, not equals operator
		bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
		bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

		// dereference operator
		T & operator * () { return *p; }
		const T & operator * () const { return *p; }

		// prefix increment
		iterator & operator ++ ()
		{
			p++;
			return *this;
		}

		// postfix increment
		iterator operator ++ (int postfix)
		{
			iterator tmp(*this);
			p++;
			return tmp;
		}

		// prefix decrease
		iterator & operator -- ()
		{
			p--;
			return *this;
		}

		// postfix decrease
		iterator operator -- (int postfix)
		{
			iterator tmp(*this);
			p--;
			return tmp;
		}

	private:
		T * p;
	};


	/********************************************
	 *  STACK :: END
	 * Note that you have to use "typename" before
	 * the return value type
	 ********************************************/
	template <class T>
	typename stack <T> ::iterator stack <T> ::end()
	{
		return iterator(data + numElements);
	}

	/**************************************************
	* stack CONST_ITERATOR
	 * An iterator through array
	*************************************************/
	template <class T>
	class stack <T> ::const_iterator
	{
	public:
		// defaul constructors
		const_iterator() : p(NULL) {              }

		//
		const_iterator(T * p) : p(p) {              }
		//
		const_iterator(const const_iterator & rhs) { *this = rhs; }

		//asignment
		const_iterator & operator = (const const_iterator & rhs)
		{
			this->p = rhs.p;
			return *this;
		}

		// equals, not equals operator
		bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
		bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

		// dereference operator
		T & operator * () { return *p; }
		const T & operator * () const { return *p; }

		// prefix increment
		const_iterator & operator ++ ()
		{
			p++;
			return *this;
		}

		// postfix increment
		const_iterator operator ++ (int postfix)
		{
			const_iterator tmp(*this);
			p++;
			return tmp;
		}

		// prefix decrease
		const_iterator & operator -- ()
		{
			p--;
			return *this;
		}

		// postfix decrease
		const_iterator operator -- (int postfix)
		{
			const_iterator tmp(*this);
			p--;
			return tmp;
		}

	private:
		T * p;
	};


	/********************************************
	 *  stack :: CEND
	 * Note that you have to use "typename" before
	 * the return value type
	 ********************************************/
	template <class T>
	typename stack <T> ::const_iterator stack <T> ::cend() const
	{
		return const_iterator(data + numElements);
	}

}; // namespace custom

#endif // STACK_H


