#pragma once
#include "WidgetParent.h"
class ProductInfo : public WidgetParent
{
public:
	ProductInfo(wxWindow* parent = nullptr, const wxString Title = "");
	virtual ~ProductInfo();

private:
	void BtnTitleInit() override;
	void LeftBodyInit() override;
	void InfoTitleInit() override;
	void RightBodyInit() override;

private:
};

