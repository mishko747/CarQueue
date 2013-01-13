/**
 * @file	Item.h
 * @brief	Defining the struct Item, constants and functions
 *
 * @autor	Sorokovskiy Muchailo
 */


#ifndef ITEM_H_
#define ITEM_H_

#define ENUMERATION_BEGIN(arg) const char* const arg##_strs[] = {	// Character array elements of enum
#define DECLARE_MEMBER(arg) #arg
#include "Brand.h"
#include "Brand.h"

#define MAX_NAME_LEN 20U		// Max name length
#define AVR_NAME_LEN 10U		// Average name length
#define MAX_BRAND_LEN 15U		// Max brand length
#define CURRENT_YEAR 2012U		// Current year

#pragma pack(push, 1)
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
const size_t DATA_ITEM_SIZE = sizeof(Item) - sizeof(void*);

/**
* @brief	This function provides input from the keyboard string
* @param	[in, out]	str Pointer to an array of characters
* @param	[in]	max Maximum length of string
* @return	void
*/
void InputStr ( char *&str, const size_t maxLen );

/**
* @brief	This function provides input from the keyboard unsigned integer number
* @param	[in]	max Maximum acceptable value for input
* @return	unsignde int
*/
unsigned int InputUInt ( const unsigned int max );

/**
* @brief	This function provides input data of structure "Item" from the keyboard
* @param	[in, out]	item Link structure "Item"
* @post		Returns a pointer to the structure
* @return	bool
*/
bool InputItem ( Item & item );

#endif /* ITEM_H_ */