// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw "wrong size";
	else
		MemLen = len / 32 + 1;
	pMem = new TELEM[MemLen];
	BitLen = len;
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int res = n / 32;
	return res;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM t=1;
	int shift = n % 32;
	TELEM result = t << shift;
	return result;
	
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen)) throw "wrong size";
	else {
		TELEM m = GetMemMask(n);
		int idx = GetMemIndex(n);
		pMem[idx] = pMem[idx] | m;
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen)) throw "wrong size";
	else {
		TELEM m = ~(GetMemMask(n));
		int idx = GetMemIndex(n);
		pMem[idx] = pMem[idx] & m;
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen)) throw "wrong size";
	else {
		TELEM m = GetMemMask(n);
		int idx = GetMemIndex(n);
		TELEM res = m & pMem[idx];
		return res;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (MemLen != bf.MemLen)
	{
		delete[] pMem;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
	}
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
	{
		
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		for (int i = 0; i < (MemLen-1); i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				return false;
			}
		}
		return false;
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
		{
			return false;
		}
	}
	return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int maxL = bf.BitLen;
	if (BitLen > bf.BitLen) maxL = BitLen;
	TBitField res(maxL);
	for (int i = 0; i < MemLen; i++)
		res.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		res.pMem[i] = bf.pMem[i] | res.pMem[i];

	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	return* this;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++)
	{
		res.pMem[i] = ~(pMem[i]);
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &is, TBitField &bf) // ввод
{
	char a;
	for (int i = 0; i < bf.MemLen; i++)
	{
		bf.pMem[i] = 0;
	}
	for (int i = 0; i < bf.BitLen; i++) 
	{
		is >> a;
		if (a == '1') bf.SetBit(i);
		else 
			if (a == '0') bf.ClrBit(i);
		else break;
	}
	return is;
}

ostream &operator<<(ostream &os, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i)) os << '1';
		else os << '0';
	}
	return os;

}
