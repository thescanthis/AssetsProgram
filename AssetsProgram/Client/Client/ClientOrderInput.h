#pragma once

class ClientOrderInput : public wxFrame
{
public:
    explicit ClientOrderInput(wxWindow* parent = nullptr,
        const wxString& title = "발주서입력",
        const wxSize& size = wxSize(850, 700));
    ~ClientOrderInput() override = default;

private:
    // ===== UI 빌드 =====
    void BuildUI();
    void BuildTopBar(wxBoxSizer* root);       // 상단 저장/종료
    void BuildHeader(wxBoxSizer* root);       // 좌/우 기본정보
    void BuildOrderMeta(wxBoxSizer* root);    // 발주일/납기일/메모
    void BuildItems(wxBoxSizer* root);        // 품목 툴바 + 그리드
    void BuildTotals(wxBoxSizer* root);       // 공급가액/세액/합계금액
    void BuildBottomMemo(wxBoxSizer* root);   // 메모 1~4

    // ===== 공용 헬퍼(폼 컨텍스트) =====
    void BeginForm(wxPanel* panel, wxBoxSizer* fields,
        int labelWidth = 78, int rowVPad = 4, int labelGap = 6);
    void EndForm();

    void AddRow(const wxString& label, wxWindow* editor, int proportion = 1);
    wxTextCtrl* AddEditRow(const wxString& label, const wxString& hint = wxEmptyString,
        bool multiline = false, long extraStyle = 0);
    wxChoice* AddChoiceRow(const wxString& label, const wxArrayString& choices, int sel = 0);
    wxSearchCtrl* AddSearchRow(const wxString& label, const wxString& hint = wxEmptyString);

    void         InstallEscClose();

    // ===== 이벤트 =====
    void OnSave(wxCommandEvent&);
    void OnClose(wxCommandEvent&);
    void OnAddClient(wxCommandEvent&);
    void OnFindClient(wxCommandEvent&);
    void OnAddItem(wxCommandEvent&);
    void OnDeleteSelected(wxCommandEvent&);

    void OnGridClick(wxGridEvent& e);

private:
    // 컨테이너
    wxPanel* m_panel{ nullptr };

    // 상단 버튼
    wxButton* m_btnSave{ nullptr };
    wxButton* m_btnClose{ nullptr };

    // 좌측(수신/발주 안내)
    wxSearchCtrl* m_rcvSearch{ nullptr };
    wxButton* m_btnAddClient{ nullptr };
    wxTextCtrl* m_edRef{ nullptr };
    wxTextCtrl* m_edContact{ nullptr };
    wxTextCtrl* m_edPayTerm{ nullptr };

    // 우측(거래처 정보)
    wxTextCtrl* m_edRegNo{ nullptr };
    wxTextCtrl* m_edCEO{ nullptr };
    wxTextCtrl* m_edCompany{ nullptr };
    wxChoice* m_chDept{ nullptr };
    wxChoice* m_chPerson{ nullptr };
    wxTextCtrl* m_edPhone{ nullptr };
    wxTextCtrl* m_edEmail{ nullptr };

    // 발주 메타
    wxDatePickerCtrl* m_dpOrderDate{ nullptr };
    wxDatePickerCtrl* m_dpDueDate{ nullptr };
    wxTextCtrl* m_edMemoTop{ nullptr };

    // 품목
    wxButton* m_btnPickItem{ nullptr };
    wxButton* m_btnDelSel{ nullptr };
    wxGrid* m_gridItems{ nullptr };

    // 합계
    wxTextCtrl* m_edSubtotal{ nullptr };
    wxTextCtrl* m_edVat{ nullptr };
    wxTextCtrl* m_edTotal{ nullptr };

    // 하단 메모
    wxTextCtrl* m_edMemo1{ nullptr };
    wxTextCtrl* m_edMemo2{ nullptr };
    wxTextCtrl* m_edMemo3{ nullptr };
    wxTextCtrl* m_edMemo4{ nullptr };

    // 폼 컨텍스트
    wxPanel* m_formPanel{ nullptr };
    wxBoxSizer* m_formFields{ nullptr };
    int         m_labelW{ 78 };
    int         m_rowVPad{ 4 };
    int         m_labelGap{ 6 };
};