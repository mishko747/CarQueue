/**
 * @file	QCars.cpp
 * @brief	Realization methods of the class QCars
 *
 * @autor	Sorokovskiy Muchailo
 */

#include "QCars.h"

#include <iostream>
#include <new>

// Constructor without parameters
QCars::QCars ( bool compact ) :  QArrSize( 0U )
{
	if( compact == false )
	{
		nFront = NULL;
		nRear = NULL;
	}
	else
	{
		QArrSize = INITIAL_SIZE_QUEUE * ( AVR_NAME_LEN + sizeof(Item) );	// Calculate the initial size of the array
		cFront = new char[ QArrSize ];
		cRear = cFront + SERVICE_DATA_SIZE;	// A pointer to end of the queue
	
		Shift *s = new(cFront) Shift;
		s->Beg = SERVICE_DATA_SIZE;		// Shift from the beginning of the array to the begining of the queue
		s->End = SERVICE_DATA_SIZE;		// Shift from the end of the array to the end of the queue
	}
}

// Class destructor
QCars::~QCars ( void )
{
	if( QArrSize != 0U )
	{
		delete[] cFront;
	}
	else
	{
		Node *tmp;
		while( nFront != NULL )
		{
			tmp = nFront;
			nFront = nFront->next;
			delete[] tmp->item.name;
			delete tmp;
		}
	}
}

//This method allocates memory for the array to queue
inline bool QCars::Realloc ( void )
{
	std::cout<< "REALLOC\n";

	Shift *s = new(cFront) Shift;
	const size_t DATA_SIZE = s->End - s->Beg;

	if( DATA_SIZE / (float)QArrSize > MAX_FILLING )	// If the array is filled with more than DIV
	{
		QArrSize = (size_t)(QArrSize * MULT);	// Increasing the size of array
	}
	else
	{
		if(	DATA_SIZE / (float)QArrSize < MIN_FILLING )
		{
			QArrSize = (size_t)(QArrSize / MULT);	// Reduction the size of array
		}
	}

	std::cout<< "REALLOC QArrSize: " << QArrSize << std::endl;

	// Allocate memory for the array
	char *tmp = cFront;
	try
	{
		cFront = new char[ QArrSize ];
	}
	catch( std::bad_alloc )
	{
		cFront = tmp;
		return false;
	}
	memcpy( cFront + SERVICE_DATA_SIZE,	tmp + s->Beg, DATA_SIZE );	// Copying queue data
	s->End = SERVICE_DATA_SIZE + DATA_SIZE;
	s->Beg = SERVICE_DATA_SIZE;
	cRear = cFront + s->End;
	memcpy( cFront, tmp, SERVICE_DATA_SIZE );	// Saving service data
	delete[] tmp;
	return true;
}

// This method adds the element to the normal queue
bool QCars::AddNormal ( const Item & item )
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

	if( nFront == NULL )
	{
		nFront = add;
	}
	else
	{
		nRear->next = add;
	}
	nRear = add;

	return true;
}

// This method adds the element to the compact queue
bool QCars::AddCompact ( const Item & item )
{
	if( QArrSize == 0U )
	{
		return false;
	}

	Shift *s = new(cFront) Shift;
	size_t lenName = strlen( item.name ) + 1U;

	// If the element is not placed in allocated memory
	if( s->End + lenName + DATA_ITEM_SIZE >= QArrSize )
	{
		if( Realloc() == false )
		{
			return false;
		}
		s = new(cFront) Shift;
	}

	memcpy( cRear, item.name, lenName );
	cRear += lenName;
	memcpy( cRear, &item.brand, DATA_ITEM_SIZE );
	cRear += DATA_ITEM_SIZE;

	s->End = cRear - cFront;
	return true;
}

// This method removes the tltment of the normal queue
bool QCars::DelNormal ( void )
{
	if( nFront == NULL )
	{
		return false;
	}

	Node *temp = nFront;
	nFront = nFront->next;

	delete temp;
	if( nFront == NULL )
	{
		nRear = NULL;
	}
	return true;
}

// This method removes the tltment of the compact queue
bool QCars::DelCompact ( void )
{
	Shift *s = new(cFront) Shift;
	if( QArrSize == 0U ||  s->Beg == s->End)
	{
		return false;
	}
	s->Beg = s->Beg + strlen( cFront + s->Beg ) + 1U + DATA_ITEM_SIZE;
	return true;
}

// This method displays information about the car in the normal queue
void QCars::OutputNormal ( void ) const
{
	using std::cout;
	using std::endl;
	
	if( nFront == NULL )
	{
		cout<<"Normal queue is empty.\n";
		return;
	}

	cout<< "Elements of the normal queue:\n";
	Node *temp = nFront;
	do
	{
		cout<< "-------------------------------"
			<< "\nADDR Item:\t"	<< &(temp->item)
			//<< "\nName: \t"		<< temp->item.name
			//<< "\nBrand:\t"		<< Brand_strs[temp->item.brand]
			//<< "\nYear: \t"		<< temp->item.year
			//<< "\nColor:\t"		<< temp->item.color
			//<< "\nMileage:"		<< temp->item.milleage
			<< "\n-------------------------------\n";
	}
	while( (temp = temp->next) != NULL );
	cout<< "End of the queue.\n";
}
	
