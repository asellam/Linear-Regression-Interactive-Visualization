char*szClassName3="GDLR";
HINSTANCE hInstance;
#define MAX_DBWINDOWS 65536
//Dialog Box Windows
HWND dbHwnds[MAX_DBWINDOWS];
//Dialog Box Count
int dbCount=0;
//Creates a new Font
HFONT NewFont(char*FontFace,int FontSize)
{
    return CreateFont(FontSize,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,FontFace);
}
//Creates a new Font
HFONT NewBFont(char*FontFace,int FontSize)
{
    return CreateFont(FontSize,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,FontFace);
}
//Creates a General Overlapped Window
HWND NewWindow(int Left,int Top,int Width,int Height,char*Title)
{
    HWND WINDOW=CreateWindowEx(0,szClassName3,Title,WS_POPUP|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,Left,Top,Width,Height,HWND_DESKTOP,NULL,hInstance,NULL);
    return WINDOW;
}
//Creates a Popup Overlapped Window
HWND NewPopup(HWND Parent,int Left,int Top,int Width,int Height,char*Title)
{
    RECT AREA;
    AREA.top=0;AREA.bottom=Height;
    AREA.left=0;AREA.right=Width;
    AdjustWindowRectEx(&AREA,WS_POPUP|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,FALSE,0);
    int aHeight=AREA.bottom-AREA.top;
    int aWidth=AREA.right-AREA.left;
    HWND WINDOW=CreateWindowEx(0,szClassName3,Title,WS_POPUP|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,Left-aWidth+Width,Top-aHeight+Height,aWidth,aHeight,Parent,NULL,hInstance,NULL);
    return WINDOW;
}
//Creates a General Overlapped Window
HWND NewWindow(HWND Parent,int Width,int Height,char*Title)
{
    RECT AREA,ClientArea;
    ClientArea.top=0;ClientArea.bottom=Height;
    ClientArea.left=0;ClientArea.right=Width;
    SystemParametersInfo(SPI_GETWORKAREA,0,&AREA,0);
    AdjustWindowRectEx(&ClientArea,WS_POPUP|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,FALSE,0);
    int aHeight=ClientArea.bottom-ClientArea.top;
    int aWidth=ClientArea.right-ClientArea.left;
    HWND WINDOW=CreateWindowEx(0,szClassName3,Title,WS_POPUP|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,(AREA.right-AREA.left-aWidth)/2,(AREA.bottom-AREA.top-aHeight)/2,aWidth,aHeight,Parent,NULL,hInstance,NULL);
    return WINDOW;
}
//Creates a General Overlapped Window
HWND NewWindow(char*ClassName,HWND Parent,int Width,int Height,char*Title)
{
    RECT AREA,ClientArea;
    ClientArea.top=0;ClientArea.bottom=Height;
    ClientArea.left=0;ClientArea.right=Width;
    SystemParametersInfo(SPI_GETWORKAREA,0,&AREA,0);
    AdjustWindowRectEx(&ClientArea,WS_POPUP|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,FALSE,0);
    int aHeight=ClientArea.bottom-ClientArea.top;
    int aWidth=ClientArea.right-ClientArea.left;
    HWND WINDOW=CreateWindowEx(0,ClassName,Title,WS_POPUP|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,(AREA.right-AREA.left-aWidth)/2,(AREA.bottom-AREA.top-aHeight)/2,aWidth,aHeight,Parent,NULL,hInstance,NULL);
    return WINDOW;
}
//Creates a General Overlapped Window
HWND NewDlgWindow(HWND Parent,int Width,int Height,char*Title)
{
    RECT AREA,ClientArea;
    ClientArea.top=0;ClientArea.bottom=Height;
    ClientArea.left=0;ClientArea.right=Width;
    SystemParametersInfo(SPI_GETWORKAREA,0,&AREA,0);
    AdjustWindowRectEx(&ClientArea,WS_POPUP|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,FALSE,0);
    int aHeight=ClientArea.bottom-ClientArea.top;
    int aWidth=ClientArea.right-ClientArea.left;
    HWND WINDOW=CreateWindowEx(0,szClassName3,Title,WS_POPUP|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,(AREA.right-AREA.left-aWidth)/2,(AREA.bottom-AREA.top-aHeight)/2,aWidth,aHeight,Parent,NULL,hInstance,NULL);
    dbHwnds[dbCount]=WINDOW;
    dbCount++;
    return WINDOW;
}
//Creates a General Overlapped Window
HWND NewDlgWindow(char*ClassName,HWND Parent,int Width,int Height,char*Title)
{
    RECT AREA,ClientArea;
    ClientArea.top=0;ClientArea.bottom=Height;
    ClientArea.left=0;ClientArea.right=Width;
    SystemParametersInfo(SPI_GETWORKAREA,0,&AREA,0);
    AdjustWindowRectEx(&ClientArea,WS_POPUP|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,FALSE,0);
    int aHeight=ClientArea.bottom-ClientArea.top;
    int aWidth=ClientArea.right-ClientArea.left;
    HWND WINDOW=CreateWindowEx(0,ClassName,Title,WS_POPUP|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,(AREA.right-AREA.left-aWidth)/2,(AREA.bottom-AREA.top-aHeight)/2,aWidth,aHeight,Parent,NULL,hInstance,NULL);
    dbHwnds[dbCount]=WINDOW;
    dbCount++;
    return WINDOW;
}
//Creates a General ToolBar Container
HWND NewToolBar(HWND Parent)
{
    return CreateWindowEx(0,"STATIC","TOOLBARFACE",WS_CHILD|WS_VISIBLE|SS_BITMAP,0,0,1366,32,Parent,NULL,hInstance,NULL);
}
//Creates a General Radio Button
HWND NewRadio(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON",Title,WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General Check Box
HWND NewCheckBox(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON",Title,WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX|BS_MULTILINE,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General Check Box
HWND NewDlgCheckBox(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON",Title,WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_AUTOCHECKBOX,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General Check Box
HWND New3State(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON",Title,WS_CHILD|WS_VISIBLE|BS_3STATE,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a Visible Tab Page
HWND NewPanel(HWND Parent,int Left,int Top,int Width,int Height)
{
    HWND SURFACE = CreateWindowEx(0,szClassName3,"",WS_CHILD|WS_VISIBLE,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    return SURFACE;
}
//Creates a Visible Tab Page
HWND NewVTabPage(HWND Parent,int Left,int Top,int Width,int Height)
{
    HWND SURFACE = CreateWindowEx(0,szClassName3,"",WS_CHILD|WS_VISIBLE|WS_BORDER,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    return SURFACE;
}
//Creates a Hidden Tab Page
HWND NewHTabPage(HWND Parent,int Left,int Top,int Width,int Height)
{
    HWND SURFACE = CreateWindowEx(0,szClassName3,"",WS_CHILD|WS_BORDER,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    return SURFACE;
}
//Creates a General Button
HWND NewButton(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON",Title,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General Button
HWND NewMLButton(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON",Title,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_MULTILINE,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General Button
HWND NewButton(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont,char*MainIcon)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON",Title,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    HICON SURFACE_ICON=LoadIcon(hInstance,MainIcon);
    SendMessage(SURFACE,BM_SETIMAGE,IMAGE_ICON,(LPARAM)SURFACE_ICON);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General Button
HWND NewMLButton(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont,char*MainIcon)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON",Title,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_MULTILINE,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    HICON SURFACE_ICON=LoadIcon(hInstance,MainIcon);
    SendMessage(SURFACE,BM_SETIMAGE,IMAGE_ICON,(LPARAM)SURFACE_ICON);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General Button
HWND NewDlgDefButton(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont,char*MainIcon)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON",Title,WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_DEFPUSHBUTTON,Left,Top,Width,Height,Parent,(HMENU)IDOK,hInstance,NULL);
    HICON SURFACE_ICON=LoadIcon(hInstance,MainIcon);
    SendMessage(SURFACE,BM_SETIMAGE,IMAGE_ICON,(LPARAM)SURFACE_ICON);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}//Creates a General Button
HWND NewDlgButton(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont,char*MainIcon)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON",Title,WS_CHILD|WS_VISIBLE|WS_TABSTOP,Left,Top,Width,Height,Parent,(HMENU)IDOK,hInstance,NULL);
    HICON SURFACE_ICON=LoadIcon(hInstance,MainIcon);
    SendMessage(SURFACE,BM_SETIMAGE,IMAGE_ICON,(LPARAM)SURFACE_ICON);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General Button
HWND NewDlgDefButton(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON",Title,WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_DEFPUSHBUTTON,Left,Top,Width,Height,Parent,(HMENU)IDOK,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}//Creates a General Button
HWND NewDlgButton(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON",Title,WS_CHILD|WS_VISIBLE|WS_TABSTOP,Left,Top,Width,Height,Parent,(HMENU)IDOK,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General Button
HWND NewIconButton(HWND Parent,int Left,int Top,int Width,int Height,char*MainIcon)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON","",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_ICON,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    HICON SURFACE_ICON=LoadIcon(hInstance,MainIcon);
    SendMessage(SURFACE,BM_SETIMAGE,IMAGE_ICON,(LPARAM)SURFACE_ICON);
    return SURFACE;
}
//Creates a General Button
HWND NewBitmButton(HWND Parent,int Left,int Top,int Width,int Height,char*BitMap)
{
    HWND SURFACE = CreateWindowEx(0,"BUTTON","",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_BITMAP,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    HBITMAP SURFACE_BITM=LoadBitmap(hInstance,BitMap);
    SendMessage(SURFACE,BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)SURFACE_BITM);
    return SURFACE;
}
//Creates a General STATIC TEXT
HWND NewStaticNoEllip(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"STATIC",Title,WS_VISIBLE|WS_CHILD,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General STATIC TEXT
HWND NewStatic(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"STATIC",Title,WS_VISIBLE|WS_CHILD|WS_BORDER,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General STATIC TEXT
HWND NewBStatic(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(WS_EX_STATICEDGE,"STATIC",Title,WS_VISIBLE|WS_CHILD|SS_ENDELLIPSIS,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates an IconView
HWND NewIconView(HWND Parent,int Left,int Top,int Width,int Height,char*Icon)
{
    HWND SURFACE = CreateWindowEx(0,"STATIC",Icon,WS_VISIBLE|WS_CHILD|SS_ICON|SS_REALSIZEIMAGE,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    return SURFACE;
}
//Creates an ImageView
HWND NewImageView(HWND Parent,int Left,int Top,char*Image)
{
    HWND SURFACE = CreateWindowEx(0,"STATIC",Image,WS_VISIBLE|WS_CHILD|SS_BITMAP|SS_REALSIZEIMAGE,Left,Top,0,0,Parent,NULL,hInstance,NULL);
    return SURFACE;
}
//Creates a Right-Aligned STATIC TEXT
HWND NewDlgStatic(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"STATIC",Title,WS_VISIBLE|WS_CHILD|SS_RIGHT,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a Center-Aligned STATIC TEXT
HWND NewTtlStatic(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"STATIC",Title,WS_VISIBLE|WS_CHILD|SS_CENTER,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a Password EDIT TEXT
HWND NewPEdit(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Title,WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_PASSWORD,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General EDIT TEXT
HWND NewIntEdit(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Title,WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_NUMBER,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General EDIT TEXT
HWND NewEdit(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Title,WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General EDIT TEXT
HWND NewEdit(HWND Parent,int Left,int Top,int Width,int Height,int MaxLength,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Title,WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    SendMessage(SURFACE,EM_LIMITTEXT,MaxLength,0);
    return SURFACE;
}
//Creates a DLG EDIT TEXT
HWND NewDlgTextArea(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Title,WS_VISIBLE|WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_WANTRETURN|ES_MULTILINE|WS_VSCROLL,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a EDIT TEXT
HWND NewETextArea(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Title,WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_WANTRETURN|ES_MULTILINE|ES_CENTER|WS_VSCROLL,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a EDIT TEXT
HWND NewTextArea(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Title,WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_WANTRETURN|ES_MULTILINE|WS_VSCROLL,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a DLG EDIT TEXT
HWND NewDlgEdit(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Title,WS_VISIBLE|WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a DLG EDIT TEXT
HWND NewDlgEdit(HWND Parent,int Left,int Top,int Width,int Height,int MaxLength,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Title,WS_VISIBLE|WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    SendMessage(SURFACE,EM_LIMITTEXT,MaxLength,0);
    return SURFACE;
}
//Creates a DLG Password EDIT TEXT
HWND NewDlgPEdit(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Title,WS_VISIBLE|WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_PASSWORD,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a INT EDIT TEXT
HWND NewDlgIntEdit(HWND Parent,int Left,int Top,int Width,int Height,char*Title,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Title,WS_VISIBLE|WS_CHILD|WS_TABSTOP|ES_NUMBER|ES_AUTOHSCROLL,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General ListBox
HWND NewListBoxC(HWND Parent,int Left,int Top,int Width,int Height,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"LISTBOX","",WS_CHILD|WS_VISIBLE|WS_VSCROLL|LBS_NOTIFY|LBS_NOINTEGRALHEIGHT,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Creates a General ListBox
HWND NewListBox(HWND Parent,int Left,int Top,int Width,int Height,HFONT MainFont)
{
    HWND SURFACE = CreateWindowEx(0,"LISTBOX","",WS_CHILD|WS_VISIBLE|WS_BORDER|WS_VSCROLL|LBS_NOTIFY|LBS_NOINTEGRALHEIGHT,Left,Top,Width,Height,Parent,NULL,hInstance,NULL);
    SendMessage(SURFACE,WM_SETFONT,(WPARAM)MainFont,1);
    return SURFACE;
}
//Destroys a Window an Clear its handle
int EndWindow(HWND*Hwnd)
{
    if((*Hwnd)==0)
        return 0;
    DestroyWindow(*Hwnd);
    for(int i=0;i<dbCount;i++)
    {
        if(dbHwnds[i]==(*Hwnd))
        {
            for(int j=i;j<dbCount-1;j++)
                dbHwnds[j]=dbHwnds[j+1];
            dbCount--;
        }
    }
    (*Hwnd)=NULL;
    return 0;
}
//Show a Window and disables its parent allowing a Modal Behavior
void ShowModal(HWND WINDOW)
{
    HWND PARENT=GetParent(WINDOW);
    EnableWindow(PARENT,FALSE);
    ShowWindow(WINDOW,TRUE);
}
//Hides a Window and enables its parent allowing a Modal Behavior
void HideModal(HWND WINDOW)
{
    HWND PARENT=GetParent(WINDOW);
    EnableWindow(PARENT,TRUE);
    ShowWindow(WINDOW,FALSE);
}
//Show a Window and disables its parent allowing a Modal Behavior
void MyShowWindow(HWND WINDOW,HWND PARENT)
{
    ShowWindow(WINDOW,TRUE);
    ShowWindow(PARENT,FALSE);
}
//Hides a Window and enables its parent allowing a Modal Behavior
void MyHideWindow(HWND WINDOW,HWND PARENT)
{
    ShowWindow(PARENT,TRUE);
    ShowWindow(WINDOW,FALSE);
}
//Modified IsDialogMessage that checks for all popup windows
BOOL MyIsDialogMessage(LPMSG pMSG)
{
    for(int i=0;i<dbCount;i++)
        if(IsDialogMessage(dbHwnds[i],pMSG))
            return TRUE;
    return FALSE;
}
//Save File DialogBox
char*SaveFileDialog(HWND OWNER,char*DialogTitle,char*FileName,char*FilterTitle,char*FilterValue)
{
    OPENFILENAME SV;
    char FILTER[MAX_PATH];
    char FILENAME[MAX_PATH];
    int lFilterTitle=strlen(FilterTitle)+1;
    int lFilterValue=strlen(FilterValue)+1;
    strcpy(FILENAME,FileName);
    strcpy(FILTER,FilterTitle);
    strcpy(FILTER+lFilterTitle,FilterValue);
    FILTER[lFilterTitle+lFilterValue]='\0';
    ZeroMemory(&SV,sizeof(SV));
    SV.lStructSize=sizeof(OPENFILENAME);
    SV.hwndOwner=OWNER;
    SV.hInstance=NULL;
    SV.lpstrFilter=FILTER;
    SV.lpstrCustomFilter=NULL;
    SV.nMaxCustFilter=0;
    SV.nFilterIndex=0;
    SV.lpstrFile=FILENAME;
    SV.nMaxFile=MAX_PATH;
    SV.nFileOffset=0;
    SV.lpstrFileTitle=NULL;
    SV.nMaxFileTitle=0;
    SV.lpstrInitialDir=NULL;
    SV.lpstrTitle=DialogTitle;
    SV.Flags=OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST;
    SV.nFileExtension=0;
    SV.lpstrDefExt="xls";
    SV.lCustData=0;
    SV.lpfnHook=NULL;
    SV.lpTemplateName=NULL;
    if(GetSaveFileName(&SV))
        return strdup(SV.lpstrFile);
    return NULL;
}

void CmdOpenFile(char*FilePath)
{
    ShellExecute(0,"OPEN",FilePath,NULL,NULL,SW_SHOW);
}

void ShowWindow(HWND hwnd)
{
    ShowWindow(hwnd,TRUE);
}

void HideWindow(HWND hwnd)
{
    ShowWindow(hwnd,FALSE);
}

//Image File Select
char*ImageSelectDialog(HWND OWNER,char*DialogTitle,char*FileName,char*FilterTitle,char*FilterValue)
{
    OPENFILENAME OP;
    char FILTER[MAX_PATH];
    char FILENAME[MAX_PATH];
    int lFilterTitle=strlen(FilterTitle)+1;
    int lFilterValue=strlen(FilterValue)+1;
    strcpy(FILENAME,FileName);
    strcpy(FILTER,FilterTitle);
    strcpy(FILTER+lFilterTitle,FilterValue);
    FILTER[lFilterTitle+lFilterValue]='\0';
    ZeroMemory(&OP,sizeof(OP));
    OP.lStructSize=sizeof(OPENFILENAME);
    OP.hwndOwner=OWNER;
    OP.hInstance=NULL;
    OP.lpstrFilter=FILTER;
    OP.lpstrCustomFilter=NULL;
    OP.nMaxCustFilter=0;
    OP.nFilterIndex=0;
    OP.lpstrFile=FILENAME;
    OP.nMaxFile=MAX_PATH;
    OP.nFileOffset=0;
    OP.lpstrFileTitle=NULL;
    OP.nMaxFileTitle=0;
    OP.lpstrInitialDir=NULL;
    OP.lpstrTitle=DialogTitle;
    OP.Flags=OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;
    OP.nFileExtension=0;
    OP.lpstrDefExt="";
    OP.lCustData=0;
    OP.lpfnHook=NULL;
    OP.lpTemplateName=NULL;
    if(GetOpenFileName(&OP))
        return strdup(OP.lpstrFile);
    return NULL;
}
