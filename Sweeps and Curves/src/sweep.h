#ifndef ___SWEEP__H___
#define ___SWEEP__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "gl_canvas2d.h"

#include "Vector2.h"
#include "Vector3.h"
#include "bezier.h"
#include "perspective.h"

class Sweep
{
 public:
    int mouseX, mouseY, mouseSt;
    int rot, tam;
    Vector3 matrizPoints[100][360];
    std::vector <Vector2*> ControlPoints;
    std::vector <Vector2*> EstimatedPoints;
    bool clean = false;

    void render(){
        /*if(clean){
            ControlPoints.clear();
            EstimatedPoints.clear();
            clean = false;
        }*/

        if(mouseSt == 0){
            //GetControlPoints();
        }

        if(ControlPoints.size() > 3){
           //BE::Curva(ControlPoints);
        }
    }

    void GetControlPoints(){
        int i;

        //if(mouseSt == 0){
            //ControlPoints.push_back(new Vector2 (mouseX,mouseY));
           // printf("%d, %d\n", *ControlPoints[i]);
            i++;
        //}
    }

   Vector3 rotacionaY(Vector3 p , float ang)
   {
      Vector3 resp;
          resp.x = cos(ang)*p.x + sin(ang)*p.z;
          resp.y = p.y;
          resp.z = -sin(ang)*p.x + cos(ang)*p.z;
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

    void CreateSweep(std::vector<Vector3> points){
        float ang = 0.0f;
        Vector3 ptemp;
        for(int i = 0; i < points.size(); i++){
            ptemp = (points[i]);
            matrizPoints[i][0] = ptemp;
        }
        //printf("for 1 sweep\n");
        for(int i = 0, col = 1; i < 360; i += 45, col ++){
            ang = (PI * i)/180;
            for(int linha = 0; linha < points.size(); linha ++){
                matrizPoints[linha][col] = rotacionaY(matrizPoints[linha][0], ang);
                matrizPoints[linha][col] = translada(matrizPoints[linha][col], Vector3(0,0,-20));
            }
            rot = col;
            tam = points.size();
        }
        //printf("fim");
    }

};

#endif


