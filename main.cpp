//---------------------------------------
//- Gradient Descent Linear Regression  -
//---------------------------------------
//- By: SELLAM Abdellah                 -
//- PhD Student at USTHB-LRIA/ALGERIA   -
//---------------------------------------
//- Creation Date: 26-06-2018           -
//---------------------------------------
//- This program illustrates the use of -
//- Linear Regression based on Gradient -
//- Descent to find the line that       -
//- approximates a 2D-Points'           -
//- distribution                        -
//- Rendering is done with OpenGL and   -
//- Win32 API                           -
//---------------------------------------

//Windows' Stuff
#define _WIN32_WINNT 0x0501
#define _WIN32_IE    0x0300
//Include Windows API
#include <windows.h>
#include <commctrl.h>
//stdio is used for Number-To-String conversion using sprintf
#include <stdio.h>
//Invoke the OpenGL API
#include <gl/gl.h>
//A library which contains some WinAPI Shortcuts
#include "WinStuff.h"
//Maximum Number of points defined by the user
#define MAX_POINTS 64
#define PS 0.05
#define BS 50
#define WD 440
#define HG 440

HBRUSH MainBackGD,WhiteBrush;
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
HWND mwnd,//Main Window
     pwnd,//OpenGL 2D-Points Rendering Window
     plist,//2D-Points Data ListBox View
     atext,//display for: a (Line Model)
     btext,//display for: b (Line Model)
     datext,//display for: loss partial derivative in respect to a
     dbtext,//display for: loss partial derivative in respect to b
     ltext,//display for: loss function's value
     etext,//display for: Epoch
     lredit,//User-Input-Field for: Learning Rate
     meedit,//User-Input-Field for: Max Epochs
     cbutton,//Clear 2D-points' data button
     sbutton,//Start Linear Regresssion
     obutton;//Start Linear Regresssion for one step only
HDC pDC;//Win32 GDI Device Context
HGLRC pRC;//OpenGL Rendering Context
int GDLR_START=0;//A boolean to fire Automatic Linear Regression
int GDLR_EPOCH=0;//Current Linear Regression's Iteration
int GDLR_MAXEP=1000;//Maximum number of Epochs
float GDLR_LR=0.01f;//Learning Rate
float a=0.0f,b=0.0f;//(a,b) Linear Model (y=ax+b)
float X[MAX_POINTS],Y[MAX_POINTS];//List of 2D-Points (X,Y)
int N=0;//Number of Points
DWORD LastFrame,FrameStep=100;//Linear Regression Frame Rate
                              //Expressed in terms of milliseconds
                              //Between each computation(iteration)

