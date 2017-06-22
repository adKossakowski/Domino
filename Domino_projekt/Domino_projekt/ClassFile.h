#pragma once
#ifndef ClassFile_hpp
#define ClassFile_hpp

#pragma once
#define MAX 20
#define LICZK 7
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<ctime>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<Windows.h>
#include<sys/stat.h>

using namespace std;

bool file_exists(const char *cSpecyf_Zbioru)
{
	struct stat buf;
	if (stat(cSpecyf_Zbioru, &buf) == 0)
		return true;
	else return false;
}


template<typename T, int rozmiar>
class MyContener {
	T stos[rozmiar];
	int top;
public:
	friend class Saving;

	MyContener() : top(0) {}

	int getTop()
	{
		return top;
	}

	void push_first(const T& i) {
		top++;
		for (int j = (top - 1); j >= 0; j--) {
			stos[j] = stos[j - 1];
		}
		stos[0] = i;
	}

	void push(const T& i) {
		stos[top++] = i;
	}
	T pop(int i) {
		T tmp = stos[i];
		for (int j = i; j < top - 1; j++)
		{
			swap(stos[j], stos[j + 1]);
		}
		top--;
		return tmp;
	}

	T wyswietl(int i)
	{
		return stos[i];
	}

	void setTop() { top++; };

	void SetTop(int i)
	{
		top = i;
	}
};

class KostkaLicz {
	int liczbaL;
	int liczbaP;

public:

	KostkaLicz()
	{
		liczbaL = 0;
		liczbaP = 0;
	}

	KostkaLicz(int l, int p)
	{
		liczbaL = l;
		liczbaP = p;
	}

	KostkaLicz(const KostkaLicz &cpy)
	{
		liczbaL = cpy.liczbaL;
		liczbaP = cpy.liczbaP;
	}

	bool czyTakieSame()
	{
		if (liczbaL == liczbaP)
			return true;
		else return false;
	}

	void swap()
	{
		int tmp = liczbaL;
		liczbaL = liczbaP;
		liczbaP = tmp;
	}

	int getLiczba_l()
	{
		return liczbaL;
	}

	int getLiczba_p()
	{
		return liczbaP;
	}

};

class UlozenieKostek
{
	MyContener<KostkaLicz, 28> lista;

public:

	friend class Saving;

	void pushU(KostkaLicz &k) {
		lista.push(k);
	}

	void push_firstU(KostkaLicz &k) {
		lista.push_first(k);
	}

	int pierwsza()
	{
		return lista.wyswietl(0).getLiczba_l();
	}

	int ostatnia()//dla klasy Komputer zwraca ostatni numer kostki
	{
		return lista.wyswietl(lista.getTop() - 1).getLiczba_p();
	}


	bool filling_list(int left_N, int right_N) {
		if (left_N >= 0 && left_N <= 6 && right_N >= 0 && right_N <= 6) {
			KostkaLicz tmp = KostkaLicz(left_N, right_N);
			lista.push(tmp);
			return true;
		}
		else return false;
	}

	void pierwsza_kostka(MyContener<KostkaLicz, 28> &kostkaTab)
	{
		int wyb = rand() % kostkaTab.getTop();
		lista.push(kostkaTab.pop(wyb));
	}

	void wyswietl_kostki()
	{
		cout << "\nUłożenie kostek:\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		for (int i = 0; i < lista.getTop(); i++) {
			printf("|%i|%i| ", lista.wyswietl(i).getLiczba_l(), lista.wyswietl(i).getLiczba_p());
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}

};

class Gracz
{
protected:

	char nazwa_Gracza[MAX];
	int punkty;
	int punkty_doOddania;
	MyContener<KostkaLicz, 28> moje_kostki;

	void zwiekszTop()
	{
		moje_kostki.setTop();
	}

	KostkaLicz ukladanie(int i)
	{
		return moje_kostki.pop(i);
	}

