#include "pch.h"
#include "ProductAdd.h"

ProductAdd::ProductAdd(wxWindow* parent, const wxString Title)
    :WidgetParent(parent, Title)
{
    SetSizeHints(310, 420, 310, 420);         // 고정 크기(원하면 제거)
    auto* shell = new wxBoxSizer(wxVERTICAL);
    m_panel->SetSizer(shell);

    BtnTitleInit();
    auto* line = new wxStaticLine(m_panel, wxID_ANY);

    LeftBodyInit();

    shell->Add(m_TopPanel, 0, wxEXPAND);
    shell->Add(line, 0, wxEXPAND);
    shell->Add(m_bodySizer, 1, wxEXPAND);   // ← 핵심!

    // 프레임 채우기
    auto* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(m_panel, 1, wxEXPAND, 10);
    SetSizer(frameSizer);
    Center();
}

ProductAdd::~ProductAdd()
{
}

void ProductAdd::BtnTitleInit()
{
    auto* topSz = new wxBoxSizer(wxHORIZONTAL);
    m_TopPanel->SetSizer(topSz);
    topSz->AddStretchSpacer();
    auto* btnSave = new wxButton(m_TopPanel, wxID_SAVE, "저장");
    auto* btnCancel = new wxButton(m_TopPanel, wxID_SAVE, "취소");
    topSz->Add(btnSave, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
    topSz->Add(btnCancel, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
}

void ProductAdd::LeftBodyInit()
{
    m_LeftPanel->SetSizeHints(310, -1, 310, -1);      // 폭 300 고정

    // 왼쪽 패널 내부용 세로 sizer
    auto* leftRoot = new wxBoxSizer(wxVERTICAL);
    m_LeftPanel->SetSizer(leftRoot);

    InfoTitleInit();

    m_bodySizer->Add(m_LeftPanel, 0, wxEXPAND);
}

void ProductAdd::InfoTitleInit()
{
    auto* left = new wxPanel(m_LeftPanel, wxID_ANY);
    left->SetBackgroundColour(*wxWHITE);
    left->SetMinSize(wxSize(300, -1));

    auto* v = new wxBoxSizer(wxVERTICAL);

    const int kTopBarH = 32;

    auto* topL = new wxBoxSizer(wxHORIZONTAL);
    auto* title = new wxStaticText(left, wxID_ANY, "[기본정보]");
    TitleFontInit(title);

    topL->Add(title, 0, wxALIGN_CENTER_VERTICAL);
    topL->AddStretchSpacer();

    topL->SetMinSize(wxSize(-1, kTopBarH));

    v->Add(topL, 0, wxLEFT | wxEXPAND | wxBOTTOM, 5);

    auto* fields = new wxBoxSizer(wxVERTICAL);
    v->Add(fields, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);

    for (int i = 0; i < InventoryTitle.size(); i++)
        addRow(left, fields, wxString(std::to_string(i + 1)) + ". " + InventoryTitle[i], makeEdit(left, "",true));
    left->SetSizer(v);

    auto* leftRoot = wxDynamicCast(m_LeftPanel->GetSizer(), wxBoxSizer);
    leftRoot->Add(left, 1, wxEXPAND);
}

void ProductAdd::RightBodyInit()
{
}
