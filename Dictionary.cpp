#include "Dictionary.h"


Node::Node(char s, int ctr , int lvl , std::string prx, bool val) : sym(s), counter(ctr)
    , level(lvl) , prefix(prx), next(NULL) , child(NULL){}

Node::Node() {};


void print_node(pNode p)
{
    if(p)
    {
    cout << "\n========NODO =========\n";
    cout << "prefix :" << p->prefix <<"\n";
    cout << "char  :" << p->sym << "\n";
    cout << "counter  :" << p->counter << "\n";
    cout << "level  :" << p->level << "\n";
    cout << "\n=======================\n";
    }
    else
    {
        cout << "\n========NODO =========\n";
        cout << "       EMPTY NODE        \n";
        cout << "\n=======================\n";
    }
}



WordDictionary::WordDictionary()
{
     total=0;
     max_branching_factor=0;
}

/*
    Private functions
*/

int WordDictionary::get_total()
{
	return total;
}


void WordDictionary::set_total()
{
	total++;
}

int WordDictionary::get_branching()
{
    return max_branching_factor;
}

int WordDictionary::get_branching_factor()
{

    return get_branching();

}


pNode WordDictionary::add_r_word(pNode root, int lvl, int branching , std::string word, std::string prefix,bool h)
{
        int w_size=word.size();
        std::string new_prefix;
        if(lvl<w_size-1) // se arrivo alla fine della parola restituisco root e concludo la ricorsi
        {
            char to_insert = word[lvl];
            if(root==NULL) // se sono in un nodo nullo lo aggiungo
            {
                //cout << "nuovo nodo : carattere da inserire " << to_insert  << "lvl :" << lvl << "\n \n";
                root= new Node(to_insert,1,lvl, prefix, h);
                new_prefix= prefix + to_insert ;
                root->child=add_r_word(root->child,++lvl, 1,word, new_prefix , true );

            }
            else
            {
                if(root->sym==to_insert) //  caso in cui matcha il carattere della stringa con quello nell'albero
                {                        //  esiste già una parola con quel prefisso

                    root->counter++;
                    new_prefix= prefix + to_insert ; // aggiorno il prefisso per i nodi a livelli piu bassi
                    root->child=add_r_word(root->child,++lvl, 1 ,word, new_prefix , h);

                }
                else
                {

                    root->next=add_r_word(root->next,lvl, ++branching ,word,prefix, false); // esegue una ricerca sui fratelli
                    if(branching>max_branching_factor)
                    {
                        max_branching_factor=branching;
                    }
                    pNode actual=root;
                    pNode next_childs=root->next->next;

                    if (root->counter < root->next->counter) // eseguo uno swap nel caso in cui il fratello risulta
                    {                                        // avere probabilità piu ampia
                        root=root->next;
                        root->next=actual;
                        root->next->next=next_childs;
                    }
                }
            }
        }
        //cout << "\n Load :" << word << "\n";
        return root;



}

pNode WordDictionary::search_path(pNode root,std::string prefix, int current_level)
{
    pNode p;


    if(prefix.compare("")==0) // caso stringa vuoto restituisco i nodi a livello 0 piu probabili
    {
        p=root;
    }
    else
    {
        int size_prefix=prefix.size();
        if (current_level==size_prefix-1) // se raggiungo l'ultimo livello e il caratteree non matcha =>
        {
            if(root==NULL)
            {
                return NULL; // non esiste quel prefisso (o quella parola)
            }
            else
            {

                if(root->sym==prefix[current_level]) //
                {
                    return root; // restituisco il nodo , matcha con il prefisso in input
                }
                else
                {
                    p=search_path(root->next,prefix,current_level); // ricerca sui fratelli
                }
            }

        }
        else // caso livelli intermedi
        {
            if(root==NULL)
            {
                return NULL;
            }
            else
            {
                if(root->sym==prefix[current_level]) // carattere i del prefisso matcha con un nodo
                {
                    p=search_path(root->child,prefix,++current_level);
                }
                else // ricerca sui fratelli del root a livello current_level
                {
                    p=search_path(root->next,prefix,current_level);
                }
            }
        }

    }
    return p;
}


/*
    Restituisco  i primi MAX_NUM_CHILDS nodi figli del nodo p
*/

