/* =======================================================================
 * Pacote de implementação das funções do GPS
 * =======================================================================
 * Últimas modificações:
 *
 * 1_ Alterada como a função leituraGPS trata os erros
 *
 * 2_ Removido gps_stream da função killGPS
 *
 * 3_ Adicionadas bibliotecas com constantes e definições para tratamento
 * de erros (errno e outras constantes)
 *
 * Deve ser feito:
 *
 * 1_ Alterar os comentários ao longo do código .cpp e .h para melhor
 * documentar o funcionamento do módulo
 *
 * 2_ Testar a leitura de dados pelo GPS em ambiente de céu aberto
 * 
 * =======================================================================
 */

#include "implementacaoGPS.h"

// =======================================================================
// Função de inicialização do GPS
// =======================================================================
void initGPS(gps_data_t* dataGPS){
  int rc;

  printf("Inicializando GPS ...\n");
  if((rc = gps_open(GPSD_SHARED_MEMORY, 0, dataGPS)) == -1){
    printf("Erro na inicializacao do GPS na linha # %d\nRazao do erro: %s\n", __LINE__, gps_errstr(rc));
    exit(EXIT_FAILURE);
  }
} // FIM DA FUNÇÃO initGPS

// =======================================================================
// Função de leitura dos dados do GPS
// =======================================================================
void leituraGPS(gps_data_t* dataGPS){
  int rc = 0;
  int errsv;

  rc = gps_read(dataGPS); errsv = errno;
      if (rc == -1) {
          printf("Erro ao realizar a leitura do GPS na linha # %d\nCodigo do erro: %d\n",__LINE__, errsv /*gps_errstr(rc)*/);
      }else{
          if ((dataGPS->status == STATUS_FIX) &&
              (dataGPS->fix.mode == MODE_2D || dataGPS->fix.mode == MODE_3D) &&
              !isnan(dataGPS->fix.latitude) &&
              !isnan(dataGPS->fix.longitude)) {
                  // Print para fins de testes. Esta linha deve ser comentada!
                  //fprintf(stderr, "\nLatitude: %f\nLongitude: %f\nVelocidade: %f\nMarca de Tempo: %lf\n", (*dataGPS)->fix.latitude, (*dataGPS)->fix.longitude, (*dataGPS)->fix.speed, (*dataGPS)->fix.time);
          }else{
              printf("Sem dados do GPS disponiveis!\n");
          }
      } // FIM DO IF DE ESPERA ENTRE LEITURAS
} // FIM DA FUNÇÃO leituraGPS

// =======================================================================
// Função de encerramento do daemon do GPS
// =======================================================================
void killGPS(gps_data_t* dataGPS){
  gps_close (dataGPS);
} // FIM DA FUNÇÃO killGPS