//OpenGL Stuff -> Initialization
//------------------------------
//Sets the projection matrix to Orthogonal in respect to
//The size of the rendering window
//Arguments:
//----------
//W: Width
//H: Height
void glResize(float W,float H)
{
    glViewport(0,0,W,H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5f*W/BS,+0.5f*W/BS,-0.5f*H/BS,+0.5f*H/BS,-1.0f,+1.0f);
    glMatrixMode(GL_MODELVIEW);
}
//OpenGL Stuff -> Rendering
//-------------------------
//Does the main rendering (Rendering of the 2D-Points and
//                         The Line (a,b)
void glRender()
{
    int BS2=2*BS;//Grid's Block Size in pixels (X/Y Step)
    float px=1.0f/BS;//A pixel's Size in OpenGL Projection Space
    float MinX=-WD/BS2-1.0f;//Minimum visible X as Integer
    float MaxX=+WD/BS2+1.0f;//Maximum visible X as Integer
    float MinY=-HG/BS2-1.0f;//Minimum visible Y as Integer
    float MaxY=+HG/BS2+1.0f;//Maximum visible Y as Integer
    glClearColor(1.0f,1.0f,1.0f,1.0f);//Background Color (White)
    glClear(GL_COLOR_BUFFER_BIT);//Background Rendering
    glColor3ub(127,127,127);//Gray Color From X/Y Grid Lines
    glBegin(GL_LINES);//Starts a Lines' OpenGL Rendering List
    for(float x=MinX;x<=MaxX;x+=1.0f)//Go through integer X Values (Grid Rednering)
    {
        glVertex2f(x,MinY);
        glVertex2f(x,MaxY);
    }
    for(float y=MinY;y<=MaxY;y+=1.0f)//Go through integer Y Values (Grid Rednering)
    {
        glVertex2f(MinX,y);
        glVertex2f(MaxX,y);
    }
    glEnd();//Stop Line Rendering Mode
    glColor3ub(0,0,0);//Black Color for X=0/Y=0
    glBegin(GL_LINES);//Starts a Lines' OpenGL Rendering List
    glVertex2f(+0.0f,MinY);
    glVertex2f(+0.0f,MaxY);//Render X=0 line
    glVertex2f(MinX,+0.0f);
    glVertex2f(MaxX,+0.0f);//Render Y=0 line
    glEnd();//Stop Line Rendering Mode

    glColor3ub(255,0,0);//Red Color For 2D-Points
    glBegin(GL_QUADS);//Quads Rednering Mode
    for(int i=0;i<N;i++)//Go trough all 2D-Points
    {                   //And Reder them as diamonds
        glVertex2f(X[i]-PS,Y[i]);
        glVertex2f(X[i],Y[i]-PS);
        glVertex2f(X[i]+PS,Y[i]);
        glVertex2f(X[i],Y[i]+PS);
    }
    glEnd();

    glColor3ub(0,0,255);//Blue Color For the Line model
    glBegin(GL_LINES);
    glVertex2f(MinX,a*MinX+b);
    glVertex2f(MaxX,a*MaxX+b);
    glEnd();

    //Outer Frame Rendering
    float X0=-0.5f*WD/BS;
    float X1=+0.5f*WD/BS;
    float Y0=-0.5f*HG/BS;
    float Y1=+0.5f*HG/BS;
    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(X0+px,Y0);
    glVertex2f(X1,Y0);
    glVertex2f(X1,Y1-px);
    glVertex2f(X0,Y1-px);
    glEnd();
}

//Linear Regression on a Single 2D-Point
//--------------------------------------
void gdLinearRegression()
{
    int i=GDLR_EPOCH%N;// 2D-Point Used on This Epoch
    float er=a*X[i]+b-Y[i];// The Error Between Real and
                           // Computed Output
    float da=2*X[i]*er;// Partial Loss Derivative in respect to a
    float db=2*er;// Partial Loss Derivative in respect to b
    a=a-GDLR_LR*da;// Gradient Descent Update for a
    b=b-GDLR_LR*db;// Gradient Descent Update for b
    float l=er*er;// Loss Computation
    //Windows' Stuff -> Displaying Learning Params
    char A[64],B[64],DA[64],DB[64],L[64],E[64];
    sprintf(A," a:\n %.03f",a);
    sprintf(B," b:\n %.03f",b);
    sprintf(DA," dL/da:\n %.03f",da);
    sprintf(DB," dL/db:\n %.03f",db);
    sprintf(L," Loss ( L=(y-ax-b)² ):\n %.03f",l);
    sprintf(E," Epoch:\n %d",GDLR_EPOCH);
    SetWindowText(atext,A);
    SetWindowText(btext,B);
    SetWindowText(datext,DA);
    SetWindowText(dbtext,DB);
    SetWindowText(ltext,L);
    SetWindowText(etext,E);
    SendMessage(plist,LB_SETCURSEL,i,0);
    //Advancing One Epoch
    GDLR_EPOCH++;
    if(GDLR_EPOCH>=GDLR_MAXEP)
    {
        SetWindowText(sbutton,"Start");
        GDLR_START=0;
        GDLR_EPOCH=0;
    }
}

