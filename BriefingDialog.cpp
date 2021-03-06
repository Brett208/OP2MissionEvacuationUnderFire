/* The following code will allow showing a modal dialog during a new scenario's initialization.
   A resource script and resource.h are required that define the parameters of the modal dialog
   and add the briefing text as a resource to the DLL scenario.*/

#include "resource.h"
#include "odasl/odasl.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <richedit.h>

extern HINSTANCE hInst; //HINSTANCE needs to be accessed from the dllMain function.
LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


void ShowBriefing()
{
    // OP2 turns off the skinning before the game loads.
    // We have to re-enable it (otherwise the briefing box will look ugly).
    wplEnable();
    // Show the dialog box, using the shell window as the parent
	HWND shellWnd = FindWindow("Outpost2Shell", NULL);
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_MISSIONINFO), shellWnd, (DLGPROC)DialogProc, NULL);
    // Turn off the skinning again (probably not needed but a good idea to do it anyway)
    wplDisable();
}

LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HRSRC txtRes = NULL;
    HWND richEdit = NULL;
	switch(msg)
	{
		case WM_INITDIALOG:
            // Make the BG black in the rich edit box
            richEdit = GetDlgItem(hWnd, IDC_TEXTAREA);
            SendMessage(richEdit, EM_SETBKGNDCOLOR, 0, 0);

            // Find the text resource
            txtRes = FindResource(hInst, MAKEINTRESOURCE(IDR_MISSIONTEXT), "TEXT");
            if (txtRes)
            {
                // Load it
                HGLOBAL resHdl = LoadResource(hInst, txtRes);
                if (resHdl)
                {
                    // Lock it and set the text
                    char *briefing = (char*)LockResource(resHdl);
                    if (briefing)
                    {
                        SetDlgItemText(hWnd, IDC_TEXTAREA, briefing);
                        return TRUE;
                    }
                }
            }
            SetDlgItemText(hWnd, IDC_TEXTAREA, "Error: Mission text could not be loaded.");
            return TRUE;
        case WM_COMMAND:
            if (wParam == IDOK)
            {
                EndDialog(hWnd, IDOK);
                return TRUE;
            }
            return FALSE;
	}
	return FALSE;
}
