/**
 * @file	QCars.h
 * @brief	Defining the class QCars
 *
 * @autor	Sorokovskiy Muchailo
 */

#ifndef Q_CARS_H_
#define Q_CARS_H_

#define INITIAL_SIZE_QUEUE 10U
#define MULT 1.6	// The coefficient reallocation memory to queue
#define MAX_FILLING 0.8 // The filling coeficient where make changes the size of the array
#define MIN_FILLING 0.4 // The filling coeficient where make changes the size of the array
#define AVR_NAME_LEN 15	// Average name length


#define ENUMERATION_BEGIN(arg) const char* const arg##_strs[] = {	// Character array elements of enum
#define DECLARE_MEMBER(arg) #arg
#include "Brand.h"
#include "Brand.h"

#pragma pack(push, 1)
// Shift from the beginning of the array
struct Shift
{
	size_t Beg;	// to begin of the queue
	size_t End;	// to end of the queue
};
const size_t SERVICE_DATA_SIZE = sizeof(Shift); // Size of service data in an array

// Data structure of the car
struct Item
{
	char *name;						// Name of the owner
	Brand brand;					// Car brand
	unsigned long long int year		: 16;	// Year of production car
	unsigned long long int color	: 24;	// Color of the car
	unsigned long long int milleage	: 24;	// Mileage
};
#pragma pack(pop)

// Size of the structure "Item" without the pointer to the field "name"
const size_t DATA_ITEM_SIZE = sizeof(Item) - sizeof(char*);

// Class Queuing for cars
class QCars
{
private:
	size_t QArrSize;	// Flag of compact data placement and the numbers of bytes are allocated for data
	
	// The structure of element queue
	struct Node 
	{
		Item item;	// Data of the car
		Node *next;	// Pointer to the next element
	};

	union
	{
		Node *nFront;
		char *cFront;
	};

	union
	{
		Node *nRear;
		char *cRear;
	};

	inline bool Realloc ( void );

	bool AddNormal ( const Item & item );
	bool AddCompact ( const Item & item );

	bool DelNormal ( void );
	bool DelCompact ( void );

	void OutputNormal ( void ) const;
	void OutputCompact ( void ) const;

public:
	
	/**
	* @brief	Constructor without parameters
	* @post		Initializes pointers to the first and last elements of the queue, and the way placing elements
	*/
	QCars ( bool compact = false );

	/**
	* @brief Class destructor
	*/
	~QCars ( void );
	// This function selects a method according to some queue state
	inline bool AddItem ( const Item & item )
	{
		return QArrSize == 0U ? AddNormal( item ) : AddCompact( item );
	}
	// This function selects a method according to some queue state
	inline bool DelItem ( void )
	{
		return QArrSize == 0U ? DelNormal() : DelCompact();
	}
	// This function selects a method according to some queue state
	inline void Output ( void )
	{
		return QArrSize == 0U ? OutputNormal() : OutputCompact();
	}
	bool Compact ( void );
	bool InCompact ( void );
};

#endif /* Q_CARS_H_ */