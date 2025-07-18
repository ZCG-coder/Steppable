#####################################################################################################
#  Copyright (c) 2023-2025 NWSOFT                                                                   #
#                                                                                                   #
#  Permission is hereby granted, free of charge, to any person obtaining a copy                     #
#  of this software and associated documentation files (the "Software"), to deal                    #
#  in the Software without restriction, including without limitation the rights                     #
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                        #
#  copies of the Software, and to permit persons to whom the Software is                            #
#  furnished to do so, subject to the following conditions:                                         #
#                                                                                                   #
#  The above copyright notice and this permission notice shall be included in all                   #
#  copies or substantial portions of the Software.                                                  #
#                                                                                                   #
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                       #
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                         #
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                      #
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                           #
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                    #
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                    #
#  SOFTWARE.                                                                                        #
#####################################################################################################

import platform
import tkinter as tk
from tkinter import ttk


class MenuButton(ttk.Label):
    def __init__(self, master, name: str):
        super().__init__(master, takefocus=True, padding=(5, 0))
        self["text"] = name
        self.bind("<Button-1>", self._open_popup)
        self._menu = tk.Menu(self)
        self._menu.bind("<FocusOut>", lambda _: self._menu.grab_release())

    def _open_popup(self, _):
        try:
            self._menu.tk_popup(
                self.winfo_rootx(), self.winfo_rooty() + self.winfo_height()
            )
        finally:
            self._menu.grab_release()

    def add_command(self, *args, **kwargs):
        self._menu.add_command(*args, **kwargs)

    def add_checkbutton(self, *args, **kwargs):
        self._menu.add_checkbutton(*args, **kwargs)

    def add_cascade(self, *args, **kwargs):
        self._menu.add_cascade(*args, **kwargs)

    def add_radiobutton(self, *args, **kwargs):
        self._menu.add_radiobutton(*args, **kwargs)

    def add_separator(self, *args, **kwargs):
        self._menu.add_separator(*args, **kwargs)

    def pack(self, *args, **kwargs):
        kwargs["side"] = tk.LEFT
        kwargs["ipadx"] = 10
        kwargs["ipady"] = 2
        super().pack(*args, **kwargs)


class Menu(ttk.Frame):
    def __init__(self, master):
        super().__init__(master)


class _MainWindow(tk.Tk):
    def __init__(
        self,
        screenName: str | None = None,
        baseName: str | None = None,
        className: str = "Tk",
        useTk: bool = True,
        sync: bool = False,
        use: str | None = None,
    ) -> None:
        super().__init__(screenName, baseName, className, useTk, sync, use)
        self.title("Steppable")

        # Fix the title on macOS
        if platform.system() == "Darwin":
            _menu = tk.Menu()
            _python_menu = tk.Menu(_menu, name="apple")
            _menu.add_cascade(menu=_python_menu)
            self["menu"] = _menu
            _python_menu.destroy()

        menu_frame = Menu(self)
        menu = MenuButton(menu_frame, name="FILE")
        # Add options to the menu
        menu.add_command(label="Option 1")
        menu.add_command(label="Option 2")
        menu.pack()
        menu = MenuButton(menu_frame, name="FILE")
        # Add options to the menu
        menu.add_command(label="Option 1")
        menu.add_command(label="Option 2")
        menu.pack()

        menu_frame.pack(anchor=tk.W)


if __name__ == "__main__":
    win = _MainWindow()
    win.mainloop()
