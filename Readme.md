# feup-prog-Scrabble

Project for the Programming course @ FEUP - 2019/2020

The goal of this project was to develop an Scrabble command line game in C++ using Object Orienting.

**Grade:** 17.9


Estes dois programas foram desenvolvidos pelos estudantes da turma 1MIEIC07:
- Henrique Nunes (up201906852) - 60% de participação
- Raquel Sousa   (up201906957) - 40% de participação


## Board Builder

Este programa, tem como objetivo a criação de tabuleiros para o jogo Scrabble, representados através de uma matriz 2D segundo
as diretivas presentes no "PROGRAM SPECIFICATION", assim como algumas restrições e caracteríticas por nós implementadas, nomeadamente:

- Para começar a construir o tabuleiro, o utilizador tem de começar por introduzir o nome do ficheiro onde pretende criá-lo (sem a extensão .txt);
- O fim da colocação de palavras no tabuleiro deve ser sinalizado pelo utilizador através da introdução de CTRL+Z quando é pedida a posição da palavra, tal como é dito no início do programa;
- Decidimos que o tabuleiro não deveria ter dimensões não pertencentes ao intervalo [4,20] (a restrição a nível do limite superior encontra-se especificada no "PROGRAM SPECIFICATION");
- Ao ser construído um tabuleiro com menos de 14 letras (número mínimo de letras para iniciar um jogo de Scrabble Junior com dois jogadores) é dado um aviso de que este é inutilizável; 
- Consideramos que o programa deveria passar automaticamente as coordenadas da posição da palavra (quando válidas, ou seja, pertencentes ao conjunto de letras que surgem as margens do tabuleiro) para o modo normalizado (primeira letra maiúscula e a seguinte minúscula), assim como a orientação automaticamente para letra maiúscula (quando válida), de forma a minimizar erros de escrita no ficheiro "BOARD.TXT", e a facilitar a inserção da posição das palavras pelo utilizador;
- Não permitimos a inserção no tabuleiro de uma palavra que consista em apenas uma letra;
- Para que o programa funcione corretamente, deve ter o ficheiro "WORDS.TXT", no mesmo diretório onde se encontra o código do programa;
- Não permitimos a colocação, no tabuleiro, de palavras adjacentes, permitindo na mesma a sua interseção quando é o caso e esta seja possível, de forma a não se formarem palavras não introduzidas pelo utilizador;
- Também não permitimos a inserção da mesma palavra mais do que uma vez no tabuleiro;
- Não permitimos a escrita de palavras em cima de outras, mesmo que as letras que as contituem coincidam (por exemplo: se escrever "BANANA" no tabuleiro, não poderá escrever "ANA" em cima das últimas 3 letras da palavra), de modo a que todas as palavras inseridas apareçam como claramente distintas no tabuleiro;
- Permitimos ao utilizador a visualização do tabuleiro tanto no ínicio, como à medida que vai inserindo as palavras, facilitando o seu posicionamento, pelo que não vimos a necessidade de adicionar uma vista 2D da matriz ao fim do ficheiro "BOARD.TXT";

**NOTA**: Ter em atenção que a formação de um determinado tabuleiro pode ser influenciada pela ordem de inserção das palavras, por exemplo: 

```
    									    S I T
Aa H SIT			Aa H SIT					E P I C		
Ac V TEACH  --> possível	Bc H EPIC  --> impossível			A
Bc H EPIC			Ac V TEACH				  	C
		      								H	
```

A nível do estado de desenvolvimento, demos grande importância às validações, tanto quanto à palavra em si, como ao seu posicionamento e à sua possível interseção.
Consideramos ainda que todos os objetivos relacionados com este programa foram cumpridos.


## Scrabble Junior

Este programa, tem como objetivo jogar o "Scrabble Junior" a partir da utilização de um tabuleiro criado pelo programa "Board Builder", tendo por base as 
diretivas presentes em "PROGRAM SPECIFICATION", ao que foram acrescentadas algumas melhorias:
- O programa é constituido por três classes ("board", "pool" e "player");
- O utilizador tem de escolher o tabulerio (ficheiro.txt) que pretende utilizar, introduzindo o "path" que o leva até ele;
- O jogador pode escolher o seu nome (entre 1 e 20 caractéres), assim como uma cor representativa (cores listadas no momento da sua escolha);
- Foi implementado um modo de jogo que consiste apenas na escolha das coordenadas do tabulerio onde o jogador pretende colocar a sua letra, para assim evitar a escolha óbvia da peça que pretende colocar. Para isso, cada jogador, na sua vez ("Nome do joagor":) deve introduzir as coordenadas, no formato letra maiúscula seguida de letra minúscula (ex. Aa), do local onde pretende colocar a letra. Posteriormente, se a jogada for válida, a peça será colocada no tabulerio, caso contrário será pedido ao jogador para efetuar uma nova jogada;
- O programa deteta quando não é possível o jogador efetuar a sua jogada, direcionando-a para uma nova situação, de acordo com as regras do jogo (passar, trocar letras, finalizar a jogada e recolher letras da "pool" ou finalizaar o jogo);
- O procedimento de recolha de uma peça da "pool" no final de cada jogada é feita de forma aleatória e automatizada;
- Quando é necessario o jogador trocar de letras, este deve escolher uma das letras que possui na sua mão;
- Qualquer jogador pode decidir acabar o jogo prematuramente introduzindo crtl+z, no entanto a pontuação do desistente é reposta a 0;
- No final do jogo (tanto de forma regular como por desistência), é anunciado o vencedor, assim como uma tabela ordenada com os jogadores e respetivas pontuações;

Desta forma, consideramos que todos os objetivos relacionados com este programa foram cumpridos.
