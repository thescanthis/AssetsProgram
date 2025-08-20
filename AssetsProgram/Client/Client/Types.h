#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include <array>

class TemplateFunc;

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


#if 1 Protobuf Move
//Company - C,Product
struct C_Details
{
	std::array<wxString, 7> CompanyInfoArr = {};
	enum
	{
		C_Name,
		C_Numbering,
		Corp_Numbering,
		CorpPerson,
		C_Address,
		C_Type,
		C_Item
	};
};

struct I_Detalis
{
	wxString I_Product;
	wxString I_Year;
	wxString I_InvenNumber;
	wxString I_Client;
	wxString I_Itmes;
	wxString I_Uint;
	wxString I_Type;
	wxString I_BusinessName;
};
#endif

// Inventory Grid Info(Search,ClickInfo)
const wxString LabelStr[8] = { "��ǰ��","��¥","����ȣ","�ŷ�ó","����","����","���з�","�����" };
const int32 wid[8] = { 140,70,140,210,70,70,70,180 };

//ProductInfo,CompanyDetails
const wxString P_LabelStr[5] = { "","�����Ǻз�","����ȣ","��ǰ��","�԰�"};
const int32 P_gridWid[5] = { 0,70,140,140,70 };

//ClientInfo
const wxString C_LabelStr[4] = { "����","ȸ���","����ڹ�ȣ","��ǥ�ڸ�" };
const int32 C_gridWid[4] = { 30,170,90,50 };

extern TemplateFunc* Template;