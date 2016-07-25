// -------------------------------------------------------------------------- //
//	文件名	:	kctwstring.h
//	创建者	:	朱星霈
//	创建时间: 	2016-7-21	10:36
//	功能描述:  基于共享字符串池的字符串类
//
// -------------------------------------------------------------------------- //
#pragma once
#ifndef _MSTRING_H_
#define _MSTRING_H_

#include "../../kfc/include/alg/msr.h"


using namespace alg;

namespace chart
{
class KCTWString
{
	friend KCTWString operator + (const KCTWString &lhs, const KCTWString &rhs);
public:
	KCTWString(void);
	KCTWString (const KCTWString &s);
	KCTWString (PCWSTR str);
	KCTWString (PCWSTR str, size_t len);	
	~KCTWString(void);

	KCTWString& operator = (const KCTWString &other);
	KCTWString& operator = (PCWSTR str);

	KCTWString& operator += (const KCTWString &other);
	KCTWString& operator += (PCWSTR str);

	KCTWString& Append (const KCTWString &other);
	KCTWString& Append (const KCTWString &other, size_t pos, size_t sublen);
	KCTWString& Append (PCWSTR str);
	KCTWString& Append (PCWSTR str, size_t len);
	KCTWString& Append (size_t len, wchar_t c);

	KCTWString& Insert (size_t pos, PCWSTR str);
	KCTWString& Insert (size_t pos, PCWSTR str, size_t len);
	KCTWString& Insert (size_t pos, const KCTWString &other);
	KCTWString& Insert (size_t pos, const KCTWString &other, size_t len);
	KCTWString& Insert (size_t pos,  size_t len, wchar_t c);

	size_t GetLength() const { return m_Data->get_length(); }
	PCWSTR GetValue() const { return m_Data->get_value();}
	bool IsEmpty()const;
	void print();
	void pdata();

	static void test();

private:

	/*
	struct Data{
		wchar_t *str;
		size_t size;
		size_t refer;
	};

	Data *d;

	//自定义哈希函数
	struct hash_func
	{
		size_t operator()(const Data* d)const
		{
			size_t value = _HASH_SEED;
			size_t size = d->size;
			if (size > 0) {
				size_t temp = (size / 16) + 1;
				size -= temp;
				for (size_t idx = 0; idx <= size; idx += temp) {
					value += (size_t)d->str[(int)idx];
				}
			}
			return value;
		}
	};

	//自定义哈希equal_to
	struct hash_comp
	{
		bool operator()(const Data *lhs, const Data *rhs) const
		{
			return (!wcscmp(lhs->str, rhs->str));
		}
	};

	static unordered_set< Data* , hash_func , hash_comp > s_MSet;

	static Data s_SharedNull;
	*/

	MSR_HANDLE m_Data;

	static MSR_DATA s_SharedNull;



};

}//namespace chart

#endif // KCTWSTRING_H