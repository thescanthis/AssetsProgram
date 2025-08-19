#pragma once
#include "SubFrame.h"

class CompanyInfo;

class CopyFrame : public SubFrame
{
public:
	CopyFrame(wxWindow* parent,const wxString&);
	virtual ~CopyFrame();

private:
	CompanyInfo* PanelAt(size_t i) { return i < CompanyPanels.size() ? CompanyPanels[i] : nullptr; }

private:
	std::vector<CompanyInfo*> CompanyPanels;
};

