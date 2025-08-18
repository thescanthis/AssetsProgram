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

void InventorySearch::BuildLayoutInit()
{

}

void InventorySearch::BtnTitleInit()
{
	m_TopPanel->SetSizeHints(TREESCREEN, -1, TREESCREEN, -1);      // �� 300 ����
	m_TopSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* topSz = new wxBoxSizer(wxHORIZONTAL);
	m_TopPanel->SetSizer(topSz);

	auto* title = new wxStaticText(m_TopPanel, wxID_ANY, "[��� �з�]");
	TitleFontInit(title);

	topSz->Add(title, 0, wxALL, 10);
	topSz->AddStretchSpacer(1);
	m_TopSizer->Add(m_TopPanel);
}

void InventorySearch::LeftBodyInit()
{
	// 1) ���� �г� �� ����
	m_LeftPanel->SetMinSize(wxSize(TREE_SIZE_X, 530));
	m_LeftPanel->SetMaxSize(wxSize(TREE_SIZE_X, 530));

	// ���� �г� ���ο� ���� sizer
	auto* leftRoot = new wxBoxSizer(wxVERTICAL);
	m_LeftPanel->SetSizer(leftRoot);

	// 4) Ʈ��
	TreeCtrl = new wxTreeCtrl(
		m_LeftPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_FULL_ROW_HIGHLIGHT
	);

	leftRoot->Add(TreeCtrl, 1, wxEXPAND | wxALL, 4);

	// 5) ��� ����
	auto rootId = TreeCtrl->AddRoot("������з�");
	auto basic = TreeCtrl->AppendItem(rootId, "����");
	TreeCtrl->AppendItem(basic, "���");
	TreeCtrl->AppendItem(basic, "����");
	auto adv = TreeCtrl->AppendItem(rootId, "������");
	TreeCtrl->AppendItem(adv, "��Ʈ��ŷ");
	TreeCtrl->AppendItem(adv, "�׷��� Ž��");
	TreeCtrl->ExpandAll();
}

void InventorySearch::LeftBottomInit()
{
	m_LeftBottmPanel = new wxPanel(m_LeftPanel, wxID_ANY);
	auto* bottomSz = new wxBoxSizer(wxHORIZONTAL);
	m_LeftBottmPanel->SetSizer(bottomSz);

	m_LeftBottmPanel->SetMinSize(wxSize(-1, 30));

	// 2) ������(�Է� + ��ư)
	auto* edit = new wxTextCtrl(m_LeftBottmPanel, wxID_ANY, "",
		wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	auto* btn = new wxButton(m_LeftBottmPanel, wxID_ANY, "�˻�");

	bottomSz->Add(edit, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT);
	bottomSz->Add(btn, 0, wxALIGN_CENTER_VERTICAL);

	// 3) m_LeftPanel�� ����(leftRoot)�� �߰��ؾ� ��!
	auto* leftRoot = wxDynamicCast(m_LeftPanel->GetSizer(), wxBoxSizer);
	wxASSERT(leftRoot); // �ݵ�� �����ؾ� �� (LeftBodyInit���� SetSizer �߾���)
	leftRoot->Add(m_LeftBottmPanel, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 4);

	m_bodySizer->Add(m_LeftPanel, 0, wxEXPAND);
}

void InventorySearch::InfoTitleInit()
{
	m_RightTopPanel = new wxPanel(m_panel, wxID_ANY);
	auto* sz = new wxBoxSizer(wxHORIZONTAL);
	m_RightTopPanel->SetSizer(sz);

	auto* title = new wxStaticText(m_RightTopPanel, wxID_ANY, "����");
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
	m_grid->CreateGrid(30, 7);                    // �ʱ� 10�� 5�� (���ϸ� �ٲ㵵 OK)
	m_grid->SetSizeHints(770, 550, 770, 550);

	// �׸��� ���� ��
	m_grid->SetDefaultCellAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// ���(��)�� ���
	m_grid->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
	m_grid->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// �÷� ��
	m_grid->SetColLabelValue(0, "��¥");
	m_grid->SetColLabelValue(1, "����ȣ");
	m_grid->SetColLabelValue(2, "�԰�");
	m_grid->SetColLabelValue(3, "���");
	m_grid->SetColLabelValue(4, "���");
	m_grid->SetColLabelValue(5, "�԰�ó");
	m_grid->SetColLabelValue(6, "���ó");

	// ���/���� �⺻��
	m_grid->EnableEditing(true);                 // �б� ����(���ϸ� true)
	m_grid->SetSelectionMode(wxGrid::wxGridSelectRows);
	m_grid->EnableGridLines(true);
	m_grid->SetRowLabelSize(40);
	m_grid->SetColLabelSize(28);
	m_grid->SetDefaultRowSize(24);

	// ���� ������(���ϸ� ����)
	m_grid->SetCellValue(0, 0, "24.10.27");
	m_grid->SetCellValue(0, 1, "AND-MES-B001~B008");
	m_grid->SetCellValue(0, 2, "8 EA");
	m_grid->SetCellValue(0, 3, "");
	m_grid->SetCellValue(0, 4, "8EA");
	m_grid->SetCellValue(0, 5, "�ֿ��������ȸ��");
	m_grid->SetCellValue(0, 6, "");
	m_grid->AutoSizeColumns();

	m_grid->SetColSize(0, 70);
	m_grid->SetColSize(1,140);
	m_grid->SetColSize(2, 70);
	m_grid->SetColSize(3, 70);
	m_grid->SetColSize(4, 70);
	m_grid->SetColSize(5, 140);
	m_grid->SetColSize(6, 140);

	rightRoot->Add(m_grid, 1, wxALIGN_LEFT | wxALIGN_TOP);           // �׸��带 ������ �гο� �� ä��

	// �� ���� H-BoxSizer�� ������� �߰�: Left | vline | Right
	m_bodySizer->Add(vline, 0, wxEXPAND | wxALL, 4);
	m_bodySizer->Add(m_RightPanel, 1, wxEXPAND | wxALL, 4);
}
