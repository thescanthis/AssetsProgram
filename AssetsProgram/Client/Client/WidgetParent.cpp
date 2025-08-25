#include "pch.h"
#include "WidgetParent.h"

#if 0 Lamda 예제
공통 : 한 줄 추가(라벨 + 이미 만든 에디트 위젯)
auto addRow = [&](const wxString& label, wxWindow* editor) {
	wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* lb = new wxStaticText(left, wxID_ANY, label);
	lb->SetMinSize(wxSize(110, -1));
	InfoTitle.push_back(lb);
	row->Add(lb, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);

	row->Add(editor, 1, wxEXPAND);
	fields->Add(row, 0, wxTOP | wxEXPAND | wxBOTTOM, 5);
	};

// 일반 입력칸 생성 헬퍼 (쓰기 가능)
auto makeEdit = [&](const wxString& hint)->wxTextCtrl* {
	wxTextCtrl* ed = new wxTextCtrl(left, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
	if (!hint.empty()) ed->SetHint(hint);
	ed->Enable(false);
	ed->SetBackgroundColour(*wxWHITE);
	ed->SetForegroundColour(wxColour(50, 50, 50));
	InfoEdit.push_back(ed);
	return ed;
	};
#endif

WidgetParent::WidgetParent(wxWindow* parent, const wxString Title, wxSize Size)
	:wxFrame(parent, wxID_ANY, Title, wxDefaultPosition, Size)
{
	m_panel = new wxPanel(this, wxID_ANY);
	m_panel->SetBackgroundColour(wxColour(247, 249, 253));

	m_TopPanel = new wxPanel(m_panel, wxID_ANY);
	m_TopPanel->SetBackgroundColour(wxColour(247, 249, 253));
	m_LeftPanel = new wxPanel(m_panel, wxID_ANY);
	m_LeftPanel->SetBackgroundColour(*wxWHITE);
	m_bodySizer = new wxBoxSizer(wxHORIZONTAL);

	Bind(wxEVT_CHAR_HOOK, &WidgetParent::OnCharHook, this);
}

WidgetParent::~WidgetParent()
{
	InfoTitle.clear();
	InfoEdit.clear();
}

void WidgetParent::TitleFontInit(wxStaticText* title, int AddFontSize)
{
	wxFont f = title->GetFont(); 
	f.MakeBold(); 
	f.SetPointSize(f.GetPointSize() + AddFontSize);  // 현재보다 +3pt
	title->SetFont(f);
	title->SetForegroundColour(wxColour(80, 80, 120));
}

void WidgetParent::OnCharHook(wxKeyEvent& key)
{
	if (key.GetKeyCode() == WXK_ESCAPE) {
		Close();
		return; // 기본 처리 막음
	}
	key.Skip();   // 다른 키는 정상 전달
}

void WidgetParent::addRow(wxPanel* panel, wxBoxSizer* fields ,const wxString& Label, wxWindow* editor)
{
	wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* lb = new wxStaticText(panel, wxID_ANY, Label);
	lb->SetMinSize(wxSize(110, -1));
	InfoTitle.push_back(lb);
	row->Add(lb, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);

	row->Add(editor, 1, wxEXPAND);
	fields->Add(row, 0, wxTOP | wxEXPAND | wxBOTTOM, 5);
}

wxTextCtrl* WidgetParent::makeEdit(wxPanel* panel,const wxString& hint, const bool EnableText)
{
	wxTextCtrl* ed = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
	if (!hint.empty()) ed->SetHint(hint);
	ed->Enable(EnableText);
	ed->SetBackgroundColour(*wxWHITE);
	ed->SetForegroundColour(wxColour(50, 50, 50));
	InfoEdit.push_back(ed);
	return ed;
}
