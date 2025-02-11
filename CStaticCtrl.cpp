#include "stdafx.h"
#include "StaticCtrl.h"

IMPLEMENT_DYNAMIC(CStaticCtrl, CStatic)

CStaticCtrl::CStaticCtrl()
    : m_enStyle(TEXT),
    m_clrBkColor(RGB(45, 45, 48)),
    m_clrTextColor(RGB(255, 255, 255)),
    m_strText(_T("")),
    m_uTextFormat(DT_LEFT | DT_VCENTER), // Ensure DT_SINGLELINE is included
    m_clrOutLine(RGB(45, 45, 48)),
    m_clrInLine(RGB(45, 45, 48)),
    m_nX(0), m_nY(0)
{
}

CStaticCtrl::~CStaticCtrl()
{
}

void CStaticCtrl::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
    ModifyStyle(0, SS_OWNERDRAW | SS_NOTIFY);
}

void CStaticCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    if (!pDC)
        return;

    CRect rcClient;
    GetClientRect(rcClient);

    // Draw background
    if (m_bIsGradientEnabled)
    {
        TRIVERTEX vertices[4];
        GRADIENT_RECT gRect;

        // Create a horizontal gradient centered in the control
        vertices[0].x = rcClient.left;
        vertices[0].y = rcClient.top;
        vertices[0].Red = GetRValue(m_clrBkColor) << 8;
        vertices[0].Green = GetGValue(m_clrBkColor) << 8;
        vertices[0].Blue = GetBValue(m_clrBkColor) << 8;
        vertices[0].Alpha = 0x0000;

        vertices[1].x = rcClient.right;
        vertices[1].y = rcClient.top + (rcClient.Height() / 2);
        vertices[1].Red = GetRValue(m_clrBkColor2) << 8;
        vertices[1].Green = GetGValue(m_clrBkColor2) << 8;
        vertices[1].Blue = GetBValue(m_clrBkColor2) << 8;
        vertices[1].Alpha = 0x0000;

        vertices[2].x = rcClient.left;
        vertices[2].y = rcClient.top + (rcClient.Height() / 2);
        vertices[2].Red = GetRValue(m_clrBkColor2) << 8;
        vertices[2].Green = GetGValue(m_clrBkColor2) << 8;
        vertices[2].Blue = GetBValue(m_clrBkColor2) << 8;
        vertices[2].Alpha = 0x0000;

        vertices[3].x = rcClient.right;
        vertices[3].y = rcClient.bottom;
        vertices[3].Red = GetRValue(m_clrBkColor) << 8;
        vertices[3].Green = GetGValue(m_clrBkColor) << 8;
        vertices[3].Blue = GetBValue(m_clrBkColor) << 8;
        vertices[3].Alpha = 0x0000;

        gRect.UpperLeft = 0;
        gRect.LowerRight = 1;
        pDC->GradientFill(vertices, 4, &gRect, 1, GRADIENT_FILL_RECT_V);
    }
    else
    {
        CBrush brush(m_clrBkColor);
        pDC->FillRect(rcClient, &brush);
    }

    // Draw background image
    if (m_bIsBgImageEnabled && !m_bgImage.IsNull())
    {
        m_bgImage.Draw(pDC->GetSafeHdc(), rcClient.left, rcClient.top,
            m_bgImage.GetWidth(), m_bgImage.GetHeight(),
            0, 0, m_bgImage.GetWidth(), m_bgImage.GetHeight());
    }

    if (m_enStyle == TEXT && !m_strText.IsEmpty())
    {
        CRect rcText(rcClient);
        rcText.DeflateRect(m_nX + 2, m_nY + 2);

        CFont font;
        CFont* pOldFont = nullptr;

        if (m_bVerticalText)
        {
            LOGFONT lf;
            GetFont()->GetLogFont(&lf);
            lf.lfEscapement = lf.lfOrientation = 900;
            font.CreateFontIndirect(&lf);
            pOldFont = pDC->SelectObject(&font);
        }
        else
        {
            pOldFont = pDC->SelectObject(GetFont());
        }

        pDC->SetTextColor(m_clrTextColor);
        pDC->SetBkMode(TRANSPARENT);

        // Ensure DT_VCENTER works by including DT_SINGLELINE
        UINT uFormat = m_uTextFormat | DT_END_ELLIPSIS;
        if (uFormat & DT_VCENTER)
            uFormat |= DT_SINGLELINE;

        pDC->DrawText(m_strText, rcText, uFormat);

        if (pOldFont)
        {
            pDC->SelectObject(pOldFont);
            if (m_bVerticalText)
                font.DeleteObject();
        }
    }
}

BEGIN_MESSAGE_MAP(CStaticCtrl, CStatic)
END_MESSAGE_MAP()

void CStaticCtrl::EnableBackgroundImage(bool bEnable)
{
    m_bIsBgImageEnabled = bEnable;
    RedrawWindow();
}

void CStaticCtrl::EnableGradientBackground(bool bEnable)
{
    m_bIsGradientEnabled = bEnable;
    RedrawWindow();
}

void CStaticCtrl::SetStyle(STATIC_STYLE enStyle)
{
    m_enStyle = enStyle;
    RedrawWindow();
}

void CStaticCtrl::SetVerticalText(BOOL bVertical)
{
    m_bVerticalText = bVertical;
    RedrawWindow();
}

void CStaticCtrl::SetTextColor(COLORREF clrTextColor)
{
    m_clrTextColor = clrTextColor;
    RedrawWindow();
}

void CStaticCtrl::SetBkColor(COLORREF clrBkColor)
{
    m_clrBkColor = clrBkColor;
    RedrawWindow();
}

void CStaticCtrl::SetBkColor2(COLORREF clrBkColor2)
{
    m_clrBkColor2 = clrBkColor2;
    RedrawWindow();
}

void CStaticCtrl::SetText(CString strText, UINT uFormat)
{
    m_strText = strText;
    m_uTextFormat = uFormat;
    RedrawWindow();
}

void CStaticCtrl::SetOutLineColor(COLORREF clrOutLine)
{
    m_clrOutLine = clrOutLine;
    RedrawWindow();
}

void CStaticCtrl::SetInLineColor(COLORREF clrInLine)
{
    m_clrInLine = clrInLine;
    RedrawWindow();
}

void CStaticCtrl::SetPadding(INT nX, INT nY)
{
    m_nX = nX;
    m_nY = nY;
    RedrawWindow();
}

void CStaticCtrl::SetBgImage(LPCTSTR imgFilePath)
{
    m_bgImage.Destroy();
    m_bgImage.Load(imgFilePath);
    RedrawWindow();
}