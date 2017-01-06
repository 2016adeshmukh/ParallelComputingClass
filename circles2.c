//
// Torbert, March 2015
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 640
#define N 480
typedef struct
{
   double x ;
   double y ;
   double z ;
   //
} triple ;

typedef struct
{
  triple color;
  triple center;
  double r;
} sphere ;
//
triple e = { 0.50 , 0.50 , -1.00 } ; // the eye
triple g = { 0.00 , 1.25 , -0.50 } ; // the light
sphere a[4];
//
double dotp( triple t , triple u )
{
   return t.x * u.x + t.y * u.y + t.z * u.z ;
}
//
void diff( triple* t , triple u , triple v ) // t = u - v
{
   t->x = u.x - v.x ;
   t->y = u.y - v.y ;
   t->z = u.z - v.z ;
}
//

void init()
{
   
   a[0].center.x =      0.50 ;
   a[0].center.y = -20000.00 ; // the floor
   a[0].center.z =      0.50 ;
   a[0].r   =  20000.25 ;
   a[0].color.x =    205    ; // color is Peru
   a[0].color.y =    133    ;
   a[0].color.z =     63    ;
   //
   a[1].center.x =      0.50 ;
   a[1].center.y =      0.50 ;
   a[1].center.z =      0.50 ;
   a[1].r   =      0.25 ;
   a[1].color.x =      0    ; // color is Blue
   a[1].color.y =      0    ;
   a[1].color.z =    255    ;
   //
   a[2].center.x =      1.00 ;
   a[2].center.y =      0.50 ;
   a[2].center.z =      1.00 ;
   a[2].r   =      0.25 ;
   a[2].color.x =      0    ; // color is Green
   a[2].color.y =    255    ;
   a[2].color.z =      0    ;
   //
   a[3].center.x =      0.00 ;
   a[3].center.y =      0.75 ;
   a[3].center.z =      1.25 ;
   a[3].r   =      0.50 ;
   a[3].color.x =    255    ; // color is Red
   a[3].color.y =      0    ;
   a[3].color.z =      0    ;
}
double intersect(triple eye, triple vector, triple cent, int i)
{
 double a=1;
 //b is 2*dot of r and (eye-center)
 triple eyecent;
 diff(&eyecent, eye, cent);
 double b=dotp(vector, eyecent);
 //c is (ex-cx)^2+(ey-xy)^2+(ez-cz)^2-r^2
 double c=pow((eye.x-cent.x),2)+pow((eye.y-cent.y),2)+pow((eye.z-cent.z),2);
 double det=pow(b,2)-4*a*c;
 double toreturn=500;
 if(det>0)
 {
   double xone=((-1*b)+det)/(2*a); 
   double xtwo=((-1*b)-det)/(2*a);
   if(xone>0&&xtwo>0)
   {
      if(xone<xtwo)
      {
         toreturn=xone;
      }
      else
      {
         toreturn=xtwo;
      }
   }
   else if(xone>0)
   {
      return xone;
   }
   else if (xtwo>0)
   {
      return xtwo;
   }
   else
   {
      return toreturn;
   }
 }
}
int main(void)
{
   int rgb[N][M][3] ; // red-green-blue for each pixel
   //
   int y , x ;
   //
   FILE* fout ;
   //
   
   for( y = 0 ; y < N ; y++ )
   {
      for( x = 0 ; x < M ; x++)
      {
	 triple p;
	 p.x=(x/480);
	 p.y=(y/480);
	 p.z=0;
	 //set p vector and scale x and y
	 triple r;
	 diff(&r, p, e);
	 //make r vector between screen and eye
	 double rMagnitude =sqrt(dotp(r,r));
	r.x /= rMagnitude;
	r.y /= rMagnitude;
	r.z /= rMagnitude;
	//normalizes r vector so magnitude is 1
	int aa;
   double small=1000;
   double smalltemp;
   double sph=4;
	for(aa=0;aa<4;aa++)
	{
	  smalltemp=intersect(e, r, a[aa].center, a[aa].r);
     if(smalltemp<small)
     {
      small=smalltemp;
      sph=aa;
     }
	}
	 rgb[y][x][0] = 0   ; // red
         rgb[y][x][1] = 255 ; // green
         rgb[y][x][2] = 0   ; // blue
      }
   }
   //
   //
   //
   fout = fopen( "allgreen.ppm" , "w" ) ;
   //
   fprintf( fout , "P3\n" ) ;
   fprintf( fout , "%d %d\n" , M , N ) ;
   fprintf( fout , "255\n" ) ;
   //
   for( y = 0 ; y < N ; y++ )
   {
      for( x = 0 ; x < M ; x++)
      {
         fprintf( fout , "%d %d %d\n" ,
          rgb[y][x][0] , rgb[y][x][1] , rgb[y][x][2] ) ;
      }
   }
   fclose( fout ) ;
   //
  return 0;
}
   