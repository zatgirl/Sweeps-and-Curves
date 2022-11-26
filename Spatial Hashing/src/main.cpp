/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Versao 2.0
// *********************************************************************/
///Objetivos
///
///

///Implementações:
/// [ ]
/// [ ]
/// [ ]
/// [ ]
/// [ ]
/// [ ]


#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "gl_canvas2d.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Frames.h"

int screenWidth = 1200, screenHeight = 700;
bool click = false;
float fps;

Frames *frames;

void render()
{
    fps = frames->getFrames();
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

}

int main(void)
{
    frames = new Frames();

    CV::init(&screenWidth, &screenHeight, "T2 - Spatial Hashing");
    CV::run();
    return 0;
}
