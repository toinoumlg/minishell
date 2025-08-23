A faire:
Signaux 

A refacto:
- pwd : si on est dans un dossier supp et que getcwd() return NULL
- cd : si on supprime le dossier parent et qu'on essaie de faire cd ..
	(ex: mkdir -p a/b
	cd a/b
	pwd == "../a/b"
	rm -rf ../../a
	cd .. == "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory"
	) et apres le pwd est a/b/.. (tant que cd .. retourne une erreur sur le parent directory on rajoute .. a la fin du pwd)
- norme
- Sortir et free correctement le parsing
- export / unset : faire fonctionner avec les variables d'environnement/ refedefinir 
et expend si on utilise des variables d'env
- envp : _ / oldpwd / pwd
- si pas minishell lance avec "env -i" (sans environnement) ?
