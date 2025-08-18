#include "pch.h"
#include "WidgetParent.h"

WidgetParent::WidgetParent(wxWindow* parent, const wxString Title, wxSize Size)
	:wxFrame(parent, wxID_ANY, Title, wxDefaultPosition, Size)
{
	m_panel = new wxPanel(this, wxID_ANY);
	m_panel->SetBackgroundColour(wxColour(247, 249, 253));

	m_TopPanel = new wxPanel(m_panel, wxID_ANY);
	m_TopPanel->SetBackgroundColour(wxColour(247, 249, 253));
	//m_TopPanel->SetBackgroundColour(wxColour(0, 0,255));
	m_LeftPanel = new wxPanel(m_panel, wxID_ANY);
	m_LeftPanel->SetBackgroundColour(*wxWHITE);
	m_bodySizer = new wxBoxSizer(wxHORIZONTAL);

	m_RightPanel = new wxPanel(m_panel, wxID_ANY);
	m_RightPanel->SetBackgroundColour(*wxWHITE);
}

WidgetParent::~WidgetParent()
{
}

void WidgetParent::TitleFontInit(wxStaticText* title, int AddFontSize)
{
	wxFont f = title->GetFont(); 
	f.MakeBold(); 
	f.SetPointSize(f.GetPointSize() + AddFontSize);  // 현재보다 +3pt
	title->SetFont(f);
	title->SetForegroundColour(wxColour(80, 80, 120));
}
