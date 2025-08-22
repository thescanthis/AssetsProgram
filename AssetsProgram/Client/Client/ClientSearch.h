#pragma once
class ClientSearch : public wxFrame
{
public:
    explicit ClientSearch(wxWindow* parent = nullptr,
         wxString title = "�ŷ�ó ����",
         wxSize size = wxSize(780, 520));
    ~ClientSearch() override = default;

private:
    // === UI ���� ===
    void BuildUI();
    void BuildTopBar(wxBoxSizer* root);
    void BuildSearchBar(wxBoxSizer* root);
    void BuildNotebook(wxBoxSizer* root);

    // === ���� ���� ===
    wxButton* MakeButton(wxWindow* parent, const wxString& text,
        wxObjectEventFunction handler,
        int rightPad = 0, long style = 0);
   
    void      AutoPadLastColumn(wxGrid* grid, int extra = 10);
    void      InstallEscToClose();

    // === �̺�Ʈ ===
    void OnClickQuickAdd(wxCommandEvent&);   // ���: ���� �߰�
    void OnClickClose(wxCommandEvent&);      // ���: �ݱ�
    void OnClickSearch(wxCommandEvent&);     // �˻� ��ư
    void OnGridDClick(wxGridEvent& e);       // ����Ŭ��

private:
    // �����̳�
    wxPanel* m_panel = nullptr;
    wxNotebook* m_book = nullptr;

    // ��� ��ư��
    wxButton* m_btnQuickAdd = nullptr;
    wxButton* m_btnClose = nullptr;

    // �˻���
    wxChoice* m_cbField = nullptr;
    wxTextCtrl* m_edQuery = nullptr;
    wxButton* m_btnSearch = nullptr;

    // �� & �׸���
    wxPanel* m_tabCompany = nullptr;
    wxPanel* m_tabPerson = nullptr;
    wxGrid* m_gridCompany = nullptr;
    wxGrid* m_gridPerson = nullptr;

    wxDECLARE_EVENT_TABLE();
};

