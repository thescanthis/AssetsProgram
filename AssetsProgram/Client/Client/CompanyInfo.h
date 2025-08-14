#pragma once
#include "SubFrame.h"
class CompanyInfo : public SubFrame 
{
public:
	using Callback = std::function<void()>;

	CompanyInfo(wxWindow* parent,const wxString& title);
	virtual ~CompanyInfo();

	wxButton* AddButton(const wxString& label, Callback cb, int bottom = 8);
};

