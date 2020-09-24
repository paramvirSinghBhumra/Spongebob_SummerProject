#include "helperFunctions.h"


//texture arrays
unsigned int spongebob_front; //front pants, side pants, etc.
unsigned int spongebob_side;
unsigned int spongebob_house;
unsigned int spongebob_door;
unsigned int squidward_door;
unsigned int window;
unsigned int surprise_window;
unsigned int leaves;
unsigned int sand; // sand texture (we'll use this for squidward's house too)
unsigned int patrick_pants;
unsigned int patrick_back;
unsigned int patrick_house;
unsigned int patrick_face;

int    sky[2];   //  Sky textures
int axes=0;       //  Display axes
int mode=0;       //  Projection mode
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=5.0;   //  Size of world
double idle = 0.0;
int window_width = 600;
int window_height = 600;
int left_click_down = 0;
int saved_th = 0;
int saved_ph = 0;
int light = 1;
int camera = 1;
int one       =   1;  // Unit value
int distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny = 1;    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   1.5;  // Elevation of light
int modify = 1;       // Will allow us to move the light
float xPos = 0.0;     // X position of the light
float yPos = 0.0;     // Y position of the light


/*
 *  Draw vertex in polar coordinates with normal
 */
void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
    glTexCoord2d(th/360.0,ph/180.0+0.5);
   glVertex3d(x,y,z);
}


/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny+3);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// spongebob squarepants section
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
*  Draw a sphere
*     color (r,g,b)
*     at (x,y,z)
*     radius (radius)
*/
void SPHERE(double r, double g, double b, double x, double y, double z, double radius){
    int ph, th;
    glPushMatrix();
    //  Offset, scale and rotate
    glTranslated(x,y,z);
    glScaled(radius,radius,radius);
    //  White ball
    glColor3f(r,g,b);
    //  Bands of latitude
    for (ph=-90;ph<90;ph+=inc)
    {
       glBegin(GL_QUAD_STRIP);
       for (th=0;th<=360;th+=2*inc)
       {
          Vertex(th,ph);
          Vertex(th,ph+inc);
       }
       glEnd();
    }
    //  Undo transofrmations
    glPopMatrix();
}


