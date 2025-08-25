#include "pch.h"
#include "ClientInfo.h"
#include "ClientDetailInfo.h"
#include "ClientOrderInput.h"

ClientInfo::ClientInfo(wxWindow* parent, const wxString Title) : 
    WidgetParent(parent,Title)
{
	SetSizeHints(770, 600, 770, 600);         // 고정 크기(원하면 제거)
    m_RightPanel = new wxPanel(m_panel, wxID_ANY);
    m_RightPanel->SetBackgroundColour(*wxWHITE);

	// 메인 패널
	shell = new wxBoxSizer(wxVERTICAL);
	m_panel->SetSizer(shell);

	BtnTitleInit();
    LeftBodyInit();
    RightBodyInit();

	Center();
}

ClientInfo::~ClientInfo()
{

}

void ClientInfo::BtnClientAdd(wxCommandEvent& event)
{
    G_Template->MakeSingletonOpener<ClientDetailInfo>(this, "거래처등록")();
}

void ClientInfo::BtnClientChange(wxCommandEvent& event)
{
    G_Template->MakeSingletonOpener<ClientDetailInfo>(this, "거래처수정")();
}

void ClientInfo::BtnClientCancel(wxCommandEvent& event)
{
    this->Close(true);
}

void ClientInfo::GridClickEvent(wxGridEvent& e)
{
    int32 Row = e.GetRow();
    int32 Rows = m_grid->GetNumberRows();
    int32 Cols = m_grid->GetNumberCols();

    G_Template->MakeSingletonOpener<ClientDetailInfo>(this, "거래처수정")();
    e.Skip();
}

void ClientInfo::BtnTitleInit()
{
	auto* topSz = new wxBoxSizer(wxHORIZONTAL);
	m_TopPanel->SetSizer(topSz);
	topSz->AddStretchSpacer();

    auto* btnAdd = new wxButton(m_TopPanel, wxID_EXIT, "등록");
    auto* btnChange = new wxButton(m_TopPanel, wxID_EXIT, "수정");
	auto* btnExit = new wxButton(m_TopPanel, wxID_EXIT, "나가기");

	topSz->Add(btnAdd, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
    topSz->Add(btnChange, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
    topSz->Add(btnExit, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
	auto* line = new wxStaticLine(m_panel, wxID_ANY);

	shell->Add(m_TopPanel, 0, wxEXPAND);
	shell->Add(line, 0, wxEXPAND);

    btnAdd->Bind(wxEVT_BUTTON, &ClientInfo::BtnClientAdd, this);
    btnChange->Bind(wxEVT_BUTTON, &ClientInfo::BtnClientChange, this);
    btnExit->Bind(wxEVT_BUTTON, &ClientInfo::BtnClientCancel, this);
}

void ClientInfo::LeftBodyInit()
{
	// 왼쪽 패널 내부용 세로 sizer
	auto* leftRoot = new wxBoxSizer(wxVERTICAL);
	m_LeftPanel->SetSizer(leftRoot);

    InfoTitleInit();

   shell->Add(m_bodySizer);
}

void ClientInfo::RightBodyInit()
{
    auto* vline = new wxStaticLine(m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);

    // 오른쪽 내부 sizer
    auto* rightSz = new wxBoxSizer(wxVERTICAL);
    m_RightPanel->SetSizer(rightSz);

    auto* right = new wxPanel(m_RightPanel, wxID_ANY);
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

        addRow(right, fields, wxString(std::to_string(cnt++)) + ". " + ClientInfoTitle[i], makeEdit(right,""));
    }
    right->SetSizer(v);

    // ★★★ (1) right를 rightSz에 등록
    rightSz->Add(right, 1, wxEXPAND);

    // ★★★ (2) vline과 m_RightPanel을 본문 H-sizer에 등록
    m_bodySizer->Add(vline, 0, wxEXPAND /*| wxLEFT|wxRIGHT, 4*/);
    m_bodySizer->Add(m_RightPanel, 1, wxEXPAND);

    // 갱신은 이 컨테이너 쪽에
    m_panel->Layout();   // 또는 최상위 프레임에서 Layout();
}

void ClientInfo::InfoTitleInit()
{
    auto* LeftSz = new wxBoxSizer(wxVERTICAL);
    m_LeftPanel->SetSizer(LeftSz);

    auto* topH = new wxBoxSizer(wxHORIZONTAL);

    auto* Ltitle = new wxStaticText(m_LeftPanel, wxID_ANY, "[거래처 정보]");
    { wxFont f = Ltitle->GetFont(); f.MakeBold(); Ltitle->SetFont(f); }
    Ltitle->SetForegroundColour(wxColour(80, 80, 120));
    topH->Add(Ltitle, 0, wxLEFT | wxTOP | wxRIGHT | wxBOTTOM, 8);

    topH->AddStretchSpacer();
    auto* btnExit = new wxButton(m_LeftPanel, wxID_EXIT, "삭제");
    topH->Add(btnExit, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);

    // 상단 가로바를 우측 패널의 세로 레이아웃에 추가
    LeftSz->Add(topH, 0, wxEXPAND | wxBOTTOM, 8);

    m_grid = WU::MakeGrid(m_LeftPanel, C_LabelStr, C_gridWid, wxEVT_GRID_CELL_LEFT_DCLICK, &ClientInfo::GridClickEvent, this);
    
    // 예시 데이터(원하면 제거)
    m_grid->SetCellValue(0, 0, "");
    m_grid->SetCellValue(0, 1, "휘온정보통신 주식회사");
    m_grid->SetCellValue(0, 2, "352-81-00723");
    m_grid->SetCellValue(0, 3, "김기종");
    m_grid->AutoSizeColumns();

    WU::GridColumnInitilize(m_grid, C_gridWid);

    LeftSz->Add(m_grid, 1, wxALIGN_LEFT | wxALIGN_TOP);           // 그리드를 오른쪽 패널에 꽉 채움

    m_bodySizer->Add(m_LeftPanel, 1, wxEXPAND | wxALL, 6);
}