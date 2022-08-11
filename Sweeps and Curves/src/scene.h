#ifndef __SCENE__H___
#define __SCENE__H___

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>

#include "bezier.h"
#include "Botao.h"
#include "sweep.h"

Botao *checkboxSweepRotacional = NULL;
Botao *checkboxSweepTranslacional = NULL;
Botao *increasePointsInBezier = NULL;
Botao *decreasePointsInBezier = NULL;
Botao *increasePoints = NULL;
Botao *decreasePoints = NULL;
Botao *increaseRot = NULL;
Botao *decreaseRot = NULL;
Botao *perspectiv = NULL;
Botao *create = NULL;
Botao *clean = NULL;

Sweep *sweep;
Perspective *perspective;

class Scene
{
public:
    int screenWidth, screenHeight;
    ///vari�veis controladas pela main.cpp
    std::vector <Vector3> _controlPoints;
    std::vector <Vector3> _curvePoints;
    float _ajusted = -1200, _ajustez = -1200;
    int _rotacoes = 8, _pointsInCurve = 8, _maxPointsInBezier = 5;
    bool _translacional = false, _rotacional = true;
    int mouseX, mouseY, mouseSt;

    ///vari�veis utilizadas na classe
    bool pass = true;
    bool createSt = true, perspectiveSt = false, boxmenusSt = false, click;
    int selectMenu, selectMenuCreate, selectMenuPerspective;
    float vxLeft[3], vyLeft[3], vxRight[3], vyRight[3], vxCenter[3], vyCenter[3];
    int points = 8, rotations = 9;

    Scene(){
    }

    Scene(int _screenWidth, int _screenHeight){
        this->screenWidth  = _screenWidth;
        this->screenHeight = _screenHeight;

        sweep = new Sweep();
        perspective = new Perspective();
    }

    void render(){
        ///CartesianScene Default
        UI();
        ManagerMenu();
        if(createSt){
            CartesianScene();
            BE::Curva(_controlPoints);
            //perspectiveSt = false;
        }
        if(perspectiveSt){
            PerspectiveScene();
            //createSt = false;
            _curvePoints.clear();
            _curvePoints = BE::Curva(_controlPoints, _pointsInCurve);
            sweep->CreateSweep(_curvePoints, _ajustez, _rotacoes);
            perspective->persp(sweep->matrizPoints, sweep->tam, sweep->rot, _ajusted);
            perspective->render();
        }
    }

    void ManagerMenu(){
        Botao *menu[] = {create, perspectiv};
        Botao *menuCreate[] = {clean, increasePointsInBezier, decreasePointsInBezier, checkboxSweepRotacional, checkboxSweepTranslacional};
        Botao *menuPerspective[] = {increasePoints, decreasePoints, increaseRot, decreaseRot};
        if(mouseSt == 1){
            if(menu[0]->Colidiu(mouseX,mouseY)){
                createSt = true;
                perspectiveSt = false;
            }
            if(menu[1]->Colidiu(mouseX,mouseY)){
                createSt = false;
                perspectiveSt = true;
            }
            if(menuCreate[3]->Colidiu(mouseX,mouseY)){
                _rotacional = true;
                _translacional = false;
            }
            if(menuCreate[4]->Colidiu(mouseX,mouseY)){
                _rotacional = false;
                _translacional = true;
            }
            _maxPointsInBezier = (menuCreate[1]->Colidiu(mouseX,mouseY) ? _pointsInCurve + 1 : _pointsInCurve);
            _maxPointsInBezier = (menuCreate[2]->Colidiu(mouseX,mouseY) ? _pointsInCurve - 1 : _pointsInCurve);
            points = (menuPerspective[0]->Colidiu(mouseX,mouseY) ? points + 1 : points);
            points = (menuPerspective[1]->Colidiu(mouseX,mouseY) ? points - 1 : points);
            rotations = (menuPerspective[2]->Colidiu(mouseX,mouseY) ? rotations + 1 : rotations);
            rotations = (menuPerspective[3]->Colidiu(mouseX,mouseY) ? rotations - 1 : rotations);
            if (menuCreate[0]->Colidiu(mouseX,mouseY)){
                _curvePoints.clear();
                _controlPoints.clear();
            }
        }
    }

    void UI(){
        ///Fundo
        CV::color(0.827, 0.827, 0.827);
        CV::rectFill(0,0,screenWidth,screenHeight);
        ///Menu
        create = new Botao(0,screenHeight - 27, 150, 25, "Create", 0.752, 0.752, 0.752);
        create->Draw();
        perspectiv = new Botao(155, screenHeight - 27, 150, 25, "Perspective", 0.752, 0.752, 0.752);
        perspectiv->Draw();

        increasePoints = new Botao(10, screenHeight - 100, 25, 25, "<", 0.254, 0.411, 1);
        decreasePoints = new Botao(70, screenHeight - 100, 25, 25, ">", 0.254, 0.411, 1);
        increaseRot = new Botao(10, screenHeight - 150, 25, 25, "<", 0.254, 0.411, 1);
        decreaseRot = new Botao(70, screenHeight - 150, 25, 25, ">", 0.254, 0.411, 1);
        increasePointsInBezier = new Botao(10, screenHeight - 150, 25, 25, "<", 0.254, 0.411, 1);
        decreasePointsInBezier = new Botao(70, screenHeight - 150, 25, 25, ">", 0.254, 0.411, 1);
        checkboxSweepRotacional = new Botao(10, screenHeight - 200, 25, 25, " ", 1, 1, 1);
        checkboxSweepTranslacional = new Botao(10, screenHeight - 250, 25, 25, " ", 1, 1, 1);
    }

