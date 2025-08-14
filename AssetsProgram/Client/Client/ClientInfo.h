#pragma once
class ClientInfo : public wxFrame
{
public:
	explicit ClientInfo(wxWindow* parent = nullptr);
	~ClientInfo();

public:
	
private:
	void BtnTitleInit();
	void LeftBodyInit();
	void RightBodyInit();
	void RightBottmInit();
	void ClientDetails();
private:
	wxPanel* m_panel, * m_TopPanel, * m_LeftPanel, * m_RightPanel,*m_RightBottmPanel;
	std::vector<wxStaticText*> InfoTitle;
	std::vector<wxTextCtrl*>   InfoEdit;

	wxBoxSizer* shell = nullptr;
	wxBoxSizer* m_bodySizer = nullptr;
	wxGrid* m_grid;
};

