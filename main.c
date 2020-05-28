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

void print_currnt_state(enum States *states){

    int i;
    for(i = 0; i < 2; i++)
    {
        printf(" q%d ", states[i]);
    }
    printf(" \n ");
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

        if(currnet_char == '#'){
            printf("koniec slowa \n\n\n");
            states[0] = q0;
            states[1] = q0;
            //break;
        }

        else if(states[0] == q8 || states[0] == q9)
        {
            printf("still finit is ");
            print_currnt_state(states);
        }
        else
        {
            int double_zeros = currnet_char == '0' && states[1] == q1;
            int double_ones = currnet_char == '1' && states[1] == q2;
            int double_twos = currnet_char == '2' && states[1] == q3;
            int double_threes = currnet_char == '3' && states[1] == q4;

            int double_a = currnet_char == 'a' && states[1] == q5;
            int double_b = currnet_char == 'b' && states[1] == q6;
            int double_c = currnet_char == 'c' && states[1] == q7;

            if(double_zeros == 1 || double_ones == 1 || double_twos == 1 || double_threes ==1)
            {
                states[0] = q8;
                states[1] = q8;
                printf("finit state is ", states[1]);
                print_currnt_state(states);
            }
            else if(double_a == 1 || double_b == 1 || double_c == 1)
            {
                states[0] = q9;
                states[1] = q9;
                printf("finit state is ");
                print_currnt_state(states);
            }
            else
            {
                switch(currnet_char)
                {
                case '0':
                    states[1] = q1;
                    break;
                case '1':
                    states[1] = q2;
                    break;
                case '2':
                    states[1] = q3;
                    break;
                case '3':
                    states[1] = q4;
                    break;
                case 'a':
                    states[1] = q5;
                    break;
                case 'b':
                    states[1] = q6;
                    break;
                case 'c':
                    states[1] = q7;
                    break;
                default:
                    printf("a");
                    return -1;
                }
                printf("current state is " );
                print_currnt_state(states);
            }
        }
    }
}

struct Node
{
    void  *data;
    struct Node *next;
};

void push(struct Node** head_ref, void *new_data, size_t data_size)
{
    // Allocate memory for node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data  = malloc(data_size);
    new_node->next = (*head_ref);

    // Copy contents of new_data to newly allocated memory.
    // Assumption: char takes 1 byte.
    int i;
    for (i=0; i<data_size; i++)
        *(char *)(new_node->data + i) = *(char *)(new_data + i);

    // Change head pointer as new node is added at the beginning
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
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    unsigned size = MAXCHAR*sizeof(char);
    int licz = 0;
    while (fgets(str, MAXCHAR, fp) != NULL)
        push(&start, &str, size);
        licz++;
    fclose(fp);

    //printList(start, printState);
    printf(" licz %d a string to %s \n\n\n", licz, str);
    nfa(str);
    return 0;

}
