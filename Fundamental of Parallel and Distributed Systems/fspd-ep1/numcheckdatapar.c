/* Você deve implementar uma versão usando paralelismo de dados (também
 * chamado decomposição/partição de domínio (domain partition/decomposition)
 * Para simplificar, você pode considerar que seu programa criará oito
 * threads para processar todos os números. Todas as threads devem executar
 * o mesmo código, já que estarão executando as mesmas operações para
 * partes diferentes do conjunto de dados.
 * 
 * O programa deve aceitar o mesmo parâmetro de linha de comando da versão
 * sequencial - e nenhum outro. 
 * A saída deve sequir exatamente o mesmo formato da versão sequencial.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "timediff.h"   // calcula tempo decorrido
#include "numchecks.h"  // conta números com mais condições válidas
#include "conditions.h" // verifica cada condição
#include <pthread.h>

pthread_mutex_t mut;

struct thread_data{
    int ndigits;
    long beg;
    long final;
};


typedef struct thread_data th_data;

// Contadores para cada uma das condições testadas
long match_some_test = 0,
     palindromes = 0,
     repeated_seqs = 0,
     sums_are_ap = 0,
     have_tripled_digits = 0,
     have_four_repetitions = 0;


/* check_num: concentra todos os testes a serem aplicados a cada número.
 */
void* check_num(void* arg){
    th_data *data = (th_data *)arg;
    // Transforma número (n) em vetor de dígitos (num)
    for(long n=data->beg;n<=data->final;n++){
        int all = 0, pal = 0, rep = 0, sum= 0, dou= 0, fou= 0;
        digit_t num;
        long orign = n;
        pthread_mutex_lock(&mut);
        break_into_digits(n, num, data->ndigits);

        // Aplica os diversos testes a um dado número
        pal = is_palindrome(num, data->ndigits);
        rep = has_repeated_seq(num, data->ndigits);
        sum = sum_is_ap(num, data->ndigits);
        dou = has_tripled_digits(num, data->ndigits);
        fou = has_four_repetitions(num, data->ndigits);

        // Para processar número de condições satisfeitas
        all = pal + rep + sum + dou + fou;
        if (all > 0){
            match_some_test += 1;
        }

        update_max(orign, all);
        // Atualiza os contadores por condição
        palindromes += pal;
        repeated_seqs += rep;
        sums_are_ap += sum;
        have_tripled_digits += dou;
        have_four_repetitions += fou;
        pthread_mutex_unlock(&mut);
    }
    pthread_exit(NULL);
}

int
main( int argc, char* argv[] )
{
    th_data data[8] = {0};
    int  ndigits; // núm. de dígitos para representar até o maior número

    long tmp, maxnum;

    struct timeval t1, t2; // marcação do tempo de execução

    // tratamento da linha de comando
    if (argc!=2) {
        fprintf(stderr,"usage: %s maxnum\n",argv[0]);
        exit(1);
    }
    maxnum = atol(argv[1]);

    // determinação de ndigits em função do maxnum
    tmp = maxnum;
    ndigits=0;
    do {
        ndigits++;
        tmp=tmp/10;
    } while (tmp>0);

    long aux = maxnum/8;
    for(int i=0;i<8;i++){
        data[i].ndigits = ndigits;
        data[i].beg = aux * i;
        data[i].final = (i+1)*aux  - 1;
        if(i == 7) data[i].final = maxnum;
    };

    pthread_t thread_id[8];
    pthread_mutex_init(&mut, NULL);

    // Marca o tempo e checa cada número na faixa definida.
    // Note que o valor do parâmetro maxnum é considerado inclusive (<=)
    gettimeofday(&t1,NULL);
       for(int i=0;i<8;i++){
           pthread_create(&thread_id[i], NULL, check_num, (void *) &data[i]);
        }

        for(int i=0;i<8;i++){
            pthread_join(thread_id[i], NULL);
        }

        pthread_mutex_destroy(&mut);

    gettimeofday(&t2,NULL);

    // Escrita das estatísticas ao final da execução
    printf("%ld match_some_test (%d%%)\n", match_some_test, (int)((100.0*match_some_test)/maxnum));
    printf("%ld palindromes\n", palindromes);
    printf("%ld repeated_seqs\n", repeated_seqs);
    printf("%ld sums_are_ap\n", sums_are_ap);
    printf("%ld have_tripled_digits\n", have_tripled_digits);
    printf("%ld have_four_repetitions\n", have_four_repetitions);
    print_max( ndigits );
    printf("\ntempo: %lf\n",timediff(&t2,&t1));
}
