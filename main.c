//
//  main.c
//  ray tracer
//
//  Created by Joseph Spinosa on 4/11/17.
//  Copyright © 2017 Joseph Spinosa. All rights reserved.
//  last save:  2:13 pm 5/05/17
// Dave Vanora helped me get the shadow

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <stdio.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <OpenGL/glext.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TRI_STORAGE 20  // for future triangles

struct point{
    float x, y, z;
    };
typedef struct point point;


typedef struct light{
    point l1;
    float radius;
}light;

struct triangle{
    point t1;
    point t2;
    point t3;
    };
typedef struct triangle TRIANGLE;


TRIANGLE TRIANGLES [MAX_TRI_STORAGE];   // holds pointers to triangles
int tri_index = 0;
int *tri_index_point = &tri_index;
light goofy;


point makePoint(float x, float y, float z){
    point result;
    result.x = x;
    result.y = y;
    result.z = z;
    
    return result;
}

TRIANGLE makeTriangle(point t1, point t2, point t3){  // use calls to make point as actual arguements
    TRIANGLE T;
    T.t1 = t1;
    T.t2 = t2;
    T.t3 = t3;
    
    return T;  // this should be stored in the array of triangle pointers
    
}

void scene(float x, float y, float z, float len){   // PASS .2,.15,.6,.1
    
goofy.l1 = makePoint(.5, .5, 1.5);
goofy.radius = .1;
    

    
TRIANGLES[0] = makeTriangle(makePoint(x-len, y+len, z+len), makePoint(x-len, y-len, z+len), makePoint(x-len, y-len, z-len)); // LS1
TRIANGLES[1] = makeTriangle(makePoint(x-len, y+len, z+len), makePoint(x-len, y+len, z-len), makePoint(x-len, y-len, z-len)); // LS2
    
    
TRIANGLES[2] = makeTriangle(makePoint(x+len, y+len, z+len), makePoint(x+len, y+len, z-len), makePoint(x+len, y-len, z-len)); // RS1
TRIANGLES[3] = makeTriangle(makePoint(x+len, y+len, z+len), makePoint(x+len, y-len, z+len), makePoint(x+len, y-len, z-len)); // RS2
    
    
TRIANGLES[4] = makeTriangle(makePoint(x-len, y+len, z-len), makePoint(x-len, y+len, z+len), makePoint(x+len, y+len, z+len)); // TS1
TRIANGLES[5] = makeTriangle(makePoint(x-len, y+len, z-len), makePoint(x+len, y+len, z-len), makePoint(x+len, y+len, z+len)); // TS2
    
TRIANGLES[6] = makeTriangle(makePoint(x-len, y-len, z-len), makePoint(x-len, y-len, z+len), makePoint(x+len, y-len, z+len)); // BS1
TRIANGLES[7] = makeTriangle(makePoint(x-len, y+len, z-len), makePoint(x+len, y-len, z-len), makePoint(x+len, y+len, z+len)); // BS2
    
    
TRIANGLES[8] = makeTriangle(makePoint(x-len, y+len, z+len), makePoint(x-len, y-len, z+len), makePoint(x+len, y-len, z+len)); // FS1
TRIANGLES[9] = makeTriangle(makePoint(x-len, y+len, z+len), makePoint(x+len, y+len, z+len), makePoint(x+len, y-len, z+len)); // FS2

TRIANGLES[10] = makeTriangle(makePoint(x-len, y+len, z-len), makePoint(x+len, y+len, z-len), makePoint(x+len, y-len, z-len)); // BS1
TRIANGLES[11] = makeTriangle(makePoint(x-len, y+len, z-len), makePoint(x-len, y-len, z-len), makePoint(x+len, y-len, z-len)); // BS2

    
TRIANGLES[12] = makeTriangle(makePoint(0, 0, 0), makePoint(0, 0, 1), makePoint(1, 0, 0)); // FLOOR 1
TRIANGLES[13] = makeTriangle(makePoint(0, 0, 1), makePoint(1, 0, 1), makePoint(1, 0, 0)); // FLOOR 2
    
}

point point_subtract( point point1,  point point2){  // this will return the result of sub
    point result; // new point
    result.x = point1.x - point2.x;
    result.y = point1.y - point2.y;
    result.z = point1.z - point2.z;
    
    return result;  // result is a point
}

