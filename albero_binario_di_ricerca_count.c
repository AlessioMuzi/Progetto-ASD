#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct nodo_albero_bin   /* struttura dati: albero binario di ricerca */
{
 int                    valore;
 char                   *stringa;
 struct nodo_albero_bin *sx_p, *dx_p;
} nodo_albero_bin_t;


int  acquisizione_n      (void);

void  inserimento_albero (nodo_albero_bin_t **radice_p,
		          int               valore,
		 	  char              *stringa,
			  int               *contatore);

void visita_simmetrica   (nodo_albero_bin_t *nodo_p,
		          int               *contatore);

nodo_albero_bin_t * ricerca_elemento (nodo_albero_bin_t *radice_p,
		                      int               valore,
				      int               *contatore);


int main (void)
{
    int               n,           /* input: numero per la generazione casuale dei valori */
		      i,
		      j,           
		      k,           /* variabili contatore */
		      doppione,    /* variabile di controllo valori uguali */
	              ricerca;     /* variabile di selezione della ricerca */

    int               *chiavi;     /* array delle chiavi numeriche */

    char              **stringhe;  /* array bidimensionale delle stringhe */

    nodo_albero_bin_t *radice,     /* input: albero binario di ricerca */
		      *nodo_r;     /* nodo della ricerca */

    int               contatore;   /* contatore dei passi */

    
    srand(time(NULL));       /* inizializzazione del generatore */
    
    radice = NULL;
    stringhe = NULL;         /* inizializzazione dei puntatori */

    n = acquisizione_n();    /* acquisizione del numero n */ 

    chiavi = (int *)malloc(n * sizeof(int));            
    
    stringhe = (char **)malloc(n * sizeof(char*));
    for (i = 0;
	 i < n;
         i++)	 
    stringhe[i] = (char *)malloc(10 * sizeof(char));  /* allocazione dinamica degli array */

    for (i = 0;
         i < n;
         i++)
         {
           do
          {
           doppione = 0;		  
           chiavi[i] = rand() % (3 * n);               /* generazione del numero casuale */
           for (k = 0;
		i > k;
                k++)
                if (chiavi[i] == chiavi [k])           /* controllo dell'esistenza di chiavi numeriche uguali */
                   doppione = 1;
          }
          while (doppione == 1);	          
	  for (j = 0;
               j < 10;
               j++)
               stringhe[i][j] = rand() % 52 + 'A';    /* generazione della stringa casuale */
          inserimento_albero(&radice,                 /* inserimento nell'albero binario */
	         	     chiavi[i], 
			     stringhe[i],
			     &contatore);
         }      
    printf("Passi eseguiti per inserire l'ultimo elemento: %d.\n",
           contatore);		                 

    /* output: stampa dei dati ordinati secondo la chiave numerica */
    contatore = 0;
    printf("\nVisualizzazione dei dati secondo la chiave numerica:\n\n"); 
    visita_simmetrica(radice,
		      &contatore);
    printf("Passi eseguiti: %d.\n",
           contatore);

    ricerca = rand() % (3 * n);
    printf("\nElemento da ricercare: %d\n",
           ricerca);

    contatore = 0;

    nodo_r = ricerca_elemento(radice, 
		              ricerca,
			      &contatore);  /* output: ricerca di un elemento */

    if (nodo_r != NULL)
       {
        printf("L'elemento è presente nell'albero binario.\n");
        printf("Stringa associata all'elemento ricercato: %s\n",
	       nodo_r -> stringa);
       }
    else
       printf("L'elemento non è presente nell'albero binario.\n");

    printf("Passi eseguiti: %d.\n",
           contatore);

    return (0);
}


int acquisizione_n (void)
{
    int n,
        esito_lettura;  /* variabile per la validazione */
	
    do
      {
       printf("Digita un numero intero n.\n");
       esito_lettura = scanf("%d",
		             &n);
       if (esito_lettura != 1 || n <= 0)
           printf("Input non accettabile!\n");
       while (getchar() != '\n');
      }
    while (esito_lettura != 1 || n <= 0);

    return (n);
}


void inserimento_albero (nodo_albero_bin_t **radice_p,
	  	         int               valore,
			 char              *stringa,
		 	 int               *contatore)
{    	
    nodo_albero_bin_t *nodo_p,
		      *padre_p,
		      *nuovo_p;	

    (*contatore) = 0;    

    (*contatore)++;
    for (nodo_p = padre_p = *radice_p;
	 (nodo_p != NULL) && (nodo_p -> valore != valore);
        (*contatore) += 4, padre_p = nodo_p, nodo_p = (valore < nodo_p -> valore)?
	                                               nodo_p -> sx_p:
				                       nodo_p -> dx_p);
    (*contatore) += 2;
    if (nodo_p == NULL)
    {	    
      nuovo_p = (nodo_albero_bin_t *)malloc(sizeof(nodo_albero_bin_t));
      nuovo_p -> valore = valore;
      nuovo_p -> stringa = stringa;
      nuovo_p -> sx_p = nuovo_p -> dx_p = NULL;
      (*contatore) += 5;
      if (nodo_p == *radice_p)
        {      
         *radice_p = nuovo_p;
         (*contatore)++;
	} 
      else
        {     
	 (*contatore)++;     
         if (valore < padre_p -> valore)
            { 		 
	     padre_p -> sx_p = nuovo_p;
	     (*contatore)++;
	    } 
	 else
	    {		 
	     padre_p -> dx_p = nuovo_p;
	     (*contatore)++;
            } 
	} 
    }    
}


void visita_simmetrica (nodo_albero_bin_t *nodo_p,
		        int               *contatore)
{
    if (nodo_p != NULL)
    {
     visita_simmetrica(nodo_p -> sx_p,
		       contatore);
     printf("%d %s\n",
            nodo_p -> valore,		     
	    nodo_p -> stringa);
     visita_simmetrica(nodo_p -> dx_p,
		       contatore);
    }
    (*contatore)++;
}


nodo_albero_bin_t * ricerca_elemento (nodo_albero_bin_t *radice_p,
				      int               valore,
				      int               *contatore)
{
    nodo_albero_bin_t *nodo_p;  /* nodo da ricercare */

    (*contatore)++;
    for (nodo_p = radice_p;
	 (nodo_p != NULL) && (nodo_p -> valore != valore);
	(*contatore) += 3, nodo_p = (valore < nodo_p -> valore)?
	                             nodo_p -> sx_p:
		                     nodo_p -> dx_p);

    (*contatore)++;
    
    return (nodo_p);
}