pNode * WordDictionary::possibilities(pNode p)
{
    pNode * possibilities = new pNode[MAX_NUM_CHILDS];
    pNode * it = &(p->child);
    int j=0;
    bool empty_node=true;
    bool max_int=true;
    while((empty_node=(*it!=NULL))==true && (max_int=(j<MAX_NUM_CHILDS))==true)
    {
        possibilities[j]=*it;

        it=&((*it)->next);
        j++;
    }


    if(j==MAX_NUM_CHILDS-1 && *it==NULL) // inizializza il resto dell'array se esistono un numero di figli
    {                                    // MAX_NUM_CHILDS -1
        possibilities[j]=NULL;

    }


    if(j<MAX_NUM_CHILDS-1) // inizializza il resto dell'array in caso di numero di figli < MAX_NUM_CHILDS-1
    {

        while(j<MAX_NUM_CHILDS)
        {
            possibilities[j]=NULL;
            j++;
        }

    }

    return possibilities;
}



/*
    Public functions
*/

int WordDictionary::total_word()
{
    return get_total();
}


void WordDictionary::add_word(std::string word)
{
    root=add_r_word(root,0, 1 ,word,"",true);
    total++;
}

void WordDictionary::view()
{
    print_dictionary(root);

}


void WordDictionary::entropy(int max_level)
{
    dictionary_entropy(root,max_level);

}





// Stampa dei nodi piu probabili su terminale

void WordDictionary::print_most_prob_chars(std::string prefix)
{
    cout << "\n=========MOST CHARACTER=========== \n";

    cout << "\n Choose for prefix : " << prefix << "\n" ;

    pNode p=search_path(root,prefix,0);
    if(p)
    {
        int i=0;
        pNode * character=possibilities(p);

        while(character[i]!=NULL && i<MAX_NUM_CHILDS)
        {
            print_node(character[i]);
            cout << "Select : "<< i+1 <<"- char : " << character[i]->sym << " counter : " << character[i]->counter << "\n" ;
            i++;
        }
    }
    else
    {
        cout << "None words with this prefix \n";

    }

    cout <<"\n=========MOST CHARACTER=========== \n";

}

// stampa dei caratteri piu probabili usando ncurses

void WordDictionary::w_print_most_prob_chars(std::string prefix)
{
    printw("\n=========MOST CHARACTER=========== \n");
    char *a=new char[prefix.size()+1];
    a[prefix.size()]=0;
    memcpy(a,prefix.c_str(),prefix.size());

    printw("\n Choose for prefix : %s \n", a);

    pNode p=search_path(root,prefix,0);
    if(p)
    {
        int i=0;
        pNode * character=possibilities(p);

        while(character[i]!=NULL && i<MAX_NUM_CHILDS)
        {
            printw("n Select : %d - char : %c - counter : %d \n" ,i+1, character[i]->sym,character[i]->counter) ;
            i++;
        }
    }
    else
    {
        printw("None words with this prefix \n");

    }

    printw("\n=========MOST CHARACTER=========== \n");

}


/*
    Calcolo dell'entropia del dizionario
    viene passato il nodo iniziale e il massimo del valore del livello in cui eseguire il calcolo
    l'Algoritmo di calcolo esegue una visita in ampiezza per mezza di una coda implementata
    mediante linked listt
*/



void WordDictionary::dictionary_entropy(pNode p, int max_level)
{
    if (p==NULL)
    {
        cout << "EMPTY DICTIONARY";
        return;

    }

    Level_Queue * Q = new Level_Queue();
    pNode * r;
    r=&(p);

    // Inizialize with first list of tree

    double en = 0;
    int actual=0;
    double prob = 0;
    double d_total=(double)total;
    double d_child_counter;
    double * entropies=new double[max_level]();

    while(*r!=NULL)
    {
        Q->add(*r);
        d_child_counter=(double)(*r)->counter;
        prob=d_child_counter/d_total;
        //cout << " char : " << (*r)->sym << " -  Prob : " << prob << " total "<< d_total << "\n";
        entropies[(*r)->level] += prob*log2f(1/prob);
        r=&((*r)->next);
    }


    cout << "\n Entropy Level " << actual << " value " << entropies[0] <<" bits \n";
    actual++;


    en=0;


    while(!(Q->isEmpty()) )
    {

        pNode tmp=Q->get_first();
        double tmp_counter=(double)(tmp->counter);

        if (tmp->level==actual+1) // tmp is part of next level
        {
            cout << "\n Entropy Level " << actual << " value " << entropies[actual] <<" bits \n";
            actual++;
            en=0;
        }


        if(tmp->child!=NULL && tmp->child->level <= max_level) // calcolo entropia sui figli del nodo tmp corrente
        {                                                      // espansione del nodo p solo se il numero di figli
            double char_entropy=0;                             // risulta <= max_level
            r=&(tmp->child);
            std::string prefix=(*r)->prefix;
            int child_level=(tmp->child->level);

            while(*r!=NULL) // visita dei figli di tmp
            {
                Q->add(*r);
                d_child_counter=(double)(*r)->counter;
                prob=d_child_counter/tmp_counter;
                char_entropy += (prob)*log2f(1/prob);
                r=&((*r)->next);
            }


            entropies[child_level] += (tmp_counter/d_total)*char_entropy;

        }

        // after childs add i remove elem from queue

        pNode first=Q->extract();
        usleep(2);
    }

    double dictionary_en=0;

    for(int i=0;i<max_level;i++)
    {
        dictionary_en +=entropies[i];
    }

    cout << "\n Entropy Level " << actual << " value " << entropies[actual] <<" bits \n";
    cout << "\n Entropy All dictionary " << dictionary_en << "bits \n " ;

}




