
#include "ClassFile.h"


int przywitanie()
{
	cout << "=========================================================" << endl;
	cout << "Witamy w grze Domino" << endl << endl;
	cout << "Autor: Adam Kossakowski" << endl;
	cout << "Uniwersytet Kardyn³a Stefana Wyszyñskiego\nWydzia³ Matematyczno-Przyrodniczy Szko³a Nauk Œcis³ych" << endl << endl;
	cout << "Przedmiot:\tProgramowanie Obiektowe" << endl;
	cout << "=========================================================" << endl;
	cout << "Proszê wcisn¹æ przycisk aby przejœæ dalej" << endl;
	char enter;
	getchar();
	int wybor;
	system("cls");
	while (true) {
		cout << "=========================================================" << endl;
		cout << "Menu" << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 1 |  Gra z komputerem                                 |" << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 2 |  Gra z innym graczem                              |" << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 3 |  Rozpoczêcie od ostatniej gry                     |" << endl;
		cout << "+---+---------------------------------------------------+" << endl << endl;
		cout << "========================================================" << endl;
		cout << "Wybór:\t";
		cin >> wybor;
		if (wybor == 1 || wybor == 2 || wybor == 3)
			break;
		else
		{
			cout << "=========================================================" << endl;
			cout << "Niepoprawny znak\nProszê wprowadziæ jeszcze raz";
			Sleep(1000);
			system("cls");
		}
	}
	system("cls");
	return wybor;
}

int main()
{
	///tworzenie kostek domina
	srand(time(NULL));
	setlocale(LC_ALL, "");
	MyContener<KostkaLicz, 28> kontener;
	for (int i = 0; i < 7; i++)
	{
		for (int j = i; j < 7; j++)
		{
			KostkaLicz tmp = KostkaLicz(i, j);
			kontener.push(tmp);
		}
	}
	///rozlosowanie zmiennych dla graczy
	int wybor = przywitanie();
	while (true)
	{
		if (wybor == 1)
		{
			putchar('\n');
			cout << "Proszê wprowadziæ nazwê pierwszego gracza:\t";
			char nazwa[MAX];
			cin >> nazwa;
			Gracz gracz1 = Gracz(nazwa);
			Gracz gracz3 = Gracz("Computer");
			Komputer gracz2 = Komputer(gracz3);
			Sleep(1000);
			system("cls");
			//losowanie kostek dla graczy
			gracz1.wylosuj_kostki(kontener);
			gracz2.wylosuj_kostki(kontener);
			///gra
			UlozenieKostek ulk;
			ulk.pierwsza_kostka(kontener);
			//wylosowano kostke do ulozenia
			while (true)
			{
				gracz1.polozKostke(kontener, ulk);
				//jesli brak kostek gracz jeden wygrywa
				if (gracz1.top() == 0)
				{
					gracz1.wygrana();
					break;
				}
				//
				Sleep(1000);
				system("cls");
				//
				gracz2.polozKostke(kontener, ulk);
				if (gracz2.top() == 0)
				{
					gracz2.wygrana();
					break;
				}

			}
			break;
		}
		else if (wybor == 2) {
			putchar('\n');
			cout << "Proszê wprowadziæ nazwê pierwszego gracza:\t";
			char nazwa[MAX];
			cin >> nazwa;
			Gracz gracz1 = Gracz(nazwa);
			cout << "Proszê wprowadziæ nazwê pierwszego gracza:\t";
			cin >> nazwa;
			Gracz gracz2 = Gracz(nazwa);
			Sleep(1000);
			system("cls");
			//lososwanie kostek dla graczy
			gracz1.wylosuj_kostki(kontener);
			gracz2.wylosuj_kostki(kontener);
			///gra
			UlozenieKostek ulk;
			ulk.pierwsza_kostka(kontener);
			while (true) {
				gracz1.polozKostke(kontener, ulk);
				if (gracz1.top() == 0)
				{
					gracz1.wygrana();
					break;
				}
				Sleep(1000);
				system("cls");
				gracz2.polozKostke(kontener, ulk);
				Sleep(1000);
				system("cls");
				if (gracz2.top() == 0)
				{
					gracz2.wygrana();
					break;
				}
			}
			break;
		}
		else {

		}
	}

	return 0;
}