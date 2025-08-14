#include "pch.h"
#include "SubFrame.h"


SubFrame::SubFrame(wxWindow* parent, const wxString& title, wxWindowID id)
	:wxPanel(parent,id,wxDefaultPosition,wxDefaultSize, wxBORDER_NONE), themeColour(226, 230, 240)
{
    SetBackgroundColour(*wxWHITE);
    SetMinSize(wxSize(220, 330)); // ��û ũ��
    Bind(wxEVT_PAINT, &SubFrame::OnPaint, this); // ��ȸ�� �׵θ�

    rootSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(rootSizer);

    CreateTitleBar(title); // �� ���� ����
   
    // ���� ��ġ
    contentSizer = new wxBoxSizer(wxVERTICAL);
    rootSizer->Add(contentSizer, 1, wxEXPAND | wxALL, 10);
}

SubFrame::~SubFrame()
{
}

void SubFrame::CreateTitleBar(const wxString& title)
{
    if (title == "����") {
        // ����ٸ� ������ ����
        titlePanel = nullptr;
        // titleText � ������ ����
        return;
    }

    titlePanel = new wxPanel(this, wxID_ANY);
    titlePanel->SetBackgroundColour(themeColour);    // ���� ����
    titlePanel->SetMinSize(wxSize(-1, 30));

    titleText = new wxStaticText(titlePanel, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont f = titleText->GetFont(); 
    f.MakeBold(); 
    f.SetPointSize(12); // �⺻���� ũ��
    titleText->SetFont(f);
    titleText->SetForegroundColour(wxColour(120,120,120)); //or 96,96,96

    auto* titleSizer = new wxBoxSizer(wxHORIZONTAL);
    titleSizer->Add(titleText, 1, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL, 6);
    titlePanel->SetSizer(titleSizer);

    // ���� ��ü�� �� ä��
    rootSizer->Add(titlePanel, 0, wxEXPAND);
}

void SubFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    dc.SetBrush(wxBrush(GetBackgroundColour()));
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(GetClientRect());
    dc.SetPen(wxPen(wxColour(226, 230, 240), 1));    // ��ȸ�� �׵θ�
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(0, 0, GetSize().x - 1, GetSize().y - 1);
}
