#include <windows.h>

#define NUM 300

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static int iKeep [NUM][4] ;
     HDC        hdcScr, hdcMem ;
     int        cx, cy ;
     HBITMAP    hBitmap ;
     HWND       hwnd ;
     int        i, j, x1, y1, x2, y2 ;

     if (LockWindowUpdate (hwnd = GetDesktopWindow ()))
     {
          hdcScr  = GetDCEx (hwnd, NULL, DCX_CACHE | DCX_LOCKWINDOWUPDATE) ;
          hdcMem  = CreateCompatibleDC (hdcScr) ;
          cx      = GetSystemMetrics (SM_CXSCREEN) / 10 ;
          cy      = GetSystemMetrics (SM_CYSCREEN) / 10 ;
          hBitmap = CreateCompatibleBitmap (hdcScr, cx, cy) ;

          SelectObject (hdcMem, hBitmap) ;

          srand ((int) GetCurrentTime ()) ;

          for (i = 0 ; i < 2   ; i++)
          for (j = 0 ; j < NUM ; j++)
          {
               if (i == 0)
               {
                    iKeep [j] [0] = x1 = cx * (rand () % 10) ;
                    iKeep [j] [1] = y1 = cy * (rand () % 10) ;

                    iKeep [j] [2] = x2 = cx * (rand () % 10) ;
                    iKeep [j] [3] = y2 = cy * (rand () % 10) ;
               }
               else
               {
                    x1 = iKeep [NUM - 1 - j] [0] ;
                    y1 = iKeep [NUM - 1 - j] [1] ;
                    x2 = iKeep [NUM - 1 - j] [2] ;
                    y2 = iKeep [NUM - 1 - j] [3] ;
               }
               BitBlt (hdcMem,  0,  0, cx, cy, hdcScr, x1, y1, SRCCOPY) ;
               BitBlt (hdcScr, x1, y1, cx, cy, hdcScr, x2, y2, SRCCOPY) ;
               BitBlt (hdcScr, x2, y2, cx, cy, hdcMem,  0,  0, SRCCOPY) ;

               Sleep (10) ;
          }

          DeleteDC (hdcMem) ;
          ReleaseDC (hwnd, hdcScr) ;
          DeleteObject (hBitmap) ;

          LockWindowUpdate (NULL) ;
     }
     return FALSE ;
}
