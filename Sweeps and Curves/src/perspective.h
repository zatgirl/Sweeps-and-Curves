#ifndef ___PERSPECTIVE__H___
#define ___PERSPECTIVE__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "gl_canvas2d.h"

#include "Vector2.h"

class Perspective
{
 public:
    Vector2 matrizPersp[100][300];
    int tam, rot;

    void render(){
        for(int i = 0; i < rot; i++){
            for(int j = 0; j < tam; j++){
                CV::color(4);
                CV::circleFill(matrizPersp[i][j].x, matrizPersp[i][j].y, 4, 10);
            }
        }
        wire();
    }

    Vector2 projeta(Vector3 p, float _d)
   {
       float d = -100;
       Vector2 resp;
       resp.x = (p.x*_d) / p.z;
       resp.y = (p.y*_d) / p.z;
       return resp;
   }

   Vector2 translacao(Vector2 point){
       Vector2 resp;
       resp.x = point.x + 300;
       resp.y = point.y + 200;
       return resp;
   }

   void persp(Vector3 points[][360], int _tam, int _rot, float _d){
       rot = _rot;
       tam = _tam;
      for(int x=0; x < _tam; x++){
         for(int z=0; z < _rot; z++)
         {
             Vector2 temp;
             temp = projeta(points[x][z], _d);
             matrizPersp[x][z] = translacao(temp);
             //printf("matrizPersp[%d][%d] = %.2f, %.2f\n", x, z, matrizPersp[x][z].x, matrizPersp[x][z].y);
         }
      }
   }

   void wire(){
    CV::color(0.7,0.7,0.7);
    for(int y = 0; y < tam; y++){
    for(int x = 0; x < rot; x++){
            CV::line(matrizPersp[y][x], matrizPersp[y][x+1]); //linha horizontal
            CV::line(matrizPersp[y][x], matrizPersp[y+1][x]); //linha vertical
            CV::line(matrizPersp[y][x], matrizPersp[y+1][x+1]); //linha diagonal
        }
    }
}

};

#endif

