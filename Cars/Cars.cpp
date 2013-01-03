
#include "Cars.h"
#include "CarsQueue.h"
#include <iostream>
#include <stdlib.h>

void main ( void )
{
	using std::cin;
	using std::cout;
	using std::endl;

	CarsQueue *q = new CarsQueue();
	Item *i = new Item;

	i->name = "mixan";
	i->brand = AUDI;
	i->year = 1998;
	i->color = 324;
	i->milleage = 324231;

	Item *j = new Item;
	j->name = new char[10];

	cout<< "Input name: ";
	cin>> j->name;

	j->brand = BMW;
	j->year = 1998;
	j->color = 324;
	j->milleage = 324231;

	q->Add( i );
	q->Add( j );
	q->Output();
	
	if( q->Compact() == false )
	{
		cout<< "Compact() == false\n";
	}
	else
	{
		cout<< "Compact() == true\n";
	}

	delete i;
	delete q;

	system("pause");
}