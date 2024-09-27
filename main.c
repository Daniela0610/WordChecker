#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 128
int count=0;

//tipo di dato  che contiene la lettera e la posizione in cui DEVE esserci o in cui NON PUò  esserci
typedef struct elemPos{
    char simbolo;
    int  position;
} elemPos;

//tipo di dato  che contiene la lettera e il numero di occorrenze della lettera nella parola
typedef struct elemOcc{
    char simbolo;
    int  occ;
} elemOcc;

//liste con elementi di tipo elemPos
typedef struct ListNodePos{
    elemPos data;
    struct ListNodePos* next;

} ListNodePos;

//liste con elementi di tipo elemPos
typedef struct ListNodeOcc{
    elemOcc data;
    struct ListNodeOcc* next;
} ListNodeOcc;

// tipo di dato che rappresenta un nodo nel binary search tree.

typedef struct BSTNode {
    char *word;
    struct BSTNode *dx;
    struct BSTNode *sx;
    struct BSTNode *parent;
    bool compatible; //to check if the word is still compatible with respect to the constraints
}BSTNode;

typedef struct puntNodo{
    BSTNode *nodo;
    struct puntNodo *next;
} puntNodo;

// funz per creare la radice del BST
typedef struct binary_search_tree {
    BSTNode *root;
}binary_search_tree;

// funzione per creare un nuovo nodo nell albero, alloco memoria ogni volta nell albero per un nodo
// e uso funzione strdup per allocare spazio e copiare
// la parola che deve essere contenuta in quel nodo.
BSTNode *new_node(char newParola[], bool compatible){
    BSTNode *temp=(BSTNode*)malloc(sizeof(BSTNode));
    temp->sx=NULL;
    temp->dx=NULL;
    temp->parent=NULL;
    temp->word= strdup(newParola);
    temp->compatible=compatible;
    return temp;
}
//aggiungo in testa alla lista che punta ai nodi del BST
 puntNodo *addtoListInTesta(puntNodo *head, BSTNode *node){
        if(head!=NULL){
          puntNodo *nodoSuccessivo= head;
            head= ( puntNodo*) malloc(sizeof(puntNodo));
            head->nodo=node;
            head->next= nodoSuccessivo;
        }else{
            head=(puntNodo*)malloc(sizeof(puntNodo));
            head->nodo=node;
            head->next=NULL;
        }
        return head;
    }
    //aggiungo in coda alla lista che punta ai nodi del BST
    puntNodo * addtoListIncoda(puntNodo *head, BSTNode *node){
        if(head!=NULL){
            puntNodo *nodoSuccessivo= head;
            while(nodoSuccessivo->next!=NULL){
                nodoSuccessivo=nodoSuccessivo->next;
            }
            nodoSuccessivo->next= addtoListInTesta(NULL,node);
        }
        else{
            head=addtoListInTesta(head,node);
        }
        return head;
}

ListNodePos * add_to_Pos(char simbolo, int position ,ListNodePos* head){
    if(head != NULL){
        ListNodePos * nodoSuccessivo = head;
        head = (ListNodePos *) malloc(sizeof(ListNodePos));
        head->data.simbolo=simbolo;
        head->data.position=position;
        head -> next = (struct ListNodePos *) nodoSuccessivo;
    }
    else{
        head = (ListNodePos *) malloc(sizeof(ListNodePos));
        head->data.simbolo=simbolo;
        head->data.position=position;
        head -> next = NULL;
    }
    return head;
}
//scorro lista per vedere se già c'è un nodo con il determinato simbolo
/*ListNodePos * add_to_Pos(char simbolo, int position ,ListNodePos* head){
    for( ListNodePos* itr=head; itr!=NULL; itr=itr->next){
        if(itr->data.simbolo==simbolo && itr->data.position==position){
         return head;}

    head=add_to_Pos(simbolo,position,head);
    return head;
    }
 DA QUA NON SERVE PIù SI PUò FERMARE SOPRA
    else {
      while( head->next!=NULL || head->data.simbolo!=simbolo){
          head=head->next;
      }
    }
    if(head->data.simbolo==simbolo && head->data.position!=position){
        // se ho già un carattere uguale ma con posizione diversa, creo un altro nodo
        head= add_to_headPos(simbolo,position,head);
        return head;
    }
    else if(head->data.simbolo==simbolo && head->data.position==position){
        // se ho già un carattere uguale con la stessa posizione, non faccio nulla
        return head;
    } //non c'è quel carattere nella lista
    else {
        head= add_to_headPos(simbolo,position,head);
        return head;
    }


}*/