void WordDictionary::print_dictionary(pNode p)
{
    if (p==NULL)
    {
        cout << "EMPTY DICTIONARY";
        return;

    }

    Level_Queue * Q = new Level_Queue();
    pNode * r;
    r=&(p);

    // Inizialize with first list of tree

    while(*r!=NULL)
    {
        Q->add(*r);
        r=&((*r)->next);
    }



    while(!(Q->isEmpty()))
    {
        pNode tmp=Q->get_first();

        // Add to queue direct child list of first queue elem

        if(tmp->child!=NULL)
        {
            r=&(tmp->child);
            while(*r!=NULL)
            {
                Q->add(*r);
                r=&((*r)->next);
            }

            usleep(1);

        }

        // after childs add i remove elem from queue

        pNode first=Q->extract();
        print_node(first);

    }
}


/*
    Tastiera predittiva , visualizza i nodi piu probabili in base ai caratteri selezionati
    La funzione keyboard utilizza ncurses per generare
*/

void WordDictionary::keyboard()
{

    initscr();
    keypad(stdscr, TRUE);


    printw("=========TEST KEYBOARD========== \n \n");
    string prefix = "";
    bool flag=true;
    while(flag)
    {
        char *a=new char[prefix.size()+1];
        a[prefix.size()]=0;
        memcpy(a,prefix.c_str(),prefix.size());

        int dim=prefix.size();
        char c='\0';
        int ch=getch();

        //printw("pressed key %d", ch);
        switch(ch)
        {
            case 10: //  exit
                clear();
                w_print_most_prob_chars(prefix);
                break;
            case 27 : // esc
                printw("press EXIT \n");
                flag=false;
                break;
            case 32 : // space
                clear();
                break;
            case 263 : // backspace
                prefix=prefix.substr(0,prefix.size()-1);
                clear();
                w_print_most_prob_chars(prefix);
                break;
            case 97 ... 122 : // lettere
                c=ch;
                prefix=prefix+c;
                a=new char[prefix.size()+1];
                a[prefix.size()]=0;
                memcpy(a,prefix.c_str(),prefix.size());
                clear();
                w_print_most_prob_chars(prefix);
                //printw("%s \n",a);
                break;

            default:
                break;
        }

    }




    printw("==============================\n");

    endwin();

}


/*
    Crea il dizionario w , valutando lo stream di un testo contenente parole
*/

void Load_Dictionary(WordDictionary * w , std::ifstream * dict )
{
    std::string line;
    getline(*dict,line);
    int total_word;
    istringstream (line) >> total_word;
    int feedback = (total_word/100)*10;
    int perc=1;
    int fd=feedback;

    cout << "\n======LOAD DICTIONARY=========\n";
    cout << "Num words : " << total_word << "\n";
    cout << "\n==============================\n";

    if(dict->good())
    {
        while(getline(*dict,line))
        {
            w->add_word(line);
            if(w->total_word()==fd)
            {
                cout <<"\n Percentage : " << perc*10 << "\n"; // percentuale di operazione di load del file
                fd=fd+feedback;                                // nel dizionario w
                perc++;
            }
        }
    }

    dict->close();


    cout <<"\n=====END LOAD==============\n";

}





int main (void)
{

		WordDictionary * w = new WordDictionary();
        ifstream dict ("dict.ngl");
        Load_Dictionary(w,&dict);
        //w->entropy(2);
        //w->print_most_prob_chars("abc");
        w->keyboard();
		return 0;
}
