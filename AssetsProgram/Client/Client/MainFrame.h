#pragma once

class CopyFrame;

class MainFrame : public wxFrame
{
public:
	MainFrame();
	~MainFrame();

private:
	wxPanel* m_panel;
	CopyFrame* frames;
};

