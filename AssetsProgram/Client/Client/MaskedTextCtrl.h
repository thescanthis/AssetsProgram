#pragma once
#include <wx/wx.h>
#include <wx/clipbrd.h>
#include <wx/dataobj.h>

class MaskedTextCtrl : public wxTextCtrl {
public:
    // mask: '_' = 입력 슬롯, 그 외 문자는 고정(-, 공백, 얇은 공백 등)
    MaskedTextCtrl(wxWindow* parent, wxWindowID id, const wxString& mask,
        long style = wxBORDER_SIMPLE);

    wxString GetDigits() const;        // 하이픈/공백 제거 숫자만
    wxString GetFormatted() const;     // 마스크 포함 전체 문자열
    void     SetDigits(const wxString& digits); // 숫자만 주면 채움

private:
    wxString mask_, buf_;

    // 슬롯/이동 헬퍼
    bool IsSlot(long i) const;
    long NextSlot(long from, bool include_from = false) const;
    long PrevSlot(long from, bool include_from = false) const;

    // 뷰/캐럿
    void RefreshView(long caret);
    void PlaceCaretAt(long idx);

    // 이벤트
    void OnFocus(wxFocusEvent&);
    void OnKeyDown(wxKeyEvent&);
    void OnCharHook(wxKeyEvent&);
    void OnLeftDown(wxMouseEvent&);
    void OnPaste(wxClipboardTextEvent&);

    // 공통 키 처리(숫자/이동/삭제) — 처리했으면 true
    bool HandleKey(int code);
};