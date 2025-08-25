#include "pch.h"
#include "ProductInfo.h"
#include "ProductAdd.h"

ProductInfo::ProductInfo(wxWindow* parent, const wxString Title)
	:WidgetParent(parent,Title)
{
    SetSizeHints(600, 420, 600, 420);         // 고정 크기(원하면 제거)

    m_RightPanel = new wxPanel(m_panel, wxID_ANY);
    m_RightPanel->SetBackgroundColour(*wxWHITE);

    ProductInfos = DBMaps->ProductInfos;

    // 메인 패널
    auto* shell = new wxBoxSizer(wxVERTICAL);
    m_panel->SetSizer(shell);
    
    // 저장 나가기 공간
    BtnTitleInit();
    auto* line = new wxStaticLine(m_panel, wxID_ANY);

    //좌측 정보
    LeftBodyInit();
    //우측 그리드
    RightBodyInit();
    
    // 위→아래로 배치
    shell->Add(m_TopPanel, 0, wxEXPAND);
    shell->Add(line, 0, wxEXPAND);
    shell->Add(m_bodySizer, 1, wxEXPAND);   // ← 핵심!

    // 프레임 채우기
    auto* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(m_panel, 1, wxEXPAND);
    SetSizer(frameSizer);
    Layout();
    Center();
}
ProductInfo::~ProductInfo()
{
}

void ProductInfo::BtnProductAdd(wxCommandEvent& event)
{
    G_Template->MakeSingletonOpener<ProductAdd>(this, "상품등록")();
    //int32 size = InfoEdit.size();
    //C_Details Temp;
    //
    //for (int32 j = 0; j < size; j++)
    //{
    //    wxString str = InfoEdit[j]->GetValue();
    //    Temp.CompanyInfoArr[j] = str;
    //}
    //std::string Title = static_cast<std::string>(InfoEdit[3]->GetValue().c_str());
    //ProductInfos[Title].push_back(Temp);
    //
    //GridInfoAdd(Title);
}

void ProductInfo::BtnProductChange(wxCommandEvent& event)
{
    G_Template->MakeSingletonOpener<ProductAdd>(this, "상품수정")();
}

void ProductInfo::BtnProductCancel(wxCommandEvent& event)
{
    for (int32 i = 0; i < InfoEdit.size(); i++)
        InfoEdit[i]->Clear();

    this->Close();
}

void ProductInfo::GridInfoAdd(std::string title)
{
    if (m_grid->GetNumberRows() < ProductInfos.size())
    {
        int32 size = ProductInfos.size() - m_grid->GetNumberRows();
        for(int32 i=0; i<size; i++)
            m_grid->AppendRows(1);
    }  

    int32 ItemNum = 0;
    std::vector<std::string> EndInfo;
    for (auto Details : ProductInfos[title])
    {
        std::string temp, temp1, temp2;
        temp = temp1 = temp2 = "";
        std::map<std::string, int32> TMap,TMap1;

        for (int i = 0; i < ProductInfos[title].size(); i++)
        {
            C_Details& detail = ProductInfos[title][i];
            temp1 = static_cast<std::string>(detail.CompanyInfoArr[detail.C_Numbering].c_str());
            temp2 = static_cast<std::string>(detail.CompanyInfoArr[detail.Corp_Numbering].c_str());
            temp = static_cast<std::string>(detail.CompanyInfoArr[detail.C_Item].c_str());

            TMap[temp1]++;
            TMap1[temp2]++;

            InvenNames.push_back(TMap);
            InvenNames1.push_back(TMap1);

            ItemNum += (temp.empty()) ? 0 : stoi(temp);
        }

        std::string Numbering = static_cast<std::string>(Details.CompanyInfoArr[Details.C_Numbering].c_str());
        std::string Numbering1 = static_cast<std::string>(Details.CompanyInfoArr[Details.Corp_Numbering].c_str());
        temp = TMap.size() > 1 ? Numbering +"외" + std::to_string(TMap.size()-1)+"개" : Numbering;
        temp1 = TMap1.size() > 1 ? Numbering1 + "외" + std::to_string(TMap1.size()-1)+"개" : Numbering1;

        EndInfo.push_back(title);
        EndInfo.push_back(temp);
        EndInfo.push_back(temp1);
        EndInfo.push_back(static_cast<std::string>(Details.CompanyInfoArr[Details.CorpPerson].c_str()));
        EndInfo.push_back(std::to_string(ItemNum));

        break;
    }

    for (int32 i = 0; i < m_grid->GetNumberCols(); i++)
    {
        wxString temp = EndInfo[i];
        m_grid->SetCellValue(ProductInfos.size()-1,i,temp);
    }
    

    DBMaps->ProductInfos = ProductInfos;

    //1. Lock
    //2. Validate Check
    //3. DB ADD
    m_grid->Refresh();
}

void ProductInfo::BtnGridInfoDel(wxCommandEvent& event)
{
    //1. Lock
    //2. Validate Check
    //3. DB ADD
    if (m_gridRow < 0)
        return;
   // ProductInfos.erase(ProductInfos.begin() + m_gridRow, ProductInfos.begin() + m_gridRow + 1);

    m_grid->DeleteRows(m_gridRow);
    m_grid->Refresh();
}

void ProductInfo::GridClickEvent(wxGridEvent& e)
{
    int32 Row = e.GetRow();
    int32 Rows = m_grid->GetNumberRows();
    int32 Cols = m_grid->GetNumberCols();

    G_Template->MakeSingletonOpener<ProductAdd>(this, "상품수정")();
    e.Skip();
}