	virtual void wyswietlMoje_kostki()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("\n\nGracz:\t%s\nTwoje kostki\n\n", nazwa_Gracza);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		for (int i = 0; i < moje_kostki.getTop(); i++) {
			printf("%i\t|%i|%i|\t\t", i + 1, moje_kostki.wyswietl(i).getLiczba_l(), moje_kostki.wyswietl(i).getLiczba_p());
			if (i % 2 == 1)
				putchar('\n');
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("\n\n%i\tPobranie kostki", moje_kostki.getTop() + 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 30);
		printf("\n\n%i\tWyjście z gry", moje_kostki.getTop() + 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("\n\nPunkty :\t%i", punkty);
	}

	bool pobierz_Kostke(MyContener<KostkaLicz, 28> &kontener)
	{
		if (kontener.getTop() != 0) {
			int ran = rand() % kontener.getTop();
			moje_kostki.push(kontener.pop(ran));
			return true;
		}
		else return false;
	}

	bool czySaKostki(UlozenieKostek &ulk)
	{
		for (int i = 0; i < this->moje_kostki.getTop(); i++)
		{
			if (this->moje_kostki.wyswietl(i).getLiczba_l() == ulk.ostatnia())
			{
				return true;
			}
			else if (this->moje_kostki.wyswietl(i).getLiczba_p() == ulk.ostatnia()) {
				return true;
			}
			else if (this->moje_kostki.wyswietl(i).getLiczba_p() == ulk.pierwsza()) {
				return true;
			}
			else if (this->moje_kostki.wyswietl(i).getLiczba_l() == ulk.pierwsza()) {
				return true;
			}
		}
		return false;
	}

public:

	friend class Saving;

	Gracz(char *name) :punkty(0), punkty_doOddania(0)
	{
		strcpy(this->nazwa_Gracza, name);
		punkty = 0;
		cout << "=========================================================" << endl;
		cout << "Ustawiono nazwę gracza na :\t" << nazwa_Gracza << endl;
		cout << "=========================================================" << endl << endl;
		Sleep(3000);
	}

	Gracz(char *name, int points) :punkty(points), punkty_doOddania(0)
	{
		strcpy(this->nazwa_Gracza, name);
	}

	void zeruj()
	{
		this->moje_kostki.SetTop(0);
	}

	int top()
	{
		return moje_kostki.getTop();
	}

	int kto_wygral()
	{
		return punkty;
	}

	char* getNazwa_Gracza() {
		return nazwa_Gracza;
	}

	void liczenie_punktow(int kostka_ulozenie, int kostka_dodaj, bool czyIdentyczne) {
		if (((kostka_dodaj + kostka_ulozenie) % 2) == 0) {
			if (czyIdentyczne)
				punkty += 2 * kostka_dodaj + kostka_ulozenie;
			else
				punkty += kostka_dodaj + kostka_ulozenie;
		}
	}

	bool filling(int left_N, int right_N) {
		if (left_N >= 0 && left_N <= 6 && right_N >= 0 && right_N <= 6) {
			KostkaLicz tmp = KostkaLicz(left_N, right_N);
			moje_kostki.push(tmp);
			return true;
		}
		else return false;
	}

	void wygrana(UlozenieKostek &ulk, Gracz& gr)
	{
		system("cls");
		ulk.wyswietl_kostki();
		for (int i = 0; i < gr.moje_kostki.getTop(); i++)
		{
			this->punkty += (gr.moje_kostki.wyswietl(i).getLiczba_l() + gr.moje_kostki.wyswietl(i).getLiczba_p());
		}
		for (int i = 0; i < moje_kostki.getTop(); i++)
		{
			this->punkty -= (moje_kostki.wyswietl(i).getLiczba_l() + moje_kostki.wyswietl(i).getLiczba_p());
		}
		printf("\n\nBrawo !!!\nGracz:\t%s Wygrał!!!!\n\n", nazwa_Gracza);
		printf("Liczba punktów gracza %s:\t%d\n\n", nazwa_Gracza, punkty);
	}

	virtual void wygrajRunde(Gracz& gr)
	{
		cout << "\n\nGracz " << nazwa_Gracza << " wygra³ mecz\n\n";
		cout << "+=======================================================================================+\n";
		printf("|Wynik meczu:Gracz: %-20s |Gracz: %-20s:\t%3i:%3i         |\n", this->nazwa_Gracza, gr.nazwa_Gracza, this->punkty, gr.punkty);
		cout << "+=======================================================================================+\n";
		Sleep(8000);
		FILE *plik;
		if (file_exists("plik_rankingowy.txt")) {
			if ((plik = fopen("plik_rankingowy.txt", "r")) != NULL)
			{
				vector<int> t_pkt;
				vector<string> naz;
				int l;
				char n[30];
				string sn;
				do {
					fscanf(plik, "%s" "%d\n", n, &l);
					sn = n;
					t_pkt.push_back(l);
					naz.push_back(sn);
				} while (!feof(plik));
				fclose(plik);
				if (plik = fopen("plik_rankingowy.txt", "w"))
				{
					bool insert = false;
					for (int i = 0; i < t_pkt.size(); i++)
					{
						if (t_pkt[i] <= punkty && insert == false) {
							fprintf(plik, "%s %d\n", nazwa_Gracza, punkty);
							fprintf(plik, "%s %d\n", naz[i].c_str(), t_pkt[i]);
							insert = true;
						}
						else
							fprintf(plik, "%s %d\n", naz[i].c_str(), t_pkt[i]);
						cout << "\nZapisywanie\n";
						system("cls");
					}
					if (insert == false)
						fprintf(plik, "%s %d\n", nazwa_Gracza, punkty);

					fclose(plik);
				}

			}
		}
		else {
			if ((plik = fopen("plik_rankingowy.txt", "w")) == NULL) {
				cout << "\a\nNie udało się otworzyć pliku do zapisu\n";
			}
			else {
				fprintf(plik, "%s %d\n", nazwa_Gracza, punkty);
				fclose(plik);
			}
		}
		system("cls");
	}

	int f_punkty() {
		int zwroc = 0;
		for (int i = 0; i < moje_kostki.getTop(); i++)
		{
			zwroc += moje_kostki.wyswietl(i).getLiczba_l();
			zwroc += moje_kostki.wyswietl(i).getLiczba_p();
		}
		punkty_doOddania = zwroc;
		return zwroc;
	}

	void wylosuj_kostki(MyContener<KostkaLicz, 28> &kostkaTab)
	{
		int * wylosowane = new int[LICZK];
		int wylosowanych = 0;
		do {
			int wybd = rand() % +(kostkaTab.getTop());
			moje_kostki.push(kostkaTab.pop(wybd));
		} while (moje_kostki.getTop() < LICZK);
		delete[] wylosowane;
	}

	virtual int polozKostke(MyContener<KostkaLicz, 28> &kontener, UlozenieKostek &ulk)
	{
		bool czyOk;
		bool czyPobranoKostke = true;
		do {
			putchar('\n');
			ulk.wyswietl_kostki();
			this->wyswietlMoje_kostki();
			putchar('\n');
			int wyb;
			cout << "\nProszę wybrać kostkę:\t";
			while (true) {
				cin >> wyb;
				bool czyDobra = cin.good();
				if (czyDobra && wyb > 0)
					break;
				else {
					cout << "Niepoprawna dana proszę wybrać jeszcze raz:\t";
					std::cin.clear();
					std::cin.ignore(1000, '\n');
				}
			}
			if ((wyb - 1) == this->top())
			{
				czyOk = true;
				czyPobranoKostke = this->pobierz_Kostke(kontener);
				break;//przerwanie petli pobieramy kostke i juz dalej jej nie ukladamy
			}
			else if (wyb == this->top() + 2) {
				return 3;//przerwanie gry
			}
			czyOk = this->uluz_kostke(this->ukladanie(wyb - 1), ulk);//uloz kostke sprawdza czy kostka pasuje do ulozenia
			if (czyOk == false) {
				cout << "Nieprawidlowy wybór proszę wybrać kostkę jeszcze raz:\t";
				this->zwiekszTop();
				Sleep(1000);
				system("cls");
			}

		} while (czyOk == false);

		if (czyPobranoKostke == false)
		{
			bool czyDaSieUlozyc = this->czySaKostki(ulk);
			if (czyDaSieUlozyc == false)
				return 0;//nie da sie ulozyc
		}
		return 1;//da sie ulozyc
	}

	bool uluz_kostke(KostkaLicz newKostka, UlozenieKostek& ulk)
	{
		if (ulk.ostatnia() == newKostka.getLiczba_l()) {
			cout << "\nWstawiono kostke\n";
			ulk.pushU(newKostka);
			liczenie_punktow(ulk.pierwsza(), ulk.ostatnia(), newKostka.czyTakieSame());
			return true;
		}
		else if (ulk.ostatnia() == newKostka.getLiczba_p())
		{
			cout << "\nWstawiono kostke\n";//odwrocenie kostki i jej wstawienie
			newKostka.swap();
			ulk.pushU(newKostka);
			liczenie_punktow(ulk.pierwsza(), ulk.ostatnia(), newKostka.czyTakieSame());
			return true;
		}// tu sprawdza czy pierwsza mozna ulozyc
		else if (ulk.pierwsza() == newKostka.getLiczba_p())
		{
			cout << "\nWstawiono kostke\n";
			ulk.push_firstU(newKostka);
			liczenie_punktow(ulk.ostatnia(), ulk.pierwsza(), newKostka.czyTakieSame());
			return true;
		}
		else if (ulk.pierwsza() == newKostka.getLiczba_l()) {
			cout << "\nWstawiono kostke\n";//odwrocenie kostki i jej wstawienie
			newKostka.swap();
			ulk.push_firstU(newKostka);
			liczenie_punktow(ulk.ostatnia(), ulk.pierwsza(), newKostka.czyTakieSame());
			return true;
		}

		return false;

	}

};

class Komputer :public Gracz {

protected:

