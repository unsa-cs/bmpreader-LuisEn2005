#include "bmp.h"
#include <GL/glut.h>
#include <stdio.h>

BMPImage *image;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  if (image) {
    drawBMP(image);
  }
  glFlush();
}

int main(int argc, char *argv[]) {
  char filename[256];
  if(!argv[1]){
    printf("No se ingresó un archivo\n");
    printf("Recuerde ingresarlo con la extensión .bmp\n");
    return 1;
  }
  int i;
  for(i = 0; argv[1][i]!= '\0';i++){
    filename[i] = argv[1][i];
  }
  filename[i] = '\0';

  image = readBMP(filename);

  if (!image) return 1;
  printf("Abriendo archivo %s\n",argv[1]);

  // Inicializar GLUT
  glutInit(&argc, argv);

  // Establecer el modo de visualización
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(image->width, image->height);
  glutCreateWindow("Visualizador de BMP");

  glLoadIdentity();
  glOrtho(0, image->width, image->height, 0, -1, 1);

  glutDisplayFunc(display);
  glutMainLoop();

  freeBMP(image);
  return 0;
}
