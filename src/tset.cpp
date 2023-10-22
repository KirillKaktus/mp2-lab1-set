// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : bf(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : bf(s.bf),MaxPower(s.MaxPower)
{}

// конструктор преобразования типа
TSet::TSet(const TBitField &_bf) : bf(_bf),MaxPower(_bf.GetLength())
{}

TSet::operator TBitField()
{
    return*this;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (bf.GetBit(Elem))
        return 1;
    else
        return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    bf.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    bf.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &set) // присваивание
{
    bf = set.bf;
    MaxPower = set.MaxPower;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{

    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet res(s);
    res.bf = bf | s.bf;
    res.MaxPower = res.bf.GetLength();
    return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res(*this);
    res.DelElem(Elem);
    return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    return *this;
}

TSet TSet::operator~(void) // дополнение
{
    return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &is, TSet &s) // ввод
{
    int m;
    char d;
    is >> d;
    while (d!=')')
    {
        is >> m;
        s.InsElem(m);
        is >> d;

    }
    return is;
}

ostream& operator<<(ostream &os, const TSet &s) // вывод
{
    os << "{";
    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.IsMember(i))
            os << i << " ";
    }
    os << "}";
    return os;
}