ListNodeOcc* add_to_headOcc(char simbolo, int occurrences ,ListNodeOcc* head){
    if(head != NULL){
        ListNodeOcc * nodoSuccessivo = head;
        head = (ListNodeOcc *) malloc(sizeof(ListNodeOcc));
        head->data.simbolo=simbolo;
        head->data.occ=occurrences;
        head -> next = (struct ListNodeOcc *) nodoSuccessivo;
    }
    else{
        head = (ListNodeOcc *) malloc(sizeof(ListNodeOcc));
        head->data.simbolo=simbolo;
        head->data.occ=occurrences;
        head -> next = NULL;
    }
    return head;
}
//funzione per liberare una lista
void freeListPos(ListNodePos *head) {
    ListNodePos * tmp;
    while (head!= NULL) {
        tmp=head;
        head=head->next;
        free(tmp);
    }
}
void freeListaSup(puntNodo *head) {
    puntNodo * tmp;
    while (head!= NULL) {
        tmp=head;
        head=head->next;
        free(tmp);
    }
}
void freeListOcc(ListNodeOcc *head) {
    ListNodeOcc * tmp;
    while (head!= NULL) {
        tmp=head;
        head=head->next;
        free(tmp);
    }
}
/*puntNodo * removeNodoLista( puntNodo *head, puntNodo *nodoDaEliminare){

    puntNodo *tmp=head;
    puntNodo *tmp2=head;
    if(head==nodoDaEliminare){
        head=head->next;
        free(tmp);
        return head;
    }
    while(tmp!=NULL){
        if(tmp==nodoDaEliminare){
            tmp2->next=tmp->next;
            free(tmp);
            return head;
        }
        tmp2=tmp;
        tmp=tmp->next;
    }
    return head;
}*/

binary_search_tree* new_binary_search_tree() {
    binary_search_tree *t = (binary_search_tree *)malloc(sizeof(binary_search_tree));
    t->root = NULL;
    return t;
}
//funzione per fare compare tra due stringhe
int stringcmp(const char *s1, const char *s2){
    while(*s1 &&*s1==*s2){
        s1++; s2++;}
    return *(const unsigned char*)s1-*(const unsigned char*)s2;
}
// restituisce il minimo dell albero , facendo partire l 'iterazione della radice
BSTNode* minimum(binary_search_tree *t, BSTNode *x) {
    while(x->sx != NULL)
        x = x->sx;
    return x;
}
// ritorna il successore nell albero di un determinato nodo che gli passo in input
BSTNode * successorOfTheNode (binary_search_tree *t, BSTNode*x){
    if(x->dx!=NULL){
        return minimum(t, x->dx);
    }
    BSTNode *y=x->parent;
    while(y!=NULL && x==y->dx){
        x=y;
        y=y->parent;
    }
    return y;
}
//inserimento di un nodo nell albero, prestando attenzioe all ordine, le parole devono essere inseriti in ordine lessicografico.
void insertNewNode(binary_search_tree *t, BSTNode *n) {
    BSTNode *y = NULL;
    BSTNode *temp = t->root;
    while(temp != NULL) {
        y = temp;
        if(stringcmp(n->word, temp->word) < 0)
            temp = temp->sx;
        else
            temp = temp->dx;
    }
    n->parent = y;

    if(y == NULL) //newly added BSTNode is root
        t->root = n;
    else if(stringcmp(n->word, y->word) < 0)
        y->sx = n;
    else
        y->dx = n;
}

