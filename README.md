# Trabalho de Computação Gráfica

Projeto de *Computação Gráfica* desenvolvido em *C* utilizando *OpenGL* e *FreeGLUT*. O objetivo é implementar uma aplicação gráfica que permite a criação, manipulação e transformação de objetos geométricos.

## Estrutura do Projeto
bash
├── src/            # Código-fonte (.c)
├── include/        # Cabeçalhos (.h)
├── obj/Debug/      # Objetos compilados (.o)
├── bin/Debug/      # Executável (.exe)
├── Makefile        # Makefile para compilar o projeto
├── save_tela.txt   # Arquivo de Backup
└── README.md


## Requisitos

- *Compilador*: GCC ou MinGW (via MSYS2)
- *Bibliotecas*:
  - OpenGL
  - GLU
  - FreeGLUT
- *Sistema*: Windows (via MSYS2/MinGW)

> No MSYS2, instale os pacotes necessários com:
bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-freeglut


## Compilação
- Abra o MSYS2 MinGW 64-bit.
- Navegue até a pasta do projeto:

bash
cd /caminho/para/computer-graphics-project

Compile usando o Makefile:

bash
make

Isso irá gerar o executável em bin/Debug/Trabalho.exe.

### Execução
No MSYS2, execute com o Makefile:
bash
make run

Ou diretamente, com o comando:
bash
./bin/Debug/Trabalho.exe


### Limpeza
Para remover arquivos compilados e o executável:

bash
make clean


## Estrutura do Código
> main.c: Inicializa o programa e controla a execução.

> estado.c: Gerencia o estado do programa e dos objetos.

>interface.c: Implementa a interface gráfica e interação do usuário.

> listaPontos.c, listaRetas.c, listaPoligonos.c: Implementação das listas de objetos geométricos.

> menu.c: Menu de opções do programa.

> transformacoes.c: Funções para aplicar transformações geométricas (translação, rotação, escala).

## Controles
- As setas do teclado permitem a translação.
- Os botões *‘n’* e *‘m’* permitem a escala.
- Os botões *‘r’* e *‘t’* permitem a rotação.
- Os botões *‘c’* e *‘v’* permitem o cisalhamento.
- Os botões *‘w’* e *‘d’* permitem a reflexão.
