# Mutex Trânsito
Código na linguagem `C`, utilizando `threads` e `mutex` para haver concorrência na travessia da encruzilhada de maneira visual no terminal.

## Descrição:
Os carros `(C1, C2)` andam até o semáforo inicialmente vermelho e buscam acessar a variável `ruaX` ao mesmo tempo dentros das suas threads. Logo o mutex organiza o acesso a esse dado deixando apenas um dos carros passar por vez, trocando as cores do semáforo e liberando para o próximo carro passar.
