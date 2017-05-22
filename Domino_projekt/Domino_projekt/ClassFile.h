#pragma once
#ifndef ClassFile_hpp
#define ClassFile_hpp

#pragma once
#define MAX 20
#define LICZK 7

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<ctime>
#include<stdlib.h>
#include<Windows.h>

using namespace std;

template<typename T, int rozmiar>
class MyContener {
	T stos[rozmiar];
	int top;
public:
	int getTop()
	{
		return top;
	}
	MyContener() : top(0) {}
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

	int ostatnia()//dla klasy Komputer zwraca ostatni numer kostki
	{
		return lista.wyswietl(lista.getTop() - 1).getLiczba_p();
	}

	void pierwsza_kostka(MyContener<KostkaLicz, 28> &kostkaTab)
	{
		int wyb = rand() % kostkaTab.getTop();
		lista.push(kostkaTab.pop(wyb));
	}

	void wyswietl_kostki()
	{
		cout << "\nUlo¿enie kostek:\n\n";
		for (int i = 0; i < lista.getTop(); i++) {
			printf("|%i|%i| ", lista.wyswietl(i).getLiczba_l(), lista.wyswietl(i).getLiczba_p());
		}
	}

	bool uluz_kostke(KostkaLicz newKostka)
	{
		if (lista.wyswietl(lista.getTop() - 1).getLiczba_p() == newKostka.getLiczba_l()) {
			cout << "\nWstawiono kostke\n";
			lista.push(newKostka);
			return true;
		}
		else if (lista.wyswietl(lista.getTop() - 1).getLiczba_p() == newKostka.getLiczba_p())
		{
			cout << "\nWstawiono kostke\n";
			newKostka.swap();
			lista.push(newKostka);
			return true;
		}
		else
			return false;

	}
};

class Gracz
{
protected:
	char nazwa_Gracza[MAX];
	int punkty;
	MyContener<KostkaLicz, LICZK + 4> moje_kostki;

	virtual void wyswietlMoje_kostki()
	{
		printf("\n\nGracz:\t%s\nTwoje kostki\n\n", nazwa_Gracza);
		for (int i = 0; i < moje_kostki.getTop(); i++) {
			printf("%i\t|%i|%i|\t\t", i + 1, moje_kostki.wyswietl(i).getLiczba_l(), moje_kostki.wyswietl(i).getLiczba_p());
			if (i % 2 == 1)
				putchar('\n');
		}
		printf("\n\n%i\tPobranie kostki", moje_kostki.getTop() + 1);
	}

	void zwiekszTop()
	{
		moje_kostki.setTop();
	}

	KostkaLicz ukladanie(int i)
	{
		return moje_kostki.pop(i);
	}

	void pobierz_Kostke(MyContener<KostkaLicz, 28> &kontener)
	{
		int ran = rand() % kontener.getTop();
		moje_kostki.push(kontener.pop(ran));
	}

public:

	Gracz(char *nazwaGracza)
	{
		strcpy(this->nazwa_Gracza, nazwaGracza);
		punkty = 0;
		cout << "=========================================================" << endl;
		cout << "Ustawiono nazwê gracza na :\t" << nazwa_Gracza << endl;
		cout << "=========================================================" << endl << endl;
	}

	int top()
	{
		return moje_kostki.getTop();
	}

