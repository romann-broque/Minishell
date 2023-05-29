import os
from utils import EXECUTABLES, FILES_OUT, UNWRITABLE
import sys


def pytest_sessionstart(session):
    assert os.system("make -s") == 0
    sys.path.append(os.path.join(os.getcwd(), EXECUTABLES))
    os.chmod(UNWRITABLE, 0o444)
    try:
        os.mkdir(FILES_OUT)
    except FileExistsError:
        pass
