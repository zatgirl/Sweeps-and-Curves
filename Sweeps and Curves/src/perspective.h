#ifndef ___PERSPECTIVE__H___
#define ___PERSPECTIVE__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "gl_canvas2d.h"

#include "Vector2.h"
#include "fill.h"

Fill *filld;

class Perspective
{
 public:
    Vector2 matrizPersp[100][300];
    Vector2 matrizOrthogonal[100][300];
    std::vector<Vector2> MatrizZBuffer;
    int tam, rot;
    bool _translational = false;

    void render(){
        for(int i = 1; i <= tam; i++){
            for(int j = 1; j <= rot; j++){
                //CV::color(1+j);
                //CV::circleFill(matrizPersp[i][j].x, matrizPersp[i][j].y, 4, 10);
                //filld->fillTriangle((int)matrizPersp[i][j].x, (int)matrizPersp[i][j].y, (int)matrizPersp[i+1][j].x, (int)matrizPersp[i+1][j].y, (int)matrizPersp[i+1][j+1].x, (int)matrizPersp[i+1][j+1].y,4);
                //printf("x0[%d][%d]: %d, y0[%d][%d]: %d, x1[%d][%d]: %d, y1[%d][%d]: %d, x2[%d][%d]: %d, y2[%d][%d]: %d\n", i,j,(int)matrizPersp[i][j].x, i,j,(int)matrizPersp[i][j].y, i+1, j, (int)matrizPersp[i+1][j].x, i+1, j,(int)matrizPersp[i+1][j].y, i+1, j+1,(int)matrizPersp[i+1][j+1].x, i+1, j+1,(int)matrizPersp[i+1][j+1].y);
                //filld->render((int)matrizPersp[i][j].x, (int)matrizPersp[i][j].y, (int)matrizPersp[i+1][j].x, (int)matrizPersp[i+1][j].y, (int)matrizPersp[i+1][j+1].x, (int)matrizPersp[i+1][j+1].y);
            }
        }
        //filld->render(200, 200, 400, 300, 500, 190);

        wire();
    }

    Vector2 projeta(Vector3 p, float _d)
   {
       float d = -100;
           Vector2 resp;
           resp.x = (p.x*_d) / (p.z - 2000);
           resp.y = (p.y*_d) / (p.z - 2000);
       return resp;
   }

   Vector2 translacao(Vector2 point){
       Vector2 resp;
       resp.x = point.x + 600;
       resp.y = point.y + 205;
       return resp;
   }

