// //Medir para todas as plataformas utilizadas (PC-Linux e Arduino UNO)
// 	- Tempo de computação (DO ALGORITMO, excluindo partes de I/O, geração de dados de entrada, impressão etc)
// 	- Tamanho da memória de código utilizada pela aplicação (excluindo dados de entrada)
// 	- Tamanho da memória de dados utilizada pela aplicação

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/resource.h>

struct timeval tempo_inicial;
struct timeval tempo_final;

void pega_tempo_antes_da_execucao()
{
  gettimeofday(&tempo_inicial, NULL);
}

void pega_tempo_depois_da_execucao()
{
  gettimeofday(&tempo_final, NULL);
}

void calcula_e_exibe_duracao()
{
  printf("Tempo da execução foi: %ld\n", (tempo_final.tv_sec - tempo_inicial.tv_sec) * 1000000 + tempo_final.tv_usec - tempo_inicial.tv_usec);
}

void pega_tamanho_memoria()
{
  long rss = 0L;
  FILE *fp = NULL;
  if ((fp = fopen("/proc/self/statm", "r")) == NULL)
    return; /* Can't open? */
  if (fscanf(fp, "%*s%ld", &rss) != 1)
  {
    fclose(fp);
    return; /* Can't read? */
  }
  fclose(fp);
  printf("%ld\n", (size_t)rss * (size_t)sysconf(_SC_PAGESIZE));
  // return (size_t)rss * (size_t)sysconf(_SC_PAGESIZE);
}
