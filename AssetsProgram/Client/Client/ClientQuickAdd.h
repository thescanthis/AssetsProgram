#pragma once

class ClientQuickAdd : public wxFrame
{
public:
    explicit ClientQuickAdd(wxWindow* parent = nullptr,
        const wxString& title = "간편 추가",
        const wxSize& size = wxSize(360, 420));
    ~ClientQuickAdd() override = default;

private:
    // UI build
    void BuildUI();
    void BuildTopBar(wxBoxSizer* root);
    void BuildForm(wxBoxSizer* root);

    // Helpers (폼 컨텍스트)
    void BeginForm(wxPanel* panel, wxBoxSizer* fields,
        int labelWidth = 86, int rowVPad = 4, int labelGap = 6);
    void EndForm();

    void AddRow(const wxString& label, wxWindow* editor, int proportion = 1);
    wxChoice* AddChoiceRow(const wxString& label, const wxArrayString& choices, int sel = 0);
    wxTextCtrl* AddEditRow(const wxString& label, const wxString& hint = wxEmptyString,
        bool multiline = false, bool enable = true, long extraStyle = 0);

    void InstallEscClose();

    // Events
    void OnSave(wxCommandEvent&);
    void OnClose(wxCommandEvent&);

private:
    // containers
    wxPanel* m_panel{ nullptr };
    wxButton* m_btnClose{ nullptr };
    wxButton* m_btnSave{ nullptr };

    // fields
    wxChoice* m_cbClientKind{ nullptr }; // 거래처구분: 회사/개인
    wxChoice* m_cbTradeKind{ nullptr }; // 거래구분: 매입/매출
    wxTextCtrl* m_edCompany{ nullptr };
    wxTextCtrl* m_edBizNo{ nullptr }; // 사업자번호(마스크 대신 힌트)
    wxTextCtrl* m_edCeo{ nullptr };
    wxTextCtrl* m_edAddr{ nullptr };
    wxTextCtrl* m_edPhone{ nullptr };
    wxTextCtrl* m_edEmail{ nullptr };
    wxTextCtrl* m_edMemo{ nullptr };

    // form context
    wxPanel* m_formPanel{ nullptr };
    wxBoxSizer* m_formFields{ nullptr };
    int         m_labelW{ 86 };
    int         m_rowVPad{ 4 };
    int         m_labelGap{ 6 };
};

