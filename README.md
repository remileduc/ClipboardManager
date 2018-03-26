ClipboardManager
================

`ClipboardManager` is a ligtweight tool used to analyze and modify the content of the system clipboard.

Usage
-----

### Analyze the content ###

First, you need to copy something. Then, in the ClipboardManager, click on the `Paste` button. The content of the clipboard is loaded in the application. You can 
see all the MIME types with their attached data. The MIME types are listed in the combobox. The content is automatically updated on MIME type change.

Note that you can edit the content and/or the MIME types and then copy the new version into the clipboard. See the next subsection for more information on 
changing the content of the clipboard.

### Modify the content ###

At any moment, you can clear the content of the application with the `clear` button. Note that it will not clear the clipboard.

You can start from a cleared state, or from a previous paste state. In any cases, you can add a MIME type by typing in the combobox. Then, you can attach data to 
this MIME type by typing in the text area.

When your editing is finished, click on the `Copy` button. This will copy all your data in the clipboard. You can now paste it in different applications to see 
how they behave (like Excel that totally ignores `text/csv` but takes `text/html` easily...).

Compile
-------

ClipboardManager is written in C++/Qt. The easiest way to compile it is to install the latest version of Qt (tested with Qt 5.10.1) and open the 
[ClipboardManager.pro](./source/ClipboardManager.pro) 
file in `QtCreator`.

Extra
-----

You can learn more about MIME types on [Wikipedia](https://en.wikipedia.org/wiki/Media_type).
