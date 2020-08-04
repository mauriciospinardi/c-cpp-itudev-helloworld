# Itu Developers "Hello, World!"

Reposit�rio de apoio ao 7� MeetUp Itu Developers - "Construindo uma solu��o
multiplataforma: conceitos, responsabilidades e trabalho em equipe".  
Exerc�cios e desafios s�o propostos na �ltima se��o deste documento.  

## Sum�rio

- [Ambiente de desenvolvimento]()
- [Compila��o]()
  - [Definindo o ambiente]()
  - [Comandos]()
  - [Visual Studio Code]()
- [Execu��o e depura��o]()
  - [GTK]()
  - [V-OS2]()
- [Exerc�cios]()
  - [Teoria]()
  - [Pr�tica (individual)]()
  - [Pr�tica]()

## Ambiente de desenvolvimento

O arquivo ```.\misc\env.bat``` define o ambiente de desenvolvimento e deve ser
considerado o ponto de entrada deste projeto. Neste arquivo, destaca-se o
diret�rio ra�z ```C:\cygwin64```.  

[Cygwin](https://www.cygwin.com) prov� todas as depend�ncias:  

- GNU Compiler Collection
- The GNU version of the 'make' utility
- GNOME desktop icon theme for Win64 toolchain
- GTK+ GUI toolkit for Win64 toolchain
- Default fallback icon theme for Win64 toolchain

## Compila��o

### Definindo o ambiente

Conforme se��o anterior, ```.\misc\env.bat``` define o ambiente de
desenvolvimento. Isto �, em uma janela do prompt de comandos do Windows:  

```cmd
<...\itudev-helloworld>.\misc\env.bat
```

### Comandos

Uma vez definido o ambiente de desenvolvimento, estar�o dispon�veis as
ferramentas b�sicas que acompanham uma distribui��o Cygwin. Na mesma janela
mencionada anteriormente, execute:  

```cmd
<...\itudev-helloworld>bash -c "make CFG_NAME=debug"
```

O comando acima ir� disparar o processo de compila��o em configura��o
```debug```.  

### Visual Studio Code

Este projeto possui integra��o (opcional) com Visual Studio Code. Os arquivos
no diret�rio ```./vscode``` podem ser consultados como refer�ncia para os
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
usado para disparar o processo de compila��o em configura��o ```debug```.  

## Execu��o e depura��o

### GTK

O diret�rio de sa�da para o bin�rio gerado pelo processo de compila��o segue o
formato ```./bin/<plataforma>/<configura��o>/<execut�vel>```. Isto �, depois de
uma compila��o bem sucedida, em modo de depura��o, execute:  

```cmd
<...\itudev-helloworld>.\bin\gtk\debug\helloworld.exe
```

Este comando dever� inicializar a aplica��o, em janela pr�pria. Trechos de
depura��o ser�o direcionados para a mesma janela onde o comando de inicializa��o foi executado:  

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

Por raz�es de confidencialidade e direitos de terceiros, regras de compila��o e
depend�ncias necess�rias para a constru��o do pacote
```dl.itudev_01.00.00.tar```, em ```./bin/vos2/debug/``` foram aqui omitidas.
C�digo-fonte, entretanto, est� dispon�vel para consulta em ```./src/vos2/```.  

## Exerc�cios

### Teoria

1. Qual a organiza��o deste reposit�rio? Quais os arquivos de sa�da?
2. Qual organiza��o seria recomendada para incluir implementa��es de novas
   plataformas?
3. Qual(is) a(s) diferen�a(s) entre as vers�es GTK e V-OS2?  
   Para a vers�o V-OS2, referir-se ao v�deo em ```./bin/vos2/debug/```.

### Pr�tica (individual)

4. Procure e elabore coment�rios sobre os trechos de c�digo com prefixo "Para
   pensar:". O que pode ser dito a respeito?
5. Escolha uma "nova plataforma" e implemente a API ItuDev. Quais os desafios e
   dificuldades?  
   Sugest�o: [Windows API](https://docs.microsoft.com/en-us/windows/win32/apiindex/windows-api-list).
6. Como a API ItuDev proposta nesse reposit�rio poderia evoluir? Quais fun��es
   acrescentar/modificar? Quais suas cr�ticas e sugest�es?

### Pr�tica

7. Implemente a API ItuDev para duas novas plataformas. Quais responsabilidades
   foram atribu�das a cada membro da equipe?  
   Sugest�o: Android C/C++ - ```main.c``` - via NDK.
8. Controle de vers�o: qual a organiza��o do(s) seu(s) reposit�rio(s) depois de
   concluir o exerc�cio 7?
9. Commits e documenta��o:  
   - Quais observa��es o time pode fazer a respeito das mensagens de commits
     deste reposit�rio?
   - Quais observa��es o time pode fazer a respeito dos arquivos de extens�o
     *.md?
   - Qual o conte�do do arquivo CHANGELOG.md gerado pela sua equipe? Foram
     criadas novas TAGs?
     - Sugest�o: [Keep a changelog!](https://keepachangelog.com/en/1.0.0/)
