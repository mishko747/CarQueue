
#include "Cars.h"
//#include "CarsQueue.h"
#include "QCars.h"
#include <iostream>
#include <stdlib.h>

void main ( void )
{
	using std::cin;
	using std::cout;
	using std::endl;

	Item *i = new Item;

	i->name = "mixan";
	i->brand = AUDI;
	i->year = 1998;
	i->color = 324;
	i->milleage = 324231;

	Item *j = new Item;

	j->name = "mishko";
	j->brand = BMW;
	j->year = 2006;
	j->color = 235;
	j->milleage = 183473;

	Item *k = new Item;

	k->name = "Oleg";
	k->brand = MERCEDES;
	k->year = 1754;
	k->color = 111;
	k->milleage = 14326;

	QCars *qc;
	try
	{
		qc = new QCars(); 
	}
	catch( std::bad_alloc & ba )
	{
		std::cout<< "Error:" << ba.what() << endl;
		system("pause");
		exit(1);
	}

	std::cout<< "Add i: " << qc->AddItem(*i) << std::endl;
	std::cout<< "Add j: " << qc->AddItem(*j) << std::endl;
	std::cout<< "Add k: " << qc->AddItem(*k) << std::endl;
	
	std::cout<< "Del: " << qc->DelItem() << std::endl;

	std::cout << "Compact: " << qc->Compact() << std::endl;

	std::cout<< "Del: " << qc->DelItem() << std::endl;
		
	int n = 1;
	int q = 1;

	for( ; n < 20 ; n++)
		std::cout<< "#" << n << "\tAdd j: " << qc->AddItem(*k) << std::endl;
	
	for( ; q < 15 ; q++)
	std::cout<< "Del: " << qc->DelItem() << std::endl;

	for( ; n < 40 ; n++)
		std::cout<< "#" << n + 1 << "\tAdd j: " << qc->AddItem(*k) << std::endl;

	qc->Output();



	delete qc;

	system("pause");
}