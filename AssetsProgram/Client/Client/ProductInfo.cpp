#include "pch.h"
#include "ProductInfo.h"

ProductInfo::ProductInfo(wxWindow* parent, const wxString Title)
	:WidgetParent(parent,Title)
{
    SetSizeHints(800, 400, 800, 400);         // 고정 크기(원하면 제거)

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
ProductInfo::~ProductInfo()
{
}

void ProductInfo::BtnTitleInit()
{
    auto* topSz = new wxBoxSizer(wxHORIZONTAL);
    m_TopPanel->SetSizer(topSz);
    topSz->AddStretchSpacer();
    auto* btnSave = new wxButton(m_TopPanel, wxID_SAVE, "저장");
    auto* btnExit = new wxButton(m_TopPanel, wxID_EXIT, "나가기");
    topSz->Add(btnSave, 0, wxALL, 8);
    topSz->Add(btnExit, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
}

void ProductInfo::LeftBodyInit()
{
    m_LeftPanel->SetSizeHints(300, -1, 300, -1);      // 폭 300 고정

    // 왼쪽 패널 내부용 세로 sizer
    auto* leftRoot = new wxBoxSizer(wxVERTICAL);
    m_LeftPanel->SetSizer(leftRoot);

    InfoTitleInit();

    m_bodySizer->Add(m_LeftPanel, 0, wxEXPAND);
}

void ProductInfo::InfoTitleInit()
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

    // 공통: 한 줄 추가(라벨 + 이미 만든 에디트 위젯)
    auto addRow = [&](const wxString& label, wxWindow* editor) {
        wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);

        wxStaticText* lb = new wxStaticText(left, wxID_ANY, label);
        lb->SetMinSize(wxSize(110, -1));
        InfoTitle.push_back(lb);
        row->Add(lb, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);

        row->Add(editor, 1, wxEXPAND);
        fields->Add(row, 0, wxTOP | wxEXPAND | wxBOTTOM, 5);
        };

    // 일반 입력칸 생성 헬퍼 (쓰기 가능)
    auto makeEdit = [&](const wxString& hint)->wxTextCtrl* {
        wxTextCtrl* ed = new wxTextCtrl(left, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
        if (!hint.empty()) ed->SetHint(hint);
        ed->SetBackgroundColour(*wxWHITE);
        ed->SetForegroundColour(wxColour(50, 50, 50));
        InfoEdit.push_back(ed);
        return ed;
        };

    for (int i = 0; i < InventoryTitle.size(); i++)
        addRow(wxString(std::to_string(i+1))+". " + InventoryTitle[i], makeEdit(""));

    auto* btnAdd = new wxButton(left, wxID_EXIT, "추가");
    auto* btnExit = new wxButton(left, wxID_EXIT, "취소");
    wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);

    row->AddStretchSpacer();
    row->Add(btnAdd, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
    row->Add(btnExit, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
    row->AddStretchSpacer();
    fields->Add(row, 0, wxTOP | wxEXPAND | wxBOTTOM, 12);


    left->SetSizer(v);

    auto* leftRoot = wxDynamicCast(m_LeftPanel->GetSizer(), wxBoxSizer);
    leftRoot->Add(left, 1, wxEXPAND);
}

void ProductInfo::RightBodyInit()
{
    // 세로 구분선 (부모는 m_panel — m_bodySizer가 붙은 윈도우와 동일)
    auto* vline = new wxStaticLine(
        m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);

    // 오른쪽 내부 sizer
    auto* rightSz = new wxBoxSizer(wxVERTICAL);
    m_RightPanel->SetSizer(rightSz);

    auto* topH = new wxBoxSizer(wxHORIZONTAL);

    // ★ [거래처정보] 제목 (왼쪽과 동일한 스타일)
    auto* rtitle = new wxStaticText(m_RightPanel, wxID_ANY, "[자제실 정보]");
    { wxFont f = rtitle->GetFont(); f.MakeBold(); rtitle->SetFont(f); }
    rtitle->SetForegroundColour(wxColour(80, 80, 120));
    topH->Add(rtitle, 0, wxLEFT | wxTOP | wxRIGHT | wxBOTTOM, 8);

    topH->AddStretchSpacer();
    auto* btnExit = new wxButton(m_RightPanel, wxID_EXIT, "삭제");
    topH->Add(btnExit, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);

    // 상단 가로바를 우측 패널의 세로 레이아웃에 추가
    rightSz->Add(topH, 0, wxEXPAND | wxBOTTOM, 8);

    m_grid = new wxGrid(m_RightPanel, wxID_ANY);
    m_grid->CreateGrid(20, 4);                    // 초기 10행 5열 (원하면 바꿔도 OK)
    m_grid->SetSizeHints(485, 270, 485, 270); // = Min=Max=465x283

    // 컬럼 라벨
    m_grid->SetColLabelValue(0, InventoryTitle[M_CLASS]);
    m_grid->SetColLabelValue(1, InventoryTitle[I_CLASS]);
    m_grid->SetColLabelValue(2, InventoryTitle[P_CLASS]);
    m_grid->SetColLabelValue(3, InventoryTitle[IS_CLASS]);

    // 모양/동작 기본값
    m_grid->EnableEditing(false);                 // 읽기 전용(원하면 true)
    m_grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    m_grid->EnableGridLines(true);
    m_grid->SetRowLabelSize(40);
    m_grid->SetColLabelSize(28);
    m_grid->SetDefaultRowSize(24);

    // 예시 데이터(원하면 제거)
    m_grid->SetCellValue(0, 0, "A-12");
    m_grid->SetCellValue(0, 1, "C-123456788");
    m_grid->SetCellValue(0, 2, "무전통신기-X025");
    m_grid->SetCellValue(0, 3, "123456");
    m_grid->AutoSizeColumns();

    m_grid->SetColSize(0, 70);
    m_grid->SetColSize(1, 140);
    m_grid->SetColSize(2, 140);
    m_grid->SetColSize(3, 70);

    rightSz->Add(m_grid, 1, wxALIGN_LEFT | wxALIGN_TOP);


    m_bodySizer->Add(vline, 0, wxEXPAND);
    m_bodySizer->Add(m_RightPanel, 1, wxEXPAND);
}
