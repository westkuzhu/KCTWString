#include "stdafx.h"
#include "KCTWString.h"
//#include <iostream>
//#include <cstring>
//using namespace std;

namespace chart
{

//unordered_set< KCTWString::Data * , KCTWString::hash_func,KCTWString::hash_comp> KCTWString::s_MSet
//=unordered_set< KCTWString::Data * ,KCTWString::hash_func,KCTWString::hash_comp>();

MSR_DATA KCTWString::s_SharedNull ={ L"", 0, 1};

void KCTWString::test()
{
	KCTWString a(L"a");
	KCTWString bc = L"bc";
	KCTWString abc = a + bc ;

	a += abc;

	bc.Append(10 , L'X');

	a.Insert(2, 3, L'O');

	abc.Insert(0,L"OOXX",3);

}

KCTWString::KCTWString (void)
{
	m_Data = &s_SharedNull;

	msrReferStringResource(m_Data);
}

KCTWString::KCTWString (const KCTWString &s)
{
	m_Data = s.m_Data;

	msrReferStringResource(m_Data);
}

KCTWString::KCTWString (PCWSTR str)
{
	if(!str) 
	{
		m_Data = &s_SharedNull;
		msrReferStringResource(m_Data);
	}

	else 
	{		
		m_Data = msrIdentifyStringResource(str);
	}
}

KCTWString& KCTWString::operator = (const KCTWString &other)
{
	if(m_Data == other.m_Data) return *this;

	msrUnreferStringResource(m_Data);

	if(other.m_Data == &s_SharedNull)
	{
		m_Data = &s_SharedNull;
		msrReferStringResource(m_Data);

	}
	else 
	{
		m_Data = other.m_Data;
		msrReferStringResource(m_Data);
	}

	return *this;
}

KCTWString& KCTWString::operator = (PCWSTR str)
{
	if(!wcscmp(m_Data->get_value() , str)) return *this;

	msrUnreferStringResource(m_Data);

	if(!str)
	{
		m_Data = &s_SharedNull;
		msrReferStringResource(m_Data);
	}
	else
	{
		m_Data = msrIdentifyStringResource(str);
	}
	return *this;
}

KCTWString operator + (const KCTWString &lhs, const KCTWString &rhs)
{
	KCTWString s = lhs;
	s += rhs;
	return s;
}

KCTWString& KCTWString::operator += (const KCTWString &other)
{
	if(other.m_Data == &s_SharedNull) return *this;


	if(m_Data == &s_SharedNull ) 
	{
		msrUnreferStringResource(m_Data);
		m_Data = msrIdentifyStringResource(other.m_Data->get_value());
		return *this;
	}

	size_t sizeSum = m_Data->get_length()+other.m_Data->get_length();
	LPWSTR strSum = (LPWSTR)AlgAlloc2(sizeof(WCHAR) * (sizeSum + 1));
	memcpy(strSum, m_Data->get_value(), m_Data->get_length()*sizeof(WCHAR));
	memcpy(strSum + m_Data->get_length(),  other.m_Data->get_value(), other.m_Data->get_length()*sizeof(WCHAR));

	strSum[sizeSum] = 0;

	msrUnreferStringResource(m_Data);
	m_Data = msrIdentifyStringResource(strSum);

	delete[] strSum;
	return *this;
}

KCTWString& KCTWString::operator += (PCWSTR str)
{
	if(!str) return *this;

	if( m_Data == &s_SharedNull ) 
	{
		msrUnreferStringResource(m_Data);
		m_Data = msrIdentifyStringResource(str);
		return *this;
	}

	size_t sizeSum = GetLength() + wcslen(str);
	LPWSTR strSum = (LPWSTR)AlgAlloc2(sizeof(WCHAR) * (sizeSum + 1));
	memcpy(strSum, GetValue(), GetLength()*sizeof(WCHAR));
	memcpy(strSum + GetLength(), str, wcslen(str)*sizeof(wchar_t));
	strSum[sizeSum] = 0;

	msrUnreferStringResource(m_Data);
	m_Data = msrIdentifyStringResource(strSum);
	//释放临时数组
	delete[] strSum;
	return *this;
}



KCTWString& KCTWString::Append(const KCTWString &other)
{
	return (*this) += other;
}

KCTWString& KCTWString::Append(PCWSTR str)
{
	return *this += str;
}

KCTWString& KCTWString::Append(size_t len, WCHAR c)
{
	if(len <= 0) return *this;

	LPWSTR strSum = (LPWSTR)AlgAlloc2(sizeof(WCHAR) * (GetLength() + len + 1));
	memcpy(strSum, GetValue(), GetLength()*sizeof(WCHAR));
	wmemset(strSum + GetLength(), c, len);

	strSum[GetLength() + len] = 0;

	msrUnreferStringResource(m_Data);
	m_Data = msrIdentifyStringResource(strSum);

	delete[] strSum;
	return *this;
}

KCTWString& KCTWString::Append(PCWSTR str, size_t len)
{
	if(!str || len<=0) return *this;

	if( len > wcslen(str)) len = wcslen(str);

	LPWSTR strSum = (LPWSTR)AlgAlloc2(sizeof(WCHAR) * (GetLength() + len + 1));
	memcpy( strSum, GetValue(), GetLength() * sizeof(WCHAR));
	memcpy( strSum + GetLength(), str, len * sizeof(wchar_t));

	strSum[GetLength() + len] = 0;

	msrUnreferStringResource(m_Data);
	m_Data = msrIdentifyStringResource(strSum);

	delete [] strSum;
	return *this;
}

KCTWString& KCTWString::Append (const KCTWString &other, size_t subpos, size_t sublen)
{
	if( other.IsEmpty() || sublen<=0 || subpos >= other.GetLength()) return *this;

	if(subpos < 0) 
	{
		subpos = 0;
	}

	if( subpos + sublen > other.GetLength() ) 
		sublen = other.GetLength() - subpos ;

	LPWSTR strSum = (LPWSTR)AlgAlloc2(sizeof(WCHAR) * (GetLength() + sublen + 1));

	memcpy(strSum, GetValue(), GetLength()*sizeof(WCHAR) );
	memcpy(strSum + GetLength(), other.GetValue() + subpos, sublen*sizeof(WCHAR));

	strSum[GetLength() + sublen] = 0;

	msrUnreferStringResource(m_Data);
	m_Data = msrIdentifyStringResource(strSum);

	delete[] strSum;

	return *this;
}

KCTWString& KCTWString::Insert(size_t pos, PCWSTR str)
{
	return Insert(pos, str, wcslen(str));
}

KCTWString& KCTWString::Insert(size_t pos, PCWSTR str, size_t len)
{
	if(pos < 0 || pos >= GetLength() || !str)  
	{
		return *this;
	}

	if(len > wcslen(str)) len = wcslen(str);

	LPWSTR strSum = (LPWSTR)AlgAlloc2(sizeof(WCHAR) * (GetLength() + len + 1));

	memcpy(strSum, GetValue(), pos*sizeof(WCHAR));
	memcpy(strSum + pos, str, len*sizeof(WCHAR));
	memcpy(strSum + pos + len, GetValue() + pos, (GetLength() - pos)*sizeof(WCHAR));

	strSum[GetLength() + len] = 0;

	msrUnreferStringResource(m_Data);
	m_Data = msrIdentifyStringResource(strSum);

	delete[] strSum;

	return *this;
}

KCTWString& KCTWString::Insert(size_t pos, const KCTWString &other)
{
	return Insert(pos, other.GetLength(), other.GetLength());
}

KCTWString& KCTWString::Insert(size_t pos, const KCTWString &other, size_t len)
{
	return Insert(pos, other.GetValue(), len);
}

KCTWString& KCTWString::Insert(size_t pos,  size_t len, wchar_t c)
{
	LPWSTR str = (LPWSTR)AlgAlloc2(sizeof(WCHAR) * (len + 1));
	wmemset(str, c, len);
	str[len] = 0;

	*this = Insert(pos, str, len);

	delete[] str;

	return *this;
}

bool KCTWString::IsEmpty() const
{
	return (m_Data == &s_SharedNull);
}

/*
void KCTWString::ReduceRefer()
{	
	d->refer--;

	if(d == &s_SharedNull) return;

	if(d->refer<=0)
	{
		auto it = s_MSet.find(d);
		if(it != s_MSet.end()) s_MSet.erase(d);
		delete[] d->str;
		delete d;
		d = NULL;
	}
}
void KCTWString::AddData(Data& v)
{

	auto it = s_MSet.find(&v);

	//存在则更新ref
	if(it != s_MSet.end())
	{
		d = *it;
		d->refer++;
	}
	//不存在则插入新数据
	else
	{
		size_t strLength = v.size;
		d = (Data*) malloc(sizeof(Data));		 
		d->str = new wchar_t[strLength + 1];
		memcpy(d->str, v.str, (strLength + 1)*sizeof(wchar_t));
		d->size = strLength;
		d->refer = 1;
		s_MSet.insert(d);	  
	}
}
*/
void KCTWString::print()
{
	//待写
   return;
}

void KCTWString::pdata()
{
	//待写
	return;
}

KCTWString::~KCTWString()
{
	msrUnreferStringResource(m_Data);
	m_Data = NULL;
}

}//namespace chart