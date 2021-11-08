/bin/ls sem argumento -> retorna todo o conteúdo da pasta atual
echo -> printa a string no output com \n
echo -n -> printa a string no output sem \n
exit -> sai do terminal
exit $ -> sai e mostra o código de saída (como implementar? maior bruxaria da vida)


**Perguntar - status do exit e se tem algum outro argumento que o exit recebe.
Perguntar dos testes da régua de correção que a gente não lembra/não entende.**

**Signals**

ctrl-C -> sai/interrompe o processo tanto com a linha cheia quanto com ela vazia (SIGINTERRUPT)
ctrl-\ -> no prompt vazio não faz nada nem com linha parcialmente cheia. (Ver qual signal que é)
ctrl-D -> na linha vazia sai do terminal. Se a linha estiver cheia não faz nada. (Ver qual sinal que é)

**Aspas duplas**
(ver o que fazer aqui)
também serve como escape dos caracteres especiais

env -> tem que mostrar todas as variáveis de ambiente ativas e seus respectivos valores (incluindo as adicionadas)
também temque atualizar quando mexemos no valor da variável

export -> adicionar uma variável de ambiente (com ou sem valor acoplado)

unset -> remover uma variável de ambiente e seu valor (caso haja)

variável de ambiente -> verifica se consegue acessar os valores. (usando echo $Variável). Se "$ARG" -> imprime o valor contido na variável.
Se '$ARG' -> imprime $ARG 

cd -> cd . continua na pasta atual e devolve o prompt
cd .. volta uma pasta
cd klajsdlkjaskdljas entra na pasta se houver
se tiver o caminho, vai para a pasta do caminho (não tá funfando o nosso por enquanto)

pwd -> tem que mostrar o caminho da pasta atual

Caminho relativo
usar caminhos relativos e ser muito doido e testar com vários ../kjagsjdgasj

Caminho do ambiente
começa a testar os comandos sem usar o /bin
ver o caminho com $PATH, dar um unset (não pode funcionar mais), depois dar um set com o valor anterior e assegurar que os diretórios estão na odem da esquerda pra direita.

**Aspas simples**
descobrir o que essa p***** testa
usar como escape dos caracteres especiais

**Redirecionamento**
Confirmar os sentidos dos sinais. (pra que serve?)
Verificar se redirecionamentos múltiplos falham
(Quando se faz um redirecionamento duplo do echo com > o texto vai parar no último arquivo e o do meio fica intacto)

**Pipe**
ver todas as coisas que o pipe faz
verificar questão do grep

**Testa as coisa doida e histórico**
acessar histórico de comandos e tentar comandos errados novamente
pesquisar (de novo) sobre onde fica armazenado o histórico de comandos
colocar proteção e erro para comandos que nào existem