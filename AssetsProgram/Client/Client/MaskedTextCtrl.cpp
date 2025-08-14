#include "pch.h"
#include "MaskedTextCtrl.h"
#include <wx/clipbrd.h>
#include <wx/dataobj.h>

// ASCII 숫자 판별(유니코드 변환 없이 안전)
static inline bool IsAsciiDigit(wxChar ch) { return ch >= wxChar('0') && ch <= wxChar('9'); }
static inline bool IsAsciiDigitInt(int keycode) { return keycode >= '0' && keycode <= '9'; }

MaskedTextCtrl::MaskedTextCtrl(wxWindow* parent, wxWindowID id, const wxString& mask, long style)
    : wxTextCtrl(parent, id, mask, wxDefaultPosition, wxDefaultSize, style),
    mask_(mask), buf_(mask)
{
    ChangeValue(buf_);                              // 초기 텍스트는 마스크 자체
    PlaceCaretAt(NextSlot(0, true));                // 첫 슬롯으로 캐럿

    Bind(wxEVT_SET_FOCUS, &MaskedTextCtrl::OnFocus, this);
    Bind(wxEVT_KEY_DOWN, &MaskedTextCtrl::OnKeyDown, this);
    Bind(wxEVT_CHAR_HOOK, &MaskedTextCtrl::OnCharHook, this);
    Bind(wxEVT_LEFT_DOWN, &MaskedTextCtrl::OnLeftDown, this);
    Bind(wxEVT_TEXT_PASTE, &MaskedTextCtrl::OnPaste, this);

    SetEditable(true);
}

wxString MaskedTextCtrl::GetDigits() const {
    wxString d; d.reserve(buf_.length());
    for (auto ch : buf_) if (IsAsciiDigit((wxChar)ch)) d += (wxChar)ch;
    return d;
}
wxString MaskedTextCtrl::GetFormatted() const { return buf_; }

void MaskedTextCtrl::SetDigits(const wxString& digits) {
    wxString only; only.reserve(digits.length());
    for (auto ch : digits) if (IsAsciiDigit((wxChar)ch)) only += (wxChar)ch;

    size_t di = 0;
    for (size_t i = 0; i < buf_.length(); ++i) {
        wxChar m = mask_.GetChar(i);
        if (m == wxChar('_')) {
            if (di < only.length()) buf_[i] = only.GetChar(di++);
            else                     buf_[i] = wxChar('_');
        }
        else {
            buf_[i] = m;
        }
    }
    ChangeValue(buf_);
    PlaceCaretAt(NextSlot(0, true));
}

// ─ helpers ─
bool  MaskedTextCtrl::IsSlot(long i) const { return i >= 0 && (size_t)i < mask_.length() && mask_.GetChar((size_t)i) == wxChar('_'); }
long  MaskedTextCtrl::NextSlot(long from, bool include_from) const {
    long i = include_from ? from : from + 1;
    while ((size_t)i < mask_.length() && !IsSlot(i)) ++i;
    if ((size_t)i >= mask_.length()) i = (long)mask_.length();
    return i;
}
long  MaskedTextCtrl::PrevSlot(long from, bool include_from) const {
    long i = include_from ? from : from - 1;
    while (i >= 0 && !IsSlot(i)) --i;
    if (i < 0) i = NextSlot(0, true);
    return i;
}
void  MaskedTextCtrl::PlaceCaretAt(long idx) {
    if (idx < 0) idx = 0;
    if ((size_t)idx > buf_.length()) idx = (long)buf_.length();

    // ★ 이벤트 루프가 끝난 뒤에 캐럿을 놓는다(가시성 확보)
    CallAfter([this, idx] {
        long pos = idx;
        if ((size_t)pos > buf_.length()) pos = (long)buf_.length();
        SetInsertionPoint(pos);
        SetSelection(pos, pos);   // 하이라이트 제거 + 캐럿 보이기
        ShowPosition(pos);        // 스크롤 보정
        });
}
void  MaskedTextCtrl::RefreshView(long caret) {
    ChangeValue(buf_);
    PlaceCaretAt(caret);
}

