/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <string>
#include <gl/gl.h>
#include "GLUTMingw32\include\GL/glut.h"
#include <stdlib.h>


/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

/**************************
 * Custom Function Declarations and obj initialization
 *
 **************************/
/// Includes Game class.
#include "game.h"

extern void displayText(float, float, int,int,int,const char *);

#include "screenData.h"



/********************
 * Window Procedure
 *
 ********************/
///Function to handle window inputs.
LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        case 'Q':
            PostQuitMessage(0);
            return 0;
        case VK_SPACE:
            if (game.ifStarted()==0)
            {
                game.start();

            }

            game.flip(1);
            return 0;
        case VK_NUMPAD0 :
            game.flip(2);
            return 0;
        case 'M':
            game.over(0);
            return 0;
        case 'A':
            game.About(1);
            return 0;
        case 'H':
            game.Help(1);
            return 0;
        }

        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/
///Function to enable OpenGL in the window. Counterpart of DisableOpenGL().
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/
///Function to disable OpenGL in the window. Counterpart of EnableOpenGL().
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}

/**************************
 * WinMain
 *
 **************************/
///     Main function to initialize window using WINAPI.
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "RivalRun";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
               "RivalRun", "RivalRun",
               WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
               0, 0, 1000, 500,
               NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            if (game.ifStarted())
            {
                gameGround(hDC);

            }
            else if (game.About()) about();
            else if (game.Help()) help();
            else if (game.Winner()) summary();
            else
            {
                startScreen(hDC, game.Theta());
                game.Theta(0);

            }


            SwapBuffers (hDC);
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            game.Theta(game.Theta()+ 5.0f);
            Sleep (1);

        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}
///Function to display text wrapping glutBitmapCharacter().
void displayText( float x, float y, int r, int g, int b, const char *string )
{
    int j = strlen( string );

    glColor3f( r, g, b );
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    }
}
/// Function to display number wrapping glutBitmapCharacter().
void displayNum( float x, float y, int r, int g, int b, int num )
{
    glColor3f( r, g, b );
    glRasterPos2f( x, y );
    int m,n;
    m= num%10;
    n= num/10;
    if(num>9) glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, 48+n );
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, 48+m );
}

