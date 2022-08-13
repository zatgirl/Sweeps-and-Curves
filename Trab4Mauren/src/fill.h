#ifndef ___FILL__H___
#define ___FILL__H___

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <limits>

#include "gl_canvas2d.h"

#include "Vector2.h"
#include "Vector3.h"

class Fill
{
 public:

    ///retirado da internet
     // troca duas variaveis de pos
    #define SWAP(x,y) do { (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); } while(0)

    void lcd_hline(int x1, int x2, int y)
    {
        if (x1 >= x2)
            SWAP(x1, x2);

        for (; x1 <= x2; x1++)
            CV::point(x1, y);
    }

    // Fill a triangle - slope method
    // Original Author: Adafruit Industries
    void fillTriangleslope(int x0, int y0,int x1, int y1, int x2, int y2) {
        int a, b, y, last;
        // Sort coordinates by Y order (y2 >= y1 >= y0)
        if (y0 > y1) {
            SWAP(y0, y1);
            SWAP(x0, x1);
        }
        if (y1 > y2) {
            SWAP(y2, y1);
            SWAP(x2, x1);
        }
        if (y0 > y1) {
            SWAP(y0, y1);
            SWAP(x0, x1);
        }

        if(y0 == y2) { // All on same line case
            a = b = x0;
            if(x1 < a)      a = x1;
            else if(x1 > b) b = x1;
            if(x2 < a)      a = x2;
            else if(x2 > b) b = x2;
            lcd_hline(a, b, y0);
            return;
        }

        int
            dx01 = x1 - x0,
            dy01 = y1 - y0,
            dx02 = x2 - x0,
            dy02 = y2 - y0,
            dx12 = x2 - x1,
            dy12 = y2 - y1;
        int sa = 0, sb = 0;

        // For upper part of triangle, find scanline crossings for segment
        // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y
        // is included here (and second loop will be skipped, avoiding a /
        // error there), otherwise scanline y1 is skipped here and handle
        // in the second loop...which also avoids a /0 error here if y0=y
        // (flat-topped triangle)
        if(y1 == y2) last = y1;   // Include y1 scanline
        else         last = y1-1; // Skip it

        for(y=y0; y<=last; y++) {
                //printf("x0: %d, sa: %d, dy01: %d, dy02: %d, last: %.2f \n", x0,sa,dy01,dy02, last);
            a   = x0 + sa / dy01;
            b   = x0 + sb / dy02;
            sa += dx01;
            sb += dx02;
            // longhand a = x0 + (x1 - x0) * (y - y0) / (y1 - y0)
            //          b = x0 + (x2 - x0) * (y - y0) / (y2 - y0)
            lcd_hline(a, b, y);
        }

        // For lower part of triangle, find scanline crossings for segment
        // 0-2 and 1-2.  This loop is skipped if y1=y2
        sa = dx12 * (y - y1);
        sb = dx02 * (y - y0);
        for(; y<=y2; y++) {
            a   = x1 + sa / dy12;
            b   = x0 + sb / dy02;
            sa += dx12;
            sb += dx02;
            // longhand a = x1 + (x2 - x1) * (y - y1) / (y2 - y1)
            //          b = x0 + (x2 - x0) * (y - y0) / (y2 - y0)
            lcd_hline(a, b, y);
        }
    }

    // Fill a triangle - Bresenham method
    // Original from http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
    void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
        int t1x,t2x,y,minx,maxx,t1xp,t2xp;
        bool changed1 = false;
        bool changed2 = false;
        int signx1,signx2,dx1,dy1,dx2,dy2;
        int e1,e2;
        // Sort vertices
        if (y1>y2) { SWAP(y1,y2); SWAP(x1,x2); }
        if (y1>y3) { SWAP(y1,y3); SWAP(x1,x3); }
        if (y2>y3) { SWAP(y2,y3); SWAP(x2,x3); }

        t1x=t2x=x1; y=y1;   // Starting points

