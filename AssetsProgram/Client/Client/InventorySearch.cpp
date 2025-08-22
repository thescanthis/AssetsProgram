#include "pch.h"
#include "InventorySearch.h"
#include "InventoryAdd.h"
#include "Inventory_ClickInfo.h"

#define MAX_SCREEN_X 1145
#define MAX_SCREEN_Y 600
#define TREE_SIZE_X 100
#define TREESCREEN  MAX_SCREEN_X-(MAX_SCREEN_X-TREE_SIZE_X)



InventorySearch::InventorySearch(wxWindow* parent, const wxString Title) 
	: WidgetParent(parent, Title)
{
	m_RightPanel = new wxPanel(m_panel, wxID_ANY);
	m_RightPanel->SetBackgroundColour(*wxWHITE);

	SetSizeHints(MAX_SCREEN_X, MAX_SCREEN_Y, MAX_SCREEN_X, MAX_SCREEN_Y);         // ���� ũ��(���ϸ� ����)

	shell = new wxBoxSizer(wxVERTICAL);
	m_panel->SetSizer(shell);

	BtnTitleInit();  //����Ÿ��Ʋ
	InfoTitleInit(); //����Ÿ��Ʋ

	LeftBodyInit();
	LeftBottomInit();
	RightBodyInit();

	shell->Add(m_TopSizer,1,wxEXPAND);
	shell->Add(m_bodySizer, 1, wxEXPAND);   // �� �ٽ�!
	Layout();
	Center();
}

InventorySearch::~InventorySearch()
{

}



void InventorySearch::BtnTitleInit()
{
	m_TopPanel->SetSizeHints(MAX_SCREEN_X, -1, MAX_SCREEN_X, -1);      // �� 300 ����
	m_TopSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* topSz = new wxBoxSizer(wxHORIZONTAL);
	m_TopPanel->SetSizer(topSz);

	auto* title = new wxStaticText(m_TopPanel, wxID_ANY, "[�������]");
	TitleFontInit(title);

	topSz->Add(title, 0, wxALL, 10);
	topSz->AddStretchSpacer(1);
	m_TopSizer->Add(m_TopPanel, 0, wxEXPAND | wxALL, 4);
}

void InventorySearch::LeftBodyInit()
{
	// 1) ���� �г� �� ����
	m_LeftPanel->SetMinSize(wxSize(TREE_SIZE_X, 530));
	m_LeftPanel->SetMaxSize(wxSize(TREE_SIZE_X, 530));
	
	// ���� �г� ���ο� ���� sizer
	auto* leftRoot = new wxBoxSizer(wxVERTICAL);
	m_LeftPanel->SetSizer(leftRoot);
}

void InventorySearch::LeftBottomInit()
{
	m_LeftBottmPanel = new wxPanel(m_LeftPanel, wxID_ANY);
	auto* bottomSz = new wxBoxSizer(wxVERTICAL);
	m_LeftBottmPanel->SetSizer(bottomSz);

	//m_LeftBottmPanel->SetMinSize(wxSize(-1, 30));

	// 2) ������(��ư)
	auto* AssetAdd = new wxButton(m_LeftBottmPanel, wxID_ANY, "����ڻ� �߰�");
	auto* AssetDel = new wxButton(m_LeftBottmPanel, wxID_ANY, "����ڻ� ����");
	auto* AssetDeliveryNote = new wxButton(m_LeftBottmPanel, wxID_ANY, "����� ���");

	bottomSz->Add(AssetAdd, 0, wxEXPAND | wxBOTTOM, 4);
	bottomSz->Add(AssetDel, 0, wxEXPAND | wxBOTTOM, 4 );
	bottomSz->Add(AssetDeliveryNote, 0, wxEXPAND | wxBOTTOM, 4);

	// 3) m_LeftPanel�� ����(leftRoot)�� �߰��ؾ� ��!
	auto* leftRoot = wxDynamicCast(m_LeftPanel->GetSizer(), wxBoxSizer);
	wxASSERT(leftRoot); // �ݵ�� �����ؾ� �� (LeftBodyInit���� SetSizer �߾���)
	leftRoot->Add(m_LeftBottmPanel, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 4);

	m_bodySizer->Add(m_LeftPanel, 0, wxEXPAND);

	AssetAdd->Bind(wxEVT_BUTTON, &InventorySearch::BtnAddInventory, this);
	AssetDel->Bind(wxEVT_BUTTON, &InventorySearch::BtnDelInventory, this);
	AssetDeliveryNote->Bind(wxEVT_BUTTON, &InventorySearch::BtnDeliveryNote, this);
}

void InventorySearch::InfoTitleInit()
{
	m_RightTopPanel = new wxPanel(m_panel, wxID_ANY);
	auto* sz = new wxBoxSizer(wxHORIZONTAL);
	m_RightTopPanel->SetSizer(sz);

	auto* title = new wxStaticText(m_RightTopPanel, wxID_ANY, "���� - ���");
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

	int size = sizeof(LabelStr) / sizeof(wxString);

	m_grid = new wxGrid(m_RightPanel, wxID_ANY);
	m_grid->CreateGrid(30, size);                    // �ʱ� 10�� 5�� (���ϸ� �ٲ㵵 OK)
	m_grid->SetSizeHints(MAX_SCREEN_X - TREE_SIZE_X, 550, MAX_SCREEN_X - TREE_SIZE_X, 550);

	WU::GridLabelInitilize(m_grid, LabelStr);

	wxString Data[9] = { "������","24.10.27","AND-MES-B001~B008","�ֿ��������ȸ��","8","EA","�԰�","�������ü��" };
	for (int32 i = 0; i < size; i++)
		m_grid->SetCellValue(0,i, Data[i]);

	WU::GridColumnInitilize(m_grid, wid);

	rightRoot->Add(m_grid, 1, wxALIGN_LEFT | wxALIGN_TOP);           // �׸��带 ������ �гο� �� ä��

	// �� ���� H-BoxSizer�� ������� �߰�: Left | vline | Right
	m_bodySizer->Add(vline, 0, wxEXPAND | wxALL, 4);
	m_bodySizer->Add(m_RightPanel, 1, wxEXPAND | wxALL, 4);

	m_grid->Bind(wxEVT_GRID_CELL_LEFT_DCLICK, &InventorySearch::GridClickEvent, this);
}

void InventorySearch::BtnAddInventory(wxCommandEvent& event)
{
	AddInven = new InventoryAdd();
	AddInven->Show();
}

void InventorySearch::BtnDelInventory(wxCommandEvent& event)
{
	wxMessageBox("asdad");
}

void InventorySearch::BtnDeliveryNote(wxCommandEvent& event)
{
	wxMessageBox("asdad");
}

void InventorySearch::GridClickEvent(wxGridEvent& e)
{
	int32 Row = e.GetRow();
	int32 Rows = m_grid->GetNumberRows();
	int32 Cols = m_grid->GetNumberCols();

	Inventory_ClickInfo* ClickInfo = new  Inventory_ClickInfo({ MAX_SCREEN_X - TREE_SIZE_X, 600});
	ClickInfo->Show();
	e.Skip();
}
