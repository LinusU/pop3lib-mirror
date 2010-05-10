/*
Copyright (C) 2009 Populous Mana Source Development Team

This file is part of poplib.

poplib is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

poplib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with poplib. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _H_DMKP32_WINDOWS32_MSGBOX_HEADER_MAIN__
#define _H_DMKP32_WINDOWS32_MSGBOX_HEADER_MAIN__

#include "msgBoxEnums.h"

//define _DMKP32_WINDOWS32_ALLOW_UNSAFE_OPTIONS_ to allow the other messagebox options which can clash with the other things without care!

//To simplify things, I have decided to not include the complicated shit that noone ever fucking needs!

namespace poplib {

/* FIXME not crossplatform code
DialogResult MsgBox(HWND hOwner, char* strMessage);
DialogResult MsgBox(HWND hOwner, char* strMessage, char* strTitle);
DialogResult MsgBox(HWND hOwner, char* strMessage, char* strTitle, MsgBoxButtons btns);
DialogResult MsgBox(HWND hOwner, char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons);
//This is like the "core" message box function, as it has the most options and can therefore be called by most of its overloads
DialogResult CoreMsgBox(HWND hOwner, char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxDefButtons defBtns);
//The next function has one more argument which I do not wish to have in by default
DialogResult MsgBox(HWND hOwner, char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxDefButtons defBtns, MsgBoxOptions options);

//Displays a message box with no owner in modal mode - TASKMODAL
DialogResult MsgBox(char* strMessage);
DialogResult MsgBox(char* strMessage, char* strTitle);
DialogResult MsgBox(char* strMessage, char* strTitle, MsgBoxButtons btns);
DialogResult MsgBox(char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons);
DialogResult MsgBox(char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxDefButtons defBtns);
DialogResult MsgBox(char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxDefButtons defBtns, MsgBoxOptions options);


//Displays a message box with no owner in non-modal mode
//DialogResult NonModalMsgBox(char* strMessage);
//DialogResult NonModalMsgBox(char* strMessage, char* strTitle);
//DialogResult NonModalMsgBox(char* strMessage, char* strTitle, MsgBoxButtons btns);
//DialogResult NonModalMsgBox(char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons);
//DialogResult NonModalMsgBox(char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxDefButtons defBtns);
//DialogResult NonModalMsgBox(char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxDefButtons defBtns, MsgBoxOptions options);

#pragma region fucked
//the following messageboxes have a default title of ""
//DialogResult MessageBox(HWND hOwner, char* strMessage, MsgBoxButtons btns);
//DialogResult MessageBox(HWND hOwner, char* strMessage, MsgBoxButtons btns, MsgBoxIcons icons);
//DialogResult MessageBox(HWND hOwner, char* strMessage, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxOptions options);

//DialogResult MessageBox(char* strMessage, MsgBoxButtons btns, );
//DialogResult MessageBox(char* strMessage, MsgBoxButtons btns, MsgBoxIcons icons);
//DialogResult MessageBox(char* strMessage, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxOptions options);

//Displays a message box with no owner in modal mode - TASKMODAL
//DialogResult ModalMsgBox(char* strMessage, MsgBoxButtons btns);
//DialogResult ModalMsgBox(char* strMessage, MsgBoxButtons btns, MsgBoxIcons icons);
//DialogResult ModalMsgBox(char* strMessage, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxOptions options);
//Core message box function
#pragma endregion

//Displays a message box with no owner in non-modal mode
//DialogResult NonModalMsgBox(char* strMessage);
//DialogResult NonModalMsgBox(char* strMessage, char* strTitle);
//DialogResult NonModalMsgBox(char* strMessage, char* strTitle, MsgBoxButtons btns);
//DialogResult NonModalMsgBox(char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons);
//DialogResult NonModalMsgBox(char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxDefButtons defBtns);
//DialogResult NonModalMsgBox(char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxDefButtons defBtns, MsgBoxOptions options);
*/

} // namespace util

#endif /* _H_DMKP32_WINDOWS32_MSGBOX_HEADER_MAIN__ */
