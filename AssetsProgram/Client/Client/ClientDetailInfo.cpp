#include "pch.h"
#include "ClientDetailInfo.h"

ClientDetailInfo::ClientDetailInfo(wxWindow* parent, const wxString Title)
	:WidgetParent(parent,Title)
{
	// ���� �г�
    SetSizeHints(390, 600, 390, 600);
	shell = new wxBoxSizer(wxVERTICAL);
	m_panel->SetSizer(shell);

    BtnTitleInit();
    auto* line = new wxStaticLine(m_panel, wxID_ANY);

    LeftBodyInit();

    shell->Add(m_TopPanel, 0, wxEXPAND);
    shell->Add(line, 0, wxEXPAND);
    shell->Add(m_bodySizer, 1, wxEXPAND);   // �� �ٽ�!

    // ������ ä���
    auto* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(m_panel, 1, wxEXPAND, 10);
    SetSizer(frameSizer);
    Layout();
    Center();
}

ClientDetailInfo::~ClientDetailInfo()
{

}

void ClientDetailInfo::BtnTitleInit()
{
    auto* topSz = new wxBoxSizer(wxHORIZONTAL);
    m_TopPanel->SetSizer(topSz);
    topSz->AddStretchSpacer();
    auto* btnSave = new wxButton(m_TopPanel, wxID_SAVE, "����");
    auto* btnCancel = new wxButton(m_TopPanel, wxID_SAVE, "���");
    topSz->Add(btnSave, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
    topSz->Add(btnCancel, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
}

void ClientDetailInfo::LeftBodyInit()
{
    // �⺻����
    m_bodySizer = new wxBoxSizer(wxHORIZONTAL);

    // ���� �г� ���ο� ���� sizer
    auto* leftRoot = new wxBoxSizer(wxVERTICAL);
    m_LeftPanel->SetSizer(leftRoot);
    InfoTitleInit();
}

void ClientDetailInfo::RightBodyInit()
{
}

void ClientDetailInfo::InfoTitleInit()
{
    auto* vline = new wxStaticLine(m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);

     // ������ ���� sizer
    auto* rightSz = new wxBoxSizer(wxVERTICAL);
    m_LeftPanel->SetSizer(rightSz);

    auto* right = new wxPanel(m_LeftPanel, wxID_ANY);
    right->SetBackgroundColour(*wxWHITE);

    auto* v = new wxBoxSizer(wxVERTICAL);

    const int kTopBarH = 32; // �ʿ��ϸ� FromDIP(32, this) ���
    // [�⺻����] ����
    // ���� ��ܹ�: [�⺻����] ..... (�����)
    auto* topL = new wxBoxSizer(wxHORIZONTAL);
    auto* title = new wxStaticText(right, wxID_ANY, "[����]");
    TitleFontInit(title);

    topL->Add(title, 0, wxALIGN_CENTER_VERTICAL);
    topL->AddStretchSpacer();


    // �� �����ʰ� ���� ���� �ο�
    topL->SetMinSize(wxSize(-1, kTopBarH));

    // ��ܹ� �߰� (������ �����ʰ� ���� 8����)
    v->Add(topL, 0, wxLEFT | wxEXPAND | wxBOTTOM, 10);

    // ��+����Ʈ �ٵ��� ���η� �״� �����̳�
    auto* fields = new wxBoxSizer(wxVERTICAL);
    v->Add(fields, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);         // �� ��ü �¿� �е� 10

    int32 cnt = 1;
    int32 Titlecnt = 0;
    wxString titles[2] = { "[�ŷ�ó����]","[����ó]" };
    for (int i = 0; i < ClientInfoTitle.size(); i++)
    {
        if (ClientInfoTitle[i] == ",") {
            auto* hdr = new wxStaticText(right, wxID_ANY, titles[Titlecnt++]);
            TitleFontInit(hdr); // �ʿ��ϸ� �� ���� ����� ���� ��Ÿ��
            fields->Add(hdr, 0, wxTOP | wxBOTTOM, 6);
            continue;
        }
        addRow(right, fields, wxString(std::to_string(cnt++)) + ". " + ClientInfoTitle[i], makeEdit(right, ""));
    }
    right->SetSizer(v);

    // �ڡڡ� (1) right�� rightSz�� ���
    rightSz->Add(right, 1, wxEXPAND);

    // �ڡڡ� (2) vline�� m_RightPanel�� ���� H-sizer�� ���
    m_bodySizer->Add(vline, 0, wxEXPAND /*| wxLEFT|wxRIGHT, 4*/);
    m_bodySizer->Add(m_LeftPanel, 1, wxEXPAND);
}
