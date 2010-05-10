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

// #include <windows.h>"

//define _DMKP32_WINDOWS32_ALLOW_UNSAFE_OPTIONS_ to allow the other messagebox options which can clash with the other things without care!

//To simplify things, I have decided to not include the complicated shit that noone ever fucking needs!

#include "messageBox.h"
#include "dialogResult.h"

namespace poplib
{

/* FIXME not crossplatform code
//CoreMsgBoxFunction
DialogResult CoreMsgBox ( HWND hOwner, char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxDefButtons defBtns )
{
    if ( hOwner )
    {
        return ( DialogResult ) ( MessageBoxA ( hOwner, strMessage, strTitle, ( btns | icons | defBtns ) ) );
    }
    else
    {
        return ( DialogResult ) ( MessageBoxA ( hOwner, strMessage, strTitle, ( btns | icons | defBtns | MB_TASKMODAL ) ) );
    }

    return ( DialogResult ) 0;
}

DialogResult MsgBox ( HWND hOwner, char* strMessage )
{
    return CoreMsgBox ( hOwner, strMessage, "", MsgBoxButtons::OK, MsgBoxIcons::None, MsgBoxDefButtons::Default1 );
}

DialogResult MsgBox ( HWND hOwner, char* strMessage, char* strTitle )
{
    return CoreMsgBox ( hOwner, strMessage, strTitle, MsgBoxButtons::OK, MsgBoxIcons::None, MsgBoxDefButtons::Default1 );
}

DialogResult MsgBox ( HWND hOwner, char* strMessage, char* strTitle, MsgBoxButtons btns )
{
    return CoreMsgBox ( hOwner, strMessage, strTitle, btns, MsgBoxIcons::None, MsgBoxDefButtons::Default1 );
}

DialogResult MsgBox ( HWND hOwner, char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons )
{
    return CoreMsgBox ( hOwner, strMessage, strTitle, btns, icons, MsgBoxDefButtons::Default1 );
}

DialogResult MsgBox ( HWND hOwner, char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxDefButtons defBtns, MsgBoxOptions options )
{
    return ( DialogResult ) ( MessageBoxA ( hOwner, strMessage, strTitle, ( btns | icons | defBtns | options ) ) );
}



//Displays a message box with no owner in modal mode - TASKMODAL
DialogResult MsgBox ( char* strMessage )
{
    return CoreMsgBox ( 0, strMessage, "", MsgBoxButtons::OK, MsgBoxIcons::None, MsgBoxDefButtons::Default1 );
}

DialogResult MsgBox ( char* strMessage, char* strTitle )
{
    return CoreMsgBox ( 0, strMessage, strTitle, MsgBoxButtons::OK, MsgBoxIcons::None, MsgBoxDefButtons::Default1 );
}

DialogResult MsgBox ( char* strMessage, char* strTitle, MsgBoxButtons btns )
{
    return CoreMsgBox ( 0, strMessage, strTitle, btns, MsgBoxIcons::None, MsgBoxDefButtons::Default1 );
}

DialogResult MsgBox ( char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons )
{
    return CoreMsgBox ( 0, strMessage, strTitle, btns, icons, MsgBoxDefButtons::Default1 );
}

DialogResult MsgBox ( char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxDefButtons defBtns )
{
    return CoreMsgBox ( 0, strMessage, strTitle, btns, icons, defBtns );
}

DialogResult MsgBox ( char* strMessage, char* strTitle, MsgBoxButtons btns, MsgBoxIcons icons, MsgBoxDefButtons defBtns, MsgBoxOptions options )
{
    return ( DialogResult ) ( MessageBoxA ( 0, strMessage, strTitle, ( btns | icons | defBtns | options | MB_TASKMODAL ) ) );
}
*/

} // namespace util
