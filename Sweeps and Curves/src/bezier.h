#ifndef ___BEZIER__H___
#define ___BEZIER__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "gl_canvas2d.h"

#include "Vector2.h"

class BE
{
 public:


    static float Fatorial(int num){
        float res = 1;
        if(num > 0){
            for (int i = 1; i <= num; i++){
                res *= i;
            }
        }
        return res;
    }

    static float CalcBezier(int i, float t, int qntPontos){
        float ni;
        float qnt = qntPontos - 1;

        ni = Fatorial(qnt) / (Fatorial(i) * Fatorial(qnt - i));
        return ni * pow(t, i) * pow(1 - t, qnt - i);
    }

    static void Curva(std::vector <Vector2*> v){
       Vector2 p;
       CV::color(1);
       int quantPontos = v.size();

       for(float t = 0; t < 1; t+=0.001){
          p.set(0,0);
          for(int ponto = 0; ponto < quantPontos; ponto++){
             p = ((*v[ponto]) * CalcBezier(ponto, t, quantPontos) + p);
             CV::color(1,0,0);
             CV::circleFill(*v[ponto], 6, 10);
          }
          CV::color(1,1,1);
          CV::point(p.x,p.y);
       }
    }

    static void Curva(std::vector <Vector3*> v){
       Vector3 p;
       CV::color(1);
       int quantPontos = v.size();

       for(float t = 0; t < 1; t+=0.001){
          p.set(0,0,0);
          for(int ponto = 0; ponto < quantPontos; ponto++){
             p = ((*v[ponto]) * CalcBezier(ponto, t, quantPontos) + p);
             CV::color(1,0,0);
             CV::circleFill(*v[ponto], 6, 10);
          }
          CV::color(3);
          CV::point(p.x,p.y);
       }
    }

};

#endif

