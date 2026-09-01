# 💻 Algoritmos e Programação

<p align="center">
  <img src="https://img.shields.io/badge/Status-Finalizado-success?style=for-the-badge" alt="Status do Projeto">
  <img src="https://img.shields.io/badge/Linguagem-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white" alt="C" />
</p>

## 📖 Sobre o Repositório

Este repositório é dedicado a armazenar os códigos, listas de exercícios e trabalhos práticos desenvolvidos durante meus estudos na disciplina de **Algoritmos e Programação** do curso de **Bacharelado em Ciência da Computação** da **UFRGS**.

O objetivo principal destes códigos é consolidar a base da lógica de programação e o entendimento de algoritmos clássicos.

## 📂 Estrutura do Repositório

Aqui está uma visão geral de como os arquivos estão organizados:

```text
📦 AlgoritmosProgramacao
 ┣ 📂 Práticas                # Exercícios propostos pelo Professor
 ┣ 📂 Práticas Adicionais     # Exercícios encorajados pelo Professor para fixação de conteúdo e diferentes padrões
 ┣ 📂 FlappyInf               # Trabalho final da disciplina. Um jogo baseado no FlappyBird
 ┗ 📜 README.md
```

 # 🕹 FlappyInf

<p align="center">
  <img src="https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/raylib-FFFFFF?style=for-the-badge&logo=raylib&logoColor=black" alt="Raylib" />
</p>

O **FlappyInf** é um clone do clássico jogo Flappy Bird, desenvolvido inteiramente em **C** utilizando a biblioteca gráfica **Raylib**. Este projeto foi construído como trabalho final para a disciplina de Algoritmos e Programação do curso de Ciência da Computação da **UFRGS**.

O foco do projeto foi aplicar conceitos fundamentais de programação estruturada, como manipulação de ponteiros, alocação dinâmica e leitura/escrita de arquivos, em um cenário visual e interativo.

## ⚙ Funcionalidades

* **Dificuldade Progressiva:** A velocidade e a complexidade dos obstáculos aumentam à medida que o jogador sobrevive por mais tempo, testando os reflexos do usuário.
* **Configuração Dinâmica:** Os parâmetros principais do jogo (como gravidade, velocidade e tamanho dos canos) são carregados a partir de arquivos de texto (`.txt`). Isso permite alterar a física e o comportamento do jogo sem a necessidade de recompilar o código-fonte.
* **Ranking Persistente:** Sistema de pontuação máxima (High Score) e placar de líderes. Os dados dos jogadores são salvos de forma segura utilizando arquivos binários (`.bin`), garantindo que o ranking seja mantido mesmo após fechar o jogo.

## 🛠️ Aprendizados e Tecnologias

* **Linguagem C:** Aprofundamento em controle de fluxo, estruturas (`structs`), ponteiros e manipulação de arquivos (texto e binários).
* **Raylib:** Utilização da biblioteca para renderização 2D, controle de taxa de quadros (FPS), reprodução de áudio e captura de input (teclado).

## 🚀 Como Executar

Para rodar este projeto, você precisará de um compilador C (como o `gcc`) e a biblioteca **Raylib** instalada e configurada no seu sistema.

1. Clone este repositório:
   ```bash
   git clone [https://github.com/yrnnicolas/FlappyInf.git](https://github.com/yrnnicolas/FlappyInf.git)
