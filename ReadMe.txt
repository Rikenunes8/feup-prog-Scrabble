Estes dois programas foram desenvolvidos pelos estudantes da turma 1MIEIC07:
	- Henrique Nunes (up201906852) - 50% de participa��o
	- Raquel Sousa   (up201906957) - 50% de participa��o


- Programa "Board Builder"

Este programa, tem como objetivo a cria��o de tabuleiros para o jogo Scrabble, representados atrav�s de uma matriz 2D segundo
as diretivas presentes no "PROGRAM SPECIFICATION", assim como algumas restri��es e caracter�ticas por n�s implementadas, nomeadamente:
	- Para come�ar a construir o tabuleiro, o utilizador tem de come�ar por introduzir o nome do ficheiro onde pretende cri�-lo (sem a extens�o .txt);
	- O fim da coloca��o de palavras no tabuleiro deve ser sinalizado pelo utilizador atrav�s da introdu��o de CTRL+Z quando � pedida a posi��o da 
	  palavra, tal como � dito no in�cio do programa;
	- Decidimos que o tabuleiro n�o deveria ter dimens�es n�o pertencentes ao intervalo [4,20] (a restri��o a n�vel do limite superior encontra-se 
	  especificada no "PROGRAM SPECIFICATION");
	- Ao ser constru�do um tabuleiro com menos de 14 letras (n�mero m�nimo de letras para iniciar um jogo de Scrabble Junior com dois jogadores) � dado
	  um aviso de que este � inutiliz�vel; 
	- Consideramos que o programa deveria passar automaticamente as coordenadas da posi��o da palavra (quando v�lidas, ou seja, pertencentes ao 
	  conjunto de letras que surgem as margens do tabuleiro) para o modo normalizado (primeira letra mai�scula e a seguinte min�scula), assim como a
	  orienta��o automaticamente para letra mai�scula (quando v�lida), de forma a minimizar erros de escrita no ficheiro "BOARD.TXT", e a facilitar 
	  a inser��o da posi��o das palavras pelo utilizador;
	- N�o permitimos a inser��o no tabuleiro de uma palavra que consista em apenas uma letra;
	- Para que o programa funcione corretamente, deve ter o ficheiro "WORDS.TXT", no mesmo diret�rio onde se encontra o c�digo do programa;
	- N�o permitimos a coloca��o, no tabuleiro, de palavras adjacentes, permitindo na mesma a sua interse��o quando � o caso e esta seja poss�vel, de 
	  forma a n�o se formarem palavras n�o introduzidas pelo utilizador;
	- Tamb�m n�o permitimos a inser��o da mesma palavra mais do que uma vez no tabuleiro;
	- N�o permitimos a escrita de palavras em cima de outras, mesmo que as letras que as contituem coincidam (por exemplo: se escrever "BANANA" no 
	  tabuleiro, n�o poder� escrever "ANA" em cima das �ltimas 3 letras da palavra), de modo a que todas as palavras inseridas apare�am como 
	  claramente distintas no tabuleiro;
	- Permitimos ao utilizador a visualiza��o do tabuleiro tanto no �nicio, como � medida que vai inserindo as palavras, facilitando o seu posicionamento,
	  pelo que n�o vimos a necessidade de adicionar uma vista 2D da matriz ao fim do ficheiro "BOARD.TXT";

    NOTA: Ter em aten��o que a forma��o de um determinado tabuleiro pode ser influenciada pela ordem de inser��o das palavras, por exemplo: S I T			
								Aa H SIT			Aa H SIT					E P I C		
								Ac V TEACH  --> poss�vel	Bc H EPIC  --> imposs�vel			A
								Bc H EPIC			Ac V TEACH				  	C
		      															  	H	

A n�vel do estado de desenvolvimento, demos grande import�ncia �s valida��es, tanto quanto � palavra em si, como ao seu posicionamento e � sua poss�vel interse��o.
Consideramos ainda que todos os objetivos relacionados com este programa foram cumpridos.



- Programa "Scrabble Junior"

Este programa, tem como objetivo jogar o "Scrabble Junior" a partir da utiliza��o de um tabuleiro criado pelo programa "Board Builder", tendo por base as 
diretivas presentes em "PROGRAM SPECIFICATION", ao que foram acrescentadas algumas melhorias:
	- O programa � constituido por tr�s classes ("board", "pool" e "player");
	- O utilizador tem de escolher o tabulerio (ficheiro.txt) que pretende utilizar, introduzindo o "path" que o leva at� ele;
	- O jogador pode escolher o seu nome (entre 1 e 20 caract�res), assim como uma cor representativa (cores listadas no momento da sua escolha);
	- Foi implementado um modo de jogo que consiste apenas na escolha das coordenadas do tabulerio onde o jogador pretende colocar a sua letra, para 
	  assim evitar a escolha �bvia da pe�a que pretende colocar. Para isso, cada jogador, na sua vez ("Nome do joagor":) deve introduzir as coordenadas,
	  no formato letra mai�scula seguida de letra min�scula (ex. Aa), do local onde pretende colocar a letra. Posteriormente, se a jogada for v�lida a,
	  a pe�a ser� colocada no tabulerio, caso contr�rio ser� pedido ao jogador para efetuar uma nova jogada;
	- O programa deteta quando n�o � poss�vel o jogador efetuar a sua jogada, direcionando-a para uma nova situa��o, de acordo com as regras do jogo 
	  (passar, trocar letras, finalizar a jogada e recolher letras da "pool" ou finalizaar o jogo);
	- O procedimento de recolha de uma pe�a da "pool" no final de cada jogada � feita de forma aleat�ria e automatizada;
	- Quando � necessario o jogador trocar de letras, este deve escolher uma das letras que possui na sua m�o;
	- Qualquer jogador pode decidir acabar o jogo prematuramente introduzindo crtl+z, no entanto a pontua��o do desistente � reposta a 0;
	- No final do jogo (tanto de forma regular como por desist�ncia), � anunciado o vencedor, assim como uma tabela ordenada com os jogadores e
	  respetivas pontua��es;
Desta forma, consideramos que todos os objetivos relacionados com este programa foram cumpridos.