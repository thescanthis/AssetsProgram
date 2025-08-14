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

	void OpenInventoryAdd();
	void OpenPartnerInfo();
	void OpenInventoryQuery();
private:
	std::vector<CompanyInfo*> CompanyPanels;
	std::unordered_map<std::type_index, wxWindow*> singletons_;

public:
	template<class WinT,class... Args>
	std::function<void()> MakeSingletonOpener(wxWindow* parent, Args&&... args) {
        auto args_tuple = std::make_tuple(std::forward<Args>(args)...);

        return [this, parent, args_tuple]() mutable {
            auto& ptr = singletons_[std::type_index(typeid(WinT))];
            if (ptr && ptr->IsBeingDeleted()) ptr = nullptr;

            if (!ptr) {
                ptr = std::apply([&](auto&&... as) {
                    return static_cast<wxWindow*>(new WinT(parent, std::forward<decltype(as)>(as)...));
                    }, args_tuple);

                ptr->Bind(wxEVT_CLOSE_WINDOW, [](wxCloseEvent& e) { e.Skip(); });
                ptr->Bind(wxEVT_DESTROY, [this](wxWindowDestroyEvent& ev) {
                    wxWindow* w = static_cast<wxWindow*>(ev.GetEventObject());
                    for (auto& kv : singletons_) if (kv.second == w) { kv.second = nullptr; break; }
                    });
            }
            if (!ptr->IsShown()) ptr->Show();
            ptr->Raise();
            };
	}
};

