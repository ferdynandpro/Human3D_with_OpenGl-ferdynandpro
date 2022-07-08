#include <iostream>
#include <vector>
#include <stdlib.h>
#include <GL/freeglut.h>

#include "imageloader.h"
#include "textureloader.h"
//Ferdynand Silalahi<672020028>

bool movement = false;
float XR = 0.0f; //xr = rotasi x
float YR = 0.0f; //yr = rotasi y
float XP = 0.0f; //xp = pergerakan x
float YP = 0.0f;//yp = pergerakan y
float ZP = 0.0f;//zp = pergerakan z
float sizes = 1.0f;

void display();

void LoadTexture() { //Texture pada folder texturloader.h
	Model file = Model("J:/672020028/672020028/Woman1.tga");
	glEnable(GL_TEXTURE_2D);
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, file.HasAlphaChannel() ? GL_RGBA : GL_RGB, file.GetWidth(), file.GetWidth(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, file.GetPixels().data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void transform() {//transformasi animasi berputar
	glRotatef(XR, 0.0f, 0.0f, 1.0f);
	glRotatef(YR, 0.0f, 1.0f, 0.0f);
	glTranslatef(XP, YP, ZP);
	glScalef(sizes, sizes, sizes);
	movement = true;
}

void timer(int) {//waktu/durasi animasi
	glutTimerFunc(1000 / 30, timer, 0);
	if (movement)
		YR += 5.0f;
	else
		YR = YR;
	glutPostRedisplay();
}

void display() {
	//perulangan untuk membaca file .nfg
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	loaderNfg objek;
	objek.readfile();

	int menampilkan = objek.totalNFG / 3;

	LoadTexture();

	gluLookAt(0.0, 2.0, 8.0, 0.0, 1.5, 3.0, 0, 1, 0);
	transform();
	for (int i = 0; i < menampilkan; i++) {//looping

		glBegin(GL_TRIANGLES);
		glTexCoord2f(objek.JumlahVertex[objek.JumlahTampilan[i].pos.x].uv.x, objek.JumlahVertex[objek.JumlahTampilan[i].pos.x].uv.y);
		glVertex3f(objek.JumlahVertex[objek.JumlahTampilan[i].pos.x].pos.x,
			objek.JumlahVertex[objek.JumlahTampilan[i].pos.x].pos.y,
			objek.JumlahVertex[objek.JumlahTampilan[i].pos.x].pos.z);
		glTexCoord2f(objek.JumlahVertex[objek.JumlahTampilan[i].pos.y].uv.x, objek.JumlahVertex[objek.JumlahTampilan[i].pos.y].uv.y);
		glVertex3f(objek.JumlahVertex[objek.JumlahTampilan[i].pos.y].pos.x,
			objek.JumlahVertex[objek.JumlahTampilan[i].pos.y].pos.y,
			objek.JumlahVertex[objek.JumlahTampilan[i].pos.y].pos.z);
		glTexCoord2f(objek.JumlahVertex[objek.JumlahTampilan[i].pos.z].uv.x, objek.JumlahVertex[objek.JumlahTampilan[i].pos.z].uv.y);
		glVertex3f(objek.JumlahVertex[objek.JumlahTampilan[i].pos.z].pos.x,
			objek.JumlahVertex[objek.JumlahTampilan[i].pos.z].pos.y,
			objek.JumlahVertex[objek.JumlahTampilan[i].pos.z].pos.z);
		glEnd();
	}
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void ukuran(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w > h) {
		glViewport(0, 0, w, w);
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		glScalef(-0.5, 0.5, -0.5);
	}
	else {
		glViewport(0, 0, w, h);
	}

	gluPerspective(20.0, w / h, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myinit() {
	glClearColor(0.0, 1.0, 6.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
}

void keyboard(unsigned char key, int x, int y) { //Melakukan Fungsi Keyboard
	switch (key) {
	case 'q':
	case 'Q': //ke depan
		sizes += 0.2f;
		break;
	case 'e':
	case 'E'://ke belakang
		sizes -= 0.2f;
		break;
	case 'a':
	case 'A'://ke kanan 
		YR -= 5.0f;
		break;
	case 'd':
	case 'D'://ke kiri
		YR += 5.0f;
		break;
	case 's':
	case 'S'://ke atas
		XR += 5.0f;
		break;
	case 'w':
	case 'W'://ke bawah
		XR -= 5.0f;
		break;
	case '`': // menutup window
		exit(1);
	}
	glutPostRedisplay();
}

void keyboard1(int key, int x, int y) {
	switch (key) {
	case 100:
		XP -= 0.025f;
		break;
	case 101:
		YP += 0.025f;
		break;
	case 102:
		XP += 0.025f;
		break;
	case 103:
		YP -= 0.025f;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("TR_672020028_Ferdynand Silalahi");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	glutTimerFunc(0, timer, 0);
	glutReshapeFunc(ukuran);
	glutDisplayFunc(display);
	myinit();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard1);
	glutMainLoop();
	return 0;
}