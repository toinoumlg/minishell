# minishell

A small interactive shell written in C (42 project style), with parsing, expansion, redirections, pipes, and a set of Bash-like builtins.

## Build and run

```bash
make
./minishell
```

This shell is interactive only (`isatty` check in `main`), so it does not run in non-interactive mode.

## What is implemented

- Tokenization + parsing into command structures
- Pipes: `|`
- Redirections: `<`, `>`, `>>`, `<<`
- Variable expansion (`$VAR`, `$?`)
- Builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## Tokenization choices (mostly based on Bash/man bash)

The lexer/parser behavior is intentionally close to Bash basics, with a limited subset.

### Token types used

From `include/minishell.h`, tokens are classified as:

- words and quoted strings (`word`, `simple_quote`, `double_quote`)
- separators/operators (`is_pipe`, `input`, `output`, `append_file`, `here_doc`)
- spaces (`space`)
- expansion-generated tokens (`word_expanded`, `space_expanded`)

### Operators recognized

Only these operators are valid:

- `|`
- `<`
- `>`
- `<<`
- `>>`

`||`, `&&`, and other Bash operators are not supported.

### Explicitly rejected characters

During token generation, `;` and `\\` are treated as syntax errors.

### Quotes

- Single quotes are tokenized as literal content.
- Double quotes are tokenized and later eligible for expansion.
- Unclosed quotes trigger syntax error.

### Expansion behavior

Expansion is run after tokenization (`expand()`), then adjacent token merge (`merge_adjacent()`).

- Expansion targets only `word` and `double_quote` tokens.
- `simple_quote` tokens are not expanded.
- `$?` expands to `last_status`.
- `$NAME` expands for alnum/underscore names.
- If a variable is missing (or has no value), it expands to empty.
- In plain `word` tokens, expanded text is split on spaces/tabs into multiple tokens.
- In `double_quote` tokens, no post-expansion split is done.
- The token immediately following `<<` (Heredoc limiter) is skipped by expander.

### Syntax checks

The parser reports `minishell: syntax error near unexpected token ...` for cases like:

- invalid operator sequences
- invalid or missing redirect target
- empty command segment around pipes
- unexpected end of line after required token

## Builtins (exact behavior from current code)

### Execution context

- `cd`, `export`, `unset`, `exit` run in **parent only when there is a single command**.
- In pipelines (or multi-command lines), builtins run in child process.
- So `ls | exit` exits only that child, not the main shell process.

### `echo`

File: `source/builtsin/child/echo.c`

- Supports repeated `-n` forms like `-n`, `-nnn`, `-nn`.
- Skips all leading valid `-n` arguments.
- Prints remaining args separated by one space.
- Prints trailing newline only if first argument is **not** a valid `-n` form.
- Return status: `0`.

### `pwd`

File: `source/builtsin/child/pwd.c`

- If first arg starts with `-`, prints `pwd: bad option: <2 chars>` on stderr.
- Uses `PWD` env value if present; otherwise falls back to `getcwd()`.
- Prints resolved path to stdout.
- `getcwd` failure prints `minishell: pwd` via `perror` and returns `1`.
- Otherwise returns `0`.

Note: the option error path does not stop execution; it still prints a directory and returns success.

### `env`

File: `source/builtsin/child/env.c`

- Prints only env entries that contain `=` (`contains_sign == 1`).
- One entry per line.
- Return status: `0`.

### `cd`

File: `source/builtsin/parent/cd.c`

- `cd` or `cd ~`: uses `HOME`.
- `cd -`: uses `OLDPWD`, prints destination when successful.
- `cd <path>`: `chdir(path)`.
- More than one argument: prints `minishell: cd: too many arguments` and returns `1`.
- On success, updates `PWD` and `OLDPWD` (`update_pwd`).

Error details:

- Missing `HOME`: prints `minishell: cd: HOME not set`, returns `1`.
- Missing `OLDPWD`: prints `minishell: cd: OLDPWD not set`, returns `1`.
- `chdir` failure uses `perror("chdir")`.

Note: in `cd_home`, `chdir` failure path returns `0` in current code.

### `export`

Files: `source/builtsin/parent/export.c`, `source/builtsin/parent/export_sorted.c`

- With no args: prints sorted export view from `envp_array`.
- With args: validates identifiers as:
  - first char: alpha or `_`
  - following chars until `=`: alnum or `_`
- Invalid identifier prints:
  - `minishell: export: \`<arg>\': not a valid identifier`
  - and sets return status to `1` (continues processing others).
- Existing var is updated only if `=` is present.
- Missing var is appended.
- Return status: `0` if all valid, else `1`.

No `+=` behavior is implemented.

### `unset`

File: `source/builtsin/parent/unset.c`

- For each argument, removes matching env node if it exists.
- If a name is missing, it is ignored.
- No identifier validation message.
- Return status: `0`.

### `exit`

File: `source/builtsin/parent/exit.c`

- `exit` with no args: exits with `last_status`.
- `exit <number>`: exits with `ft_atoi(arg) % 256`.
- Non-numeric first arg:
  - prints `exit` and `numeric argument required`
  - exits with code `2`.
- More than one arg (when first is numeric):
  - prints `exit` and `too many arguments`
  - does **not** exit, returns status `1`.

`exit` banner printing (`exit\n`) is conditioned to main-shell context (`single command`, first pipeline slot).

## Known differences vs Bash

- No `;`, `\\`, `&&`, `||` support.
- Limited expansion grammar.
- `pwd` option handling and some `cd` error returns differ from Bash conventions.
- `export` output formatting is custom and no `+=` support.

## Quick examples

```bash
echo hello world
echo -nnn no-newline
export TEST=42
env | grep TEST
cd -
pwd
```
