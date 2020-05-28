#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 1000
/* Wszystkie mozliwe stany automatu */
enum States
{
    q0 = 0,
    q1 = 1,
    q2 = 2,
    q3 = 3,
    q4 = 4,
    q5 = 5,
    q6 = 6,
    q7 = 7,
    q8 = 8,
    q9 = 9,
};

/* Metoda pokazujaca wszystkie stany automatu. */
void show_states(char **state_list, int len)
{
    printf("LISTA STANOW TO : [");

    int i;
    for(i=0; i < len+1; i++)
    {
        printf(" %s ", state_list[i]);
    }
    printf("]\n");
}

void print_currnt_state(enum States *states)
{
    printf("current state is " );
    int i;
    for(i = 0; i < 2; i++)
    {
        printf(" q%d ", states[i]);
    }
    printf(" \n");
}

void nfa(char* word)
{

    /* Stan poczatkowy - q0 */
    enum States states[2];
    states[0] = q0;

    int word_len = strlen(word);
    int i;
    for(i =0; i< word_len; i++)
    {
        char currnet_char = word[i];

        /* znak # oznacza konca slowa, wtedy automat zaczyna analizowac kolejne slowo */
        if(currnet_char == '#')
        {
            printf("koniec slowa \n\n\n");
            states[0] = q0;
            states[1] = q0;
            //break;
        }
        /* gdy osiagnieto stan koncowy to zostajemy w nim do konca slowa */
        else if(states[0] == q8)
        {
            states[0] = q8;
            states[1] = q8;
            print_currnt_state(states);
        }
        else if(states[0] == q9)
        {
            states[0] = q9;
            states[1] = q9;
            print_currnt_state(states);
        }

        /* nie osiagnieto stanu koncowego */
            else
            {
                if(states[0] == q0)
                {
                    switch(currnet_char)
                    {
                    case '0':
                        if(states[1]==q1){
                            states[0] = q8;
                            states[1] = q8;
                        }
                        else{
                            states[1] = q1;
                        }

                        break;
                    case '1':
                        if(states[1]==q2){
                            states[0] = q8;
                            states[1] = q8;
                        }
                        else{
                            states[1] = q2;
                        }
                        break;
                    case '2':
                        if(states[1]==q3){
                            states[0] = q8;
                            states[1] = q8;
                        }
                        else{
                            states[1] = q3;
                        }
                        break;
                    case '3':
                        if(states[1]==q4){
                            states[0] = q8;
                            states[1] = q8;
                        }
                        else{
                            states[1] = q4;
                        }
                        break;
                    case 'a':
                        if(states[1]==q5){
                            states[0] = q9;
                            states[1] = q9;
                        }
                        else{
                            states[1] = q5;
                        }
                        break;
                    case 'b':
                        if(states[1]==q6){
                            states[0] = q9;
                            states[1] = q9;
                        }
                        else{
                            states[1] = q6;
                        }
                        break;
                    case 'c':
                        if(states[1]==q7){
                            states[0] = q9;
                            states[1] = q9;
                        }
                        else{
                            states[1] = q7;
                        }
                        break;
                    default:
                        printf("byq -1");
                        return -1;
                    }
                    print_currnt_state(states);
                }
            }

    }
}

/*  Lista ze strony https://www.geeksforgeeks.org/generic-linked-list-in-c-2/ */
struct Node
{
    void  *data;
    struct Node *next;
};

void push(struct Node** head_ref, void *new_data, size_t data_size)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data  = malloc(data_size);
    new_node->next = (*head_ref);

    int i;
    for (i=0; i<data_size; i++)
        *(char *)(new_node->data + i) = *(char *)(new_data + i);

    (*head_ref)    = new_node;
}

void printList(struct Node *node, void (*fptr)(void *))
{
    while (node != NULL)
    {
        (*fptr)(node->data);
        node = node->next;
    }
}


void printState(char *n)
{
    printf("%s \n", n);
}

/*   Koniec ------------ ----------------------------------------------Listy  */

int main()
{
    printf("NFA \n\n");

    char* word = "abcc12";
    //nfa(word);

    struct Node *start = NULL;

    FILE *fp;
    char str[MAXCHAR];
    char* filename = "strings.txt";

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s",filename);
        return 1;
    }
    unsigned size = MAXCHAR*sizeof(char);
    while (fgets(str, MAXCHAR, fp) != NULL){
        //push(&start, &str, size);
    }

    fclose(fp);

    //printList(start, printState);
    printf("String to %s \n\n\n", str);
    nfa(str);

    return 0;

}
