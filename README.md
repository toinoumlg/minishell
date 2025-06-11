# MINISHELL

A simple shell implementation written in C, inspired by bash. This project recreates basic shell functionality including command parsing, tokenization, piping, and redirection.

## 📋 Table of Contents
- [Features](#features)
- [Building](#building)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
- [Debugging Tools](#debugging-tools)
- [To Do List](#to-do-list)

## ✨ Features

### ✅ Currently Implemented
- **Interactive prompt**: `minishell >>` display
- **Exit command**: Clean exit with `exit`
- **Advanced tokenizer**: Converts input into structured tokens with proper types
- **Quote handling**: Support for single `'` and double `"` quotes (parsing only)
- **Operator recognition**: `|`, `<`, `>`, `<<`, `>>`
- **Word extraction**: Proper word boundary detection
- **Pipeline validation**: Syntax checking for pipes and redirections
- **Metacharacter handling**: Space, tab, newline, operators
- **Command structure building**: Converts tokens to executable command structures
- **Memory management**: Comprehensive cleanup functions

### 🚧 Parsing Features (Structure Ready)
- **Input redirection parsing**: `<` syntax recognition
- **Output redirection parsing**: `>` syntax recognition  
- **Append mode parsing**: `>>` syntax recognition
- **Here document parsing**: `<<` syntax recognition
- **Command chaining parsing**: `|` pipeline structure
- **File structure creation**: Ready for validation and execution

## 🔨 Building

### Installation
```bash
# Clone the repository
git clone git@github.com:toinoumlg/minishell.git
cd minishell

# Build the project
make

# Run the shell
./minishell
```

### Make Targets
```bash
make          # Build the project
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild everything
make valgrind # Run with valgrind for memory checking
```

## 🚀 Usage

Currently, the shell can parse and validate complex command structures but execution is not yet implemented.

### What Works Now
```bash
# Basic parsing
minishell >> ls -la
# → Correctly tokenized and structured

# Pipe parsing
minishell >> ls | grep txt
# → Pipeline structure created

# Redirection parsing  
minishell >> cat < input.txt > output.txt
# → Input/output files identified

# Quote parsing
minishell >> echo "hello world" 'literal string'
# → Quotes properly handled

# Exit
minishell >> exit
# → Clean shutdown
```

## 🔧 Implementation Details

### Data Structures

#### Token Structure
```c
typedef enum s_enum_token
{
    word,
    is_pipe,
    input,
    output,
    here_doc,
    append_file,
    double_quote,
    simple_quote
} t_enum_token;

typedef struct s_token {
    char         *string;    // Token content
    t_enum_token type;       // Token type
    struct s_token *next;    // Linked list pointer
} t_token;
```

#### File Structure
```c
typedef struct s_file
{
    char    *path;      // Path to file
    int     fd;         // File descriptor (when opened)
    int     exist;      // access(F_OK) result
    int     read;       // access(R_OK) result  
    int     write;      // access(W_OK) result
    int     exec;       // access(X_OK) result
} t_file;
```

#### Command Structure
```c
typedef struct s_cmd
{
    t_file      *program;       // Program file (not yet implemented)
    char        **args;         // Command arguments array
    t_file      *infile;        // Input redirection file
    t_file      *outfile;       // Output redirection file
    int         here_doc;       // Here document flag
    int         append_file;    // Append mode flag
    struct s_cmd *next;         // Next command in pipeline
} t_cmd;
```

### Parsing Pipeline

1. **Tokenization** ([`token.c`](source/token.c))
   - ✅ Input string → Token list
   - ✅ Handles quotes, operators, words
   - ✅ Validates basic syntax
```c
int	get_tokens_list(char *read_line, t_token **tokens)
{
	memset(tokens, 0, sizeof(t_token *));
	// parse all string sent from read_line() in main
	while (*read_line)
	{
		// every if / else if check for the characther on read_line
		// add the proper token with the enum thats fits the right token
		// return 1 if an allocation fails
		if (is_quote(*read_line) && extract_quoted_string(&read_line,
				*read_line, tokens))
			return (1);
		else if (is_operator(*read_line) && add_operator_token(&read_line,
				tokens))
			return (1);
		else if (*read_line == ' ')
			read_line++;
		else if (pick_word(&read_line, tokens))
			return (1);
	}
	// parse all the tokens created and check for pipe and 
	// redirects syntax errors
	if (check_pipes(*tokens) || check_for_redirect_duplicate(*tokens))
		return (1);
	else
		return (0);
}
```
2. **Command Building** ([`commands.c`](source/commands.c))
   - ✅ Token list → Command structures
   - ✅ Extracts arguments and redirections
   - ✅ Handles pipeline separation
```c
int	add_new_command(t_token **tokens, t_minishell *minishell)
{
	t_cmd	*new;

	new = set_new_command();
	// parse all tokens until it encounter a pipe or a null to next cmd
	// add a file with its path in the cmd for either input or output
	// delete the token with the redirect operator and the next one
	if (pick_redirects(new, tokens))
		return (1);
	// parse all tokens and join them in an array of string
	// delete all the tokens until encounter a pipe or a null to next cmds
	new->args = set_args(tokens);
	if (!new->args)
		return (1);
	// free the pipe token if existing
	free_pipe(tokens);
	// adds the newly creadted cmd to the end of the cmd list
	append_new_command(&minishell->cmds, new);
	return (0);
}

int	set_commands(t_token **tokens, t_minishell *minishell)
{
	// until all tokens are deleted we add a new cmd
	// if there is any allocation error returns 1 else 0
	while (*tokens)
		if (add_new_command(tokens, minishell))
			return (1);
	return (0);
}
```
3. **Access Validation** ([`access.c`](source/access.c))
   - 🚧 Path resolution (placeholder)
   - 🚧 File permission checking (not implemented)
```c
void	try_access(t_cmd *cmds, char **env)
{
	// not set yes but will parse every file structure and every command
	// check if they exits and fills the permission
	(void)cmds;
	(void)env;
}
```
### Memory Management

- ✅ **Token cleanup**: [`free_token()`](source/parse_read_line.c)
- ✅ **Command cleanup**: [`free_cmds()`](source/free.c)  
- ✅ **Array cleanup**: [`free_array()`](source/free.c)
- ✅ **Comprehensive error handling**: Allocation failure management

### Current Limitations

- **No command execution**: Parsing only, no process creation
- **No file operations**: Structure ready but not validated/opened
- **No environment variables**: `$VAR` expansion not implemented
- **No built-ins**: Only `exit` works
- **No signal handling**: Ctrl+C, Ctrl+D, Ctrl+\ not handled

## 🔗 Pipes

**Current Status: Parsing Complete**
- ✅ Pipeline syntax validation
- ✅ Command separation at pipe boundaries
- ✅ Multi-command structure creation
- 🚧 Process communication (not implemented)

**Validation Rules:**
- ✅ No pipes at beginning or end
- ✅ No consecutive pipes  
- ✅ Proper command separation

## 🔄 Redirections

**Current Status: Parsing Complete**

| Operator | Parsing Status | Execution Status |
|----------|----------------|------------------|
| `<` | ✅ Complete | 🚧 Not implemented |
| `>` | ✅ Complete | 🚧 Not implemented |
| `>>` | ✅ Complete | 🚧 Not implemented |
| `<<` | ✅ Complete | 🚧 Not implemented |

**Features Implemented:**
- ✅ Syntax recognition and validation
- ✅ File path extraction
- ✅ Command structure integration
- 🚧 File validation (structure ready)
- 🚧 File operations (not implemented)

## 🐛 Debugging Tools
- **Print functions**: [`print_tokens()`](source/utils.c), [`print_commands()`](source/utils.c)
- **Valgrind support**: `make valgrind` target
- **Memory leak detection**: Comprehensive cleanup on errors

## 📋 To Do List 

### High Priority
- [ ] **Command execution**: Implement actual process creation and execution
- [ ] **File operations**: Implement file opening, validation, and I/O redirection
- [ ] **Pipeline execution**: Implement inter-process communication with pipes
- [ ] **Built-in commands**: `cd`, `export`, `unset`, `env`, `pwd`

### Medium Priority  
- [ ] **Environment variable expansion**: `$VAR` support
- [ ] **Signal handling**: Proper Ctrl+C, Ctrl+D, Ctrl+\ handling
- [ ] **Path resolution**: Command lookup in `$PATH`
- [ ] **Access validation**: Complete file permission checking

### Low Priority
- [ ] **Command history**: Using GNU readline library  
- [ ] **Error messages**: More descriptive error reporting
- [ ] **Advanced features**: Wildcards, background processes

---

**Current State**: Advanced parser with complete tokenization and command structure generation. Ready for execution implementation.