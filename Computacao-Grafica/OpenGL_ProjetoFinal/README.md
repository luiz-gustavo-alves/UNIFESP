# Demonstração
[![Computer Graphics Final Project - Physiotherapy Exercises Humanoid Animation (OpenGL)](http://img.youtube.com/vi/HnEtkhV3gA4/0.jpg)](https://www.youtube.com/watch?v=HnEtkhV3gA4 "Computer Graphics Final Project - Physiotherapy Exercises Humanoid Animation (OpenGL)")


## Trabalho Final de Computação Gráfica 
Projeto feito em linguagem C com utilização da bilbioteca OpenGL para renderização gráfica.

O trabalho possibilita a criação de um ambiente de visualização tridimensional e interativo com usuário através do teclado e o menu de opções pré-estabelecidas.

## Objetivo
O projeto tem como objetivo apresentar as principais técnicas e métodos de Computação Gráfica desenvolvidas no decorrer da disciplina, tais como: visualização tridimensional, animação, interação com usuário, iluminação e textura.

Para cumprir este objetivo, o trabalho em questão demonstra a aplicação direta do aprendizado adquirido por meio da criação de um ambiente tridimensional interativo que simula sequências de exercícios de reabilitação para pacientes que precisam de fisioterapia.

A motivação da escolha dos exercícios tem como base em trabalhar a resistência, flexibilidade, fortalecimento da musculatura, alívio de dores e posicionamento da postura corporal. Para este projeto foi feita a escolha de 10 exercícios no total em que 5 destes exercícios são executados sem equipamentos e os outros 5 exercícios com equipamentos, sendo um par de halteres o equipamento a ser utilizado.

## Menu Principal

Para selecionar o menu, é necessário clicar com o botão direito do mouse.<br>
O menu principal consiste em 4 opções:

- Resetar: para a animação atual (apenas para exercícios com equipamento) e reseta a animação do humanoide.

- Movimentação Individual: permite controlar cada parte do corpo do humanoide de modo separado (quando uma animação estiver sendo executada e o usuário selecionar esta opção, a animação será automaticamente resetada). Segue abaixo as seguintes opções de movimentação individual:
  - Mover Cabeça.
  - Mover Braço Esquerdo.
  - Mover Braço Direito.
  - Mover Antebraço Esquerdo.
  - Mover Antebraço Direito.
  - Mover Perna Esquerda.
  - Mover Perna Direita.
  - Mover Joelho Esquerdo.
  - Mover Joelho Direito.

- Exercícios - Aquecimento: Executa as animações dos exercícios sem equipamentos. Segue abaixo as seguintes opções de exercícios de aquecimento (sem equipamento):
  - Alongamento Quadriceps.
  - Alongamento Pescoço.
  - Flexão Lateral de Tronco.
  - Agachamento.
  - Polichinelo.
  - Todos (executa todas as animações acima, em ordem).

- Exercícios - Halteres: Executa as animações dos exercícios com equipamentos. Para tanto, é necessário primeiramente que o usuário selecione a opção de “Pegar Equipamento” antes de realizar qualquer exercício. Quando o personagem estiver com equipamento não é possível selecionar as outras opções do menu principal além deste menu com exercícios com equipamentos, para poder selecionar outras opções é necessário que o usuário selecione a opção de “Devolver Equipamento”. Segue abaixo as seguintes opções de exercícios com halteres (com equipamento):
  - Pegar Equipamento (é necessário selecionar esta opção antes de realizar os exercícios com equipamento).
  - Rosca Alternada.
  - Rosca Simultânea.
  - Elevação Frontal.
  - Elevação Lateral.
  - Afundo.
  - Todos (executa todas as animações acima, em ordem).
  - Devolver Equipamento (devolver par de halteres e liberar as outras opções do menu principal).

## Opções de Teclas do Teclado

- ESC: sair do programa.
- (x, y, z): aplica uma rotação positiva em um dos eixos x, y, ou z. Utilizado em
conjunto quando o usuário escolher movimentar individualmente uma dada
estrutura do corpo humano.
- (X, Y, Z): aplica uma rotação negativa em um dos eixos x, y, ou z. Utilizado
em conjunto quando o usuário escolher movimentar individualmente uma
dada estrutura do corpo humano.
- (+): aplica um _zoom in_ na câmera.
- (-): aplica um _zoom out_ na câmera.
- (Teclas direcionais - esquerda, direita): aplica uma rotação azimutal (rotação
em y) para a posição da câmera, sendo a tecla direcional da esquerda uma
rotação negativa e a tecla direcional da direita uma rotação positiva.
- (Teclas direcionais - baixo, cima): aplica uma rotação elevação (rotação em
x) para a posição da câmera, sendo a tecla direcional para baixo uma
rotação negativa e a tecla direcional para cima uma rotação positiva.

## Imagens do Cenário

<div align="center">
  <img width="850" height="450" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/f0ba29fb-b66d-435a-8a12-9c9a6a93eac7"/>
  <p>Visao horizontal do cenário.</p>
</div>
<br>
<div align="center">
  <img width="850" height="450" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/886d2650-503e-4ce5-81dc-6e8bd8606af8"/>
  <p>Visão vertical do cenário</p>
</div>

## Imagens da Animação

<div align="center">
  <img width="600" height="400" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/11b2594e-389b-4cb3-8719-dd34feb6776a"/>
  <p>Alongamento Quadricps.</p><br>
  <img width="600" height="400" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/98c996ac-58fc-4eda-9bf6-43500ffc5a3b"/>
  <p>Alongamento Pescoço</p><br>
  <img width="600" height="400" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/41f490fa-b1c3-4057-9966-78caffeb7f82"/>
  <p>Flexão Lateral do Tronco</p><br>
  <img width="600" height="400" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/9483ef77-8953-4481-87f0-7669f0227500"/>
  <p>Agachamento</p><br>
  <img width="400" height="400" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/691a1d28-2926-4107-a1df-6b4200dc1bb2"/>
  <p>Polichinelo</p><br>
  <img width="800" height="400" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/d626949e-baf2-40e4-8434-ad65d9be7d40"/>
  <p>Pegar Equipamento</p><br>
  <img width="600" height="400" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/7b372a62-bdb5-49f6-be7c-c1230614cb44"/>
  <p>Rosca Alternada</p><br>
  <img width="600" height="400" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/c73fefd0-1088-4db1-8848-6d222d908ce0"/>
  <p>Rosca Simultânea</p><br>
  <img width="600" height="400" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/f8bc9c92-5f1d-4d4a-be82-ee128c15fafe"/>
  <p>Elevação Frontal</p><br>
  <img width="600" height="400" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/8cdf09fb-9cbc-4e37-a1fd-468870b570c6"/>
  <p>Elevação Lateral</p><br>
  <img width="600" height="400" src="https://github.com/luiz-gustavo-alves/UNIFESP/assets/114351018/3407b0f3-fa9c-495d-ae7f-47de94046f5c"/>
  <p>Afundo</p><br>
</div>
