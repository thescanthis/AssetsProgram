#pragma once
#include "WidgetParent.h"

class wxTreeCtrl;
class InventoryAdd;
class InventorySearch : public WidgetParent
{
public:
	explicit InventorySearch(wxWindow* parent = nullptr, const wxString Title = "");
	virtual ~InventorySearch();

public:
	virtual void BtnTitleInit() override;
	virtual void LeftBodyInit() override;
	void LeftBottomInit();

	virtual void InfoTitleInit() override;
	virtual void RightBodyInit() override;

private:
	void BtnAddInventory(wxCommandEvent& event);
	void BtnDelInventory(wxCommandEvent& event);
	void BtnDeliveryNote(wxCommandEvent& event);


private:
	void GridClickEvent(wxGridEvent& e);
protected:

	wxBoxSizer* shell = nullptr;

	wxPanel* m_RightTopPanel;
	wxPanel* m_LeftBottmPanel;

	wxBoxSizer* m_TopSizer = nullptr;   // 본문(좌우) 배치용 H sizer

private:
	InventoryAdd* AddInven;
};

