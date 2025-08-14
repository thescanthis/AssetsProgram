#pragma once
class CompanyInfoDetail : public wxFrame
{
public:
	explicit  CompanyInfoDetail(wxWindow* parent = nullptr);
	~CompanyInfoDetail();

	void BtnTitleInit();

	void LeftBodyInit();
	void InfoTitleInit();

	void RightBodyInit();
private:

	C_Details Infomation;
	wxPanel *m_panel, *m_TopPanel, *m_LeftPanel, *m_RightPanel;
	std::vector<wxStaticText*> InfoTitle;
	std::vector<wxTextCtrl*>   InfoEdit;

	wxBoxSizer* m_bodySizer = nullptr;   // 본문(좌우) 배치용 H sizer
};