//per stampare in modo iterativo con boolean 'compatible' a true
//usata nel momento in cui ricevo da file il comando 'stampa_filtrate' e stampa tutte le parole che sono ancora compatibili fino a quel momento
// con i vincoli appresi
/*void inOrderIterative(binary_search_tree *t, BSTNode *n) {
    BSTNode *curr= minimum(t, n);
    while(curr!=NULL){
        if(curr->compatible == true)
        {printf("%s", curr->word);}
        curr= successorOfTheNode(t, curr);
    }
}*/
//versione ricorsiva della funzione di sopra,
/*void inOrderRecursive(binary_search_tree *t, BSTNode *n){
    if(n!=NULL){
        inOrderRecursive(t, n->sx);
        if(n->compatible ==true){
        printf("%s",n->word);}
        inOrderRecursive(t, n->dx);
    }
}*/
// risetta a tutti i nodi il flag 'compatibile' a true dopo la fine di una partita.
/*void inorderFlag(binary_search_tree *t, BSTNode *n) {
    BSTNode *curr= minimum(t, n);
    while(curr != NULL) {
        curr->compatible=true;
        curr= successorOfTheNode(t, curr);
    }
}*/
/*void inOrderIterativa(binary_search_tree *t, BSTNode *n){
    BSTNode *curr= minimum(t, n);
    while(curr!=NULL){
        printf("%s",curr->word);
        curr= successorOfTheNode(t, curr);
}
}*/

// ricerca se una parola esiste nel dizionario, perchè ogni volta che ricevo in input una parola da confrontare
//bisogna verificare che esista nel dizionario , se non esiste stampo in output' not_exists'
BSTNode* search_word_in_tree(BSTNode *n, char parola[]) {
    while(n!=NULL){
        if(stringcmp(n->word, parola) == 0)
            return n;
        else if(stringcmp(parola,n->word) < 0)
            return search_word_in_tree(n->sx, parola);
        else
            return search_word_in_tree(n->dx, parola);
    }
    return NULL;
}


//conta quante volte il char 'elem' compare nella parola
int occorrenza(char parola[], char elem, int lenParola)
{  int count=0;
    for(int i=0;i<lenParola;i++) {
        if (parola[i] == elem)
            count++;
    }
    return count;
}
//This function is used to fitrate le parole nell'albero.
//ho 4 liste:
//mustBeInThisPosition: ogni nodo contiene una lettera e la posizione in cui deve esserci
//cantBeInThisPositione:  ogni nodo contiene una lettera e la posizione in cui NON può esserci
//atLeastOcc: ogni nodo contiene una lettera e il numero di occorrenze della lattera che deve esserci(almeno n volte)
//exactOcc: ogni nodo contiene una lettera e il numero di occorrenze della lattera che deve esserci(ESATTAMENTE n volte)
//Data la parola in input, scorro tutte le liste per verificare che la specifica parola rispetti i vincoli memorizzati nelle liste
// non appena si verifica che non rispetta un vincolo, esce dalla funzione e ritorna 'true', ovvero che è da eliminare, altrimenti dopo aver
// fatto lo scorriemnto su tutte le liste e aver verificato che rispetta tutti i vincoli ritorna false, cioè non è da eliminare ed è ancora buona
bool toEliminate(char word[], int wordLenght, ListNodePos *mustBeInThisPosition, ListNodePos *cantBeInThisPosition, ListNodeOcc *atLeastOcc, ListNodeOcc *exactOcc){
    if(mustBeInThisPosition!=NULL){
            while(mustBeInThisPosition!=NULL){
                if(word[mustBeInThisPosition->data.position] != mustBeInThisPosition->data.simbolo){
                return true;
            }else{
                mustBeInThisPosition = mustBeInThisPosition->next;
            }
        }
    }

    if(cantBeInThisPosition!=NULL) {
            while (cantBeInThisPosition != NULL) {
                if (word[cantBeInThisPosition->data.position] == cantBeInThisPosition->data.simbolo) {
                    return true;
                } else {
                    cantBeInThisPosition = cantBeInThisPosition->next;
                }
            }
    }

    if(atLeastOcc!=NULL) {
            while (atLeastOcc != NULL) {
                if (occorrenza(word, atLeastOcc->data.simbolo, wordLenght) < atLeastOcc->data.occ) {
                    return true;
                } else {
                    atLeastOcc = atLeastOcc->next;
                }
            }
    }

    if(exactOcc!=NULL) {
            while (exactOcc != NULL) {
                if (exactOcc->data.occ != occorrenza(word, exactOcc->data.simbolo, wordLenght)) {
                    return true;
                } else {
                    exactOcc = exactOcc->next;
                }
            }
    }
        return false;

}
puntNodo * rimuovi_in_testa(puntNodo* testa){
    if(testa != NULL){
        puntNodo* daEliminare = testa;
        testa = testa -> next;
        free(daEliminare);
    }
    return testa;
}
//scorro la lista dei puntatori ed elimino nodi non compatibili
puntNodo *NumberOfLeftWords(puntNodo *head, int wordLenght, ListNodePos *mustBeInThisPosition, ListNodePos *cantBeInThisPosition, ListNodeOcc *atLeastOcc, ListNodeOcc *exactOcc){
    puntNodo *tmp2=NULL;
   puntNodo *iter=head;
   while(iter!=NULL){
       if(toEliminate(iter->nodo->word, wordLenght, mustBeInThisPosition, cantBeInThisPosition, atLeastOcc, exactOcc)==true){
           if(tmp2==NULL){
               head=rimuovi_in_testa(head);
               iter=head;
           }
           else{
               tmp2->next=iter->next;
               free(iter);
               iter=tmp2->next;}

       }
       else {
           count ++;
           tmp2=iter;
           iter=iter->next;}
   }
  return head;
}
//a partire da una posizione data in input tramite la variabile position, cerco un occorrenza nella parte destra
// di quella lettera nella parola. se non trova nessuna occorrenza ritorna -1
int SearchLetterIntheWord(char r[], char elem, int position, int wordLenght)
{
    while(position <= wordLenght - 1) {
        if(r[position] == elem){
            return position;
        }
        else if(position == wordLenght - 1 && r[position] != elem) {
            position = -1;
            return position;
        }
        position++;
    }
    return -1;
}
//It compares 2 words, according to the game's rules. memorizzo l'output nell'array di char out

