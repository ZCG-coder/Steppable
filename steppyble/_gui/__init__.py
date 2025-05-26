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
