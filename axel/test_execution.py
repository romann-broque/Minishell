from utils import (
    EXECUTABLES,
    F1,
    F2,
    F3,
    UNWRITABLE,
    check_redirections,
    compare,
)


def test_fail_parsing():
    compare("echo lol |||")
    compare("| what")
    compare("echo lol >")


def test_absolute_path():
    compare("/usr/bin/ls")
    compare("/usr/bin/ls | /usr/bin/rev")
    compare("/usr/bin/ls | /usr/bin/rev | /usr/bin/rev")
    compare("/usr/bin/ls | /usr/bin/wc | /usr/bin/rev")
    compare("/usr/bin/ls | /usr/bin/wc | /usr/bin/rev")
    compare("/usr/bin/ls | /usr/bin/rev | /usr/bin/tac")
    compare("/usr/bin/ls | /usr/bin/rev | /usr/bin/tac | /usr/bin/rev | /usr/bin/tac")


def test_relative_path():
    compare(f"./{EXECUTABLES}/shout Wesh")
    compare(f"./{EXECUTABLES}/shout Wesh la famille.")


def test_path():
    compare("ls")
    compare("ls | grep s")
    compare("shout lol")


def test_fail_execution():
    compare("/usr/bin/jexistepas")
    compare("/bin/ls/fsafsa")
    compare("jexistepas")
    compare("./Makefile")
    compare("/bin/ls/dfs")
    compare("/bin")
    compare("includes")
    compare("./includes")
    compare("..")


def test_spaces():
    compare("ls            -la\t")
    compare("", " ", "")
    compare("echo lol '' mdr")


def test_random_bullshit():
    compare("abc | abc | abc | abc | abc | abc | abc | abc | abc | abc | abc")
    compare("exit | echo wololo")
    compare("ls" + " | rev | tac" * 50)
    compare("ls" + " | rev | tac" * 51)


def test_pipe():
    compare("ls -la | wc | wc")
    compare("eclo lol | echo lol")
    compare("echo lol | eclo lol")
    compare("echo yo | less")
    compare("ls | echo yes | grep s")
    compare("cat | cat | ls")
    compare("cat | cat | echo abc")
    compare("echo bonsoir | pwd | asdf | cat -e")


def test_dev_full():
    compare("cd - > /dev/full")
    compare("clear > /dev/full")
    compare("echo lol mdr > /dev/full")
    compare("env > /dev/full")
    compare("exit > /dev/full")
    compare("export > /dev/full")
    compare("pwd > /dev/full")
    compare("which ls > /dev/full")
    compare("ls > /dev/full")


def test_variables():
    compare("export HAHA=0123456789", "export HAHA=$HAHA$HAHA", "echo $HAHA")
    compare("echo $", "echo $?", "echo $,lol")
    compare("$")
    compare("echo $")
    compare('$"USER"')
    compare('''""$"US"""ER""''')
    compare('echo $"JEXISTEPAS"')
    compare("echo $JEXISTEPAS")
    compare("export CMD='ls -l'", "echo $CMD")
    compare("export CMD='ls -l'", "$CMD")
    compare('export a="ho bonjour"', "ec$a")
    compare('export a="ho bonjour > outfile"', "ec$a")


def test_unexpected_token():
    compare(">")
    compare("echo >")
    compare("| ls")
    compare("echo lol > > >")
    compare("echo |||")
    compare("| w ||")


def test_yes():
    compare("yes | wc-l")
    compare("yes | ls")
    compare("yes | ls | wc-l")
    compare("yes | ls | wc -l")
    compare("yes | head -n 10")


def test_redirection_file():
    compare(f"echo lol > {UNWRITABLE}")
    compare(f"shout lol > /tmp/garbage < fsfasfasfa")
    compare(f"echo lol > /")
    compare(f"echo lol < inexistant")
    compare(f"echo lol < /")
    compare(f"echo lol < inexistant > {UNWRITABLE}")
    compare("echo lol > /", "echo mdr")
    check_redirections([F1], f"echo lol > {UNWRITABLE} > {F1}")
    check_redirections(
        [F1, F2], f"echo f1 > {F1} | echo unwritable {UNWRITABLE} | echo f2 > {F2}"
    )


def test_redirections_in():
    compare(f"tac < Makefile")
    compare(f"rev < Makefile < srcs/main.c")


def test_redirections_out_single():
    check_redirections([F1], f"> {F1}")
    check_redirections([F1, F2, F3], f"echo mdr > {F1} >> {F2} > {F3}")
    check_redirections([F1], f"echo mdr > {F1} | rev")
    check_redirections([F1], f"ls | echo mdr > {F1}")


def test_redirections_out_multiple():
    check_redirections([F1, F2], f"> {F1} > {F2}")
    check_redirections([F1, F2], f"echo mdr > {F1} > {F2}")
    check_redirections([F1, F2], f"ls | echo mdr > {F1} > {F2}")
    check_redirections([F1, F2, F3], f"echo toto > {F1} > {F2} > '' > {F3}")


def test_append():
    check_redirections([F1], f"echo mdr >> {F1}", f"ls >> {F1}")


def test_redirections_both():
    check_redirections([F1], f"sort <Makefile >{F1}")
    check_redirections([F1, F2], f"sort <Makefile <srcs/main.c >{F1} > {F2}")
    check_redirections([F1], f"sort <Makefile >{F1}", f"sort <{F1} >{F1}")
