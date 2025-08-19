#include "pch.h"
#include "InventoryAdd.h"

InventoryAdd::InventoryAdd()
	:wxFrame(nullptr, wxID_ANY, "����ڻ��߰�", wxDefaultPosition, wxSize(350, 320))
{
    ScreenInit();
	Center();
	Layout();
}

InventoryAdd::~InventoryAdd()
{
}

void InventoryAdd::ScreenInit()
{
    // �ֻ��� �����̳�
    m_panel = new wxPanel(this, wxID_ANY);
    m_panel->SetBackgroundColour(*wxWHITE);

    // ������ ��Ʈ ����
    frameSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(frameSizer);
    frameSizer->Add(m_panel, 1, wxEXPAND);

    // �г� ���� ��Ʈ
    auto* root = new wxBoxSizer(wxVERTICAL);
    m_panel->SetSizer(root);

    // ������������������������������������������������������������������������������������������
    // ��: 2��(��/����Ʈ), ���� �÷� Ȯ��
    // rows=0 �� �ʿ��� ��ŭ ��������
    auto* form = new wxFlexGridSizer(0, 2, 6, 10);
    form->AddGrowableCol(1, 1); // ����Ʈ/�޺� �ִ� 2��° �÷��� ���η� Ȯ��

    // �� �� ������ ���� ��� (�ʿ信 ���� ����)
    const int kLabelWidth = 110;

    // �� �ؽ�Ʈ�� (������ �� ���� �޺� �ڽ�)
    wxString LabelStr[8] = { "��ǰ��","��¥","����ȣ","�ŷ�ó","����","����","���з�","�����" };
    int size = sizeof(LabelStr) / sizeof(wxString);

    for (int i = 0; i < size; ++i)
    {
        // ��
        auto* lb = new wxStaticText(m_panel, wxID_ANY, LabelStr[i]);
        lb->SetMinSize(wxSize(kLabelWidth, -1));
        form->Add(lb, 0, wxALIGN_CENTER_VERTICAL);

        if (i == 6) {
            // 7��° ��: �޺��ڽ�
            wxArrayString choices;
            choices.Add("�԰�");
            choices.Add("���");
            auto* combo = new wxComboBox(m_panel, wxID_ANY, "",
                wxDefaultPosition, wxDefaultSize,
                choices, wxCB_READONLY);
            form->Add(combo, 1, wxEXPAND);
        }
        else {
            // ������ ��: ����Ʈ
            auto* edit = new wxTextCtrl(m_panel, wxID_ANY, "");
            form->Add(edit, 1, wxEXPAND | wxLEFT, 4);
        }
    }

    root->Add(form, 0, wxEXPAND | wxALL, 4);

    // ������������������������������������������������������������������������������������������
    // ��ư �� (������ ����)
    auto* btnBar = new wxBoxSizer(wxHORIZONTAL);
    auto* SaveBtn = new wxButton(m_panel, wxID_ANY, "�ҷ�����");
    auto* btnOK = new wxButton(m_panel, wxID_OK, "�߰�");
    auto* btnCancel = new wxButton(m_panel, wxID_CANCEL, "���");

    btnBar->Add(SaveBtn, 0, wxLEFT, 4);
    btnBar->AddStretchSpacer(1);
    btnBar->Add(btnOK, 0, wxRIGHT, 6);
    btnBar->Add(btnCancel, 0, wxRIGHT, 6);

    root->Add(btnBar, 0, wxEXPAND | wxTOP, 12);

    // ���̾ƿ� ������ + �߾� ��ġ(�θ� ������ �θ� ����)
    Layout();
    if (GetParent()) CentreOnParent();
    else             CentreOnScreen();
}
