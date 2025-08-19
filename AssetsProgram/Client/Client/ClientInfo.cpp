#include "pch.h"
#include "ClientInfo.h"

ClientInfo::ClientInfo(wxWindow* parent, const wxString Title) : WidgetParent(parent,Title)
{
	SetSizeHints(800, 600, 800, 600);         // 고정 크기(원하면 제거)
	//m_panel = new wxPanel(this, wxID_ANY);
	//m_panel->SetBackgroundColour(*wxWHITE);

	// 메인 패널
	shell = new wxBoxSizer(wxVERTICAL);
	m_panel->SetSizer(shell);

	BtnTitleInit();
    LeftBodyInit();
    RightBodyInit();
    RightBottmInit();

	Center();
}

ClientInfo::~ClientInfo()
{

}

void ClientInfo::BtnTitleInit()
{
	auto* topSz = new wxBoxSizer(wxHORIZONTAL);
	m_TopPanel->SetSizer(topSz);
	topSz->AddStretchSpacer();
	auto* btnExit = new wxButton(m_TopPanel, wxID_EXIT, "나가기");
	topSz->Add(btnExit, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
	auto* line = new wxStaticLine(m_panel, wxID_ANY);

	shell->Add(m_TopPanel, 0, wxEXPAND);
	shell->Add(line, 0, wxEXPAND);
}

void ClientInfo::LeftBodyInit()
{
	// 기본정보
	//m_LeftPanel = new wxPanel(m_panel, wxID_ANY);
    //m_LeftPanel->SetBackgroundColour(*wxWHITE);
	m_bodySizer = new wxBoxSizer(wxHORIZONTAL);

	// 왼쪽 패널 내부용 세로 sizer
	auto* leftRoot = new wxBoxSizer(wxVERTICAL);
	m_LeftPanel->SetSizer(leftRoot);

    InfoTitleInit();

   shell->Add(m_bodySizer);
}

void ClientInfo::RightBodyInit()
{
    auto* vline = new wxStaticLine(m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);

   // m_RightPanel = new wxPanel(m_panel, wxID_ANY);
   // m_RightPanel->SetBackgroundColour(*wxWHITE);

    // 오른쪽 내부 sizer
    auto* rightSz = new wxBoxSizer(wxVERTICAL);
    m_RightPanel->SetSizer(rightSz);

    auto* right = new wxPanel(m_RightPanel, wxID_ANY);
    right->SetBackgroundColour(*wxWHITE);
    // right->SetMinSize(wxSize(300, -1));   // ← 우측은 확장시킬 거면 이 줄 삭제!

    auto* v = new wxBoxSizer(wxVERTICAL);

    const int kTopBarH = 32; // 필요하면 FromDIP(32, this) 사용
    // [기본정보] 제목
// 가로 상단바: [기본정보] ..... (빈공간)
    auto* topL = new wxBoxSizer(wxHORIZONTAL);
    auto* title = new wxStaticText(right, wxID_ANY, "[기본정보]");
    TitleFontInit(title);

    auto* btnAdd = new wxButton(right, wxID_EXIT, "추가");
    auto* btnExit = new wxButton(right, wxID_EXIT, "취소");
    
    topL->Add(title, 0, wxALIGN_CENTER_VERTICAL);

    topL->AddStretchSpacer();
    topL->Add(btnAdd, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
    topL->Add(btnExit, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);

    // ★ 오른쪽과 같은 높이 부여
    topL->SetMinSize(wxSize(-1, kTopBarH));

    // 상단바 추가 (여백은 오른쪽과 맞춰 8권장)
    v->Add(topL, 0, wxLEFT | wxEXPAND | wxBOTTOM, 10);

    // 라벨+에디트 줄들을 세로로 쌓는 컨테이너
    auto* fields = new wxBoxSizer(wxVERTICAL);
    v->Add(fields, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);         // 폼 전체 좌우 패딩 10

    // 공통: 한 줄 추가(라벨 + 이미 만든 에디트 위젯)
    auto addRow = [&](const wxString& label, wxWindow* editor) {
        wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);

        wxStaticText* lb = new wxStaticText(right, wxID_ANY, label);
        lb->SetMinSize(wxSize(110, -1));                        // 라벨 폭 통일
        InfoTitle.push_back(lb);
        row->Add(lb, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);

        row->Add(editor, 1, wxEXPAND);
        fields->Add(row, 0, wxTOP | wxEXPAND | wxBOTTOM, 6);
        };

    // 일반 입력칸 생성 헬퍼 (쓰기 가능)
    auto makeEdit = [&](const wxString& hint)->wxTextCtrl* {
        wxTextCtrl* ed = new wxTextCtrl(right, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
        if (!hint.empty()) ed->SetHint(hint);                   // 입력 시작하면 사라지는 힌트
        ed->SetBackgroundColour(*wxWHITE);
        ed->SetForegroundColour(wxColour(50, 50, 50));
        InfoEdit.push_back(ed);
        return ed;
        };

    // ── 실제 필드 추가 (요청: 01/02/04/05/07/08/09) ──
    // 01. 회사명
    addRow("01. 회사명", makeEdit(""));

    // 02. 사업자등록번호 (3-2-5) — 항상 보이는 마스크
    auto* bizMask = new MaskedTextCtrl(
        right, wxID_ANY,
        L"_\u2009_\u2009_-\u2009_\u2009_\u2009-_\u2009_\u2009_\u2009_\u2009_",
        wxBORDER_SIMPLE
    );
    InfoEdit.push_back(bizMask);        // ← wxTextCtrl*로 보관 (업캐스트)
    addRow("02. 사업자등록번호", bizMask);

    // 03. 법인등록번호 (6-7)
    auto* corpMask = new MaskedTextCtrl(
        right, wxID_ANY,
        L"_\u2009_\u2009_\u2009_\u2009_\u2009_-\u2009_\u2009_\u2009_\u2009_\u2009_\u2009_\u2009_\u2009",
        wxBORDER_SIMPLE
    );
    InfoEdit.push_back(corpMask);
    addRow("03. 법인등록번호", corpMask);

    // 04. 대표자명
    addRow("04. 대표자명", makeEdit(""));

    // 05. 사업장주소
    addRow("05. 사업장주소", makeEdit(""));

    // 06. 업태
    addRow("06. 업태", makeEdit(""));

    // 07. 종목
    addRow("07. 종목", makeEdit(""));

    right->SetSizer(v);

    // ★★★ (1) right를 rightSz에 등록
    rightSz->Add(right, 1, wxEXPAND);

    // ★★★ (2) vline과 m_RightPanel을 본문 H-sizer에 등록
    m_bodySizer->Add(vline, 0, wxEXPAND /*| wxLEFT|wxRIGHT, 4*/);
    m_bodySizer->Add(m_RightPanel, 1, wxEXPAND);

    // 갱신은 이 컨테이너 쪽에
    m_panel->Layout();   // 또는 최상위 프레임에서 Layout();
}

void ClientInfo::RightBottmInit()
{
    // 1) 우측 아래 패널(부모는 m_RightPanel!)
    m_RightBottmPanel = new wxPanel(m_RightPanel, wxID_ANY);
    m_RightBottmPanel->SetBackgroundColour(*wxWHITE);

    auto* bottomV = new wxBoxSizer(wxVERTICAL);
    m_RightBottmPanel->SetSizer(bottomV);

    // 2) 상단 가로바 (제목 + 버튼) — 부모는 m_RightBottmPanel
    auto* topH = new wxBoxSizer(wxHORIZONTAL);

    auto* title = new wxStaticText(m_RightBottmPanel, wxID_ANY, "[거래처 담당자]");
    TitleFontInit(title);

    topH->Add(title, 0, wxALIGN_CENTER_VERTICAL);

    topH->AddStretchSpacer();
    bottomV->Add(topH, 0, wxLEFT |wxEXPAND | wxBOTTOM, 8);

    // 3) 그리드 — 부모는 m_RightBottmPanel
    auto* grid = new wxGrid(m_RightBottmPanel, wxID_ANY);
    grid->CreateGrid(20, 3);

    // 라벨/모양 세팅 (원래 코드 그대로)
    grid->SetColLabelValue(0, "담당자명");
    grid->SetColLabelValue(1, "전화번호");
    grid->SetColLabelValue(2, "이메일");
    grid->EnableEditing(true);
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->EnableGridLines(true);
    grid->SetRowLabelSize(40);
    grid->SetColLabelSize(28);
    grid->SetDefaultRowSize(24);

    // 필요 시 컬럼 폭
    grid->SetColSize(0, 60);
    grid->SetColSize(1, 100);
    grid->SetColSize(2, 160);

    // ★ 우측 아래 섹션에서 그리드는 “확장”
    bottomV->Add(grid, 1, wxEXPAND);

    // 4) 우측 전체 시저(= m_RightPanel의 sizer)에 수평 구분선 + 아래 패널 추가
    auto* rightSz = wxDynamicCast(m_RightPanel->GetSizer(), wxBoxSizer);
    wxASSERT(rightSz);

    // 우측 아래 패널을 우측 칼럼에 추가 (비율은 취향: 1이면 위와 공간 나눔)
    rightSz->Add(m_RightBottmPanel, 1, wxEXPAND);

    // 5) 레이아웃 갱신 — 우측 컨테이너 기준으로
    m_RightPanel->Layout();
    m_panel->Layout(); // 필요 시
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

    auto* grid = new wxGrid(m_LeftPanel, wxID_ANY);
    grid->CreateGrid(20, 4);                    // 초기 10행 5열 (원하면 바꿔도 OK)
    grid->SetSizeHints(400, 450, 400, 450); // = Min=Max=465x283

    // 컬럼 라벨
    grid->SetColLabelValue(0, "");
    grid->SetColLabelValue(1, "회사명");
    grid->SetColLabelValue(2, "사업자번호");
    grid->SetColLabelValue(3, "대표자명");

    // 모양/동작 기본값
    grid->EnableEditing(false);                 // 읽기 전용(원하면 true)
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->EnableGridLines(true);
    grid->SetRowLabelSize(40);
    grid->SetColLabelSize(28);
    grid->SetDefaultRowSize(24);

    // 예시 데이터(원하면 제거)
    grid->SetCellValue(0, 0, "");
    grid->SetCellValue(0, 1, "휘온정보통신 주식회사");
    grid->SetCellValue(0, 2, "352-81-00723");
    grid->SetCellValue(0, 3, "김기종");
    grid->AutoSizeColumns();

    grid->SetColSize(0, 30);
    grid->SetColSize(1, 170);
    grid->SetColSize(2, 90);
    grid->SetColSize(3, 50);

    LeftSz->Add(grid, 1, wxALIGN_LEFT | wxALIGN_TOP);           // 그리드를 오른쪽 패널에 꽉 채움

    m_bodySizer->Add(m_LeftPanel, 1, wxEXPAND);
}
