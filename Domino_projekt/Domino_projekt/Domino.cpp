
#include "ClassFile.h"
#define _WIN32_WINNT 0x0500
#define ROUND 2


void poczatek()
{
	cout << "=========================================================" << endl;
	cout << "Witamy w grze Domino" << endl << endl;
	cout << "Autor: Adam Kossakowski" << endl;
	cout << "Uniwersytet Kardynała Stefana Wyszyśskiego\nWydział Matematyczno-Przyrodniczy Szkoła Nauk Ścisłych" << endl << endl;
	cout << "Przedmiot:\tProgramowanie Obiektowe" << endl;
	cout << "=========================================================" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	cout << R"(     D       O       M       I      N      O
 	_______________________________________   
 	|                  |                  |   
 	|                  |        __        |   
 	|                  |       |  |       |   
 	|       __         |       |__|       |   
 	|      |  |        |                  |   
 	|      |__|        |        __        |   
 	|                  |       |  |       |   
 	|                  |       |__|       |   
 	|                  |                  |   
 	|__________________|__________________|  
	)";
	cout << "\n\nProszę wcisnąć przycisk aby przejść dalej" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	string enter;
	char z;
	while (!(z = getchar()) && z) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
}

int menu()
{
	int wybor;
	system("cls");
	while (true) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 121);
		cout << "=========================================================" << endl;
		cout << "Menu                                                     " << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 1 |  Gra z komputerem                                 |" << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 2 |  Gra z innym graczem                              |" << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 3 |  Ranking                                          |" << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 4 |  Rozpoczęcie ostatniej gry                        |" << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 5 |  Zakończenie gry                                  |" << endl;
		cout << "+---+---------------------------------------------------+" << endl << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "========================================================" << endl;
		cout << "Wybór:\t";
		while (true) {
			cin >> wybor;
			bool czyDobra = cin.good();
			if (czyDobra)
				break;
			else {
				cout << "Niepoprawna dana proszę wybrać jeszcze raz:\t";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
		}
		if (wybor == 1 || wybor == 2 || wybor == 3 || wybor == 4 || wybor == 5)
			break;
		else
		{
			cout << "=========================================================" << endl;
			cout << "Niepoprawny znak\nProszę wprowadzić jeszcze raz";
			Sleep(1000);
			system("cls");
		}
	}
	system("cls");
	return wybor;
}

void errorFind()
{
	cout << "Ups wystipił błąd niestety nie znaleziono odpowiedniego pliku :(\n";
	Sleep(8000);
}

void errorOpen()
{
	cout << "Ups wystipił błąd niestety nie mo¿na otworzyæ odpowiedniego pliku :(\n";
	Sleep(8000);
}