char* Comparison2Words(char v[], char t[], char out[], int lenParola)
{   int k=lenParola;
    char v2[lenParola+5];
    strcpy(v2,v);
    int pos;
    for(int i=0; i<k;i++)
    {
        if (t[i] == v2[i])
        {
            v2[i]='*';
            out[i]='+';
        } else
        {
            pos = SearchLetterIntheWord(v2, t[i], 0, k);
            while(pos!=-1)
            {
                if(v2[pos]==t[pos])
                {
                    pos= SearchLetterIntheWord(v2, t[i], pos + 1, k);
                }
                else
                {
                    v2[pos]='*';
                    out[i]='|';
                    break;
                }

            }
            if(pos==-1)
            {
                out[i] = '/';
            }
        }
    } out[lenParola]='\0';
    return out;
}
void stampaFiltrate(puntNodo* node){
    while(node!=NULL){
        printf("%s", node->nodo->word);
        node=node->next;
    }
}
//funzione per ricreare la lista che punta ai nodi dell'albero dopo ogni partita.
puntNodo *ricreaLista(puntNodo *head, binary_search_tree *t, BSTNode *n){
    BSTNode *curr= minimum(t,n);
    while(curr!=NULL){
        if(curr->compatible==true){
            head= addtoListIncoda(head,curr);
        }
        curr= successorOfTheNode(t, curr);
    }
    return head;
}
int main() {
    binary_search_tree *t = new_binary_search_tree(); // nuovo albero
    char buffer[INF], *bufferPtr,c;
    int wordLength = 0, leftAttempts = 0, nrOfWordsAdmissible, pos, k=0;
    bool insertionOutOfRound, ItIs=false; //ItIs è un boolean utilizzato quando si apprendono i vincoli: nel momento in cui
    // abbiamo un simbolo '/' in output per un determinato carattere significa che si è raggiunto il numero esatto di occorrenze di quel carattere
    puntNodo * listSup= NULL;
    //contains the letter and the position in which it must be
    ListNodePos *letterMustBeInThisPos = NULL;
    //contains the letters that can t be at all in the word
    ListNodePos *letterCantBeInThisPosition = NULL;
    // cotains the minimum number of a letter occurrences that must be in the word
    ListNodeOcc *atLeastNumberOfOccurrences = NULL;
    // cotains the exact number of a letter occurrences that must be in the word
    ListNodeOcc *exactNumberOfOccurrences = NULL;

    // la prima riga del file contiene il numero che indica la lunghezza delle parole
    while(c!='\n'){
        c=getchar_unlocked();
        buffer[k]=c;
        k++;
    }
    wordLength=atoi(buffer);
    char outputString[wordLength + 1], referenceWord[wordLength + 1], wordToCompare[wordLength + 1];
    // qua inizio a memorizzare le parole del dizionario.
    // continuo finchè non arriva il comando di stampa filtrate oppure di inserimento di nuove parole( non ne capisco qua il senso ma
    //a quanto pare ci può essere nei test non pubblici)
    while (fgets(buffer, INF, stdin) != NULL) {
        if (stringcmp(buffer, "+nuova_partita\n") == 0) {
            insertionOutOfRound=false;
            break;
        }

        else if (stringcmp(buffer, "+inserisci_inizio\n") == 0) {
            while (fgets(buffer, INF, stdin) != NULL) {
                if (stringcmp(buffer, "+inserisci_fine\n") == 0) {
                    break;
                } else {
                    BSTNode *z = new_node(buffer,true);
                    insertNewNode(t, z);
                    //listSup= addtoList(listSup, z);
                }
            }
        } else {
            BSTNode *z = new_node(buffer,true);
            insertNewNode(t, z);

        }
    }
    //creo la lista
    listSup= ricreaLista(listSup,t,t->root);
    // qua ci arrivo perchè comincia una nuova partita. copio la parola di riferimento in un array per averla sempre a disposizione
    bufferPtr = fgets(buffer, INF, stdin);
    if (bufferPtr != NULL) {
        memcpy(referenceWord,buffer,sizeof(referenceWord));
    }
    // poi subito dopo arriva il numero di tentativi
    bufferPtr = fgets(buffer, INF, stdin);
    if (bufferPtr != NULL) {
        leftAttempts = atoi(buffer);
    }
    //when the round starts there are differents options.
    // durante una partita possono succedere diverse cose: possono arrivare nuove parole che devono rispettare i vincoli, può essere chiesto
    // di stampare le filtrate oppure si deve semplicemente confrontare la parola che arriva con quella di riferimento e dire quante
    // parole sono compatibili
    while (fgets(buffer, INF, stdin) != NULL) {
        if (stringcmp(buffer, "+nuova_partita\n") == 0) {
            bufferPtr = fgets(buffer, INF, stdin);
            if (bufferPtr != NULL) {
                memcpy(referenceWord,buffer,sizeof(referenceWord));
            }
            bufferPtr = fgets(buffer, INF, stdin);
            if (bufferPtr != NULL) {
                leftAttempts = atoi(buffer);
            }
            // ad ogni nuova partita svuote le liste perchè ogni partita  ha dei nuovi vincoli
            freeListPos(letterMustBeInThisPos);
            freeListOcc(atLeastNumberOfOccurrences);
            freeListPos(letterCantBeInThisPosition);
            freeListOcc(exactNumberOfOccurrences);
            freeListaSup(listSup);

            // rimetto i puntatori alla lista al NULL
            letterMustBeInThisPos= NULL;
            letterCantBeInThisPosition = NULL;
            atLeastNumberOfOccurrences = NULL;
            exactNumberOfOccurrences = NULL;
            listSup=NULL;
            listSup= ricreaLista(listSup,t,t->root);
            // NB: se l'inserimento è fuori partita non ci sono vincoli da rispettare quindi vanno bene tutte
            insertionOutOfRound = false;

        } // qua gestisco l'opzione di inserisic inizio , sia dentro che fuori partita.
            // finchè non mi arriva il comando di inserisci fine vai avanti e ricevi le parole
        else if (stringcmp(buffer, "+inserisci_inizio\n") == 0) {
            while (fgets(buffer, INF, stdin) != NULL) {
                if (stringcmp(buffer, "+inserisci_fine\n") == 0) {
                    break;
                } else {
                    if(insertionOutOfRound == false){
                        BSTNode *u = new_node(buffer,true);
                        insertNewNode(t, u);
                        //listSup=addtoList(listSup,u);
                    }
                    else { // qua gestisco inserimento dentro partita, se la parola non rispetta i vincoli la aggiungo al dizionario con il boolean true, che sta ad indicare che la parola non va bene
                        if(toEliminate(buffer, wordLength, letterMustBeInThisPos, letterCantBeInThisPosition,
                                       atLeastNumberOfOccurrences, exactNumberOfOccurrences) == true){
                            BSTNode *e = new_node(buffer,false);
                            insertNewNode(t, e);}
                        else
                        {    BSTNode *e = new_node(buffer,true);
                            insertNewNode(t, e);
                           // listSup=addtoList(listSup,e);}
                    }
                }
            }
       }   free(listSup);
            listSup=NULL;
            listSup= ricreaLista(listSup,t,t->root);
        } else if (stringcmp(buffer, "+stampa_filtrate\n") == 0) {
            stampaFiltrate(listSup);
        } else { //arriva word da confrontare
            strcpy(wordToCompare, buffer);
            // se la parola non esiste nel dizionario scrivo su stdout 'not_exists'
            if (search_word_in_tree(t->root, wordToCompare) == NULL) {
                puts("not_exists");
            } else if (stringcmp(wordToCompare, referenceWord) == 0) {
                puts("ok");
                // dopo ok finisce la partita quindi rimetto a true che se qua il prossimo comando è inserisci_inizio allora so che è fuori partita
                insertionOutOfRound = true;
            } else {
                char *out1 = Comparison2Words(referenceWord, wordToCompare, outputString, wordLength);
                //la stringa fatta tutta di più non la devo stampare, perchè ci metto ok
                for (int n = 0; n < wordLength; n++) {
                    if (out1[n] != '+') {
                        puts(outputString);
                        break;
                    }
                }
                //parte che viene eseguita dopo ogni confronto, perchè dopo ogni confronto ho vincoli da aggiungere
                for (int i = 0; i < wordLength; i++) {
                    ItIs=false;
                    int occorrenze = 0;
                    if (wordToCompare[i] != '*') {
                        pos = SearchLetterIntheWord(wordToCompare, wordToCompare[i], i + 1, wordLength);
                        if (pos == -1) {
                            if (out1[i] == '+') {
                                letterMustBeInThisPos = add_to_Pos(wordToCompare[i], i,letterMustBeInThisPos);
                            } else if (out1[i] == '|') {
                                atLeastNumberOfOccurrences = add_to_headOcc(wordToCompare[i],  1, atLeastNumberOfOccurrences);
                                letterCantBeInThisPosition = add_to_Pos(wordToCompare[i], i, letterCantBeInThisPosition);

                            } else if (out1[i] == '/') {
                                exactNumberOfOccurrences = add_to_headOcc(wordToCompare[i], 0,  exactNumberOfOccurrences);
                            }

                        } else {
                            if (out1[i] == '+') {
                                occorrenze++;
                                letterMustBeInThisPos = add_to_Pos(wordToCompare[i], i,letterMustBeInThisPos);
                            } else if (out1[i] == '|') {
                                occorrenze++;
                                letterCantBeInThisPosition = add_to_Pos(wordToCompare[i], i, letterCantBeInThisPosition);
                            } else if(out1[i] == '/'){
                                ItIs = true;
                                occorrenze=0;
                            }
                            while (pos != -1) {

                                if (out1[pos] == '+') {
                                    occorrenze++;
                                    letterMustBeInThisPos = add_to_Pos(wordToCompare[pos], pos,letterMustBeInThisPos);
                                } else if (out1[pos] == '|') {
                                    occorrenze++;
                                    letterCantBeInThisPosition = add_to_Pos(wordToCompare[pos], pos, letterCantBeInThisPosition);
                                } else if(out1[pos]=='/'){
                                    letterCantBeInThisPosition = add_to_Pos(wordToCompare[pos], pos, letterCantBeInThisPosition);
                                    ItIs=true;
                                }
                                wordToCompare[pos] = '*';
                                pos = SearchLetterIntheWord(wordToCompare, wordToCompare[i], pos + 1, wordLength);
                            }
                            if (ItIs == false) {
                                atLeastNumberOfOccurrences = add_to_headOcc(wordToCompare[i], occorrenze, atLeastNumberOfOccurrences);
                            } else  {
                                exactNumberOfOccurrences = add_to_headOcc(wordToCompare[i], occorrenze, exactNumberOfOccurrences);
                            }
                        }
                    }
                }
                // subito dopo che confronto devo scrivere su stdout nr di parole rimastev
                listSup = NumberOfLeftWords(listSup, wordLength, letterMustBeInThisPos,
                                                        letterCantBeInThisPosition, atLeastNumberOfOccurrences, exactNumberOfOccurrences);
                printf("%d\n", count);
                count=0;
                //controllo tentativi
                leftAttempts--;
                if (leftAttempts == 0)
                    puts("ko"); // se finisco i tentativi finisce la partita e scrivo su stdout ko
                insertionOutOfRound = true;

            }
        }
    }
    return 0;
}

