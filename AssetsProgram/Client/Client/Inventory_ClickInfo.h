#pragma once
class Inventory_ClickInfo : public wxFrame
{
public:
	Inventory_ClickInfo(wxSize size);
	~Inventory_ClickInfo();

	void TopTitle();
	void DownBody();
private:
	std::vector<I_Detalis> InvenDetails;
	wxGrid* m_grid;

	wxPanel* m_panel;
	wxBoxSizer* frameSizer = nullptr;
};

