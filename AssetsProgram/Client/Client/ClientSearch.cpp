#include "pch.h"
#include "ClientSearch.h"
#include "ClientQuickAdd.h"

wxBEGIN_EVENT_TABLE(ClientSearch, wxFrame)
EVT_BUTTON(wxID_ANY, ClientSearch::OnClickSearch) // 안전망(특정 id도 아래서 바인딩)
wxEND_EVENT_TABLE()

ClientSearch::ClientSearch(wxWindow* parent, wxString title, const wxSize size)
    : wxFrame(parent, wxID_ANY, title, wxDefaultPosition, size)
{
    // 메인 패널/루트
    SetSizeHints(600, 600, 600, 600);
    m_panel = new wxPanel(this, wxID_ANY);
    m_panel->SetBackgroundColour(wxColour(247, 249, 253));
    auto* frameSizer = new wxBoxSizer(wxVERTICAL);
    auto* root = new wxBoxSizer(wxVERTICAL);
    m_panel->SetSizer(root);

    BuildUI();

    frameSizer->Add(m_panel, 1, wxEXPAND);

    InstallEscToClose();
    CentreOnParent(); // 또는 CentreOnScreen()
}

void ClientSearch::BuildUI()
{
    auto* root = wxDynamicCast(m_panel->GetSizer(), wxBoxSizer);
    BuildTopBar(root);
    root->Add(new wxStaticLine(m_panel, wxID_ANY), 0, wxEXPAND);

    BuildSearchBar(root);
    root->AddSpacer(4);

    BuildNotebook(root);

    // 여백
    root->AddSpacer(6);
}

void ClientSearch::BuildTopBar(wxBoxSizer* root)
{
    auto* bar = new wxPanel(m_panel, wxID_ANY);
    auto* h = new wxBoxSizer(wxHORIZONTAL);
    bar->SetSizer(h);

    h->AddStretchSpacer(1);
    m_btnQuickAdd = WU::MakeButton(bar, "간편 추가", &ClientSearch::OnClickQuickAdd, this);
    m_btnClose = WU::MakeButton(bar, "닫기", &ClientSearch::OnClickClose,this);

    h->Add(m_btnQuickAdd, 0, wxRIGHT, 6);
    h->Add(m_btnClose, 0, wxRIGHT);
    
    root->Add(bar, 0, wxEXPAND | wxALL, 6);
}

void ClientSearch::BuildSearchBar(wxBoxSizer* root)
{
    auto* row = new wxPanel(m_panel, wxID_ANY);
    auto* h = new wxBoxSizer(wxHORIZONTAL);
    row->SetSizer(h);

    auto* lb = new wxStaticText(row, wxID_ANY, "검색");
    h->Add(lb, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);

    wxArrayString fields;
    fields.Add("회사명");
    fields.Add("대표자명");
    fields.Add("주민번호");
    fields.Add("주소");
    m_cbField = new wxChoice(row, wxID_ANY, wxDefaultPosition, wxSize(100, -1), fields);
    m_cbField->SetSelection(0);
    h->Add(m_cbField, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);

    m_edQuery = new wxTextCtrl(row, wxID_ANY, "", wxDefaultPosition, wxSize(260, -1));
    h->Add(m_edQuery, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);

    m_btnSearch = WU::MakeButton(row, "검색", &ClientSearch::OnClickSearch,this);
    h->Add(m_btnSearch, 0, wxALIGN_CENTER_VERTICAL);

    root->Add(row, 0, wxEXPAND | wxALL, 6);
}

void ClientSearch::BuildNotebook(wxBoxSizer* root)
{
    m_book = new wxNotebook(m_panel, wxID_ANY);
    root->Add(m_book, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);

    // 탭들
    m_tabCompany = new wxPanel(m_book, wxID_ANY);
    m_tabPerson = new wxPanel(m_book, wxID_ANY);

    m_book->AddPage(m_tabCompany, "회사", true);
    m_book->AddPage(m_tabPerson, "개인");

    // 공통 헤더
    const int32 wid[5] = { 80,140,100,80,100 };
    const wxArrayString headers = { "거래구분","회사명","사업자등록번호","대표자명","연락처" };
    
    // 각 탭의 그리드
    m_gridCompany = WU::MakeGrid(m_tabCompany, headers, wid,wxEVT_GRID_CELL_LEFT_DCLICK,&ClientSearch::OnGridDClick, this);
    m_gridPerson = WU::MakeGrid(m_tabPerson, headers, wid, wxEVT_GRID_CELL_LEFT_DCLICK,&ClientSearch::OnGridDClick, this);

    // 레이아웃
    for (wxPanel* p : { m_tabCompany, m_tabPerson }) {
        auto* v = new wxBoxSizer(wxVERTICAL);
        p->SetSizer(v);
        // 테두리 박스 느낌을 주고 싶으면 StaticBoxSizer 사용가능
        v->Add(m_gridCompany && p == m_tabCompany ? m_gridCompany :
            m_gridPerson,
            1, wxEXPAND | wxALL, 6);
    }
}

void ClientSearch::AutoPadLastColumn(wxGrid* grid, int extra)
{
    int last = grid->GetNumberCols() - 1;
    if (last < 0) return;
    int curW = grid->GetColSize(last);
    int vscrollW = wxSystemSettings::GetMetric(wxSYS_VSCROLL_X);
    grid->SetColSize(last, curW + vscrollW + extra);
    grid->FitInside();
}

void ClientSearch::InstallEscToClose()
{
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_NORMAL, WXK_ESCAPE, wxID_CLOSE);
    SetAcceleratorTable(wxAcceleratorTable(1, entries));
    Bind(wxEVT_MENU, &ClientSearch::OnClickClose, this, wxID_CLOSE);
}

// ===== 이벤트 =====
void ClientSearch::OnClickQuickAdd(wxCommandEvent&)
{
    G_Template->MakeSingletonOpener<ClientQuickAdd>(this)();
}

void ClientSearch::OnClickClose(wxCommandEvent&)
{
    Close(); // Close()가 wxEVT_CLOSE_WINDOW 트리거
}

void ClientSearch::OnClickSearch(wxCommandEvent&)
{
    const int field = m_cbField ? m_cbField->GetSelection() : 0;
    const wxString q = m_edQuery ? m_edQuery->GetValue() : wxString();
    wxLogMessage("검색: field=%d, query=%s", field, q);

    // TODO: 실제 검색 → 활성 탭의 그리드에 결과 채우기
    wxGrid* g = nullptr;
    switch (m_book->GetSelection()) {
    case 0: g = m_gridCompany; break;
    case 1: g = m_gridPerson;  break;
    }
    if (!g) return;

    // 예시 데이터 한 줄
    if (g->GetNumberRows() == 0) g->AppendRows(1);
    g->SetCellValue(0, 0, "홍길동");
    g->SetCellValue(0, 1, "길동상사");
    g->SetCellValue(0, 2, "900101-1******");
    g->SetCellValue(0, 3, "사원");
    g->SetCellValue(0, 4, "서울시 어딘가");
    g->AutoSizeColumns();
    AutoPadLastColumn(g, 12);
}

void ClientSearch::OnGridDClick(wxGridEvent& e)
{
    const int r = e.GetRow();
    const int c = e.GetCol();
    wxLogMessage("더블클릭: row=%d col=%d", r, c);
    e.Skip();
}