   Vector2 projetaSpring(Vector3 p, float _d)
   {
       float d = -100;
           Vector2 resp;
           resp.x = (p.x*_d) / (p.z);
           resp.y = (p.y*_d) / (p.z);
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

   void persp(Vector3 points[][360], int _tam, int _rot, float _d, float rotX){
       rot = _rot;
       tam = _tam;
       Vector3 ptemp;
      for(int x=0; x < _tam; x++){
         for(int z=0; z < _rot+1; z++)
         {
             matrizOrthogonal[x][z].set(points[x][z].x, points[x][z].y);
             if(_translational){
                matrizPersp[x][z] = translacao(projetaSpring(points[x][z], _d + 4010));
             } else {
                ptemp = (rotacionaX(points[x][z], rotX));
                matrizPersp[x][z] = translacao(projeta(ptemp, _d));
             }
         }
         if(!_translational){
            matrizOrthogonal[x][_rot+1].set(points[x][1].x, points[x][1].y);
            matrizPersp[x][_rot+1] = matrizPersp[x][1];
         }
      }
   }

   void wire(){
        CV::color(0);
        for(int linha = 0; linha <= tam; linha++){
            for(int col = 0; col <= rot; col++){
                if(_translational){
                    if(col < rot){
                        CV::line(matrizPersp[linha][col].x, matrizPersp[linha][col].y, matrizPersp[linha][col+1].x, matrizPersp[linha][col+1].y); //linha horizontal
                    if((linha < tam - 1))
                        CV::line(matrizPersp[linha][col].x, matrizPersp[linha][col].y, matrizPersp[linha+1][col].x, matrizPersp[linha+1][col].y); //linha vertical
                    }
                    if((col < rot - 1) && (linha < tam - 1)){
                        CV::line(matrizPersp[linha][col].x, matrizPersp[linha][col].y, matrizPersp[linha+1][col+1].x, matrizPersp[linha+1][col+1].y); //linha diagonal
                    }
                    if(((col == rot - 1) && (linha < tam - 1))){
                        CV::line(matrizPersp[linha][col].x, matrizPersp[linha][col].y, matrizPersp[linha+1][col+1].x, matrizPersp[linha+1][col+1].y); //linha diagonal
                    }
                } else {
                    CV::line(matrizPersp[linha][col], matrizPersp[linha][col+1]); //linha horizontal
                    if(linha < tam - 1){
                        CV::line(matrizPersp[linha][col], matrizPersp[linha+1][col]); //linha vertical
                        CV::line(matrizPersp[linha][col], matrizPersp[linha+1][col+1]); //linha diagonal
                    } else if(linha < tam - 1 && (_translational)){
                        CV::line(matrizPersp[linha][col], matrizPersp[0][col]); //linha vertical
                    }
                }
            }
        }
   }

   void wireOrthogonal(){
        CV::color(1,1,1);
        int offsetx = 855, offsety = 60;
        for(int linha = 0; linha <= tam; linha++){
            for(int col = 0; col <= rot; col++){
                if(_translational){
                    if(col < rot){
                        CV::line(matrizOrthogonal[linha][col].x + offsetx, matrizOrthogonal[linha][col].y + offsety, matrizOrthogonal[linha][col+1].x + offsetx, matrizOrthogonal[linha][col+1].y + offsety); //linha horizontal
                    }
                    if((linha < tam - 1)){
                        CV::line(matrizOrthogonal[linha][col].x + offsetx, matrizOrthogonal[linha][col].y + offsety, matrizOrthogonal[linha+1][col].x + offsetx, matrizOrthogonal[linha+1][col].y + offsety); //linha vertical
                    }
                    if((col < rot - 1) && (linha < tam - 1)){
                        CV::line(matrizOrthogonal[linha][col].x + offsetx, matrizOrthogonal[linha][col].y + offsety, matrizOrthogonal[linha+1][col+1].x + offsetx, matrizOrthogonal[linha+1][col+1].y + offsety); //linha diagonal
                    }
                    if(((col == rot - 1) && (linha < tam - 1))){
                        CV::line(matrizOrthogonal[linha][col].x + offsetx, matrizOrthogonal[linha][col].y + offsety, matrizOrthogonal[linha+1][col+1].x + offsetx, matrizOrthogonal[linha+1][col+1].y + offsety); //linha diagonal
                    }
                } else {
                    CV::line(matrizOrthogonal[linha][col].x + offsetx, matrizOrthogonal[linha][col].y + offsety, matrizOrthogonal[linha][col+1].x + offsetx, matrizOrthogonal[linha][col+1].y + offsety); //linha horizontal
                    if((linha < tam - 1)){
                        CV::line(matrizOrthogonal[linha][col].x + offsetx, matrizOrthogonal[linha][col].y + offsety, matrizOrthogonal[linha+1][col].x + offsetx, matrizOrthogonal[linha+1][col].y + offsety); //linha vertical
                        CV::line(matrizOrthogonal[linha][col].x + offsetx, matrizOrthogonal[linha][col].y + offsety, matrizOrthogonal[linha+1][col+1].x + offsetx, matrizOrthogonal[linha+1][col+1].y + offsety); //linha diagonal
                    } else if(linha < tam - 1){
                        CV::line(matrizOrthogonal[linha][col].x + offsetx, matrizOrthogonal[linha][col].y + offsety, matrizOrthogonal[0][col].x + offsetx, matrizOrthogonal[0][col].y + offsety); //linha vertical
                    }
                }
            }
        }
   }

   void zBuffer(){
        MatrizZBuffer = (filld->fillfunction(matrizPersp, tam, rot));
   }
   void drawbuffer(){
        for(int x = 0; x < 1200; x++){
            for(int y = 0; y < 700; y++){
                CV::color(2);
                CV::point(MatrizZBuffer[x+(y*1200)].x, MatrizZBuffer[x+(y*1200)].y);
            }
        }
   }

};

#endif

