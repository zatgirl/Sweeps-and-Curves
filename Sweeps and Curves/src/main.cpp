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
Vector2 p[25][25];
//std::vector <Vector3*> transf;

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
    float maiorr = 0;
    float minbx= 100, minby= 100, maxbx = -100, maxby = -100;
    for(int m = 0; m < controlPoints.size(); m ++){
        if(maiorr < matrizPoints[0][m].y){
            maiorr = matrizPoints[0][m].y;
        }
    }
    float d = -150;
    for(int col = 0; col < 8; col++){
        for(int linha = 0; linha < controlPoints.size(); linha++){
            p[col][linha].x = (matrizPoints[col][linha].x * d) / ((matrizPoints[col][linha].z));
            p[col][linha].y = (matrizPoints[col][linha].y * d) / ((matrizPoints[col][linha].z));
            CV::color(3);
            CV::translate(600,200);
            CV::circleFill(p[col][linha].x,p[col][linha].y,4,10);
            minbx = (minbx > p[col][linha].x) ? p[col][linha].x : minbx;
            minby = (minby > p[col][linha].y) ? p[col][linha].y : minby;
            maxbx = (maxbx < p[col][linha].x) ? p[col][linha].x : maxbx;
            maxby = (maxby < p[col][linha].y) ? p[col][linha].y : maxby;
        }
    }
    CV::color(0,0,1);
    CV::rect(minbx,minby,maxbx,maxby);
}

void wire(){
    CV::color(0.7,0.7,0.7);
    for(int y = 0; y < 8; y ++){
    for(int x = 0; x < controlPoints.size(); x++){
            CV::line(p[y][x], p[y][x+1]); //linha horizontal
            CV::line(p[y][x], p[y+1][x]); //linha vertical
            CV::line(p[y][x], p[y+1][x+1]); //linha diagonal
        }
    }
}


   //faz a rotacao de um unico ponto 3D no eixo X
   Vector3 rotacionaY(Vector3 p , int x)
   {
      Vector3 resp;
      float ang = (PI*x)/180;
      //ang += 0.00001;

      resp.x = cos(ang)*p.x + sin(ang)*p.z;
      resp.y = p.y;
      resp.z = -sin(ang)*p.x + cos(ang)*p.z;

      return resp;
   }

   //faz a translacao de um unico ponto
   Vector3 translada(Vector3 p)
   {
       Vector3 resp;

       resp.x = p.x;
       resp.y = p.y - 10 ;
       resp.z = p.z - 12;

       return resp;
   }

   //projecao em perspectiva, assumindo camera na origem olhando para z negativo.
   Vector3 projeta( Vector3 p )
   {
       float d = -10.0;
       Vector3 resp;

       resp.x = (p.x*d) / p.z;
       resp.y = (p.y*d) / p.z;
       resp.z = 0;

       return resp;
   }


   //aplica sequencia de transformacoes na malha para fazer a animacao e visualizacao.
   void transforma()
   {
       Vector3 p;
       printf("entrou\n");
      //Processa cada vertice da superficie individualmente.
    for(int r=0; r = 1; r++){
      for(int x=0; x<=8; x++){
        printf("1 for: %d\n", x);
         for(int z=0; z<=controlPoints.size(); z++)
         {
             printf("2 for: %d\n", z);
              //copia os pontos originais
              p = controlPoints[r][z];

              //rotacao no eixo y
              p = rotacionaY( p, x );

              //translacao no eixo z
              p = translada( p );

              //projecao em perspectiva
              matrizPoints[x][z] = projeta( p );
         }
      }
    }
   }

void render()
{
    if(controlPoints.size() > 3){
      //a cada renderizacao aplica uma transformacao na superficie que faz a rotacao e projecao em perspectiva.
      transforma();
        CV::color(0);
        CV::translate(300,200);
        //desenha os vertices
      for(int x=0; x<=8; x++){
         for(int z=0; z<=controlPoints.size(); z++)
         {
             CV::point(matrizPoints[x][z].x, matrizPoints[x][z].y);
         }
      }

     CV::translate(600,200);
     CV::color(3);
      //desenha as arestas
      for(int x=0; x<8; x++){
         for(int z=0; z<controlPoints.size(); z++)
         {
             CV::line(matrizPoints[x][z].x, matrizPoints[x][z].y, matrizPoints[x+1][z].x, matrizPoints[x+1][z].y );
             CV::line(matrizPoints[x][z].x, matrizPoints[x][z].y, matrizPoints[x][z+1].x, matrizPoints[x][z+1].y );
         }
      }

    }
    //CV::translate(300,200);
    /*if(controlPoints.size() > 0){


        //BE::Curva(controlPoints);
        //sweepp();
        persp();
        CV::translate(1000,200);
        wire();
    }*/
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
