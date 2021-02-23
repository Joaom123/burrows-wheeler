// //Medir para todas as plataformas utilizadas (PC-Linux e Arduino UNO)
// 	- Tempo de computação (DO ALGORITMO, excluindo partes de I/O, geração de dados de entrada, impressão etc)
// 	- Tamanho da memória de código utilizada pela aplicação (excluindo dados de entrada)
// 	- Tamanho da memória de dados utilizada pela aplicação

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>

unsigned long tempo_inicial;
unsigned long tempo_final;

void pega_tempo_antes_da_execucao()
{
  tempo_inicial = clock();
}

void pega_tempo_depois_da_execucao()
{
  tempo_final = clock();
}

void calcula_e_exibe_duracao()
{
  printf("Tempo da execução foi: %ld\n", tempo_final - tempo_inicial);
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
