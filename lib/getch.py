import sys


class _Getch:
    """Gets a single character from standard input.  Does not echo to the
    screen."""

    def __init__(self):
        if not hasattr(sys.stdin, "fileno"):
            self.impl = input
            return
        try:
            self.impl = _GetchWindows()
        except ImportError:
            self.impl = _GetchUnix()

    def __call__(self):
        return self.impl()


class _GetchUnix:
    def __init__(self):
        import tty  # pyright: ignore

    def __call__(self) -> str:
        import termios
        import tty

        fd = sys.stdin.fileno()
        error = False
        try:
            old_settings = termios.tcgetattr(fd)
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
            error = False
        except termios.error:
            ch = input()
            error = True
        finally:
            if not error:
                termios.tcsetattr(
                    fd, termios.TCSADRAIN, old_settings  # pyright: ignore
                )
        return ch


class _GetchWindows:
    def __init__(self):
        import msvcrt  # pyright: ignore

    def __call__(self) -> str:
        import msvcrt

        return msvcrt.getch()  # pyright: ignore


getch = _Getch()
