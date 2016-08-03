#include "stdafx.h"
#include "KCTWString.h"

//#include <iostream>
//#include <cstring>
//using namespace std;

namespace chart
{


void KCTWString::test()
{
	KCTWString emp;

	KCTWString a(L"a");

	KCTWString bc = L"bc";
	
	KCTWString bc2 = bc;

	emp = a;

    bc.Append(L"1234567",2,4);

	a += bc;

	a += emp;

	KCTWString abca;

	abca = L"abca";

	abca.Append(bc2);
	abca.Append(L"XXOO");
	abca.Append(L"123456",4);
	abca.Append(6,L'M');

	abca.Insert(3,L"cao");
	abca.Insert(2,L"PPPP",3);
	abca.Insert(2,bc);
	abca.Insert(3,a,1,3);
	abca.Insert(2,3,L'F');

	int pos = abca.Find(L"PPP");

	KCTWString sub = abca.SubStr(3,5);

	abca.Replace(3,5,bc);

	KCTWString s1(L"S1");
	KCTWString s2(L"S2");
	KCTWString s3(L"S3");
	KCTWString s4(L"S4");
	KCTWString s5(L"S5");
	KCTWString s6(L"bc");
	KCTWString s7 = abca;

	KCTWString sum = Muticat(&s1,&s2,&s3,&s4,&s5,&s6,&s7,NULL);


	KCTWString n1;
	KCTWString n2;


	KCTWString testNULL = Muticat(&n1,&n2,NULL);

	KCTWString testMid = Muticat(&n1,&s1,&n2,NULL);

	KCTWString testpre = Muticat(&s1,&n1,&n2,NULL);
}

KCTWString::KCTWString (void)
{	
	m_Data = NULL;
    
}

KCTWString::KCTWString (const KCTWString &s)
{
	if(s.IsEmpty())
	{
		m_Data = NULL;
	}
	else
	{
		m_Data = s.m_Data;

		msrReferStringResource(m_Data);
	}
}

KCTWString::KCTWString (PCWSTR str)
{
	if(!str || !(*str)) 
	{
		m_Data = NULL;
	}

	else 
	{
		m_Data = msrIdentifyStringResource(str);
	}
}

KCTWString& KCTWString::operator = (const KCTWString &other)
{
	if(m_Data == other.m_Data) return *this;

	UnRefer();
	m_Data = other.m_Data;
	if(!IsEmpty())
		msrReferStringResource(m_Data);
	return *this;
}

KCTWString& KCTWString::operator = (PCWSTR str)
{
	if(!IsEmpty())
	{
		if(!wcscmp(GetValue() , str)) return *this;
	}

	UnRefer();

	if(!str || !(*str))
	{
		m_Data = NULL;
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
	s.Append(rhs);
	return s;
}

KCTWString& KCTWString::operator += (const KCTWString &other)
{
	Append(other.GetValue());
	return *this;
}

KCTWString& KCTWString::operator += (PCWSTR str)
{
	Append(str);
	return *this;
}



KCTWString& KCTWString::Append(const KCTWString &other)
{
	Append(other.GetValue());
	return *this;
}

KCTWString& KCTWString::Append(PCWSTR str)
{
	if(!str || !(*str)) return *this;

	if(IsEmpty()) 
	{;
	m_Data = msrIdentifyStringResource(str);
	return *this;
	}

	ks_wstring strSum;
	strSum.append(GetValue());
	strSum.append(str);
	UnRefer();
	m_Data = msrIdentifyStringResource(strSum.c_str());
	return *this;
}

KCTWString& KCTWString::Append(size_t len, WCHAR c)
{
	if(len <= 0) return *this;

	ks_wstring strSum;
	if(!IsEmpty())
	{
		strSum.append(GetValue());
	}
	strSum.append(len,c);
	UnRefer();
	m_Data = msrIdentifyStringResource(strSum.c_str());

	return *this;
}

KCTWString& KCTWString::Append(PCWSTR str, size_t len)
{
	if(!str || !(*str) || len <= 0) return *this;

	if( len > wcslen(str)) len = wcslen(str);

	ks_wstring strSum;

	if(!IsEmpty())
	{
		strSum.append(GetValue());
	}
	strSum.append(str,len);
	UnRefer();
	m_Data = msrIdentifyStringResource(strSum.c_str());

	return *this;
}

KCTWString& KCTWString::Append (const KCTWString &other, size_t subpos, size_t sublen)
{
	if( other.IsEmpty() || sublen <= 0 || subpos >= other.GetLength()) 
		return *this;

	if(subpos < 0) 
		subpos = 0;


	if( subpos + sublen > other.GetLength() ) 
		sublen = other.GetLength() - subpos ;

	ks_wstring strSum;
	if(!IsEmpty())
	{
		strSum.append(GetValue());
	}
	strSum.append(other.GetValue(), subpos, sublen);

	UnRefer();
	m_Data = msrIdentifyStringResource(strSum.c_str());

	return *this;
}


KCTWString& KCTWString::Insert(size_t pos, PCWSTR str)
{
	if(!str || !(*str)) return *this;

	Insert(pos, str, wcslen(str));
	 return *this;
}

KCTWString& KCTWString::Insert(size_t pos, PCWSTR str, size_t len)
{

	if(pos < 0 || pos >= GetLength() || !str || !(*str))
		return *this;

	if(len > wcslen(str)) len = wcslen(str);

	ks_wstring strSum;
	if(IsEmpty())
	{
		strSum.append(str,len);
	}
	else
	{
		if(pos != 0) strSum.append(GetValue(),pos);
		strSum.append(str,len);
		strSum.append(GetValue() + pos , GetLength() - pos);
	}

	UnRefer();
	m_Data = msrIdentifyStringResource(strSum.c_str());

	return *this;
}

KCTWString& KCTWString::Insert(size_t pos, const KCTWString &other)
{
	if(!other.IsEmpty())
		Insert(pos, other.GetValue());
	return *this;
}

KCTWString& KCTWString::Insert(size_t pos, const KCTWString &other, size_t subpos, size_t sublen)
{
	if( pos > GetLength() ||other.IsEmpty() || subpos >= other.GetLength() || sublen <= 0)
		return *this;

	if(subpos + sublen > other.GetLength()) 
		sublen = other.GetLength() - subpos;

	ks_wstring strSum;
	strSum.append(other.GetValue(),subpos,sublen);

	Insert(pos, strSum.c_str());
	return *this;
}

KCTWString& KCTWString::Insert(size_t pos,  size_t len, WCHAR c)
{
	ks_wstring strSum;

	strSum.append(len,c);

	Insert(pos, strSum.c_str());

	return *this;
}

bool KCTWString::IsEmpty() const
{
	return (m_Data == NULL || GetLength() == 0);
}

void KCTWString::UnRefer()
{
	if(m_Data != NULL) 
	msrUnreferStringResource(m_Data);
}

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
	UnRefer();
}

size_t KCTWString::GetLength() const
{
	if(m_Data == NULL) return 0;
	
	else return (size_t)msrGetStringResourceLen(m_Data);
}

PCWSTR KCTWString::GetValue() const
{
	if(m_Data == NULL) return NULL;
	
	else return msrGetStringResourceValue(m_Data);
}

KCTWString KCTWString::SubStr( size_t pos, size_t len )
{
	KCTWString sub;
	if(!IsEmpty() && pos < GetLength() && len > 0)
	{
		if(pos + len > GetLength())
			len = GetLength() - pos;

		ks_wstring strSub;
		strSub.append(GetValue(),pos,len);
		sub = strSub.c_str();
	}
	return sub;
}

int KCTWString::Find( PCWSTR tar )
{
	 PCWSTR sur = GetValue();
	 int sur_len = (int) GetLength();
	 int tar_len = (int) wcslen(tar);

	 int i = 0;
	 int j = 0;

	 int head = 0;
	 int fence = tar_len;
	 int search;
	 int count;

	 if ((!sur) || (!tar)|| sur_len < tar_len )
		 return -1;

	 while ( i < sur_len && j < tar_len){
		if (sur[i] == tar[j])
		{
			if(j == (tar_len - 1)) 
				return head;
			i++;
			j++;
			continue;
		}
		else
		{
			search = tar_len - 1;
			count = 1;
			while(search >= 0)
			{
				if(sur[fence] == tar[search]) break;
				search--;
				count++;
			}
			head += count;
			fence += count;
			if(head + tar_len -1 >= sur_len) return -1;

			i = head;
			j = 0;
		}
	}
	 return  -1;
}

KCTWString& KCTWString::Replace( size_t pos, size_t len, const KCTWString &other )
{
	if(pos > GetLength() || len <= 0)
		return *this;

	ks_wstring strRep;
	if(pos < 0) 
		pos = 0;
	if(pos > 0)
	strRep.append(GetValue(),0,pos);
	strRep.append(other.GetValue());
	strRep.append(GetValue() + pos + len);

	UnRefer();
	m_Data = msrIdentifyStringResource(strRep.c_str());

	return *this;
}



KCTWString KCTWString::Muticat( const KCTWString* fmt,... )
{
	KCTWString result;
	KCTWString *src = (KCTWString*) fmt;

	if(src == NULL) return result;

	ks_wstring str;
	va_list valist;
	va_start(valist, fmt);
	for(;;)
	{
		str.append(src->GetValue());
		if((src = va_arg(valist,KCTWString *)) == NULL) break;
	}
	va_end(valist);

	result = str.c_str();

	return result;
}

}//namespace chart