/*
*  Draw a hand
*     at (x,y,z)
*/
void drawHand(double x, double y, double z){
    double r = 248/255.0, g = 234/255.0, b = 76/255.0;
    glPushMatrix();
    glTranslated(x,y,z);
    SPHERE(r,g,b, 0,0,0, 0.75);
    glPopMatrix();


    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(0.7,4,0.7);
    SPHERE(r,g,b, 0,0.3,0, 0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(20, 0,0,1);
    glScaled(0.7,4,0.7);
    SPHERE(r,g,b, -0.5,0.3,0, 0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(-20, 0,0,1);
    glScaled(0.7,4,0.7);
    SPHERE(r,g,b, 0.5,0.3,0, 0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(-45, 0,0,1);
    glScaled(0.7,4,0.7);

    SPHERE(r,g,b, 0.5,0.3,0, 0.3);
    glPopMatrix();
}

/*
*  Draw a shoe
*     at (x,y,z)
*/
void drawShoe(double x, double y, double z){
    double r = 0, g = 0, b = 0;
    glPushMatrix();
    glTranslated(x,y,z);

    SPHERE(r,g,b, 0,0,0, 1);


    // front
   glColor3f(r,g,b);
    glNormal3f(0,0,1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,2.5);
    for (int k=0;k<=360;k+=10)
    {
        glVertex3f(Cos(k),Sin(k), 2.5);
    }
    glEnd();


    // back
    glNormal3f(0,0,-1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,0);
    for (int k=0;k<=360;k+=10)
    {
        glVertex3f(0.7*Cos(k),0.7*Sin(k),0);
    }
    glEnd();

   //edge
   glBegin(GL_QUAD_STRIP);
   for (int k=0;k<=360;k+=10)
   {
       glNormal3f(0.85*Cos(k),0.85*Sin(k), 0);
       glVertex3f(Cos(k),Sin(k), 2.5);
      glVertex3f(0.7*Cos(k),0.7*Sin(k), 0);
   }
   glEnd();



    glPopMatrix();
}

/*
*  Draw spongebob's arm
*     with scale (scale)
*     at (x,y,z)
*/
void draw_sb_arms(double scale, double x, double y, double z){
    glPushMatrix();

    if(x<0){
        glTranslated(x-0.5,y,z);
        glRotated(-45,0,0,1);
    }
    else{
        glTranslated(x+0.5,y,z);
        glRotated(45,0,0,1);
    }

    glScaled(scale*5,scale,scale);

    //  ends
    glColor3f(248/255.0,234/255.0,76/255.0);
    for (int i=1;i>=-1;i-=2)
    {
       glNormal3f(i,0,0);
       glBegin(GL_TRIANGLE_FAN);
    //       glTexCoord2f(0.5,0.5);
       glVertex3f(i,0,0);
       for (int k=0;k<=360;k+=10)
       {
    //          glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
           glVertex3f(i,0.7*Cos(k),0.7*Sin(k));
       }
       glEnd();
    }

    //edge
    glBegin(GL_QUAD_STRIP);
    for (int k=0;k<=360;k+=10)
    {
        glNormal3f(0,0.7*Cos(k),0.7*Sin(k));
       glVertex3f(+1,0.7*Cos(k),0.7*Sin(k));
       glVertex3f(-1,0.7*Cos(k),0.7*Sin(k));
    }

    glEnd();
    glPopMatrix();

    glPushMatrix();
    if(x<0){
        glTranslated(x-1.5,y+1,z);
        glRotated(45,0,0,1);
    }
    else{
        glTranslated(x+1.5,y+1,z);
        glRotated(-45,0,0,1);
    }
    glScaled(scale,scale,scale);
    drawHand(0,-2,0);
    ErrCheck("Spongebob-arms");
    glPopMatrix();

}

/*
*  Draw spongebob's legs
*     with scale (scale)
*     at (x,y,z)
*/
void draw_sb_legs(double scale, double x, double y, double z){
    glPushMatrix();
        glTranslated(x,y-1,z);
        glScaled(scale,scale*5,scale);
    //      ends
        glColor3f(248/255.0,234/255.0,76/255.0);
        for (int i=1;i>=-1;i-=2)
        {
           glNormal3f(0,i,0);
           glBegin(GL_TRIANGLE_FAN);
    //       glTexCoord2f(0.5,0.5);
           glVertex3f(0,i,0);
           for (int k=0;k<=360;k+=10)
           {
    //          glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
               glVertex3f(0.8*Cos(k),i,0.8*Sin(k));
           }
           glEnd();
        }
        //edge
        glBegin(GL_QUAD_STRIP);
        for (int k=0;k<=360;k+=10)
        {
           glNormal3f(0.8*Cos(k),0,0.8*Sin(k));
           glVertex3f(0.8*Cos(k),+1,0.8*Sin(k));
           glVertex3f(0.8*Cos(k),-1,0.8*Sin(k));
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslated(x,y-1.6,z);
        glScaled(scale,scale,scale);
        drawShoe(0,-2,0);
        ErrCheck("Spongebob-legs");
    glPopMatrix();
}


/*
*  Draw spongebob
*     with scale (scale)
*     at (x,y,z)
*     rotated th about the y axis
*/
void drawSpongebob(double scale, double x, double y, double z, double th){
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();
    glTranslated(x,y+1.1,z);
        glRotated(th,0,1,0);
        glScaled(scale,scale,scale);



        //  Enable textures
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
        glColor3f(1,1,1);
        glBindTexture(GL_TEXTURE_2D,spongebob_front);

        // front
        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glNormal3f(0,0,1);
        glTexCoord2f(0,0); glVertex3f(-1,-1.5,0.25);
        glTexCoord2f(0,1); glVertex3f(-1,1.5,0.25);
        glTexCoord2f(1,1); glVertex3f(1,1.5,0.25);
        glTexCoord2f(1,0); glVertex3f(1,-1.5,0.25);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
        glColor3f(1,1,1);
        glBindTexture(GL_TEXTURE_2D, spongebob_side);
        // right
        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glNormal3f(1,0,0);
        glTexCoord2f(0,0); glVertex3f(1,-1.5,0.25);
        glTexCoord2f(0,1); glVertex3f(1,1.5,0.25);
        glTexCoord2f(0.189,1); glVertex3f(1,1.5,-0.25);
        glTexCoord2f(0.189,0); glVertex3f(1,-1.5,-0.25);
        glEnd();

        // back
        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glNormal3f(0,0,-1);
        glTexCoord2f(0.189,0); glVertex3f(1,-1.5,-0.25);
        glTexCoord2f(0.189,1); glVertex3f(1,1.5,-0.25);
        glTexCoord2f(0.811,1); glVertex3f(-1,1.5,-0.25);
        glTexCoord2f(0.811,0); glVertex3f(-1,-1.5,-0.25);
        glEnd();

        // left
        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glNormal3f(-1,0,0);
        glTexCoord2f(0.811,0); glVertex3f(-1,-1.5,-0.25);
        glTexCoord2f(0.811,1); glVertex3f(-1,1.5,-0.25);
        glTexCoord2f(1,1); glVertex3f(-1,1.5,0.25);
        glTexCoord2f(1,0); glVertex3f(-1,-1.5,0.25);
        glEnd();

        // bottom
        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glNormal3f(0,-1,0);
        glTexCoord2f(0.189,0); glVertex3f(-1,-1.5,0.25);
        glTexCoord2f(0.189,0.189); glVertex3f(-1,-1.5,-0.25);
        glTexCoord2f(0.811,0.189); glVertex3f(1,-1.5,-0.25);
        glTexCoord2f(0.811,0); glVertex3f(1,-1.5,0.25);
        glEnd();

        //top
        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glNormal3f(0,1,0);
        glTexCoord2f(0.189,0.811); glVertex3f(-1,1.5,0.25);
        glTexCoord2f(0.189,1); glVertex3f(-1,1.5,-0.25);
        glTexCoord2f(0.811,1); glVertex3f(1,1.5,-0.25);
        glTexCoord2f(0.811,0.811); glVertex3f(1,1.5,0.25);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        //left leg
        draw_sb_legs(1/5.0, -0.5,-1.5,0);

        //right leg
        draw_sb_legs(1/5.0, 0.5,-1.5,0);

        // left arm
        draw_sb_arms(1/5.0, -1,0.5,0);

        //right arm
        draw_sb_arms(1/5.0, 1,0.5,0);

        ErrCheck("Spongebob");
    glPopMatrix();

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// spongebob's house section
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
*  Draw spongebob's roof leaves
*     with scale (scale)
*     at (x,y,z)
*     rotated th about the z axis, rotated ph about the x axis
*/
void drawRoofLeaves(double scale, double x, double y, double z, double th, double ph){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, leaves);
    glTranslated(x,y,z);
    glRotated(th, 0,0,1);
    glRotated(ph, 1,0,0);
    glScaled(scale,scale,scale);
    //  ends
//    glColor3f(1,1,1);
    glColor3f(93/255.0, 132/255.0, 55/255.0);
    glNormal3f(0,1,0);
    glBegin(GL_TRIANGLE_FAN);
    //       glTexCoord2f(0.5,0.5);
    glTexCoord2f(0.5,0.5); glVertex3f(0,4,0);
    for (int k=0;k<=360;k+=10)
    {
        glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
        glVertex3f(0.4*Cos(k),0,0.4*Sin(k));
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ErrCheck("draw roof leaves");
}


/*
*  Draw a door
*     with scale (scale)
*     and color (r,g,b)
*     at (x,y,z)
*     rotated th about the y axis
*/
void drawDoor(double scale, double r, double g, double b, double x, double y, double z, double th, int spongebob){
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,(spongebob)?spongebob_door:squidward_door);
        glTranslated(x,y+2,z);
        glRotated(th, 0,1,0);
        glScaled(scale,scale*0.8,scale);

        //  ends
        glColor3f(1,1,1);
        glNormal3f(0,0,1);
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5,0.664);
        glVertex3f(0,0,0.5);
        for (int k=0;k<=180;k+=10)
        {
            glTexCoord2f(0.5*Cos(k)+0.5,0.336*Sin(k)+0.664);
            glVertex3f(0.8*Cos(k),0.8*Sin(k),0.5);
        }
        glEnd();
        glDisable(GL_TEXTURE_2D);

        //edge
        glColor3f(r,g,b);
        glBegin(GL_QUAD_STRIP);
        for (int k=0;k<=180;k+=10)
        {
           glNormal3f(0.8*Cos(k),0.8*Sin(k),0);
            glVertex3f(0.8*Cos(k),0.8*Sin(k),0.5);
            glVertex3f(0.8*Cos(k),0.8*Sin(k),-0.5);
        }
        glEnd();

        glPushMatrix();
            glTranslated(0,-2,0);
        //    glRotated(th, 0,1,0);
        //    glScaled(scale,scale,scale);
            //  ends

        //    glColor3f(65/255.0,98/255.0,137/255.0);
        //    glNormal3f(0,0,1);

            // front
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,(spongebob)?spongebob_door:squidward_door);
            glBegin(GL_QUADS);
            glColor3f(1,1,1);
            glNormal3f(0,0,1);
            glTexCoord2f(0,0); glVertex3f(-0.8,0,0.5);
            glTexCoord2f(0,0.664); glVertex3f(-0.8,2,0.5);
            glTexCoord2f(1,0.664); glVertex3f(0.8,2,0.5);
            glTexCoord2f(1,0); glVertex3f(0.8,0,0.5);
            glEnd();
            glDisable(GL_TEXTURE_2D);

            // left
            glBegin(GL_QUADS);
            glColor3f(r,g,b);
            glNormal3f(-1,0,0);
            glVertex3f(-0.8,0,0.5);
            glVertex3f(-0.8,2,0.5);
            glVertex3f(-0.8,2,-0.5);
            glVertex3f(-0.8,0,-0.5);
            glEnd();

            // right
            glBegin(GL_QUADS);
            glColor3f(r,g,b);
            glNormal3f(1,0,0);
            glVertex3f(0.8,0,0.5);
            glVertex3f(0.8,2,0.5);
            glVertex3f(0.8,2,-0.5);
            glVertex3f(0.8,0,-0.5);
            glEnd();

            // bottom
            glBegin(GL_QUADS);
            glColor3f(r,g,b);
            glNormal3f(0,0,1);
            glVertex3f(-0.8,0,0.5);
            glVertex3f(-0.8,0,-0.5);
            glVertex3f(0.8,0,-0.5);
            glVertex3f(0.8,0,0.5);
            glEnd();

        glPopMatrix();
    glPopMatrix();


    ErrCheck("draw door");
}

/*
*  Draw a windows
*     with scale (scale)
*     at (x,y,z)
*     rotated th about the y axis
*/
void drawWindow(double scale, double x, double y, double z, double th, int surprise){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

    glTranslated(x,y,z);
    glRotated(th, 0,1,0);
    glScaled(scale,scale,scale);

    //  ends
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, (surprise)?surprise_window:window);
    glNormal3f(0,0,1);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0,0,0.5);
    for (int k=0;k<=360;k+=10)
    {
        glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
        glVertex3f(0.8*Cos(k),0.8*Sin(k),0.5);
    }
   glEnd();
    glDisable(GL_TEXTURE_2D);

    //edge
    glColor3f(112/255.0,136/255.0,208/255.0);
    glBegin(GL_QUAD_STRIP);
    for (int k=0;k<=360;k+=10)
    {
       glNormal3f(0.8*Cos(k),0.8*Sin(k),0);
        glVertex3f(0.8*Cos(k),0.8*Sin(k),0.5);
        glVertex3f(0.8*Cos(k),0.8*Sin(k),-1);
    }
    glEnd();
    glPopMatrix();
}


