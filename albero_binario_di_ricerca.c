#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct nodo_albero_bin  /* struttura dati: albero binario di ricerca */
{
 int                    valore;
 char                   *stringa;
 struct nodo_albero_bin *sx_p, *dx_p;
} nodo_albero_bin_t;


int  acquisizione_n      (void);

void  inserimento_albero (nodo_albero_bin_t **radice_p,
		          int               valore,
		 	  char              *stringa);

int  selezione_visita    (void);

void visita_anticipata   (nodo_albero_bin_t *nodo_p);

void visita_simmetrica   (nodo_albero_bin_t *nodo_p);

void visita_posticipata  (nodo_albero_bin_t *nodo_p);

int  selezione_ricerca   (void);

nodo_albero_bin_t * ricerca_elemento (nodo_albero_bin_t *radice_p,
		                      int               valore);


int main (void)
{
    int               n,           /* input: numero per la generazione casuale dei valori */
		      i,
		      j,
	              k,           /* variabili contatore */
		      doppione,    /* variabile di controllo valori uguali */
                      visita,      /* variabile di selezione della visita */ 
	              ricerca;     /* variabile di selezione della ricerca */

    int               *chiavi;     /* array delle chiavi numeriche */

    char              **stringhe;  /* array bidimensionale delle stringhe */

    nodo_albero_bin_t *radice,     /* input: albero binario di ricerca */
		      *nodo_r;     /* nodo della ricerca */

    
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
		             stringhe[i]);
         }

    visita = selezione_visita();                      /* selezione della visita */

    if (visita == 1)                                  /* output: stampa a video dei dati */ 
       {
        printf("Visita in ordine anticipato:\n\n");
        visita_anticipata(radice);
       }
    else if (visita == 2)
       {	    
        printf("Visita in ordine simmetrico:\n\n");
        visita_simmetrica(radice);
       }
    else if (visita == 3)
       {	
        printf("Visita in ordine posticipato:\n\n");	    
        visita_posticipata(radice);
       }
    
    /* output: stampa dei dati ordinati secondo la chiave numerica */
    printf("\nVisualizzazione dei dati secondo la chiave numerica:\n\n"); 
    visita_simmetrica(radice);

    ricerca = selezione_ricerca();

    nodo_r = ricerca_elemento(radice, 
		              ricerca);  /* output: ricerca di un elemento */

    if (nodo_r != NULL)
       {
        printf("L'elemento è presente nell'albero binario.\n");
        printf("Stringa associata all'elemento ricercato: %s\n",
	       nodo_r -> stringa);
       }
    else
       printf("L'elemento non è presente nell'albero binario.\n");

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


void  inserimento_albero (nodo_albero_bin_t **radice_p,
		          int               valore,
			  char              *stringa)
{   
    nodo_albero_bin_t *nodo_p,
		      *padre_p,
		      *nuovo_p;

    for (nodo_p = padre_p = *radice_p;
	 (nodo_p != NULL) && (nodo_p -> valore != valore);
        padre_p = nodo_p, nodo_p = (valore < nodo_p -> valore)?
	                            nodo_p -> sx_p:
				    nodo_p -> dx_p);

    if (nodo_p == NULL)
    {	    
      nuovo_p = (nodo_albero_bin_t *)malloc(sizeof(nodo_albero_bin_t));
      nuovo_p -> valore = valore;
      nuovo_p -> stringa = stringa;               /* inserimento dei valori */
      nuovo_p -> sx_p = nuovo_p -> dx_p = NULL;
      if (nodo_p == *radice_p)
         *radice_p = nuovo_p;
      else
         if (valore < padre_p -> valore)
	     padre_p -> sx_p = nuovo_p;
	 else
	     padre_p -> dx_p = nuovo_p;
    } 
}


int selezione_visita (void)
{
    int visita,          
	esito_lettura;  /* variabile per la validazione */

    do
    {
    printf("Inserire 1 per la visita in ordine anticipato, 2 per la visita in ordine simmetrico e 3 per la visita in ordine posticipato.\n");
    esito_lettura = scanf("%d",
	                  &visita);
    if (esito_lettura != 1 || (visita <= 0) || (visita > 3))
           printf("Input non accettabile!\n");
       while (getchar() != '\n');
      }
    while (esito_lettura != 1 || (visita <= 0) || (visita > 3));

    printf("\n");  
    
    return (visita);
}


void visita_anticipata (nodo_albero_bin_t *nodo_p)
{
    if (nodo_p != NULL)
    {
     printf("%d %s\n",
            nodo_p -> valore,		     
	    nodo_p -> stringa);
     visita_anticipata(nodo_p -> sx_p);
     visita_anticipata(nodo_p -> dx_p);
    }
}


void visita_simmetrica (nodo_albero_bin_t *nodo_p)
{
    if (nodo_p != NULL)
    {
     visita_simmetrica(nodo_p -> sx_p);
     printf("%d %s\n",
            nodo_p -> valore,		     
	    nodo_p -> stringa);
     visita_simmetrica(nodo_p -> dx_p);
    }
}


void visita_posticipata (nodo_albero_bin_t *nodo_p)
{
    if (nodo_p != NULL)
    {
     visita_posticipata(nodo_p -> sx_p);
     visita_posticipata(nodo_p -> dx_p);
     printf("%d %s\n",
            nodo_p -> valore,		     
	    nodo_p -> stringa);
    }
}


int selezione_ricerca (void)
{
    int ricerca,        
	esito_ricerca;  /* variabile di validazione */

    do    
      {
       printf("\nDigita la chiave numerica dell'elemento da ricercare.\n");
       esito_ricerca = scanf("%d",
                             &ricerca);
       if (esito_ricerca != 1 || ricerca < 0)
           printf("Input non accettabile!\n");
       while (getchar() != '\n');
      }
    while (esito_ricerca != 1 || ricerca < 0);

    return (ricerca);
}



nodo_albero_bin_t * ricerca_elemento (nodo_albero_bin_t *radice_p,
				      int               valore)
{
    nodo_albero_bin_t *nodo_p;  /* nodo da ricercare */

    for (nodo_p = radice_p;
	 (nodo_p != NULL) && (nodo_p -> valore != valore);
	nodo_p = (valore < nodo_p -> valore)?
	         nodo_p -> sx_p:
		 nodo_p -> dx_p);
    
    return (nodo_p);
}
