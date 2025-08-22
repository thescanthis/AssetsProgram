#pragma once
#include "WidgetParent.h"

class ProductInfo : public WidgetParent
{
public:
	ProductInfo(wxWindow* parent = nullptr, const wxString Title = "");
	virtual ~ProductInfo();

private:
	void BtnProductAdd(wxCommandEvent& event);
	void BtnProductChange(wxCommandEvent& event);
	void BtnProductCancel(wxCommandEvent& event);

	void GridClickEvent(wxGridEvent& e);

	void GridInfoAdd(std::string title);
	void BtnGridInfoDel(wxCommandEvent& event);
private:
	void BtnTitleInit() override;
	void LeftBodyInit() override;
	void InfoTitleInit() override;
	void RightBodyInit() override;

private:
	wxPanel* m_RightPanel;
	std::map<std::string, std::vector<C_Details>> ProductInfos;
	std::vector<std::map<std::string, int32>> InvenNames, InvenNames1;
	int32 m_gridRow = -1;
};

