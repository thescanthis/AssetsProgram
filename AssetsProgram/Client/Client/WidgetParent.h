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
	"��ǰ�ڵ�",
	"��ǰ��",
	"����",
	"�ǸŴܰ�",
	"���Ŵܰ�",
	"��ǰ�׷�",
	"�޸�",
	"�Ǹ�ó",
	"�����"
	};

	std::array<const wxString, 14> ClientInfoTitle = {
		"�ŷ�ó����",
		"�ŷ�����",
		",",
		"ȸ���",
		"����ڵ�Ϲ�ȣ",
		"���ε�Ϲ�ȣ",
		"��ǥ�ڸ�",
		"������ּ�",
		"����",
		"����",
		",",
		"����ó",
		"�ѽ���ȣ",
		"�̸���"
	};
	void TitleFontInit(wxStaticText* title,int AddFontSize=0);
	void OnCharHook(wxKeyEvent& key);
	void addRow(wxPanel* panel, wxBoxSizer* fields, const wxString& Label, wxWindow* editor);
	wxTextCtrl* makeEdit(wxPanel* panel,const wxString& hint, const bool EnableText=false);

protected:
	C_Details Infomation;
	wxPanel* m_panel, * m_TopPanel, * m_LeftPanel;
	wxBoxSizer* m_bodySizer = nullptr;   // ����(�¿�) ��ġ�� H sizer

	std::vector<wxStaticText*> InfoTitle;
	std::vector<wxTextCtrl*>   InfoEdit;

	wxGrid* m_grid;
};

