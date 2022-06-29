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
///-Modelagem do objeto com op��o de rota��o e transla��o, para gera��o de objetos como
/// garrafas, donuts e molas;
///-Controle de FPS;
///-Visualiza��o ortogr�fica e perspectiva (sob v�rios �ngulos) em wireframe, com uso de
/// tri�ngulos;
///-Parametriza��o do n�mero de pontos e faces do objeto gerado;
///-Exibir vetores normais em cada face (at� 1 ponto);
///-Adi��o de mais de 4 pontos de controle (at� 1 ponto);
///-Preenchimento de pol�gonos com Ilumina��o por v�rtice (at� 4 pontos).

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "gl_canvas2d.h"

#include "Vector2.h"
#include "scene.h"
#include "Frames.h"
#include "sweep.h"

int screenWidth = 1200, screenHeight = 588;//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
bool click = false;
float fps;


Scene *scene;
//Frames *frames;


void render()
{
    scene->render();
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


        scene->click  = state;
        ///Atualiza coordenadas de tela com clique se necess�rio
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