        dx1 = (int)(x2 - x1); if(dx1<0) { dx1=-dx1; signx1=-1; } else signx1=1;
        dy1 = (int)(y2 - y1);

        dx2 = (int)(x3 - x1); if(dx2<0) { dx2=-dx2; signx2=-1; } else signx2=1;
        dy2 = (int)(y3 - y1);

        if (dy1 > dx1) {   // swap values
            SWAP(dx1,dy1);
            changed1 = true;
        }
        if (dy2 > dx2) {   // swap values
            SWAP(dy2,dx2);
            changed2 = true;
        }

        e2 = (int)(dx2>>1);
        // Flat top, just process the second half
        if(y1==y2) goto next;
        e1 = (int)(dx1>>1);

        for (int i = 0; i < dx1;) {
            t1xp=0; t2xp=0;
            if(t1x<t2x) { minx=t1x; maxx=t2x; }
            else		{ minx=t2x; maxx=t1x; }
            // process first line until y value is about to change
            while(i<dx1) {
                i++;
                e1 += dy1;
                while (e1 >= dx1) {
                    e1 -= dx1;
                   if (changed1) t1xp=signx1;//t1x += signx1;
                    else          goto next1;
                }
                if (changed1) break;
                else t1x += signx1;
            }
        // Move line
        next1:
            // process second line until y value is about to change
            while (1) {
                e2 += dy2;
                while (e2 >= dx2) {
                    e2 -= dx2;
                    if (changed2) t2xp=signx2;//t2x += signx2;
                    else          goto next2;
                }
                if (changed2)     break;
                else              t2x += signx2;
            }
        next2:
            if(minx>t1x) minx=t1x; if(minx>t2x) minx=t2x;
            if(maxx<t1x) maxx=t1x; if(maxx<t2x) maxx=t2x;
            lcd_hline(minx, maxx, y);    // Draw line from min to max points found on the y
            // Now increase y
            if(!changed1) t1x += signx1;
            t1x+=t1xp;
            if(!changed2) t2x += signx2;
            t2x+=t2xp;
            y += 1;
            if(y==y2) break;

       }
        next:
        // Second half
        dx1 = (int)(x3 - x2); if(dx1<0) { dx1=-dx1; signx1=-1; } else signx1=1;
        dy1 = (int)(y3 - y2);
        t1x=x2;

        if (dy1 > dx1) {   // swap values
            SWAP(dy1,dx1);
            changed1 = true;
        } else changed1=false;

        e1 = (int)(dx1>>1);

        for (int i = 0; i<=dx1; i++) {
            t1xp=0; t2xp=0;
            if(t1x<t2x) { minx=t1x; maxx=t2x; }
            else		{ minx=t2x; maxx=t1x; }
            // process first line until y value is about to change
            while(i<dx1) {
                e1 += dy1;
                while (e1 >= dx1) {
                    e1 -= dx1;
                    if (changed1) { t1xp=signx1; break; }//t1x += signx1;
                    else          goto next3;
                }
                if (changed1) break;
                else   	   	  t1x += signx1;
                if(i<dx1) i++;
            }
        next3:
            // process second line until y value is about to change
            while (t2x!=x3) {
                e2 += dy2;
                while (e2 >= dx2) {
                    e2 -= dx2;
                    if(changed2) t2xp=signx2;
                    else          goto next4;
                }
                if (changed2)     break;
                else              t2x += signx2;
            }
        next4:

            if(minx>t1x) minx=t1x; if(minx>t2x) minx=t2x;
            if(maxx<t1x) maxx=t1x; if(maxx<t2x) maxx=t2x;
            lcd_hline(minx, maxx, y);    // Draw line from min to max points found on the y
            // Now increase y
            if(!changed1) t1x += signx1;
            t1x+=t1xp;
            if(!changed2) t2x += signx2;
            t2x+=t2xp;
            y += 1;
            if(y>y3) return;
        }
    }

    Fill(){
    }


};

#endif


