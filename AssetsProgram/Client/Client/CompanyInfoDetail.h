#pragma once
#include "WidgetParent.h"
class CompanyInfoDetail : public WidgetParent
{
public:
	explicit  CompanyInfoDetail(wxWindow* parent = nullptr, const wxString Title="");
	virtual ~CompanyInfoDetail();

	void BtnTitleInit() override;
	void LeftBodyInit() override;
	void InfoTitleInit() override;
	void RightBodyInit() override;
};

