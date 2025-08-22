#include "pch.h"
#include "Inventory_ClickInfo.h"
#include <wx/datectrl.h>
#include <wx/dateevt.h>

Inventory_ClickInfo::Inventory_ClickInfo(wxSize size)
	:wxFrame(nullptr,wxID_ANY,"재고자산 세부내용", wxDefaultPosition, size)
{
    m_panel = new wxPanel(this, wxID_ANY);
    m_panel->SetBackgroundColour(*wxWHITE);
    frameSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(frameSizer);
    frameSizer->Add(m_panel, 1, wxEXPAND);

    auto* root = new wxBoxSizer(wxVERTICAL);
    m_panel->SetSizer(root);

    TopTitle();   // ── 상단 검색바
    DownBody();   // ── 그리드

    Layout();
    if (GetParent()) CentreOnParent(); else CentreOnScreen();


	Center();
}

Inventory_ClickInfo::~Inventory_ClickInfo()
{
}

void Inventory_ClickInfo::TopTitle()
{
    auto* root = wxDynamicCast(m_panel->GetSizer(), wxBoxSizer);
    wxASSERT(root);

    // 상단 바를 별도 패널에 구성(배경/여백 관리 쉬움)
    auto* bar = new wxPanel(m_panel, wxID_ANY);
    auto* topBar = new wxBoxSizer(wxHORIZONTAL);
    bar->SetSizer(topBar);

    auto* lbSearch = new wxStaticText(bar, wxID_ANY, "상품명");
    auto* edSearch = new wxTextCtrl(bar, wxID_ANY, "");

    topBar->Add(lbSearch, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);
    topBar->Add(edSearch, 1, wxALIGN_CENTER_VERTICAL); // ← 에디트는 가로 확장

    topBar->AddStretchSpacer(1); // 가운데 공간 확보
    topBar->AddStretchSpacer(1); // 가운데 공간 확보topBar->AddStretchSpacer(1); // 가운데 공간 확보

    auto* dtFrom = new wxDatePickerCtrl(bar, wxID_ANY);
    auto* tilde = new wxStaticText(bar, wxID_ANY, "~");
    auto* dtTo = new wxDatePickerCtrl(bar, wxID_ANY);
    auto* btnGo = new wxButton(bar, wxID_ANY, "검색");

    topBar->Add(dtFrom, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    topBar->Add(tilde, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 4);
    topBar->Add(dtTo, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
    topBar->Add(btnGo, 0, wxALIGN_CENTER_VERTICAL);

    root->Add(bar, 0, wxEXPAND | wxALL, 8);
}

void Inventory_ClickInfo::DownBody()
{
    auto* root = wxDynamicCast(m_panel->GetSizer(), wxBoxSizer);
    wxASSERT(root);

    int size = sizeof(LabelStr) / sizeof(wxString);
    m_grid = new wxGrid(m_panel, wxID_ANY);
    m_grid->CreateGrid(30, size); // 필요에 맞게 조정

    WU::GridLabelInitilize(m_grid, LabelStr);
    
    int32 InvenSize = InvenDetails.size();
    for (int32 i = 0; i < InvenSize; i++)
    {
        
    }

    WU::GridColumnInitilize(m_grid, wid);

    root->Add(m_grid, 1, wxEXPAND|wxALL,8); // ← 남는 공간 전부 그리드로
}
