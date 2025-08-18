#pragma once
#include "WidgetParent.h"
class wxTreeCtrl;

class InventorySearch : public WidgetParent
{
public:
	explicit InventorySearch(wxWindow* parent = nullptr, const wxString Title = "");
	virtual ~InventorySearch();

private:
	void BuildLayoutInit();

public:
	virtual void BtnTitleInit() override;
	virtual void LeftBodyInit() override;
	void LeftBottomInit();

	virtual void InfoTitleInit() override;
	virtual void RightBodyInit() override;

	

private:

	wxBoxSizer* shell = nullptr;
	wxTreeCtrl* TreeCtrl = nullptr;

	wxPanel* m_RightTopPanel;
	wxPanel* m_LeftBottmPanel;

	wxBoxSizer* m_TopSizer = nullptr;   // 본문(좌우) 배치용 H sizer
};

