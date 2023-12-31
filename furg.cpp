#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>

// Variáveis globais para controle da rotação
GLfloat angle, fAspect; 


// Variáveis de rotação
GLfloat rotateX = 0.0f;
GLfloat rotateY = 0.0f;

// Função para calcular a transposta de uma matriz 4x4
void Transposta(float matriz[4][4]) {
    float aux;
    for (int i = 0; i < 4; i++) {
        for (int j = i; j >= 0; j--) {
            aux = matriz[i][j];
            matriz[i][j] = matriz[j][i];
            matriz[j][i] = aux;
        }
    }
}

// Função para realizar uma translação usando uma matriz 4x4
void Translate(float dx, float dy, float dz) {
    float matriz[4][4] = {{1,0,0,0},
                          {0,1,0,0},
                          {0,0,1,0},
                          {0,0,0,1}};
    matriz[0][3] = dx;
    matriz[1][3] = dy;
    matriz[2][3] = dz;
    Transposta(matriz);
    glMultMatrixf((float *) matriz);
}

// Função para desenhar um retângulo
void retangulo(float x, float y, float z, float largura, float altura) {
    Translate(x, y, z);
    glColor3f(1.0f, 1.0f, 1.0f); 
    
    glBegin(GL_QUADS);
        glVertex3f(-largura / 2, -altura / 2, 0);
        glVertex3f(largura / 2, -altura / 2, 0);
        glVertex3f(largura / 2, altura / 2, 0);
        glVertex3f(-largura / 2, altura / 2, 0);
    glEnd();
    glPopAttrib(); 
}

// Função para desenhar um semicírculo
void desenharSemiCirculo(float x, float y, float z, float raio, float anguloInicial, float anguloFinal) {
    int numSegmentos = 100; 

    glPushMatrix();
    glTranslatef(x, y, z);

    glPushAttrib(GL_CURRENT_BIT); 
    glColor3f(1.0f, 0.5f, 0.0f); 

    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(x, y, z);

    for (int i = 0; i <= numSegmentos; ++i) {
        float angulo = anguloInicial + (i * (anguloFinal - anguloInicial) / numSegmentos);
        float xBorda = x + (raio/0.9) * cos(angulo);
        float yBorda = y + (raio / 2) * sin(angulo);
        glVertex3f(xBorda, yBorda, z);
    }

    glEnd();
    glPopAttrib(); 
    glPopMatrix();
}

// Função para desenhar um semicírculo à direita
void desenharSemiCirculoDireita(float x, float y, float z, float raio, float anguloInicial, float anguloFinal) {
    int numSegmentos = 100;

    glPushMatrix();
    glTranslatef(x, y, z);

    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(x, y - raio, z);

    for (int i = 0; i <= numSegmentos; ++i) {
        float angulo = anguloInicial + (i * (anguloFinal - anguloInicial) / numSegmentos);
        float xBorda = x + (raio / 0.9) * cos(angulo);
        float yBorda = (y - raio) + (raio / 2) * sin(angulo);
        glVertex3f(xBorda, yBorda, z);
    }

    glEnd();
    glPopMatrix();
}

// Função para desenhar um semicírculo abaixo
void desenharSemiCirculoEmbaixo(float x, float y, float z, float raio, float anguloInicial, float anguloFinal) {
    int numSegmentos = 100;

    glPushMatrix();
    glTranslatef(x, y, z);

    glPushAttrib(GL_CURRENT_BIT); 
    glColor3f(1.0f, 0.5f, 0.0f); 

    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(x, y - raio, z);

    for (int i = 0; i <= numSegmentos; ++i) {
        float angulo = anguloInicial + (i * (anguloFinal - anguloInicial) / numSegmentos);
        float xBorda = x + (raio / 0.9) * cos(angulo);
        float yBorda = (y - raio) + (raio / 2) * sin(angulo);
        glVertex3f(xBorda, yBorda, z);
    }

    glEnd();
    glPopAttrib(); 
    glPopMatrix();
}

