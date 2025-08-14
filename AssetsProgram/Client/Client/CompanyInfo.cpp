#include "pch.h"
#include "CompanyInfo.h"

CompanyInfo::CompanyInfo(wxWindow* parent, const wxString& title) : SubFrame(parent, title)
{

}

CompanyInfo::~CompanyInfo()
{
}

wxButton* CompanyInfo::AddButton(const wxString& label, Callback cb, int bottom)
{
    auto* btn = new wxButton(this, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
    if (cb) btn->Bind(wxEVT_BUTTON, [cb](wxCommandEvent&) { cb(); });

    GetContentSizer()->Add(btn, 0, wxEXPAND | (bottom > 0 ? wxBOTTOM : 0), bottom);
    return btn;
}
