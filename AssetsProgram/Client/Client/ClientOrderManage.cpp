#include "pch.h"
#include "ClientOrderManage.h"
#include "ClientOrderInput.h"


ClientOrderManage::ClientOrderManage(wxWindow* parent,
    const wxString& title,
    const wxSize& size)
    : wxFrame(parent, wxID_ANY, title, wxDefaultPosition, size)
{
    m_panel = new wxPanel(this, wxID_ANY);
    m_panel->SetBackgroundColour(wxColour(247, 249, 253));

    auto* frame = new wxBoxSizer(wxVERTICAL);
    auto* root = new wxBoxSizer(wxVERTICAL);
    m_panel->SetSizer(root);

    BuildUI();

    frame->Add(m_panel, 1, wxEXPAND);
    SetSizer(frame);
    Layout();
    InstallEscClose();
    CentreOnParent();
}

void ClientOrderManage::BuildUI()
{
    auto* root = wxDynamicCast(m_panel->GetSizer(), wxBoxSizer);

    BuildToolbar(root);
    root->Add(new wxStaticLine(m_panel, wxID_ANY), 0, wxEXPAND);

    BuildTabs(root);

    root->AddSpacer(4);
}

/* ================= Toolbar ================= */
void ClientOrderManage::BuildToolbar(wxBoxSizer* root)
{
    auto* bar = new wxPanel(m_panel, wxID_ANY);
    auto* h = new wxBoxSizer(wxHORIZONTAL);
    bar->SetSizer(h);

    h->AddStretchSpacer(1);

    m_btnPrint = WU::MakeButton(bar, "�μ�", &ClientOrderManage::OnPrint,this);
    h->Add(m_btnPrint, 0, 0);
    h->AddSpacer(6);

    m_btnNew = WU::MakeButton(bar, "�߰�", &ClientOrderManage::OnAdd, this);
    h->Add(m_btnNew, 0, 0);
    h->AddSpacer(6);

    m_btnEdit = WU::MakeButton(bar, "����", &ClientOrderManage::OnEdit, this);
    h->Add(m_btnEdit, 0, 0);
    h->AddSpacer(6);

    m_btnDel = WU::MakeButton(bar, "����", &ClientOrderManage::OnDelete, this);
    h->Add(m_btnDel, 0, 0);
    h->AddSpacer(6);

    m_btnClose = WU::MakeButton(bar, "����", &ClientOrderManage::OnClose, this);
    h->Add(m_btnClose, 0, 0);

    root->Add(bar, 0, wxEXPAND | wxALL, 6);
}

/* ================= Tabs ================= */
void ClientOrderManage::BuildTabs(wxBoxSizer* root)
{
    m_book = new wxNotebook(m_panel, wxID_ANY);
    root->Add(m_book, 1, wxEXPAND | wxALL, 6);

    m_tabPeriod = new wxPanel(m_book, wxID_ANY);
    m_tabByClient = new wxPanel(m_book, wxID_ANY);

    m_book->AddPage(m_tabPeriod, "�Ⱓ ��ȸ", true);
    m_book->AddPage(m_tabByClient, "�ŷ�ó�� ��ȸ");

    BuildTab_Period(m_tabPeriod);
    BuildTab_ByClient(m_tabByClient);
}

/* ===== �Ⱓ ��ȸ �� ===== */
void ClientOrderManage::BuildTab_Period(wxPanel* tab)
{
    auto* v = new wxBoxSizer(wxVERTICAL);
    tab->SetSizer(v);

    BuildDateRangeBar(tab, (wxWindow*&)m_periodBar, m_dpStart, m_dpEnd, m_btnQuick, m_btnQuery, /*withLeftAllButton*/true, &m_btnAll);
    v->Add(m_periodBar, 0, wxEXPAND | wxALL, 4);

    // �÷� ���
    const wxArrayString headers{ "������","������","�ŷ�ó","��ǰ��","���ް���","����","�հ�","���" };
    const int32 CM_gridWid[8] = { 80,80,160,210,80,80,80,150 };

    m_gridPeriod = WU::MakeGrid(tab, headers, CM_gridWid, wxEVT_GRID_CELL_LEFT_DCLICK, &ClientOrderManage::OnGridDClick, this);
    v->Add(m_gridPeriod, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 4);

    // �̺�Ʈ
    if (m_btnAll)   m_btnAll->Bind(wxEVT_BUTTON, &ClientOrderManage::OnAll, this);
    if (m_btnQuick) m_btnQuick->Bind(wxEVT_BUTTON, &ClientOrderManage::OnQuickPeriod, this);
    if (m_btnQuery) m_btnQuery->Bind(wxEVT_BUTTON, &ClientOrderManage::OnQuery, this);
}

/* ===== �ŷ�ó�� ��ȸ �� ===== */
void ClientOrderManage::BuildTab_ByClient(wxPanel* tab)
{
    auto* v = new wxBoxSizer(wxVERTICAL);
    tab->SetSizer(v);

    BuildDateRangeBar(tab, (wxWindow*&)m_clientBar, m_dpCStart, m_dpCEnd, m_btnCQuick, m_btnCQuery);
    v->Add(m_clientBar, 0, wxEXPAND | wxALL, 4);

    // (�ʱ⿣ ���� ��� ���)
    const wxArrayString headers{ "������","������","�ŷ�ó","��ǰ","���ް���","����","�հ�","���" };
    m_gridClient = WU::MakeGrid(tab, headers, wid, wxEVT_GRID_CELL_LEFT_DCLICK, &ClientOrderManage::OnGridDClick,this);
    v->Add(m_gridClient, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 4);

    if (m_btnCQuick) m_btnCQuick->Bind(wxEVT_BUTTON, &ClientOrderManage::OnQuickPeriod, this);
    if (m_btnCQuery) m_btnCQuery->Bind(wxEVT_BUTTON, &ClientOrderManage::OnQuery, this);
}

