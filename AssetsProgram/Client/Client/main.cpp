#include "pch.h"
#include "MainFrame.h"

TemplateFunc* Template = nullptr;

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  // �ڵ� �� üũ
        wxInitAllImageHandlers(); // wxImage�� �ʱ�ȭ

        Template = new TemplateFunc();

        frame = new MainFrame();
        frame->Show();
        SetTopWindow(frame);
        SetExitOnFrameDelete(true);  // �̰� ���������� �������� ���� �� delete ��
        return true;
    }

    virtual int OnExit() override {
        delete Template;
        wxImage::CleanUpHandlers(); // ���� �۾�
        return wxApp::OnExit();
    }

private:
    MainFrame* frame = nullptr;
};

wxIMPLEMENT_APP(MyApp);