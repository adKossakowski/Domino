
#include "ClassFile.h"
#define _WIN32_WINNT 0x0500
#define ROUND 2


void poczatek()
{
	cout << "=========================================================" << endl;
	cout << "Witamy w grze Domino" << endl << endl;
	cout << "Autor: Adam Kossakowski" << endl;
	cout << "Uniwersytet Kardyn�a Stefana Wyszy�skiego\nWydzia� Matematyczno-Przyrodniczy Szko�a Nauk �cis�ych" << endl << endl;
	cout << "Przedmiot:\tProgramowanie Obiektowe" << endl;
	cout << "=========================================================" << endl;
	cout << "Prosz� wcisn�� przycisk aby przej�� dalej" << endl;
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
		cout << "| 4 |  Rozpocz�cie ostatniej gry                        |" << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 5 |  Zako�czenie gry                                  |" << endl;
		cout << "+---+---------------------------------------------------+" << endl << endl;
		cout << "========================================================" << endl;
		cout << "Wyb�r:\t";
		while (true) {
			cin >> wybor;
			bool czyDobra = cin.good();
			if (czyDobra)
				break;
			else {
				cout << "Niepoprawna dana prosz� wybra� jeszcze raz:\t";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
		}
		if (wybor == 1 || wybor == 2 || wybor == 3 || wybor == 4 || wybor == 5)
			break;
		else
		{
			cout << "=========================================================" << endl;
			cout << "Niepoprawny znak\nProsz� wprowadzi� jeszcze raz";
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
		
		///rozlosowanie zmiennych dla graczy
		while (true)
		{
			int wybor = przywitanie();
			if (wybor == 1)
			{
				putchar('\n');
				bool jakiKoniec = true;
				cout << "Prosz� wprowadzi� nazw� pierwszego gracza:\t";
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
						int g1 = gracz1->polozKostke(kontener, ulk);
						if (gracz1->top() == 0)
						{
							gracz1->wygrana(ulk, gracz2->doWygranej());
							break;
						}
						//zapisywanie
						if (g1 == 3){
							Saving *saving = new Saving(1, q);
							jakiKoniec = saving->zapiss(ulk, kontener, *gracz1, *gracz2, 'k');
							q = ROUND;
							delete(saving);
							break;
						}
						//
						Sleep(1000);
						system("cls");
						//
						int g2 = gracz2->polozKostke(kontener, ulk);
						if (gracz2->top() == 0)
						{
							gracz2->wygrana(ulk, gracz1->doWygranej());
							break;
						}

						if (g1 == 0 && g2 == 0) {//sparwdza czy gracze mog� po�o�y� jaszcze jakies kostki jesli nie konczy gre
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
				if (jakiKoniec == true) {
					if (gracz1->kto_wygral() >= gracz2->kto_wygral())
					{
						gracz1->wygrajRunde();
					}
					else gracz2->wygrajRunde();
					delete(gracz1);
					delete(gracz2);
					break;
				}
			}
			else if (wybor == 2) {
				putchar('\n');
				bool jakiKoniec = true;
				cout << "Prosz� wprowadzi� nazw� pierwszego gracza:\t";
				char nazwa[MAX];
				cin >> nazwa;
				Gracz *gracz1 = new Gracz(nazwa);
				cout << "Prosz� wprowadzi� nazw� pierwszego gracza:\t";
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
						int g1 = gracz1->polozKostke(kontener, ulk);
						if (gracz1->top() == 0)
						{
							gracz1->wygrana(ulk, gracz2->doWygranej());
							break;
						}
						if (g1 == 3) {
							Saving *saving = new Saving(1, q);
							jakiKoniec = saving->zapiss(ulk, kontener, *gracz1, *gracz2, 'g');
							q = ROUND;
							delete(saving);
							break;
						}
						Sleep(1000);
						system("cls");
						int g2 = gracz2->polozKostke(kontener, ulk);
						Sleep(1000);
						system("cls");
						if (gracz2->top() == 0)
						{
							gracz2->wygrana(ulk, gracz2->doWygranej());

							break;
						}
						if (g2 == 3) {
							Saving *saving = new Saving(2, q);
							jakiKoniec = saving->zapiss(ulk, kontener, *gracz1, *gracz2, 'g');
							q = ROUND;
							delete(saving);
							break;
						}
						if (g1 == 0 && g2 == 0) {
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
				if (jakiKoniec == true) {
					if (gracz1->kto_wygral() >= gracz2->kto_wygral())
					{
						gracz1->wygrajRunde();
					}
					else gracz2->wygrajRunde();
				}
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
							printf("Nazwa gracza:\t%20s\tLiczba punkt�w:\t%4i\n", nazwa, punkty);
						} while (!feof(open));
						
					}
					else {
						cout << "\nPlik rankingowy jeszcze nie istnieje\n";
					}
				}
				cout << "\nNaci�nij Q aby wyj��\n";
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