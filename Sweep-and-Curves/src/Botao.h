#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "gl_canvas2d.h"

class Botao{
  float altura, largura, r, g, b;
  int x, y;
  char label[100];

public:
  Botao(int _x, int _y, float _larg, float _alt, char *_label, float _r, float _g, float _b)
  {
     r = _r;    altura  = _alt;          x = _x;
     g = _g;    largura = _larg;         y = _y;
     b = _b;    strcpy(label, _label);
  }

    //Desenha os botões
    void Draw(){
        CV::color(r,g,b); CV::rectFill(x, y, x+largura, y+altura);
        CV::color(0,0,0); CV::text(x+10, y+(altura/3), label);
    }

    //recebe as coordenadas do mouse para tratar clique ou detectar quando o mouse esta em cima do botao
    bool Colidiu(int mx, int my)
    {
        if( mx >= x && mx <= (x + largura) && my >= y && my <= (y + altura) )
        {
            return true;
        }
            return false;
    }
};
#endif
