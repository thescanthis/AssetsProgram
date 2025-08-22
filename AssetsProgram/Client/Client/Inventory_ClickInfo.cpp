#include "pch.h"
#include "Inventory_ClickInfo.h"
#include <wx/datectrl.h>
#include <wx/dateevt.h>

Inventory_ClickInfo::Inventory_ClickInfo(wxSize size)
	:wxFrame(nullptr,wxID_ANY,"����ڻ� ���γ���", wxDefaultPosition, size)
{
    m_panel = new wxPanel(this, wxID_ANY);
    m_panel->SetBackgroundColour(*wxWHITE);
    frameSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(frameSizer);
    frameSizer->Add(m_panel, 1, wxEXPAND);

    auto* root = new wxBoxSizer(wxVERTICAL);
    m_panel->SetSizer(root);

    TopTitle();   // ���� ��� �˻���
    DownBody();   // ���� �׸���

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

    // ��� �ٸ� ���� �гο� ����(���/���� ���� ����)
    auto* bar = new wxPanel(m_panel, wxID_ANY);
    auto* topBar = new wxBoxSizer(wxHORIZONTAL);
    bar->SetSizer(topBar);

    auto* lbSearch = new wxStaticText(bar, wxID_ANY, "��ǰ��");
    auto* edSearch = new wxTextCtrl(bar, wxID_ANY, "");

    topBar->Add(lbSearch, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);
    topBar->Add(edSearch, 1, wxALIGN_CENTER_VERTICAL); // �� ����Ʈ�� ���� Ȯ��

    topBar->AddStretchSpacer(1); // ��� ���� Ȯ��
    topBar->AddStretchSpacer(1); // ��� ���� Ȯ��topBar->AddStretchSpacer(1); // ��� ���� Ȯ��

    auto* dtFrom = new wxDatePickerCtrl(bar, wxID_ANY);
    auto* tilde = new wxStaticText(bar, wxID_ANY, "~");
    auto* dtTo = new wxDatePickerCtrl(bar, wxID_ANY);
    auto* btnGo = new wxButton(bar, wxID_ANY, "�˻�");

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
    m_grid->CreateGrid(30, size); // �ʿ信 �°� ����

    WU::GridLabelInitilize(m_grid, LabelStr);
    
    int32 InvenSize = InvenDetails.size();
    for (int32 i = 0; i < InvenSize; i++)
    {
        
    }

    WU::GridColumnInitilize(m_grid, wid);

    root->Add(m_grid, 1, wxEXPAND|wxALL,8); // �� ���� ���� ���� �׸����
}
