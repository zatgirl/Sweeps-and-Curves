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

Botao *increasePoints = NULL;
Botao *decreasePoints = NULL;
Botao *increaseRot = NULL;
Botao *decreaseRot = NULL;
Botao *perspective = NULL;
Botao *create = NULL;
Botao *clean = NULL;
Sweep *sweep;

class Scene
{
public:
    int screenWidth, screenHeight;
    std::vector<Vector2*> montain;
    bool pass = true;
    bool createSt = true, perspectiveSt, click;
    float vxLeft[3], vyLeft[3], vxRight[3], vyRight[3], vxCenter[3], vyCenter[3];
    int mouseX, mouseY, mouseSt;
    int points = 8, rotations = 9;

    Scene(){
    }

    Scene(int _screenWidth, int _screenHeight){
        this->screenWidth  = _screenWidth;
        this->screenHeight = _screenHeight;
    }

    void render(){
        ///CartesianScene Default
        UI();
        ManagerMenu();

        if(createSt){
            CartesianScene();
            if(mouseSt == 0){
                sweep->render();
            }

        }
        if(perspectiveSt){
            PerspectiveScene();
        }
    }

    void ManagerMenu(){
        Botao *menu[] = {create, perspective};
        Botao *menuCreate[] = {clean};
        Botao *menuPerspective[] = {increasePoints, decreasePoints, increaseRot, decreaseRot};
        if(mouseSt == 1){
            createSt = (menu[0]->Colidiu(mouseX,mouseY) ? true : false);
            perspectiveSt = (menu[1]->Colidiu(mouseX,mouseY) ? true : false);
            points = (menuPerspective[0]->Colidiu(mouseX,mouseY) ? points + 1 : points);
            points = (menuPerspective[1]->Colidiu(mouseX,mouseY) ? points - 1 : points);
            rotations = (menuPerspective[2]->Colidiu(mouseX,mouseY) ? rotations + 1 : rotations);
            rotations = (menuPerspective[3]->Colidiu(mouseX,mouseY) ? rotations + 1 : rotations);
            if (menuCreate[0]->Colidiu(mouseX,mouseY)){
                sweep->clean = true;
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
        perspective = new Botao(155, screenHeight - 27, 150, 25, "Perspective", 0.752, 0.752, 0.752);
        perspective->Draw();

        increasePoints = new Botao(10, screenHeight - 100, 25, 25, "<", 0.254, 0.411, 1);
        decreasePoints = new Botao(70, screenHeight - 100, 25, 25, ">", 0.254, 0.411, 1);
        increaseRot = new Botao(10, screenHeight - 150, 25, 25, "<", 0.254, 0.411, 1);
        decreaseRot = new Botao(70, screenHeight - 150, 25, 25, ">", 0.254, 0.411, 1);

        if(mouseSt == 0){
            sweep->mouseX = this->mouseX;
            sweep->mouseY = this->mouseY;
            sweep->mouseSt = this->mouseSt;
        }

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
    }

    void PerspectiveScene(){
        ///Fundo
        CV::color(0.607, 0.607, 0.607);
        CV::rectFill(0,0,screenWidth,screenHeight/17*16.5);

        ///Parametrização da curva
        CV::color(0);
        CV::text(10, screenHeight - 70, "Points");

        increasePoints->Draw();
        CV::color(1,1,1);
        CV::rectFill(40, screenHeight - 100, 65, screenHeight - 75);
        CV::color(0);
        char* tempFtoChar = (char*)malloc(5);
        std::sprintf(tempFtoChar, "%d", points);
        CV::text(49, screenHeight - 95, tempFtoChar);
        decreasePoints->Draw();
        CV::color(0);
        CV::text(10, screenHeight - 120, "Rotations");

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
        CV::rectFill(0,screenHeight-22, 50, screenHeight);
        std::sprintf(tempFtoChar, "%.2f", fps);
        CV::color(0,0,0);
        CV::text(0,screenHeight-20, tempFtoChar);
    }

    void viewInstructions(int screenWidth, int screenHeight){
        CV::text(0, screenHeight-40, "[+] Adiciona raios na bicicleta");
        CV::text(0, screenHeight-60, "[-] Remove raios na bicicleta");
        CV::text(0, screenHeight-80, "[>] Aumenta velocidade");
        CV::text(0, screenHeight-100, "[<] Diminui velocidade");
    }
};


#endif // __SCENE__H___
