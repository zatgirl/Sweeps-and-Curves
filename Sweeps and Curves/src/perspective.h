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

    void render(Vector2 mouse){
        for(int i = 0; i < tam; i++){

            for(int j = 0; j < rot+1; j++){
                CV::color(1+j);
                //CV::circleFill(matrizPersp[i][j].x, matrizPersp[i][j].y, 4, 10);
            }
        }
        wire();
        whatposition(mouse);
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
         for(int z=0; z < _rot+1; z++)
         {
             Vector2 temp;
             temp = projeta(points[x][z], _d);
             matrizPersp[x][z] = translacao(projeta(points[x][z], _d));
         }
         matrizPersp[x][_rot+1] = matrizPersp[x][1];
      }
   }

   void whatposition(Vector2 position){
        for(int col = 0; col < rot; col++){
            for(int linha = 0; linha < tam; linha++){
                    if(matrizPersp[col][linha].x == position.x && matrizPersp[col][linha].y == position.y){
                        printf("matrizPersp[%d][%d]\n", matrizPersp[col][linha].x, matrizPersp[col][linha].y);
                    }
            }
        }
   }

   void wire(){
        CV::color(0.7,0.7,0.7);
        for(int linha = 0; linha <= tam; linha++){
            for(int col = 0; col <= rot; col++){
                CV::line(matrizPersp[linha][col], matrizPersp[linha][col+1]); //linha horizontal
                if(linha < tam-1){
                    CV::line(matrizPersp[linha][col], matrizPersp[linha+1][col]); //linha vertical
                    CV::line(matrizPersp[linha][col], matrizPersp[linha+1][col+1]); //linha diagonal
                } else if(linha < tam-1){
                    CV::line(matrizPersp[linha][col], matrizPersp[0][col]); //linha vertical
                }

                if(col < rot && linha < tam-1){

                } else {
                    //CV::line(matrizPersp[col][linha], matrizPersp[col+1][0]); //linha diagonal
                }
            }
        }
   }

};

#endif

