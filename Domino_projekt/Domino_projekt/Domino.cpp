
#include "ClassFile.h"
#define _WIN32_WINNT 0x0500
#define ROUND 2


void poczatek()
{
	cout << "=========================================================" << endl;
	cout << "Witamy w grze Domino" << endl << endl;
	cout << "Autor: Adam Kossakowski" << endl;
	cout << "Uniwersytet Kardyn³a Stefana Wyszyñskiego\nWydzia³ Matematyczno-Przyrodniczy Szko³a Nauk Œcis³ych" << endl << endl;
	cout << "Przedmiot:\tProgramowanie Obiektowe" << endl;
	cout << "=========================================================" << endl;
	cout << "Proszê wcisn¹æ przycisk aby przejœæ dalej" << endl;
	string enter;
	char z;
	while (!(z = getchar()) && z) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
}

int przywitanie()
{
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
		cout << "| 3 |  Ranking						                     |" << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 4 |  Zakoñczenie gry                                  |" << endl;
		cout << "+---+---------------------------------------------------+" << endl << endl;
		cout << "========================================================" << endl;
		cout << "Wybór:\t";
		while (true) {
			cin >> wybor;
			bool czyDobra = cin.good();
			if (czyDobra)
				break;
			else {
				cout << "Niepoprawna dana proszê wybraæ jeszcze raz:\t";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
		}
		if (wybor == 1 || wybor == 2 || wybor == 3 || wybor == 4)
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
	MoveWindow(GetConsoleWindow(), 150, 100, 1000, 500, true);
	srand(time(NULL));
	setlocale(LC_ALL, "");
	poczatek();
	while (true) {
		int wybor = przywitanie();
		///rozlosowanie zmiennych dla graczy
		while (true)
		{
			if (wybor == 1)
			{
				putchar('\n');
				cout << "Proszê wprowadziæ nazwê pierwszego gracza:\t";
				char nazwa[MAX];
				cin >> nazwa;
				Gracz *gracz1 = new Gracz(nazwa);
				Komputer *gracz2 = new Komputer("Computer");
				Sleep(1000);
				system("cls");
				for (int q = 0; q < ROUND; q++) {
					MyContener<KostkaLicz, 28> kontener;
					for (int i = 0; i < 7; i++)
					{
						for (int j = i; j < 7; j++)
						{
							KostkaLicz tmp = KostkaLicz(i, j);
							kontener.push(tmp);
						}
					}

					//losowanie kostek dla graczy
					gracz1->wylosuj_kostki(kontener);
					gracz2->wylosuj_kostki(kontener);
					///gra
					UlozenieKostek ulk;
					ulk.pierwsza_kostka(kontener);
					//wylosowano kostke do ulozenia
					while (true)
					{
						bool g1 = gracz1->polozKostke(kontener, ulk);
						if (gracz1->top() == 0)
						{
							gracz1->wygrana(ulk, gracz2->doWygranej());
							break;
						}
						//
						Sleep(1000);
						system("cls");
						//
						bool g2 = gracz2->polozKostke(kontener, ulk);
						if (gracz2->top() == 0)
						{
							gracz2->wygrana(ulk, gracz1->doWygranej());
							break;
						}

						if (g1 == false && g2 == false) {//sparwdza czy gracze mog¹ po³o¿yæ jaszcze jakies kostki jesli nie konczy gre
							if (gracz1->f_punkty() <= gracz2->f_punkty())
							{
								gracz1->wygrana(ulk, gracz2->doWygranej());
							}
							else {
								gracz2->wygrana(ulk, gracz1->doWygranej());
							}
							break;
						}

					}
					Sleep(10000);
					system("cls");
					gracz1->zeruj();
					gracz2->zeruj();
				}
				if (gracz1->kto_wygral() >= gracz2->kto_wygral())
				{
					gracz1->wygrajRunde();
				}
				else gracz2->wygrajRunde();
				delete(gracz1);
				delete(gracz2);
				break;
			}
			else if (wybor == 2) {
				putchar('\n');
				cout << "Proszê wprowadziæ nazwê pierwszego gracza:\t";
				char nazwa[MAX];
				cin >> nazwa;
				Gracz *gracz1 = new Gracz(nazwa);
				cout << "Proszê wprowadziæ nazwê pierwszego gracza:\t";
				cin >> nazwa;
				Gracz *gracz2 = new Gracz(nazwa);
				Sleep(1000);
				system("cls");
				for (int q = 0; q < ROUND; q++) {
					MyContener<KostkaLicz, 28> kontener;
					for (int i = 0; i < 7; i++)
					{
						for (int j = i; j < 7; j++)
						{
							KostkaLicz tmp = KostkaLicz(i, j);
							kontener.push(tmp);
						}
					}
					//lososwanie kostek dla graczy
					gracz1->wylosuj_kostki(kontener);
					gracz2->wylosuj_kostki(kontener);
					///gra
					UlozenieKostek ulk;
					ulk.pierwsza_kostka(kontener);
					while (true) {
						bool g1 = gracz1->polozKostke(kontener, ulk);
						if (gracz1->top() == 0)
						{
							gracz1->wygrana(ulk, gracz2->doWygranej());
							break;
						}
						Sleep(1000);
						system("cls");
						bool g2 = gracz2->polozKostke(kontener, ulk);
						Sleep(1000);
						system("cls");
						if (gracz2->top() == 0)
						{
							gracz2->wygrana(ulk, gracz2->doWygranej());

							break;
						}

						if (g1 == false && g2 == false) {
							if (gracz1->f_punkty() <= gracz2->f_punkty())
							{
								gracz1->wygrana(ulk, gracz2->doWygranej());
							}
							else {
								gracz2->wygrana(ulk, gracz1->doWygranej());
							}
							break;
						}
					}
					Sleep(10000);
					system("cls");
					gracz1->zeruj();
					gracz2->zeruj();
				}
				if (gracz1->kto_wygral() >= gracz2->kto_wygral())
				{
					gracz1->wygrajRunde();
				}
				else gracz2->wygrajRunde();
				delete(gracz1);
				delete(gracz2);
				break;
			}
			else if (wybor == 3) {
				FILE *open;
				if (file_exists("plik_rankingowy.txt") == true) {
					if (open = fopen("plik_rankingowy.txt", "r")) {
						cout << "\t\t\tRanking graczy\n";
						do {
							char nazwa[20];
							int punkty;
							fscanf(open, "%s %d\n", nazwa, &punkty);
							printf("Nazwa gracza:\t%20s\tLiczba punktów:\t%4i\n", nazwa, punkty);
						} while (!feof(open));
						
					}
					else {
						cout << "\nPlik rankingowy jeszcze nie istnieje\n";
					}
				}
				cout << "\nNaciœnij Q aby wyjœæ\n";
				char z;
				while (true)
				{
					z = getchar();
					if (z == 'q' || z=='Q')
						break;
				}
				system("cls");
				break;
			}
			else {
				return 0;
			}
		}
		
	}
	return 0;
}