    void CartesianScene(){
        ///Fundo
        CV::color(0);
        CV::rectFill(0,0,screenWidth,screenHeight/17*16.5);
        ///Eixos
        CV::color(1,0,0);
        CV::line(20,screenHeight/10*2, screenWidth - 20, screenHeight/10*2);
        CV::line(screenWidth/10*5, 20, screenWidth/10*5, screenHeight - 40);
        vxLeft[0] = 10;                          vyLeft[0] = (screenHeight/10*2);
        vxLeft[1] = 20;                          vyLeft[1] = (screenHeight/10*2)-10;
        vxLeft[2] = 20;                          vyLeft[2] = (screenHeight/10*2)+10;
        CV::polygonFill(vxLeft,vyLeft,3);
        CV::text(10,(screenHeight/10*2)-20, "-X");
        vxRight[0] = screenWidth - 10;           vyRight[0] = (screenHeight/10*2);
        vxRight[1] = screenWidth - 20;           vyRight[1] = (screenHeight/10*2)-10;
        vxRight[2] = screenWidth - 20;           vyRight[2] = (screenHeight/10*2)+10;
        CV::polygonFill(vxRight,vyRight,3);
        CV::text(screenWidth - 20,(screenHeight/10*2)-20, "X");
        vxCenter[0] = screenWidth/10*5;          vyCenter[0] = screenHeight - 30;
        vxCenter[1] = (screenWidth/10*5)-10;     vyCenter[1] = screenHeight - 40;
        vxCenter[2] = (screenWidth/10*5)+10;     vyCenter[2] = screenHeight - 40;
        CV::polygonFill(vxCenter,vyCenter,3);
        CV::text((screenWidth/10*5)+10,screenHeight - 40, "Y");

        clean = new Botao(10, screenHeight - 100, 100, 25, "Clean", 0.254, 0.411, 1);
        clean->Draw();

        ///Ajuste da quantidade de pontos estimados na curva de bezier
        CV::color(1,1,1);
        CV::text(10, screenHeight - 120, "MAX POINTS TO DRAW CURVE");
        increasePointsInBezier->Draw();
        CV::color(1,1,1);
        CV::rectFill(40, screenHeight - 150, 65, screenHeight - 125);
        CV::color(0);
        char* tempFtoChar3 = (char*)malloc(5);
        std::sprintf(tempFtoChar3, "%d", _maxPointsInBezier);
        CV::text(49, screenHeight - 145, tempFtoChar3);
        decreasePointsInBezier->Draw();

        ///Checkbox para selecionar o tipo de sweep desenhado:
        /// -> Rotacional: Tacas e donuts;
        /// -> Translacional: Molas, espirais ---------OBS: N�o vai gerar um circulo perfeito por ter utilizado curva de bezier
        CV::color(1,1,1);
        CV::text(40, screenHeight - 195, "SWEEP ROTACIONAL");
        CV::text(40, screenHeight - 245, "SWEEP TRANSLACIONAL");
        checkboxSweepRotacional->Draw();
        checkboxSweepTranslacional->Draw();
        ///Sele��o das checkbox
        CV::color(2);
        if(_rotacional){
            CV::line(10, screenHeight - 175, 35, screenHeight - 200);
            CV::line(10, screenHeight - 200, 35, screenHeight - 175);
        }
        if(_translacional){
            CV::line(10, screenHeight - 225, 35, screenHeight - 250);
            CV::line(10, screenHeight - 250, 35, screenHeight - 225);
        }
    }

    void PerspectiveScene(){
        ///Fundo
        CV::color(0.607, 0.607, 0.607);
        CV::rectFill(0,0,screenWidth,screenHeight/17*16.5);

        ///Parametriza��o da curva
        CV::color(0);
        CV::text(10, screenHeight - 70, "Rotations");

        increasePoints->Draw();
        CV::color(1,1,1);
        CV::rectFill(40, screenHeight - 100, 65, screenHeight - 75);
        CV::color(0);
        char* tempFtoChar = (char*)malloc(5);
        std::sprintf(tempFtoChar, "%d", points);
        CV::text(49, screenHeight - 95, tempFtoChar);
        decreasePoints->Draw();
        CV::color(0);
        CV::text(10, screenHeight - 120, "Estimated Points In Curve");

        increaseRot->Draw();
        CV::color(1,1,1);
        CV::rectFill(40, screenHeight - 150, 65, screenHeight - 125);
        CV::color(0);
        char* tempFtoChar2 = (char*)malloc(5);
        std::sprintf(tempFtoChar2, "%d", rotations);
        CV::text(49, screenHeight - 145, tempFtoChar2);
        decreaseRot->Draw();
    }

    void viewFrames(float fps, int screenWidth, int screenHeight){
        char* tempFtoChar = (char*)malloc(5);
        CV::color(1,1,0);
        CV::rectFill(screenWidth-51,screenHeight-23, screenWidth, screenHeight-3);
        std::sprintf(tempFtoChar, "%.2f", fps);
        CV::color(0,0,0);
        CV::text(screenWidth-51,screenHeight-20, tempFtoChar);
    }

    void viewInstructions(int screenWidth, int screenHeight){
        CV::text(0, screenHeight-40, "[+] Adiciona raios na bicicleta");
        CV::text(0, screenHeight-60, "[-] Remove raios na bicicleta");
        CV::text(0, screenHeight-80, "[>] Aumenta velocidade");
        CV::text(0, screenHeight-100, "[<] Diminui velocidade");
    }

};


#endif // __SCENE__H___
