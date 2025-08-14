#pragma once
#include <wx/wx.h>
#include <wx/grid.h>

using BYTE = unsigned char;
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

enum
{
	T_COMPANY = 0,
	T_INVENTORY = 1
};


//Company - C
struct C_Details
{
	wxString C_Name;
	wxString C_Numbering;
	wxString Corp_Numbering;
	wxString CorpPerson;
	wxString C_Address;
	wxString C_Type;
	wxString C_Item;
};