point point_add( point point1,  point point2){  // this will return the result of add
    point result; // new point
    result.x = point1.x + point2.x;
    result.y = point1.y + point2.y;
    result.z = point1.z + point2.z;
    
    return result;  // result is a point
}

point cross_product( point sub1, point sub2){ // assumes you've fed it p3-p1 and p2-p1
    point cross;
    cross.x = (sub1.y * sub2.z) - (sub1.z * sub2.y);
    cross.y = (sub1.z * sub2.x) - (sub1.x * sub2.z);
    cross.z = (sub1.x * sub2.y) - (sub1.y * sub2.x);
    
    return cross;  // cross is a point
}

float dot_product(point p1, point p2){
    
    return ((p1.x * p2.x) + (p1.y * p2.y) + (p1.z * p2.z));
    
}

point pointscaler_mult(float scaler, point point){
    struct point result;
    result.x = scaler * point.x;
    result.y = scaler * point.y;
    result.z = scaler * point.z;
    
    return result;
}


void drawpixel(float x,float y,float r,float g,float b) // assume x,y 0-100
{
#define SZ  .004    // used to be .02  OR .04
    glBegin(GL_TRIANGLES);
    glColor3f(r,g,b);
    glVertex2f(-1.0+.02*(float)x,     -1.0+.02*(float)y);   // USED TO BE .02'S
    glVertex2f(-1.0+.02*(float)x,     -1.0+.02*(float)y+ SZ);
    glVertex2f(-1.0+.02*(float)x+ SZ, -1.0+.02*(float)y);
    
    glVertex2f(-1.0+.02*(float)x+ SZ, -1.0+.02*(float)y);
    glVertex2f(-1.0+.02*(float)x+ SZ, -1.0+.02*(float)y+ SZ);
    glVertex2f(-1.0+.02*(float)x,     -1.0+.02*(float)y+ SZ);
    glEnd();
}

float magnitude(point p1, point p2){     // p1 newray   p2 light source
    
    point sub = point_subtract(p1, p2);  // be careful of reverse !!
    float result = sqrtf((sub.x * sub.x) + (sub.y * sub.y) + (sub.z * sub.z));
    return result;
    
}

float sphere_dist(point p1, point p2, point lightcen){
    
    
    float u = (((lightcen.x - p1.x) * (p2.x - p1.x)) + ((lightcen.y - p1.y) * (p2.y - p1.y)) +
               ((lightcen.z - p1.z) * (p2.z - p1.z))) / (magnitude(p2, p1) * magnitude(p2, p1));
    return u;
}

float tri_dist(point N, point p1, point p2, point p3){
    
    float u = dot_product(N, point_subtract(p3, p1)) / (dot_product(N, point_subtract(p2, p1)));
    return u;
}

TRIANGLE Tri_hit(float x, float y, float z, point p1){  //if we collide with a triangle, this is that triangle
    
    point N,I,V1,V2,V3,C1,C2,C3,P2;
    P2.x = x;
    P2.y = y;
    P2.z = z;
    float U,D1,D2,D3;
    TRIANGLE T;
    
    float best_u = INFINITY;
    TRIANGLE best_tri = makeTriangle(makePoint(-100, -100, -100), makePoint(-200, -200, -200), makePoint(-300, -300, -300));
    
    for(int i=0; i<=13; i++){
    
    T = TRIANGLES[i];
        
    N = cross_product((point_subtract(T.t3, T.t1)), (point_subtract(T.t2, T.t1)));
    U = dot_product(N, (point_subtract(T.t1, p1))) / dot_product(N, (point_subtract(P2, p1)));
    I = point_add(p1 , pointscaler_mult(U, (point_subtract(P2, p1))));
    
    V1 = point_subtract(T.t1, I);
    V2 = point_subtract(T.t2, I);
    V3 = point_subtract(T.t3, I);
    
    C1 = cross_product(V1, V2);
    C2 = cross_product(V2, V3);
    C3 = cross_product(V3, V1);
    
    D1 = dot_product(C1, C2);
    D2 = dot_product(C2, C3);
    D3 = dot_product(C3, C1);
    
    
    if((D1 > 0) && (D2 > 0) && (D3 > 0)){
        if(U < best_u  &&  U>0){
            best_u = U;
            best_tri = T;
        }
    }
    
    
    } //end for
    
    
    return best_tri;  // the best triangle

}

