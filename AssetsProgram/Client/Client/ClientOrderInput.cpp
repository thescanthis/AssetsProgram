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

/* ---------- ��� ��ư�� ---------- */
void ClientOrderInput::BuildTopBar(wxBoxSizer* root)
{
    auto* bar = new wxPanel(m_panel, wxID_ANY);
    auto* h = new wxBoxSizer(wxHORIZONTAL);
    bar->SetSizer(h);

    h->AddStretchSpacer(1);
    m_btnSave = MakeButton(bar, "����", wxCommandEventHandler(ClientOrderInput::OnSave));
    h->AddSpacer(4);
    m_btnClose = MakeButton(bar, "����", wxCommandEventHandler(ClientOrderInput::OnClose));

    root->Add(bar, 0, wxEXPAND | wxALL, 6);
}

/* ---------- ��/�� �⺻���� ���� ---------- */
void ClientOrderInput::BuildHeader(wxBoxSizer* root)
{
    auto* box = new wxStaticBox(m_panel, wxID_ANY, "");
    auto* sb = new wxStaticBoxSizer(box, wxHORIZONTAL);
    root->Add(sb, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 6);

    /* Left panel */
    auto* left = new wxPanel(box, wxID_ANY);
    auto* lv = new wxBoxSizer(wxVERTICAL);
    left->SetSizer(lv);

    // ���� + �˻�
    {
        auto* row = new wxBoxSizer(wxHORIZONTAL);
        auto* lb = new wxStaticText(left, wxID_ANY, "����");
        row->Add(lb, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);

        m_rcvSearch = new wxSearchCtrl(left, wxID_ANY, "",
            wxDefaultPosition, FromDIP(wxSize(260, -1), this));
#if wxCHECK_VERSION(3,1,0)
        m_rcvSearch->ShowSearchButton(true);
#endif
        row->Add(m_rcvSearch, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);

        m_btnAddClient = MakeButton(left, "����", wxCommandEventHandler(ClientOrderInput::OnAddClient));
        row->Add(m_btnAddClient, 0);

        lv->Add(row, 0, wxEXPAND | wxBOTTOM, 4);
    }

    // "������ ���� �����մϴ�." �� �ʵ�
    {
        auto* msg = new wxStaticText(left, wxID_ANY, "������ ���� �����մϴ�.");
        lv->Add(msg, 0, wxBOTTOM, 2);

        auto* fields = new wxBoxSizer(wxVERTICAL);
        lv->Add(fields, 0, wxEXPAND);

        BeginForm(left, fields, FromDIP(wxSize(72, -1), this).GetWidth());

        m_edRef = AddEditRow("����");
        m_edContact = AddEditRow("����ó");
        m_edPayTerm = AddEditRow("��������");

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

        m_edRegNo = AddEditRow("��Ϲ�ȣ");
        m_edCEO = AddEditRow("��ǥ");
        m_edCompany = AddEditRow("�� ȣ");

        m_edPhone = AddEditRow("��ȭ��ȣ");
        m_edEmail = AddEditRow("�̸���");

        EndForm();
    }

    // ��/�� �߰�
    sb->Add(left, 1, wxEXPAND | wxALL, 6);
    sb->Add(new wxStaticLine(box, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL),
        0, wxEXPAND | wxTOP | wxBOTTOM, 6);
    sb->Add(right, 1, wxEXPAND | wxALL, 6);
}

