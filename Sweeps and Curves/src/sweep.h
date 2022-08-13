#ifndef ___SWEEP__H___
#define ___SWEEP__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "gl_canvas2d.h"

#include "Vector2.h"
#include "Vector3.h"
#include "perspective.h"

class Sweep
{
 public:
    int mouseX, mouseY, mouseSt;
    int rot, tam;
    Vector3 matrizPoints[100][360];
    Vector3 matrizPointsRotY[100][360];
    std::vector <Vector2*> ControlPoints;
    std::vector <Vector2*> EstimatedPoints;
    bool _translational = false;


   Vector3 rotacionaY(Vector3 p , float ang)
   {
      Vector3 resp;
          resp.x = cos(ang)*p.x + sin(ang)*p.z;
          resp.y = p.y;
          resp.z = -sin(ang)*p.x + cos(ang)*p.z;
      return resp;
   }

   Vector3 rotacionaX(Vector3 p , float ang)
   {
      Vector3 resp;
          resp.x = p.x;
          resp.y = cos(ang)*p.y - sin(ang)*p.z;
          resp.z = sin(ang)*p.y + cos(ang)*p.z;
      return resp;
   }

   Vector3 translada(Vector3 p, Vector3 offset)
   {
       Vector3 resp;
       resp.x = p.x + offset.x;
       resp.y = p.y + offset.y;
       resp.z = p.z + offset.z;
       return resp;
   }

    void CreateSweep(std::vector<Vector3> points, float _z, int rotacoes, int _amountSpiralSpring, float _offsetHeightSpring, float rotX){
        float ang = 0.0f;
        int stepsweep = 360/rotacoes;
        int maiorY= - 300, menorY=300;
        Vector3 ptemp;
        for(int i = 0; i < points.size(); i++){
            ptemp = (points[i]);
            matrizPoints[i][0] = ptemp;
            menorY = (ptemp.x < menorY) ? ptemp.x : menorY;
            maiorY = (ptemp.y < maiorY) ? ptemp.y : maiorY;
        }
        //int tamanho = maiorY - menorY;
        if(_translational){
            for(int linha = 0; linha < points.size(); linha ++){
                for(int i = 0, col = 1; i < 360; i += stepsweep, col ++){
                    ang = (PI * i)/(390/_amountSpiralSpring);
                    matrizPoints[linha][col] = rotacionaY(matrizPoints[linha][0], ang);
                    matrizPoints[linha][col] = translada(matrizPoints[linha][col], Vector3(0,(col+5+(i*_offsetHeightSpring)), _z+4010));
                    rot = col;
                }
                tam = points.size();
            }
        } else {
            for(int linha = 0; linha < points.size(); linha ++){
                for(int i = 0, col = 1; i < 360; i += stepsweep, col ++){
                    ang = ((PI * i)/180) + rotX;
                    matrizPoints[linha][col] = rotacionaY(matrizPoints[linha][0], ang);
                    matrizPoints[linha][col] = translada(matrizPoints[linha][col], Vector3(0,0,0));
                    rot = col;
                }
                tam = points.size();
            }
        }
    }


};

#endif


