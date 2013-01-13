/**
 * @file	QCars.cpp
 * @brief	Realization functions to work with the structure Item
 *
 * @autor	Sorokovskiy Muchailo
 */

#include "Item.h"
#include <iostream>

// This function provides input from the keyboard string
void InputStr ( char *&buff, const size_t maxLen )
{
	using std::cin;
	using std::cout;

	if( buff == NULL)
	{
		buff = new char[ maxLen + 1U ];
	}

	cout << "Please enter the string: ";

	cin.clear();	// Cleaning state of stream
	cin.sync();		// Clearing buffer stdin

	// If a problem input or the user has introduced many characters
	while( cin.getline( buff, maxLen + 1U ).fail() == true || buff[0] == '\0' )
	{
		if( buff[0] == '\0' )
		{
			cout<< "Field can not be empty!\n";
		}
		else
		{
			cout<< "Exceeded maximum number of characters!\n";
		}
		cout<< "Please re-enter: ";
		cin.clear();	// Cleaning state of stream
		cin.sync();		// Clearing buffer stdin
	}
}

// This feature provides input from the keyboard unsigned integer number
unsigned int InputUInt ( const unsigned int max )
{
	using std::cout;
	using std::cin;

	unsigned int temp;

	cout << "Please enter the number: ";

	cin.clear();	// Cleaning state of stream
	cin.sync();		// Clearing buffer stdin
	while( !(cin >> temp) || cin.get() != '\n' || temp > max )	// If entered incorrect data
	{
		cout<< "Incorrectly entered data or exceeded the maximum value!\n";
		cout<< "Please re-enter: ";
		cin.clear();	// Cleaning state of stream
		cin.sync();		// Clearing buffer stdin
	}
	return temp;
}

// This function provides input data of structure "Item" from the keyboard
bool InputItem ( Item & item )
{
	using std::cout;
	using std::cin;
	using std::endl;
	
	char *buff = NULL;
	//Item *item = NULL;		// Pointer to a structure that will be initialized with keyboard

	cin.exceptions( std::ios::badbit );

	try
	{
		try
		{
			cout << "\n--->\tEntering the name of car owner\t<---\n";
			cout << "String length should not exceed " << MAX_NAME_LEN << " characters.\n";
			InputStr( buff, MAX_NAME_LEN );
		
			size_t lenName = strlen( buff );	// Length of the string that the user entered

			//item = new Item;	// Dynamic memory allocation for structure
			item.name = new char[ lenName + 1U ];
			
			memcpy( item.name, buff, lenName + 1U );	// Copy owner name of the car with buffer in structure

			delete[] buff;
			buff = NULL;

			cout << "\n--->\tEntering the car brand\t<---\n";
			cout << "Sting length should not exceed " << MAX_BRAND_LEN << " characters.\n";

			unsigned int i = BEGIN;
			item.brand = END;
			do
			{
				InputStr( buff, MAX_BRAND_LEN );	// Enter car brand
				i = BEGIN;
				
				while( i < END )
				{
					++i;
					if( strcmp( buff, Brand_strs[i] ) == 0 )
					{
						item.brand = (Brand)i;
					}
				}
				if( item.brand == END )	// If the value has not changed
				{
					cout<< "This brand is not in the database!\n";
					cout<< "Please re-enter: ";
				}
			}
			while( item.brand == END );
	
			delete[] buff;
			buff = NULL;

			cout << "\n--->\tEntering the car year\t<---\n";
			cout << "Number can not exceed " << CURRENT_YEAR << ".\n";
			item.year = InputUInt( CURRENT_YEAR );

			unsigned char* rgb = new( (char*)&item + sizeof(item.name) + sizeof(item.brand) + 2U ) unsigned char[1U];

			cout << "\n--->\tEntering the car color\t<---\n";
			cout << "Numbers can not exceed " << UCHAR_MAX << ".\n";
			cout << "Entering the R.\n";
			*rgb = InputUInt( UCHAR_MAX );
			rgb++;
			cout << "Entering the G.\n";
			*rgb = InputUInt( UCHAR_MAX );
			rgb++;
			cout << "Entering the B.\n";
			*rgb = InputUInt( UCHAR_MAX );

			cout << "\n--->\tEntering the car milleage\t<---\n";
			item.milleage	= 0U;
			item.milleage	= ~(item.milleage);
			cout << "Number can not exceed " << item.milleage << ".\n";
			item.milleage	= InputUInt( item.milleage );
		}
		catch( std::ios_base::failure &bf )	// If a problem input
		{
			cout << "Error: " << bf.what() << endl;
			throw bf;
		}
		catch( std::bad_alloc & ba )
		{
			cout << "Error: " << ba.what() << endl;
			throw ba;
		}
	}
	catch(...)
	{
		if( buff != NULL )
		{
			delete[] buff;
		}
		if( item.name != NULL )
		{
			delete[] item.name;
		}
		return false;
	}

	return true;
}