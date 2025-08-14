#include "pch.h"
#include "CompanyInfoDetail.h"
#include "MaskedTextCtrl.h"

/*
Frame(CompanyInfoDetail)
└─ m_panel : wxPanel
   └─ shell(V) : wxBoxSizer(VERTICAL)
      ├─ m_TopPanel : wxPanel                         // 상단 버튼바
      │  └─ topSz(H) : wxBoxSizer(HORIZONTAL)
      │     ├─ (stretch)
      │     ├─ wxButton "저장"
      │     └─ wxButton "나가기"
      ├─ line : wxStaticLine(H)                       // 가로 구분선
      └─ bodyH(H) : wxBoxSizer(HORIZONTAL)            // 본문 가로 배치(m_bodySizer)
         ├─ m_LeftPanel : wxPanel (폭 300 고정)
         │  └─ leftRoot(V) : wxBoxSizer(VERTICAL)
         │     └─ left : wxPanel
         │        └─ v(V) : wxBoxSizer(VERTICAL)
         │           ├─ topL(H) : wxBoxSizer(H)      // 좌측 상단바(높이 kTopBarH)
         │           │  ├─ wxStaticText "[기본정보]" (Bold)
         │           │  └─ (stretch)
         │           └─ fields(V) : wxBoxSizer(V)    // 폼 영역
         │              ├─ row(H) : [StaticText "01. 회사명", wxTextCtrl]
         │              ├─ row(H) : [StaticText "02. 사업자등록번호", MaskedTextCtrl]
         │              ├─ row(H) : [StaticText "04. 법인등록번호",   MaskedTextCtrl]
         │              ├─ row(H) : [StaticText "05. 대표자명",       wxTextCtrl]
         │              ├─ row(H) : [StaticText "07. 사업장주소",     wxTextCtrl]
         │              ├─ row(H) : [StaticText "08. 업태",           wxTextCtrl]
         │              └─ row(H) : [StaticText "09. 종목",           wxTextCtrl]
         ├─ vline : wxStaticLine(VERTICAL)            // 좌/우 세로 구분선
         └─ m_RightPanel : wxPanel
            └─ rightV(V) : wxBoxSizer(VERTICAL)
               ├─ topR(H) : wxBoxSizer(H)            // 우측 상단바(높이 kTopBarH)
               │  ├─ wxStaticText "[자재실 정보]" (Bold)
               │  ├─ (stretch)
               │  ├─ wxButton "추가"
               │  └─ wxButton "삭제"
               └─ grid : wxGrid                      // 우측 컨텐츠
                  (※ 고정 크기면 SetSizeHints(465,283,465,283) 후 proportion=0로 Add,
                     확장 사용이면 proportion=1 | wxEXPAND)
*/

CompanyInfoDetail::CompanyInfoDetail(wxWindow* parent)
	:wxFrame(parent, wxID_ANY, "회사정보", wxDefaultPosition, wxSize(800, 400))
{
	SetSizeHints(800, 400, 800, 400);         // 고정 크기(원하면 제거)
    m_panel = new wxPanel(this, wxID_ANY);
    m_panel->SetBackgroundColour(wxColour(247, 249, 253));

    // 메인 패널
    auto* shell = new wxBoxSizer(wxVERTICAL);
    m_panel->SetSizer(shell);

    // 저장 나가기 공간
    BtnTitleInit();
    auto* line = new wxStaticLine(m_panel, wxID_ANY);

    //좌측 정보
    LeftBodyInit();
    
    //우측 그리드
    RightBodyInit();

    // 위→아래로 배치
    shell->Add(m_TopPanel, 0, wxEXPAND);
    shell->Add(line, 0, wxEXPAND);
    shell->Add(m_bodySizer, 1, wxEXPAND);   // ← 핵심!

	// 프레임 채우기
	auto* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->Add(m_panel, 1, wxEXPAND);
	SetSizer(frameSizer);
	Layout();
	Center();
}

CompanyInfoDetail::~CompanyInfoDetail()
{
    
}

