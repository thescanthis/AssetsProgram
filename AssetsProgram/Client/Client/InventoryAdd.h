#pragma once
class InventoryAdd : public wxFrame
{
public:
	InventoryAdd();
	virtual ~InventoryAdd();

private:
	void ScreenInit();
private:
	wxPanel* m_panel = nullptr;
	wxBoxSizer* frameSizer = nullptr;
};

