from string import ascii_lowercase
from utils import compare


def test_cd_pwd():
    def compare_cd_pwd(*args):
        compare(*args, "pwd", "export | grep PWD")

    compare_cd_pwd("cd")
    compare_cd_pwd("cd /")
    compare_cd_pwd("cd /tmp | grep ls")
    compare_cd_pwd("cd - | rev")
    compare_cd_pwd("cd non | ls")
    compare_cd_pwd("cd /usr/bin | ls")
    compare_cd_pwd("ls | cd /usr/bin")
    compare_cd_pwd("unset PWD", "unset OLDPWD")
    compare_cd_pwd("unset PWD", "unset OLDPWD", "cd /")
    compare_cd_pwd(f"cd {ascii_lowercase * 10}")


def test_export():
    compare("export A=B")
    compare("export A=B=42")
    compare("export C=D E=F")
    compare("export EQUAL===LOL", "export")
    compare("export Z=42 | wc")
    compare("export Z=42 | export")
    compare("export Z=42", "export")
    compare("export 42=answer")
    compare("export =answer")


def test_exit():
    compare("exit")
    compare("exit -9223372036854775808")
    compare("exit -42")
    compare("exit -1")
    compare("exit 0")
    compare("exit 1")
    compare("exit  2")
    compare("exit    +042")
    compare("exit 9223372036854775807")
    compare("exit -9223372036854775809")
    compare("exit 9223372036854775808")
    compare("exit nope42")
    compare("exit 42nope")
    compare("exit ''")
    compare("exit 42 42")
    compare("exit 42 what")
    compare("exit what 42")
    compare("exit what what")


def test_echo():
    compare("echo")
    compare("echo test")
    compare("echo a b")
    compare("echo a b c")
    compare("echo ")
    compare("echo ''")
    compare("echo  a")
    compare("echo a ")
    compare("echo a '' '' a")
    compare("echo a'' ''a")
    compare("echo -n")
    compare("echo -n test")
    compare("echo -nn test")
    compare("echo -n -nnnn test")
    compare("echo -n -n mdr -n test")
    compare("echo - test")
    compare("echo -non test")
    compare("echo -nn - -nn test")