// This method displays information about the car in the compact queue
void QCars::OutputCompact ( void ) const
{
	using std::cout;
	using std::endl;
	
	Shift *s = new( cFront ) Shift;
	char *tmp = cFront + s->Beg;
	if( QArrSize == 0U || cRear == tmp )
	{
		cout<<"Compact queue is empty.\n";
		return;
	}

	size_t lenName;
	Item *item;
	const size_t SIZE_T = sizeof(size_t);

	cout<< "Elements of the compact queue:\n";
	do
	{
		lenName = strlen( tmp ) + 1U;
		cout<< "-------------------------------\n"
			<< "ADDR Item:\t"	<< (void*)tmp					<< endl
			<< "Name: \t"		<< tmp							<< endl;
		tmp += lenName;
		item = new(tmp - SIZE_T) Item;	// Overlay structure an item on top of the array 
		cout<< "Brand:\t"		<< Brand_strs[item->brand]	<< endl
			<< "Year: \t"		<< item->year				<< endl
			<< "Color:\t"		<< item->color				<< endl
			<< "Mileage:"		<< item->milleage
			<< "\n-------------------------------\n";
		tmp += DATA_ITEM_SIZE;
	}
	while( tmp != cRear );
	cout<< "End of the queue.\n";
}

// This method places elements of the queue successively in the memory
bool QCars::Compact ( void )
{
	if( QArrSize != 0U || nFront == NULL )	// If the queue is compact or empty
	{
		return false;
	}

	Node *tmpFront = nFront;	// Backup
	Node *tmp = nFront;

	// Calculating the count of elements
	size_t count = 1U;	
	while( (tmp = tmp->next) != NULL )	count++;

	// Calculating array size to store compact queue
	QArrSize = count * (size_t)( ( sizeof(Item) + AVR_NAME_LEN) * MULT );	
	
	// Allocation of memory to store compact queue
	try
	{
		cFront = new char[ QArrSize ];	// Allocate memory for the array
	}
	catch(...)
	{
		QArrSize = 0U;
		nFront = tmpFront;
		return false;
	}
	
	Shift *s = new( cFront ) Shift;
	s->Beg = SERVICE_DATA_SIZE;
	s->End = SERVICE_DATA_SIZE;

	// Copying data
	Node *tmpRear = nRear;				// Backup
	cRear = cFront + SERVICE_DATA_SIZE;	// Setting the pointer to end of the queue

	size_t lenName;
	tmp = tmpFront;
	do
	{
		lenName = strlen(tmp->item.name) + 1U;	// Calculating the length of the field "name"
	
		if( s->End + lenName + DATA_ITEM_SIZE >= QArrSize ) // If the element is not placed in allocated memory
		{
			if( Realloc() == false )	// If memory reallocation failure
			{														
				delete[] cFront;
				cFront = NULL;
				tmp->next = NULL;	// End of cycle
				continue;
			}
			s = new(cFront) Shift;
		}
		memcpy( cRear, tmp->item.name, lenName );
		cRear += lenName;
		memcpy( cRear, &(tmp->item.brand), DATA_ITEM_SIZE );
		cRear += DATA_ITEM_SIZE;
		s->End = cRear - cFront;
	}
	while( (tmp = tmp->next) != NULL );

	// If the conversion failed - restore the original state of the queue
	if( cFront == NULL )
	{
		QArrSize = 0U;
		nFront = tmpFront;
		nRear = tmpRear;
		return false;
	}

	// Remove the normal queue
	tmp = tmpFront;
	while( tmpFront != NULL )
	{
		tmp = tmpFront;
		tmpFront = tmpFront->next;
		delete[] tmp->item.name;
		delete tmp;
	}
	return true;
}

// This method places the elements the queue in memory randomly
bool QCars::InCompact ( void )
{
	if( QArrSize == 0U || cFront == NULL )
	{
		return false;
	}
	
	Shift *s = new (cFront) Shift;
	if( s->Beg == s->End )	// If the queue is not empty
	{
		return false;
	}
	Node *tmpFront;
	char *tmp = cFront + s->Beg;	// Setting the pointer to the first byte queue
	try
	{
		// Creating a temporary first element queue
		tmpFront = new Node;		
		tmpFront->item.name = new char[1U];
	}
	catch(...)
	{
		return false;
	}
		
	Node *add;						// Aointer to the new element that is added
	size_t lenName;					// Length of the field "name"

	Node *tmpRear = tmpFront;
	while( tmp != cRear )			// Until the pointer to the first byte of the queue 
	{								// is not equal pointer to the last byte queue	
		try
		{
			// Memory allocation for the new element
			add = new Node;
			lenName = strlen( tmp ) + 1U;
			add->item.name = new char[lenName];
		}
		catch(...)
		{
			// Remove the new item
			if( add != NULL)
			{
				if( add->item.name != NULL )
				{
					delete[] add->item.name;
				}
				delete add;
			}
			add = NULL;		// Sign of crash
			tmp = cRear;	// Out of the cycle
			continue;
		}	// End of Catch(...)

		// Copying data from the array to a new element
		memcpy( add->item.name, tmp, lenName );
		tmp += lenName;
		memcpy( &add->item.brand, tmp, DATA_ITEM_SIZE );
		tmp += DATA_ITEM_SIZE;
		add->next = NULL;

		// Adding a new element to the queue
		tmpRear->next = add;
		tmpRear = add;
	}	// End of while( tmp != cRear )
	
	if( add == NULL )	// If crash
	{
		// Deleting built queue
		do
		{
			add = tmpFront;
			tmpFront = tmpFront->next;
			delete[] add->item.name;
			delete add;
		}
		while( tmpFront != NULL );
		return false; 
	}

	// Deleting a temporary first element queue
	add = tmpFront;
	tmpFront = tmpFront->next;
	delete[] add->item.name;
	delete add;

	delete[] cFront;	// Deleting compact array queue
	QArrSize = 0U;		// Sign of the normal queue

	// Saving pointers to the front and rear of the queue
	nFront = tmpFront;
	nRear = tmpRear;
	return true;
}