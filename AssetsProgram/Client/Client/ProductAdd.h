#pragma once
#include "WidgetParent.h"
class ProductAdd : public WidgetParent
{
public:
	explicit ProductAdd(wxWindow* parent = nullptr, const wxString Title = "");
	virtual ~ProductAdd();

private:
	void BtnTitleInit() override;
	void LeftBodyInit() override;
	void InfoTitleInit() override;
	void RightBodyInit() override;

private:

};