// ─ events ─
void MaskedTextCtrl::OnFocus(wxFocusEvent&) {
    long caret = GetInsertionPoint();
    if (!IsSlot(caret)) caret = NextSlot(caret, true);
    PlaceCaretAt(caret);
}
void MaskedTextCtrl::OnLeftDown(wxMouseEvent& e) {
    SetFocus();                   // 클릭 시 포커스 보장
    e.Skip();
    CallAfter([this] {
        long caret = GetInsertionPoint();
        if (!IsSlot(caret)) caret = NextSlot(caret, true);
        PlaceCaretAt(caret);      // 클릭 후 슬롯 위치로 보정 + 표시
        });
}

// 공통 키 처리 — 처리했으면 true
bool MaskedTextCtrl::HandleKey(int code) {
    long caret = GetInsertionPoint();

    switch (code) {
    case WXK_LEFT:  PlaceCaretAt(PrevSlot(caret, false)); return true;
    case WXK_RIGHT: PlaceCaretAt(NextSlot(caret, false)); return true;
    case WXK_HOME:  PlaceCaretAt(NextSlot(0, true));      return true;
    case WXK_END: {
        long last = (long)mask_.length() - 1;
        while (last >= 0 && !IsSlot(last)) --last;
        PlaceCaretAt(last >= 0 ? last : 0);
        return true;
    }
    case WXK_TAB:
    case WXK_RETURN:
        return false; // 기본 처리 통과
    default: break;
    }

    // 숫자키(상단/키패드)
    bool isDigitKey = IsAsciiDigitInt(code);
    bool isNumpad = (code >= WXK_NUMPAD0 && code <= WXK_NUMPAD9);
    if (isDigitKey || isNumpad) {
        wxChar ch = isNumpad ? wxChar('0' + (code - WXK_NUMPAD0)) : wxChar(code);
        if (caret >= (long)buf_.length()) caret = NextSlot(0, true);
        if (!IsSlot(caret)) caret = NextSlot(caret, true);
        if ((size_t)caret < buf_.length() && IsSlot(caret)) {
            buf_[(size_t)caret] = ch;
            caret = NextSlot(caret, false);
        }
        RefreshView(caret);
        return true;
    }

    // 삭제키
    if (code == WXK_BACK) {
        long pos = IsSlot(caret) ? caret : PrevSlot(caret, false);
        if ((size_t)pos < buf_.length() && IsSlot(pos)) { buf_[(size_t)pos] = wxChar('_'); caret = pos; }
        RefreshView(caret);
        return true;
    }
    if (code == WXK_DELETE) {
        if ((size_t)caret < buf_.length() && IsSlot(caret)) buf_[(size_t)caret] = wxChar('_');
        RefreshView(caret);
        return true;
    }
    return false; // 그 외 키는 기본 입력 막음(핸들러에서 처리)
}

void MaskedTextCtrl::OnKeyDown(wxKeyEvent& e) {
    int code = e.GetKeyCode();
    if (code == WXK_TAB || code == WXK_RETURN) { e.Skip(); return; } // 예외만 통과
    if (HandleKey(code)) return;  // 숫자/이동/삭제 → 내부에서 커서 배치
    return;                       // 그 외 키(영문/기호)는 기본 입력 차단
}

void MaskedTextCtrl::OnCharHook(wxKeyEvent& e) {
    int code = e.GetKeyCode();
    if (code == WXK_TAB || code == WXK_RETURN) { e.Skip(); return; }
    if (HandleKey(code)) return;
    return;                       // 차단
}

void MaskedTextCtrl::OnPaste(wxClipboardTextEvent&) {
    wxString clip;
    if (wxTheClipboard->Open()) {
        if (wxTheClipboard->IsSupported(wxDF_TEXT)) {
            wxTextDataObject data; wxTheClipboard->GetData(data); clip = data.GetText();
        }
        wxTheClipboard->Close();
    }
    if (clip.empty()) return;

    wxString digits; for (auto ch : clip) if (IsAsciiDigit((wxChar)ch)) digits += (wxChar)ch;

    long caret = GetInsertionPoint();
    if (!IsSlot(caret)) caret = NextSlot(caret, true);

    for (auto d : digits) {
        if ((size_t)caret >= buf_.length()) break;
        if (!IsSlot(caret)) { caret = NextSlot(caret, true); if ((size_t)caret >= buf_.length()) break; }
        buf_[(size_t)caret] = d;
        caret = NextSlot(caret, false);
    }
    RefreshView(caret);
}