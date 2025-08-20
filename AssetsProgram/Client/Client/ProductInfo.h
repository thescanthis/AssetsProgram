#pragma once
#include "WidgetParent.h"
class ProductInfo : public WidgetParent
{
public:
	ProductInfo(wxWindow* parent = nullptr, const wxString Title = "");
	virtual ~ProductInfo();

private:
	void BtnProductAdd(wxCommandEvent& event);
	void BtnProductCancel(wxCommandEvent& event);

	void GridInfoAdd(string title);
	void BtnGridInfoDel(wxCommandEvent& event);
	void GridClickEvent(wxGridEvent& e);
private:
	void BtnTitleInit() override;
	void LeftBodyInit() override;
	void InfoTitleInit() override;
	void RightBodyInit() override;

private:
	map<string, vector<C_Details>> ProductInfos;
	vector<map<string, int32>> InvenNames, InvenNames1;
	int32 m_gridRow = -1;
};