void errorData()
{
	cout << "Ups coś się nie powiodło, niepoprawne dane wczytywania\n";
	Sleep(8000);
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
			int wybor = menu();
			if (wybor == 1)
			{
				putchar('\n');
				bool jakiKoniec = true;
				cout << "Proszę wprowadzić nazwę pierwszego gracza:\t";
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
					UlozenieKostek *ulk = new UlozenieKostek;
					ulk->pierwsza_kostka(kontener);
					//wylosowano kostke do ulozenia
					while (true)
					{
						int g1 = gracz1->polozKostke(kontener, *ulk);
						if (gracz1->top() == 0)
						{
							gracz1->wygrana(*ulk, *gracz2);
							break;
						}
						//zapisywanie
						if (g1 == 3) {
							Saving *saving = new Saving(1, q);
							jakiKoniec = saving->zapiss(*ulk, kontener, *gracz1, *gracz2, 'k');
							q = ROUND;
							delete(saving);
							break;
						}
						//
						Sleep(1000);
						system("cls");
						//
						int g2 = gracz2->polozKostke(kontener, *ulk);
						if (gracz2->top() == 0)
						{
							gracz2->wygrana(*ulk, *gracz1);
							break;
						}

						if (g1 == 0 && g2 == 0) {//sparwdza czy gracze mog¹ po³o¿yæ jaszcze jakies kostki jesli nie konczy gre
							if (gracz1->f_punkty() <= gracz2->f_punkty())
							{
								gracz1->wygrana(*ulk, *gracz2);
							}
							else {
								gracz2->wygrana(*ulk, *gracz1);
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
						gracz1->wygrajRunde(*gracz2);
					}
					else gracz2->wygrajRunde(*gracz1);

					delete(gracz1);
					delete(gracz2);
					break;
				}
			}
			else if (wybor == 2) {
				putchar('\n');
				bool jakiKoniec = true;
				cout << "Proszę wprowadzić nazwę pierwszego gracza:\t";
				char nazwa[MAX];
				cin >> nazwa;
				Gracz *gracz1 = new Gracz(nazwa);
				cout << "Proszę wprowadzić nazwę pierwszego gracza:\t";
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
							gracz1->wygrana(ulk, *gracz2);
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
							gracz2->wygrana(ulk, *gracz2);

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
								gracz1->wygrana(ulk, *gracz2);
							}
							else {
								gracz2->wygrana(ulk, *gracz1);
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
						gracz1->wygrajRunde(*gracz2);
					}
					else gracz2->wygrajRunde(*gracz1);
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
					if (z == 'q' || z == 'Q')
						break;
				}
				system("cls");
				break;
			}
			else if (wybor == 4) {
				FILE *stream;
				if (file_exists("plik_savingGame_Tryb.txt") && file_exists("plik_savingGame_Gracz1.txt")
					&& file_exists("plik_savingGame_Gracz2.txt") && file_exists("plik_savingGame_list.txt") && file_exists("plik_savingGame_koszyk.txt")) {
					if (stream = fopen("plik_savingGame_Tryb.txt", "r")) {
						char procedure;
						int points_A, points_B, move, round_S;
						char player1_S[20], player2_S[20];

						fscanf(stream, "%c\n", &procedure);
						fscanf(stream, "%d" "%d" "%d" "%d\n", &points_A, &points_B, &move, &round_S);
						fscanf(stream, "%s" "%s", player1_S, player2_S);

						fclose(stream);

						if (procedure == 'k') {

							Gracz *gracz1 = new Gracz(player1_S, points_A);
							Komputer *gracz2 = new Komputer(player2_S, points_B);

							FILE *player1_P, *player2_P;

							if (player1_P = fopen("plik_savingGame_Gracz1.txt", "r")) {
								int left, right;
								do {
									fscanf(player1_P, "%d" "%d\n", &left, &right);
									if (gracz1->filling(left, right)); else {
										errorData();
										break;
									}
								} while (!feof(player1_P));
								fclose(player1_P);
							}
							else {
								errorOpen();
								break;
							}
							if (player2_P = fopen("plik_savingGame_Gracz2.txt", "r")) {
								int left, right;
								do {
									fscanf(player2_P, "%d" "%d\n", &left, &right);
									if (gracz2->filling(left, right)); else {
										errorData();
										break;
									}
								} while (!feof(player2_P));
								fclose(player2_P);
							}
							else {
								errorOpen();
								break;
							}

							bool jakiKoniec = true;
							for (int q = round_S; q < ROUND; q++) {
								UlozenieKostek *ulk = new UlozenieKostek;
								MyContener<KostkaLicz, 28> kontener;
								if (q != round_S) {
									for (int i = 0; i < 7; i++) {
										for (int j = i; j < 7; j++)
										{
											KostkaLicz tmp = KostkaLicz(i, j);
											kontener.push(tmp);
										}
									}
									gracz1->wylosuj_kostki(kontener);
									gracz2->wylosuj_kostki(kontener);

									ulk->pierwsza_kostka(kontener);
								}
								else {
									FILE *list_P;
									if (list_P = fopen("plik_savingGame_list.txt", "r")) {
										int left, right;
										do {
											fscanf(list_P, "%d" "%d\n", &left, &right);
											if (ulk->filling_list(left, right)); else {
												errorData();
												break;
											}
										} while (!feof(list_P));
										fclose(list_P);
									}
									else {
										errorOpen();
										break;
									}

									if (stream = fopen("plik_savingGame_koszyk.txt", "r")) {
										do {
											int block_Left, block_Right;
											fscanf(stream, "%d" "%d\n", &block_Left, &block_Right);
											if (block_Left >= 0 && block_Left <= 6 && block_Right >= 0 && block_Right <= 6) {
												KostkaLicz tmp = KostkaLicz(block_Left, block_Right);
												kontener.push(tmp);
											}
											else {
												errorData();
												break;
											}


										} while (!feof(stream));
										fclose(stream);
									}
									else {
										errorOpen();
										break;
									}
								}

								while (true)
								{
									int g1 = gracz1->polozKostke(kontener, *ulk);
									if (gracz1->top() == 0)
									{
										gracz1->wygrana(*ulk, *gracz2);
										break;
									}
									//zapisywanie
									if (g1 == 3) {
										Saving *saving = new Saving(1, q);
										jakiKoniec = saving->zapiss(*ulk, kontener, *gracz1, *gracz2, 'k');
										q = ROUND;
										delete(saving);
										break;
									}
									//
									Sleep(1000);
									system("cls");
									//
									int g2 = gracz2->polozKostke(kontener, *ulk);
									if (gracz2->top() == 0)
									{
										gracz2->wygrana(*ulk, *gracz1);
										break;
									}

									if (g1 == 0 && g2 == 0) {//sparwdza czy gracze mog¹ po³o¿yæ jaszcze jakies kostki jesli nie konczy gre
										if (gracz1->f_punkty() <= gracz2->f_punkty())
										{
											gracz1->wygrana(*ulk, *gracz2);
										}
										else {
											gracz2->wygrana(*ulk, *gracz1);
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
									gracz1->wygrajRunde(*gracz2);
								}
								else gracz2->wygrajRunde(*gracz1);

								delete(gracz1);
								delete(gracz2);
								break;
							}
						}
						else if (procedure == 'g') {

							Gracz *gracz1 = new Gracz(player1_S, points_A);
							Gracz *gracz2 = new Gracz(player2_S, points_B);

							FILE *player1_P, *player2_P;

							if (player1_P = fopen("plik_savingGame_Gracz1.txt", "r")) {
								int left, right;
								do {
									fscanf(player1_P, "%d" "%d\n", &left, &right);
									if (gracz1->filling(left, right)); else {
										errorData();
										break;
									}
								} while (!feof(player1_P));
								fclose(player1_P);
							}
							else {
								errorOpen();
								break;
							}
							if (player2_P = fopen("plik_savingGame_Gracz2.txt", "r")) {
								int left, right;
								do {
									fscanf(player2_P, "%d" "%d\n", &left, &right);
									if (gracz2->filling(left, right)); else {
										errorData();
										break;
									}
								} while (!feof(player2_P));
								fclose(player2_P);
							}
							else {
								errorOpen();
								break;
							}

							bool jakiKoniec = true;
							for (int q = round_S; q < ROUND; q++) {

								UlozenieKostek *ulk = new UlozenieKostek;
								MyContener<KostkaLicz, 28> kontener;

								if (q != round_S) {
									for (int i = 0; i < 7; i++) {
										for (int j = i; j < 7; j++)
										{
											KostkaLicz tmp = KostkaLicz(i, j);
											kontener.push(tmp);
										}
									}

									gracz1->wylosuj_kostki(kontener);
									gracz2->wylosuj_kostki(kontener);

									ulk->pierwsza_kostka(kontener);
								}
								else {
									FILE *list_P;
									if (list_P = fopen("plik_savingGame_list.txt", "r")) {
										int left, right;
										do {
											fscanf(list_P, "%d" "%d\n", &left, &right);
											if (ulk->filling_list(left, right)); else {
												errorData();
												break;
											}
										} while (!feof(list_P));
										fclose(list_P);
									}
									else {
										errorOpen();
										break;
									}

									if (stream = fopen("plik_savingGame_koszyk.txt", "r")) {
										do {
											int block_Left, block_Right;
											fscanf(stream, "%d" "%d\n", &block_Left, &block_Right);
											if (block_Left >= 0 && block_Left <= 6 && block_Right >= 0 && block_Right <= 6) {
												KostkaLicz tmp = KostkaLicz(block_Left, block_Right);
												kontener.push(tmp);
											}

										} while (!feof(stream));
										fclose(stream);
									}
								}

								if (move == 1) {
									while (true)
									{
										int g1 = gracz1->polozKostke(kontener, *ulk);
										if (gracz1->top() == 0)
										{
											gracz1->wygrana(*ulk, *gracz2);
											break;
										}
										if (g1 == 3) {
											Saving *saving = new Saving(1, q);
											jakiKoniec = saving->zapiss(*ulk, kontener, *gracz1, *gracz2, 'g');
											q = ROUND;
											delete(saving);
											break;
										}
										Sleep(1000);
										system("cls");
										int g2 = gracz2->polozKostke(kontener, *ulk);
										Sleep(1000);
										system("cls");
										if (gracz2->top() == 0)
										{
											gracz2->wygrana(*ulk, *gracz2);

											break;
										}
										if (g2 == 3) {
											Saving *saving = new Saving(2, q);
											jakiKoniec = saving->zapiss(*ulk, kontener, *gracz1, *gracz2, 'g');
											q = ROUND;
											delete(saving);
											break;
										}
										if (g1 == 0 && g2 == 0) {
											if (gracz1->f_punkty() <= gracz2->f_punkty())
											{
												gracz1->wygrana(*ulk, *gracz2);
											}
											else {
												gracz2->wygrana(*ulk, *gracz1);
											}
											break;
										}

									}
								}
								else if (move == 2) {
									while (true)
									{
										int g2 = gracz2->polozKostke(kontener, *ulk);
										if (gracz2->top() == 0)
										{
											gracz2->wygrana(*ulk, *gracz1);
											break;
										}
										if (g2 == 3) {
											Saving *saving = new Saving(2, q);
											jakiKoniec = saving->zapiss(*ulk, kontener, *gracz1, *gracz2, 'g');
											q = ROUND;
											delete(saving);
											break;
										}
										Sleep(1000);
										system("cls");
										int g1 = gracz1->polozKostke(kontener, *ulk);
										Sleep(1000);
										system("cls");
										if (gracz1->top() == 0)
										{
											gracz1->wygrana(*ulk, *gracz2);

											break;
										}
										if (g1 == 3) {
											Saving *saving = new Saving(1, q);
											jakiKoniec = saving->zapiss(*ulk, kontener, *gracz1, *gracz2, 'g');
											q = ROUND;
											delete(saving);
											break;
										}
										if (g1 == 0 && g2 == 0) {
											if (gracz1->f_punkty() <= gracz2->f_punkty())
											{
												gracz1->wygrana(*ulk, *gracz2);
											}
											else {
												gracz2->wygrana(*ulk, *gracz1);
											}
											break;
										}

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
									gracz1->wygrajRunde(*gracz2);
								}
								else gracz2->wygrajRunde(*gracz1);

								delete(gracz1);
								delete(gracz2);
								break;
							}
						}
						else {
							errorData();
							break;
						}
					}
					else {
						errorOpen();
						break;
					}
				}
				else {
					errorFind();
					break;
				}
			}
			else {
				return 0;
			}
		}

	}

	return 0;
}