	void wyswietlMoje_kostki()
	{
		printf("\n\nGracz:\t%s\nTwoje kostki\n\n", nazwa_Gracza);
		for (int i = 0; i < moje_kostki.getTop(); i++) {
			printf("%i\t|%i|%i|\t\t", i + 1, moje_kostki.wyswietl(i).getLiczba_l(), moje_kostki.wyswietl(i).getLiczba_p());
			if (i % 2 == 1)
				putchar('\n');
		}
	}

public:

	Komputer(char *name) :Gracz(name) { ; }

	Komputer(char *name, int pkt) :Gracz(name, pkt) { ; }

	void wygrajRunde(Gracz &gr)
	{
		cout << "\n\nGracz " << nazwa_Gracza << " wygrał mecz\n\n";
		cout << "+=======================================================================================+\n";
		printf("Wynik meczu:Gracz %20s ||Gracz%20s:\t%3i:%3i\n", this->nazwa_Gracza, gr.getNazwa_Gracza(), this->punkty, gr.kto_wygral());
		cout << "+=======================================================================================+\n";
		Sleep(8000);
	}

	int polozKostke(MyContener<KostkaLicz, 28> &kontener, UlozenieKostek &ulk)
	{
		bool czyUlozono = false;
		bool czyPobranoKostke = true;
		for (int i = 0; i < this->moje_kostki.getTop(); i++)
		{
			if (this->moje_kostki.wyswietl(i).getLiczba_l() == ulk.ostatnia())
			{
				czyUlozono = this->uluz_kostke(this->ukladanie(i), ulk);
				cout << "\nKomputer ułożył kostke" << endl;
				break;
			}
			else if (this->moje_kostki.wyswietl(i).getLiczba_p() == ulk.ostatnia()) {
				czyUlozono = this->uluz_kostke(this->ukladanie(i), ulk);
				cout << "\nKomputer ułożył kostke" << endl;
				break;
			}
			else if (this->moje_kostki.wyswietl(i).getLiczba_p() == ulk.pierwsza()) {
				czyUlozono = this->uluz_kostke(this->ukladanie(i), ulk);
				cout << "\nKomputer ułożył kostke" << endl;
				break;
			}
			else if (this->moje_kostki.wyswietl(i).getLiczba_l() == ulk.pierwsza()) {
				czyUlozono = this->uluz_kostke(this->ukladanie(i), ulk);
				cout << "\nKomputer ułożył kostke" << endl;
				break;
			}

		}
		if (czyUlozono == false) {
			czyPobranoKostke = this->pobierz_Kostke(kontener);
			if (czyPobranoKostke == true)
				cout << "\nPobranie kostki\n";
		}
		if (czyPobranoKostke == false)
		{
			bool czyDaSieUlozyc = this->czySaKostki(ulk);
			if (czyDaSieUlozyc == false)
				return 0;//nie da sie ulozyc
		}
		return 1;//da sie ulozyc
	}
};

class Saving {

protected:

