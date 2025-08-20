#pragma once
#include "MaskedTextCtrl.h"
#include "WidgetParent.h"
class WidgetParent : public wxFrame
{
public:
	explicit WidgetParent(wxWindow* parent = nullptr, const wxString Title = "", wxSize Size = {800,600});
	virtual ~WidgetParent();

	virtual void BtnTitleInit() = 0;
	virtual void LeftBodyInit() = 0;
	virtual void InfoTitleInit() = 0;
	virtual void RightBodyInit() = 0;

protected:
	void TitleFontInit(wxStaticText* title,int AddFontSize=0);

	enum
	{
		B_CLASS = 0,  // Business
		M_CLASS = 1,  // Material
		I_CLASS = 2,  // Inventory
		P_CLASS = 3,  // PRODUCT
		UP_CLASS = 4, // UNIT PRICE
		U_CLASS = 5,  // UINT
		IS_CLASS = 6  // ITEM_SEND
	};

	const int32 InventoryPick[5] = { B_CLASS,M_CLASS ,I_CLASS ,P_CLASS, IS_CLASS };

	std::array<wxString, 7> InventoryTitle = {
		"사업분류",
		"자제실분류",
		"재고번호",
		"상품명",
		"구매단가",
		"단위",
		"입고량"
	};

protected:
	C_Details Infomation;
	wxPanel* m_panel, * m_TopPanel, * m_LeftPanel, * m_RightPanel;
	wxBoxSizer* m_bodySizer = nullptr;   // 본문(좌우) 배치용 H sizer

	std::vector<wxStaticText*> InfoTitle;
	std::vector<wxTextCtrl*>   InfoEdit;

	wxGrid* m_grid;
};

