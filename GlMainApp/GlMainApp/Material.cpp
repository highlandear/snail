#include "Impl.hpp"
#include "gdraw.hpp"


GLfloat no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };				// �޲�����ɫ
GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };			// ������ɫ
GLfloat mat_ambient_color[] = { 0.8f, 0.6f, 0.2f, 1.0f };
GLfloat mat_diffuse[] = { 0.2f, 0.5f, 0.8f, 1.0f };			// ɢ����ɫ
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };		// ���淴����ɫ
GLfloat no_shininess[] = { 0.0f };						// ���淴��ָ��Ϊ0 
GLfloat low_shininess[] = { 5.0f };						// ���淴��ָ��Ϊ5.0
GLfloat high_shininess[] = { 100.0f };					// ���淴��ָ��Ϊ100.0
GLfloat mat_emission[] = { 0.3f, 0.2f, 0.3f, 0.0f };		// �������ɫ

void Material::init()
{
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };	// ������
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // �����
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };// �����
	GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };// ��Դλ��

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	///��ʼ��
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

	/** ��һ�е�һ�л��Ƶ���������������޻�����;���⡣*/
	glPushMatrix();
	glTranslatef(-2.0, 1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** ��һ�еڶ��л��Ƶ������������;���⣬���е͸߹⣬���޻����� ��*/
	glPushMatrix();
	glTranslatef(-0.75, 1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** ��һ�е����л��Ƶ������������;���⣬���к����ĸ߹⣬���޻����� ��*/
	glPushMatrix();
	glTranslatef(0.75, 1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** ��һ�е����л��Ƶ������������ͷ���⣬���޻����;��淴��⡣*/
	glPushMatrix();
	glTranslatef(2.0, 1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** �ڶ��е�һ�л��Ƶ������������ͻ����⣬�����淴��⡣*/
	glPushMatrix();
	glTranslatef(-2.0, 0.0, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** �ڶ��еڶ��л��Ƶ�����������⡢������;���⣬���е͸߹⡣*/
	glPushMatrix();
	glTranslatef(-0.75, 0.0, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** �ڶ��е����л��Ƶ�����������⡢������;���⣬���к����ĸ߹⡣*/
	glPushMatrix();
	glTranslatef(0.75, 0.0, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** �ڶ��е����л��Ƶ�����������⡢������ͷ���⣬���޾���⡣*/
	glPushMatrix();
	glTranslatef(2, 0.0, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** �����е�һ�л��Ƶ�����������������ɫ�Ļ����⣬���޾���⡣*/
	glPushMatrix();
	glTranslatef(-2.0, -1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** �����еڶ��л��Ƶ�����������������ɫ�Ļ������Լ�����⣬���е͸߹⡣*/
	glPushMatrix();
	glTranslatef(-0.75, -1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** �����е����л��Ƶ�����������������ɫ�Ļ������Լ�����⣬���к����ĸ߹⡣*/
	glPushMatrix();
	glTranslatef(0.75, -1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	/** �����е����л��Ƶ�����������������ɫ�Ļ������Լ�����⣬���޾���⡣*/
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