#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
bool turnonanimation = false;
double rotation=0;
double cam = 0;
bool up = true;
int view = 1;
#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)




class Vector3f {
public:
	double x, y, z;

	Vector3f(double _x = 0.0f, double _y = 0.0f, double _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f const &v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f  const &v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(double n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(double n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;
public:double eyeX = 0; double eyeY = 3.0f; double eyeZ = 0.1f;

	Camera(double _eyeX=0, double _eyeY =0, double _eyeZ = 0, double centerX = 0.0f, double centerY = 0.0f, double centerZ = 0.0f, double upX = 0.0f, double upY = 1.0f, double upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(double d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(double d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(double d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(double a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(double a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}

	void updateEye(double x,double y,double z) {
		eye = Vector3f(x, y, z);

	}
};

class Jack {
public:
	double r1;
	double g1;
	double b1;

	double r1R;
	double g1R;
	double b1R;

	int random;

	Jack() {


	}
	void color_random() {
		if(random==0) return; {
			r1 = (rand()%11)*(0.1);
			g1 = (rand()%11)*(0.1);
			b1 = (rand()%11)*(0.1);

		}

	}
	void reset() {
		random = 0;
		r1 = .2;
		g1 = .6;
		b1 = .8;

	}
	void drawJackPart() {
		glPushMatrix();
		glScaled(0.2, 0.2, 1.0);
		glutSolidSphere(1, 15, 15);
		glPopMatrix();
		glPushMatrix();
		glTranslated(0, 0, 1.2);
		glutSolidSphere(0.2, 15, 15);
		glTranslated(0, 0, -2.4);
		glutSolidSphere(0.2, 15, 15);
		glPopMatrix();
	}
	void drawJack() {
		glPushMatrix();
		drawJackPart();
		glRotated(90.0, 0, 1, 0);
		drawJackPart();
		glRotated(90.0, 1, 0, 0);
		drawJackPart();
		glPopMatrix();
	}
public: void draw() {
	glPushMatrix();
	glTranslated(0, cam*.1, 0);

	glPushMatrix();
	glTranslated(0.35, 0.45, -.86);
	glRotated(45, 0, 0, 1);
	glScaled(0.08, 0.08, 0.08);
	glColor3d(r1, g1, b1);

	drawJack();//
	glPopMatrix();

	glPopMatrix();

}
};

class Ghost {
public:Vector3f pos;

	   double moving;
		 double angel ;

	   Ghost() {

		   moving = 1.5;
	   }
		 void updatelocation(){
			 moving-=.001;
			 angel+=.75;

			 if(moving<-1)
			 		moving=1.3;
				if(angel>360)
						angel=0;
		 }

	   void show() {
		   glPushMatrix();
		   glTranslated(0+.5, 0, moving);
		   glPushMatrix();

			 glPushMatrix();

			 glTranslated(0.25, 0.42, 0.35);

			 glRotated(angel , 0, 1, 0);
			 glTranslated(-0.25, -0.42, -0.35);


		   glPushMatrix();
		   glTranslated(0.26, 0.45, 0.39);
		   glScaled(0.1*0.05 ,0.15*0.05, 0.1*0.05);
		   glColor3d(.6, .5, .7);
			 glutSolidSphere(3,15,15);
		   glPopMatrix();



		   glPushMatrix();
		   glTranslated(0.25, 0.42, 0.35);
		   glScaled(0.1*0.5,0.15*0.5,0.1*0.5);
		   glColor3d(1,1,0.9);
			 glutSolidSphere(1,15,15);
		   glPopMatrix();

			 glPopMatrix();

		   glPushMatrix();
		   glTranslated(0.25, 0.29, 0.35);
		   glScaled(0.15*0.5, 0.35, 0.1*0.5);
		   glColor3d(0, 0, 0);
		   glutSolidCube(1);
		   glPopMatrix();



		   glPushMatrix();
		   glTranslated(0.30, 0.33, 0.3);
		   glRotated(90, 1, 0, 0);
		   glScaled(0.15*0.2, 0.15, 0.1*0.2);
		   glutSolidCube(1);
		   glPopMatrix();


		   glPushMatrix();
		   glTranslated(0.20, 0.33, 0.3);
		   glRotated(90 , 1, 0, 0);
		   glScaled(0.15*0.2, 0.15, 0.1*0.2);
		   glutSolidCube(1);
		   glPopMatrix();


		   glPopMatrix();
		   glPopMatrix();
		   glPopMatrix();

	   }
};


class Table {
public:double R;
	   double G;
	   double B;
	   Table() {

	   }
public: void drawTable(double topWid, double topThick, double legThick, double legLen) {
	glPushMatrix();
	glTranslated(0.5, 0.5 * 0.2, 0.5);
	glRotated(rotation, 0, 1, 0);
	glTranslated(-0.5, -0.5 * 0.2, -0.5);
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glColor3d(.37, .99, .25);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.5 * 0.2+3, 0.5);
	glutSolidTeapot(0.8);
	glPopMatrix();


	double dist = 0.95*topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	glPopMatrix();
}

	void drawTableLeg(double thick, double len) {
			glPushMatrix();
			glTranslated(0, len / 2, 0);
			glScaled(thick, len, thick);
			glutSolidCube(1.0);
			glPopMatrix();
		}


};



class Chair {
public:
			double r1;
	   double g1;
	   double b1;
	   double r2;
	   double g2;
	   double b2;



	   int random;

	   Chair() {



	   }
public: void color_random() {
		if(random==0) return;
		r1 = (rand()%11)*(0.1);
		g1 = (rand()%11)*(0.1);
		b1 = (rand()%11)*(0.1);
		r2 = (rand()%11)*(0.1);
		b2 = (rand()%11)*(0.1);
		g2 = (rand()%11)*(0.1);



}
		void reset() {
			random = false;
			r1 = .7;
 		 g1 = .6;
 		 b1 = .3;
 		 r2 = .91;
 		 b2 = .3;
 		 g2 = .6;
		}
public:void draw(double t,double th,double lh,double ll) {

	drawTable(t,th,lh,ll);

}
public: void drawTable(double topWid, double topThick, double legThick, double legLen) {
	glPushMatrix();
	glTranslated(0.5, 0.5 * 0.2, 0.5);
	glRotated(rotation, 0, 1, 0);
	glTranslated(-0.5, -0.5 * 0.2, -0.5);
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();




	double dist = 0.95*topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
	glPopMatrix();
}

	void drawTableLeg(double thick, double len) {
			glPushMatrix();
			glTranslated(0, len / 2, 0);
			glScaled(thick, len, thick);
			glutSolidCube(1.0);
			glPopMatrix();
		}

};

class Bed {

public:
	double r1;
	double g1;
	double b1;
	double r2;
	double g2;
	double b2;
	double r3;
	double g3;
	double b3;


	int random=0;

	Bed() {

	}

	void reset() {
		random = 0;
		r1 = .8;
		g1 = .2;
		b1 = .4;
		r2 = .3;
		g2 = .8;
		b2 = 1;
		r3 = .4;
		g3 = .2;
		b3 = .6;
	}
void color_random(){
	if(random==0)
		return;
	g1 = (rand() % 201)*0.01;
	b1 = (rand() % 201)*0.01;
	r2 = (rand() % 201)*0.01;
	r1 = (rand()%100)*.0001;
	g2 = (rand()%1000)*.0001;
	b2 = (rand()%11)*(0.1);
	r3 = (rand()%11)*(0.1);
	g3 = (rand()%1000)*.0001;
	b3 = (rand()%11)*(0.1);

}


public: void draw() {


	glPushMatrix();
	glTranslated(0, cam*.1, .18);

	glPushMatrix();
	glTranslated(0.8, 0.2, -0.5);
	glScaled(0.35, 0.1, 0.5);
	glColor3d(r2, g2, b2);
	glutSolidCube(1.f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.8, 0.1, -0.27);
	glScaled(0.35, 0.1, 0.03);
	glColor3d(r2, g2, b2);
	glutSolidCube(1.f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.8, 0.1, -0.73);
	glScaled(0.35, 0.1, 0.03);
	glColor3d(r2, g2, b2);
	glutSolidCube(1.f);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0.8, 0.23, -0.5);
	glScaled(0.35*0.9, 0.1*0.9, 0.5*0.9);
	glColor3d(r1, g1, b1);
	glutSolidCube(1.f);
	glPopMatrix();

	glPopMatrix();

}


};
class Komodeno {
public:
		 double r1;
	   double g1;
	   double b1;
	   double r2;
	   double g2;
	   double b2;


		 int random=0;


 public: void color_random() {
		if(random==0)return;
		r1 = (rand()%11)*(0.1);
		g1 = (rand()%11)*(0.1);
		b1 = (rand()%11)*(0.1);
		r2 = (rand()%11)*(0.1);
		g2 = (rand()%11)*(0.1);
		b2 = (rand()%11)*(0.1);

}
		void reset() {
			r1 = .2;
	 		g1 = .5;
	 		r2 = 1;
	 		g2 = .7;
	 		b2 = .2;
			random=0;
		}
public: void draw() {
	b1 = .3;
	glPushMatrix();
	glTranslated(.01, cam*.1, .08);
	glPushMatrix();
	glTranslated(0.3, 0.2, -0.8);
	glScaled(0.26, 0.35, 0.16);
	glColor3d(r1, g1, b1);
	glutSolidCube(1.f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.1, 0);
	glPushMatrix();
	glTranslated(0.3, 0.2, -0.70);
	glScaled(0.26*0.75, 0.35*0.3, 0.16*0.3);
	glColor3d(r1, g1, b1);
	glutSolidCube(1.f);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.3, 0.2, -0.70);
	glScaled(0.03, 0.03, 0.03);
	glColor3d(r2,  g2, b2);
	glutSolidSphere(1.f, 50, 50);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}
};

class Wall {
public:
	double r1;
	double g1;
	double b1;
	double old_r;
	double old_b;
	double old_g;
	int random=0;

public:Wall(double R,double G,double B) {
		   r1 = R;
		   b1 = B;
		   g1 = G;
		   old_r = r1;
		   old_g = g1;
		   old_b = b1;



	   }
public: void drawWall() {
	glPushMatrix();

	glTranslated(0.5, 0.5 *.02, 0.5);
	glRotated(rotation, 0, 1, 0);
	glColor3d(r1, g1, b1);
	glScaled(1.0, 0.5 *.02, 1.0);

	glutSolidCube(1);
	glPopMatrix();
}

		void color_random() {
			if(random==0) return;

				r1 = (rand()%11)*(0.1);
				g1 = (rand()%11)*(0.1);
				b1 = (rand()%11)*(0.1);


		}
		void reset() {
			random = false;
			r1 = old_r;
			g1 = old_g;
			b1 = old_b;
		}
};




class Mirror {
public:
	double r1;
	double g1;
	double b1;
	double r2;
	double g2;
	double b2;
	double r3;
	double g3;
	double b3;



	int random=0;

	Mirror() {

	}
	void color_random() {
		if(random==0) return; {
			r1 = (rand()%11)*(0.1);
			g1 = (rand()%11)*(0.1);
			b1 = (rand()%11)*(0.1);
			r2 = (rand()%11)*(0.1);
			b2 = (rand()%11)*(0.1);
			g2 = (rand()%11)*(0.1);
			r3 = (rand()%11)*(0.1);
			b3 = (rand()%11)*(0.1);
			g3 = (rand()%11)*(0.1);
		}

	}
	void reset() {
		r1 = 1;
		g1 = .2;
		b1 = .8;

		r2 = .3;
		g2 = .4;
		b2 = 1;

		r3 = .7;
		g3 = .28;
		b3 = .23;

		random=0;
	}
public: void draw() {
	glPushMatrix();
	glTranslated(0, cam*.1, .6);

	glPushMatrix();
	glTranslated(-0.01, 0.6, -0.15);
	glScaled(0.26*0.2, 0.35*1.3, 0.16*1.5);
	glColor3d(r1, b1, g1);
	glutSolidCube(1.f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.02, 0.6, -0.15);
	glScaled(0.26*0.2, 0.35*1.3, 0.16*1.5);
	glColor3d(r2, b2, g2);
	glutSolidCube(.9f);
	glPopMatrix();


glPushMatrix();
glTranslated(.02+.02, 0.02+.79, -0.15-.02);
glScaled(0.26*0.2, 0.35*1.3, 0.16*1.5);
glColor3d(r3, b3, g3);
glutSolidCube(.2);
glPopMatrix();


	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}
};






Camera camera;
Ghost ghost;

Chair chair;
Chair chair2;

Table table;
Wall w1(.2f,.8,.3f);
Wall w2(.4f, 1, .6f);
Wall w3(.8f, .1f, .2f);
Wall w4(.7f, .1f, .3f);
Wall w5(.6f, .1f, .6f);
Wall w6(.5f, .1f, .4f);
Bed bed;
Jack jack;
Komodeno k1;
Mirror mirror;

void anime() {
	if (turnonanimation) {
		rotation += 0.1;


		if(cam>=1)
			up=false;
			else 	if ( up) {
			cam += 0.15;
		}




	}


	ghost.updatelocation();


	glutPostRedisplay();

}



void drawJackPart() {
	glPushMatrix();
	glScaled(0.2, 0.2, 1.0);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, 1.2);
	glutSolidSphere(0.2, 15, 15);
	glTranslated(0, 0, -2.4);
	glutSolidSphere(0.2, 15, 15);
	glPopMatrix();
}
void drawJack() {
	glPushMatrix();
	drawJackPart();
	glRotated(90.0, 0, 1, 0);
	drawJackPart();
	glRotated(90.0, 1, 0, 0);
	drawJackPart();
	glPopMatrix();
}


void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, 640 / 480, 0.001, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}



void Display() {
	setupCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ghost.show();

	glPushMatrix();
	glTranslated(.5, 0, 0.8);
	glColor3d(0.5, 0.3, 0.4);
	chair.draw(.2, .03, 0.01, .19);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.5, .37, .91);
	glScaled(0.3*0.5, 0.35, 0.1*0.2);
	glColor3d(0.5, 0.3, 0.4);
	glutSolidCube(1);
	glPopMatrix();






	glPushMatrix();
	glScaled(0.1, 0.1, 0.1);
	glTranslated(4, 0, 4);
	table.drawTable(4, 1, 0.1, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4, 0.0, 0.4);
	glPopMatrix();

	w1.drawWall();
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);

	w2.drawWall();
	glPopMatrix();
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	w3.drawWall();
	glPopMatrix();

	bed.draw();

	jack.draw();


glPushMatrix();
glTranslated(0.3, 0.2, -0.8);

glRotated(90, 0.0, 1.0, 0.0);
glTranslated(-0.3, -0.2, 0.8);
	k1.draw();
	mirror.draw();

	glPopMatrix();





	glPushMatrix();
	glTranslated(0, 0.0, -1.0);
	glPushMatrix();
	glTranslated(0.4, 0.0, 0.4);
	glPopMatrix();
	glColor3d(.8, .1, .3);
	w4.drawWall();
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);