/* ---------- ������/������/�޸� ---------- */
void ClientOrderInput::BuildOrderMeta(wxBoxSizer* root)
{
    auto* row = new wxPanel(m_panel, wxID_ANY);
    auto* h = new wxBoxSizer(wxHORIZONTAL);
    row->SetSizer(h);

    // ������
    h->Add(new wxStaticText(row, wxID_ANY, "������"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    m_dpOrderDate = new wxDatePickerCtrl(row, wxID_ANY);
    h->Add(m_dpOrderDate, 0, wxRIGHT, 10);

    // ������
    h->Add(new wxStaticText(row, wxID_ANY, "������"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    m_dpDueDate = new wxDatePickerCtrl(row, wxID_ANY);
    h->Add(m_dpDueDate, 0, wxRIGHT, 10);

    // �޸�
    h->Add(new wxStaticText(row, wxID_ANY, "�޸�"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    m_edMemoTop = new wxTextCtrl(row, wxID_ANY, "", wxDefaultPosition,
        FromDIP(wxSize(260, -1), this));
    h->Add(m_edMemoTop, 1, wxALIGN_CENTER_VERTICAL);

    root->Add(row, 0, wxEXPAND | wxLEFT | wxRIGHT, 6);
}

/* ---------- ǰ�� ���� + �׸��� ---------- */
void ClientOrderInput::BuildItems(wxBoxSizer* root)
{
    // ����
    auto* bar = new wxPanel(m_panel, wxID_ANY);
    auto* h = new wxBoxSizer(wxHORIZONTAL);
    bar->SetSizer(h);

    m_btnPickItem = MakeButton(bar, "��ǰ�߰�", wxCommandEventHandler(ClientOrderInput::OnAddItem));
    m_btnDelSel = MakeButton(bar, "���û���", wxCommandEventHandler(ClientOrderInput::OnDeleteSelected));

    h->Add(m_btnPickItem, 0, 0);
    h->Add(m_btnDelSel, 0, 0);
    h->AddStretchSpacer(1);
    root->Add(bar, 0, wxEXPAND | wxALL, 6);

    const wxArrayString headers={"��ǰ�ڵ�","��ǰ��","����","����","�ܰ�","���ް���","����","�հ�","���"};

    // �׸���
    m_gridItems = WU::MakeGrid(m_panel, headers,wid, wxEVT_GRID_CELL_LEFT_CLICK,&ClientOrderInput::OnGridClick,this);
    root->Add(m_gridItems, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);
}

/* ---------- �հ�/���� ---------- */
void ClientOrderInput::BuildTotals(wxBoxSizer* root)
{
    auto* box = new wxStaticBox(m_panel, wxID_ANY, "�� �հ�ݾ�.");
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

    addAmt("���ް���", m_edSubtotal);
    addAmt("����", m_edVat);
    addAmt("�հ�ݾ�", m_edTotal);
}

/* ---------- �ϴ� �޸� ---------- */
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

    // "�޸�" �� + ù ���� ����
    {
        auto* h = new wxBoxSizer(wxHORIZONTAL);
        h->Add(new wxStaticText(p, wxID_ANY, "�߰��޸�"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);
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
    wxASSERT_MSG(m_formPanel && m_formFields, "BeginForm() ���� ȣ���ϼ���");
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
    return b; // Add�� ȣ��ο���
}

void ClientOrderInput::InstallEscClose()
{
    wxAcceleratorEntry e[1];
    e[0].Set(wxACCEL_NORMAL, WXK_ESCAPE, wxID_CLOSE);
    SetAcceleratorTable(wxAcceleratorTable(1, e));
    Bind(wxEVT_MENU, &ClientOrderInput::OnClose, this, wxID_CLOSE);
}

/* ---------- �̺�Ʈ ---------- */
void ClientOrderInput::OnSave(wxCommandEvent&)
{
    // TODO: ��ȿ�� �˻�/���/����
    wxMessageBox("����Ǿ����ϴ�.", "�˸�", wxOK | wxICON_INFORMATION, this);
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
    // m_rcvSearch ���
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
    // �ڿ������� ������ index ����
    for (int i = sel.GetCount() - 1; i >= 0; --i)
        m_gridItems->DeleteRows(sel[i], 1);
}

void ClientOrderInput::OnGridClick(wxGridEvent& e)
{
    const int r = e.GetRow();
    const int c = e.GetCol();
    wxLogMessage("Ŭ��: row=%d col=%d", r, c);
    e.Skip();
}