/*========================================================

 XephTools - Clipboard
 Copyright (C) 2022 Jon Bogert (jonbogert@gmail.com)

 This software is provided 'as-is', without any express or implied warranty.
 In no event will the authors be held liable for any damages arising from the use of this software.

 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely,
 subject to the following restrictions:

 1. The origin of this software must not be misrepresented;
	you must not claim that you wrote the original software.
	If you use this software in a product, an acknowledgment
	in the product documentation would be appreciated but is not required.

 2. Altered source versions must be plainly marked as such,
	and must not be misrepresented as being the original software.

 3. This notice may not be removed or altered from any source distribution.

========================================================*/


#ifndef XE_CLIPBOARD_H
#define XE_CLIPBOARD_H

#include <string>
#include <vector>
#include <windows.h>

namespace xe
{
	bool CopyToClipboard(const std::string& str)
	{
        if (!OpenClipboard(NULL))
	    {
            return false;
        }
	    
        if (!EmptyClipboard())
	    {
            CloseClipboard();
            return false;
        }
	    
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, str.size() + 1);
        if (!hMem) 
        {
            CloseClipboard();
            return false;
        }
	    
        void* pMem = GlobalLock(hMem);
        if (!pMem)
	    {
            GlobalFree(hMem);
            CloseClipboard();
            return false;
        }
	    
        memcpy(pMem, str.c_str(), str.size() + 1);
        GlobalUnlock(hMem);
	    
        if (SetClipboardData(CF_TEXT, hMem) == NULL)
	    {
            GlobalFree(hMem);
            CloseClipboard();
            return false;
        }
	    
        CloseClipboard();
        return true;
	}
	
	bool CopyToClipboard(const std::vector<unsigned char>& bytes)
	{
        if (!OpenClipboard(NULL))
	    {
            return false;
        }
	    
        if (!EmptyClipboard())
	    {
            CloseClipboard();
            return false;
        }
	    
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, bytes.size());
        if (!hMem) 
        {
            CloseClipboard();
            return false;
        }
	    
        void* pMem = GlobalLock(hMem);
        if (!pMem)
	    {
            GlobalFree(hMem);
            CloseClipboard();
            return false;
        }
	    
        memcpy(pMem, bytes.data(), bytes.size());
        GlobalUnlock(hMem);
	    
        if (SetClipboardData(CF_TEXT, hMem) == NULL)
	    {
            GlobalFree(hMem);
            CloseClipboard();
            return false;
        }
	    
        CloseClipboard();
        return true;
	}
}

#endif //!XE_CLIPBOARD_H