/*
*  Draw spongebob's
*     with scale (scale)
*     at (x,y,z)
*     rotated th about the y axis
*/
void drawSpongebobHouse(double scale, double x, double y, double z, double th){
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(th,0,1,0);
    glScaled(scale*1.2,scale*1.45,scale*1.2);



    //  Enable textures
    glEnable(GL_TEXTURE_2D);
//    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,spongebob_house);

        int p, t;
        glPushMatrix();
        //  Offset, scale and rotate
        glTranslated(0,3*(7.7/9.0),0);
        glRotated(-90, 1,0,0);
        glScaled(3,3,4);

//        glColor3f(201/255.0, 104/255.0, 45/255.0);
        glColor3f(1,1,1);
        //  Bands of latitude
        for (p=-40;p<90;p+=2.5*inc)
        {
           glBegin(GL_QUAD_STRIP);
            for (t=0;t<=360;t+=2*inc)
           {
               Vertex(t,p+2.5*inc);
               Vertex(t,p);
           }
           glEnd();
        }
        //  Undo transofrmations
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        glPushMatrix();
        // back
        glNormal3f(0,-1,0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0,0,0);
        for (int k=0;k<=360;k+=10)
        {
            glVertex3f(2.45*Cos(k),0,2.45*Sin(k));
        }
        glEnd();

        drawWindow(0.9, 1.6,2.23,2, 37, 0);
        drawWindow(0.9, -1.6,4,2, -37, 0);

        drawDoor(1, 103/255.0,133/255.0,216/255.0, 0,-0.4,2.5, 0, 1);

        for (int k = 0; k<=360; k+=inc){
            drawRoofLeaves(1.2, 0,5,0, 40*(Sin(k)), 40*(Cos(k)));
            if (k%20 == 0){
                drawRoofLeaves(1.2, 0,4.9,0, 25*(Sin(k)), 25*(Cos(k)));
            }
            if (k % 30 == 0){
                drawRoofLeaves(1.2, 0,4.8,0, 10*(Sin(k)), 10*(Cos(k)));
            }
        }

        glPopMatrix();

    glPopMatrix();


    ErrCheck("Spongebob's House");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// generate squidward house section
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void squidwardHouseBody(double scale, double x,double y,double z, double th){
    glEnable(GL_TEXTURE_2D);
   glPushMatrix();
       glTranslated(x,y,z);
       glRotated(th, 0,1,0);
       glScaled(scale,scale,scale);
    glBindTexture(GL_TEXTURE_2D,sand);
       //  ends
       glColor3f(65/255.0,98/255.0,137/255.0);
      glNormal3f(0,0,1);
      glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5,0.5);
    glVertex3f(0,3.6,0);
      for (int k=0;k<=360;k+=10)
      {
             glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
            glVertex3f(0.75*Cos(k),3.6,0.75*Sin(k));
      }
      glEnd();

       //edge
       glBegin(GL_QUAD_STRIP);
       for (int k=0;k<=360;k+=10)
       {
           glNormal3f((1-0.8)/2*Cos(k),0,(1-0.8)/2*Sin(k));
           glTexCoord2f(0,0.0005*k); glVertex3f(0.75*Cos(k),3.6,0.75*Sin(k));
           glTexCoord2f(5,0.0005*k); glVertex3f(1*Cos(k),0,1*Sin(k));
       }
       glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
  }


