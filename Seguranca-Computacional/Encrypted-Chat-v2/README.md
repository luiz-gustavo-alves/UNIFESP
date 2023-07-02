# Demonstração
https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/30a819c6-ed15-4b0d-88c2-3cf4c166e489

## Instruções para executar o arquivo:

- Rodar o arquivo server.py em apenas UM terminal.
    - Fornecer o IP do servidor (EX: 127.0.0.1 - Localhost)

- Rodar o arquivo client.py em um ou mais terminais.
    - Fornecer o IP da máquina a ser conectada (EX: 127.0.0.1 - Localhost).
    - Fornecer o nome do usuário.

## Instruções da utilização da interface gráfica

- As configurações atuais do chat estão disponívels no canto inferior direito da tela: BROADCAST, PUBLIC, SDES e ECB por padrão.
- Essas configurações podem ser trocadas ao clicar nos botões (DM, SDES - RC4, ECB - CBC, PUBLIC key - SECRET key - Sesssion key).
- Campo Message: Enviar mensagem na caixa de texto e pressione o botão SEND para enviar sua mensagem.

- Select Algorithm: Seleciona o algoritmo de criptografia a ser utilizado na comunicação:
    - SDES: Criptografia SDES;
    - RC4: Criptografia RC4.

- Select SDES operation: Seleciona o modo de operação da criptografia SDES:
    - ECB: Modo de operação ECB;
    - CBC: Modo de operação CBC.

- Select Key: Seleciona o tipo de chave a ser utilizado na comunicação:
    - Public Key: Utilização da chave pública;
    - Secret Key: Utilização da chave privada (secreta);
    - Session Key: Utilização da chave de sessão (DH).

- Send DM: Inserir nome ou IP do usuário para se comunicar no chat
    - Caso o nome ou IP fornecidos não exista no sistema, a forma de comunicação será padrão: BROADCAST, PUBLIC, SDES e ECB.

- Secret Key: Inserir chave privada para comunicação via DM - é necessário ainda escolher o tipo de criptografia SDES ou RC4.
    - SDES key: Fornecer chave secreta a ser utilizada na comunicação por criptografia SDES;
    - RC4 key: Fornecer chave secreta a ser utilizada na comuniação por criptografia RC4.

- Session Key value: Inserir o valor do secredo (não compartilhado) para a chave de sessão.

## Informações a respeito das configurações do chat:

- BROADCAST refere-se a forma de comunicação do chat - enviar mensagem para todos os clientes.
- DM refere-se a forma de comunicação do chat - enviar mensagem privada para um cliente.
- PUBLIC/SECRET/SESSION refere-se a chave pública/secreta/sessão a ser utilizada.
- SDES/RC4 refere-se ao algoritmo de criptografia a ser utilizado.
- ECB/CBC refere-se ao modo de operação SDES a ser utilizado.
