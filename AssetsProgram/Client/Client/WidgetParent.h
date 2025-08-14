#pragma once
#include "MaskedTextCtrl.h"
#include "WidgetParent.h"
class WidgetParent : public wxFrame
{
public:
	explicit WidgetParent(wxWindow* parent = nullptr,const wxString Title="");
	virtual ~WidgetParent();

	virtual void BtnTitleInit() = 0;
	virtual void LeftBodyInit() = 0;
	virtual void InfoTitleInit() = 0;
	virtual void RightBodyInit() = 0;

protected:
	C_Details Infomation;
	wxPanel* m_panel, * m_TopPanel, * m_LeftPanel, * m_RightPanel;
	wxBoxSizer* m_bodySizer = nullptr;   // 본문(좌우) 배치용 H sizer

	std::vector<wxStaticText*> InfoTitle;
	std::vector<wxTextCtrl*>   InfoEdit;
};