static void Ear(double scale, double x,double y,double z, double th)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(th, 0,1,0);
    glScaled(scale,scale,scale);

    //  Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,sand);

    //front
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0,1); glVertex3f(-0.65,-3,0.5);
    glTexCoord2f(1,1); glVertex3f(-0.65,3,0.5);
    glTexCoord2f(1,0); glVertex3f(0.65,3,0.5);
    glTexCoord2f(0,0); glVertex3f(0.65,-3,0.5);
    glEnd();

    //top
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0,0); glVertex3f(-0.65,3,0.5);
    glTexCoord2f(1,0); glVertex3f(0.65,3,0.5);
    glTexCoord2f(1,1); glVertex3f(0.65,3,-1);
    glTexCoord2f(0,1); glVertex3f(-0.65,3,-1);
    glEnd();

    //bottom
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0,0); glVertex3f(-0.65,-3,-1);
    glTexCoord2f(1,0); glVertex3f(0.65,-3,-1);
    glTexCoord2f(1,1); glVertex3f(0.65,-3,0.5);
    glTexCoord2f(0,1); glVertex3f(-0.65,-3,0.5);
    glEnd();

    //left
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.65,-3,-1);
    glTexCoord2f(1,0); glVertex3f(-0.65,-3,0.5);
    glTexCoord2f(1,1); glVertex3f(-0.65,3,0.5);
    glTexCoord2f(0,1); glVertex3f(-0.65,3,-1);
    glEnd();

    //right
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0); glVertex3f(0.65,-3,0.5);
    glTexCoord2f(1,0); glVertex3f(0.65,-3,-1);
    glTexCoord2f(1,1); glVertex3f(0.65,3,-1);
    glTexCoord2f(0,1); glVertex3f(0.65,3,0.5);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

static void Unibrow(double scale, double x,double y,double z, double th)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(th, 0,1,0);
    glScaled(scale,scale,scale);

    //  Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,sand);

    //front
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0,1); glVertex3f(-3.5,-0.5,0.5);
    glTexCoord2f(1,1); glVertex3f(-3.5,0.5,0.5);
    glTexCoord2f(1,0); glVertex3f(3.5,0.5,0.5);
    glTexCoord2f(0,0); glVertex3f(3.5,-0.5,0.5);
    glEnd();

    //top
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0,0); glVertex3f(-3.5,0.5,0.5);
    glTexCoord2f(1,0); glVertex3f(3.5,0.5,0.5);
    glTexCoord2f(1,1); glVertex3f(3.5,0.5,-3.4);
    glTexCoord2f(0,1); glVertex3f(-3.5,0.5,-3.4);
    glEnd();

    //bottom
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0,0); glVertex3f(-3.5,-0.5,-3.4);
    glTexCoord2f(1,0); glVertex3f(3.5,-0.5,-3.4);
    glTexCoord2f(1,1); glVertex3f(3.5,-0.5,0.5);
    glTexCoord2f(0,1); glVertex3f(-3.5,-0.5,0.5);
    glEnd();

    //left
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0,0); glVertex3f(-3.5,-0.5,-3.4);
    glTexCoord2f(1,0); glVertex3f(-3.5,-0.5,0.5);
    glTexCoord2f(1,1); glVertex3f(-3.5,0.5,0.5);
    glTexCoord2f(0,1); glVertex3f(-3.5,0.5,-3.4);
    glEnd();

    //right
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0); glVertex3f(3.5,-0.5,0.5);
    glTexCoord2f(1,0); glVertex3f(3.5,-0.5,-3.4);
    glTexCoord2f(1,1); glVertex3f(3.5,0.5,-3.4);
    glTexCoord2f(0,1); glVertex3f(3.5,0.5,0.5);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