	void wygrana()
	{
		printf("Brawo !!!\nGracz:\t%s Wygra³!!!!\n\n", nazwa_Gracza);
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
	
	virtual void polozKostke(MyContener<KostkaLicz, 28> &kontener, UlozenieKostek &ulk)
	{
		bool czyOk;
		do {
			putchar('\n');
			ulk.wyswietl_kostki();
			this->wyswietlMoje_kostki();
			putchar('\n');
			int wyb;
			cout << "\nProszê wybraæ kostkê:\t";
			cin >> wyb;
			if ((wyb - 1) == this->top())
			{
				czyOk = true;
				this->pobierz_Kostke(kontener);
				break;
			}
			czyOk = ulk.uluz_kostke(this->ukladanie(wyb - 1));
			if (czyOk == false) {
				cout << "Nieprawidlowy wybór proszê wybraæ kostkê jeszcze raz:\t";
				this->zwiekszTop();
				Sleep(1000);
				system("cls");
			}
		} while (czyOk == false);
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

	Komputer(Gracz gr) :Gracz(gr) { ; }

	void polozKostke(MyContener<KostkaLicz, 28> &kontener, UlozenieKostek &ulk)
	{
		this->wyswietlMoje_kostki();
		bool czyUlozono = false;
		for (int i = 0; i < this->moje_kostki.getTop(); i++)
		{
			if (this->moje_kostki.wyswietl(i).getLiczba_l() == ulk.ostatnia())
			{
				czyUlozono = ulk.uluz_kostke(this->ukladanie(i));
				cout << "\nKomputer ulozyl kostke" << endl;
				break;
			}
			else if (this->moje_kostki.wyswietl(i).getLiczba_p() == ulk.ostatnia()) {
				czyUlozono = ulk.uluz_kostke(this->ukladanie(i));
				cout << "\nKomputer ulozyl kostke" << endl;
				break;
			}
			
		}
		if(czyUlozono==false) {
			this->pobierz_Kostke(kontener);
			cout << "\nPobranie kostki\n";
		}
		Sleep(3000);
		system("cls");
	}

	
	
};

#endif

//int * wylosowane = new int[size];
//int wylosowanych = 0;
//if (wyb == 1) {
//	do {
//		int wybd;
//		wyswietl(v, wylosowane, size, tmp);
//		cout << "Proszê wybraæ dru¿yny z listy:\n";
//		cout << "Twoj wybór:\t";
//		cin >> wybd;
//		if (czyBylaWylosowana(wybd - 1, wylosowane, wylosowanych) == false)
//		{
//			tmp.push_back(v[wybd - 1]);//tu bylo v
//			wylosowane[wylosowanych] = wybd - 1;
//			wylosowanych++;
//		}
//		else {
//			cout << "Dru¿yna ju¿ wybana, proszê wybraæ jeszcze raz" << endl;
//			Sleep(1000);
//		}
//	} while (wylosowanych < size);
//	delete[] wylosowane;
//}

//template <class T>
//class  Vector {
//public:
//
//	typedef T* Iterator;
//
//	Vector();
//	Vector(unsigned int size);
//	Vector(unsigned int size, const T & initial);
//	Vector(const Vector<T>& v);
//	~Vector();
//
//	unsigned int capacity() const;
//	unsigned int size() const;
//	bool empty() const;
//	Iterator begin();
//	Iterator end();
//	T& front();
//	T& back();
//	void push_back(const T& value);
//	void pop_back();
//
//	void reserve(unsigned int capacity);
//	void resize(unsigned int size);
//
//	T & operator[](unsigned int index);
//	Vector<T> & operator = (const Vector<T> &);
//	void clear();
//private:
//	unsigned int _size;
//	unsigned int _capacity;
//	unsigned int Log;
//	T* buffer;
//};
//
//template<class T>
//Vector<T>::Vector() {
//	_capacity = 0;
//	_size = 0;
//	buffer = 0;
//	Log = 0;
//}
//
//template<class T>
//Vector<T>::Vector(const Vector<T> & v) {
//	_size = v._size;
//	Log = v.Log;
//	_capacity = v._capacity;
//	buffer = new T[_size];
//	for (unsigned int i = 0; i < _size; i++)
//		buffer[i] = v.buffer[i];
//}
//
//template<class T>
//Vector<T>::Vector(unsigned int size) {
//	_size = size;
//	Log = ceil(log((double)size) / log(2.0));
//	_capacity = 1 << Log;
//	buffer = new T[_capacity];
//}
//
//template <class T>
//bool Vector<T>::empty() const {
//	return _size == 0;
//}
//
//template<class T>
//Vector<T>::Vector(unsigned int size, const T& initial) {
//	_size = size;
//	Log = ceil(log((double)size) / log(2.0));
//	_capacity = 1 << Log;
//	buffer = new T[_capacity];
//	for (unsigned int i = 0; i < size; i++)
//		buffer[i] = initial;
//}
//
//template<class T>
//Vector<T>& Vector<T>::operator = (const Vector<T> & v) {
//	delete[] buffer;
//	_size = v._size;
//	Log = v.Log;
//	_capacity = v._capacity;
//	buffer = new T[_capacity];
//	for (unsigned int i = 0; i < _size; i++)
//		buffer[i] = v.buffer[i];
//	return *this;
//}
//
//template<class T>
//typename Vector<T>::Iterator Vector<T>::begin() {
//	return buffer;
//}
//
//template<class T>
//typename Vector<T>::Iterator Vector<T>::end() {
//	return buffer + size();
//}
//
//template<class T>
//T& Vector<T>::front() {
//	return buffer[0];
//}
//
//template<class T>
//T& Vector<T>::back() {
//	return buffer[_size - 1];
//}
//
//template<class T>
//void Vector<T>::push_back(const T & v) {
//	/*
//	Incidentally, one common way of regrowing an array is to double the size as needed.
//	This is so that if you are inserting n items at most only O(log n) regrowths are performed
//	and at most O(n) space is wasted.
//	*/
//	if (_size >= _capacity) {
//		reserve(1 << Log);
//		Log++;
//	}
//	buffer[_size++] = v;
//}
//
//template<class T>
//void Vector<T>::pop_back() {
//	_size--;
//}
//
//template<class T>
//void Vector<T>::reserve(unsigned int capacity) {
//	T * newBuffer = new T[capacity];
//
//	for (unsigned int i = 0; i < _size; i++)
//		newBuffer[i] = buffer[i];
//
//	_capacity = capacity;
//	delete[] buffer;
//	buffer = newBuffer;
//}
//
//template<class T>
//unsigned int Vector<T>::size() const {
//	return _size;
//}
//
//template<class T>
//void Vector<T>::resize(unsigned int size) {
//	Log = ceil(log((double)size) / log(2.0));
//	reserve(1 << Log);
//	_size = size;
//}
//
//template<class T>
//T& Vector<T>::operator[](unsigned int index) {
//	return buffer[index];
//}
//
//template<class T>
//unsigned int Vector<T>::capacity()const {
//	return _capacity;
//}
//
//template<class T>
//Vector<T>::~Vector() {
//	delete[] buffer;
//}
//
//template <class T>
//void Vector<T>::clear() {
//	_capacity = 0;
//	_size = 0;
//	buffer = 0;
//	Log = 0;
//}