	glColor3d(.4, .2, 1);
	w5.drawWall();
	glPopMatrix();
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	w6.drawWall();
	glPopMatrix();
	glPopMatrix();



	glFlush();
}

void Keyboard(unsigned char key, int x, int y) {
	double d = 0.02;
if(key =='y')
 turnonanimation = true;
 if(	key== 'u'){
 		turnonanimation = false;

 		rotation =0;
 		cam = 0;
	}
	if(key=='p') camera.updateEye(0,3.0f,0.1f);
	if(key=='o')  camera.updateEye(2.f, 1.0f, 2.0f);
	if(key=='i')  camera.updateEye(-2.f, 1.0f, 2.0f);


	switch (key) {
	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;
	case 'f':
		w1.random = 1^w1.random;
		w2.random = 1^ w2.random;
		w3.random = 1^w3.random;
		w4.random = 1^w4.random;
		w5.random = 1^w5.random;
		w6.random = 1^w6.random;
		bed.random =1 ^ bed.random;
		k1.random = 1 ^ k1.random;
		mirror.random = 1^ mirror.random;
		jack.random = 1^ jack.random;
		chair.random = 1^ chair.random;
		 break;
	case 'r':

		w1.reset();
		w2.reset();
		w3.reset();
		w4.reset();
		w5.reset();
		w6.reset();
		bed.reset();
		k1.reset();
		mirror.reset();
		jack.reset();
		chair.reset();
		break;




	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	double a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

void randoms(int val) {

	w1.color_random();
	w2.color_random();
	w3.color_random();
	w4.color_random();
	w5.color_random();
	w6.color_random();
	bed.color_random();
	k1.color_random();
	mirror.color_random();
	jack.color_random();
	chair.color_random();
	glutTimerFunc(600, randoms,0);
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(1280, 768);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Hor");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutIdleFunc(anime);
	glutTimerFunc(0, randoms, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
	return 0;
}
