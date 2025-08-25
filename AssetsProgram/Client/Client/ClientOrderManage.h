#pragma once

class ClientOrderManage : public wxFrame
{
public:
    explicit ClientOrderManage(wxWindow* parent = nullptr,
        const wxString& title = "���ְ���",
        const wxSize& size = wxSize(1024, 600));
    ~ClientOrderManage() override = default;

private:
    // ==== UI ���� ====
    void BuildUI();
    void BuildToolbar(wxBoxSizer* root);
    void BuildTabs(wxBoxSizer* root);

    // �ǵ�
    void BuildTab_Period(wxPanel* tab);     // �Ⱓ ��ȸ
    void BuildTab_ByClient(wxPanel* tab);   // �ŷ�ó�� ��ȸ

    // ==== ���� ���� ====
    void      AutoPadLastColumn(wxGrid* g, int extra = 12);
    void      InstallEscClose();

    // ���� ���͹�: ����ȸ�Ⱓ [start] - [end]  [�Ⱓ]   (������) [��ȸ]��
    void BuildDateRangeBar(wxWindow* parent,
        wxWindow*& outPanel,
        wxDatePickerCtrl*& outStart,
        wxDatePickerCtrl*& outEnd,
        wxButton*& outQuickBtn,
        wxButton*& outFindBtn,
        bool withLeftAllButton = false,
        wxButton** outAllBtn = nullptr);

    // ==== �̺�Ʈ ====
    void OnPrint(wxCommandEvent&);
    void OnAdd(wxCommandEvent&);
    void OnEdit(wxCommandEvent&);
    void OnDelete(wxCommandEvent&);
    void OnClose(wxCommandEvent&);

    void OnAll(wxCommandEvent&);        // ����ü�� ��ư
    void OnQuickPeriod(wxCommandEvent&);// ���Ⱓ�� ��ư (��: �ֱ� 7�� ���)
    void OnQuery(wxCommandEvent&);      // ����ȸ�� ��ư

    void OnGridDClick(wxGridEvent& e);       // ����Ŭ��

private:
    // �����̳�
    wxPanel* m_panel{ nullptr };
    wxNotebook* m_book{ nullptr };

    // ���� ��ư
    wxButton* m_btnPrint{ nullptr };
    wxButton* m_btnNew{ nullptr };
    wxButton* m_btnEdit{ nullptr };
    wxButton* m_btnDel{ nullptr };
    wxButton* m_btnClose{ nullptr };

    // �Ⱓ ��ȸ ��
    wxPanel* m_tabPeriod{ nullptr };
    wxPanel* m_periodBar{ nullptr };
    wxDatePickerCtrl* m_dpStart{ nullptr };
    wxDatePickerCtrl* m_dpEnd{ nullptr };
    wxButton* m_btnQuick{ nullptr };
    wxButton* m_btnQuery{ nullptr };
    wxButton* m_btnAll{ nullptr };
    wxGrid* m_gridPeriod{ nullptr };

    // �ŷ�ó��/���� �� (������ ���� �������� ����)
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
