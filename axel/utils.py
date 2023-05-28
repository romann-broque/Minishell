from dataclasses import dataclass
import re
import subprocess

TASH = ["./minishell"]
BASH = ["bash", "--posix"]
EXECUTABLES = "axel/executables"
UNWRITABLE = "axel/files_in/unwritable"
FILES_OUT = "axel/files_out"
F1 = f"{FILES_OUT}/outfile1"
F2 = f"{FILES_OUT}/outfile2"
F3 = f"{FILES_OUT}/outfile3"


@dataclass
class Execution:
    returncode: int
    stdout: str
    stderr: str


def execute(shell, lines):
    p1 = subprocess.Popen(["echo", "\n".join(lines)], stdout=subprocess.PIPE)
    p2 = subprocess.Popen(
        shell, stdin=p1.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )
    stdout, stderr = [s or b"" for s in p2.communicate()]
    stdout = stdout.decode().strip()
    stdout = re.sub(r"(export )?_=.*\n?", "", stdout).strip()
    stderr = stderr.decode().strip()
    stderr = re.sub(r"bash: line \d+: ", "minishell: ", stderr)
    stderr = "\n".join(sorted(stderr.split("\n")))
    return Execution(p2.returncode, stdout, stderr)


def compare(*lines):
    tash_exec = execute(TASH, lines)
    bash_exec = execute(BASH, lines)
    assert tash_exec == bash_exec, lines


def check_redirections(files_out, *args):
    s = " ".join(files_out)
    compare(f"rm -f {s}", *args, f"cat {s}")