int light_intersect(point P, point lightcen, float lightradius){ // do we hit the light source?
    
    float mag = magnitude(P, lightcen);
    if(mag <= lightradius)
    
    {return 1;}
    
    
    else{ return 0; }
    
}

point tri_intersect( TRIANGLE T, point p1, point p2){   // p1 is eye p2 is our current xyz in loop
    
    point N,I,P2;
    float U;
    P2.x = p2.x;
    P2.y = p2.y;
    P2.z = p2.z;

    N = cross_product((point_subtract(T.t3, T.t1)), (point_subtract(T.t2, T.t1)));
    U = dot_product(N, (point_subtract(T.t1, p1))) / dot_product(N, (point_subtract(P2, p1)));
    I = point_add(p1 , pointscaler_mult(U, (point_subtract(P2, p1))));

    return I;

}


point find_normal( TRIANGLE T){   // find the normal of the triangle. A helper for Dot_compare
    
    point N;
    N = cross_product((point_subtract(T.t3, T.t1)), (point_subtract(T.t2, T.t1)));
    return N;
    
}

int Dot_compare(point ray, point newray,  TRIANGLE T){
    
    float CR = dot_product(ray, find_normal(T));  // for the current ray
    float LS = dot_product(goofy.l1, find_normal(T));   // for the light source used to be goofy.l1 not newray

    if((CR > 0 && LS > 0) || (CR < 0 && LS < 0)){   // they have the same sign, end the recursion
        return 0;
        
    }
    
    else{ return 1;}  // the signs differ, fire another ray
    
}


float ray(float x, float y, float z, point eye){ //returns total brightness of pixel we are coloring. pass eye and xyz
    float brightness = 0; //= 0.1; // default brightness
    point curr = makePoint(x, y, z);
    TRIANGLE trihit = Tri_hit(x,y,z,eye); // this is the best triangle or a dummy value
    float tri_u = -100;
    float light_u = 0;
    
    if(trihit.t1.x != -100){
        tri_u = tri_dist(find_normal(trihit), eye, curr, trihit.t3);    // !! passing wrong values
    }
    
    light_u = sphere_dist(eye, curr, goofy.l1);
    point P = point_add(eye, pointscaler_mult(light_u, point_subtract(curr, eye))); // closest point to light?
  
    
    if( (trihit.t1.x == -100) && (!(light_intersect(P, goofy.l1, goofy.radius)))){   // we have neither hit a tri nor the light
        
        brightness = 0;
    }
    
    if(light_intersect(P, goofy.l1, goofy.radius)){ // lightu < tri_u
         if(tri_u == -100){
         brightness = 1; // we have hit the light
         }
         
    }
   
    
     if(trihit.t1.x != -100 && (tri_u < light_u)){              // tri_u < light_u
        brightness = .1;
        point tri_point = tri_intersect(trihit, eye, curr);
       
        if(Dot_compare(point_subtract(curr, eye),point_subtract(goofy.l1, tri_point), trihit)){   // old ray , new ray used to be tri - goofy
            
            brightness += (ray(goofy.l1.x, goofy.l1.y, goofy.l1.z, tri_point))/(magnitude(goofy.l1, tri_point));  // used to be tri_point flipped
        }
    
     }
  
    return brightness;
}

void display(void)
{
    float bright_val;
    point eye;
    eye.x = eye.y = .5;
    eye.z = -1.0;
    scene(.2,.15,.6,.1);
    glClear(GL_COLOR_BUFFER_BIT);
    for(float x=0; x<=1; x+=.002){
        for(float y=0; y<=1; y+=.002){
           
            bright_val = ray(x, y, 0, eye);
            drawpixel(x*100, y*100, bright_val, bright_val, bright_val);  // USED TO BE *100
            
            }
    }
    
   
    glFlush();
}


int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutCreateWindow("platos scene");
    glutDisplayFunc(display);
    glutMainLoop();
}


