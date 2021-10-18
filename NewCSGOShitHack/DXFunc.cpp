#include "includes.h"

void HACK::InitLines(LPDIRECT3DDEVICE9& pDevice)
{
    D3DXCreateLine(pDevice, &DXLines::Line);
    D3DXCreateLine(pDevice, &DXLines::p_Line);

    D3DXCreateLine(pDevice, &DXLines::BodyLine);
    D3DXCreateLine(pDevice, &DXLines::rLegLine);
    D3DXCreateLine(pDevice, &DXLines::lLegLine);
    D3DXCreateLine(pDevice, &DXLines::rArmLine);
    D3DXCreateLine(pDevice, &DXLines::lArmLine);

    D3DXCreateLine(pDevice, &DXLines::HealthBarLine);
    D3DXCreateLine(pDevice, &DXLines::ArmorBarLine);
}

void HACK::DrawRect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9& pDevice)
{
    D3DRECT rect = { x, y, x + w, y + h };
    pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void HACK::DrawBones(ID3DXLine* _Line, DWORD Entity, std::vector<int> Bones, float thickness)
{
    int VecSize = Bones.size();

    for (int i = 0; i < (VecSize - 1); i++) 
    {
        Vec3 BonePosition1 = Game.GetPlayerBonePos(Entity, Bones[i]);
        Vec3 BonePosition2 = Game.GetPlayerBonePos(Entity, Bones[i + 1]);
        Vec3 BonePos1ToScreen;
        Vec3 BonePos2ToScreen;

        Game.WorldToScreen(BonePosition1, BonePos1ToScreen);
        Game.WorldToScreen(BonePosition2, BonePos2ToScreen);

        if (BonePosition1.z >= 0.01f && BonePosition2.z >= 0.01)
        {
            DrawLine(_Line, BonePosition1.x, BonePosition1.y, BonePosition2.x, BonePosition2.y, config::esp::LineWidth, true, D3DCOLOR_COLORVALUE(config::esp::DX_ESP[0], config::esp::DX_ESP[1], config::esp::DX_ESP[2], 1));
        }
    }
}

void HACK::DrawBox(float x, float y, float w, float h, float px, D3DCOLOR color)
{
    D3DXVECTOR2 points[5];
    points[0] = D3DXVECTOR2(x, y);
    points[1] = D3DXVECTOR2(x + w, y);
    points[2] = D3DXVECTOR2(x + w, y + h);
    points[3] = D3DXVECTOR2(x, y + h);
    points[4] = D3DXVECTOR2(x, y);

    DXLines::p_Line->SetWidth(px);
    DXLines::p_Line->Draw(points, 5, color);
    DXLines::p_Line->End();
}

void HACK::DrawRect(LPDIRECT3DDEVICE9& pDevice, int baseX, int baseY, int baseW, int baseH, D3DCOLOR Cor)
{
    D3DRECT BarRect = { baseX, baseY, baseX + baseW, baseY + baseH };
    pDevice->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Cor, 0, 0);
}

void HACK::DrawLine(ID3DXLine* _Line, float x1, float y1, float x2, float y2, float width, bool antialias, D3DCOLOR color)
{
    D3DXVECTOR2 linePos[] = { D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2) };

    _Line->SetWidth(width);
    _Line->SetAntialias(antialias);
    _Line->Begin();
    _Line->Draw(linePos, 2, color);
    _Line->End();
}

void HACK::DrawMessage(LPD3DXFONT& font, unsigned int x, unsigned int y, D3DCOLOR color, LPCSTR Message)
{
    RECT rct;
    rct.left = x;
    rct.right = 1920;
    rct.top = y;
    rct.bottom = rct.top + 200;

    font->DrawTextA(NULL, Message, -1, &rct, 0, color);
}