/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Versao 2.0
// *********************************************************************/
///Objetivos
///Explorar transformações geométricas, curvas, modelagem 3D, projeção em perspectiva,
///movimentação de câmera, visualização 3D.

///Implementações:
///-Modelagem do objeto com opção de rotação e translação, para geração de objetos como
/// garrafas, donuts e molas;
///-Controle de FPS;
///-Visualização ortográfica e perspectiva (sob vários ângulos) em wireframe, com uso de
/// triângulos;
///-Parametrização do número de pontos e faces do objeto gerado;
///-Exibir vetores normais em cada face (até 1 ponto);
///-Adição de mais de 4 pontos de controle (até 1 ponto);
///-Preenchimento de polígonos com Iluminação por vértice (até 4 pontos).

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
#include "sweep.h"
#include "bezier.h"

int screenWidth = 1200, screenHeight = 588;//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
bool click = false;
float fps;
std::vector <Vector3> controlPoints;
std::vector <Vector3> curvePoints;
float ajusted = -100, ajustez = 20;
int rotacoes = 8, pointsInCurve = 8;
bool translacional;

Scene *scene;
Sweep *sweep;
Perspective *perspective;
Vector2 mousep;

//Frames *frames;



void render()
{
    scene->render();
    curvePoints.clear();
     if(controlPoints.size() > 3){
        curvePoints = BE::Curva(controlPoints, pointsInCurve);
        sweep->CreateSweep(curvePoints, ajustez, rotacoes);
        perspective->persp(sweep->matrizPoints, sweep->tam, sweep->rot, ajusted);
        perspective->render(mousep);
        BE::Curva(controlPoints);
        //perspective->whatposition(mousep);
    }



    //fps = frames->getFrames();
    //scene->viewFrames(fps, screenWidth, screenHeight);
    //scene->viewInstructions(screenWidth, screenHeight);
}

void keyboard(int key)
{
    ///incrementa _d no a
    if (key == 97){
        ajusted += 10;
    }
    ///decrementa _d no d
    if(key == 100){
        ajusted -= 10;
    }
    printf("_d: %.2f", ajusted);

    ///incrementa _z no w
    if (key == 119){
        ajustez += 10;
    }
    ///decrementa _z no s
    if(key == 115){
        ajustez -= 10;
    }
     printf("ajustez: %.2f\n", ajustez);

    ///incrementa rotacoes no t
    if (key == 116){
        rotacoes += 1;
    }
    ///decrementa rotacoes no r
    if(key == 114){
        rotacoes -= 1;
    }

    ///incrementa pointsInCurve no o
    if (key == 111){
        pointsInCurve += 1;
    }
    ///decrementa pointsIncurve no p
    if(key == 112){
        pointsInCurve -= 1;
    }

}

void keyboardUp(int key)
{

}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
//    scene->mouseX = x;
 //   scene->mouseY = y;
 //   scene->mouseSt = state;
    static int posvetor = 0;
    static bool click = false;

    if(state == 0){
        if(controlPoints.size() < 5){
            controlPoints.push_back(Vector3(x,y,0));
            printf("x: %d, y: %d\n", x,y);
        }

//        scene->click  = state;
        ///Atualiza coordenadas de tela com clique se necessário
//        scene->screenHeight = screenHeight;
//        scene->screenWidth = screenWidth;
        for(int i = 0; i < controlPoints.size(); i ++){
            if((sqrt(pow(controlPoints[i].x - x, 2) + pow(controlPoints[i].y - y, 2))) < 8){
                posvetor = i;
                click = true;
            }
        }
    }

    if((state == -2) && (click)){
        controlPoints[posvetor].set(x,y,0);
    }
    if((state == 1) && (click)){
        controlPoints[posvetor].set(x,y,0);
        click = false;
    }
}

int main(void)
{
    sweep = new Sweep();
    perspective = new Perspective();
    scene = new Scene(screenWidth, screenHeight);
 // frames = new Frames();

    CV::init(&screenWidth, &screenHeight, "T4 - Sweeps and Curves");
    CV::run();
    return 0;
}
