#pragma once
class SubFrame : public wxPanel
{
public:
	SubFrame(wxWindow* parent,const wxString& title, wxWindowID id = wxID_ANY);
	virtual ~SubFrame();

	wxBoxSizer* GetContentSizer() const { return contentSizer; }
protected:
	wxColour themeColour;
	wxPanel* titlePanel = nullptr;

private:
	void CreateTitleBar(const wxString& title);
	void OnPaint(wxPaintEvent& event);
private:
	wxBoxSizer* rootSizer = nullptr;
	wxBoxSizer* contentSizer = nullptr;

	wxStaticText* titleText = nullptr;
};

