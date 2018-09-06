#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<string.h>
#include<math.h>
int ww = 640, wh = 480;  
  int first = 0;  
  int xi, yi, xf, yf;  
/* Function to plot a point */
void setPixel(GLint x, GLint y) {
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}

int X1, Y1, X2, Y2; 

/* Bresenham's Algorithm */
void Bresenham(int x1, int y1, int x2, int y2)
{
  int dx,dy,Po;
  int k=0;
  dx=(x2-x1);
  dy=(y2-y1);
  if(dy<=dx&&dy>0)
	  {
	  dx=abs(dx);
	  dy=abs(dy);
 	  Po=(2*dy)-dx;
	  setPixel(x1,y1);
	  int xk=x1;
	  int yk=y1;
	  for(k=x1;k<x2;k++)
	  { 
	    if(Po<0)
		{	
			setPixel(++xk,yk);
			Po=Po+(2*dy);
		}
	    else{
			setPixel(++xk,++yk);
			Po=Po+(2*dy)-(2*dx);
		}
	  }
	}
  else if(dy>dx&&dy>0)
          {
	  dx=abs(dx);
	  dy=abs(dy);
	  Po=(2*dx)-dy;
	  setPixel(x1,y1);
	  int xk=x1; int yk=y1;
	  for(k=y1;k<y2;k++)
	  { 
	    if(Po<0)
		{	
			setPixel(xk,++yk);
			Po=Po+(2*dx);
		}
	    else{
			setPixel(++xk,++yk);
			Po=Po+(2*dx)-(2*dy);
		}
	  }			
	}
  else if(dy>=-dx)
	 {
	  dx=abs(dx);
	  dy=abs(dy);
          Po=(2*dy)-dx;
	  setPixel(x1,y1);
	  int xk=x1;
	  int yk=y1;
	  for(k=x1;k<x2;k++)
	  { 
	    if(Po<0)
		{	
			setPixel(++xk,yk);
			Po=Po+(2*dy);
		}
	    else{
			setPixel(++xk,--yk);
			Po=Po+(2*dy)-(2*dx);
		}
	  }
         }
  else if(dy<-dx)
	{
	  dx=abs(dx);
	  dy=abs(dy);
 	  Po=(2*dy)-dx;
	  setPixel(x1,y1);
	  int xk=x1;
	  int yk=y1;
	  for(k=y1;k>y2;k--)
	  { 
	    if(Po<0)
		{	
			setPixel(xk,--yk);
			Po=Po+(2*dx);
		}
	    else{
			setPixel(++xk,--yk);
			Po=Po+(2*dx)-(2*dy);
		}
	  }
	}
  glFlush();
}
//displaying text
void *font = GLUT_BITMAP_TIMES_ROMAN_10;
void *fonts[] = {
      GLUT_BITMAP_9_BY_15,
      GLUT_BITMAP_TIMES_ROMAN_10,
      GLUT_BITMAP_TIMES_ROMAN_24
};

void show(int x, int y, char *string){
      int len, i;
      glRasterPos2f(x, y);
      len = (int) strlen(string);
      for (i = 0; i < len; i++)
            glutBitmapCharacter(font, string[i]);
}
void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  int i;
  //draw axis	
  for(i=-(ww/2);i<(ww/2);i=i+10)
  {
 	setPixel(i,0);
 	setPixel(0,i);
  } 
    //WRITING AXIS NAMES
    show(-(ww/2),0,"- X-AXIS");
    show((wh/2)+30,0,"X-AXIS");
    show(0,(wh/2)-10,"Y-AXIS");
    show(0,-(wh/2)+5,"- Y-AXIS");    
    glutSwapBuffers();
  glFlush();
}
//when mouse click for points on screen
  void mouse(int btn, int state, int x, int y) 
       {  
       if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
        { 
	char initial[10];
	char final[10];
       switch(first)  
       {  
       case 0:  
        xi = x-(ww/2);  
        yi = (wh/2)-y;  
        first = 1;  
	sprintf(initial,"X=%d,Y=%d",xi,yi);
	show(xi+5,yi,initial);
        break;  
       case 1:  
        xf = x-(ww/2);  
        yf = (wh/2)-y;
        sprintf(final,"X=%d,Y=%d",xf,yf);
	show(xf+5,yf,final);
	if(xi>xf)
	{
	  int temp=xi;
 	  xi=xf;
	  xf=temp;  
	  temp=yi;
 	  yi=yf;
	  yf=temp;  
	}
        Bresenham( xi, yi, xf, yf);  
        first = 0;  
        break;   
       }  
       }  
      }  

void init() { 
  glViewport(-(ww/2),0,(ww/2),0); 
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(ww, wh);
  glutCreateWindow("Bresenham's Algorithm");
  glClearColor(0.0,0.0,0.0,0);
  glColor3f(1.0,1.0,1.0);
  gluOrtho2D(-(ww/2),(ww/2),-(wh/2),(wh/2)); 
  
}
int main(int argc, char **argv) 
{
  glutInit(&argc, argv);
  init();
  glutDisplayFunc(draw);
  glutMouseFunc(mouse);  
  glutMainLoop();
  return 0;
}


