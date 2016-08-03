// -------------------------------------------------------------------------- //
//	文件名	:	kctwstring.h
//	创建者	:	朱星霈
//	创建时间: 	2016-7-21	10:36
//	功能描述:  基于共享字符串池的字符串类
//
// -------------------------------------------------------------------------- //
#pragma once
#ifndef _KCTWSTRING_H_
#define _KCTWSTRING_H_

#include "../../kfc/include/alg/msr.h"


using namespace alg;

namespace chart
{
class KCTWString
{
	friend KCTWString operator + (const KCTWString &lhs, const KCTWString &rhs);
public:
	KCTWString  (void);
	KCTWString  (const KCTWString &s);
	KCTWString  (PCWSTR str);
	KCTWString  (PCWSTR str, size_t len);	
	~KCTWString (void);

	KCTWString& operator = (const KCTWString &other);
	KCTWString& operator = (PCWSTR str);

	KCTWString& operator += (const KCTWString &other);
	KCTWString& operator += (PCWSTR str);

	KCTWString& Append (const KCTWString &other);
	KCTWString& Append (const KCTWString &other, size_t subpos, size_t sublen); 
	KCTWString& Append (PCWSTR str);
	KCTWString& Append (PCWSTR str, size_t len);
	KCTWString& Append (size_t len, WCHAR c);

	KCTWString& Insert (size_t pos, PCWSTR str);
	KCTWString& Insert (size_t pos, PCWSTR str, size_t len);
	KCTWString& Insert (size_t pos, const KCTWString &other);
	KCTWString& Insert (size_t pos, const KCTWString &other, size_t subpos, size_t sublen);
	KCTWString& Insert (size_t pos, size_t len, WCHAR c);

	KCTWString& Replace (size_t pos, size_t len, const KCTWString &other);

	KCTWString SubStr (size_t pos, size_t len);
	
	int Find(PCWSTR tar);
	size_t GetLength() const;
	PCWSTR GetValue() const;
	bool IsEmpty()const;
	void print();
	void pdata();
	void UnRefer();

	static void test();
	static KCTWString Muticat(const KCTWString* fmt,...);

private:

	MSR_HANDLE m_Data;

};

}//namespace chart

#endif // KCTWSTRING_H