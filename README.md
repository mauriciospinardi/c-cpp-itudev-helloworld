# Itu Developers "Hello, World!"

Repositório de apoio ao 7º MeetUp Itu Developers - "Construindo uma solução
multiplataforma: conceitos, responsabilidades e trabalho em equipe".  
Exercícios e desafios são propostos na última seção deste documento.  

## Sumário

- [Ambiente de desenvolvimento]()
- [Compilação]()
  - [Definindo o ambiente]()
  - [Comandos]()
  - [Visual Studio Code]()
- [Execução e depuração]()
  - [GTK]()
  - [V-OS2]()
- [Exercícios]()
  - [Teoria]()
  - [Prática (individual)]()
  - [Prática]()

## Ambiente de desenvolvimento

O arquivo ```.\misc\env.bat``` define o ambiente de desenvolvimento e deve ser
considerado o ponto de entrada deste projeto. Neste arquivo, destaca-se o
diretório raíz ```C:\cygwin64```.  

[Cygwin](https://www.cygwin.com) provê todas as dependências:  

- GNU Compiler Collection
- The GNU version of the 'make' utility
- GNOME desktop icon theme for Win64 toolchain
- GTK+ GUI toolkit for Win64 toolchain
- Default fallback icon theme for Win64 toolchain

## Compilação

### Definindo o ambiente

Conforme seção anterior, ```.\misc\env.bat``` define o ambiente de
desenvolvimento. Isto é, em uma janela do prompt de comandos do Windows:  

```cmd
<...\itudev-helloworld>.\misc\env.bat
```

### Comandos

Uma vez definido o ambiente de desenvolvimento, estarão disponíveis as
ferramentas básicas que acompanham uma distribuição Cygwin. Na mesma janela
mencionada anteriormente, execute:  

```cmd
<...\itudev-helloworld>bash -c "make CFG_NAME=debug"
```

O comando acima irá disparar o processo de compilação em configuração
```debug```.  

### Visual Studio Code

Este projeto possui integração (opcional) com Visual Studio Code. Os arquivos
no diretório ```./vscode``` podem ser consultados como referência para os
comandos mais importantes e de uso comum. Por exemplo:  

- Para o correspondente de ```bash -c "make CFG_NAME=debug"```, em ```./vscode/tasks.json```,
  teremos:

```json
{
    "label": "--build-debug",
    "type": "shell",
    "command": "& bash -c \"make CFG_NAME=debug\" & exit",
    "group": "build"
}
```

Nota-se que a chave ```"command"``` define ```bash -c "make CFG_NAME=debug"```,
usado para disparar o processo de compilação em configuração ```debug```.  

## Execução e depuração

### GTK

O diretório de saída para o binário gerado pelo processo de compilação segue o
formato ```./bin/<plataforma>/<configuração>/<executável>```. Isto é, depois de
uma compilação bem sucedida, em modo de depuração, execute:  

```cmd
<...\itudev-helloworld>.\bin\gtk\debug\helloworld.exe
```

Este comando deverá inicializar a aplicação, em janela própria. Trechos de
depuração serão direcionados para a mesma janela onde o comando de inicialização foi executado:  

```cmd
<...\itudev-helloworld>.\bin\gtk\debug\helloworld.exe

Aug  4 2020 12:51:35 src/gtk/itudev.c #0113 itudev_start::gtk_application_new() [8950080]
Aug  4 2020 12:51:35 src/gtk/itudev.c #0207 activate::gtk_application_window_new() [9417296]
Aug  4 2020 12:51:36 src/main.c #0044 main::itudev_start() [0]
Aug  4 2020 12:51:35 src/gtk/itudev.c #0245 create_image::gtk_image_new_from_file() [57987392]
Aug  4 2020 12:51:35 src/gtk/itudev.c #0249 create_image::gtk_event_box_new() [57987744]
Aug  4 2020 12:51:35 src/gtk/itudev.c #0085 itudev_image_flush::create_image() [57987744]
Aug  4 2020 12:51:36 src/main.c #0053 main::itudev_image_flush() [0]
Aug  4 2020 12:51:35 src/gtk/itudev.c #0063 itudev_end::application [8950080]
Aug  4 2020 12:51:36 src/main.c #0062 main::itudev_end() [0]
Aug  4 2020 12:51:35 src/gtk/itudev.c #0126 itudev_start::g_application_run() [0]
Aug  4 2020 12:51:35 src/gtk/itudev.c #0063 itudev_end::application [0]
Aug  4 2020 12:51:35 src/gtk/itudev.c #0135 itudev_start::itudev_end() [0] (platform exiting point...)
```

### V-OS2

Por razões de confidencialidade e direitos de terceiros, regras de compilação e
dependências necessárias para a construção do pacote
```dl.itudev_01.00.00.tar```, em ```./bin/vos2/debug/``` foram aqui omitidas.
Código-fonte, entretanto, está disponível para consulta em ```./src/vos2/```.  

## Exercícios

### Teoria

1. Qual a organização deste repositório? Quais os arquivos de saída?
2. Qual organização seria recomendada para incluir implementações de novas
   plataformas?
3. Qual(is) a(s) diferença(s) entre as versões GTK e V-OS2?  
   Para a versão V-OS2, referir-se ao vídeo em ```./bin/vos2/debug/```.

### Prática (individual)

4. Procure e elabore comentários sobre os trechos de código com prefixo "Para
   pensar:". O que pode ser dito a respeito?
5. Escolha uma "nova plataforma" e implemente a API ItuDev. Quais os desafios e
   dificuldades?  
   Sugestão: [Windows API](https://docs.microsoft.com/en-us/windows/win32/apiindex/windows-api-list).
6. Como a API ItuDev proposta nesse repositório poderia evoluir? Quais funções
   acrescentar/modificar? Quais suas críticas e sugestões?

### Prática

7. Implemente a API ItuDev para duas novas plataformas. Quais responsabilidades
   foram atribuídas a cada membro da equipe?  
   Sugestão: Android C/C++ - ```main.c``` - via NDK.
8. Controle de versão: qual a organização do(s) seu(s) repositório(s) depois de
   concluir o exercício 7?
9. Commits e documentação:  
   - Quais observações o time pode fazer a respeito das mensagens de commits
     deste repositório?
   - Quais observações o time pode fazer a respeito dos arquivos de extensão
     *.md?
   - Qual o conteúdo do arquivo CHANGELOG.md gerado pela sua equipe? Foram
     criadas novas TAGs?
     - Sugestão: [Keep a changelog!](https://keepachangelog.com/en/1.0.0/)
