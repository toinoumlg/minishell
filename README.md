A faire:
Signaux 

A refacto:
- norme
- Sortir et free correctement le parsing
- envp : _
- si minishell lance avec "env -i" (sans environnement) ?
- si pas de = dans le export export quand meme mais ne pas afficher en utilisant la cmd env
- ./minishell | ./minish (istty)
- exit a refacto un peu pareil cd
- quand path unset exit au bout de 2 prompt ?
- quand pipe toujours fork (avant le while minishell.cmds juste check si cmds.next existe et soit envoyer dans un exec avec fork ou envoyer un exec (surtout surtout sur les builts ins))