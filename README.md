# Boleias Partilhadas - ShareIt (nome provisório)
==================
1.º Trabalho de Grupo de AEDA, FEUP

AEDA1617_2MIEIC1_E

Requisitos Obrigatórios:
------------------------
- [X] Visualização dos Users
- [ ] Visualização do histórico de viagens
- [ ] Ficheiro: Users
- [ ] Ficheiro: Relationships ("buddies")
- [ ] Ficheiro: Trip Record (histórico de viagens realizadas)
- [ ] Associar buddies
...


File Syntax
===========

Source cpp:
----------
= welcomeMenu =
> display do esqueleto do menu
> retorna opcao de inicio de sessão

= main =
> extrai informação dos ficheiros de texto
> chama menu inicial (welcomeMenu)

Agency h/cpp:
----------
> criação de singleton
> variáveis globais, acessiveis a todas as classes: sessionID e sessionPos (ID e posição do "User" no vetor Users - Informação do Login) // vetores Users, Trips, Transactions.

= registerUser =
> menu de registo de um novo user
> adiciona ao vetor Users um novo objeto

= loginUser =
> menu de login de um user
> acede à conta, novo menu e afins

= mainMenu_Admin =
> menu apenas visualizado pelo administrador da agency: credenciais-> admin, admin

= mainMenu_User =
> menu principal de um user

= displayUsers =
> diplay do id, nome, balance, username, pass

= menuDisplayUsers =
> menu de dipay de users

= displayBuddies =
> diplay do nome do user e dos seus buddies

= menuDisplayBuddies =
> menu de display de buddies 

= displayTransactions =
> diplay do id, data e value das transactions

= menuDisplayTransactions =
> menu de display de transactions

= extractUsers =
> extrai do ficheiro de texto "Users.txt" a informação de todos os users para um vetor Users

= writeUsers =
> guarda toda a informação do vetor Users, no ficheiro de texto

= extractBuddies =
> extrai do ficheiro de texto "Buddies.txt" a informação de todos os users para um vetor Buddies

= writeBuddies =
> guarda toda a informação do vetor Buddies, no ficheiro de texto

= extractTransactions =
> extrai do ficheiro de texto "Transactions.txt" a informação de todos os users para um vetor Users

= writeTransactions =
> guarda toda a informação do vetor Transactions, no ficheiro de texto

= validUser =
> booleano que retorna de um user "nome" existe

= validPassword =
> booleano que retorna se a password de respetivo user está correta

= findID =
> recebe o nome de um user e retorna respetivo ID

= getPos =
> recebe o ID de um user, e retorna a posição do user no vetor Users (é bastante útil)

= getUsers =
> retorna o vetor Users

= addUser =
> adiciona um novo objeto User ao vetor Users

= checkStop =
> recebe uma string e verifica se ela pertence ao vetor de paragens disponiveis, retorna false se nao existir

= addTrip = 
> adiciona uma trip ao vetor sob o User que está logado na aplicação

User h/cpp:
----------
> tem classes derivadas: Driver, Passenger

= getID =
> retorna ID do user

= getName =
> retorna o nome do user

= getPassword =
> retorna password do user

= depoist =
> carrega o saldo (balance) do user com value

= payment =
> faz pagamento à empresa de cada user - VIRTUAL

= car =
> retorna se tem carro ou nao (driver ou passenger) - VIRTUAL

= addTrip =
> recebe como parametro um objeto do tipo Trip, e adiciona ao Driver associado - VIRTUAL

Guest h/cpp:
---------------
= getName =
> retorna nome

= getStart =
> retorna origem da viagem pretendida

= getEnd =
> retorna o destino da viagem pretendida

Trip h/cpp:
---------------
= getDriver =
> retorna o driver

= getID =
> retorna o ID da viagem (para uso interno)

= getStops =
> retorna vetor de paragens da viagem (itinerário)

= getOrigin =
> retorna origem

= getDestination =
> retorna destino

= setDriverID =
> recebe como parametro o ID de um User, ao qual fica associado a viagem

= setID =
> recebe como parametro um inteiro, ao qual fica associado o ID da viagem para uso interno

= setStops =
> recebe como parametro um vetor de strings, atribui a uma viagem esse vetor de paragens

= addBuddy =
> recebe o user que pretende adicionar ao vetor de buddies

= deleteBuddies =
> limpa o vetor de buddies

= getBuddies=
> retorna o vetor buddies

Tools h/cpp:
---------------
= outputName =
> util para o utilizador inserir ID ou nome
> verifica se output é um inteiro(false) ou string(true)

= insertPassword =
> processo de inserir pass
> retorna password escrita com ***

= sameString =
> vê se duas strings são iguais (true/false)

