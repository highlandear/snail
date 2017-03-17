#include "Impl.hpp"
#include "gdraw.hpp"


GLfloat no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };				// 无材质颜色
GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };			// 环境颜色
GLfloat mat_ambient_color[] = { 0.8f, 0.6f, 0.2f, 1.0f };
GLfloat mat_diffuse[] = { 0.2f, 0.5f, 0.8f, 1.0f };			// 散射颜色
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };		// 镜面反射颜色
GLfloat no_shininess[] = { 0.0f };						// 镜面反射指数为0 
GLfloat low_shininess[] = { 5.0f };						// 镜面反射指数为5.0
GLfloat high_shininess[] = { 100.0f };					// 镜面反射指数为100.0
GLfloat mat_emission[] = { 0.3f, 0.2f, 0.3f, 0.0f };		// 发射光颜色

void Material::init()
{
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };	// 环境光
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // 漫射光
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };// 镜面光
	GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };// 光源位置

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	///初始化
	glClearColor(0.0f, 0.2f, 0.2f, 0.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void Material::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/** 第一行第一列绘制的球仅有漫反射光而无环境光和镜面光。*/
	glPushMatrix();
	glTranslatef(-2.0, 1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** 第一行第二列绘制的球有漫反射光和镜面光，并有低高光，而无环境光 。*/
	glPushMatrix();
	glTranslatef(-0.75, 1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** 第一行第三列绘制的球有漫反射光和镜面光，并有很亮的高光，而无环境光 。*/
	glPushMatrix();
	glTranslatef(0.75, 1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** 第一行第四列绘制的球有漫反射光和辐射光，而无环境和镜面反射光。*/
	glPushMatrix();
	glTranslatef(2.0, 1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** 第二行第一列绘制的球有漫反射光和环境光，而镜面反射光。*/
	glPushMatrix();
	glTranslatef(-2.0, 0.0, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** 第二行第二列绘制的球有漫反射光、环境光和镜面光，且有低高光。*/
	glPushMatrix();
	glTranslatef(-0.75, 0.0, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** 第二行第三列绘制的球有漫反射光、环境光和镜面光，且有很亮的高光。*/
	glPushMatrix();
	glTranslatef(0.75, 0.0, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** 第二行第四列绘制的球有漫反射光、环境光和辐射光，而无镜面光。*/
	glPushMatrix();
	glTranslatef(2, 0.0, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** 第三行第一列绘制的球有漫反射光和有颜色的环境光，而无镜面光。*/
	glPushMatrix();
	glTranslatef(-2.0, -1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** 第三行第二列绘制的球有漫反射光和有颜色的环境光以及镜面光，且有低高光。*/
	glPushMatrix();
	glTranslatef(-0.75, -1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** 第三行第三列绘制的球有漫反射光和有颜色的环境光以及镜面光，且有很亮的高光。*/
	glPushMatrix();
	glTranslatef(0.75, -1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** 第三行第四列绘制的球有漫反射光和有颜色的环境光以及辐射光，而无镜面光。*/
	glPushMatrix();
	glTranslatef(2, -1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	gdraw::drawBall(0.5);
	glPopMatrix();

	glFlush();
}