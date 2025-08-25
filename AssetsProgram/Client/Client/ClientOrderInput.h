#pragma once

class ClientOrderInput : public wxFrame
{
public:
    explicit ClientOrderInput(wxWindow* parent = nullptr,
        const wxString& title = "���ּ��Է�",
        const wxSize& size = wxSize(850, 700));
    ~ClientOrderInput() override = default;

private:
    // ===== UI ���� =====
    void BuildUI();
    void BuildTopBar(wxBoxSizer* root);       // ��� ����/����
    void BuildHeader(wxBoxSizer* root);       // ��/�� �⺻����
    void BuildOrderMeta(wxBoxSizer* root);    // ������/������/�޸�
    void BuildItems(wxBoxSizer* root);        // ǰ�� ���� + �׸���
    void BuildTotals(wxBoxSizer* root);       // ���ް���/����/�հ�ݾ�
    void BuildBottomMemo(wxBoxSizer* root);   // �޸� 1~4

    // ===== ���� ����(�� ���ؽ�Ʈ) =====
    void BeginForm(wxPanel* panel, wxBoxSizer* fields,
        int labelWidth = 78, int rowVPad = 4, int labelGap = 6);
    void EndForm();

    void AddRow(const wxString& label, wxWindow* editor, int proportion = 1);
    wxTextCtrl* AddEditRow(const wxString& label, const wxString& hint = wxEmptyString,
        bool multiline = false, long extraStyle = 0);
    wxChoice* AddChoiceRow(const wxString& label, const wxArrayString& choices, int sel = 0);
    wxSearchCtrl* AddSearchRow(const wxString& label, const wxString& hint = wxEmptyString);

    void         InstallEscClose();

    // ===== �̺�Ʈ =====
    void OnSave(wxCommandEvent&);
    void OnClose(wxCommandEvent&);
    void OnAddClient(wxCommandEvent&);
    void OnFindClient(wxCommandEvent&);
    void OnAddItem(wxCommandEvent&);
    void OnDeleteSelected(wxCommandEvent&);

    void OnGridClick(wxGridEvent& e);

private:
    // �����̳�
    wxPanel* m_panel{ nullptr };

    // ��� ��ư
    wxButton* m_btnSave{ nullptr };
    wxButton* m_btnClose{ nullptr };

    // ����(����/���� �ȳ�)
    wxSearchCtrl* m_rcvSearch{ nullptr };
    wxButton* m_btnAddClient{ nullptr };
    wxTextCtrl* m_edRef{ nullptr };
    wxTextCtrl* m_edContact{ nullptr };
    wxTextCtrl* m_edPayTerm{ nullptr };

    // ����(�ŷ�ó ����)
    wxTextCtrl* m_edRegNo{ nullptr };
    wxTextCtrl* m_edCEO{ nullptr };
    wxTextCtrl* m_edCompany{ nullptr };
    wxChoice* m_chDept{ nullptr };
    wxChoice* m_chPerson{ nullptr };
    wxTextCtrl* m_edPhone{ nullptr };
    wxTextCtrl* m_edEmail{ nullptr };

    // ���� ��Ÿ
    wxDatePickerCtrl* m_dpOrderDate{ nullptr };
    wxDatePickerCtrl* m_dpDueDate{ nullptr };
    wxTextCtrl* m_edMemoTop{ nullptr };

    // ǰ��
    wxButton* m_btnPickItem{ nullptr };
    wxButton* m_btnDelSel{ nullptr };
    wxGrid* m_gridItems{ nullptr };

    // �հ�
    wxTextCtrl* m_edSubtotal{ nullptr };
    wxTextCtrl* m_edVat{ nullptr };
    wxTextCtrl* m_edTotal{ nullptr };

    // �ϴ� �޸�
    wxTextCtrl* m_edMemo1{ nullptr };
    wxTextCtrl* m_edMemo2{ nullptr };
    wxTextCtrl* m_edMemo3{ nullptr };
    wxTextCtrl* m_edMemo4{ nullptr };

    // �� ���ؽ�Ʈ
    wxPanel* m_formPanel{ nullptr };
    wxBoxSizer* m_formFields{ nullptr };
    int         m_labelW{ 78 };
    int         m_rowVPad{ 4 };
    int         m_labelGap{ 6 };
};