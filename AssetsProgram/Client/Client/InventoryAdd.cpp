#include "pch.h"
#include "InventoryAdd.h"

InventoryAdd::InventoryAdd()
	:wxFrame(nullptr, wxID_ANY, "재고자산추가", wxDefaultPosition, wxSize(350, 320))
{
    ScreenInit();
	Center();
	Layout();
}

InventoryAdd::~InventoryAdd()
{
}

void InventoryAdd::ScreenInit()
{
    // 최상위 컨테이너
    m_panel = new wxPanel(this, wxID_ANY);
    m_panel->SetBackgroundColour(*wxWHITE);

    // 프레임 루트 시저
    frameSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(frameSizer);
    frameSizer->Add(m_panel, 1, wxEXPAND);

    // 패널 내부 루트
    auto* root = new wxBoxSizer(wxVERTICAL);
    m_panel->SetSizer(root);

    // ─────────────────────────────────────────────
    // 폼: 2열(라벨/에디트), 우측 컬럼 확장
    // rows=0 ⇒ 필요한 만큼 동적으로
    auto* form = new wxFlexGridSizer(0, 2, 6, 10);
    form->AddGrowableCol(1, 1); // 에디트/콤보 있는 2번째 컬럼이 가로로 확장

    // 라벨 폭 통일을 위한 상수 (필요에 따라 조절)
    const int kLabelWidth = 110;

    // 라벨 텍스트들 (마지막 전 줄이 콤보 박스)
    wxString LabelStr[8] = { "상품명","날짜","재고번호","거래처","수량","단위","재고분류","사업명" };
    int size = sizeof(LabelStr) / sizeof(wxString);

    for (int i = 0; i < size; ++i)
    {
        // 라벨
        auto* lb = new wxStaticText(m_panel, wxID_ANY, LabelStr[i]);
        lb->SetMinSize(wxSize(kLabelWidth, -1));
        form->Add(lb, 0, wxALIGN_CENTER_VERTICAL);

        if (i == 6) {
            // 7번째 줄: 콤보박스
            wxArrayString choices;
            choices.Add("입고");
            choices.Add("출고");
            auto* combo = new wxComboBox(m_panel, wxID_ANY, "",
                wxDefaultPosition, wxDefaultSize,
                choices, wxCB_READONLY);
            form->Add(combo, 1, wxEXPAND);
        }
        else {
            // 나머지 줄: 에디트
            auto* edit = new wxTextCtrl(m_panel, wxID_ANY, "");
            form->Add(edit, 1, wxEXPAND | wxLEFT, 4);
        }
    }

    root->Add(form, 0, wxEXPAND | wxALL, 4);

    // ─────────────────────────────────────────────
    // 버튼 줄 (오른쪽 정렬)
    auto* btnBar = new wxBoxSizer(wxHORIZONTAL);
    auto* SaveBtn = new wxButton(m_panel, wxID_ANY, "불러오기");
    auto* btnOK = new wxButton(m_panel, wxID_OK, "추가");
    auto* btnCancel = new wxButton(m_panel, wxID_CANCEL, "취소");

    btnBar->Add(SaveBtn, 0, wxLEFT, 4);
    btnBar->AddStretchSpacer(1);
    btnBar->Add(btnOK, 0, wxRIGHT, 6);
    btnBar->Add(btnCancel, 0, wxRIGHT, 6);

    root->Add(btnBar, 0, wxEXPAND | wxTOP, 12);

    // 레이아웃 마무리 + 중앙 배치(부모 있으면 부모 기준)
    Layout();
    if (GetParent()) CentreOnParent();
    else             CentreOnScreen();
}
