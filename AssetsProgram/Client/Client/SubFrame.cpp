#include "pch.h"
#include "SubFrame.h"


SubFrame::SubFrame(wxWindow* parent, const wxString& title, wxWindowID id)
	:wxPanel(parent,id,wxDefaultPosition,wxDefaultSize, wxBORDER_NONE), themeColour(226, 230, 240)
{
    SetBackgroundColour(*wxWHITE);
    SetMinSize(wxSize(220, 330)); // 요청 크기
    Bind(wxEVT_PAINT, &SubFrame::OnPaint, this); // 연회색 테두리

    rootSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(rootSizer);

    CreateTitleBar(title); // ← 제목 먼저
   
    // 내부 배치
    contentSizer = new wxBoxSizer(wxVERTICAL);
    rootSizer->Add(contentSizer, 1, wxEXPAND | wxALL, 10);
}

SubFrame::~SubFrame()
{
}

void SubFrame::CreateTitleBar(const wxString& title)
{
    if (title == "없음") {
        // 제목바를 만들지 않음
        titlePanel = nullptr;
        // titleText 등도 만들지 않음
        return;
    }

    titlePanel = new wxPanel(this, wxID_ANY);
    titlePanel->SetBackgroundColour(themeColour);    // 제목 배경색
    titlePanel->SetMinSize(wxSize(-1, 30));

    titleText = new wxStaticText(titlePanel, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont f = titleText->GetFont(); 
    f.MakeBold(); 
    f.SetPointSize(12); // 기본보다 크게
    titleText->SetFont(f);
    titleText->SetForegroundColour(wxColour(120,120,120)); //or 96,96,96

    auto* titleSizer = new wxBoxSizer(wxHORIZONTAL);
    titleSizer->Add(titleText, 1, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL, 6);
    titlePanel->SetSizer(titleSizer);

    // 가로 전체를 꽉 채움
    rootSizer->Add(titlePanel, 0, wxEXPAND);
}

void SubFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    dc.SetBrush(wxBrush(GetBackgroundColour()));
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(GetClientRect());
    dc.SetPen(wxPen(wxColour(226, 230, 240), 1));    // 연회색 테두리
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(0, 0, GetSize().x - 1, GetSize().y - 1);
}
