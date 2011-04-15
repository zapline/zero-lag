/*
作者： 
日期： 2011-03-13
功能： 
*/
#ifndef _H_EXTENTWINDOW_H
#define _H_EXTENTWINDOW_H

#include "../KuiLib/Include/wtlhelper/whwindow.h"

template <class T, int BorderSize=5 >
class CWHSizeableRoundRect : public CWHRoundRectFrameHelper<T>
{
public:
    BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0)
    {
        BOOL bHandled = TRUE;

        switch(dwMsgMapID)
        {
        case 0:
            switch (uMsg)
			{
			case WM_SIZE:
				CWHRoundRectFrameHelper<T>::OnSize((UINT)wParam, _WTYPES_NS::CSize(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
                lResult = 0;
				break;
			case WM_CREATE:
				{
					DWORD nStyle = GetWindowLong( hWnd, GWL_STYLE );
					if( nStyle & WS_THICKFRAME )
					{
						nStyle &= ~WS_THICKFRAME;
						SetWindowLong( hWnd, GWL_STYLE, nStyle );
					}
				}
				break;
			case WM_LBUTTONDOWN:
				{
					int x = GET_X_LPARAM(lParam);
					int y = GET_Y_LPARAM(lParam);
					if( x<BorderSize )
					{
						if( y<BorderSize )
							SendMessage( hWnd, WM_SYSCOMMAND, SC_SIZE | 4, 0 );
						else if( y>m_sizeWnd.cy-BorderSize )
							SendMessage( hWnd, WM_SYSCOMMAND, SC_SIZE | 7, 0 );
						else
							SendMessage( hWnd, WM_SYSCOMMAND, SC_SIZE | 1, 0 );
					}
					else if( x>m_sizeWnd.cx-BorderSize )
					{
						if( y<BorderSize )
							SendMessage( hWnd, WM_SYSCOMMAND, SC_SIZE | BorderSize, 0 );
						else if( y>m_sizeWnd.cy-BorderSize )
							SendMessage( hWnd, WM_SYSCOMMAND, SC_SIZE | 8, 0 );
						else
							SendMessage( hWnd, WM_SYSCOMMAND, SC_SIZE | 2, 0 );
					}
					else
					{
						if( y<BorderSize )
							SendMessage( hWnd, WM_SYSCOMMAND, SC_SIZE | 3, 0 );
						else if( y>m_sizeWnd.cy-BorderSize )
							SendMessage( hWnd, WM_SYSCOMMAND, SC_SIZE | 6, 0 );
					}
					
				}
				break;
			case WM_SETCURSOR:
				{
					POINT pt;
					GetCursorPos( &pt );
					ScreenToClient( hWnd, &pt );
					
					if( pt.x<BorderSize )
					{
						if( pt.y<BorderSize )
							::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));
						else if( pt.y>m_sizeWnd.cy-BorderSize )
							::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));
						else
							::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));

						return TRUE;
					}
					else if( pt.x>m_sizeWnd.cx-BorderSize )
					{
						if( pt.y<BorderSize )
							::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));
						else if( pt.y>m_sizeWnd.cy-BorderSize )
							::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));
						else
							::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
						return TRUE;
					}
					else
					{
						if( pt.y<BorderSize )
						{
							::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));
							return TRUE;
						}
						else if( pt.y>m_sizeWnd.cy-BorderSize )
						{
							::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));
							return TRUE;
						}
						
					}

				}
				break;
			}
			
        }
        return FALSE;
    }

	
};

#endif
