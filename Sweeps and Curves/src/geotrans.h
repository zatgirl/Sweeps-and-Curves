#ifndef ___GEOTRANS__H___
#define ___GEOTRANS__H___

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gl_canvas2d.h"
#include "Vector2.h"
#include "bezier.h"


class raios {
public:
    Vector2 p1[32];
    Vector2 p2[32];
};

class GeoTrans
{
public:
    Vector2 aros[8], arosTrans[8], pedalLeft[2], pedalRight[2], centerLeft, centerRight, centerPedal, guidaoLeft, guidaoRight;
    Vector2 joelhoLeft, joelhoRight, quadril, pl,pr;
    int amountRays;
    float ang = 0.0, rayCircle;
    raios *raysLeft = new raios();
    raios *raysRight = new raios();
    float speed = 0.0;
    double scale;
    float vel = 0.01;
    float perna_size = 190;

    GeoTrans(){
    }

    GeoTrans(int _amountRays, Vector2 _centerLeft, Vector2 _centerRight, float _rayCircle, double _scale){
        this->amountRays = _amountRays;
        this->centerLeft.set(_centerLeft.x, _centerLeft.y);
        this->centerRight.set(_centerRight.x, _centerRight.y);
        this->rayCircle = _rayCircle;
        this->scale = _scale;
    }

    void render(){
        DrawBike();
        Rot();
        DrawRays();
        DrawMan();
    }

