#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stringIcindekiVeriyiTemizle(char dizi[])		/* Kolon İsimlerini Temizlemek İçin Yazdım*/
{		
	int k=0;
	while(dizi[k]!=NULL){
		if(dizi[k]==34 || dizi[k]==dizi[k] || dizi[k]==32){
			dizi[k]=dizi[k+1];
		}
		k++;
	}

}

int main(int argc,char* argv[]) {
	
	int i=0,j=0;
	char *dosyaAdi1 = argv[1];
	char *dosyaAdi2 = argv[2];
	char *headerMetni = argv[3];
	char tag[20]="kolon";
	int header=0;
	int tahminiSatirUzunlugu=255;
	char headerSatiri[tahminiSatirUzunlugu];
	char headerKontrol[9]="header=ON";
	char yazdirilacakKarakter;
	char kolonAdlari[10][30];
	int spaceSayaci=0;
	int satir=1,kolon=1;
	FILE *pcsv = fopen(dosyaAdi1,"r");
	FILE *pjson = fopen(dosyaAdi2,"w+");
	
	
	if(strncmp(headerMetni,headerKontrol,9)==0)		/* İki String Değerin Eşitliğini Kontrol Eder*/
	{
		header=1;	
	}
	
	if(header==1)
	{
		fgets(headerSatiri, tahminiSatirUzunlugu, pcsv);
		
		char *parca = strtok(headerSatiri,",");
		
			while(parca!=NULL)						/* Satır İçindeki Kolon İsimlerini Delimeter İle Bulur ve Diziye Atar*/
				{
					strcpy(kolonAdlari[i],parca);
					parca = strtok(NULL,",");
					i++;
				}
		
			for(j=0;j<i;j++)
				{
						stringIcindekiVeriyiTemizle(kolonAdlari[j]);
				}
		i=0;
			
	}
    	
	
	fputc(123,pjson);
	fputc(10,pjson);
	
		while(!feof(pcsv))
			{
						
				if((kolon == 1) || (yazdirilacakKarakter == 10))
					{	
					
						fprintf(pjson,"satir %d",satir);
						satir++;
						fputc(9,pjson);
						fputc(123,pjson);
						fputc(10,pjson);
						fputc(34,pjson);
						
						if(header==1)
							{
								strcpy(tag,kolonAdlari[i]);
								i++;
							}
							
						fprintf(pjson,"%s %d",tag,kolon);
						fputc(34,pjson);
						kolon++;
						fputc(58,pjson);
						fputc(34,pjson);
					}
				
				yazdirilacakKarakter = fgetc(pcsv);
				
				if(yazdirilacakKarakter == 32)
				{
					spaceSayaci++;
					
					if(spaceSayaci>1)
						{
							continue;
						}
				} else
					{
						spaceSayaci = 0;
					}
				
				if(yazdirilacakKarakter == 44)	/* virgül okunduğunda yani csv içinde field değiştiğnde*/
					{
						fputc(34,pjson);
						fputc(44,pjson);
						fputc(10,pjson);
						fputc(34,pjson);
						
						if(header==1)
							{
								strcpy(tag,kolonAdlari[i]);
								i++;
							}
							
						fprintf(pjson,"%s %d",tag,kolon);
						fputc(34,pjson);
						kolon++;
						fputc(58,pjson);
						fputc(34,pjson);
						continue;
					}	
					
				if(yazdirilacakKarakter == 34) /* çift tırnak okunduğunda*/
					{
						continue;
					}
				
				if(yazdirilacakKarakter == 10)	/* record değiştiğinde yani csv içinde alt satıra geçtiğinde*/
					{	
						i=0;
						kolon = 1;
						fputc(34,pjson);
						fputc(yazdirilacakKarakter,pjson);
						fputc(9,pjson);
						fputc(125,pjson);
						fputc(10,pjson);
						fputc(9,pjson);
						continue;
					}
				
				fputc(yazdirilacakKarakter,pjson);
			
				
			}
	fputc(10,pjson);
	fputc(125,pjson);
	
	fclose(pcsv);
	fclose(pjson);
		
	return 0;
}