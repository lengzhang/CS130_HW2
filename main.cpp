#include <iostream>
#include <iomanip>
#include "vec.h"

using namespace std;

void Dump_png(unsigned int* data,int width,int height,const char* filename);

/*
 Problems 1-4
 
 Rewrite each loop so that only addition and subtraction occur inside any loop.
 This includes operations performed on the vec3 vectors.  Ignore the operations
 that occur while printing the results.
 
 Each problem is worth 10 points.  Note that for Problem 4, you must clear the
 multiplications and divisions from both loops.  If you are able to clear the
 multiplications and divisions from only the inner loop, you will still get 5
 points.
 */

void Problem_1(int n, float x, float y)
{
    /*
    for(int i = -n ; i <= n ; i++)
    {
        float z = i * x + y;
        cout << z << endl;
    }
    */
    
    float z[2*n+1];
    z[n] = y;
    for (int i = 1; i < 2*n+1; i++) {
        z[n-i] = z[n-i+1] - x;
        z[n+i] = z[n+i-1] + x;
    }
    for (int i = 0; i <= 2*n; i++) {
        cout << z[i] << endl;
    }
}

void Problem_2(int n, float x, float dx)
{
    /*
    for(int i = 0 ; i < n ; i++)
    {
        float y = x + dx * i;
        float z = y * y;
        cout << z << endl;
    }
    */
    float a = x * x;
    float b = x * dx;
    float c = dx * dx;
    
    float z = 0;
    int k = 1;
    
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            z += a;
        }
        else
        {
            z += b + b;
            for (int j = 0; j < k; j++) {
                z += c;
            }
            k += 2;
        }
        cout << z << endl;
    }
}

void Problem_3(int n, vec3 u, vec3 v, vec3 du)
{
    /*
    for(int i = 0 ; i < n ; i++)
    {
        vec3 w = u + du * i;
        float z = dot(w,v)/dot(v,v);
        cout << z << endl;
    }
    */
    float u_v = dot(u,v) / dot(v,v);
    float du_v = dot(du, v) / dot(v, v);
    float z = u_v - du_v;
    for (int i = 0; i < n; i++) {
        z += du_v;
        cout << z << endl;
    }
}

void Problem_4(int n, vec3 w, vec3 u, vec3 v)
{
    /*
    for(int i = 0 ; i <= n ; i++)
    {
        for(int j = 0 ; i + j <= n ; j++)
        {
            float a = (float)i/n;
            float b = (float)j/n;
            float c = 1 - a - b;
            vec3 z = a * w + b * u + c * v;
            cout << z << endl;
        }
    }
    */
    vec3 a = (w - v) / n;
    vec3 b = (u - v) / n;
    
    vec3 z_i = v - a - b;
    
    for (int i = 0 ; i <= n ; i++) {
        z_i += a;
        vec3 z = z_i;
        for (int j = 0 ; i + j <= n ; j++) {
            z += b;
            cout << z << endl;
        }
        
    }
}

/*
 Problem 5
 
 Draw a white circle centered at (x,y) with radius r.
 For example, data[y][x]=0xffffffff; would set the center of the circle to white.
 The circle should not have gaps.
 You may assume that the circle does not cross the edges of the circle.
 
 20 points.
 
 Extra credit options:
 A = you don't use any floating point.
 B = you do not use * or / in any loop, including in the loop condition.
 C = you fill the circle red (0xff0000ff) while keeping the outline white.
 
 A = 2% extra credit
 A + B = 5% extra credit
 A + B + C = 10% extra credit
 */
void draw_circle(int x, int y, int r)
{
    unsigned int data[512][512];
    for(int i = 0 ; i < 512; i++)
        for(int j = 0 ; j < 512; j++)
            data[i][j] = 0xff000000; // set all pixels to (0,0,0,1) = black.
     
    // TODO: your code here
    int X = 0;
    int Y = r;
    int D = 3 - 2 * r;

    data[x][y] = 0xff0000ff;
    data[x+X][y+Y] = 0xffffffff;
    data[x+X][y-Y] = 0xffffffff;
    for (int i = y - Y + 1; i < y + Y; i++)
                data[x+X][i] = 0xff0000ff;

    while (X < Y)
    {
        if (D < 0)
        {
            D = D + X + X + X + X + 6;
        }
        else
        {
            D = D + (X - Y) + (X - Y) + (X - Y) + (X - Y) + 10;
            Y--;
        }
        X++;
        data[x+X][y+Y] = 0xffffffff;
        data[x+X][y-Y] = 0xffffffff;
	for (int i = y - Y + 1; i < y + Y; i++)
		data[x+X][i] = 0xff0000ff;

	data[x-X][y+Y] = 0xffffffff;
	data[x-X][y-Y] = 0xffffffff;
	for (int i = y - Y + 1; i < y + Y; i++)
		data[x-X][i] = 0xff0000ff;
    }

    Y = 0;
    X = r;
    D = 3 - 2 * r;
    
    data[x+X][y+Y] = 0xffffffff;
    data[x-X][y+Y] = 0xffffffff;
    while (X > Y)
    {
	if (D < 0)
	{
		D = D + Y + Y + Y + Y + 6;
	}
	else
	{
		D = D + (Y - X) + (Y - X) + (Y - X) + (Y - X) + 10;
		X--;
	}
	Y++;
	data[x+X][y+Y] = 0xffffffff;
        data[x+X][y-Y] = 0xffffffff;
        data[x-X][y+Y] = 0xffffffff;
        data[x-X][y-Y] = 0xffffffff;
	for (int i = y - Y + 1; i < y + Y; i++)
                data[x+X][i] = 0xff0000ff;
	for (int i = y - Y + 1; i < y + Y; i++)
                data[x-X][i] = 0xff0000ff;
    }
    Dump_png(&data[0][0],512,512,"circle.png");
    
}

int main()
{
    cout << std::setprecision(4);
    
    cout << "== Problem 1 ==" << endl;
    
    Problem_1(5, -0.123, 2.114);
    
    cout << "== Problem 2 ==" << endl;
    
    Problem_2(5, -0.123, 2.114);
    
    cout << "== Problem 3 ==" << endl;
    
    Problem_3(5, vec3(.1,.2,.3), vec3(0.9,0.2,0.8), vec3(0.0,0.1,0.6));
    
    cout << "== Problem 4 ==" << endl;
    
    Problem_4(5, vec3(.1,.2,.3), vec3(0.9,0.2,0.8), vec3(0.0,0.1,0.6));
    
    cout << "== Problem 5 ==" << endl;
    
    draw_circle(220, 260, 200);
    
    return 0;
}

