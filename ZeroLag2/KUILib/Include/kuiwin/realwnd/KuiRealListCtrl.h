// Copyright (c) 2010 Kingsoft Corporation. All rights reserved.
// Copyright (c) 2010 The KSafe Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Bill Modify it from KingSoft open source bigfilelistctrl.h and bigfilelistctrl.cpp
#ifndef _H_KUIREALLISTCTRL_H
#define _H_KUIREALLISTCTRL_H
#pragma once

//////////////////////////////////////////////////////////////////////////

#include "../../kscgui/kdraw.h"

//////////////////////////////////////////////////////////////////////////

class CKuiRealListHdr;
typedef CWindowImpl<CKuiRealListHdr, CHeaderCtrl> CKuiRealListHdrBase;

//////////////////////////////////////////////////////////////////////////

class CKuiRealListHdr 
    : public CKuiRealListHdrBase
    , public CDoubleBufferImpl<CKuiRealListHdr>
{
public:
    BEGIN_MSG_MAP(CKuiRealListHdr)
        MSG_WM_SIZE(OnSize)
        MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
        MESSAGE_HANDLER(HDM_LAYOUT, OnHdmLayout)
        REFLECTED_NOTIFY_CODE_HANDLER(HDN_ENDTRACK, OnEndTrack)
        CHAIN_MSG_MAP(CDoubleBufferImpl<CKuiRealListHdr>)
    END_MSG_MAP()

    void Init()
    {
        GetClientRect(&m_rcClient);
    }

    BOOL SubclassWindow(HWND hWnd)
    {
        BOOL retval = FALSE;
        retval = CKuiRealListHdrBase::SubclassWindow(hWnd);

        Init();
        return retval;
    }

    LRESULT OnEndTrack(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
    {
        GetParent().InvalidateRect(NULL);
        return 0L;
    }

    LRESULT OnHdmLayout(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        LRESULT retval;
        HDLAYOUT* pHdLayout = (HDLAYOUT*)lParam;

        retval = DefWindowProc(uMsg, wParam, lParam);
        if (pHdLayout)
        {
            pHdLayout->pwpos->cy = 24;
            pHdLayout->prc->top = 24;
            pHdLayout->prc->bottom -= 24;
        }

        return 0;
    }

    LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        bHandled = TRUE;
        return 0;
    }

    void DoPaint(CDCHandle dc)
    {
        CRect rcTemp;
        CFontHandle font = KuiFontPool::GetFont(FALSE, FALSE, FALSE);
        CRect rcSplit, rcHalf;
        int nItemCount = GetItemCount();

        GetClientRect(&m_rcClient);
        rcTemp = m_rcClient;
        rcTemp.bottom -= 1;
        rcHalf = rcTemp;
        rcHalf.bottom = rcTemp.Height() / 2;
        DrawGradualColorRect(dc, rcHalf, RGB(255,255,255), RGB(248,253,255));
        rcHalf.top = rcHalf.bottom;
        rcHalf.bottom = m_rcClient.bottom - 1;
        DrawGradualColorRect(dc, rcHalf, RGB(229,246,254), RGB(238,249,255));
        rcTemp.top = m_rcClient.bottom - 1;
        rcTemp.bottom = m_rcClient.bottom;
        dc.FillSolidRect(rcTemp, RGB(150,174,202));

        dc.SetBkMode(TRANSPARENT);
        dc.SetTextColor(RGB(0,0,0));
        dc.SelectFont(font);
        for (int i = 0; i < nItemCount; ++i)
        {
            HDITEM hdi;
            CString strText;

            hdi.mask = HDI_TEXT;
            hdi.pszText = strText.GetBuffer(MAX_PATH);
            hdi.cchTextMax = MAX_PATH;

            GetItem(i, &hdi);
            strText.ReleaseBuffer();
            GetItemRect(i, rcTemp);

            dc.DrawText(strText, strText.GetLength(), rcTemp, 
                DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

            rcSplit.left = rcTemp.right - 2;
            rcSplit.right = rcTemp.right - 1;
            rcSplit.top = rcTemp.top + 4;
            rcSplit.bottom = rcTemp.bottom - 3;
            dc.FillSolidRect(rcSplit, RGB(162,186,212));
            rcSplit.left = rcTemp.right - 1;
            rcSplit.right = rcTemp.right - 0;
            dc.FillSolidRect(rcSplit, RGB(255,255,255));
        }
    }

    void OnSize(UINT nType, CSize size)
    {
        GetClientRect(&m_rcClient);
    }

private:
    RECT m_rcClient;
};

//////////////////////////////////////////////////////////////////////////

#define WM_BIGFILE_LIST_LINK        (WM_USER+101)
#define WM_BIGFILE_LIST_DBCLICK     (WM_USER+102)
#define WM_BIGFILE_LIST_CONTEXT     (WM_USER+103)
#define WM_BIGFILE_LIST_MORE        (WM_USER+104)

//////////////////////////////////////////////////////////////////////////

class CKuiRealListCtrl;
typedef CWindowImpl<CKuiRealListCtrl, CListViewCtrl> CKuiRealListCtrlBase;

//////////////////////////////////////////////////////////////////////////

typedef struct tagLinkInfo {
    CString strLink;
    CRect rcLink;
} LinkInfo;

//////////////////////////////////////////////////////////////////////////

class CKuiRealListCtrl
    : public CKuiRealListCtrlBase
    , public COwnerDraw<CKuiRealListCtrl>
{
public:
	//////////////////////////////////////////////////////////////////////////
	// Impletment
	//////////////////////////////////////////////////////////////////////////

	//CIconCache g_IconCache;

	//////////////////////////////////////////////////////////////////////////

	CKuiRealListCtrl()
	{
		//m_pOwner        = pOwner;
		m_nItemHeight   = 24;
		m_nHeaderHeight = 24;
		m_nHotItem      = -1;
		m_nHotLink      = -1;
		m_bMoreLink     = FALSE;
		m_bSysFilter    = TRUE;
	}

	~CKuiRealListCtrl()
	{

	}

	//////////////////////////////////////////////////////////////////////////

	BOOL OnEraseBkgnd(CDCHandle dc)
	{
		CRect rcClient;
		GetClientRect(rcClient);
		dc.FillSolidRect(rcClient, RGB(0xff, 0xff, 0xff));
		return TRUE;
	}

	void Init()
	{
		m_wndToolTip.Create(m_hWnd);
		m_wndToolTip.SetMaxTipWidth(400);
		m_wndToolTip.AddTool(m_hWnd);
		m_wndToolTip.Activate(FALSE);
		m_wndToolTip.SetDelayTime(0, 1000);

		ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
		m_hdr.SubclassWindow(GetHeader());
		m_hdr.SetDlgCtrlID(1000);
		//m_hdr.EnableWindow(FALSE);
	}

	BOOL SubclassWindow(HWND hWnd)
	{
		BOOL retval = FALSE;
		retval = CKuiRealListCtrlBase::SubclassWindow(hWnd);
		Init();
		return retval;
	}

	void AddLink(const CString& strLink)
	{
		LinkInfo link;
		link.strLink = strLink;
		m_vLinks.push_back(link);
	}

	void SetNotifyHwnd(HWND hNotifyWnd)
	{
		m_hNotifyWnd = hNotifyWnd;
	}

	void SetMoreItem(DWORD dwMoreItems)
	{
		m_dwMoreItems = dwMoreItems;
	}

	void SetSysFilterEnable(BOOL bEnable)
	{
		m_bSysFilter = bEnable;
	}

	BOOL GetSysFilterEnable()
	{
		return m_bSysFilter;
	}

	int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
	{
		return 0;
	}

	void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct)
	{

	}

	BOOL DeleteItem(int nItem)
	{
		return __super::DeleteItem(nItem);
	}

	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
	{
		DoDrawItem(lpDrawItemStruct->hDC, lpDrawItemStruct);
	}
    
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
	{
		lpMeasureItemStruct->itemHeight = m_nItemHeight;
	}

protected:
	LRESULT OnToolTipEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (m_wndToolTip.IsWindow())
		{
			MSG msg = { m_hWnd, uMsg, wParam, lParam };

			m_wndToolTip.RelayEvent(&msg);
		}

		SetMsgHandled(FALSE);

		return 0;
	}

	LRESULT OnMouseLeave()
	{
		return 0;
	}

	void OnVScroll(UINT nSBCode, UINT nPos, HWND hWnd)
	{
		if (SB_TOP == nSBCode || SB_ENDSCROLL == nSBCode)
		{
			Invalidate();
		}

		SetMsgHandled(FALSE);
	}

	LRESULT OnMouseWhell(UINT fwKey, short zDela,CPoint pt)
	{
		SetMsgHandled(FALSE);

		return 0;
	}

	void OnMouseMove(UINT nFlags, CPoint point)
	{
		int nItem, nLink;
		nLink = IsMouseInLink(point, nItem);

		if (-1 == nItem)
		{
			m_wndToolTip.Activate(FALSE);
			goto clean0;
		}

		if (nLink != -1)
		{
			m_nHotItem = nItem;
			m_nHotLink = nLink;
		}
		else
		{
			m_nHotItem = -1;
			m_nHotLink = -1;
		}

	clean0:
		IsMouseInMore(point, nItem);
		SetMsgHandled(FALSE);
	}

	void DoDrawItem(CDCHandle dc, LPDRAWITEMSTRUCT lpDrawItemStruct)
	{
		CRect rcItem = lpDrawItemStruct->rcItem;
		size_t idx = (size_t)lpDrawItemStruct->itemData;
		int nItem = lpDrawItemStruct->itemID;
		BOOL bSelect = lpDrawItemStruct->itemState & ODS_SELECTED;
		CRect rcDraw;


		CString strItem;
		int nCurrentEnd = rcItem.left;
		CRect rcClient;
		CFontHandle underlineFont = KuiFontPool::GetFont(FALSE, TRUE, FALSE);
		CFontHandle normalFont = KuiFontPool::GetFont(FALSE, FALSE, FALSE);

		// 绘制背景
		{
			rcDraw = rcItem;
			GetClientRect(rcClient);
			if (rcClient.right > rcDraw.right)
				rcDraw.right = rcClient.right;
			dc.FillSolidRect(rcDraw, RGB(0xff,0xff,0xff));
		}

		if (idx == -1)
		{
			CString strNone;
			dc.SelectFont(normalFont);
			dc.SetTextColor(RGB(0, 0, 0));
			strNone = _T("没有任何项目。");
			rcDraw = rcItem;
			dc.FillSolidRect(rcDraw, RGB(0xff, 0xff, 0xff));
			rcDraw.left = rcItem.left + GetColumnWidth(0) + GetColumnWidth(1);
			rcDraw.right = rcDraw.left + GetColumnWidth(2);
			dc.DrawText(strNone, strNone.GetLength(), rcDraw, DT_LEFT|DT_BOTTOM|DT_SINGLELINE|DT_END_ELLIPSIS);
			return;
		}

		rcDraw = rcItem;
		dc.SetTextColor(RGB(0,0,0));
		if (bSelect)
		{
			CPen penBorder;
			CBrush brushBk;
			CRect rcSelect = rcDraw;

			penBorder.CreatePen(PS_SOLID, 1, RGB(0x7d, 0xa2, 0xce));
			brushBk.CreateSolidBrush(RGB(0xeb, 0xf4, 0xfd));
			dc.SelectPen(penBorder);
			dc.SelectBrush(brushBk);
			dc.RoundRect(rcSelect, CPoint(3, 3));
			rcSelect.left += 2;
			rcSelect.right -= 2;
			rcSelect.top += 2;
			rcSelect.bottom -= 2;
			DrawGradualColorRect(dc, rcSelect, RGB(0xdd, 0xec, 0xfd), RGB(0xc2, 0xdc, 0xfd));
		}
		else
		{
			dc.FillSolidRect(rcDraw, RGB(0xff, 0xff, 0xff));
		}
		
		dc.SetBkMode(TRANSPARENT);

		// 绘制项目
		int nColCount = m_hdr.GetItemCount();
		rcDraw = rcItem;
		for( int nCol = 0; nCol<nColCount; ++nCol )
		{
			rcDraw.left = nCurrentEnd;
			nCurrentEnd += GetColumnWidth( nCol );
			rcDraw.right = nCurrentEnd;
			GetItemText( nItem, nCol, strItem );
			dc.DrawText(strItem, strItem.GetLength(), rcDraw, DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_END_ELLIPSIS );

		}

		// 绘制控制
		rcDraw.left = nCurrentEnd;
		nCurrentEnd += GetColumnWidth(3);
		rcDraw.right = nCurrentEnd;

		if (rcDraw.Width() > 4)
		{
			CRect rcLink;
			for (size_t i = 0; i < m_vLinks.size(); ++i)
			{
				CString strLink = m_vLinks[i].strLink;
				rcLink = rcDraw;
				rcLink.left = rcDraw.left + 4 + 40 * (long)i;
				rcLink.top += 4;
				rcLink.bottom += 4;
				dc.SelectFont(underlineFont);
				dc.SetTextColor(RGB(0x4d, 0x70, 0x96));
				dc.DrawText(strLink, strLink.GetLength(), rcLink, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
				if (rcLink.right > rcDraw.right)
					rcLink.right = rcDraw.right;
				dc.DrawText(strLink, strLink.GetLength(), rcLink, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);
				rcLink.top = (rcLink.top - m_nHeaderHeight) % m_nItemHeight;
				rcLink.bottom = (rcLink.bottom - m_nHeaderHeight) % m_nItemHeight;
				m_vLinks[i].rcLink = rcLink;
			}
		}
		
	}


	void OnLButtonUp(UINT nFlags, CPoint point)
	{

	}

	void OnRButtonDown(UINT nFlags, CPoint point)
	{
		int nItem = HitTest(point);
		if (nItem != -1)
		{
			SetMsgHandled(TRUE);
			::PostMessage(m_hNotifyWnd, WM_BIGFILE_LIST_CONTEXT, nItem, 0);
		}

		SetMsgHandled(FALSE);
	}

	void OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		int nItem = HitTest(point);

		if (nItem != -1)
		{
			::PostMessage(m_hNotifyWnd, WM_BIGFILE_LIST_DBCLICK, nItem, 0);
		}

		SetMsgHandled(FALSE);
	}

	void OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (m_bMoreLink)
		{
			::PostMessage(m_hNotifyWnd, WM_BIGFILE_LIST_MORE, 0, 0);
		}

		if (m_nHotLink != -1 && m_nHotItem != -1)
		{
			::PostMessage(m_hNotifyWnd, WM_BIGFILE_LIST_LINK, m_nHotItem, m_nHotLink);
		}

		SetMsgHandled(FALSE);
	}

	//////////////////////////////////////////////////////////////////////////

	int HitTest(CPoint pt)
	{
		LVHITTESTINFO hitinfo;

		hitinfo.pt = pt;
		return __super::HitTest(&hitinfo);
	}

	//////////////////////////////////////////////////////////////////////////

	BOOL IsMouseInMore(CPoint pt, int& nItem)
	{
		BOOL retval = FALSE;

		nItem = HitTest(pt);
		if (-1 == nItem)
			goto clean0;

		if (!m_dwMoreItems)
			goto clean0;

		if (nItem != GetItemCount() - 1)
			goto clean0;

		pt.y = (pt.y - m_nHeaderHeight) % m_nItemHeight;

		if (PtInRect(m_rcMore, pt))
		{
			retval = TRUE;
			SetCursor(LoadCursor(NULL, IDC_HAND));
			goto clean0;
		}

	clean0:
		m_bMoreLink = retval;
		return retval;
	}

	int IsMouseInLink(CPoint pt, int& nItem)
	{
		int retval = -1;
		CPoint pt2 = pt;
		size_t i;

		nItem = HitTest(pt);
		if (-1 == nItem)
			goto clean0;
	        
		pt2.y = (pt2.y - m_nHeaderHeight) % m_nItemHeight;

		for (i = 0; i < m_vLinks.size(); ++i)
		{
			if (PtInRect(m_vLinks[i].rcLink, pt2))
			{
				retval = (int)i;
				SetCursor(LoadCursor(NULL, IDC_HAND));
				goto clean0;
			}
		}

	clean0:
		return retval;
	}

protected:
    CToolTipCtrl m_wndToolTip;
    HWND m_hNotifyWnd;
    void* m_pOwner;
    std::vector<LinkInfo> m_vLinks;
    CRect m_rcMore;
    int m_nItemHeight;
    int m_nHeaderHeight;
    CKuiRealListHdr m_hdr;
    int m_nHotItem;
    int m_nHotLink;
    BOOL m_bMoreLink;
    DWORD m_dwMoreItems;
    CString m_strTip;
    BOOL m_bSysFilter;

	BEGIN_MSG_MAP_EX(CKuiRealListCtrl)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_RBUTTONDOWN(OnRButtonDown)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST, WM_MOUSELAST, OnToolTipEvent)
        MSG_WM_ERASEBKGND(OnEraseBkgnd)
        CHAIN_MSG_MAP_ALT(COwnerDraw<CKuiRealListCtrl>,1)
    END_MSG_MAP()

};



#endif