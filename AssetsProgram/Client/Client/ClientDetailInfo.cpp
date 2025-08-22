#include "pch.h"
#include "ClientDetailInfo.h"

ClientDetailInfo::ClientDetailInfo(wxWindow* parent, const wxString Title)
	:WidgetParent(parent,Title)
{
	// 메인 패널
    SetSizeHints(390, 600, 390, 600);
	shell = new wxBoxSizer(wxVERTICAL);
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
    auto* btnSave = new wxButton(m_TopPanel, wxID_SAVE, "저장");
    auto* btnCancel = new wxButton(m_TopPanel, wxID_SAVE, "취소");
    topSz->Add(btnSave, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
    topSz->Add(btnCancel, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
}

void ClientDetailInfo::LeftBodyInit()
{
    // 기본정보
    m_bodySizer = new wxBoxSizer(wxHORIZONTAL);

    // 왼쪽 패널 내부용 세로 sizer
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

     // 오른쪽 내부 sizer
    auto* rightSz = new wxBoxSizer(wxVERTICAL);
    m_LeftPanel->SetSizer(rightSz);

    auto* right = new wxPanel(m_LeftPanel, wxID_ANY);
    right->SetBackgroundColour(*wxWHITE);

    auto* v = new wxBoxSizer(wxVERTICAL);

    const int kTopBarH = 32; // 필요하면 FromDIP(32, this) 사용
    // [기본정보] 제목
    // 가로 상단바: [기본정보] ..... (빈공간)
    auto* topL = new wxBoxSizer(wxHORIZONTAL);
    auto* title = new wxStaticText(right, wxID_ANY, "[구분]");
    TitleFontInit(title);

    topL->Add(title, 0, wxALIGN_CENTER_VERTICAL);
    topL->AddStretchSpacer();


    // ★ 오른쪽과 같은 높이 부여
    topL->SetMinSize(wxSize(-1, kTopBarH));

    // 상단바 추가 (여백은 오른쪽과 맞춰 8권장)
    v->Add(topL, 0, wxLEFT | wxEXPAND | wxBOTTOM, 10);

    // 라벨+에디트 줄들을 세로로 쌓는 컨테이너
    auto* fields = new wxBoxSizer(wxVERTICAL);
    v->Add(fields, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);         // 폼 전체 좌우 패딩 10

    int32 cnt = 1;
    int32 Titlecnt = 0;
    wxString titles[2] = { "[거래처정보]","[연락처]" };
    for (int i = 0; i < ClientInfoTitle.size(); i++)
    {
        if (ClientInfoTitle[i] == ",") {
            auto* hdr = new wxStaticText(right, wxID_ANY, titles[Titlecnt++]);
            TitleFontInit(hdr); // 필요하면 좀 작은 볼드로 따로 스타일
            fields->Add(hdr, 0, wxTOP | wxBOTTOM, 6);
            continue;
        }
        addRow(right, fields, wxString(std::to_string(cnt++)) + ". " + ClientInfoTitle[i], makeEdit(right, ""));
    }
    right->SetSizer(v);

    // ★★★ (1) right를 rightSz에 등록
    rightSz->Add(right, 1, wxEXPAND);

    // ★★★ (2) vline과 m_RightPanel을 본문 H-sizer에 등록
    m_bodySizer->Add(vline, 0, wxEXPAND /*| wxLEFT|wxRIGHT, 4*/);
    m_bodySizer->Add(m_LeftPanel, 1, wxEXPAND);
}
