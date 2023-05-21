# 42sh

```text
binary name : 42sh
repository name : PSU_42sh_$ACADEMICYEAR
repository rights : ramassage-tek
language : C
compilation : via Makefile, including re,clean and fclean rules
```

You must write a Unix SHELL.
The project consists of two sections:

- a mandatory section, which MUST be completed: display a prompt, parse and execute some commands (see below),
- an optional section, which will only be evaluated if the mandatory section is fully functional.

**Authorized functions:** all functions included in the libC or the ncurses library.

## Mandatory section

This section must be COMPLETELY FUNCTIONAL. Otherwise your grade will be 0.
Concerning command parsing and execution, you must handle:

- spaces and tabs,
- $PATH and environment,
- errors and return value,
- redirections (‘<’, ‘>’, ‘<<’ and ‘>>’),
- pipes (‘|’),
- builtins: cd, echo, exit, setenv, unsetenv,
- separators: ‘;’, ‘&&’, ‘||’.

For instance, you should be able to execute the following command:

```text
∼/B-PSU-210> ./42sh
42sh> cd ; </etc/hosts od -c | grep xx | wc >> /tmp/z -l ; cd - && echo “OK”
```

## Optional section

You will get most of your points in this section.
You have free-rein and can do what you want. However, the entire project’s coherence will be taken into consideration.
Once more, **stability** will be much more important that quantity. Don’t include an option that will cause a problem for the rest of the program (especially for the mandatory section!).

```text
For the different commands and compatibility (syntax), the reference shell used will be
tcsh.
```

Here is a list of desired extras:

- inhibitors (‘\’),
- globbings (‘*’, ‘?’, ‘[’, ’]’),
- job control (‘&’, fg),
- backticks (“’),
- parentheses (‘(’ and ‘)’),
- variables (local and env),
- special variables (term, precmd, cwdcmd, cwd, ignoreof for instance),
- history (‘!’),
- aliases,
- line edition (multiline, dynamic rebinding, auto-completion dynamic),
- scripting (a bit harsh though).

```text
These extras are not bonuses! Bonuses will be evaluated only after you’ve correctly implemented every item on this list!
```

## Advice

```text
Form a solid group: make sure that you can really work together, really work together as
a group (together and through discussion)
```

```text
Split the work-load intelligently: what if a member of your team get sick? Can you finish
his part of the job, or is it a “black box” for you?
```

**Write unit tests:** if you write them as you add features, you will be more confident about the stability of your project as the code base grows.

**Never hesitate to delete or rewrite some old code:** unit tests are there to ensure your new code has the same behavior as the old one when you’re refactoring

**Git is your friend:** commit often! Do you know how to navigate in previous revisions? Do you know how to use branches?

## Final Mark

### Mark: 53 / 77 (68.83%)

- basic tests (4 / 4)
- path handling (4 / 5)
- setenv and unsetenv (2 / 2)
- builtin cd (3 / 3)
- line formatting (space and tabs) (8 / 8)
- error handling (6 / 6)
- separator (1 / 1)
- simple pipe (2 / 3)
- advanced pipe (3 / 6)
- redirections (5 / 5)
- advanced manipulations (3 / 3)
- && and || tests (1 / 3)
- globbing (0 / 1)
- var interpreter (1 / 3)
- inhibitor (0 / 2)
- magic quote (0 / 3)
- alias (2 / 4)
- scripting (0 / 1)
- foreach (1 / 1)
- which (2 / 2)
- where (2 / 2)
- if (0 / 2)
- repeat (0 / 1)
- parenthesis (0 / 1)
- history (1 / 2)
- job control (1 / 2)
- dynamic command line (1 / 2)
