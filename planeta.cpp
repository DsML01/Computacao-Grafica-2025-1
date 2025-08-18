#include <GL/glut.h>
#include <cstdio>

// Variáveis de rotação e translação
static int year = 0, day = 0;
static float planeta1_orbit = 0.0;   // Órbita do planeta 1 (direita)
static float planeta2_orbit = 0.0;   // Órbita do planeta 2 (esquerda)
static float lua1_orbit = 0.0;       // Órbita da lua 1 (eixo x)
static float lua2_orbit = 0.0;       // Órbita da lua 2 (eixo xy)
static bool animacao_ativa = false;  // Controla se a animação está ativa

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // fundo preto
}

// Protótipo da função de animação
void animate();

// Função de desenho
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Sol no centro - cor amarela
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0); // amarelo
        glRotatef((GLfloat)day, 0.0, 1.0, 0.0); // rotação do sol
        glutWireSphere(0.5, 20, 16); // Sol menor
    glPopMatrix();

    // Planeta 1 - gira para a direita (sentido horário)
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0); // azul
        glRotatef(planeta1_orbit, 0.0, 1.0, 0.0); // órbita horária
        glTranslatef(2.0, 0.0, 0.0);              // distância orbital
        glRotatef((GLfloat)day, 0.0, 1.0, 0.0);   // rotação própria
        glutWireSphere(0.15, 10, 8);              // Planeta 1
        
        // Lua 1 do Planeta 1 - orbita no eixo X
        glPushMatrix();
            glColor3f(0.8, 0.8, 0.8); // cinza
            glRotatef(lua1_orbit, 1.0, 0.0, 0.0); // rotação no eixo X
            glTranslatef(0.4, 0.0, 0.0);          // distância da lua
            glutWireSphere(0.05, 8, 6);           // Lua 1
        glPopMatrix();
        
        // Lua 2 do Planeta 1 - orbita no plano XY
        glPushMatrix();
            glColor3f(0.9, 0.9, 0.9); // cinza claro
            glRotatef(lua2_orbit, 0.0, 0.0, 1.0); // rotação no eixo Z (plano XY)
            glTranslatef(0.6, 0.0, 0.0);          // distância da lua
            glutWireSphere(0.05, 8, 6);           // Lua 2
        glPopMatrix();
    glPopMatrix();

    // Planeta 2 - gira para a esquerda (sentido anti-horário)
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0); // vermelho
        glRotatef(-planeta2_orbit, 0.0, 1.0, 0.0); // órbita anti-horária
        glTranslatef(3.0, 0.0, 0.0);               // distância orbital maior
        glRotatef((GLfloat)day, 0.0, 1.0, 0.0);    // rotação própria
        glutWireSphere(0.12, 10, 8);               // Planeta 2 (menor)
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 2.0, 8.0,   // posição da câmera (mais afastada e elevada)
        0.0, 0.0, 0.0,   // ponto para onde olha
        0.0, 1.0, 0.0    // vetor "para cima"
    );
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'y':
        case 'Y':
            // Alterna entre iniciar e parar a animação
            animacao_ativa = !animacao_ativa;
            if (animacao_ativa) {
                glutIdleFunc(animate); // Inicia animação
            } else {
                glutIdleFunc(NULL);    // Para animação
            }
            break;
        case 27: // ESC para sair
            exit(0);
            break;
        default:
            break;
    }
}

// Função de animação automática
void animate() {
    if (animacao_ativa) {
        // Movimento dos planetas
        planeta1_orbit += 0.8;  // Planeta 1 gira para direita
        planeta2_orbit += 0.6;  // Planeta 2 gira para esquerda (velocidade diferente)
        
        // Movimento das luas (mais rápido que os planetas)
        lua1_orbit += 2.0;      // Lua 1 orbita no eixo X
        lua2_orbit += 1.5;      // Lua 2 orbita no plano XY
        
        // Rotação própria dos corpos
        day = (day + 2) % 360;
        
        // Manter valores dentro de 360 graus
        if (planeta1_orbit >= 360.0) planeta1_orbit -= 360.0;
        if (planeta2_orbit >= 360.0) planeta2_orbit -= 360.0;
        if (lua1_orbit >= 360.0) lua1_orbit -= 360.0;
        if (lua2_orbit >= 360.0) lua2_orbit -= 360.0;
        
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sistema Solar - 2 Planetas com Luas");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    printf("Controles:\n");
    printf("Y - Iniciar/Parar animação dos planetas\n");
    printf("ESC - Sair\n");
    
    glutMainLoop();

    return 0;
}
