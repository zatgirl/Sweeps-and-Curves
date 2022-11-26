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

    Perspective(){
        filld = new Fill();
    }

    void render(){
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

   Vector3 rotacionaY(Vector3 p , float ang)
   {
      Vector3 resp;
          resp.x = cos(ang)*p.x + sin(ang)*p.z;
          resp.y = p.y;
          resp.z = -sin(ang)*p.x + cos(ang)*p.z;
      return resp;
   }

   void persp(Vector3 points[][360], int _tam, int _rot, float _d, float rotX){
       rot = _rot;
       tam = _tam;
       Vector3 ptemp;
      for(int x=0; x < _tam; x++){
         for(int z=0; z <= _rot; z++)
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
        Vector2 P1, P2, P3, P4;
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
                    P1.set(matrizPersp[linha][col].x, matrizPersp[linha][col].y);
                    if(col <= rot){
                        P2.set(matrizPersp[linha][col+1].x, matrizPersp[linha][col+1].y);
                    }
                    if(linha < tam - 1){
                        CV::line(matrizPersp[linha][col], matrizPersp[linha+1][col]); //linha vertical
                        P4.set(matrizPersp[linha+1][col].x, matrizPersp[linha+1][col].y);
                        CV::line(matrizPersp[linha][col], matrizPersp[linha+1][col+1]); //linha diagonal
                        P3.set(matrizPersp[linha+1][col+1].x, matrizPersp[linha+1][col+1].y);
                    } else if(linha < tam - 1 && (_translational)){
                        CV::line(matrizPersp[linha][col], matrizPersp[0][col+1]); //linha vertical
                        P3.set(matrizPersp[0][col+1].x, matrizPersp[0][col+1].y);
                    }
                }
                if(!_translational){
                    draw();
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

   void draw(){
        CV::color(0);
        Vector2 P1, P2, P3, P4;
        for(int linha = 0; linha <= tam-1; linha++){
            for(int col = 0; col <= rot-1; col++){
                    P1.set(matrizPersp[linha][col].x, matrizPersp[linha][col].y);
                    if(col <= rot){
                    P2.set(matrizPersp[linha][col+1].x, matrizPersp[linha][col+1].y);
                    }
                    if(linha < tam - 1){

                        P4.set(matrizPersp[linha+1][col].x, matrizPersp[linha+1][col].y);

                        P3.set(matrizPersp[linha+1][col+1].x, matrizPersp[linha+1][col+1].y);

                    } else if(linha < tam - 1 && (_translational)){

                        P3.set(matrizPersp[0][col+1].x, matrizPersp[0][col+1].y);
                    }
                    CV::color(2);
                    drawTriangles(P1,P2,P3);
                    drawTriangles(P1,P3,P4);
           }

        }
   }

   void drawTriangles(Vector2 P1, Vector2 P2, Vector2 P3){
       filld->fillTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y);
   }

};

#endif

