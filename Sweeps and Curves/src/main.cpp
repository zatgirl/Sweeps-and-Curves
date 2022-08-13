/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Versao 2.0
// *********************************************************************/
///Objetivos
///Explorar transforma��es geom�tricas, curvas, modelagem 3D, proje��o em perspectiva,
///movimenta��o de c�mera, visualiza��o 3D.

///Implementa��es:
/// [X] Modelagem do objeto com op��o de rota��o e transla��o, para gera��o de objetos como garrafas, donuts e molas;
/// [X] Controle de FPS;
/// [X] Visualiza��o ortogr�fica e perspectiva (sob v�rios �ngulos) em wireframe, com uso de tri�ngulos;
/// [X] Parametriza��o do n�mero de pontos e faces do objeto gerado;
/// [X] Painel para parametrizar o sweep translacional
/// [X] Interface Iterativa
/// [ ] Exibir vetores normais em cada face (at� 1 ponto);
/// [X] Adi��o de mais de 4 pontos de controle (at� 1 ponto);
/// [ ] Preenchimento de pol�gonos sem ilumina��o;
/// [ ] Preenchimento de pol�gonos com Ilumina��o por v�rtice (at� 4 pontos).

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "gl_canvas2d.h"

#include "Vector2.h"
#include "Vector3.h"
#include "scene.h"
#include "Frames.h"

int screenWidth = 1200, screenHeight = 700;
bool click = false;
float fps;

Scene *scene;
Frames *frames;

void render()
{
    scene->render();
    fps = frames->getFrames();
    scene->viewFrames(fps, screenWidth, screenHeight);
}

void keyboard(int key)
{
    switch(key){
        case 97:
            scene->_ajusted += 10;
            break;
        case 100:
            scene->_ajusted -= 10;
            break;
        case 119:
            scene->_ajustez += 10;
            break;
        case 115:
            scene->_ajustez -= 10;
            break;
        case 109:
            scene->_amountSpiralSpring += 1;
            break;
        case 110:
            scene->_amountSpiralSpring -= 1;
            break;
        case 106:
            scene->_offsetHeightSpring +=0.1;
            break;
        case 107:
            scene->_offsetHeightSpring -=0.1;
            break;
        case 104:
            scene->pinta = true;
            break;
        case 202: /// >
            scene->rotX += 0.010;
            break;
        case 200: /// <
            scene->rotX -= 0.010;
            break;
        case 201: /// ^
            scene->rotY += 0.010;
            break;
        case 203: /// \/
            scene->rotY -= 0.010;
            break;
    }
}

void keyboardUp(int key)
{

}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    scene->mouseX = x;
    scene->mouseY = y;
    scene->mouseSt = state;

    static int posvetor = 0;
    static bool click = false;

    if(((x > scene->BoundingCurveP1.x) && (x < scene->BoundingCurveP2.x)) && ((y > scene->BoundingCurveP1.y) && (y < scene->BoundingCurveP2.y))){
        if(state == 0){
            ///Adiciona a quantidade de pontos especificada pelo usuario
            if(scene->_controlPoints.size() < scene->_maxPointsInBezier){
                scene->_controlPoints.push_back(Vector3(x,y,0));
                printf("x: %d, y: %d\n", x,y);
            }
            ///Testa se o click ocorreu em cima de algum ponto de controle da curva
            for(int i = 0; i < scene->_controlPoints.size(); i ++){
                if((sqrt(pow(scene->_controlPoints[i].x - x, 2) + pow(scene->_controlPoints[i].y - y, 2))) < 8){
                    posvetor = i;
                    click = true;
                }
            }
            ///Atualiza coordenadas de tela com clique se necess�rio
            scene->screenHeight = screenHeight;
            scene->screenWidth = screenWidth;
        }

        ///Enquanto segura o click e arrasta, fica atualizando o valor do ponto selecionado, at� que o bot�o seja solto
        if((state == -2) && (click)){
            scene->_controlPoints[posvetor].set(x,y,0);
        }
        if((state == 1) && (click)){
            scene->_controlPoints[posvetor].set(x,y,0);
            click = false;
        }
    }
}

int main(void)
{
    scene = new Scene(screenWidth, screenHeight);
    frames = new Frames();


    CV::init(&screenWidth, &screenHeight, "T4 - Sweeps and Curves");
    scene->Buttons();
    CV::run();
    return 0;
}
