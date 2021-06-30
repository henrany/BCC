/* Você deve implementar uma versão usando paralelismo de funções (também
 * chamado decomposição por funções (function decomposition)
 * Para simplificar, você pode considerar que seu programa criará as
 * threads que você julgar necessárias para processar todos os números,
 * onde cada thread executará uma função diferente, com parte das ações
 * esperadas do programa final.
 * 
 * O programa deve aceitar o mesmo parâmetro de linha de comando da versão
 * sequencial - e nenhum outro. 
 * A saída deve sequir exatamente o mesmo formato da versão sequencial.
 */

#include<stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "timediff.h"   // calcula tempo decorrido
#include "numchecks.h"  // conta números com mais condições válidas
#include "conditions.h" // verifica cada condição
#include <pthread.h>
#define Max 9999999999

pthread_mutex_t mut;

struct thread_data{
    long maxnum;
    int n;
};

struct Other{
    int pal;
    int rep;
    int sum;
    int dou;
    int fou;
    int pal_verified;
    int rep_verified;
    int sum_verified;
    int dou_verified;
    int fou_verified;
};

typedef struct thread_data th_data;
typedef struct Other other;
other shared_mem[Max] = {0};

long match_some_test = 0,
     palindromes = 0,
     repeated_seqs = 0,
     sums_are_ap = 0,
     have_tripled_digits = 0,
     have_four_repetitions = 0;

void check_num(long n, int ndigits){
    int all = 0;
    if(shared_mem[n].pal_verified && shared_mem[n].rep_verified && shared_mem[n].sum_verified && shared_mem[n].dou_verified && shared_mem[n].fou_verified){
        all  = shared_mem[n].pal + shared_mem[n].rep + shared_mem[n].sum + shared_mem[n].dou + shared_mem[n].fou;
        if(all > 0){
            match_some_test += 1;
        }
        update_max(n,all);
        palindromes += shared_mem[n].pal;
        repeated_seqs += shared_mem[n].rep;
        sums_are_ap += shared_mem[n].sum;
        have_tripled_digits += shared_mem[n].dou;
        have_four_repetitions += shared_mem[n].fou;
    }
    return;
}

void* palindrome_thread(void* arg){
    th_data *data = (th_data*)arg;
    for(long i=0;i<=data->maxnum;i++){
        digit_t num;
        break_into_digits(i, num, data->n);
        pthread_mutex_lock(&mut);
        shared_mem[i].pal = is_palindrome(num, data->n);
        shared_mem[i].pal_verified = 1;
        check_num(i,data->n);
        pthread_mutex_unlock(&mut);
    }
    pthread_exit(NULL);
}

void* has_repeated_seq_thread(void* arg){
    th_data *data = (th_data *)arg;
    for(long i=0;i<=data->maxnum;i++){
        digit_t num;
        break_into_digits(i, num, data->n);
        pthread_mutex_lock(&mut);
        shared_mem[i].rep = has_repeated_seq(num, data->n);
        shared_mem[i].rep_verified = 1;
        check_num(i,data->n);
        pthread_mutex_unlock(&mut);
    }
    pthread_exit(NULL);

}

void* sum_is_ap_thread(void *arg){
    th_data *data = (th_data *)arg;
    for(long i=0;i<=data->maxnum;i++){
        digit_t num;
        break_into_digits(i,num,data->n);
        pthread_mutex_lock(&mut);
        shared_mem[i].sum = sum_is_ap(num,data->n);
        shared_mem[i].sum_verified = 1;
        check_num(i,data->n);
        pthread_mutex_unlock(&mut);
    }
    pthread_exit(NULL);
}

void* has_tripled_digits_thread(void * arg){
    th_data *data = (th_data *)arg;
    for(long i=0;i<=data->maxnum;i++){
        digit_t num;
        break_into_digits(i, num,data->n);
        pthread_mutex_lock(&mut);
        shared_mem[i].dou = has_tripled_digits(num, data->n);
        shared_mem[i].dou_verified = 1;
        check_num(i,data->n);
        pthread_mutex_unlock(&mut);
    }
    pthread_exit(NULL);
}

void* has_four_repetitions_thread(void *arg){
    th_data *data = (th_data *)arg;
    for(long i=0;i<=data->maxnum;i++){
        digit_t num;
        break_into_digits(i, num,data->n);
        pthread_mutex_lock(&mut);
        shared_mem[i].fou = has_four_repetitions(num, data->n);
        shared_mem[i].fou_verified = 1;
        check_num(i, data->n);
        pthread_mutex_unlock(&mut);
    }
    pthread_exit(NULL);
}


int main(int argc, char* argv[]){
    long tmp;
    th_data data;
    struct timeval t1, t2; // marcação do tempo de execução

    // tratamento da linha de comando
    if (argc!=2) {
        fprintf(stderr,"usage: %s maxnum\n",argv[0]);
        exit(1);
    }
    data.maxnum = atol(argv[1]);
    tmp = data.maxnum;
    data.n = 0;
    // determinação de ndigits em função do maxnum
    do{
        data.n++;
        tmp = tmp/10;
    }while(tmp>0);

    pthread_t thread_id[5];
    pthread_mutex_init(&mut, NULL);

    // Marca o tempo e checa cada número na faixa definida.
    // Note que o valor do parâmetro maxnum é considerado inclusive (<=)
    gettimeofday(&t1, NULL);
    pthread_create(&thread_id[0], NULL, palindrome_thread,(void *) &data);
    pthread_create(&thread_id[1], NULL, has_repeated_seq_thread, (void *) &data);
    pthread_create(&thread_id[2], NULL, sum_is_ap_thread, (void *)&data);
    pthread_create(&thread_id[3], NULL, has_tripled_digits_thread, (void *)&data);
    pthread_create(&thread_id[4], NULL, has_four_repetitions_thread, (void *)&data);

    for(int i=0;i<5;i++){
        pthread_join(thread_id[i], NULL);
    }

    gettimeofday(&t2, NULL);

    // Escrita das estatísticas ao final da execução
    printf("%ld match_some_test (%d%%)\n", match_some_test, (int)((100.0 * match_some_test) / data.maxnum));
    printf("%ld palindromes\n", palindromes);
    printf("%ld repeated_seqs\n", repeated_seqs);
    printf("%ld sums_are_ap\n", sums_are_ap);
    printf("%ld have_tripled_digits\n", have_tripled_digits);
    printf("%ld have_four_repetitions\n", have_four_repetitions);
    print_max(data.n);
    printf("\ntempo: %lf\n", timediff(&t2, &t1));
}
