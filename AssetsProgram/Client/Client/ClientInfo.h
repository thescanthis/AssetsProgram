#pragma once
#include "WidgetParent.h"
class ClientInfo : public WidgetParent
{
public:
	explicit ClientInfo(wxWindow* parent = nullptr, const wxString Title = "");
	virtual ~ClientInfo();

public:
	
private:
	void BtnTitleInit() override;
	void LeftBodyInit() override;
	void RightBodyInit() override;
	void InfoTitleInit() override;

	void RightBottmInit();
	
private:
	wxPanel* m_RightBottmPanel;

	wxBoxSizer* shell = nullptr;
	wxGrid* m_grid;
};