static void nose(double scale, double x,double y,double z, double th)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(th, 1,0,0);
    glScaled(scale,scale+scale*1,scale);

    //  Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,sand);


    // front
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0,1); glVertex3f(-0.15,-0.15,0.15);
    glTexCoord2f(1,1); glVertex3f(-0.05,0.15,0.15);
    glTexCoord2f(1,0); glVertex3f(0.05,0.15,0.15);
    glTexCoord2f(0,0); glVertex3f(0.15,-0.15,0.15);
    glEnd();

    // left
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1); //not right
    glTexCoord2f(0,1); glVertex3f(-0.15,-0.15,0);
    glTexCoord2f(1,1); glVertex3f(-0.15,-0.15,0.15);
    glTexCoord2f(1,0); glVertex3f(-0.05,0.15,0.15);
    glTexCoord2f(0,0); glVertex3f(-0.05,0.15,0);
    glEnd();

    // right
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1); //not right
    glTexCoord2f(0,1); glVertex3f(0.15,-0.15,0.15);
    glTexCoord2f(1,1); glVertex3f(0.15,-0.15,0);
    glTexCoord2f(1,0); glVertex3f(0.05,0.15,0);
    glTexCoord2f(0,0); glVertex3f(0.05,0.15,0.15);
    glEnd();

    // top
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0,1); glVertex3f(-0.05,0.15,0.15);
    glTexCoord2f(1,1); glVertex3f(0.05,0.15,0.15);
    glTexCoord2f(1,0); glVertex3f(0.05,0.15,0);
    glTexCoord2f(0,0); glVertex3f(-0.05,0.15,0);
    glEnd();

    // bottom
    glColor3f(65/255.0,98/255.0,137/255.0);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0,1); glVertex3f(-0.15,-0.15,0.15);
    glTexCoord2f(1,1); glVertex3f(0.15,-0.15,0.15);
    glTexCoord2f(1,0); glVertex3f(0.15,-0.15,0);
    glTexCoord2f(0,0); glVertex3f(-0.15,-0.15,0);
    glEnd();


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
  }

/*
*  Draw squidward's house
*     with scale (scale)
*     at (x,y,z)
*     rotated th about the y axis
*/
void generateSquidwardHouse(double scale, double x, double y, double z, double th){
    glPushMatrix();

    glTranslated(x,y,z);
    glRotated(th, 0,1,0);
    glScaled(scale,scale,scale);

    //  Draw house
    squidwardHouseBody(1, 0,0,0, 0);

    Ear(0.22, 1.05,1.7,0, 90);
    Ear(0.22, -1.05,1.7,0, -90);

    Unibrow(0.22, 0,2.45,1, 0);
    nose(2.25, 0,1.7,0.72, 0);

    drawWindow(0.33, -0.45,2.07,0.7, 0, 1);
    drawWindow(0.33, 0.45,2.07,0.7, 0, 0);

    drawDoor(0.4, 133/255.0,94/255.0,55/255.0, 0,-1.38,0.8, 0, 0);

    glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// generate patrick's house
/// Sourced from https://community.khronos.org/t/half-sphere/49408/2
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void house_dome() {

    glPushMatrix();
    glRotated(-90,1,0,0);
    glScaled(2,2,2);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,patrick_house);

    for (double p=0;p<90;p+=inc)
            {
               glBegin(GL_QUAD_STRIP);
                for (double t=0;t<=360;t+=2*inc)
               {
                   Vertex(t,p+1*inc);
                   Vertex(t,p);
               }

               glEnd();
            }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
static void Stick(double x,double y,double z,double r,double d, double a, double b, double c, double e)
{
   double k;
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
    glRotatef(a,b,c,e);
   glScaled(r,r,d);
     //  Edge
    glColor3f(0.752,0.752,0.329);
     glBegin(GL_QUAD_STRIP);
     for (k=0;k<=365;k+=10)
     {
        glNormal3f(Cos(k),Sin(k),10);
         glTexCoord2f(1,(0.5*k)); glVertex3f(Cos(k),Sin(k),+15); //increse length of  main cylinder
         glTexCoord2f(1,(0.5*k)); glVertex3f(Cos(k),Sin(k),-10);
     }
     glEnd();
     //  Undo transformations
     glPopMatrix();
  }
static void StickCovering1(double x,double y,double z,double r,double d,double a, double b, double c, double e)
{
   int i,k;
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,d);
    glRotatef(a,b,c,e);
   //  Head & Tail
     glColor3f(0.752,0.752,0.329);
   for (i=1;i>=-1;i-=2)
   {
      glNormal3f(0,0,i);
      glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5);
      glVertex3f(0,0,i);
      for (k=0;k<=360;k+=10)
      {
         glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
         glVertex3f(i*Cos(k),Sin(k),i);
      }
      glEnd();
   }
     glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

/*
*  Draw patrick's house
*     with scale (scale)
*     at (x,y,z)
*     rotated th about the y axis
*/
void generatePatrickHouse(double scale, double x, double y, double z, double th){
    glPushMatrix();

    glTranslated(x,y,z);
    glRotated(th, 0,1,0);
    glScaled(scale,scale,scale);

    house_dome();
    Stick(0,2,0,0.1,0.05,90,0,0,0);
    StickCovering1(0,2.2,0,0.1,0.1,90,0,0,0);
    Stick(0.1,2.4,0,0.05,0.05,90,0,10,0);

    glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// generate patrick
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void leg(double x,double y,double z,double r,double d, double a, double b, double c, double e)
{
   double k;
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
    glRotatef(a,b,c,e);
   glScaled(r,r,d);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,patrick_back);

     //  Edge
    glColor3f(0.73,0.56,0.56);
     glBegin(GL_QUAD_STRIP);
     for (k=0;k<=365;k+=10)
     {
        glNormal3f(Cos(k),Sin(k),10);
         glTexCoord2f(1,(0.5*k)); glVertex3f(Cos(k),Sin(k),+10); //increse length of  main cylinder
         glTexCoord2f(1,(0.5*k)); glVertex3f(Cos(k)*0.6,Sin(k)*0.6,-5);
     }
     glEnd();
     //  Undo transformations
     glPopMatrix();
     glDisable(GL_TEXTURE_2D);
  }

