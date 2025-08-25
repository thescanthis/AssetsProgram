#pragma once

class ClientOrderManage : public wxFrame
{
public:
    explicit ClientOrderManage(wxWindow* parent = nullptr,
        const wxString& title = "발주관리",
        const wxSize& size = wxSize(1024, 600));
    ~ClientOrderManage() override = default;

private:
    // ==== UI 구성 ====
    void BuildUI();
    void BuildToolbar(wxBoxSizer* root);
    void BuildTabs(wxBoxSizer* root);

    // 탭들
    void BuildTab_Period(wxPanel* tab);     // 기간 조회
    void BuildTab_ByClient(wxPanel* tab);   // 거래처별 조회

    // ==== 공용 헬퍼 ====
    void      AutoPadLastColumn(wxGrid* g, int extra = 12);
    void      InstallEscClose();

    // 공통 필터바: “조회기간 [start] - [end]  [기간]   (오른쪽) [조회]”
    void BuildDateRangeBar(wxWindow* parent,
        wxWindow*& outPanel,
        wxDatePickerCtrl*& outStart,
        wxDatePickerCtrl*& outEnd,
        wxButton*& outQuickBtn,
        wxButton*& outFindBtn,
        bool withLeftAllButton = false,
        wxButton** outAllBtn = nullptr);

    // ==== 이벤트 ====
    void OnPrint(wxCommandEvent&);
    void OnAdd(wxCommandEvent&);
    void OnEdit(wxCommandEvent&);
    void OnDelete(wxCommandEvent&);
    void OnClose(wxCommandEvent&);

    void OnAll(wxCommandEvent&);        // “전체” 버튼
    void OnQuickPeriod(wxCommandEvent&);// “기간” 버튼 (예: 최근 7일 토글)
    void OnQuery(wxCommandEvent&);      // “조회” 버튼

    void OnGridDClick(wxGridEvent& e);       // 더블클릭

private:
    // 컨테이너
    wxPanel* m_panel{ nullptr };
    wxNotebook* m_book{ nullptr };

    // 툴바 버튼
    wxButton* m_btnPrint{ nullptr };
    wxButton* m_btnNew{ nullptr };
    wxButton* m_btnEdit{ nullptr };
    wxButton* m_btnDel{ nullptr };
    wxButton* m_btnClose{ nullptr };

    // 기간 조회 탭
    wxPanel* m_tabPeriod{ nullptr };
    wxPanel* m_periodBar{ nullptr };
    wxDatePickerCtrl* m_dpStart{ nullptr };
    wxDatePickerCtrl* m_dpEnd{ nullptr };
    wxButton* m_btnQuick{ nullptr };
    wxButton* m_btnQuery{ nullptr };
    wxButton* m_btnAll{ nullptr };
    wxGrid* m_gridPeriod{ nullptr };

    // 거래처별/조건 탭 (간단히 동일 구성으로 시작)
    wxPanel* m_tabByClient{ nullptr };
    wxPanel* m_clientBar{ nullptr };
    wxDatePickerCtrl* m_dpCStart{ nullptr };
    wxDatePickerCtrl* m_dpCEnd{ nullptr };
    wxButton* m_btnCQuick{ nullptr };
    wxButton* m_btnCQuery{ nullptr };
    wxGrid* m_gridClient{ nullptr };

    wxPanel* m_condBar{ nullptr };
    wxDatePickerCtrl* m_dpKStart{ nullptr };
    wxDatePickerCtrl* m_dpKEnd{ nullptr };
    wxButton* m_btnKQuick{ nullptr };
    wxButton* m_btnKQuery{ nullptr };
    wxGrid* m_gridCond{ nullptr };
};
