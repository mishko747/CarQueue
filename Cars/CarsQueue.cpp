/**
 * @file	CarsQueue.cpp
 * @brief	Realization methods of the class CarsQueue
 *
 * @autor	Sorokovskiy Muchailo
 */

#include <iostream>
//#include <new.h>
#include "CarsQueue.h"


//This method allocates memory for the array to queue
inline bool CarsQueue::Realloc ( void )
{
	char *tmpFront;
	try
	{
		tmpFront = new char[(size_t)(sizeArr * MULT)];
		memcpy(tmpFront, front, sizeArr);
	}
	catch(...)
	{
		return false;
	}
	delete[] front;
	front = tmpFront;
	return true;
}

// Constructor without parameters
CarsQueue::CarsQueue ( void ) :  sizeArr( 0 ), front( NULL ), rear( NULL )
{
	// ...	
}

// Class destructor
CarsQueue::~CarsQueue ( void )
{
	if( sizeArr > 0 )
	{
		delete[] front;
		return;
	}

	Node *temp;
	Node *fr = (Node *)front;

	while( fr != NULL )
	{
		temp = fr;
		fr = fr->next;
		delete[] temp->item.name;
		delete temp;
	}
}

// This method adds the element to the queue
bool CarsQueue::Add ( const Item & item )
{
	if( sizeArr == 0 )
	{
		Node *add;	// New node
		size_t len;	// Length of the field "name"

		try
		{
			len = strlen( item.name );
			add = new Node;
			// Copying structure without field "name"
			memcpy(	&add->item.brand, &item.brand, sizeof(Item) );
			add->item.name = new char[len + 1U];
			// Copying field of "name"
			memcpy( add->item.name, item.name, len + 1U );
			add->next = NULL;
		}
		catch(...)
		{ 
			if( add != NULL)
			{
				if( add->item.name != NULL )
				{
					delete[] add->item.name;
				}
				delete add;
			}
			return false; 
		}	// End of catch(...)

		if( front == NULL )
		{
			front = (char *)add;
		}
		else
		{
			((Node *)rear)->next = add;
		}
		rear = (char *)add;
	}
	else	// if( sizeArr == 0 )
	{
		size_t lenName = strlen(item.name) + 1U;
		size_t *lenQ = (size_t *)front;
		size_t sizeOfItem = sizeof(Item) - 4U;

		if( *lenQ + lenName + sizeOfItem > sizeArr ) // If the element is not placed in allocated memory
		{
			if( Realloc() == false )	// If memory reallocation is successful
			{
				return false;
			}
		}
		rear = front + *lenQ + 1U;
		memcpy(rear, item.name, lenName);
		memcpy(rear + lenName, &item.brand, sizeof(Item) - 4);
		*lenQ += lenName + sizeOfItem;	// Save length
	}	// End else if( sizeArr == 0 )

	return true;
}

// This method removes the tltment of the queue
bool CarsQueue::Del ( void )
{
	if( front == NULL )
	{
		return false;
	}

	if( sizeArr == 0 )
	{
		Node *temp = (Node *)front;
		temp = temp->next;

		delete (Node *)front;
		if( temp == NULL )
		{
			front = NULL;
			rear = NULL;
		}
		else
		{
			front = (char *)temp;
		}
	}
	else	// else if( sizeArr == 0 )
	{
		if(rear == front + 4U)
		{
			*(size_t*)front = 4U;
			rear = NULL;
			return true;
		}
		size_t lenDel = strlen(front + 5U) + 1U + sizeof(Item) - 4U;	// Size of the first element

		char *temp = front;	
		front += lenDel;								// Shift the pointer to the front queue
		*(size_t*)front = *(size_t*)temp - lenDel;		// Calculate the new size of the queue

//		char *ttt = new(temp) char[lenDel];

	//	delete[] ttt;					// Free memory
	}	// End if( sizeArr == 0 )

	return true;
}

