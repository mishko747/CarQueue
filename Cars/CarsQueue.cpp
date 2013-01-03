/**
 * @file	CarsQueue.cpp
 * @brief	Realization methods of the class CarsQueue
 *
 * @autor	Sorokovskiy Muchailo
 */

#include <iostream>
#include "CarsQueue.h"

// Constructor without parameters
CarsQueue::CarsQueue ( void ) : compact( false ), front( NULL ), rear( NULL )
{
	// ...	
}

// Class destructor
CarsQueue::~CarsQueue ( void )
{
	if( compact == true )
	{
		delete[] (char *)front;
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
bool CarsQueue::Add ( const Item *item)
{
	std::cout<<"AddInComp\n";
	/*
	if( item == NULL )
	{
		return false;
	}


	Node *add;
	char *name;
	size_t len = strlen(item->name);

	try
	{
		add = new Node; 
		name = new char[ len + 1 ];
	}
	catch(...)
	{ 
		if( add != NULL)
		{
			delete add;
		}
		return false; 
	}

	memcpy( name, item->name, len + 1 );
	memcpy(	(void *)&(add->item), item, sizeof(Item) );
	add->item.name = name;

	add->next = NULL;
	
	if( front == NULL )
	{
		front = add;
	}
	else
	{
		rear->next = add;
	}
	rear = add;
	*/
	return true;
}

// This method removes the tltment of the queue
bool CarsQueue::Del ( Item *item )
{
	/*
	if( front == NULL )
	{
		return false;
	}

	char *name;
	size_t len = strlen(front->item.name);
	
	try
	{
		if( item != NULL )
		{
			if( item->name != NULL )
			{
				delete[] item->name;
			}
		}
		else
		{
			item = new Item;
		}
		name = new char[ len + 1 ];
	}
	catch(...)
	{
		return false;
	}
	memcpy( name, front->item.name, len + 1 );
	memcpy(	item, (void *)&(front->item), sizeof(Item) );
	item->name = name;
	
	Node *temp = front;
	front = front->next;
	delete temp;
	if( front == NULL )
	{
		rear = NULL;
	}
	*/
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
	/*
	Node *temp = (Node *)front;
	cout<< "Elements of the queue:\n";
	do
	{
		cout<< "-------------------------------\n";
		cout<< "ADDR Node:\t"	<< (void*)temp					<< endl;
		cout<< "ADDR Item:\t"	<< &(temp->item)				<< endl;
		cout<< "Name: \t"		<< temp->item.name				<< endl;
		cout<< "Brand:\t"		<< Brand_strs[temp->item.brand]	<< endl;
		cout<< "Year: \t"		<< temp->item.year				<< endl;
		cout<< "Color:\t"		<< temp->item.color				<< endl;
		cout<< "Mileage:"		<< temp->item.milleage			<< endl;
		cout<< "-------------------------------\n";
	}
	while( (temp = temp->next) != NULL );
	*/
	cout<< "End output.\n";
}

// This method places elements of the queue successively in the memory
bool CarsQueue::Compact ( void )
{
	if( front == NULL )
	{
		return false;
	}

	/*
	char *cFront;
	char *cRear;

	try
	{
		cFront = new char[10000];
	}
	catch(...)
	{
		return false;
	}
/*
	Node *temp = front;
	char *currPtr = cFront;

	size_t len;
	const size_t sizeOfItem = sizeof(Item);
	
	do
	{
		cRear = currPtr;
		len = strlen(temp->item.name) + 1U;
		memcpy( currPtr, temp->item.name, len );
		currPtr += len;
		memcpy( ++currPtr, &(temp->item.brand), sizeOfItem - 4U );
		currPtr += (sizeOfItem - 3U);
	}
	while( (temp = temp->next) != NULL );
	
	std::cout<< "cFront:" <<(void*)cFront << std::endl;
	std::cout<< "cRear:" <<(void*)cRear << std::endl;

	do
	{
		temp = front;
		front = front->next;
		delete[] temp->item.name;
		delete temp;
	}
	while( front != NULL );
	rear = NULL;
*/
	return true;
}

// This method places the elements the queue in memory randomly
bool CarsQueue::Incompact ( void )
{
	//.....
	return false;
}