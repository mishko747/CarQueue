
#include "Cars.h"
#include "QCars.h"

#include <iostream>
#include <conio.h>

void main ( void )
{
	using std::cin;
	using std::cout;
	using std::endl;

	QCars *q;
	try
	{
		q = new QCars();
	}
	catch(...)
	{
		cout<<"Error!\n";
		_getch();
		exit(1);
	}

	unsigned int n;
	do
	{
		system("cls");
		cout<<"**** MENU ****\n";
		cout<<"1 - Add item\n"
			"2 - Del item\n"
			"3 - Output\n"
			"4 - Compact\n"
			"5 - Incompact\n"
			"6 - Exit\n"
			"Enter the menu item: ";
		cin >> n;
		switch( n )
		{
			case 1:	
				if( q->AddItem() == true )
				{
					cout<< "Item added.\n";
				}
				else
				{
					cout<< "Added failed.\n";
				}
				break;
			case 2:	
				if( q->DelItem() == true )
				{
					cout<< "Item is removed.\n";
				}
				else
				{
					cout<< "Queue is empty.\n";
				}
				break;
			case 3: 
				q->Output();
				break;
			case 4: 
				if( q->Compact() == true )
				{
					cout<< "Conversion successful.\n";
				}
				else
				{
					cout<< "Conversion failed.\n";
				}
				break;
			case 5: 
				if( q->InCompact() == true )
				{
					cout<< "Conversion successful.\n";
				}
				else
				{
					cout<< "Conversion failed.\n";
				}
				break;
			case 6: 
				exit(0);
			default: 
				cout<<"Incorect input!\n";
		}
	}
	while( CONTINUE, _getch() != CODE_ESC );

	delete q;

	//i->name = "Avan";
	//i->brand = AUDI;
	//i->year = 1998;
	//i->color = 324;
	//i->milleage = 324231;

	//Item *j = new Item;

	//j->name = "Andrey";
	//j->brand = BMW;
	//j->year = 2006;
	//j->color = 235;
	//j->milleage = 183473;

	//Item *k = new Item;

	//k->name = "Oleg";
	//k->brand = MERCEDES;
	//k->year = 1754;
	//k->color = 111;
	//k->milleage = 14326;

	//QCars *qc;
	//try
	//{
	//	qc = new QCars(); 
	//}
	//catch( std::bad_alloc & ba )
	//{
	//	std::cout<< "Error:" << ba.what() << endl;
	//	system("pause");
	//	exit(1);
	//}

	//std::cout<< "Add i: " << qc->AddItem(*i) << std::endl;
	//std::cout<< "Add j: " << qc->AddItem(*j) << std::endl;
	//std::cout<< "Add k: " << qc->AddItem(*k) << std::endl;
	//
	//std::cout<< "Del: " << qc->DelItem() << std::endl;

	//std::cout << "Compact: " << qc->Compact() << std::endl;

	//std::cout<< "Del: " << qc->DelItem() << std::endl;
	//	
	//int n = 1;
	//int q = 1;

	//for( ; n < 20 ; n++)
	//	std::cout<< "#" << n << "\tAdd j: " << qc->AddItem(*k) << std::endl;
	//
	//for( ; q < 15 ; q++)
	//std::cout<< "Del: " << qc->DelItem() << std::endl;

	//for( ; n < 40 ; n++)
	//	std::cout<< "#" << n + 1 << "\tAdd j: " << qc->AddItem(*k) << std::endl;

	//qc->Output();



	//delete qc;

	//system("pause");
}