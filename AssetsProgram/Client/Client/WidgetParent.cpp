#include "pch.h"
#include "WidgetParent.h"

#if 0 Lamda ����
���� : �� �� �߰�(�� + �̹� ���� ����Ʈ ����)
auto addRow = [&](const wxString& label, wxWindow* editor) {
	wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* lb = new wxStaticText(left, wxID_ANY, label);
	lb->SetMinSize(wxSize(110, -1));
	InfoTitle.push_back(lb);
	row->Add(lb, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);

	row->Add(editor, 1, wxEXPAND);
	fields->Add(row, 0, wxTOP | wxEXPAND | wxBOTTOM, 5);
	};

// �Ϲ� �Է�ĭ ���� ���� (���� ����)
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
	f.SetPointSize(f.GetPointSize() + AddFontSize);  // ���纸�� +3pt
	title->SetFont(f);
	title->SetForegroundColour(wxColour(80, 80, 120));
}

void WidgetParent::OnCharHook(wxKeyEvent& key)
{
	if (key.GetKeyCode() == WXK_ESCAPE) {
		Close();
		return; // �⺻ ó�� ����
	}
	key.Skip();   // �ٸ� Ű�� ���� ����
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
