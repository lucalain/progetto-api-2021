
# Prova Finale di Algoritmi e Principi dell'Informatica - A.A. 2020-2021

Prova finale di algoritmi e principi dell'informatica per l'anno accademico 2020-2021.

**Valutazione**: 30L/30

## Obiettivo e Specifiche del progetto

Realizzare un programma in C per la gestione di una classifica tra grafi diretti pesati. 
La classifica tiene traccia dei `k` "migliori" grafi.
Il programma riceve in ingresso, tramite `stdin`, due parametri iniziali:

-   `d`: numero di nodi per ogni grafo,
    
-   `k`: dimensione della classifica da mantenere.

Successivamente, riceverà una sequenza di comandi: `AggiungiGrafo` o `TopK`. I risultati devono essere forniti tramite `stdout`.

### Comandi:

-   **AggiungiGrafo**: questo comando è seguito dalla matrice di adiacenza del grafo, stampata riga per riga con gli elementi separati da virgole. I nodi del grafo sono etichettati logicamente con un indice intero da 0 a `d-1`. La prima riga della matrice descrive gli archi uscenti dal nodo 0.

- **TopK**: questo comando richiede al programma di stampare gli indici interi dei `k` grafi che hanno i `k` valori più piccoli della metrica definita come la somma dei cammini più brevi tra il nodo 0 e tutti gli altri nodi del grafo raggiungibili da 0. Se più grafi hanno lo stesso valore della metrica, si dà la precedenza ai primi arrivati. Le distanze dei nodi non raggiungibili da 0 sono considerate nulle. Gli `k` indici interi devono essere stampati su un'unica riga, separati da uno spazio, in qualsiasi ordine.



### Criteri di Valutazione:

Il programma doveva essere:

-   **Corretto** (output preciso e conforme).
    
-   **Efficiente** (rispetto dei vincoli di tempo e memoria).
    

La valutazione è stata ottenuta tramite **batterie di test automatizzate**, con uno strumento fornito per il testing locale.  
Il sistema misurava **tempo macchina** e **memoria utilizzata**.

### Dettaglio test:

-   **Prima batteria**: 18 punti (pass/fail).
    
-   **Seconda batteria**: 6 test × 2 punti = 12 punti.
    
-   **Terza batteria**: test per ottenere la **lode**.
    

Tutti i test sono stati superati, ottenendo il massimo punteggio: `30L/30`.

## Scelte Progettuali

### 1. **Struttura dati**

-   **Grafi rappresentati tramite liste di adiacenza**, per efficienza in spazio e accesso rapido ai vicini.
    
-   Ogni nodo della lista contiene:
    
    -   Il nome del nodo destinazione.
        
    -   Il peso dell’arco.
        
    -   Un puntatore al nodo successivo.
        

### 2. **Algoritmo di Dijkstra**

-   Implementato manualmente con:
    
    -   Un **min-heap** statico per gestire la coda delle distanze.
        
    -   Funzione `estraiMin` per estrazione del vertice con distanza minima.
        
    -   Aggiornamento delle distanze tramite `modificaValoreNodoHeap`.
        

### 3. **Gestione della classifica Top-K**

-   E' stata utilizzata una struttura dati `max-heap` per mantenere i `k` migliori grafi in termini di distanza totale.
    
-   Se un nuovo grafo ha distanza inferiore al massimo corrente, sostituisce il peggiore nel max-heap.
    
-   Questo approccio garantisce una complessità efficiente per l’aggiornamento della classifica.
    

### 4. **Input e parsing**

-   Parsing personalizzato con `fgets`.
    
-   Gestione ottimizzata della lettura della matrice di adiacenza tramite `creaLista`.
    

### 5. **Ottimizzazione della memoria**

-   Uso minimo di malloc, con heap statici laddove possibile.
    
-   Riciclo delle strutture dati evitando ricostruzioni inutili tra grafi.
    

### 6. **Output**

-   La stampa della classifica (`TopK`) è gestita con bufferizzazione manuale in un array di caratteri per evitare stampe lente e multiple.
    
-   I numeri vengono invertiti manualmente per l’output, evitando l’uso di librerie standard come `sprintf`.
    

### 7. **Vincoli rispettati**

-   Il codice è progettato per ottimizzare:
    
    -   **Tempo di esecuzione** (attraverso heap e algoritmi efficienti).
        
    -   **Spazio** (grafi compatti, uso limitato di heap dinamico).
        
-   Nessuna libreria avanzata è usata, solo standard C (`stdlib.h`, `stdio.h`, `string.h`).




## Strumenti utilizzati

| Descrizione         | Strumento                                  |
|---------------------|--------------------------------------------|
| IDE                 | [CLion](https://www.jetbrains.com/clion/)  |
| Compilatore         | [gcc](https://gcc.gnu.org/)                |
| Misurazione memoria | [Valgrind - Massif](https://valgrind.org/) |
| Sistema operativo   | Windows 10 e Debian 11                     

## Collegamenti

📄 Specifica del progetto: [specifiche.pdf](./specifiche.pdf) 

📁 Codice sorgente: [progetto.c](./progetto.c)
