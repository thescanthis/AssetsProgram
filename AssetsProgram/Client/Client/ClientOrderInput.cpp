#include "pch.h"
#include "ClientOrderInput.h"
#include "ClientSearch.h"

ClientOrderInput::ClientOrderInput(wxWindow* parent,
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

void ClientOrderInput::BuildUI()
{
    auto* root = wxDynamicCast(m_panel->GetSizer(), wxBoxSizer);

    BuildTopBar(root);
    root->Add(new wxStaticLine(m_panel, wxID_ANY), 0, wxEXPAND);

    BuildHeader(root);
    root->AddSpacer(4);

    BuildOrderMeta(root);
    root->AddSpacer(2);

    BuildItems(root);
    BuildTotals(root);
    BuildBottomMemo(root);

    root->AddSpacer(4);
}

/* ---------- 상단 버튼바 ---------- */
void ClientOrderInput::BuildTopBar(wxBoxSizer* root)
{
    auto* bar = new wxPanel(m_panel, wxID_ANY);
    auto* h = new wxBoxSizer(wxHORIZONTAL);
    bar->SetSizer(h);

    h->AddStretchSpacer(1);
    m_btnSave = MakeButton(bar, "저장", wxCommandEventHandler(ClientOrderInput::OnSave));
    h->AddSpacer(4);
    m_btnClose = MakeButton(bar, "종료", wxCommandEventHandler(ClientOrderInput::OnClose));

    root->Add(bar, 0, wxEXPAND | wxALL, 6);
}

/* ---------- 좌/우 기본정보 영역 ---------- */
void ClientOrderInput::BuildHeader(wxBoxSizer* root)
{
    auto* box = new wxStaticBox(m_panel, wxID_ANY, "");
    auto* sb = new wxStaticBoxSizer(box, wxHORIZONTAL);
    root->Add(sb, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 6);

    /* Left panel */
    auto* left = new wxPanel(box, wxID_ANY);
    auto* lv = new wxBoxSizer(wxVERTICAL);
    left->SetSizer(lv);

    // 수신 + 검색
    {
        auto* row = new wxBoxSizer(wxHORIZONTAL);
        auto* lb = new wxStaticText(left, wxID_ANY, "수신");
        row->Add(lb, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);

        m_rcvSearch = new wxSearchCtrl(left, wxID_ANY, "",
            wxDefaultPosition, FromDIP(wxSize(260, -1), this));
#if wxCHECK_VERSION(3,1,0)
        m_rcvSearch->ShowSearchButton(true);
#endif
        row->Add(m_rcvSearch, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);

        m_btnAddClient = MakeButton(left, "선택", wxCommandEventHandler(ClientOrderInput::OnAddClient));
        row->Add(m_btnAddClient, 0);

        lv->Add(row, 0, wxEXPAND | wxBOTTOM, 4);
    }

    // "다음과 같이 발주합니다." 및 필드
    {
        auto* msg = new wxStaticText(left, wxID_ANY, "다음과 같이 발주합니다.");
        lv->Add(msg, 0, wxBOTTOM, 2);

        auto* fields = new wxBoxSizer(wxVERTICAL);
        lv->Add(fields, 0, wxEXPAND);

        BeginForm(left, fields, FromDIP(wxSize(72, -1), this).GetWidth());

        m_edRef = AddEditRow("참조");
        m_edContact = AddEditRow("연락처");
        m_edPayTerm = AddEditRow("결제조건");

        EndForm();
    }

    /* Right panel */
    auto* right = new wxPanel(box, wxID_ANY);
    auto* rv = new wxBoxSizer(wxVERTICAL);
    right->SetSizer(rv);

    {
        auto* fields = new wxBoxSizer(wxVERTICAL);
        rv->Add(fields, 1, wxEXPAND);

        BeginForm(right, fields, FromDIP(wxSize(70, -1), this).GetWidth());

        m_edRegNo = AddEditRow("등록번호");
        m_edCEO = AddEditRow("대표");
        m_edCompany = AddEditRow("상 호");

        m_edPhone = AddEditRow("전화번호");
        m_edEmail = AddEditRow("이메일");

        EndForm();
    }

    // 좌/우 추가
    sb->Add(left, 1, wxEXPAND | wxALL, 6);
    sb->Add(new wxStaticLine(box, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL),
        0, wxEXPAND | wxTOP | wxBOTTOM, 6);
    sb->Add(right, 1, wxEXPAND | wxALL, 6);
}

/* ---------- 발주일/납기일/메모 ---------- */
void ClientOrderInput::BuildOrderMeta(wxBoxSizer* root)
{
    auto* row = new wxPanel(m_panel, wxID_ANY);
    auto* h = new wxBoxSizer(wxHORIZONTAL);
    row->SetSizer(h);

    // 발주일
    h->Add(new wxStaticText(row, wxID_ANY, "발행일"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    m_dpOrderDate = new wxDatePickerCtrl(row, wxID_ANY);
    h->Add(m_dpOrderDate, 0, wxRIGHT, 10);

    // 납기일
    h->Add(new wxStaticText(row, wxID_ANY, "납기일"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    m_dpDueDate = new wxDatePickerCtrl(row, wxID_ANY);
    h->Add(m_dpDueDate, 0, wxRIGHT, 10);

    // 메모
    h->Add(new wxStaticText(row, wxID_ANY, "메모"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    m_edMemoTop = new wxTextCtrl(row, wxID_ANY, "", wxDefaultPosition,
        FromDIP(wxSize(260, -1), this));
    h->Add(m_edMemoTop, 1, wxALIGN_CENTER_VERTICAL);

    root->Add(row, 0, wxEXPAND | wxLEFT | wxRIGHT, 6);
}

/* ---------- 품목 툴바 + 그리드 ---------- */
void ClientOrderInput::BuildItems(wxBoxSizer* root)
{
    // 툴바
    auto* bar = new wxPanel(m_panel, wxID_ANY);
    auto* h = new wxBoxSizer(wxHORIZONTAL);
    bar->SetSizer(h);

    m_btnPickItem = MakeButton(bar, "상품추가", wxCommandEventHandler(ClientOrderInput::OnAddItem));
    m_btnDelSel = MakeButton(bar, "선택삭제", wxCommandEventHandler(ClientOrderInput::OnDeleteSelected));

    h->Add(m_btnPickItem, 0, 0);
    h->Add(m_btnDelSel, 0, 0);
    h->AddStretchSpacer(1);
    root->Add(bar, 0, wxEXPAND | wxALL, 6);

    const wxArrayString headers={"상품코드","상품명","수량","단위","단가","공급가액","세액","합계","비고"};

    // 그리드
    m_gridItems = WU::MakeGrid(m_panel, headers,wid, wxEVT_GRID_CELL_LEFT_CLICK,&ClientOrderInput::OnGridClick,this);
    root->Add(m_gridItems, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);
}

/* ---------- 합계/세액 ---------- */
void ClientOrderInput::BuildTotals(wxBoxSizer* root)
{
    auto* box = new wxStaticBox(m_panel, wxID_ANY, "총 합계금액.");
    auto* sb = new wxStaticBoxSizer(box, wxHORIZONTAL);
    root->Add(sb, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);

    sb->AddStretchSpacer(1);

    auto addAmt = [&](const wxString& label, wxTextCtrl*& out) {
        sb->Add(new wxStaticText(box, wxID_ANY, label), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
        out = new wxTextCtrl(box, wxID_ANY, "", wxDefaultPosition, FromDIP(wxSize(120, -1), this),
            wxTE_RIGHT | wxBORDER_SIMPLE);
        out->Enable(false);
        sb->Add(out, 0, wxRIGHT, 8);
        };

    addAmt("공급가액", m_edSubtotal);
    addAmt("세액", m_edVat);
    addAmt("합계금액", m_edTotal);
}

/* ---------- 하단 메모 ---------- */
void ClientOrderInput::BuildBottomMemo(wxBoxSizer* root)
{
    auto* box = new wxStaticBox(m_panel, wxID_ANY, "");
    auto* sb = new wxStaticBoxSizer(box, wxVERTICAL);
    root->Add(sb, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);

    auto* p = new wxPanel(box, wxID_ANY);
    auto* v = new wxBoxSizer(wxVERTICAL);
    p->SetSizer(v);
    sb->Add(p, 1, wxEXPAND | wxALL, 8);

    auto addLine = [&](int idx, wxTextCtrl*& out) {
        auto* h = new wxBoxSizer(wxHORIZONTAL);
        h->Add(new wxStaticText(p, wxID_ANY, wxString::Format("%d.", idx)),
            0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);
        out = new wxTextCtrl(p, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
        h->Add(out, 1, wxEXPAND);
        v->Add(h, 0, wxEXPAND | wxBOTTOM, 4);
        };

    // "메모" 라벨 + 첫 줄은 별도
    {
        auto* h = new wxBoxSizer(wxHORIZONTAL);
        h->Add(new wxStaticText(p, wxID_ANY, "추가메모"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);
        v->Add(h, 0, wxEXPAND | wxBOTTOM, 4);
    }
    addLine(1, m_edMemo1);
    addLine(2, m_edMemo2);
    addLine(3, m_edMemo3);
    addLine(4, m_edMemo4);
}

/* ---------- Helpers ---------- */
void ClientOrderInput::BeginForm(wxPanel* panel, wxBoxSizer* fields,
    int labelWidth, int rowVPad, int labelGap)
{
    m_formPanel = panel;
    m_formFields = fields;
    m_labelW = labelWidth;
    m_rowVPad = rowVPad;
    m_labelGap = labelGap;
}
void ClientOrderInput::EndForm()
{
    m_formPanel = nullptr; m_formFields = nullptr;
}

void ClientOrderInput::AddRow(const wxString& label, wxWindow* editor, int proportion)
{
    wxASSERT_MSG(m_formPanel && m_formFields, "BeginForm() 먼저 호출하세요");
    auto* row = new wxBoxSizer(wxHORIZONTAL);
    auto* lb = new wxStaticText(m_formPanel, wxID_ANY, label);
    lb->SetMinSize(wxSize(m_labelW, -1));
    row->Add(lb, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, m_labelGap);
    row->Add(editor, proportion, wxEXPAND);
    m_formFields->Add(row, 0, wxEXPAND | wxTOP | wxBOTTOM, m_rowVPad);
}

wxTextCtrl* ClientOrderInput::AddEditRow(const wxString& label, const wxString& hint,
    bool multiline, long extraStyle)
{
    long style = wxBORDER_SIMPLE | extraStyle | (multiline ? wxTE_MULTILINE : 0);
    auto* ed = new wxTextCtrl(m_formPanel, wxID_ANY, "", wxDefaultPosition,
        multiline ? FromDIP(wxSize(-1, 56), this) : wxDefaultSize, style);
    if (!hint.empty()) ed->SetHint(hint);
    AddRow(label, ed, 1);
    return ed;
}

wxChoice* ClientOrderInput::AddChoiceRow(const wxString& label,
    const wxArrayString& choices, int sel)
{
    auto* ch = new wxChoice(m_formPanel, wxID_ANY, wxDefaultPosition,
        FromDIP(wxSize(120, -1), this), choices);
    if (sel >= 0 && sel < (int)choices.size()) ch->SetSelection(sel);
    AddRow(label, ch, 0);
    return ch;
}

wxSearchCtrl* ClientOrderInput::AddSearchRow(const wxString& label, const wxString& hint)
{
    auto* sc = new wxSearchCtrl(m_formPanel, wxID_ANY, "", wxDefaultPosition,
        FromDIP(wxSize(260, -1), this));
#if wxCHECK_VERSION(3,1,0)
    sc->ShowSearchButton(true);
#endif
    if (!hint.empty()) sc->SetHint(hint);
    AddRow(label, sc, 1);
    return sc;
}

wxButton* ClientOrderInput::MakeButton(wxWindow* parent, const wxString& text,
    wxObjectEventFunction handler, long style)
{
    auto* b = new wxButton(parent, wxID_ANY, text, wxDefaultPosition, wxDefaultSize, style);
    if (handler) b->Bind(wxEVT_BUTTON, handler, this);
    return b; // Add는 호출부에서
}

void ClientOrderInput::InstallEscClose()
{
    wxAcceleratorEntry e[1];
    e[0].Set(wxACCEL_NORMAL, WXK_ESCAPE, wxID_CLOSE);
    SetAcceleratorTable(wxAcceleratorTable(1, e));
    Bind(wxEVT_MENU, &ClientOrderInput::OnClose, this, wxID_CLOSE);
}

/* ---------- 이벤트 ---------- */
void ClientOrderInput::OnSave(wxCommandEvent&)
{
    // TODO: 유효성 검사/계산/저장
    wxMessageBox("저장되었습니다.", "알림", wxOK | wxICON_INFORMATION, this);
}
void ClientOrderInput::OnClose(wxCommandEvent&)
{
    Close();
}
void ClientOrderInput::OnAddClient(wxCommandEvent&)
{
    G_Template->MakeSingletonOpener<ClientSearch>(this)();
}
void ClientOrderInput::OnFindClient(wxCommandEvent&)
{
    // m_rcvSearch 사용
}
void ClientOrderInput::OnAddItem(wxCommandEvent&)
{
    int r = m_gridItems->GetNumberRows();
    m_gridItems->AppendRows(1);
    m_gridItems->SetCellValue(r, 0, wxString::Format("P%04d", r + 1));
}
void ClientOrderInput::OnDeleteSelected(wxCommandEvent&)
{
    auto sel = m_gridItems->GetSelectedRows();
    if (sel.IsEmpty()) return;
    // 뒤에서부터 지워야 index 안전
    for (int i = sel.GetCount() - 1; i >= 0; --i)
        m_gridItems->DeleteRows(sel[i], 1);
}

void ClientOrderInput::OnGridClick(wxGridEvent& e)
{
    const int r = e.GetRow();
    const int c = e.GetCol();
    wxLogMessage("클릭: row=%d col=%d", r, c);
    e.Skip();
}