// Função para desenhar um semicírculo acima
void desenharSemiCirculoCima(float x, float y, float z, float raio, float anguloInicial, float anguloFinal, GLfloat cor[3]) {
    int numSegmentos = 100; 

    glPushMatrix();
    glTranslatef(x, y, z);

    glColor3fv(cor); 


    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(x, y - raio, z);

    for (int i = 0; i <= numSegmentos; ++i) {
        float angulo = anguloInicial + (i * (anguloFinal - anguloInicial) / numSegmentos);
        float xBorda = x + (raio / 0.9) * cos(angulo);
        float yBorda = (y - raio) + (raio / 2) * sin(angulo);
        glVertex3f(xBorda, yBorda, z);
    }

    glEnd();
    glPopAttrib(); 
    glPopMatrix();
}

// Função para desenhar um triângulo retângulo
void desenharTrianguloRetangulo(float x, float y, float z, float largura, float altura, GLfloat cor[3]) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glColor3fv(cor); 

    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, 0);                
    glVertex3f(largura, 0, 0);          
    glVertex3f(largura, altura, 0);     
    glEnd();

    glPopMatrix();
}

// Função para desenhar um triângulo retângulo invertido
void desenharTrianguloRetanguloInvertido(float x, float y, float z, float largura, float altura, GLfloat cor[3]) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glColor3fv(cor);

    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, 0);     
    glVertex3f(largura, 0, 0);    
    glVertex3f(0, altura, 0);  
    glEnd();

    glPopMatrix();
}

// Função para desenhar um retângulo
void desenharRetangulo(float x, float y, float z, float largura, float altura, GLfloat cor[3]) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glColor3fv(cor); 

    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);                
    glVertex3f(largura, 0, 0);          
    glVertex3f(largura, altura, 0);     
    glVertex3f(0, altura, 0);           
    glEnd();

    glPopMatrix();
}

// Função para desenhar a logo
void display(void) {
    GLfloat corAmarela[] = {1.0f, 1.0f, 0.0f};
    GLfloat corVermelha[] = {1.0f, 0.0f, 0.0f};
    GLfloat corLaranja[] = {0.8f, 0.5f, 0.0f};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST); 

    glLoadIdentity();
    gluLookAt(0, 80, 250, 0, 0, 0, 0, 1, 0); 

    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f); 

    glColor3f(0.0f, 1.0f, 0.0f); 
    retangulo(0, 0, 0, 150, 150);

    glColor3f(1.0f, 0.5f, 0.0f); 
    glPushMatrix();
    glRotatef(90, 0.0f, 0.0f, 1.0f); 
    desenharSemiCirculo(4, 18, 0.1, 31, 3.13, 0); 
    glPopMatrix();

    glColor3f(1.0f, 0.5f, 0.0f); 
    glPushMatrix();

	glTranslatef(110, 0, 0); 
    glRotatef(90, 0.0f, 0.0f, -1.0f); 
    
    desenharSemiCirculoDireita(-4, -21, 0.1, 31, 3.13, 0);
    glPopMatrix();

	glColor3f(0.0f, 0.0f, 1.0f); 
    glPushMatrix();
    glTranslatef(0, 0, 0); 
    glRotatef(-179, 0.0f, 0.0f, 1.0f); 
    desenharSemiCirculoEmbaixo(0, 31, 0.1, 27, 3.13, 0);
    glPopMatrix();
	
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f); 
    desenharSemiCirculoCima(0, 33, 0.1, 13, 3.13, 0, corAmarela); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 0); 
	desenharTrianguloRetangulo(-30, 45, 0.1, 10, 5, corVermelha);
	glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f); 
	desenharTrianguloRetanguloInvertido(20, 45, 0.1, 10, 5, corVermelha);
	glPopMatrix();

	glPushMatrix();
    glTranslatef(-30, -30, 0); 
	desenharRetangulo(0, 0, 0.1, 60, 10, corVermelha);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30,-30, 0); 
	glRotatef(90, 0.0f, 0.0f, 1.0f); 
	desenharRetangulo(0, 0, 0.1, 75, 10, corVermelha);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20,-30, 0); 
	glRotatef(90, 0.0f, 0.0f, 1.0f); 
	desenharRetangulo(0, 0, 0.1, 75, 10, corVermelha);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, -15, 0);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	desenharRetangulo(0, 0, 0.1, 70, 30, corAmarela);
	glPopMatrix();

    glutSwapBuffers();
}

