#include "TCanvas.h"

TCanvas::TCanvas(Pages *pages, int x, int y, int width, int height, Functor<CallbackType> &draw_cmd)
    : TGuiElement(pages, x, y, width, height, "Canvas"),
      nocmd(),
      draw_cmd(draw_cmd),
      click_cmd(nocmd)
{
    Draw();
}

TCanvas::~TCanvas()
{
}

void TCanvas::setClicked(Functor<CallbackType> &cmd)
{
    click_cmd = cmd;
}

void TCanvas::setDrawed(Functor<CallbackType> &cmd)
{
    draw_cmd = cmd;
}

void TCanvas::Draw()
{
    draw_cmd(surface);
}

bool TCanvas::OnMouseUp()
{
    click_cmd(surface);
    return true;
}
