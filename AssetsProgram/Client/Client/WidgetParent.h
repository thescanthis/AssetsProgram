#pragma once
#include "WidgetParent.h"
#include "BufferReader.h"
class WidgetParent : public wxFrame
{
public:
	explicit WidgetParent(wxWindow* parent = nullptr, const wxString Title = "", wxSize Size = {800,600});
	virtual ~WidgetParent();

	virtual void BtnTitleInit() = 0;
	virtual void LeftBodyInit() = 0;
	virtual void InfoTitleInit() = 0;
	virtual void RightBodyInit() = 0;

protected:
	std::array<const wxString, 9> InventoryTitle = {
	"상품코드",
	"상품명",
	"단위",
	"판매단가",
	"구매단가",
	"상품그룹",
	"메모",
	"판매처",
	"자재실"
	};

	std::array<const wxString, 14> ClientInfoTitle = {
		"거래처구분",
		"거래구분",
		",",
		"회사명",
		"사업자등록번호",
		"법인등록번호",
		"대표자명",
		"사업장주소",
		"업태",
		"종목",
		",",
		"연락처",
		"팩스번호",
		"이메일"
	};
	void TitleFontInit(wxStaticText* title,int AddFontSize=0);
	void OnCharHook(wxKeyEvent& key);
	void addRow(wxPanel* panel, wxBoxSizer* fields, const wxString& Label, wxWindow* editor);
	wxTextCtrl* makeEdit(wxPanel* panel,const wxString& hint, const bool EnableText=false);

protected:
	C_Details Infomation;
	wxPanel* m_panel, * m_TopPanel, * m_LeftPanel;
	wxBoxSizer* m_bodySizer = nullptr;   // 본문(좌우) 배치용 H sizer

	std::vector<wxStaticText*> InfoTitle;
	std::vector<wxTextCtrl*>   InfoEdit;

	wxGrid* m_grid;
};

