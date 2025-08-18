#pragma once
#include "WidgetParent.h"

class wxTreeCtrl;

class InventoryAdd : public WidgetParent
{
public:
	explicit InventoryAdd(wxWindow* parent = nullptr, const wxString Title = "");
	virtual ~InventoryAdd();

public:
	virtual void BtnTitleInit() override;
	virtual void LeftBodyInit() override;
	virtual void InfoTitleInit() override;
	virtual void RightBodyInit() override;
private:
};

