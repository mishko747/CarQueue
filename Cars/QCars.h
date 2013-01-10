/**
 * @file	QCars.h
 * @brief	Defining the class QCars
 *
 * @autor	Sorokovskiy Muchailo
 */

#ifndef Q_CARS_H_
#define Q_CARS_H_

#define INITIAL_SIZE_QUEUE 10U	// Initial number of elements queue
#define MULT 1.6				// The coefficient reallocation memory to queue
#define MAX_FILLING 0.8			// The filling coeficient where make changes the size of the array
#define MIN_FILLING 0.4			// The filling coeficient where make changes the size of the array
#define AVR_NAME_LEN 15			// Average name length


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

// Size of service data in an array
const size_t SERVICE_DATA_SIZE = sizeof(Shift); 
// Size of the structure "Item" without the pointer to the field "name"
const size_t DATA_ITEM_SIZE = sizeof(Item) - sizeof(char*);


Item* InputItem ( void );


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

	// Pointer to the front element of the queue
	union
	{
		Node *nFront;	// for normal queue
		char *cFront;	// for compact queue
	};
	// Pointer to the rear element of the queue
	union
	{
		Node *nRear;	// for normal queue
		char *cRear;	// for compact queue
	};

	/**
	* @brief	This method allocates memory for the array element placement queue
	* @post		Returns false if allocates failed
	* @return	bool
	*/
	inline bool Realloc ( void );

	/**
	* @brief	This method adds a new element to the normal queue
	* @param	[in]	item The reference to the data structure of the car
	* @return	bool
	*/
	bool AddNormal ( const Item & item );

	/**
	* @brief	This method adds a new element to the compact queue
	* @param	[in]	item The reference to the data structure of the car
	* @return	bool
	*/
	bool AddCompact ( const Item & item );

	/**
	* @brief	This method removes the element with normal queue
	* @post		Returns false if removing failed
	* @return	bool
	*/
	bool DelNormal ( void );

	/**
	* @brief	This method removes the element with compact queue
	* @post		Returns false if removing failed
	* @return	bool
	*/
	bool DelCompact ( void );

	/**
	* @brief	This method displays data element of normal queue on the screen
	* @return	void
	*/
	void OutputNormal ( void ) const;
	
	/**
	* @brief	This method displays data element of compact queue on the screen
	* @return	void
	*/
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

	/**
	* @brief	This method provides a method call, according to the state of the queue
	* @param	[in]	item The reference to the data structure of the car
	* @post		Return the value of called function
	* @return	bool
	*/
	inline bool AddItem ( const Item & item )
	{
		return QArrSize == 0U ? AddNormal( item ) : AddCompact( item );
	}

	/**
	* @brief	This method provides a method call, according to the state of the queue
	* @post		Return the value of called function
	* @return	bool
	*/
	inline bool DelItem ( void )
	{
		return QArrSize == 0U ? DelNormal() : DelCompact();
	}

	/**
	* @brief	This method provides a method call, according to the state of the queue
	* @post		Return the value of called function
	* @return	void
	*/
	inline void Output ( void )
	{
		return QArrSize == 0U ? OutputNormal() : OutputCompact();
	}

	/**
	* @brief	This method places the elements of the queue in memory row
	* @post		Returns false if the conversion failed
	* @return	bool
	*/
	bool Compact ( void );

	/**
	* @brief	This method places the elements of the queue in memory randomly
	* @post		Returns false if the conversion failed
	* @return	bool
	*/
	bool InCompact ( void );
};

#endif /* Q_CARS_H_ */