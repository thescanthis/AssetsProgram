#pragma once
class ClientSearch : public wxFrame
{
public:
    explicit ClientSearch(wxWindow* parent = nullptr,
         wxString title = "거래처 선택",
         wxSize size = wxSize(780, 520));
    ~ClientSearch() override = default;

private:
    // === UI 빌드 ===
    void BuildUI();
    void BuildTopBar(wxBoxSizer* root);
    void BuildSearchBar(wxBoxSizer* root);
    void BuildNotebook(wxBoxSizer* root);

    // === 공용 헬퍼 ===
    wxButton* MakeButton(wxWindow* parent, const wxString& text,
        wxObjectEventFunction handler,
        int rightPad = 0, long style = 0);
   
    void      AutoPadLastColumn(wxGrid* grid, int extra = 10);
    void      InstallEscToClose();

    // === 이벤트 ===
    void OnClickQuickAdd(wxCommandEvent&);   // 상단: 간편 추가
    void OnClickClose(wxCommandEvent&);      // 상단: 닫기
    void OnClickSearch(wxCommandEvent&);     // 검색 버튼
    void OnGridDClick(wxGridEvent& e);       // 더블클릭

private:
    // 컨테이너
    wxPanel* m_panel = nullptr;
    wxNotebook* m_book = nullptr;

    // 상단 버튼바
    wxButton* m_btnQuickAdd = nullptr;
    wxButton* m_btnClose = nullptr;

    // 검색바
    wxChoice* m_cbField = nullptr;
    wxTextCtrl* m_edQuery = nullptr;
    wxButton* m_btnSearch = nullptr;

    // 탭 & 그리드
    wxPanel* m_tabCompany = nullptr;
    wxPanel* m_tabPerson = nullptr;
    wxGrid* m_gridCompany = nullptr;
    wxGrid* m_gridPerson = nullptr;

    wxDECLARE_EVENT_TABLE();
};

