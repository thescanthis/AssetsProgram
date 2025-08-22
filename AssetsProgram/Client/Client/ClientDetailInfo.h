#pragma once
#include "WidgetParent.h"
class ClientDetailInfo : public WidgetParent
{
public:
	explicit ClientDetailInfo(wxWindow* parent = nullptr, const wxString Title = "");
	virtual ~ClientDetailInfo();

private:
	void BtnTitleInit() override;
	void LeftBodyInit() override;
	void RightBodyInit() override;
	void InfoTitleInit() override;
private:
	wxBoxSizer* shell = nullptr;
};

