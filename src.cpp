#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include"Header.h"
#include<fstream>
#include<time.h>
//#include<SFML\Audio.hpp>
#include<GL/glut.h>
using namespace std;
char go[] = "Game Over", scorem[] = "SCORE";
char resetm[] = "Reset", backm[] = "B for Back", snake[] = "WORM";
char hs[] = "HIGH SCORE", strt[] = " START ", high[] = "HIGH SCORE";
char sureexit[] = "ARE YOU SURE YOU WANT TO EXIT", exitm[] = "EXIT";
char yes[] = "YES", no[] = "NO", back[] = "BACK";;
int score = 0, highscore, box1 = 0, stage_flag = 0, bit = 0, box2 = 0, ts;
fstream file;
int resume, reset = 0, quit = 0;
float s[200][2];//s->snake count, a-> turns position
int egg_x, egg_y, p, no_of_egg_ate = 0, eat = 0, size_of_snake = 1;//C-> no of egg ate eat->whether egg has ate or not
int choose_change = 0;
int exit_status = 0;
//sf::Music music, music1, music2;

void mousef(int b, int s, int x, int y)
{
	if (b == GLUT_LEFT_BUTTON&& s == GLUT_DOWN&& x >= 370 && x <= 380 && (700 - y) > 325 && (700 - y) < 340 && stage_flag == 0)
		exit(0);
	// for no to exit
	if (x > 485 && 700 - y >  310 && 700 - y < 350 && x < 545 && b == GLUT_LEFT_BUTTON && s == GLUT_DOWN && quit == 1)
	{
		choose_change = resume;
		quit = 0;
	}
	// for yes to exit
	if (x > 290 && 700 - y >  310 && 700 - y < 350 && x < 350 && b == GLUT_LEFT_BUTTON && s == GLUT_DOWN && quit == 1)
	{
		exit(0);
	}
	// for resume
	if (x > 350 && 700 - y >290 && 700 - y < 340 && x < 450 && b == GLUT_LEFT_BUTTON && s == GLUT_DOWN &&choose_change == 4)
	{
		choose_change = resume;

	}
	int y1 = 700 - y;
	if (b == GLUT_LEFT_BUTTON&& s == GLUT_DOWN && x > 1040 && x< 1136 && y1>383 && y1 < 424 && exit_status != 1 && quit != 1)
	{
		score = 0;
		no_of_egg_ate = 0;
	}
	else
		//for stage greater than 1 
	if (x > 580 && 700 - y >  315 && 700 - y < 345 && x < 690 && b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
	{
		//music1.stop();
		//music2.play();
		stage_flag = 1;
		//bit = 0;
	}
	else
		//for displaying the highscore in the stage =0
	if (b == GLUT_LEFT_BUTTON&& s == GLUT_DOWN &&x > 560 && (700 - y) > 268 && (700 - y) < 298 && x < 710 && stage_flag == 0)
	{
		stage_flag = 0;
		bit = 1;
	}
	else//for exit buttoon
	if (b == GLUT_LEFT_BUTTON&& s == GLUT_DOWN &&x > 585 && (700 - y) > 220 && (700 - y) < 250 && x < 680 && stage_flag == 0)
	{
		exit(0);
	}
	else
		//for coming back to
	if (b == GLUT_LEFT_BUTTON&& s == GLUT_DOWN &&x >570 && (700 - y) >330 && (700 - y) < 380 && x < 660)
	{
		stage_flag = 0;
		bit = 0;
	}


}
void motionp(int x, int y)
{
	if (stage_flag == 0)
	{
		if (x > 580 && (700 - y) > 317 && (700 - y) < 345 && x < 690 && box1 == 0)
		{
			box1 = 1;
			//	cout << "\t" << x << "\t" << y;

		}
		else
		if ((x < 580 || (700 - y) <  317 || (700 - y) > 345 || x > 690) && box1 == 1)
		{

			glColor3f(1, 1, 0);
			glBegin(GL_LINES);
			glVertex3f(605, 320, 4);
			glVertex3f(665, 320, 4);
			glEnd();
			box1 = 0;
			cout << "\t" << x << "\t" << y << endl;
		}
		if (x > 560 && (700 - y) > 268 && (700 - y) < 298 && x < 710 && box1 == 0)
		{
			box1 = 2;
			//cout << "\t" << x << "\t" << y;
		}
		else
		if ((x < 560 || (700 - y) < 268 || (700 - y) > 298 || x >710) && box1 == 2)
		{
			glColor3f(1, 1, 0);
			glBegin(GL_LINES);
			glVertex3f(570, 274, 4);
			glVertex3f(693, 274, 4);
			glEnd();
			box1 = 0;
		}
	}
	else
	{
		if (x > 1040 && (700 - y) > 383 && (700 - y) < 424 && x < 1136 && box1 == 0)
		{
			box1 = 1;
		}
		else
		if (x < 1040 || (700 - y) <  383 || (700 - y) > 424 || x > 1136 && box1 == 1)
		{
			glColor3f(0, 0, 0);
			glBegin(GL_POLYGON);
			glVertex3f(1040, 383, 1);
			glVertex3f(1040, 424, 1);
			glVertex3f(1136, 424, 1);
			glVertex3f(1136, 383, 1);
			glEnd();
			box1 = 0;
		}
	}
	//glutPostRedisplay();

}
void managexplus(int i)// for right movement
{
	s[i][0] += 10;
	if (s[i][0] == 820)
	{
		if (stage_flag == 1) s[i][0] = 20;
		else
		{
			exit_status = 1;
			choose_change = 4;
		}
	}
}

void manageyplus(int i)	// for upward movement
{
	s[i][1] += 10;
	if (s[i][1] >= 690)
	{
		if (stage_flag == 1) s[i][1] = 10;
		else
		{
			exit_status = 1;
			choose_change = 4;
		}
	}
}
void manageyneg(int i)	// for downward movement
{
	s[i][1] -= 10;
	if (s[i][1] < 10)
	{

		if (stage_flag == 1) s[i][1] = 680;
		else
		{

			choose_change = 4;
			exit_status = 1;
		}
	}
}
void managexneg(int i)	// for leftward movement
{
	s[i][0] -= 10;

	if (s[i][0] == 10)
	{

		if (stage_flag == 1) s[i][0] = 810;
		else
		{

			exit_status = 1;
			choose_change = 4;
		}
	}
}

void keypress(unsigned char key, int xpos, int ypos)
{

	if (exit_status != 1)
	{
		//flag = 1;
		if ((key == 'w' || key == 'W') && choose_change != 3 && choose_change != 1)
			choose_change = 1;
		else
		if ((key == 'd' || key == 'D') && choose_change != 2 && choose_change != 0)
			choose_change = 0;
		else
		if ((key == 'a' || key == 'A') && choose_change != 0 && choose_change != 2)
			choose_change = 2;
		else
		if ((key == 's' || key == 'S') && choose_change != 1 && choose_change != 3)
			choose_change = 3;
		else
			//for pause
		if ((key == 'p' || key == 'P') && choose_change != 4)
		{
			resume = choose_change;
			choose_change = 4;
			exit_status = 0;
		}
		//to quit
		if ((key == 'q' || key == 'Q') && choose_change != 4)
		{
			resume = choose_change;
			quit = 1;
			if (highscore == score)
			{
				file.seekg(0, ios::beg);
				file.write((char*)&score, sizeof(score));
			}
			file.seekg(0, ios::beg);
			file.read((char*)&highscore, sizeof(highscore));
		}
	}
	else
		//after gameover
	if (key == 'b' || key == 'B')
	{
		score = 0;
		no_of_egg_ate = 0;
		choose_change = 0;
		//music2.stop();
		//music1.play();

		s[0][1] = 150;
		s[0][0] = 150;
		stage_flag = exit_status = bit = 0;
		if (highscore == score)
		{
			file.seekg(0, ios::beg);
			file.write((char*)&score, sizeof(score));
		}
		file.seekg(0, ios::beg);
		file.read((char*)&highscore, sizeof(highscore));
		//exit(0);
	}
	glutPostRedisplay();
}

void drawString(const char *str, double x = 0, double y = 0, double size = 1.0) {
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(x, y, 0);
	glScalef(size / 120, size / 120, 1.0);
	int itemCt = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (str[i] == '\n') {
			itemCt++;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(x, y - size, 0);
			glScalef(size / 153.0, size / 153.0, 1.0);
		}
		else {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
		}
	}
	glPopMatrix();
}
void upkey(int key, int x, int y)
{
	int key1 = glutGetModifiers();
	//if (key1 == GLUT_ACTIVE_ALT);
	if (exit_status != 1)
	{
		//flag = 1;
		if (key == GLUT_KEY_UP && choose_change != 3 && choose_change != 1)
			choose_change = 1;
		else
		if (key == GLUT_KEY_RIGHT && choose_change != 2 && choose_change != 0)
			choose_change = 0;
		else
		if (key == GLUT_KEY_LEFT && choose_change != 0 && choose_change != 2)
			choose_change = 2;
		else
		if (key == GLUT_KEY_DOWN&& choose_change != 1 && choose_change != 3)
			choose_change = 3;
		else
		if (key == 'p')
		{
			choose_change = 4;
			exit_status = 0;
		}
	}
	if (key == 'q')
	{

		if (highscore == score)
		{
			file.seekg(0, ios::beg);
			file.write((char*)&score, sizeof(score));
		}
		file.seekg(0, ios::beg);
		file.read((char*)&highscore, sizeof(highscore));
		exit(0);
	}
	glutPostRedisplay();
}
void movementcond()
{
	int j = size_of_snake;
	switch (choose_change)
	{
	case 0:
		// move to right
		draw_polygon(s[0][0], s[0][1]);
		managexplus(0);
		break;
	case 1:
		//move upward case
		draw_polygon(s[0][0], s[0][1]);
		manageyplus(0);
		break;
	case 2:
		// move leftward condition
		draw_polygon(s[0][0], s[0][1]);
		managexneg(0);
		break;
	case 3:
		//move downward condition
		draw_polygon(s[0][0], s[0][1]);
		manageyneg(0);

		break;

	case 4:
		// in case of pause or gameover
		draw_polygon(s[0][0], s[0][1]);
		j = no_of_egg_ate * 2;
		while (j > 0)
		{
			draw_polygon(s[j][0], s[j][1]);
			j--;
		}

		break;
	}
}
// function for displaying the highscore 
void score_page()
{
	int i;
	glColor3f(1, 0, 0);
	glRasterPos3i(545, 501, 10);
	for (i = 0; i <= strlen(high); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, high[i]);
	glRasterPos3i(600, 474, 10);
	_itoa_s(highscore, scorea, 10);
	for (i = 0; i <= strlen(scorea); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scorea[i]);
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(570, 330, 1);
	glVertex3f(570, 380, 1);
	glVertex3f(660, 380, 1);
	glVertex3f(660, 330, 1);
	glEnd();
	glColor3f(1, 0, 0);
	glRasterPos3i(580, 350, 10);
	for (i = 0; i <= strlen(back); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, back[i]);
}
void reshapef(int w, int h)
{
	glutReshapeWindow(1350, 700);
	w = 1350, h = 700;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -10, 10);
	//else
	//glOrtho(0, 1350, 0, 700,-10,10);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	srand(time(NULL));
	// except first  page background is white 
	if (stage_flag != 0){
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else
	{
		// for first page background is black
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	glColor3f(0, 0, 0);
	glDrawBuffer(GL_BACK);
	int i, j;
	if (box1 == 1)
	{

		if (stage_flag != 0){
			glColor3f(1, 1, 0);

			glBegin(GL_POLYGON);
			glVertex3f(1040, 383, 3);
			glVertex3f(1040, 424, 3);
			glVertex3f(1136, 424, 3);
			glVertex3f(1136, 383, 3);
			glEnd();
		}
		else
		{
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex3f(605, 320, 4);
			glVertex3f(665, 320, 4);
			glEnd();
		}
	}
	if (box1 == 2)
	{

		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex3f(570, 274, 4);
		glVertex3f(693, 274, 4);
		glEnd();

	}
	if (stage_flag == 0 && bit == 0)
	{

		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON);
		glVertex3f(580, 315, 1);
		glVertex3f(580, 345, 1);
		glVertex3f(690, 345, 1);
		glVertex3f(690, 315, 1);
		glEnd();
		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON);
		glVertex3f(560, 268, 1);
		glVertex3f(560, 298, 1);
		glVertex3f(710, 298, 1);
		glVertex3f(710, 268, 1);
		glEnd();
		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON);
		glVertex3f(585, 220, 1);
		glVertex3f(585, 250, 1);
		glVertex3f(680, 250, 1);
		glVertex3f(680, 220, 1);
		glEnd();
		drawString(snake, 500, 450, 80);
		glColor3f(1, 0, 0);
		glRasterPos3i(600, 325, 2);
		for (int i = 0; i <= strlen(strt); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, strt[i]);
		glRasterPos3i(575, 275, 2);
		for (int i = 0; i <= strlen(hs); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, hs[i]);
		glRasterPos3i(610, 230, 10);
		for (int i = 0; i <= strlen(exitm); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, exitm[i]);

	}
	else
		//displays the high score
	if (stage_flag == 0 && bit == 1)
	{
		score_page();
	}
	//START THE GAME
	if (stage_flag != 0)
	{
		//glDisable(GL_COLOR_LOGIC_OP);
		glColor3f(0, 0.5, 0.5);
		for (i = 0; i <= 810; i += 10)
		{

			for (j = 0; j <= 700; j += 10)
			{
				if (j == 0 || j == 690 || i == 0 || i == 810){
					if (stage_flag == 1)
						glBegin(GL_LINE_LOOP);
					else
						glBegin(GL_POLYGON);
					glVertex2f(i, j);
					glVertex2f(i + 10, j);
					glVertex2f(i + 10, j + 10);
					glVertex2f(i, j + 10);
					glEnd();
				}
			}

		}

		glColor3f(0, .6, 0);
		movementcond();


		j = 1;
		while (j <= no_of_egg_ate * 2 && choose_change != 4)
		{
			if ((s[j][0] == s[0][0] && s[j][1] == s[0][1]))
			{
				exit_status = 1; choose_change = 4;
				break;
			}
			j++;
		}

		if (quit == 1)
		{
			choose_change = 4;
			glColor3f(.8, 0, 0);
			glBegin(GL_POLYGON);
			glVertex3f(250, 290, 1);
			glVertex3f(250, 450, 1);
			glVertex3f(600, 450, 1);
			glVertex3f(600, 290, 1);
			glEnd();
			glColor3f(1, 1, 0);
			glBegin(GL_POLYGON);
			glVertex3f(485, 310, 2);
			glVertex3f(485, 350, 2);
			glVertex3f(545, 350, 2);
			glVertex3f(545, 310, 2);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(290, 310, 2);
			glVertex3f(290, 350, 2);
			glVertex3f(350, 350, 2);
			glVertex3f(350, 310, 1);
			glEnd();

			glColor3f(0, 0, 0);


			glRasterPos3i(265, 400, 4);
			for (int i = 0; i <= strlen(sureexit); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sureexit[i]);

			glRasterPos3i(300, 325, 4);
			for (int i = 0; i <= strlen(yes); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, yes[i]);
			glRasterPos3i(500, 325, 4);
			for (int i = 0; i <= strlen(no); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, no[i]);
		}
		if (exit_status == 1)
		{
			glColor3f(0, 0, 0);
			glBegin(GL_POLYGON);
			glVertex3f(315, 270, 2);
			glVertex3f(315, 430, 2);
			glVertex3f(495, 430, 2);
			glVertex3f(495, 270, 2);
			glEnd();
			glColor3f(1, 1, 1);

			glRasterPos3i(362, 370, 10);

			for (i = 0; i <= strlen(go); i++)
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, go[i]);
			glRasterPos3i(357, 330, 10);

			for (i = 0; i <= strlen(backm); i++)
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, backm[i]);
			glColor3f(1, 0, 0);
		}
		else
		if (choose_change == 4 && quit != 1)
		{
			glColor3f(.8, 0, 0);
			glBegin(GL_POLYGON);
			glVertex3f(315, 270, 2);
			glVertex3f(315, 430, 2);
			glVertex3f(495, 430, 2);
			glVertex3f(495, 270, 2);
			glEnd();
			char s[] = "GAME PAUSED", re[] = "RESUME";
			glColor3f(1, 1, 0);
			glBegin(GL_POLYGON);
			glVertex3f(350, 290, 3);
			glVertex3f(350, 340, 3);
			glVertex3f(450, 340, 3);
			glVertex3f(450, 290, 3);
			glEnd();
			glColor3f(0, 0, 0);
			glRasterPos3i(340, 375, 4);
			for (int i = 0; i <= strlen(s); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
			glRasterPos3i(365, 310, 4);
			for (int i = 0; i <= strlen(re); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, re[i]);
		}
		j = no_of_egg_ate * 2;
		glColor3f(1, 0, 0);
		if (choose_change != 4)// in case of pause no changes have to be made on the body of the snake 
		{

			while (j > 0)
			{
				glColor3f(0, .6, 0);
				s[j][0] = s[j - 1][0];
				s[j][1] = s[j - 1][1];
				draw_polygon(s[j][0], s[j][1]);
				j--;
			}
		}

		i = 1;
		// boundary condition for snake to eat snake
		if ((abs(s[0][1] - egg_y) == 0 && (s[0][0] - egg_x) == 0))// || ((abs(s[0][0] - m)) <=7&& (s[0][1]-n)==0)))
		{
			/*music.setPlayingOffset(sf::seconds(1));
			music.play();*/
			eat = 0;
			no_of_egg_ate++;//no of egg ate
			score++;
			size_of_snake = no_of_egg_ate * 2;
			// for entering into the second stage
			if (score == 10)
				stage_flag = 2;

			// if the score of the current player is greater than change the highscore to the score scored by player
			if (score > highscore)
			{
				highscore = score;
			}

			j = size_of_snake;
			while (j > 0)
			{
				s[j][0] = s[j - 1][0];
				s[j][1] = s[j - 1][1];
				draw_polygon(s[j][0], s[j][1]);
				j--;
			}

		}
		//if egg is eaten the new position of the egg
		if (eat == 0)
		{

			egg_x = 1, egg_y = 2;
			while (egg_x % 10 != 0)
				egg_x = ((rand() % 790)) + 20;
			while (egg_y % 10 != 0)
				egg_y = ((rand() % 680)) + 10;
			eat = 1;
		}
		glColor3f(1, 0, 1);
		draw_polygon(egg_x, egg_y); //display the egg
		scoresheet();
	}
	glutSwapBuffers();
	glFlush();


}
void idle(int s)
{

	glutTimerFunc(60, idle, 20);
	glutPostRedisplay();
}
int main()
{
	s[0][1] = 150;
	s[0][0] = 150;

	for (int i = 1; i < 10; i++)
	{
		s[i][1] = s[i - 1][1] - 7;
		s[i][0] = s[i - 1][0] - 7;
	}

	/*if (!music.openFromFile("eat.wav"))
		std::cout << "Can't Find the file" << std::endl;
	if (!music1.openFromFile("angels1.wav"))
		std::cout << "Can't Find the file" << std::endl;
	if (!music2.openFromFile("hob.wav"))
		std::cout << "Can't Find the file" << std::endl;
	*/
		file.open("text", ios::in | ios::out | ios::binary);
	file.seekg(0, ios::beg);
	file.read((char*)&highscore, sizeof(highscore));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1350, 700);
	glutCreateWindow("Worm");
	/*music1.play();
	music1.setLoop(true);*/
	glutDisplayFunc(display);
	glutKeyboardFunc(keypress);
	glutTimerFunc(100, idle, 20);
	glutReshapeFunc(reshapef);
	glutMouseFunc(mousef);
	glutSpecialFunc(upkey);
	glutPassiveMotionFunc(motionp);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	file.close();
}