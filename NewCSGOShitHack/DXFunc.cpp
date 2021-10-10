#include "includes.h"

void HACK::DrawRect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9& pDevice)
{
    D3DRECT rect = { x, y, x + w, y + h };
    pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void HACK::DrawBox(float x, float y, float w, float h, float px, D3DCOLOR color, LPDIRECT3DDEVICE9& pDevice)
{
    ID3DXLine* p_Line;

    D3DXCreateLine(pDevice, &p_Line);

    D3DXVECTOR2 points[5];
    points[0] = D3DXVECTOR2(x, y);
    points[1] = D3DXVECTOR2(x + w, y);
    points[2] = D3DXVECTOR2(x + w, y + h);
    points[3] = D3DXVECTOR2(x, y + h);
    points[4] = D3DXVECTOR2(x, y);

    p_Line->SetWidth(px);
    p_Line->Draw(points, 5, color);
    p_Line->End();
    p_Line->Release();
}

void HACK::DrawLine(float x1, float y1, float x2, float y2, float width, bool antialias, D3DCOLOR color, LPDIRECT3DDEVICE9& pDevice)
{
    ID3DXLine* Line;
    D3DXCreateLine(pDevice, &Line);
    D3DXVECTOR2 linePos[] = { D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2) };
    Line->SetWidth(width);
    Line->SetAntialias(antialias);
    Line->Begin();
    Line->Draw(linePos, 2, color);
    Line->End();
    Line->Release();
}