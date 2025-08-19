#pragma once
#include "WidgetParent.h"
class CompanyInfoDetail : public WidgetParent
{
public:
	explicit CompanyInfoDetail(wxWindow* parent = nullptr, const wxString Title = "");
	virtual ~CompanyInfoDetail();

	void BtnTitleInit() override;
	void LeftBodyInit() override;
	void InfoTitleInit() override;
	void RightBodyInit() override;

protected:
	std::array<wxString,7> TitleInfo = {
		"회사명", 
		"사업자등록번호",
		"법인등록번호",
		"대표자명",
		"사업장주소",
		"업태",
		"종목"
	};
};		
 

