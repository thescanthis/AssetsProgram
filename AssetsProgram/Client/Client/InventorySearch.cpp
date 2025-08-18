#include "pch.h"
#include "InventorySearch.h"
#include <wx/treectrl.h>

#define MAX_SCREEN_X 1045
#define MAX_SCREEN_Y 600
#define TREE_SIZE_X 250
#define TREESCREEN  MAX_SCREEN_X-(MAX_SCREEN_X-TREE_SIZE_X)



InventorySearch::InventorySearch(wxWindow* parent, const wxString Title) 
	: WidgetParent(parent, Title)
{
	SetSizeHints(MAX_SCREEN_X, MAX_SCREEN_Y, MAX_SCREEN_X, MAX_SCREEN_Y);         // 고정 크기(원하면 제거)
	shell = new wxBoxSizer(wxVERTICAL);
	m_panel->SetSizer(shell);

	BtnTitleInit();  //좌측타이틀
	InfoTitleInit(); //우측타이틀

	LeftBodyInit();
	LeftBottomInit();
	RightBodyInit();

	shell->Add(m_TopSizer,1,wxEXPAND);
	shell->Add(m_bodySizer, 1, wxEXPAND);   // ← 핵심!
	Layout();
	Center();
}

InventorySearch::~InventorySearch()
{

}

void InventorySearch::BuildLayoutInit()
{

}

void InventorySearch::BtnTitleInit()
{
	m_TopPanel->SetSizeHints(TREESCREEN, -1, TREESCREEN, -1);      // 폭 300 고정
	m_TopSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* topSz = new wxBoxSizer(wxHORIZONTAL);
	m_TopPanel->SetSizer(topSz);

	auto* title = new wxStaticText(m_TopPanel, wxID_ANY, "[재고 분류]");
	TitleFontInit(title);

	topSz->Add(title, 0, wxALL, 10);
	topSz->AddStretchSpacer(1);
	m_TopSizer->Add(m_TopPanel);
}

void InventorySearch::LeftBodyInit()
{
	// 1) 왼쪽 패널 폭 고정
	m_LeftPanel->SetMinSize(wxSize(TREE_SIZE_X, 530));
	m_LeftPanel->SetMaxSize(wxSize(TREE_SIZE_X, 530));

	// 왼쪽 패널 내부용 세로 sizer
	auto* leftRoot = new wxBoxSizer(wxVERTICAL);
	m_LeftPanel->SetSizer(leftRoot);

	// 4) 트리
	TreeCtrl = new wxTreeCtrl(
		m_LeftPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_FULL_ROW_HIGHLIGHT
	);

	leftRoot->Add(TreeCtrl, 1, wxEXPAND | wxALL, 4);

	// 5) 노드 예시
	auto rootId = TreeCtrl->AddRoot("사업별분류");
	auto basic = TreeCtrl->AppendItem(rootId, "마넷");
	TreeCtrl->AppendItem(basic, "재귀");
	TreeCtrl->AppendItem(basic, "스택");
	auto adv = TreeCtrl->AppendItem(rootId, "무전기");
	TreeCtrl->AppendItem(adv, "백트래킹");
	TreeCtrl->AppendItem(adv, "그래프 탐색");
	TreeCtrl->ExpandAll();
}