/* ================= Helpers ================= */

void ClientOrderManage::AutoPadLastColumn(wxGrid* g, int extra)
{
    int last = g->GetNumberCols() - 1;
    if (last < 0) return;
    int cur = g->GetColSize(last);
    int vsw = wxSystemSettings::GetMetric(wxSYS_VSCROLL_X);
    g->SetColSize(last, cur + vsw + extra);
    g->FitInside();
}

void ClientOrderManage::InstallEscClose()
{
    wxAcceleratorEntry ae[1];
    ae[0].Set(wxACCEL_NORMAL, WXK_ESCAPE, wxID_CLOSE);
    SetAcceleratorTable(wxAcceleratorTable(1, ae));
    Bind(wxEVT_MENU, &ClientOrderManage::OnClose, this, wxID_CLOSE);
}

void ClientOrderManage::BuildDateRangeBar(wxWindow* parent,
    wxWindow*& outPanel,
    wxDatePickerCtrl*& outStart,
    wxDatePickerCtrl*& outEnd,
    wxButton*& outQuickBtn,
    wxButton*& outFindBtn,
    bool withLeftAllButton,
    wxButton** outAllBtn)
{
    auto* row = new wxPanel(parent, wxID_ANY);
    auto* h = new wxBoxSizer(wxHORIZONTAL);
    row->SetSizer(h);

    if (withLeftAllButton) {
        auto* btnAll = WU::MakeButton(row, "��ü", &ClientOrderManage::OnAll, this);
        h->Add(btnAll, 0, wxRIGHT, 6);
        if (outAllBtn) *outAllBtn = btnAll;
    }

    // ���: ��ȸ�Ⱓ [start] - [end] [�Ⱓ]
    h->AddStretchSpacer(1);

    auto* lb = new wxStaticText(row, wxID_ANY, "��ȸ�Ⱓ");
    h->Add(lb, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);

    outStart = new wxDatePickerCtrl(row, wxID_ANY);
    h->Add(outStart, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);

    h->Add(new wxStaticText(row, wxID_ANY, "-"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);

    outEnd = new wxDatePickerCtrl(row, wxID_ANY);
    h->Add(outEnd, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);

    outQuickBtn =WU::MakeButton(row, "�Ⱓ", &ClientOrderManage::OnQuickPeriod,this);
    h->Add(outQuickBtn, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);

    // ������: ��ȸ
    h->AddStretchSpacer(1);
    outFindBtn = WU::MakeButton(row, "��ȸ", &ClientOrderManage::OnQuery, this);
    h->Add(outFindBtn, 0, wxALIGN_CENTER_VERTICAL);

    outPanel = row;
}

/* ================= Events ================= */

void ClientOrderManage::OnPrint(wxCommandEvent&) 
{
    wxLogMessage("�μ�"); 
}
void ClientOrderManage::OnAdd(wxCommandEvent&) 
{
    G_Template->MakeSingletonOpener<ClientOrderInput>(this)();
}
void ClientOrderManage::OnEdit(wxCommandEvent&)
{
    wxLogMessage("����"); 
}
void ClientOrderManage::OnDelete(wxCommandEvent&) 
{
    wxLogMessage("����"); 
}
void ClientOrderManage::OnClose(wxCommandEvent&)
{
    Close();
}

void ClientOrderManage::OnAll(wxCommandEvent&)
{
    // TODO: ��ü��ȸ ���� �ʱ�ȭ
    wxLogMessage("��ü ��ȸ");
}

void ClientOrderManage::OnQuickPeriod(wxCommandEvent&)
{
    // ����: ������ = ����, ������ = 30�� ��
    wxDateTime today = wxDateTime::Today();
    wxDateTime start = today - wxDateSpan::Days(30);

    // ���� ���� ��Ʈ�ѿ� ���� ����
    if (m_book->GetCurrentPage() == m_tabPeriod) {
        m_dpStart->SetValue(start); m_dpEnd->SetValue(today);
    }
    else if (m_book->GetCurrentPage() == m_tabByClient) {
        m_dpCStart->SetValue(start); m_dpCEnd->SetValue(today);
    }
    else {
        m_dpKStart->SetValue(start); m_dpKEnd->SetValue(today);
    }
}

void ClientOrderManage::OnQuery(wxCommandEvent&)
{
    // ���� ���� �׸��忡 ���� ������ �� ��
    wxGrid* g = nullptr;
    if (m_book->GetCurrentPage() == m_tabPeriod)      g = m_gridPeriod;
    else if (m_book->GetCurrentPage() == m_tabByClient) g = m_gridClient;
    else                                               g = m_gridCond;

    if (!g) return;
    int r = g->GetNumberRows();
    g->AppendRows(1);
    g->SetCellValue(r, 0, "2025-08-01");
    g->SetCellValue(r, 1, "2025-08-22");
    g->SetCellValue(r, 2, "���ðŷ�ó");
    g->SetCellValue(r, 3, "���û�ǰ");
    g->SetCellValue(r, 4, "100,000");
    g->SetCellValue(r, 5, "10,000");
    g->SetCellValue(r, 6, "110,000");
    g->SetCellValue(r, 7, "��� �޸�");
    g->AutoSizeColumns();
    AutoPadLastColumn(g, 12);
}

void ClientOrderManage::OnGridDClick(wxGridEvent& e)
{
    const int r = e.GetRow();
    const int c = e.GetCol();
    wxLogMessage("����Ŭ��: row=%d col=%d", r, c);
    e.Skip();
}