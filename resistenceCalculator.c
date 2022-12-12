//Created by Luan Rockenbach, Maicon Dickow
//UFSM - CTISM, Santa Maria - RS
//29/11/2022 - 16:13:58

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

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

void parallelResistence(const float resistence[256], const int response, const float powerSource)
{
	float equivalentResistece = 0;
	
	for(int i=0;i<response;i++)
	{
		equivalentResistece += (1/resistence[i]);
	}
	
	equivalentResistece = 1/equivalentResistece;
	
	float current = bateryCurrent(equivalentResistece, powerSource);
	
	printf("\n\n\n============================================ CIRCUITO PARALELO ======================================================"
		"\n\n - A resistência equivalente do circuito é de: %.2f Ω"
		"\n\n - A Tensão fornecida pela fonte é de: %.2f Volts"
		"\n\n - A corrente total do circuito é de: %.2f Amperes"
		"\n\n - A potência da fonte é de: %.2f Watts", equivalentResistece, powerSource, current, powerSourceWatt(powerSource, current));
		
	printf("\n"
		"\n------------------------------ Tensão, potência e Corrente dos resistores: ----------------------------------------");
	
	for(int j=0; j<response; j++)
	{
		float resistCurrent = 0;
		resistCurrent = powerSource/resistence[j];
		printf("\nR%d: %.2f Ω		Potência: %.2f Watts	 Corrente: %.2f Amperes		Tensão: %.2f Volts", j+1, resistence[j], pow(powerSource, 2)/resistence[j], resistCurrent, powerSource);
	}
	
}

void serieResistence(const float resistence[256], const int response, const float powerSource)
{
	float equivalentResistece = 0;
	
	for(int i=0;i<response;i++)
	{
		equivalentResistece += resistence[i];
	}
	
	float current = bateryCurrent(equivalentResistece, powerSource);
	
	printf("\n\n\n============================================ CIRCUITO SÉRIE ======================================================"
		"\n\n - A resistência equivalente do circuito é de: %.2f Ω"
		"\n\n - A Tensão fornecida pela fonte é de: %.2f Volts"
		"\n\n - A corrente total do circuito é de: %.2f Amperes"
		"\n\n - A potência da fonte é de: %.2f Watts", equivalentResistece, powerSource, current, powerSourceWatt(powerSource, current));
		
	printf("\n"
		"\n------------------------------ Tensão, potência e Corrente dos resistores: ----------------------------------------");
	
	for(int j=0; j<response; j++)
	{
		float resistVoltage = 0;
		resistVoltage = current * resistence[j];
		printf("\nR%d: %.2f Ω		Potência: %.2f Watts	 Corrente: %.2f Amperes		Tensão: %.2f Volts", j+1, resistence[j], pow(current, 2)/resistence[j], current, resistVoltage);
	}
	
}

void mixedResistence(const float resistence[256], const int response, const float powerSource)
{
	float equivalentResistence = 0;
	float resistenceEqui[response];
	int count=0, control=0, ctrl=0;
	if(response>2 && response%2==0)
	{
		for(int i=response;i!=0;i--)
		{
			if(count==0)
			{
				count ++;
				equivalentResistence = resistence[i-1];
				resistenceEqui[ctrl] = equivalentResistence;
			}
			else if(control==0 && count >0)
			{
				equivalentResistence += resistence[i-1];
				resistenceEqui[ctrl] = equivalentResistence;
				control =1;
			}
			else if(control ==1)
			{
				equivalentResistence = (1/resistence[i-1]) + (1/equivalentResistence);
				equivalentResistence = 1/equivalentResistence;
				resistenceEqui[ctrl] = equivalentResistence;
				control =0;
			}
			ctrl++;
		}
		
		float current = bateryCurrent(equivalentResistence, powerSource);
		float resistVoltage[256], resistCurrent[256], resistPower[256];
		
		resistVoltage[0]=current*resistence[0];
		resistCurrent[0]=resistVoltage[0]/resistence[0];
		resistPower[0]=resistVoltage[0]*resistCurrent[0];
		
		control =0;
		
		for(int j=0;j<response;j++)
		{
			if(j>0 && control==0)
			{
				resistCurrent[j] = current*(resistenceEqui[response-j]/(resistenceEqui[response-j] + resistence[j]));
				resistVoltage[j] = resistCurrent[j]*resistence[j];
				resistPower[j] = resistVoltage[j]*resistCurrent[j];
				control=1;
			}
			else if(control==1)
			{
				resistCurrent[j] = current*(resistenceEqui[response-j]/(resistenceEqui[response-j] + resistence[j]));
				resistVoltage[j] = resistCurrent[j]*resistence[j];
				resistPower[j] = resistVoltage[j]*resistCurrent[j];
			}
			printf("\nR%d: %.3f Ω		Potência: %.3f Watts	 Corrente: %.3f Amperes		Tensão: %.3f Volts", j+1, resistence[j], resistPower[j], resistCurrent[j], resistVoltage[j]);
		}
	}
	else
	{
		printf("Desculpe, o valor de resistores que existem no seu circuito é inferior ao mínimo necessário-\npara calcular uma resistencia mista");
		//return 0;
	}
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
	int response, control = 0;
	float powerSourceVoltage, resistence[256];
	char circuitType[8] = "none";
	
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
				//printf("\n\n\nPARALELO");
				parallelResistence(resistence, response, powerSourceVoltage);
				control = 1;
				break;
			case 's':
			case 'S':
				//printf("\n\n\nSÉRIE");
				serieResistence(resistence, response, powerSourceVoltage);
				control = 1;
				break;
			case 'm':
			case 'M':
				printf("\n\n\nMISTO");
				mixedResistence(resistence, response, powerSourceVoltage);
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