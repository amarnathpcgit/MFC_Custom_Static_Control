#pragma once
#include <atlimage.h>

class CStaticCtrl : public CStatic
{
    DECLARE_DYNAMIC(CStaticCtrl)

    enum STATIC_STYLE {
        DUMMY = 1,
        TEXT
    };

public:
    CStaticCtrl();
    virtual ~CStaticCtrl();

protected:
    BOOL m_bIsBgImageEnabled = FALSE;
    STATIC_STYLE m_enStyle;
    COLORREF m_clrBkColor;
    COLORREF m_clrBkColor2;
    COLORREF m_clrTextColor;
    CString m_strText;
    UINT m_uTextFormat;
    COLORREF m_clrOutLine;
    COLORREF m_clrInLine;
    INT m_nX, m_nY;
    CImage m_bgImage;
    BOOL m_bVerticalText = FALSE;
    BOOL m_bIsGradientEnabled = FALSE;

public:
    void EnableBackgroundImage(bool bEnable);
    void EnableGradientBackground(bool bEnable);
    void SetStyle(STATIC_STYLE enStyle);
    void SetVerticalText(BOOL bVertical);
    void SetTextColor(COLORREF clrTextColor);
    void SetBkColor(COLORREF clrBkColor);
    void SetBkColor2(COLORREF clrBkColor2);
    void SetText(CString strText, UINT uFormat = DT_LEFT | DT_VCENTER);
    void SetOutLineColor(COLORREF clrOutLine);
    void SetInLineColor(COLORREF clrInLine);
    void SetPadding(INT nX, INT nY);
    void SetBgImage(LPCTSTR imgFilePath);

protected:
    virtual void PreSubclassWindow();
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

    DECLARE_MESSAGE_MAP()
};