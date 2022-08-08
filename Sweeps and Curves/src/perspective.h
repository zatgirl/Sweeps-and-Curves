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
        for(int i = 0; i < rot+1; i++){
            for(int j = 0; j < tam; j++){
                CV::color(1+i);
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
      for(int x=0; x < _rot+1; x++){
         for(int z=0; z < _tam; z++)
         {
             Vector2 temp;
             temp = projeta(points[x][z], _d);
             matrizPersp[x][z] = translacao(projeta(points[x][z], _d));
         }
      }
      for(int i = 0; i < 1; i++){
         for(int j = 0; j < _tam; j++){
            matrizPersp[rot+1][j] = matrizPersp[i][j];
         }
      }
   }

   void wire(){
        CV::color(0.7,0.7,0.7);
        for(int col = 0; col < rot; col++){
            for(int linha = 0; linha < tam; linha++){

                #if 0
                if(linha < tam-1){
                    CV::line(matrizPersp[col][linha], matrizPersp[(col+1)][linha]); //linha vertical
                    CV::line(matrizPersp[col][linha], matrizPersp[(col+1)][(linha+1)%tam]); //linha diagonal
                }
                CV::line(matrizPersp[col][linha], matrizPersp[col][(linha+1)%tam]); //linha horizontal
                #endif

                #if 0
                if (col+1 == rot){
                    CV::line(matrizPersp[col][linha], matrizPersp[0][linha]);
                } else {
                    CV::line(matrizPersp[col][linha], matrizPersp[col+1][linha]);
                }
                if (linha+1 < tam){
                    CV::line(matrizPersp[col][linha], matrizPersp[col][linha+1]);
                }
                #endif

            CV::line(matrizPersp[col][linha], matrizPersp[col][linha+1]); //linha horizontal
            if(col+1 > rot){
                CV::line(matrizPersp[col][linha], matrizPersp[(0)][linha]); //linha vertical
            } else {
                CV::line(matrizPersp[col][linha], matrizPersp[(col+1)][linha]); //linha vertical
            }

            //CV::line(matrizPersp[col][linha], matrizPersp[(col+1)%rot][(linha+1)%tam]); //linha diagonal
            }
        }
       /* for(int i = 0; i < tam && ((i+1) != 0); i ++){

            CV::line(matrizPersp[rot+1][i], matrizPersp[rot+1][(i+1)]); //linha horizontal
            CV::line(matrizPersp[rot+1][i], matrizPersp[0][i]); //linha vertical
            CV::line(matrizPersp[rot+1][i], matrizPersp[0][(i+1)]); //linha diagonal
        }*/
   }

};

#endif