void CompanyInfoDetail::BtnTitleInit()
{
    // 상단바
    m_TopPanel = new wxPanel(m_panel, wxID_ANY);
    m_TopPanel->SetBackgroundColour(wxColour(247, 249, 253));

    auto* topSz = new wxBoxSizer(wxHORIZONTAL);
    m_TopPanel->SetSizer(topSz);
    topSz->AddStretchSpacer();
    auto* btnSave = new wxButton(m_TopPanel, wxID_SAVE, "저장");
    auto* btnExit = new wxButton(m_TopPanel, wxID_EXIT, "나가기");
    topSz->Add(btnSave, 0, wxALL, 8);
    topSz->Add(btnExit, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
}

void CompanyInfoDetail::LeftBodyInit()
{
    // 기본정보
    m_LeftPanel = new wxPanel(m_panel, wxID_ANY);
    m_bodySizer = new wxBoxSizer(wxHORIZONTAL);
    m_LeftPanel->SetSizeHints(300, -1, 300, -1);      // 폭 300 고정

    // 왼쪽 패널 내부용 세로 sizer
    auto* leftRoot = new wxBoxSizer(wxVERTICAL);
    m_LeftPanel->SetSizer(leftRoot);

    InfoTitleInit();

    m_bodySizer->Add(m_LeftPanel, 0, wxEXPAND);
}

void CompanyInfoDetail::RightBodyInit()
{
    // 세로 구분선 (부모는 m_panel — m_bodySizer가 붙은 윈도우와 동일)
    auto* vline = new wxStaticLine(
        m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);

    // 오른쪽 패널
    m_RightPanel = new wxPanel(m_panel, wxID_ANY);
    m_RightPanel->SetBackgroundColour(*wxWHITE);
    
    // 오른쪽 내부 sizer
    auto* rightSz = new wxBoxSizer(wxVERTICAL);
    m_RightPanel->SetSizer(rightSz);

    auto* topH = new wxBoxSizer(wxHORIZONTAL);

    // ★ [거래처정보] 제목 (왼쪽과 동일한 스타일)
    auto* rtitle = new wxStaticText(m_RightPanel, wxID_ANY, "[자제실 정보]");
    { wxFont f = rtitle->GetFont(); f.MakeBold(); rtitle->SetFont(f); }
    rtitle->SetForegroundColour(wxColour(80, 80, 120));
    topH->Add(rtitle, 0, wxLEFT |wxTOP | wxRIGHT | wxBOTTOM, 8);

    topH->AddStretchSpacer();
    auto* btnSave = new wxButton(m_RightPanel, wxID_SAVE, "추가");
    auto* btnExit = new wxButton(m_RightPanel, wxID_EXIT, "삭제");
    topH->Add(btnSave, 0, wxALL, 8);
    topH->Add(btnExit, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);

    // 상단 가로바를 우측 패널의 세로 레이아웃에 추가
    rightSz->Add(topH, 0, wxEXPAND | wxBOTTOM, 8);

    auto* grid = new wxGrid(m_RightPanel, wxID_ANY);
    grid->CreateGrid(20, 4);                    // 초기 10행 5열 (원하면 바꿔도 OK)
    grid->SetSizeHints(485, 270, 485, 270); // = Min=Max=465x283

    // 컬럼 라벨
    grid->SetColLabelValue(0, "선반위치");
    grid->SetColLabelValue(1, "라벨코드");
    grid->SetColLabelValue(2, "이름");
    grid->SetColLabelValue(3, "물품 갯수");

    // 모양/동작 기본값
    grid->EnableEditing(false);                 // 읽기 전용(원하면 true)
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->EnableGridLines(true);
    grid->SetRowLabelSize(40);
    grid->SetColLabelSize(28);
    grid->SetDefaultRowSize(24);
    
    // 예시 데이터(원하면 제거)
    grid->SetCellValue(0, 0, "A-12");
    grid->SetCellValue(0, 1, "C-123456788");
    grid->SetCellValue(0, 2, "무전통신기-X025");
    grid->SetCellValue(0, 3, "123456");
    grid->AutoSizeColumns();

    grid->SetColSize(0, 70);
    grid->SetColSize(1, 140);
    grid->SetColSize(2, 140);
    grid->SetColSize(3, 70);

    rightSz->Add(grid, 1, wxALIGN_LEFT | wxALIGN_TOP);           // 그리드를 오른쪽 패널에 꽉 채움

    // ★ 본문 H-BoxSizer에 순서대로 추가: Left | vline | Right
    m_bodySizer->Add(vline, 0, wxEXPAND);
    m_bodySizer->Add(m_RightPanel, 1, wxEXPAND);
}

void CompanyInfoDetail::InfoTitleInit()
{
    // 좌측 폼 컨테이너 (폭 300 고정)
    auto* left = new wxPanel(m_LeftPanel, wxID_ANY);
    left->SetBackgroundColour(*wxWHITE);
    left->SetMinSize(wxSize(300, -1));

    auto* v = new wxBoxSizer(wxVERTICAL);

    const int kTopBarH = 32; // 필요하면 FromDIP(32, this) 사용
    // [기본정보] 제목
// 가로 상단바: [기본정보] ..... (빈공간)
    auto* topL = new wxBoxSizer(wxHORIZONTAL);
    auto* title = new wxStaticText(left, wxID_ANY, "[기본정보]");
    { wxFont f = title->GetFont(); f.MakeBold(); title->SetFont(f); }
    title->SetForegroundColour(wxColour(80, 80, 120));
    topL->Add(title, 0, wxALIGN_CENTER_VERTICAL);
    topL->AddStretchSpacer();

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

        wxStaticText* lb = new wxStaticText(left, wxID_ANY, label);
        lb->SetMinSize(wxSize(110, -1));                        // 라벨 폭 통일
        InfoTitle.push_back(lb);
        row->Add(lb, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);

        row->Add(editor, 1, wxEXPAND);
        fields->Add(row, 0, wxTOP | wxEXPAND | wxBOTTOM, 6);
        };

    // 일반 입력칸 생성 헬퍼 (쓰기 가능)
    auto makeEdit = [&](const wxString& hint)->wxTextCtrl* {
        wxTextCtrl* ed = new wxTextCtrl(left, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
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
        left, wxID_ANY,
        L"_\u2009_\u2009_-\u2009_\u2009_\u2009-_\u2009_\u2009_\u2009_\u2009_",
        wxBORDER_SIMPLE
    );
    InfoEdit.push_back(bizMask);        // ← wxTextCtrl*로 보관 (업캐스트)
    addRow("02. 사업자등록번호", bizMask);

    // 03. 법인등록번호 (6-7)
    auto* corpMask = new MaskedTextCtrl(
        left, wxID_ANY,
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

    left->SetSizer(v);

    auto* leftRoot = wxDynamicCast(m_LeftPanel->GetSizer(), wxBoxSizer);
    leftRoot->Add(left, 1, wxEXPAND);   // ← m_LeftPanel 내부에만 추가

    // 갱신
    m_LeftPanel->Layout(); 
}