	int kogoRuch;
	int round;

public:

	Saving() :kogoRuch(0) {};

	Saving(int f_kogoRuch, int f_round) :kogoRuch(f_kogoRuch), round(f_round) {};

	~Saving() {};

	bool zapiss(UlozenieKostek &slista, MyContener<KostkaLicz, 28> &skoszyk, Gracz &sgracz1, Gracz &sgracz2, char TrybGry) {
		FILE *stream;
		if ((stream = fopen("plik_savingGame_list.txt", "w")) == NULL) {
			cout << "\a\nNie udało się otworzyć pliku do zapisu\n";
			return true;
		}
		else
			for (int i = 0; i < slista.lista.top; i++) {
				fprintf(stream, "%d %d\n", slista.lista.stos[i].getLiczba_l(), slista.lista.stos[i].getLiczba_p());
			}
		fclose(stream);
		//////////////
		if ((stream = fopen("plik_savingGame_koszyk.txt", "w")) == NULL) {
			cout << "\a\nNie udało się otworzyć pliku do zapisu\n";
			return true;
		}
		else
			for (int i = 0; i < skoszyk.top; i++) {
				fprintf(stream, "%d %d\n", skoszyk.stos[i].getLiczba_l(), skoszyk.stos[i].getLiczba_p());
			}
		fclose(stream);
		//////////////
		if ((stream = fopen("plik_savingGame_Gracz1.txt", "w")) == NULL) {
			cout << "\a\nNie udało się otworzyć pliku do zapisu\n";
			return true;
		}
		else
			for (int i = 0; i < sgracz1.moje_kostki.top; i++) {
				fprintf(stream, "%d %d\n", sgracz1.moje_kostki.stos[i].getLiczba_l(), sgracz1.moje_kostki.stos[i].getLiczba_p());
			}
		fclose(stream);
		//////////////
		if ((stream = fopen("plik_savingGame_Gracz2.txt", "w")) == NULL) {
			cout << "\a\Nie udało się otworzyć pliku do zapisu\n";
			return true;
		}
		else
			for (int i = 0; i < sgracz2.moje_kostki.top; i++) {
				fprintf(stream, "%d %d\n", sgracz2.moje_kostki.stos[i].getLiczba_l(), sgracz2.moje_kostki.stos[i].getLiczba_p());
			}
		fclose(stream);
		///////////////
		if ((stream = fopen("plik_savingGame_Tryb.txt", "w")) == NULL) {
			cout << "\a\nNie udało się otworzyć pliku do zapisu\n";
			return true;
		}
		else {
			fprintf(stream, "%c\n", TrybGry);//czy z komputerem czy z innym graczem
			fprintf(stream, "%d %d %d %d\n", sgracz1.punkty, sgracz2.punkty, kogoRuch, round);//po kolei punkty gracza1|punkty gracza2|ruch którego gracza|która runda
			fprintf(stream, "%s %s\n", sgracz1.nazwa_Gracza, sgracz2.nazwa_Gracza);
		}
		fclose(stream);
		return false;
	}
};

#endif