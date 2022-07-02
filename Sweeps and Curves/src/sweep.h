#ifndef ___SWEEP__H___
#define ___SWEEP__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "gl_canvas2d.h"

#include "Vector2.h"
#include "bezier.h"
#include "perspective.h"

class Sweep
{
 public:
    int mouseX, mouseY, mouseSt;
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
            GetControlPoints();
        }

        if(ControlPoints.size() > 3){
           BE::Curva(ControlPoints);
        }
    }

    void GetControlPoints(){
        int i;

        //if(mouseSt == 0){
            ControlPoints.push_back(new Vector2 (mouseX,mouseY));
           // printf("%d, %d\n", *ControlPoints[i]);
            i++;
        //}
    }

};

#endif


