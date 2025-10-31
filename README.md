# so_log

Regras de Mapa do Jogo
1. Formato e Tamanho

O mapa deve ser retangular, ou seja, todas as linhas têm o mesmo número de colunas.

O mapa deve ter pelo menos 3x3 de tamanho para permitir elementos mínimos de gameplay.

O mapa deve ser cercado por paredes (1), para evitar que o jogador ou inimigos saiam da tela.

2. Caracteres Válidos

Os únicos caracteres permitidos são:

'1' = parede

'0' = espaço vazio

'P' = player (apenas 1)

'E' = saída (apenas 1)

'C' = coletável (pelo menos 1)

'S' = espinho

'M' = inimigo

3. Player, Saída e Coletáveis

Player (P)

Deve existir apenas 1 player no mapa.

Deve estar posicionado em cima de um bloco sólido (1) ou de outro suporte.

Ocupa 2 blocos de altura, por causa do pulo e da gravidade.

Saída (E)

Deve existir apenas 1 saída.

Deve ser acessível pelo player, ou seja, o player consegue chegar sem atravessar paredes ou impossibilidades de pulo.

Coletáveis (C)

Deve existir pelo menos 1 coletável.

Todos os coletáveis devem ser acessíveis pelo player com o pulo de 1 bloco de altura e gravidade.

4. Espinhos e Inimigos

Espinhos (S)

Podem estar no chão ou suspensos.

Devem ser posicionados de forma que o player possa pular ou desviar.

Inimigos (M)

Andam horizontalmente entre paredes ou plataformas.

Não devem bloquear totalmente o acesso a coletáveis ou à saída.

5. Acessibilidade

Todos os coletáveis e a saída devem ser acessíveis pelo player.

Considerar:

Gravidade: o player cai se não houver chão.

Pulo: o player consegue subir 1 bloco de altura.

6. Exemplos de Validação

Uma linha do mapa: "111111" ✅ válida

Uma linha com caracteres inválidos: "12P0C1" ❌ inválida

Mais de 1 player: "P0P0C1" ❌ inválida

Saída inacessível por pulo alto demais ❌ inválida