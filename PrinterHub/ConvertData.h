#pragma once
#include <string>
class ConvertData
{
public:	ConvertData();
	  ~ConvertData();
	  static std::string CStringToString(const CString& cstr);
	  static CString StringToCString(const std::string& str);
};

