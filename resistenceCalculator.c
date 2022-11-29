//Created by Luan Rockenbach, Maicon Dickow
//UFSM - CTISM, Santa Maria - RS
//29/11/2022 - 16:13:58

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
	int response, resitence[256];
	float powerSourceVoltage;
	setlocale(LC_ALL, "Portuguese");
	
	printf("============================ Calculadora de resistência Equivalente ======================================"
		"\nOlá, seja bem vinda(a) e obrigado por usar nosso sistema clona cartão");	

	printf("\n\n -- Digite a tensão fornecida pela fonte: ");
	scanf("%f", &powerSourceVoltage);
	
	printf("\n\n -- Quantos resistores você possui em seu circuito? ");
	scanf("%d", &response);
	
	for(int i=0;i<response;i++)
	{
		///
	}

	return 0;
}