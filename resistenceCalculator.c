//Created by Luan Rockenbach, Maicon Dickow
//UFSM - CTISM, Santa Maria - RS
//29/11/2022 - 16:13:58

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

float parallelResistence(const float resistence[256], const int response)
{
	float equivalentResistece = 0;
	
	for(int i=0;i<response;i++)
	{
		equivalentResistece += (1/resistence[i]);
	}
	
	return equivalentResistece /= 1;
}

float serieResistence(const float resistence[256], const int response)
{
	float equivalentResistece = 0;
	
	for(int i=0;i<response;i++)
	{
		equivalentResistece += resistence[i];
	}
	return equivalentResistece;
}

float mistoResistence(const float resistence[256], const int response)
{
	float equivalentResistece = 0;
	int count =0;
	for(int i=response;i>0;i--)
	{
		if(i==response)
		{
				if(count == 2)
			{
				equivalentResistece += (resistence[i] * resistence[i-1]) / (resistence[i] + resistence[i-1]);
				count = 0;
			}
			else if(count >=0 && count <2)
			{
				equivalentResistece += resistence[i];
			count++;
			}
		}
		else
		{
				if(count == 1)
			{
				equivalentResistece += 1/resistence[i];
				equivalentResistece /= 1;
				count = 0;
			}
			else if(count >=0 && count <1)
			{
				equivalentResistece += resistence[i];
			}
		} 
			count++;
		
	}
	return equivalentResistece;
}

int main()
{
	int response, control = 0;
	float powerSourceVoltage, resistence[256];
	char circuitType[8] = "none";
	setlocale(LC_ALL, "Portuguese");
	
	printf("============================ Calculadora de resistência Equivalente ======================================"
		"\nOlá, seja bem vinda(a) e obrigado por usar nosso sistema clona cartão");	

	printf("\n\n -- Digite a tensão fornecida pela fonte: ");
	scanf("%f", &powerSourceVoltage);
	
	printf("\n\n -- Quantos resistores você possui em seu circuito? ");
	scanf("%d", &response);
	
	for(int i=0;i<response;i++)
	{
		printf("\n\n -- Digite o valor do resistor R%d: ", i+1);
		scanf("%f", &resistence[i]);
	}
	while(control == 0)
	{
		switch (circuitType[0])
		{
			case 'p':
			case 'P':
				printf("\n\n\nPARALELO");
				printf("\n\n%f\n\n", parallelResistence(resistence, response));
				control = 1;
				break;
			case 's':
			case 'S':
				printf("\n\n\nSÉRIE");
				printf("\n\n%f\n\n", serieResistence(resistence, response));
				control = 1;
				break;
			case 'm':
			case 'M':
				printf("\n\n\nMISTO");
				printf("\n\n%f\n\n", mistoResistence(resistence, response));
				control = 1;
				break;
			default:
				printf("\n\n - Quase lá, os resistores estão dispostos de forma:"
					"\n  - Paralela"
					"\n  - Série"
					"\n  - Misto"
					"\n Digite o formato escolhido: ");
				scanf("%s", circuitType);
		}	
	}
	

	return 0;
}