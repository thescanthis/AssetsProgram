#include "pch.h"
#include "MainFrame.h"
#include "CopyFrame.h"

MainFrame::MainFrame()
	:wxFrame(nullptr, wxID_ANY, "����ȭ��", wxDefaultPosition, wxSize(1024, 768)) 
{
	SetSizeHints(1024, 768, 1024, 768);
	m_panel = new wxPanel(this,wxID_ANY);
	m_panel->SetBackgroundColour(wxColour(247,249,253));
	

	frames =new CopyFrame(m_panel,"ȸ�����");

	auto* host = new wxBoxSizer(wxVERTICAL);
	host->Add(frames, 1, wxEXPAND);
	m_panel->SetSizer(host);
	// �����ӿ� �� ä���
	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->Add(m_panel, 1, wxEXPAND);
	SetSizer(frameSizer);
	Centre();

	Layout();  // ��ü ���̾ƿ� ����
}

MainFrame::~MainFrame()
{
}
