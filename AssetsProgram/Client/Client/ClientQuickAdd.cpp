#include "pch.h"
#include "ClientQuickAdd.h"

ClientQuickAdd::ClientQuickAdd(wxWindow* parent,
    const wxString& title,
    const wxSize& size)
    : wxFrame(parent, wxID_ANY, title,
        wxDefaultPosition, size,
        wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
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
}

void ClientQuickAdd::BuildUI()
{
    auto* root = wxDynamicCast(m_panel->GetSizer(), wxBoxSizer);

    BuildTopBar(root);
    root->AddSpacer(2);

    BuildForm(root);
    root->AddSpacer(4);
}

void ClientQuickAdd::BuildTopBar(wxBoxSizer* root)
{
    auto* bar = new wxPanel(m_panel, wxID_ANY);
    auto* h = new wxBoxSizer(wxHORIZONTAL);
    bar->SetSizer(h);
    // ���� ��ư (���ϴ� ����)
    h->AddStretchSpacer(1);

    m_btnSave = new wxButton(bar, wxID_SAVE, "����");
    m_btnClose = new wxButton(bar, wxID_CANCEL, "����");
    h->Add(m_btnSave, 0, wxRIGHT, 4);
    h->Add(m_btnClose, 0, wxRIGHT, 4);
    m_btnSave->Bind(wxEVT_BUTTON, &ClientQuickAdd::OnSave, this);
    m_btnClose->Bind(wxEVT_BUTTON, &ClientQuickAdd::OnClose, this);

    root->Add(bar, 0, wxEXPAND | wxALL, 6);
}

void ClientQuickAdd::BuildForm(wxBoxSizer* root)
{
    // ��� ���� ����
    auto* box = new wxStaticBox(m_panel, wxID_ANY, "");
    auto* sb = new wxStaticBoxSizer(box, wxVERTICAL);
    root->Add(sb, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);

    // �� �����̳�
    auto* right = new wxPanel(box, wxID_ANY);
    auto* v = new wxBoxSizer(wxVERTICAL);
    right->SetSizer(v);
    sb->Add(right, 1, wxEXPAND | wxALL, 8);

    // ��� "�˻��� ���"�� ���� ���� ��ġ
    // �ʵ� ����
    auto* fields = new wxBoxSizer(wxVERTICAL);
    v->Add(fields, 1, wxEXPAND);

    BeginForm(right, fields, /*labelW*/ FromDIP(wxSize(86, -1), this).GetWidth());

    // 1) �ŷ�ó���� (ȸ��/����)
    {
        wxArrayString choices; choices.Add("ȸ��"); choices.Add("����");
        m_cbClientKind = AddChoiceRow("�ŷ�ó����", choices, 0);
    }
    // 2) �ŷ����� (����/����)
    {
        wxArrayString choices; choices.Add("����"); choices.Add("����"); choices.Add("ȥ��");
        m_cbTradeKind = AddChoiceRow("�ŷ�����", choices, 0);
    }
    // 3) ȸ���
    m_edCompany = AddEditRow("ȸ���");

    // 4~8) ������ �ʵ�
    m_edBizNo = AddEditRow("����ڹ�ȣ", "_ _ _ - _ _ - _ _ _ _ _");   // ��Ʈ
    m_edCeo = AddEditRow("��ǥ�ڸ�");
    m_edAddr = AddEditRow("������ּ�");
    m_edPhone = AddEditRow("��ȭ��ȣ");
    m_edEmail = AddEditRow("�̸���");
    m_edMemo = AddEditRow("�޸�", "", /*multiline*/true);

    wxSize size = m_edMemo->GetSize();
    m_edMemo->SetSize({ size.GetWidth(),size.GetHeight() + 100 });

    EndForm();
}

// ========== Helpers ==========
void ClientQuickAdd::BeginForm(wxPanel* panel, wxBoxSizer* fields,
    int labelWidth, int rowVPad, int labelGap)
{
    m_formPanel = panel;
    m_formFields = fields;
    m_labelW = labelWidth;
    m_rowVPad = rowVPad;
    m_labelGap = labelGap;
}

void ClientQuickAdd::EndForm()
{
    m_formPanel = nullptr;
    m_formFields = nullptr;
}

void ClientQuickAdd::AddRow(const wxString& label, wxWindow* editor, int proportion)
{
    wxASSERT_MSG(m_formPanel && m_formFields, "BeginForm() ���� ȣ���ϼ���");

    auto* s = new wxBoxSizer(wxHORIZONTAL);

    auto* lb = new wxStaticText(m_formPanel, wxID_ANY, label);
    lb->SetMinSize(wxSize(m_labelW, -1));
    s->Add(lb, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, m_labelGap);

    s->Add(editor, proportion, wxEXPAND);
    m_formFields->Add(s, 0, wxTOP | wxBOTTOM | wxEXPAND, m_rowVPad);
}

wxChoice* ClientQuickAdd::AddChoiceRow(const wxString& label,
    const wxArrayString& choices, int sel)
{
    auto* ch = new wxChoice(m_formPanel, wxID_ANY, wxDefaultPosition,
        FromDIP(wxSize(120, -1), this), choices);
    if (sel >= 0 && sel < (int)choices.size()) ch->SetSelection(sel);
    AddRow(label, ch, 0);
    return ch;
}

wxTextCtrl* ClientQuickAdd::AddEditRow(const wxString& label,
    const wxString& hint,
    bool multiline,
    bool enable,
    long extraStyle)
{
    long style = wxBORDER_SIMPLE | extraStyle | (multiline ? wxTE_MULTILINE : 0);
    auto* ed = new wxTextCtrl(m_formPanel, wxID_ANY, "", wxDefaultPosition,
        multiline ? FromDIP(wxSize(-1, 64), this) : wxDefaultSize,
        style);
    if (!hint.empty()) ed->SetHint(hint);
    ed->Enable(enable);
    ed->SetBackgroundColour(*wxWHITE);
    ed->SetForegroundColour(wxColour(50, 50, 50));

    AddRow(label, ed, 1);
    return ed;
}

void ClientQuickAdd::InstallEscClose()
{
    wxAcceleratorEntry e[1];
    e[0].Set(wxACCEL_NORMAL, WXK_ESCAPE, wxID_CLOSE);
    SetAcceleratorTable(wxAcceleratorTable(1, e));
    Bind(wxEVT_MENU, &ClientQuickAdd::OnClose, this, wxID_CLOSE);
}

// ========== Events ==========
void ClientQuickAdd::OnSave(wxCommandEvent&)
{
    // TODO: ���� & ���� ����
    // ��) �ʼ��� üũ
    if (m_edCompany && m_edCompany->GetValue().IsEmpty()) {
        wxMessageBox("ȸ����� �Է��ϼ���.", "�˸�", wxOK | wxICON_INFORMATION, this);
        m_edCompany->SetFocus();
        return;
    }
    // ���� ���� ���� ���ԡ�
    wxMessageBox("����Ǿ����ϴ�.", "�˸�", wxOK | wxICON_INFORMATION, this);
}

void ClientQuickAdd::OnClose(wxCommandEvent&)
{
    Close(); // wxEVT_CLOSE_WINDOW �߻�
}