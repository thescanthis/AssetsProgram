#include "pch.h"
#include "InventorySearch.h"
#include "InventoryAdd.h"

#define MAX_SCREEN_X 1145
#define MAX_SCREEN_Y 600
#define TREE_SIZE_X 100
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



void InventorySearch::BtnTitleInit()
{
	m_TopPanel->SetSizeHints(MAX_SCREEN_X, -1, MAX_SCREEN_X, -1);      // 폭 300 고정
	m_TopSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* topSz = new wxBoxSizer(wxHORIZONTAL);
	m_TopPanel->SetSizer(topSz);

	auto* title = new wxStaticText(m_TopPanel, wxID_ANY, "[사업정보]");
	TitleFontInit(title);

	topSz->Add(title, 0, wxALL, 10);
	topSz->AddStretchSpacer(1);
	m_TopSizer->Add(m_TopPanel, 0, wxEXPAND | wxALL, 4);
}

void InventorySearch::LeftBodyInit()
{
	// 1) 왼쪽 패널 폭 고정
	m_LeftPanel->SetMinSize(wxSize(TREE_SIZE_X, 530));
	m_LeftPanel->SetMaxSize(wxSize(TREE_SIZE_X, 530));
	
	// 왼쪽 패널 내부용 세로 sizer
	auto* leftRoot = new wxBoxSizer(wxVERTICAL);
	m_LeftPanel->SetSizer(leftRoot);
}

void InventorySearch::LeftBottomInit()
{
	m_LeftBottmPanel = new wxPanel(m_LeftPanel, wxID_ANY);
	auto* bottomSz = new wxBoxSizer(wxVERTICAL);
	m_LeftBottmPanel->SetSizer(bottomSz);

	//m_LeftBottmPanel->SetMinSize(wxSize(-1, 30));

	// 2) 위젯들(버튼)
	auto* AssetAdd = new wxButton(m_LeftBottmPanel, wxID_ANY, "재고자산 추가");
	auto* AssetDel = new wxButton(m_LeftBottmPanel, wxID_ANY, "재고자산 삭제");

	bottomSz->Add(AssetAdd, 0, wxEXPAND | wxBOTTOM, 4);
	bottomSz->Add(AssetDel, 0, wxEXPAND | wxBOTTOM, 4 );

	// 3) m_LeftPanel의 시저(leftRoot)에 추가해야 함!
	auto* leftRoot = wxDynamicCast(m_LeftPanel->GetSizer(), wxBoxSizer);
	wxASSERT(leftRoot); // 반드시 존재해야 함 (LeftBodyInit에서 SetSizer 했었죠)
	leftRoot->Add(m_LeftBottmPanel, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 4);

	m_bodySizer->Add(m_LeftPanel, 0, wxEXPAND);

	AssetAdd->Bind(wxEVT_BUTTON, &InventorySearch::BtnAddInventory, this);
}

void InventorySearch::InfoTitleInit()
{
	m_RightTopPanel = new wxPanel(m_panel, wxID_ANY);
	auto* sz = new wxBoxSizer(wxHORIZONTAL);
	m_RightTopPanel->SetSizer(sz);

	auto* title = new wxStaticText(m_RightTopPanel, wxID_ANY, "마넷 - 재귀");
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

	wxString LabelStr[8] = { "상품명","날짜","재고번호","거래처","수량","단위","재고분류","사업명" };
	int size = sizeof(LabelStr) / sizeof(wxString);

	m_grid = new wxGrid(m_RightPanel, wxID_ANY);
	m_grid->CreateGrid(30, size);                    // 초기 10행 5열 (원하면 바꿔도 OK)
	m_grid->SetSizeHints(MAX_SCREEN_X - TREE_SIZE_X, 550, MAX_SCREEN_X - TREE_SIZE_X, 550);

	// 그리드 만든 뒤
	m_grid->SetDefaultCellAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// 헤더(라벨)도 가운데
	m_grid->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
	m_grid->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// 컬럼 라벨

	for (int32 i = 0; i < size; i++)
		m_grid->SetColLabelValue(i, LabelStr[i]);

	// 모양/동작 기본값
	m_grid->EnableEditing(false);                 // 읽기 전용(원하면 true)
	m_grid->SetSelectionMode(wxGrid::wxGridSelectRows);
	m_grid->EnableGridLines(true);
	m_grid->SetRowLabelSize(40);
	m_grid->SetColLabelSize(28);
	m_grid->SetDefaultRowSize(24);

	wxString Data[9] = { "무전기","24.10.27","AND-MES-B001~B008","휘온정보통신회사","8","EA","입고","마넷통신체계" };
	for (int32 i = 0; i < size; i++)
		m_grid->SetCellValue(0,i, Data[i]);

	int32 wid[8] = { 140,70,140,210,70,70,70,180};
	for (int i = 0; i < size; i++)
		m_grid->SetColSize(i, wid[i]);

	//m_grid->AutoSizeColumns();

	rightRoot->Add(m_grid, 1, wxALIGN_LEFT | wxALIGN_TOP);           // 그리드를 오른쪽 패널에 꽉 채움

	// ★ 본문 H-BoxSizer에 순서대로 추가: Left | vline | Right
	m_bodySizer->Add(vline, 0, wxEXPAND | wxALL, 4);
	m_bodySizer->Add(m_RightPanel, 1, wxEXPAND | wxALL, 4);
}

void InventorySearch::BtnAddInventory(wxCommandEvent& event)
{
	AddInven = new InventoryAdd();
	AddInven->Show();
}