void dome(double x,double y,double z,int scale_y, int scale_x, GLfloat r, double a,double b, double c, double e) {
    int i, j;
    glTranslated(x,y,z);
    glRotatef(a,b,c,e);
    GLfloat v[scale_x*scale_y][3];

    glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
      glColor3f(1,1,1);
      glBindTexture(GL_TEXTURE_2D,patrick_back);

    for (i=0; i<scale_x; ++i) {
      for (j=0; j<scale_y; ++j) {
        v[i*scale_y+j][0]=r*cos(j*2*M_PI/scale_y)*cos(i*M_PI/(2*scale_x));
        v[i*scale_y+j][1]=r*sin(i*M_PI/(2*scale_x));
        v[i*scale_y+j][2]=r*sin(j*2*M_PI/scale_y)*cos(i*M_PI/(2*scale_x));
      }
    }

    glBegin(GL_QUADS);
    glColor3f(0.73,0.56,0.56);
      for (i=0; i<scale_x-1; ++i) {
        for (j=0; j<scale_y; ++j) {
          glVertex3fv(v[i*scale_y+j]);
          glVertex3fv(v[i*scale_y+(j+1)%scale_y]);
          glVertex3fv(v[(i+1)*scale_y+(j+1)%scale_y]);
          glVertex3fv(v[(i+1)*scale_y+j]);
        }
      }
    glEnd();
     glDisable(GL_TEXTURE_2D);
  }
static void tid(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
    glScaled(1.25,1.25,1.25);

    glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
      glColor3f(1,1,1);
      glBindTexture(GL_TEXTURE_2D,patrick_back);

   //  White ball
    glColor3f(0.73,0.56,0.56);
   glutSolidSphere(1.0,16,16);
   //  Undo transofrmations
   glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

static void arm(double x,double y,double z,double r,double d, double a, double b, double c, double e)
{
   double k;
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
    glRotatef(a,b,c,e);
   glScaled(r,r,d);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,patrick_back);



     //  Edge
    glColor3f(0.73,0.56,0.56);
    glNormal3f(0,0,1);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0,0,-5);
    for (int k=0;k<=360;k+=10)
    {
         glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
        glVertex3f(0.6*Cos(k),0.6*Sin(k), -5);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0,0,10);
    for (int k=0;k<=360;k+=10)
    {
         glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
         glVertex3f(Cos(k),Sin(k), 10);
    }
    glEnd();



     glBegin(GL_QUAD_STRIP);
     for (k=0;k<=365;k+=10)
     {
        glNormal3f((1-0.6)/2*Cos(k),(1-0.6)/2*Sin(k),0);
         glTexCoord2f(1,(0.5*k)); glVertex3f(Cos(k),Sin(k),+10);
         glTexCoord2f(1,(0.5*k)); glVertex3f(Cos(k)*0.6,Sin(k)*0.6,-5);
     }

     glEnd();
     //  Undo transformations
     glPopMatrix();
    glDisable(GL_TEXTURE_2D);
  }

static void Head(double x,double y,double z,double r,double d, double a, double b, double c, double e, int front)
{
   double k;
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
    glRotatef(a,b,c,e);
    glScaled(r,(front)?0.6:r,(front)?0.2:d);


    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,(front)?patrick_face:patrick_back);
     //  Edge
    glColor3f(0.73,0.56,0.56);
     glBegin(GL_QUAD_STRIP);
     for (k=0;k<=360;k+=10)
     {
        glNormal3f(Cos(k),Sin(k),0);
         double temp = 0.005*(k-(-10));
         if(temp <= 1 && temp >=0){
             glTexCoord2f((temp), 0);
         }
         glVertex3f(Cos(k),Sin(k),+10); //increse length of  main cylinder
         if(temp <= 1 && temp >=0){
                 glTexCoord2f((temp), 1);
         }
         glVertex3f(Cos(k)*0.4,Sin(k)*0.4,-5);
     }
     glEnd();
     //  Undo transformations
     glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void pants(double x,double y,double z, double a,double b, double c, double e) {

        glPushMatrix();
    glTranslated(0,-3.5,0);
        glRotated(90,1,0,0);
    glScaled(1.29,1.29,1.29);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,patrick_pants);

        for (double p=0;p<90;p+=inc)
                {
                   glBegin(GL_QUAD_STRIP);
                    for (double t=0;t<=360;t+=2*inc)
                   {
                       Vertex(t,p+1.5*inc);
                       Vertex(t,p);
                   }

                   glEnd();
                }
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }

static void pantleg(double x,double y,double z,double r,double d, double a, double b, double c, double e)
{
   double k;
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
    glRotatef(a,b,c,e);
   glScaled(r,r,d);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,patrick_pants);

   //  Head & Tail
   glColor3f(1,1,1);
     //  Edge
    glColor3f(1,1,1);
     glBegin(GL_QUAD_STRIP);
     for (k=0;k<=365;k+=10)
     {
        glNormal3f(Cos(k),Sin(k),10);
         glTexCoord2f(1,(0.5*k)); glVertex3f(Cos(k),Sin(k),+2); //increse length of  main cylinder
         glTexCoord2f(1,(0.5*k)); glVertex3f(Cos(k),Sin(k),-10);
     }
     glEnd();
     //  Undo transformations
     glPopMatrix();
    glDisable(GL_TEXTURE_2D);
  }

