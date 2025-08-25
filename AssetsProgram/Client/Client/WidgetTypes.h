#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include <array>
#include "Types.h"

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
const wxArrayString LabelStr = { "��ǰ��","��¥","��ǰ��ȣ","�ŷ�ó","����","����","���з�","�����" };
const int32 wid[8] = { 140,70,140,210,70,70,70,180 };

//ProductInfo
const wxArrayString P_LabelStr = {"��ǰ�ڵ�","��ǰ��"};
const int32 P_gridWid[2] = { 70,155};

//ClientInfo
const wxArrayString C_LabelStr = { "����","ȸ���","����ڹ�ȣ","��ǥ�ڸ�" };
const int32 C_gridWid[4] = { 30,170,90,50 };


extern class TemplateFunc* G_Template;
extern class DBTest* DBMaps;