void ProductInfo::BtnTitleInit()
{
    auto* topSz = new wxBoxSizer(wxHORIZONTAL);
    m_TopPanel->SetSizer(topSz);
    topSz->AddStretchSpacer();
    auto* btnAdd = new wxButton(m_TopPanel, wxID_SAVE, "등록");
    auto* btnChange = new wxButton(m_TopPanel, wxID_SAVE, "수정");
    auto* btnExit = new wxButton(m_TopPanel, wxID_EXIT, "나가기");
    topSz->Add(btnAdd, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
    topSz->Add(btnChange, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);
    topSz->Add(btnExit, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);

    btnAdd->Bind(wxEVT_BUTTON, &ProductInfo::BtnProductAdd, this);
    btnChange->Bind(wxEVT_BUTTON, &ProductInfo::BtnProductChange, this);
    btnExit->Bind(wxEVT_BUTTON, &ProductInfo::BtnProductCancel, this);
}

void ProductInfo::LeftBodyInit()
{
    // 오른쪽 내부 sizer
    auto* rightSz = new wxBoxSizer(wxVERTICAL);
    m_RightPanel->SetSizer(rightSz);

    auto* topH = new wxBoxSizer(wxHORIZONTAL);

    // ★ [거래처정보] 제목 (왼쪽과 동일한 스타일)
    auto* rtitle = new wxStaticText(m_RightPanel, wxID_ANY, "[상품정보]");
    { wxFont f = rtitle->GetFont(); f.MakeBold(); rtitle->SetFont(f); }
    rtitle->SetForegroundColour(wxColour(80, 80, 120));
    topH->Add(rtitle, 0, wxLEFT | wxTOP | wxRIGHT | wxBOTTOM, 8);

    topH->AddStretchSpacer();
    auto* btnDel = new wxButton(m_RightPanel, wxID_EXIT, "삭제");
    btnDel->SetBackgroundColour(*wxWHITE);
    topH->Add(btnDel, 0, wxTOP | wxBOTTOM | wxRIGHT, 8);

    // 상단 가로바를 우측 패널의 세로 레이아웃에 추가
    rightSz->Add(topH, 0, wxEXPAND | wxALL, 6);

    //m_grid = new wxGrid(m_RightPanel, wxID_ANY);
    //m_grid->CreateGrid(20, 2);                    // 초기 10행 5열 (원하면 바꿔도 OK)
    ////m_grid->SetSizeHints(485, 270, 485, 270); // = Min=Max=465x283

    m_grid = WU::MakeGrid(m_RightPanel, P_LabelStr, wid, wxEVT_GRID_CELL_LEFT_DCLICK, &ProductInfo::GridClickEvent, this);

    //// 예시 데이터(원하면 제거) DB에서 긁어오는 데이터

    int Row = 0;
    for (auto info : ProductInfos)
    {
        for (int i = 0; i < info.second.size(); i++)
        {
            m_grid->SetCellValue(Row, C_Details::C_Name, info.second[i].CompanyInfoArr[C_Details::C_Name]);
            m_grid->SetCellValue(Row, C_Details::C_Numbering, info.second[i].CompanyInfoArr[C_Details::C_Numbering]);;
        }
        Row++;
    }


    WU::GridColumnInitilize(m_grid, P_gridWid);

    rightSz->Add(m_grid, 1, wxALIGN_LEFT | wxALIGN_TOP);

    m_bodySizer->Add(m_RightPanel, 1, wxEXPAND);
    btnDel->Bind(wxEVT_BUTTON, &ProductInfo::BtnGridInfoDel, this);
}

void ProductInfo::InfoTitleInit()
{
    auto* left = new wxPanel(m_LeftPanel, wxID_ANY);
    left->SetBackgroundColour(*wxWHITE);
    left->SetMinSize(wxSize(300, -1));

    auto* v = new wxBoxSizer(wxVERTICAL);

    const int kTopBarH = 32;

    auto* topL = new wxBoxSizer(wxHORIZONTAL);
    auto* title = new wxStaticText(left, wxID_ANY, "[기본정보]");
    TitleFontInit(title);

    topL->Add(title, 0, wxALIGN_CENTER_VERTICAL);
    topL->AddStretchSpacer();

    topL->SetMinSize(wxSize(-1, kTopBarH));

    v->Add(topL, 0, wxLEFT | wxEXPAND | wxBOTTOM, 5);

    auto* fields = new wxBoxSizer(wxVERTICAL);
    v->Add(fields, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);

    for (int i = 0; i < InventoryTitle.size(); i++)
        addRow(left,fields,wxString(std::to_string(i+1))+". " + InventoryTitle[i], makeEdit(left,""));
    left->SetSizer(v);

    auto* leftRoot = wxDynamicCast(m_LeftPanel->GetSizer(), wxBoxSizer);
    leftRoot->Add(left, 1, wxEXPAND);
}

void ProductInfo::RightBodyInit()
{
    m_LeftPanel->SetSizeHints(300, -1, 300, -1);      // 폭 300 고정

    // 왼쪽 패널 내부용 세로 sizer
    auto* leftRoot = new wxBoxSizer(wxVERTICAL);
    m_LeftPanel->SetSizer(leftRoot);

    InfoTitleInit();

    m_bodySizer->Add(m_LeftPanel, 0, wxEXPAND);
}
