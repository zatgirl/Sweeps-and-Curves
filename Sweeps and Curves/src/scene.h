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
    ///variáveis controladas pela main.cpp
    std::vector <Vector3> _controlPointsBackup;
    std::vector <Vector3> _controlPoints;
    std::vector <Vector3> _curvePoints;
    float _ajusted = -1200, _ajustez = -1200;
    int _rotacoes = 8, _pointsInCurve = 8, _maxPointsInBezier = 5, _amountSpiralSpring = 4;
    bool _translational = false, _rotacional = true;
    int mouseX, mouseY, mouseSt;

    ///variáveis controladas pela classe
    bool createSt = true, perspectiveSt = false, boxmenusSt = false, click;
    Vector2 BoundingCurveP1, BoundingCurveP2;
    Vector2 BoundingOrthogonalP1, BoundingOrthogonalP2;


    Scene(){
    }

    Scene(int _screenWidth, int _screenHeight){
        this->screenWidth  = _screenWidth;
        this->screenHeight = _screenHeight;

        sweep = new Sweep();
        perspective = new Perspective();
        BoundingCurveP1.set(40,50);
        BoundingCurveP2.set(500,430);
        BoundingOrthogonalP1.set(550,50);
        BoundingOrthogonalP2.set(1160,600);
    }

    void render(){
        ///CartesianScene Default
        _controlPointsBackup = (_controlPoints.size() > 1) ? _controlPoints : _controlPointsBackup;
        UI();
        ManagerMenu();
        load();
        if(createSt){
            CartesianScene();
            BE::Curva(_controlPoints);
            perspective->wireOrthogonal();
        }
        if(perspectiveSt){
            PerspectiveScene();
            perspective->render();
            viewInstructions(screenWidth, screenHeight);
            ///Caso haja alteração em alguma variável crítica, recupera valores do backup
            if(_controlPoints.size() < 1){
               _controlPoints = _controlPointsBackup;
            }
        }
       // printf("_control size: %d\n", _controlPoints.size());
       // printf("_controlbckp size: %d\n", _controlPointsBackup.size());
        //printf("_curve size: %d\n", _curvePoints.size());
    }

    void load(){
        _curvePoints.clear();
        _curvePoints = BE::Curva(_controlPoints, _pointsInCurve);

            sweep->_translational = this->_translational;
            sweep->CreateSweep(_curvePoints, _ajustez, _rotacoes, this->_amountSpiralSpring);
            perspective->_translational = this->_translational;
            perspective->persp(sweep->matrizPoints, sweep->tam, sweep->rot, _ajusted);


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
                _translational = false;
                _rotacoes = 8;
            }
            if(menuCreate[4]->Colidiu(mouseX,mouseY)){
                _rotacional = false;
                _translational = true;
                _rotacoes = 156;
            }
            _maxPointsInBezier = (menuCreate[1]->Colidiu(mouseX,mouseY) ? _maxPointsInBezier + 1 : _maxPointsInBezier);
            _maxPointsInBezier = (menuCreate[2]->Colidiu(mouseX,mouseY) ? _maxPointsInBezier - 1 : _maxPointsInBezier);
            _pointsInCurve = (menuPerspective[0]->Colidiu(mouseX,mouseY) ? _pointsInCurve + 1 : _pointsInCurve);
            _pointsInCurve = (menuPerspective[1]->Colidiu(mouseX,mouseY) ? _pointsInCurve - 1 : _pointsInCurve);
            _rotacoes = (menuPerspective[2]->Colidiu(mouseX,mouseY) ? _rotacoes + 1 : _rotacoes);
            _rotacoes = (menuPerspective[3]->Colidiu(mouseX,mouseY) ? (((_rotacoes - 1) <= 1) ? _rotacoes : _rotacoes -= 1) : _rotacoes);
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

        CV::color(1,1,1);
        CV::rect(BoundingCurveP1, BoundingCurveP2);
        CV::text(BoundingOrthogonalP1.x, BoundingOrthogonalP2.y+10, "ORTHOGONAL VIEW");
        CV::rect(BoundingOrthogonalP1, BoundingOrthogonalP2);

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
        /// -> Translacional: Molas, espirais ---------OBS: Não vai gerar um circulo perfeito por ter utilizado curva de bezier
        CV::color(1,1,1);
        CV::text(40, screenHeight - 195, "SWEEP ROTACIONAL");
        CV::text(40, screenHeight - 245, "SWEEP TRANSLACIONAL");
        checkboxSweepRotacional->Draw();
        checkboxSweepTranslacional->Draw();
        ///Seleção das checkbox
        CV::color(2);
        if(_rotacional){
            CV::line(10, screenHeight - 175, 35, screenHeight - 200);
            CV::line(10, screenHeight - 200, 35, screenHeight - 175);
        }
        if(_translational){
            CV::line(10, screenHeight - 225, 35, screenHeight - 250);
            CV::line(10, screenHeight - 250, 35, screenHeight - 225);
        }
    }

    void PerspectiveScene(){
        ///Fundo
        CV::color(0.607, 0.607, 0.607);
        CV::rectFill(0,0,screenWidth,screenHeight/17*16.5);

        ///Parametrização da curva
        CV::color(0);
        CV::text(10, screenHeight - 120, "ROTATIONS");

        increaseRot->Draw();
        CV::color(1,1,1);
        CV::rectFill(40, screenHeight - 150, 65, screenHeight - 125);
        CV::color(0);
        char* tempFtoChar = (char*)malloc(5);
        std::sprintf(tempFtoChar, "%d", _rotacoes);
        CV::text(49, screenHeight - 145, tempFtoChar);
        decreaseRot->Draw();
        CV::color(0);


        CV::text(10, screenHeight - 70, "ESTIMATED POINTS IN CURVE");
        increasePoints->Draw();
        CV::color(1,1,1);
        CV::rectFill(40, screenHeight - 100, 65, screenHeight - 75);
        CV::color(0);
        char* tempFtoChar2 = (char*)malloc(5);
        std::sprintf(tempFtoChar2, "%d", _pointsInCurve);
        CV::text(49, screenHeight - 95, tempFtoChar2);
        decreasePoints->Draw();
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
        CV::color(0 );
        CV::text(10, screenHeight-180, "AJUSTES OPCIONAIS");
        CV::text(10, screenHeight-200, "[a] DECREMENTA D");
        CV::text(10, screenHeight-220, "[d] INCREMENTA D");
        CV::text(10, screenHeight-240, "[s] DECREMENTA Z");
        CV::text(10, screenHeight-260, "[w] INCREMENTA Z");
    }

};

#endif // __SCENE__H___
