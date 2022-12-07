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
	
	return equivalentResistece = 1/equivalentResistece;
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
	int count =0, control =0;
	if(response>2)
	{
		for(int i=response;i!=0;i--)
		{
			if(count==0)
			{
				count ++;
				equivalentResistece = resistence[i-1];
				printf("\n\n%f", equivalentResistece);
			}
			else if(control==0 && count >0)
			{
				equivalentResistece += resistence[i-1];
				printf("\n\n%f", equivalentResistece);
				control =1;
			}
			else if(control ==1)
			{
				//equivalentResistece += (1/resistence[i]);
				equivalentResistece = (1/resistence[i-1]) + (1/equivalentResistece);
				equivalentResistece = 1/equivalentResistece;
				printf("\n\n%f", equivalentResistece);
				control =0;
			}
		}
		return equivalentResistece;
	}
	else
	{
		printf("Desculpe, o valor de resistores que existem no seu circuito é inferior ao mínimo necessário-\npara calcular uma resistencia mista");
		return 0;
	}
}

float bateryCurrent(const float resistence, const float powerSource)
{
	float current =0;
	current = powerSource/resistence;
	return current;
}

float powerSourceWatt(const float voltage, const float current)
{
	float power =0;
	power = voltage*current;
	return power;
}

int main()
{
	int response, control = 0;
	float powerSourceVoltage, resistence[256];
	char circuitType[8] = "none";
	setlocale(LC_ALL, "Portuguese");
	
	printf("============================ Calculadora de resistência Equivalente ======================================"
		"\nOlá, seja bem vindo(a) e obrigado por usar nosso sistema clona cartão");	

	printf("\n\n -- Digite a tensão fornecida pela fonte: ");
	scanf("%f", &powerSourceVoltage);
	
	printf("\n\n -- Quantos resistores voc� possui em seu circuito? ");
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
				printf("\n\n - A corrente é de: %f"
					"\n\n - e a potencia da fonte é: %f", bateryCurrent(serieResistence(resistence, response), powerSourceVoltage), powerSourceWatt(powerSourceVoltage, bateryCurrent(serieResistence(resistence, response), powerSourceVoltage)));
				control = 1;
				break;
			case 'm':
			case 'M':
				printf("\n\n\nMISTO");
				printf("\n\n%f\n\n", mistoResistence(resistence, response));
				control = 1;
				break;
			default:
				printf("\n\n - Quase l�, os resistores est�o dispostos de forma:"
					"\n  - Paralela"
					"\n  - S�rie"
					"\n  - Misto"
					"\n Digite o formato escolhido: ");
				scanf("%s", circuitType);
		}	
	}
	

	return 0;
}