//Windows Stuff-> Main Entry for Win32 Programs
//------------------------
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    MSG msg;
    BOOL bQuit = FALSE;
    //Window Background Brush
    MainBackGD= CreateSolidBrush(RGB(240,240,240));
    //StaticText Elements' Background Brush
    WhiteBrush= CreateSolidBrush(RGB(255,255,255));
    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, "aaMainIcon");
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = MainBackGD;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szClassName3;
    wcex.hIconSm = LoadIcon(hInstance, "aaMainIcon");;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window and its sub-elements*/
    //Font For 2D-Points ListView
    HFONT ListFont = NewBFont("Courier New",20);
    //Font For Other Window Elements
    HFONT MainFont = NewBFont("Times New Roman",20);
    //Main Window
    mwnd = NewDlgWindow(HWND_DESKTOP,WD+570,HG+20,"Linear Regression - By: SELLAM Abdellah");
    //OpenGL Rendering Element
    pwnd = NewPanel(mwnd,10,10,WD,HG);
    //ListView For 2D-Points' DataSet
    plist = NewListBox(mwnd,WD+20,10,160,HG,ListFont);
    //Current Epoch StaticText Element
    etext = NewStatic(mwnd,WD+190,10,200,45," Epoch:\n 0",MainFont);
    //a Value's StaticText Element
    atext = NewStatic(mwnd,WD+190,80,200,45," a:\n 0.000",MainFont);
    //b Value's StaticText Element
    btext = NewStatic(mwnd,WD+190,130,200,45," b:\n 0.000",MainFont);
    //Loss Value's StaticText Element
    ltext = NewStatic(mwnd,WD+190,200,200,45," Loss ( L=(y-ax-b)² ):\n 0.000",MainFont);
    //dLoss/da Value's StaticText Element
    datext = NewStatic(mwnd,WD+190,250,200,45," dL/da:\n 0.000",MainFont);
    //dLoss/db Value's StaticText Element
    dbtext = NewStatic(mwnd,WD+190,300,200,45," dL/db:\n 0.000",MainFont);
    //Learning Rate Input Field
    NewStatic(mwnd,WD+400,10,160,25," Learning Rate",MainFont);
    lredit = NewDlgEdit(mwnd,WD+400,36,160,25,"0.01",MainFont);
    //Max Epochs Input Field
    NewStatic(mwnd,WD+400,70,160,25," Max-Epochs",MainFont);
    meedit = NewDlgEdit(mwnd,WD+400,96,160,25,"1000",MainFont);
    //Start Button
    sbutton = NewDlgDefButton(mwnd,WD+400,130,160,40,"Start",MainFont);
    //One-Step Button
    obutton = NewDlgButton(mwnd,WD+400,180,160,40,"One-Step",MainFont);
    //Clear Points Button
    cbutton = NewDlgButton(mwnd,WD+400,230,160,40,"Clear Points",MainFont);

    ShowWindow(mwnd, nCmdShow);//Make the Window Visible
    SetClassLongPtr(cbutton,GCLP_HCURSOR,(LONG_PTR)LoadCursor(NULL,IDC_HAND));
    /* enable OpenGL for the window */
    EnableOpenGL(pwnd, &pDC, &pRC);
    glResize(WD,HG);//Initialize Pojection Matrix of OpenGL
    LastFrame=GetTickCount();//Start Measering Time Changes
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else  if(!MyIsDialogMessage(&msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            //Get Current Time in Milliseconds
            DWORD ThisFrame=GetTickCount();
            //if Time from last computation is enough
            if(ThisFrame-LastFrame>=FrameStep)
            {
                //Do a new computational epoch if
                //Linear Regression is fired by the user
                if(GDLR_START)
                    gdLinearRegression();
                LastFrame=ThisFrame;//Make current Time
                                    //The Last Computation's
                                    //Time
            }
            glRender();//OpenGL Rendering
            SwapBuffers(pDC);//Win32/OpenGL Stuff
            Sleep(1);//Sleep For 1 millisecond before next
                     //Work, used to free the processor if
                     //No Window message is received and
                     //Rendering is done, this will make
                     //CPU really happy! :p
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(pwnd, pDC, pRC);

    /* destroy the window explicitly */
    DestroyWindow(mwnd);

    return msg.wParam;
}

//Windows' Stuff -> Window Procedure
//----------------------------------
//User To Process Events send by windows OS to our window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE://Window is Closed
            PostQuitMessage(0);//Finished the Program
        break;

        case WM_DESTROY://Window is destroyed
            return 0;

        case WM_CTLCOLORBTN://Used to make buttons fancier
        {
            HDC hdcBtn = (HDC) wParam;
            SetBkColor(hdcBtn, RGB(240,240,240));
            SetTextColor(hdcBtn, RGB(0,0,0));
            return (LRESULT)MainBackGD;
        }

        case WM_CTLCOLORSTATIC://Used to make StaticText Elements fancier
        {
            HDC hdcBtn = (HDC) wParam;
            SetBkColor(hdcBtn, RGB(255,255,255));
            SetTextColor(hdcBtn, RGB(0,0,0));
            return (LRESULT)WhiteBrush;
        }

        case WM_LBUTTONDOWN://The Mouse button is pressed
        {
            //Verifiy that the concerned window is the
            //OpenGL window and that Linear Regression is
            //not on
            if(hwnd==pwnd&&GDLR_START==0)
            {
                int MX=LOWORD(lParam);//Mouse's X Position
                int MY=HIWORD(lParam);//Mouse's Y Position
                if(N<MAX_POINTS)//Avoids Overflow
                {
                    //Add a new point based on mouse position
                    char Point[64];
                    X[N]=(MX-0.5f*WD)/BS;
                    Y[N]=(0.5f*HG-MY)/BS;
                    if(X[N]<0&&Y[N]<0)
                        sprintf(Point,"%.03f %.03f",X[N],Y[N]);
                    else if(X[N]<0)
                        sprintf(Point,"%.03f +%.03f",X[N],Y[N]);
                    else if(Y[N]<0)
                        sprintf(Point,"+%.03f %.03f",X[N],Y[N]);
                    else
                        sprintf(Point,"+%.03f +%.03f",X[N],Y[N]);
                    SendMessage(plist,LB_ADDSTRING,0,(LPARAM)Point);
                    N++;
                }
            }
            return 0;
        }

        case WM_KEYDOWN://Keyboard pressed
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        case WM_COMMAND://Handles Click events (and others)
        {
            int wNotifyCode=HIWORD(wParam);
            int wID=LOWORD(wParam);
            HWND hwndCtl=(HWND)lParam;
            if(wNotifyCode==BN_CLICKED)//Button Clicked
            {
                if(hwndCtl==cbutton)//Clear Points' Button
                {
                    for(int i=0;i<N;i++)
                        SendMessage(plist,LB_DELETESTRING,0,0);
                    N=0;
                    return 0;
                }
                if(hwndCtl==obutton)//One-Step Button
                {
                    gdLinearRegression();
                    return 0;
                }
                if(hwndCtl==sbutton)//Linear Regression Loop
                {                   //Button
                    if(GDLR_START==0)//Linear Regression is off
                    {
                        if(N<2)//Not enough data (2D-Points)
                        {
                            MessageBox(mwnd,"Not enough data! A minimum of two points is required!","Linear Regression",MB_OK|MB_ICONWARNING);
                            return 0;//Break
                        }
                        //Get User Inputs for LR and MaxEpochs
                        char LR[16],ME[16];
                        GetWindowText(lredit,LR,16);
                        GetWindowText(meedit,ME,16);
                        GDLR_LR=atof(LR);//StringToFloat
                        GDLR_MAXEP=atoi(ME);//StringToInt
                        GDLR_START=1;//Fire Linear Regression
                                     //Loop
                        //Updating GUI
                        SetWindowText(sbutton,"Stop");
                        EnableWindow(obutton,FALSE);
                        EnableWindow(cbutton,FALSE);
                        return 0;//Break
                    }
                    //Linear Regression is on
                    //Updating GUI
                    EnableWindow(obutton,TRUE);
                    EnableWindow(cbutton,TRUE);
                    SetWindowText(sbutton,"Start");
                    //Stop Linear Regression Loop
                    GDLR_START=0;
                    return 0;
                }
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
//OpenGL Stuff -> Activate OpenGL
void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}
//OpenGL Stuff -> Deactivate OpenGL
void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

