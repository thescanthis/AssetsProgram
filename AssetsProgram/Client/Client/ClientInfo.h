#pragma once
#include "WidgetParent.h"
class ClientInfo : public WidgetParent
{
public:
	explicit ClientInfo(wxWindow* parent = nullptr, const wxString Title = "");
	virtual ~ClientInfo();

private:
	void BtnClientAdd(wxCommandEvent& event);
	void BtnClientChange(wxCommandEvent& event);
	void BtnClientCancel(wxCommandEvent& event);
	void GridClickEvent(wxGridEvent& e);

private:
	void BtnTitleInit() override;
	void LeftBodyInit() override;
	void RightBodyInit() override;
	void InfoTitleInit() override;
	
private:
	wxPanel* m_RightPanel;
	wxBoxSizer* shell = nullptr;
};