/*
*  Draw patrick
*     with scale (scale)
*     at (x,y,z)
*     rotated th about the y axis
*/
void drawPatrick(double scale, double x, double y, double z, double th){
    glPushMatrix();

    glTranslated(x,y,z);
    glRotated(th, 0,1,0);
    glScaled(scale,scale,scale);

    leg(0,1,2,0.4,0.1,90,-30,0,0);
    dome(0,0.5,2,14,30,0.23,180,0,0,0);
    tid(0.75,-2,0,0.4);
    leg(1.5,-0.5,0,0.4,0.1,-90,-30,0,0);
    dome(1.5,-0,0,4,180,0.23,0,0,0,0);
    arm(-1.75,-1.5,-0.5,0.4,0.1,-65,-80,0,0);
    arm(0.25,-1.5,-0.5,0.4,0.1,-65,-80,0,0);
    Head(-0.7,-3.8,0, 0.8,0.1,-90,30,0,0, 1); //face
    Head(-0.7,-4.4,0.1, 0.6,0.2,-85,0,0,0, 0);
    dome(-0.7,-5.3,0,20,30,0.23,180,0,0,0);
    pants(0,-4,0,15,30,1.25,180);
    pantleg(0.73,-4,-0.05,0.5,0.1,-90,0,0,0);
    pantleg(-0.77,-4,-0.05,0.5,0.1,-90,0,0,0);

    glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// generate ground section
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//this method will generate the ground on which our objects will stand on.... additonally, we'll be walking on this ground
void generateGround(double l, double w, double r, double g, double b, double x, double y, double z){
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();
    glTranslated(x,y,z);

    double temp_l = (l/2);
    double temp_w = (w/2);

    //  Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,sand);

    //top
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0,0); glVertex3f(-temp_w,0,temp_l);
    glTexCoord2f(1,0); glVertex3f(-temp_w,0,-temp_l);
    glTexCoord2f(1,1); glVertex3f(temp_w,0,-temp_l);
    glTexCoord2f(0,1); glVertex3f(temp_w,0,temp_l);
    glEnd();

    //bottom
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0,0); glVertex3f(-temp_w,-0.1,temp_l);
    glTexCoord2f(1,0); glVertex3f(-temp_w,-0.1,-temp_l);
    glTexCoord2f(1,1); glVertex3f(temp_w,-0.1,-temp_l);
    glTexCoord2f(0,1); glVertex3f(temp_w,-0.1,temp_l);
    glEnd();

    //left
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1); glVertex3f(-temp_w,0,temp_l);
    glTexCoord2f(0,1); glVertex3f(-temp_w,0,-temp_l);
    glTexCoord2f(0,0); glVertex3f(-temp_w,-0.1,-temp_l);
    glTexCoord2f(1,0); glVertex3f(-temp_w,-0.1,temp_l);
    glEnd();

    //right
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0,1); glVertex3f(temp_w,0,temp_l);
    glTexCoord2f(1,1); glVertex3f(temp_w,0,-temp_l);
    glTexCoord2f(1,0); glVertex3f(temp_w,-0.1,-temp_l);
    glTexCoord2f(0,0); glVertex3f(temp_w,-0.1,temp_l);
    glEnd();

    //front
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0,1); glVertex3f(-temp_w,0,temp_l);
    glTexCoord2f(1,1); glVertex3f(temp_w,0,temp_l);
    glTexCoord2f(1,0); glVertex3f(temp_w,-0.1,temp_l);
    glTexCoord2f(0,0); glVertex3f(-temp_w,-0.1,temp_l);
    glEnd();

    //back
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(1,0); glVertex3f(temp_w,0,-temp_l);
    glTexCoord2f(1,1); glVertex3f(-temp_w,0,-temp_l);
    glTexCoord2f(0,0); glVertex3f(temp_w,-0.1,-temp_l);
    glTexCoord2f(0,1); glVertex3f(-temp_w,-0.1,-temp_l);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

/*
 *  Draw sky box
 */
static void Sky(double D)
{
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);

   //  Sides
   glBindTexture(GL_TEXTURE_2D,sky[0]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.00,0); glVertex3f(-D,-D,-D);
   glTexCoord2f(0.25,0); glVertex3f(+D,-D,-D);
   glTexCoord2f(0.25,1); glVertex3f(+D,+D,-D);
   glTexCoord2f(0.00,1); glVertex3f(-D,+D,-D);

   glTexCoord2f(0.25,0); glVertex3f(+D,-D,-D);
   glTexCoord2f(0.50,0); glVertex3f(+D,-D,+D);
   glTexCoord2f(0.50,1); glVertex3f(+D,+D,+D);
   glTexCoord2f(0.25,1); glVertex3f(+D,+D,-D);

   glTexCoord2f(0.50,0); glVertex3f(+D,-D,+D);
   glTexCoord2f(0.75,0); glVertex3f(-D,-D,+D);
   glTexCoord2f(0.75,1); glVertex3f(-D,+D,+D);
   glTexCoord2f(0.50,1); glVertex3f(+D,+D,+D);

   glTexCoord2f(0.75,0); glVertex3f(-D,-D,+D);
   glTexCoord2f(1.00,0); glVertex3f(-D,-D,-D);
   glTexCoord2f(1.00,1); glVertex3f(-D,+D,-D);
   glTexCoord2f(0.75,1); glVertex3f(-D,+D,+D);
   glEnd();

   //  Top and bottom
   glBindTexture(GL_TEXTURE_2D,sky[1]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0,0); glVertex3f(+D,+D,-D);
   glTexCoord2f(0.5,0); glVertex3f(+D,+D,+D);
   glTexCoord2f(0.5,1); glVertex3f(-D,+D,+D);
   glTexCoord2f(0.0,1); glVertex3f(-D,+D,-D);

   glTexCoord2f(1.0,1); glVertex3f(-D,-D,+D);
   glTexCoord2f(0.5,1); glVertex3f(+D,-D,+D);
   glTexCoord2f(0.5,0); glVertex3f(+D,-D,-D);
   glTexCoord2f(1.0,0); glVertex3f(-D,-D,-D);
   glEnd();

   glDisable(GL_TEXTURE_2D);
}