    void DrawBike(){
        ///Desenhando perna, pedal esquerdo pra ficar atrás da bike
        CV::line(quadril, joelhoLeft,2);
        CV::line(joelhoLeft, pl,2);
        CV::translate(centerPedal);
        CV::color(0.8,0.8,0.8);
        CV::line(pedalLeft[0],pedalLeft[1],3);
        ///Quadro
        CV::color(1,0,0);
        CV::translate(0,0);
        ///linha baixo
        CV::line(centerLeft.x, centerLeft.y, (centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2, 4);
        CV::line((centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2, centerRight.x-rayCircle+(rayCircle/5), centerRight.y+rayCircle, 4);
        ///linha cima
        CV::line(centerLeft.x, centerLeft.y, (centerRight.x-centerLeft.y)/3 + centerLeft.x, centerLeft.y+rayCircle, 4);
        CV::line((centerRight.x-centerLeft.y)/3 + centerLeft.x, centerLeft.y+rayCircle, centerRight.x-rayCircle+(rayCircle/5), centerRight.y+rayCircle, 4);
        ///guidao
        guidaoLeft.set(centerRight.x-rayCircle/2-rayCircle-(rayCircle/2), centerRight.y+rayCircle*2);
        guidaoRight.set(centerRight.x-rayCircle/2-rayCircle+(rayCircle/5), centerRight.y+rayCircle*2);
        CV::line(guidaoRight,guidaoLeft,3);
        CV::line(centerRight.x, centerRight.y, centerRight.x-rayCircle/2-rayCircle-(rayCircle/5), centerRight.y+rayCircle*2, 4);
        ///ferro e banco
        CV::line((centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2,(centerRight.x-centerLeft.y)/3 + centerLeft.x-rayCircle/7, centerLeft.y+rayCircle+rayCircle/4, 4);
        ///banco
        CV::color(0);
        CV::line((centerRight.x-centerLeft.y)/3 + centerLeft.x-rayCircle/3, centerLeft.y+rayCircle+rayCircle/4, (centerRight.x-centerLeft.y)/3 + centerLeft.x+rayCircle/5, centerLeft.y+rayCircle+rayCircle/4, 4);
        quadril.set((centerRight.x-centerLeft.y)/3 + centerLeft.x-rayCircle/3, centerLeft.y+rayCircle+rayCircle/4);
        ///pedal
        centerPedal.set((centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2);
        for(int i = 0; i <1; i++){
            CV::translate(0,0);
            CV::color(0.5,0.5,0.5);
            CV::circleFill(centerPedal,10,10);
            CV::color(0);
            CV::circleFill(centerPedal,4,10);
            CV::translate(centerPedal);
            CV::color(0.8,0.8,0.8);
            CV::line(pedalRight[0],pedalRight[1],3);
            CV::color(0,1,1);
            CV::circleFill(pedalLeft[1],4,10);
            CV::circleFill(pedalRight[1],4,10);
            ///pl e pr recebem o valor onde os pedais estão centrados pois manipulei apenas o ponto externo
            pl = centerPedal+pedalLeft[1];
            pr = centerPedal+pedalRight[1];
        }
    }

    void DrawMan(){
        CV::translate(0,0);
        ///head
        CV::color(0);
        CV::circleFill(centerPedal.x+rayCircle/4,guidaoLeft.y+rayCircle+rayCircle/5,20,20);
        ///costas
        CV::color(0);
        CV::line(quadril.x, quadril.y,centerPedal.x,guidaoLeft.y+rayCircle,2);
        ///braços
        CV::line(centerPedal.x-rayCircle/3,guidaoLeft.y+rayCircle/3, guidaoLeft.x-rayCircle/3, guidaoLeft.y,2);
        CV::line(guidaoLeft.x-rayCircle/3, guidaoLeft.y, guidaoLeft.x, guidaoLeft.y,2);
        CV::line(centerPedal.x-rayCircle/3,guidaoLeft.y+rayCircle/3, guidaoRight.x-rayCircle/3, guidaoRight.y+rayCircle/10,2);
        CV::line(guidaoRight.x-rayCircle/3, guidaoRight.y+rayCircle/10, guidaoRight.x, guidaoRight.y,2);
        ///Perna dir não será desenhada aqui, será desenhada antes de bike
        calcJoelhos(pl,pr,quadril,perna_size);
        CV::line(quadril, joelhoRight,2);
        CV::line(joelhoRight, pr,2);
    }

    ///Função usada para rotacionar os pedais e raios
    void Rot(){
        float radRot, radPedalLeft, radPedalRight;
        for (int currentRay = 0;currentRay < amountRays ;currentRay ++){
            radPedalLeft = ((PI_2*0.5) * currentRay)+speed;
            radPedalRight = ((PI_2*0) * currentRay)+speed;
            radRot = (((PI_2)/amountRays) * currentRay)+speed;
            this->raysLeft->p2[currentRay].set(cos(radRot) * (rayCircle*scale), sin(radRot)*(rayCircle*scale));
            this->raysRight->p2[currentRay].set(cos(radRot) * (rayCircle*scale), sin(radRot)*(rayCircle*scale));
            pedalLeft[1].set(cos(radPedalLeft) * (25*scale), sin(radPedalLeft)*(25*scale));
            pedalRight[1].set(cos(radPedalRight) * (25*scale), sin(radPedalRight)*(25*scale));
        }
        speed -= vel;
    }

    void DrawRays(){
        CV::color(0,0,0);
        CV::translate(centerLeft);
        CV::circle(0,0, rayCircle*scale, 20, 6);
        for (int currentRay = 0;currentRay < amountRays ;currentRay ++){
            CV::line(raysLeft->p1[currentRay],raysRight->p2[currentRay],2);
        }
        CV::translate(centerRight);
        CV::circle(0,0, rayCircle*scale, 20, 6);
        for (int currentRay = 0;currentRay < amountRays ;currentRay ++){
            CV::line(raysRight->p1[currentRay],raysRight->p2[currentRay],2);
        }
    }

    ///https://math.stackexchange.com/questions/256100/how-can-i-find-the-points-at-which-two-circles-intersect
    void calcJoelhos(Vector2 pedal_esq, Vector2 pedal_dir, Vector2 quadril, float perna_tam){
        float d_esq, l_esq, h_esq, r1, r2, d_dir, l_dir, h_dir;
        r1 = perna_tam*0.5; r2 = perna_tam*0.5;
        d_esq = sqrt((pow(pedal_esq.x-quadril.x, 2))+ (pow(pedal_esq.y-quadril.y, 2)));
        d_dir = sqrt((pow(pedal_dir.x-quadril.x, 2))+ (pow(pedal_dir.y-quadril.y, 2)));
        l_esq = (((r1*r1) - (r2*r2)) + (d_esq*d_esq))/(2*d_esq);
        l_dir = (((r1*r1) - (r2*r2)) + (d_dir*d_dir))/(2*d_dir);
        h_esq = sqrt((r1*r1) - (l_esq*l_esq));
        h_dir = sqrt((r1*r1) - (l_dir*l_dir));
        joelhoLeft.x = ((l_esq/d_esq)*(pedal_esq.x-quadril.x) - (h_esq/d_esq)*(pedal_esq.y-quadril.y) + quadril.x);
        joelhoLeft.y = ((l_esq/d_esq)*(pedal_esq.y-quadril.y) + (h_esq/d_esq)*(pedal_esq.x-quadril.x) + quadril.y);
        joelhoRight.x = ((l_dir/d_dir)*(pedal_dir.x-quadril.x) - (h_dir/d_dir)*(pedal_dir.y-quadril.y) + quadril.x);
        joelhoRight.y = ((l_dir/d_dir)*(pedal_dir.y-quadril.y) + (h_dir/d_dir)*(pedal_dir.x-quadril.x) + quadril.y);
    }

};

#endif