void InventorySearch::LeftBottomInit()
{
	m_LeftBottmPanel = new wxPanel(m_LeftPanel, wxID_ANY);
	auto* bottomSz = new wxBoxSizer(wxHORIZONTAL);
	m_LeftBottmPanel->SetSizer(bottomSz);

	m_LeftBottmPanel->SetMinSize(wxSize(-1, 30));

	// 2) 위젯들(입력 + 버튼)
	auto* edit = new wxTextCtrl(m_LeftBottmPanel, wxID_ANY, "",
		wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	auto* btn = new wxButton(m_LeftBottmPanel, wxID_ANY, "검색");

	bottomSz->Add(edit, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT);
	bottomSz->Add(btn, 0, wxALIGN_CENTER_VERTICAL);

	// 3) m_LeftPanel의 시저(leftRoot)에 추가해야 함!
	auto* leftRoot = wxDynamicCast(m_LeftPanel->GetSizer(), wxBoxSizer);
	wxASSERT(leftRoot); // 반드시 존재해야 함 (LeftBodyInit에서 SetSizer 했었죠)
	leftRoot->Add(m_LeftBottmPanel, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 4);

	m_bodySizer->Add(m_LeftPanel, 0, wxEXPAND);
}

void InventorySearch::InfoTitleInit()
{
	m_RightTopPanel = new wxPanel(m_panel, wxID_ANY);
	auto* sz = new wxBoxSizer(wxHORIZONTAL);
	m_RightTopPanel->SetSizer(sz);

	auto* title = new wxStaticText(m_RightTopPanel, wxID_ANY, "마넷");
	TitleFontInit(title,6);

	sz->AddStretchSpacer(1);
	sz->Add(title, 0, wxALIGN_CENTER);
	sz->AddStretchSpacer(1);

	m_TopSizer->Add(m_RightTopPanel, 1, wxEXPAND | wxALL, 4);
}

void InventorySearch::RightBodyInit()
{
	auto* vline = new wxStaticLine(
		m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);

	auto* rightRoot = new wxBoxSizer(wxVERTICAL);
	m_RightPanel->SetSizer(rightRoot);

	m_grid = new wxGrid(m_RightPanel, wxID_ANY);
	m_grid->CreateGrid(30, 7);                    // 초기 10행 5열 (원하면 바꿔도 OK)
	m_grid->SetSizeHints(770, 550, 770, 550);

	// 그리드 만든 뒤
	m_grid->SetDefaultCellAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// 헤더(라벨)도 가운데
	m_grid->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
	m_grid->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// 컬럼 라벨
	m_grid->SetColLabelValue(0, "날짜");
	m_grid->SetColLabelValue(1, "재고번호");
	m_grid->SetColLabelValue(2, "입고");
	m_grid->SetColLabelValue(3, "출고");
	m_grid->SetColLabelValue(4, "재고");
	m_grid->SetColLabelValue(5, "입고처");
	m_grid->SetColLabelValue(6, "출고처");

	// 모양/동작 기본값
	m_grid->EnableEditing(true);                 // 읽기 전용(원하면 true)
	m_grid->SetSelectionMode(wxGrid::wxGridSelectRows);
	m_grid->EnableGridLines(true);
	m_grid->SetRowLabelSize(40);
	m_grid->SetColLabelSize(28);
	m_grid->SetDefaultRowSize(24);

	// 예시 데이터(원하면 제거)
	m_grid->SetCellValue(0, 0, "24.10.27");
	m_grid->SetCellValue(0, 1, "AND-MES-B001~B008");
	m_grid->SetCellValue(0, 2, "8 EA");
	m_grid->SetCellValue(0, 3, "");
	m_grid->SetCellValue(0, 4, "8EA");
	m_grid->SetCellValue(0, 5, "휘온정보통신회사");
	m_grid->SetCellValue(0, 6, "");
	m_grid->AutoSizeColumns();

	m_grid->SetColSize(0, 70);
	m_grid->SetColSize(1,140);
	m_grid->SetColSize(2, 70);
	m_grid->SetColSize(3, 70);
	m_grid->SetColSize(4, 70);
	m_grid->SetColSize(5, 140);
	m_grid->SetColSize(6, 140);

	rightRoot->Add(m_grid, 1, wxALIGN_LEFT | wxALIGN_TOP);           // 그리드를 오른쪽 패널에 꽉 채움

	// ★ 본문 H-BoxSizer에 순서대로 추가: Left | vline | Right
	m_bodySizer->Add(vline, 0, wxEXPAND | wxALL, 4);
	m_bodySizer->Add(m_RightPanel, 1, wxEXPAND | wxALL, 4);
}
