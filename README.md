# Fuga Humana <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white">


### 📌 Descrição

Este projeto é a primeira implementação de um trabalho acadêmico, onde o objetivo era encontrar um caminho entre dois pontos em uma matriz 2D. A abordagem utilizada foi a busca em largura (**BFS**), implementada sem um estudo aprofundado do algoritmo, baseando-se apenas no conceito geral de exploração por níveis.

A matriz utilizada possui os seguintes elementos:
- `o`: Caminho Livre
- `H`: Humano (Ponto inicial)
- `R`: Robos (Ponto inacessível)
- `Z`: Zona de Segurança (Ponto final)

O algoritmo deve encontrar o menor caminho possível entre `H`  e `Z`, evitando os obstáculos representados por `R`.

### 🚀 Evolução do Projeto

Uma versão aprimorada deste projeto foi desenvolvida posteriormente em **C++**, incorporando um entendimento mais sólido do algoritmo e um contexto mais complexo. Caso tenha interesse, você pode conferir a nova versão aqui:

➡ **[Missão de Resgate Espacial (Implementação em C++)](link-para-o-repositório-cpp)**

### ▶ Como Executar

1. Clone este repositório:
   ```sh
   git clone https://github.com/PeedroHG/FugaHumana.git
   cd fuga-humana
   ```

2. Compile o código:
   ```sh
   gcc main.c -o fuga_humana
   ```

3. Execute o programa:
   ```sh
   ./fuga_humana 
   ```

