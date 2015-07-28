// Foo.cpp : Implementation of CFoo

#include "stdafx.h"
#include <atlimage.h>
#include < atlenc.h>
#include <gdiplus.h>
#include <comutil.h>
#include "Foo.h"

#pragma comment(lib,"comsuppw.lib")

#pragma comment(lib,"kernel32.lib")

// CFoo


STDMETHODIMP CFoo::PicValue(BSTR* na)
{
       // TODO: Add your implementation code here
HDC hdcSrc = GetDC(NULL);
    int nBitPerPixel = GetDeviceCaps(hdcSrc, BITSPIXEL);
    int nWidth = GetDeviceCaps(hdcSrc, HORZRES);
    int nHeight = GetDeviceCaps(hdcSrc, VERTRES);
    CImage image;
    image.Create(nWidth, nHeight, nBitPerPixel);
    BitBlt(image.GetDC(), 0, 0, nWidth, nHeight, hdcSrc, 0, 0, SRCCOPY);
    ReleaseDC(NULL, hdcSrc);
    image.ReleaseDC();
        IStream * pStmImage   = NULL ;
    HGLOBAL   hMemBmp = GlobalAlloc (GMEM_MOVEABLE ,0);// ����һ��Ĭ�϶ѣ�����һ���ڴ������
    if (hMemBmp == NULL )
    return  S_OK;
    CreateStreamOnHGlobal (hMemBmp , FALSE , &pStmImage ); // ���ڴ�����Ϊ������ʼ 
    if (pStmImage == NULL ){
        GlobalFree (hMemBmp );
        return S_OK ;
   }
    image.Save(pStmImage, Gdiplus::ImageFormatJPEG);
    BYTE * pbyBmp = (BYTE *)GlobalLock (hMemBmp );// ��һ���ڴ������ת����һ��ָ��
    int   msize = GlobalSize (hMemBmp );
        BYTE* lpBuf=new BYTE[msize];// �������ݿռ�
         memcpy (lpBuf ,pbyBmp ,msize );  // �õ��ļ�������
        int nSrcLen = strlen((char*)lpBuf);
        int nDestLen = Base64EncodeGetRequiredLength(msize);
          int* mm=&nDestLen;
        LPSTR lpszDest = new char[nDestLen];
        Base64Encode((BYTE*)lpBuf, msize, lpszDest, mm);  
         *na=_com_util::ConvertStringToBSTR(lpszDest);
         // �ͷ���
    if (pStmImage != NULL ){
          pStmImage -> Release ();
          pStmImage = NULL ;
    }
    // �ͷſռ�
if ( lpBuf != NULL )
{   
    delete []lpBuf ;
    lpBuf = NULL ;
}
// �ͷŶѿռ�
if (hMemBmp != NULL )
{
    GlobalUnlock (hMemBmp );
    GlobalFree (hMemBmp );
    hMemBmp = NULL ;
}
if (image )
{
    image .Detach ();
    image .Destroy ();
}

        return S_OK;
}
