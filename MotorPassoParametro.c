/****************************************************************/
#include<16f877.h>
#use delay(clock=4000000)
#use fast_io(D)
#fuses NOWDT, XT, PUT, NOPROTECT, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#define SentidoHorario 0
#define SentidoAntiHorario 1
/********************************************************/
//Mascara para aconamento do motor
int MascaraMotor[4]={
         0b00000110, 
         0b00000011,
         0b00001001,
         0b00001100,
};
//Variavel global que contem o passo atual
int PassoAtual;
/***********************Funcoes*********************************/
// Funcao para tratamento da movimentação com o motor de passo   //
// Parametros                                                   //
//-Sentido: Recebe valores 0 ou 1 e determina sentido de giro  //
//-Passo: Recebe o nomero de passo a mover de 0 a 65535       //
//-TempoEntrePassos: Recebe o tempo em ms entre passos       //
/********************************************************/
void MotordePasso(int Sentido, long Passos, int TempoEntrePassos)
{
   long ContPassos = 0; //Auxiliar Passos ja executados
   delay_ms(800); //Fica parado por um tempo
   while(ContPassos < Passos) 
   {
      if(Sentido) //Conforme o sentido toma uma determinada acao
      {
         if(PassoAtual < 4) //A variavem passo pertence ao dominio 0 =< x =<4
            PassoAtual++;  //Avanca na leitura da tabela
         else
            PassoAtual=0;
      }
      else
      {
       if(PassoAtual > 0) //A variavem passo pertence ao dominio 0 =< x =<4
            PassoAtual--;  //Retorna na leitura da tabela
         else
            PassoAtual=4;
      }
      output_d(MascaraMotor[PassoAtual]); //Aplica na porta o valor
      delay_ms(TempoEntrePassos);   //Determina o tempo entre passos
      ContPassos++; //atualiza passos realizados
   }
}
void main()
{
   set_tris_d(0); //PortD configurado como saida
   while(1)
   {
      PassoAtual = 0;
      // Avanca 50 passos com tempo entre passos de 400ms
      MotordePasso(SentidoAntiHorario,50,400);
      // Retorna 100 passos com tempo entre passos de 200ms
      MotordePasso(SentidoHorario,100,200);
   }
}
      
   

      
