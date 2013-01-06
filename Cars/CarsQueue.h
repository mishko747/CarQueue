/**
 * @file	CarsQueue.h
 * @brief	Defining the class CarsQueue
 *
 * @autor	Sorokovskiy Muchailo
 */

#ifndef CARS_QUEUE_H_
#define CARS_QUEUE_H_

#define MULT 1.6	// The coefficient reallocation memory to queue
#define AVR_NAME_LEN 15	// Average name length

#define ENUMERATION_BEGIN(arg) const char* const arg##_strs[] = {	// Character array elements of enum
#define DECLARE_MEMBER(arg) #arg
#include "Brand.h"
#include "Brand.h"


// Data structure of the car
#pragma pack(push, 1)
struct Item
{
	char *name;						// Name of the owner
	Brand brand;					// Car brand
	unsigned long long int year		: 16;	// Year of production car
	unsigned long long int color	: 24;	// Color of the car
	unsigned long long int milleage	: 24;	// Mileage
};
#pragma pack(pop)

// Class Queuing for cars
class CarsQueue
{
private:
	size_t sizeArr;	// Flag of compact data placement and the numbers of bytes are allocated for data
	
	// The structure of element queue
	struct Node 
	{
		Item item;	// Data of the car
		Node *next;	// Pointer to the next element
	};
	char *front;	// Pointer to the front element of the queue
	char *rear;		// Pointer to the rear element of the queue

	/**
	* @brief	This method allocates memory for the array to queue
	* @post		Returns false if reallocation failed
	* @return	bool
	*/
	inline bool Realloc ( void );


public:

	/**
	* @brief	Constructor without parameters
	* @post		Initializes pointers to the first and last elements of the queue, and the way placing elements
	*/
	CarsQueue(void);

	/**
	* @brief Class destructor
	*/
	~CarsQueue(void);

	/**
	* @brief	This method adds the element to the compact queue
	* @param	[in]	item The const pointer to the struct Item
	* @post		Returns false if unable to add an item
	* @return	bool
	*/
	bool Add ( const Item & item);

	/**
	* @brief	This method removes the tltment of the queue
	* @post		Returns false if unable to remove an item
	* @return	bool
	*/
	bool Del ( void );

	/**
	* @brief	This method displays information about the car in the queue
	* @return	void
	*/
	void Output ( void ) const;
	
	/**
	* @brief	This method places elements of the queue successively in the memory
	* @post		Returns false if the conversion queue is failed 
	* @return	bool
	*/
	bool Compact ( void );

	/**
	* @brief	This method places the elements the queue in memory randomly
	* @post		Returns false if the conversion queue is failed 
	* @return	bool
	*/
	bool Incompact ( void );
};

#endif /* CARS_QUEUE_H_ */