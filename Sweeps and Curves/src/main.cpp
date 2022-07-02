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
#include "sweep.h"]
#include "bezier.h"

int screenWidth = 1200, screenHeight = 588;//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
bool click = false;
float fps;
std::vector <Vector3*> controlPoints;
Vector3 matrizPoints[25][25];
Vector2 p;


Scene *scene;
//Frames *frames;

void sweepp(){
    float ang, radius;
    float x,y,z;
    CV::translate(0,0);
    for(int i = 0, rotacao = 0; i < 360; i+= 45, rotacao ++){
        ang = (PI*i)/180;
        for(int linha = 0; linha < controlPoints.size(); linha ++){
            x = controlPoints[linha]->x*cosf(ang) + controlPoints[linha]->z*sinf(ang);
            y = controlPoints[linha]->y;
            z = -controlPoints[linha]->x*sinf(ang) + controlPoints[linha]->z*cosf(ang);
            matrizPoints[rotacao][linha].set(x,y,z);
            CV::color(0);
            CV::translate(300,200);
            CV::circleFill(x,y,3,5);
        }
    }   CV::translate(0,0);
}

void persp(){
    sweepp();
    float maiorr=0;
    for(int m = 0; m<controlPoints.size(); m++){
        if(maiorr < matrizPoints[0][m].x){
            maiorr = matrizPoints[0][m].x;
        }
    }
    float d = 50;
    for(int col = 0; col < 25; col++){
        for(int linha = 0; linha < controlPoints.size(); linha++){
            p.x = (matrizPoints[col][linha].x * d) / ((matrizPoints[col][linha].z) + maiorr);
            p.y = (matrizPoints[col][linha].y * d) / ((matrizPoints[col][linha].z) + maiorr);
            CV::color(3);
            CV::translate(300,200);
            CV::circleFill(p.x,p.y,4,10);
        }
    }
}

void render()
{
    //CV::translate(300,200);
    if(controlPoints.size() > 0){


        //BE::Curva(controlPoints);
        //sweepp();
        persp();
    }
    //scene->render();
    //fps = frames->getFrames();
    //scene->viewFrames(fps, screenWidth, screenHeight);
    //scene->viewInstructions(screenWidth, screenHeight);
}

void keyboard(int key)
{
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

    if(state == 0){

        controlPoints.push_back(new Vector3(x,y,-1));
        scene->click  = state;
        ///Atualiza coordenadas de tela com clique se necessário
        scene->screenHeight = screenHeight;
        scene->screenWidth = screenWidth;

    }
}

int main(void)
{

    scene = new Scene(screenWidth, screenHeight);
 // frames = new Frames();

    CV::init(&screenWidth, &screenHeight, "T4 - Sweeps and Curves");
    CV::run();
    return 0;
}