// Função para rotacionar a cena
void rotate(int opcao){
    switch (opcao) {
        case 1: // em x
            rotateX += 2.0f;
            break;
        case (-1): // em -x
            rotateX -= 2.0f;
            break;
        case 2: // em y
            rotateY += 2.0f;
            break;
        case (-2): // em -y
            rotateY -= 2.0f;                        
            break;
    }
    glutPostRedisplay();
}

// Função para especificar os parâmetros de visualização
void EspecificaParametrosVisualizacao(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle,fAspect,0.4,500);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(0,80,250, 0,0,0, 0,1,0); 
}

// Função callback chamada quando o tamanho da janela é alterado
void keyboard(unsigned char key, int x, int y)
{
    int hor, ver;
    hor = 0; ver = 0; 

    switch (key) {
        case 27:
            exit(0);
            break;
        case 'l':
            glDisable(GL_LIGHTING); 
            break;
        case 'f':
            glEnable(GL_LIGHTING); 
            break;
        case 'r':
        EspecificaParametrosVisualizacao();
            break;
    }

    glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos do mouse
void SpecialKeyboard(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
		rotate(1); 
    }
    else if(key == GLUT_KEY_DOWN) {
		rotate(-1); 
    }
	else if(key == GLUT_KEY_RIGHT) {
		rotate(2); 
    }
	else if(key == GLUT_KEY_LEFT) {
		rotate(-2); 
    }
	
    glutPostRedisplay(); 
}

// Função para inicializar as luzes
void initLights(){
	GLfloat ambientLight[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,-.2}; 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};
	GLfloat posicaoLuz[4]={0.0, -100.0, 250.0, 1.0}; 


	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;    

	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);

	glMateriali(GL_FRONT,GL_SHININESS,especMaterial); 
	GLfloat mat_transparent[] = { 0.0, 0.8, 0.8, 0.6 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent); 

	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );    

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);  

	glEnable(GL_LIGHT0);	

    glEnable(GL_MULTISAMPLE_ARB);	
}

// Função para inicializar o programa
void init(void)
{
	
	angle=45; // angulo de visão da camera
	

	glEnable(GL_MAP2_VERTEX_3); // habilita o uso da superfície

	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0); // define a malha de pontos
	glShadeModel(GL_SMOOTH); // define o modo de renderização

	initLights(); // inicializa as luzes

	glEnable(GL_DEPTH_TEST); // habilita o teste de profundidade
}

// Função callback chamada quando o tamanho da janela é alterado
void reshape(int w, int h)
{
	if ( h == 0 ) h = 1; // previne a divisão por zero

	glViewport(0, 0, w, h); // especifica as dimensões da viewport
 
	fAspect = (GLfloat)w/(GLfloat)h; // calcula a correção de aspecto

	EspecificaParametrosVisualizacao(); // especifica sistema de coordenadas de projeção
}

// Função principal
int main(int argc, char** argv)
{
   glutInit(&argc, argv); // inicializa o GLUT
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE); // especifica o uso de cores e buffers
   glutInitWindowSize (1200, 1000); // especifica as dimensões da janela
   glutInitWindowPosition (100, 100); // especifica a posição inicial da janela
   glutCreateWindow ("FURG LOGO"); // cria a janela
   glutDisplayFunc(display); // 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(SpecialKeyboard); 
   init (); // executa função de inicialização
   glutMainLoop(); 
}
