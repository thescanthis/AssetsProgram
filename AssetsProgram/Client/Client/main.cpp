#include "pch.h"
#include "MainFrame.h"

TemplateFunc* G_Template = nullptr;
DBTest* DBMaps = nullptr;

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  // 자동 릭 체크
        wxInitAllImageHandlers(); // wxImage용 초기화

        G_Template = new TemplateFunc();
        DBMaps = new DBTest();

        frame = new MainFrame();
        frame->Show();
        SetTopWindow(frame);
        SetExitOnFrameDelete(true);  // 이거 설정했으면 프레임이 닫힐 때 delete 됨
        return true;
    }

    virtual int OnExit() override {
        delete G_Template;
        delete DBMaps;
        wxImage::CleanUpHandlers(); // 정리 작업
        return wxApp::OnExit();
    }

private:
    MainFrame* frame = nullptr;
};

wxIMPLEMENT_APP(MyApp);