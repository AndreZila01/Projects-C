eu escolho as linhas e colunas
Os comandos acabam com \n

Mensagem de erro: "Intrução Inválida."
Não tem limite de utilizadores.

Registar utilizador (RJ {Nome de utilizador}):
    -> Se Registar com sucesso imprime, "Jogador registado com sucesso.";
    -> Se ao Registar um utilizador já existente terás de imprimir "Jogador existente.";
    
Remover utilizador (EJ {Nome}):
    -> Se Remover com sucesso imprime, "Jogador removido com sucesso.";
    -> Se o jogador não existir imprimir, "Jogador não existente";
    -> Se jogador está a participar num jogo em curso imprime, "Jogador participa no jogo em curso.";

Mostrar a lista de jogadores (LJ):
    -> Se existir dados salvos devo imprimir isto, "{Nome} {Jogos} {Vitórias}";
    -> Se não existir jogadores registados imprime, "Não existem jogadores registados."

Inicio do Jogo (IJ {NomeJogdor1} {NomeJogador2}"\n"{Comprimento} {Altura} {TamanhoSequência (o tamanho da sequência vencedora)}"\n"{TamanhoPeça} {TamanhoPeça} ... {TamanhoPeça}"):
    -> Se tudo correr bem, imprime "Jogo iniciado entre Nome e Nome."
    -> Se algum dos jogadores indicadaos não se encontr registado, imprime " Jogador não registado."
    -> Se o utilizador inserir dimensões fora do array, imprime "Dimensões de grelha inválidas.";
    -> Se um tamnho de sequência vencedora não respeitar as regras, imprime "Tamanho de sequência inválido.";
    -> Se alguma dimensão das peças especiais não respeitar as regras, imprime "Dimensões de peças especiais inválidas.";

Desistir ("D Nome[ Nome]"):
    -> Se tudo correr bem, imprime "Desistência com sucesso. Jogo terminado.";
    -> Se não existir nenhum jogo em curso, imprime "Não existe jogo em curso.";
    -> Se não houver jogadores a jogar, imprime "Jogador não participa no jogo em curso.";

Colocar Peça ("CP {NomeJogador} Posição[sentido]"):
    -> Se a peça colocada possibilita uma sequência vencedora, imprime "Sequência conseguida. Jogo terminado."
    -> Após a peça ser colocada, imprime "Peça colocada.";
    -> Se não existir jogo em curso, imprime "Não existe jogo em curso.";
    -> Se o jogador indicado não participa no jogo em curso, imprime "Jogador não participa no jogo em curso.";
    -> Se não for possível utilizar uma peça com o tamanho indicado (por inexistência ou indisponibilidade), imprime "Tamanho de peça não disponível.";
    -> Se a posição e sentido indicados não permitirem a colocação da peça, de acordo com as regras,, imprimir "Posição irregular";

Visualizar Result ("VR"):
    -> Se o jogador escrever "VR", imprime "{linha} {coluna} {Vazio/NomeJogador}";
    -> Se não existir jogo em curso mostra, imprime "Não existe jogo em curso.";

Gravar ("G"):
    -> Se o jogador gravar os dados com sucesso, imprime "Jogo gravado.";
    -> Se houver um erro na gravação, imprime "Ocorreu um erro na gravação.";

Ler ("L"):
    -> Se o jogador ler os dados com sucesso, imprime "Jogo carregado.";
    -> Se houver um erro na leitura de dados, imprime "Ocorreu um erro no carregamento.";

Iniciar jogo (IJ):
[
    Perguntar:
        SensitiveCase - Utilizadores com caps é diferente de sem caps

        Guardar dados em json - Tanto faz

        Só pode participar 2 pessoas no tabuleiro? - Sim~

        Como fazer lenght de um array com 2 dimensões? - Muito Dificil

        Criar variaveis publicas? - Não mexer

        O que é tamanhoPeça e TamanhoSequência?

        O que é Tamanho da Sequencência? -> 

        O que é "D Nome[ Nome]"? -> Se os dois jogadores quiserem sair


]

Inicio do Jogo:
1. Utilizador seleciona quantas linhasxcolunas tem de selecionar;
2.Utilizador escrever "IJ {NomeJogador1} {NomeJogador2}" "{Comprimento} {Altura} {TamanhoSequência (o tamanho da sequência vencedora)}":
    -> Se tudo correr bem escrever, imprimir: "Jogo iniciado entre {NomeJogador1} e {NomeJogador2}."
    -> Se existir um jogo em curso, imprimir "  Existe um jogo em curso."
    


