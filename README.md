# Library Management System

## Descrição

Este projeto é um sistema de gerenciamento de biblioteca desenvolvido em C++ utilizando SQLite como banco de dados. O sistema permite adicionar, remover, listar, buscar e atualizar o status de livros no banco de dados.

## Estrutura do Projeto

```
Library/
│── .vscode/               # Configuração do editor VSCode
│── bin/                   # Diretório de saída do executável
│   ├── main.exe           # Executável gerado
│── DB/                    # Banco de dados
│   ├── library.db         # Arquivo do banco de dados SQLite
│── include/               # Arquivos de cabeçalho
│   ├── sqlite3.h          # Biblioteca SQLite
│   ├── System.h           # Declaração da classe System
│── lib/                   # Bibliotecas externas
│   ├── libsqlite3.a       # Biblioteca SQLite compilada
│── src/                   # Código-fonte
│   ├── main.cpp           # Arquivo principal do programa
│   ├── System.cpp         # Implementação da classe System
│── .gitattributes         # Configuração do Git
│── .gitignore             # Arquivos ignorados pelo Git
```

## Funcionalidades

- **Adicionar um livro** ao banco de dados
- **Remover um livro** do banco de dados
- **Listar todos os livros** armazenados
- **Buscar um livro** pelo ID
- **Atualizar o status de um livro** (Disponível/Indisponível)

## Configuração e Execução

### 1. Compilar o projeto

Abra um terminal na raiz do projeto e compile os arquivos usando o compilador g++:

```sh
 g++ -o bin/main src/main.cpp src/System.cpp -Iinclude -Llib -lsqlite3
```

### 2. Executar o programa

Após a compilação, execute o programa:

```sh
 ./bin/main
```

## Dependências

- **C++**
- **SQLite3** (Inclui a biblioteca `sqlite3.h` e `libsqlite3.a`)

## Exemplo de Uso

```
LIBRARY SYSTEM

1 - Add a new book to the database
2 - Remove a book from the database
3 - List all books
4 - Search a specific book
5 - Update book's status
6 - Finish program.

Operation: 1
Title: O Senhor dos Anéis
Author: J.R.R. Tolkien
Year: 1954
Book added with success!
```
