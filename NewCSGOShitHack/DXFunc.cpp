#include "includes.h"

VOID myDevice::DrawBox(float x, float y, float w, float h, float px, D3DCOLOR color)
{
    D3DXVECTOR2 points[5];
    points[0] = D3DXVECTOR2(x, y);
    points[1] = D3DXVECTOR2(x + w, y);
    points[2] = D3DXVECTOR2(x + w, y + h);
    points[3] = D3DXVECTOR2(x, y + h);
    points[4] = D3DXVECTOR2(x, y);

    dx::lines::espBoxLine->SetWidth(px);
    dx::lines::espBoxLine->Draw(points, 5, color);
    dx::lines::espBoxLine->End();
}

VOID myDevice::DrawRect(int baseX, int baseY, int baseW, int baseH, D3DCOLOR Cor)
{
    D3DRECT BarRect = { baseX, baseY, baseX + baseW, baseY + baseH };
    pDevice->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Cor, 0, 0);
}

VOID myDevice::DrawLine(ID3DXLine* Line, float x1, float y1, float x2, float y2, float width, bool antialias, D3DCOLOR color)
{
    D3DXVECTOR2 linePos[] = { D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2) };

    Line->SetWidth(width);
    Line->SetAntialias(antialias);
    Line->Begin();
    Line->Draw(linePos, 2, color);
    Line->End();
}

VOID myDevice::DrawMessage(LPD3DXFONT &font, unsigned int x, unsigned int y, D3DCOLOR color, LPCSTR Message)
{
    RECT rct;
    rct.left = x;
    rct.right = 1920;
    rct.top = y;
    rct.bottom = rct.top + 200;

    font->DrawTextA(NULL, Message, -1, &rct, 0, color);
}