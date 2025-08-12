#include "Drawing.h"
#include <d3d9.h>
#include <LPD3DXFONT.h>
#include "box.h"
#include "box.h"

void Drawing::DrawBorderBox(int x, int y, int w, int h, int thickness, D3DCOLOR Colour, IDirect3DDevice9* pDevice)
{
    // Top horizontal line
    DrawFilledRect(x, y, w, thickness, Colour, pDevice);
    // Left vertical line
    DrawFilledRect(x, y, thickness, h, Colour, pDevice);
    // Right vertical line
    DrawFilledRect(x + w - thickness, y, thickness, h, Colour, pDevice);
    // Bottom horizontal line
    DrawFilledRect(x, y + h - thickness, w + thickness, thickness, Colour, pDevice);
}

void Drawing::DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* dev)
{
    // We create our rectangle to draw on the screen
    D3DRECT BarRect = { x, y, x + w, y + h };
    // We clear that portion of the screen and display our rectangle
    dev->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
}

void Drawing::Draw_Text(LPCSTR TextToDraw, int x, int y, D3DCOLOR Colour, LPD3DXFONT m_font)
{
    // Create a rectangle to indicate where on the screen it should be drawn
    RECT rct = { x, y, 0, 0 }; // Updated to use x, y directly

    // Draw some text
    m_font->DrawText(NULL, TextToDraw, -1, &rct, DT_NOCLIP, Colour);
}