/*
*  OpenGL (GLUT) calls this routine to display the scene
*/
void display()
{
    const double len=1.5;  //  Length of axes
    //  Erase the window and the depth buffer
    glClearColor(0,0.3,0.7,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //  Enable Z-buffering in OpenGL
    glEnable(GL_DEPTH_TEST);
    //  Undo previous transformations
    glLoadIdentity();

    if (mode) //  Perspective - set eye position
    {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
    }
    else //  Orthogonal - set world orientation
    {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
    }


      //Flat or smooth shading
    glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

    Sky(2*dim);
    ErrCheck("Sky");
    //  Light switch
    if (light)
    {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light position
        float Position[]  = {5*Cos((modify)?idle:xPos),ylight,5*Sin((modify)?idle:yPos),1.0};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  Location of viewer for specular calculations
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
    }

    double r,g,b;
    r = 85/255.0;
    g = 153/255.0;
    b = 0/255.0;

    glPushMatrix();
    glTranslated(0,-4,0);

        // generate ground
//        generateGround(20,30, 233/255.0,243/255.0,214/255.0, 0,0,-3);
        generateGround(20,30, 1,1,1, 0,0,-3);

        // generate spongebob
        drawSpongebob(0.3, 6.667,0,1, 0);
        drawSpongebobHouse(0.55, 6.667,-0.05,-3, 0);

        // generate squidward
        generateSquidwardHouse(2, 0,0,-3, 0);

        // geenerate patrick
        drawPatrick(0.5, -6.667,-0.2,1, 0);
        generatePatrickHouse(1, -6.667,0,-3, 0);


    glPopMatrix();

    if(light){
        //  disbale lighting from here on
        glDisable(GL_LIGHTING);
    }

    //  Draw axes
    glColor3f(1,1,1);
    if (axes)
    {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
    }
    //  Display parameters
    glWindowPos2i(5,5);
    Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=",th,ph,dim,fov);
    (mode)?Print("Perpective"):Print("Orthogonal");
    //  Render the scene and make it visible
    ErrCheck("display");
    glFlush();
    glutSwapBuffers();
}

/*
*  GLUT calls this routine when an arrow key is pressed
*/
void special(int key,int x,int y)
{
    //  Right arrow key - increase angle by 5 degrees
    if (key == GLUT_KEY_RIGHT)
        th += 5;
    //  Left arrow key - decrease angle by 5 degrees
    else if (key == GLUT_KEY_LEFT)
        th -= 5;
    //  Up arrow key - increase elevation by 5 degrees
    else if (key == GLUT_KEY_UP)
        ph += 5;
    //  Down arrow key - decrease elevation by 5 degrees
    else if (key == GLUT_KEY_DOWN)
        ph -= 5;
    //  PageUp key - increase dim
    else if (key == GLUT_KEY_PAGE_UP)
       dim += 0.1;
    //  PageDown key - decrease dim
    else if (key == GLUT_KEY_PAGE_DOWN)
       dim -= 0.1;

    //  Keep angles to +/-360 degrees
    th %= 360;
    ph %= 360;
    //  Update projection
    Project(mode,fov,asp,dim);
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

/*
*  GLUT calls this routine when a key is pressed
*/
void key(unsigned char ch,int x,int y)
{
    //  Exit on ESC
    if (ch == 27)
        exit(0);
    //  Toggle axes
    else if (ch == 'x' || ch == 'X')
        axes = 1-axes;
    //  Toggle lighting
    else if (ch == 'l' || ch == 'L')
        light = 1-light;
    //  Switch projection mode
    else if (ch == 'm' || ch == 'M')
        mode = (mode+1)%2;
    //  Change field of view angle
    else if (ch == '-' && ch>1)
        fov--;
    else if (ch == '+' && ch<179)
        fov++;
    //  Light elevation
    else if (ch=='[')
        ylight -= 0.1;
    else if (ch==']')
        ylight += 0.1;
    //  Ambient level
    else if (ch=='a' && ambient>0)
        ambient -= 5;
    else if (ch=='A' && ambient<100)
        ambient += 5;
    //  Diffuse level
    else if (ch=='d' && diffuse>0)
        diffuse -= 5;
    else if (ch=='D' && diffuse<100)
        diffuse += 5;
    //  Specular level
    else if (ch=='s' && specular>0)
        specular -= 5;
    else if (ch=='S' && specular<100)
        specular += 5;
    //  Emission level
    else if (ch=='e' && emission>0)
        emission -= 5;
    else if (ch=='E' && emission<100)
        emission += 5;
    //  Shininess level
    else if (ch=='n' && shininess>-1)
        shininess -= 1;
    else if (ch=='N' && shininess<7)
        shininess += 1;

    //change the direction of the light
    else if (ch == 'p' || ch == 'P')
        modify = (modify+1)%2;
    //change direction of the light source
    else if (ch == 'o'){
        xPos -= 5;
    }
    else if (ch == 'O'){
        xPos += 5;
    }
    else if (ch == 'i'){
        yPos -= 5;
    }
    else if (ch == 'I'){
        yPos += 5;
    }

    //  Translate shininess power to value (-1 => 0)
    shiny = shininess<0 ? 0 : pow(2.0,shininess);
    //  Reproject
    Project(mode,fov,asp,dim);
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(mode,fov,asp,dim);
}


/*
*  GLUT calls this routine when the window is resized
*/
void idle_function()
{
    //  Elapsed time in seconds
    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    idle = fmod(90*t,360.0);
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}


/*
*  Start up GLUT and tell it what to do
*/
int main(int argc,char* argv[])
{
    //  Initialize GLUT
    glutInit(&argc,argv);
    //  Request double buffered, true color window with Z buffering at 600x600
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(600,600);
    glutCreateWindow("Spongebob 3D Project");

    glutIdleFunc(idle_function);
    //  Set callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(key);

    //load textures
    spongebob_front = LoadTexBMP("images/spongebob-front.bmp");
    spongebob_side = LoadTexBMP("images/spongebob-side.bmp");
    spongebob_house = LoadTexBMP("images/spongebob-house.bmp");
    sand = LoadTexBMP("images/sand.bmp");
    window = LoadTexBMP("images/window.bmp");
    squidward_door = LoadTexBMP("images/sw-door.bmp");
    spongebob_door = LoadTexBMP("images/sb-door.bmp");
    leaves = LoadTexBMP("images/leaf.bmp");
    surprise_window = LoadTexBMP("images/window-squidward.bmp");
    patrick_pants = LoadTexBMP("images/patrick-pants.bmp");
    patrick_back = LoadTexBMP("images/patrick_back.bmp");
    patrick_face = LoadTexBMP("images/patrick_face.bmp");
    patrick_house = LoadTexBMP("images/patrick-house.bmp");
    //  Load skybox texture
    sky[0] = LoadTexBMP("images/background.bmp");
    sky[1] = LoadTexBMP("images/sky1.bmp");
    ErrCheck("init");
    //  Pass control to GLUT so it can interact with the user
    glutMainLoop();
    return 0;
}