// This method displays information about the car in the queue
void CarsQueue::Output ( void ) const
{
	using std::cout;
	using std::endl;
	
	if( front == NULL )
	{
		cout<<"Queue is empty.\n";
		return;
	}

	cout<< "Elements of the queue:\n";
	if( sizeArr == 0 )
	{
		Node *temp = (Node *)front;
		do
		{
			cout<< "-------------------------------\n";
			cout<< "ADDR Item:\t"	<< &(temp->item)				<< endl;
			cout<< "Name: \t"		<< temp->item.name				<< endl;
			cout<< "Brand:\t"		<< Brand_strs[temp->item.brand]	<< endl;
			cout<< "Year: \t"		<< temp->item.year				<< endl;
			cout<< "Color:\t"		<< temp->item.color				<< endl;
			cout<< "Mileage:"		<< temp->item.milleage			<< endl;
			cout<< "-------------------------------\n";
		}
		while( (temp = temp->next) != NULL );
	}
	else
	{
		char *temp = front + 5;	// Address of the front element of the queue
		Item *item;
		size_t lenName;	

		const size_t sizeOfItem = sizeof(Item) - 4;  // Size of the structure without the pointer to the field "name"

		do
		{
			lenName = strlen(temp) + 1;
			item = new(temp + lenName - 4) Item;	// Overlay structure on an array of characters
			cout<< "-------------------------------\n";
			cout<< "ADDR Item:\t"	<< (void *)temp				<< endl;
			cout<< "Name: \t"		<< temp						<<endl;
			cout<< "Brand:\t"		<< Brand_strs[item->brand]	<< endl;
			cout<< "Year: \t"		<< item->year				<< endl;
			cout<< "Color:\t"		<< item->color				<< endl;
			cout<< "Mileage:"		<< item->milleage			<< endl;
			cout<< "-------------------------------\n";
			temp += lenName + sizeOfItem;	// Shift pointer to the next element
		}
		while( temp <= rear );	
	}
	cout<< "End output.\n";
}

// This method places elements of the queue successively in the memory
bool CarsQueue::Compact ( void )
{
	if( front == NULL )
	{
		return false;
	}

	// Calculating the number of elements
	size_t count = 1;	
	Node *nFront = (Node *)front;

	while( (nFront = nFront->next) != NULL )
	{
		count++;
	}
	nFront = (Node *)front;	// For recovery in case of conversion errors

	// Allocation of memory to store a queue
	try
	{
		sizeArr = count * (sizeof(Item) + AVR_NAME_LEN) * MULT;	// Array size to store a queue
		front = new char[ sizeArr ];
	}
	catch(...)
	{
		sizeArr = 0;
		front = (char *)nFront;
		return false;
	}

	size_t *lenList = (size_t *)front;	// Pointer to the first four bytes of the array (to store size used memory)
	*lenList = 4U;						// amount of used memory = 4 bytes

	Node *nRear = (Node *)rear;	// For recovery in case of conversion errors
	Node *temp = nFront;

	size_t lenName;
	const size_t sizeOfItem = sizeof(Item) - 4U;	// Size of the structure without the pointer to the field "name"

	// Copying data
	do
	{
		lenName = strlen(temp->item.name) + 1U;
	
		if( lenName + sizeOfItem + *lenList >= sizeArr ) // If the element is not placed in allocated memory
		{
			if( Realloc() == true )	// If memory reallocation is successful
			{
				lenList = (size_t *)front;
			}
			else
			{
				delete[] front;
				front = NULL;
				temp->next = NULL;	// End of cycle
				continue;
			}
		}
		rear = front + *lenList + 1;
		memcpy( rear, temp->item.name, lenName );
		memcpy( rear + lenName, &(temp->item.brand),  sizeOfItem);
		*lenList += lenName + sizeOfItem;	
	}
	while( (temp = temp->next) != NULL );

	if( front == NULL )
	{
		sizeArr = 0;
		front = (char *)nFront;
		return false;
	}

	// Remove the queue
	do
	{
		try
		{
			temp = nFront;
			nFront = nFront->next;
			delete[] temp->item.name;
			delete temp;
		}
		catch(...)
		{
			// continue;
		}
	}
	while( nFront != NULL );
	
	return true;
}

// This method places the elements the queue in memory randomly
bool CarsQueue::Incompact ( void )
{
	//.....
	return false;
}