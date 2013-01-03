/**
 * @file	CarsQueue.h
 * @brief	Defining the class CarsQueue
 *
 * @autor	Sorokovskiy Muchailo
 */

#ifndef CARS_QUEUE_H_
#define CARS_QUEUE_H_

#define MULT 1.6	// The coefficient reallocation memory to queue

#define ENUMERATION_BEGIN(arg) const char* const arg##_strs[] = {	// Character array elements of enum
#define DECLARE_MEMBER(arg) #arg
#include "Brand.h"
#include "Brand.h"

// Data structure of the car
struct Item
{
	char *name;						// Name of the owner
	Brand brand;					// Car brand
	unsigned short int year;		// Year of production car
	unsigned int color		: 24;	// Color of the car
	unsigned int milleage	: 24;	// Mileage
};

// Class Queuing for cars
class CarsQueue
{
private:
	bool compact;	// Attribute of compact data placement
	// The structure of element queue
	struct Node 
	{
		Item item;	// Data of the car
		Node *next;	// Pointer to the next element
	};
	char *front;	// Pointer to the front element of the queue
	char *rear;		// Pointer to the rear element of the queue

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
	* @param	[in]	*item The const pointer to the struct Item
	* @post		Returns false if unable to add an item
	* @return	bool
	*/
	bool Add ( const Item *item);

	/**
	* @brief	This method removes the tltment of the queue
	* @param	[out]	*item The pointer to the struct Item
	* @post		Returns false if unable to remove an item
	* @return	bool
	*/
	bool Del ( Item *item );

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