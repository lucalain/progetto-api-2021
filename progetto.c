#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#define INFINITO 4294967295
typedef enum{false,true} bool;

struct nodo 
{
	unsigned int peso;
	int nomeNodo;
	struct nodo *next;
};

typedef struct nodo *lista;

struct nodoHeap
{
	unsigned int distanza;
	int vertice;
};

struct nodoRankHeap
{
	unsigned int distanza;
	int numeroGrafo;
};


void minHeapify(struct nodoHeap nodi[],int n,int heapSize)
{
	//min
	struct nodoHeap temp;
	int posMin;
	int l = 2*n+1;
	int r = (2*n) +2;
	if((l<heapSize) && ((nodi[l]).distanza<(nodi[n]).distanza))
	{
		posMin = l;
	}
	else
	{
		posMin = n;
	}
	if((r<heapSize)&&((nodi[r]).distanza<(nodi[posMin]).distanza))
	{
		posMin = r;
	}
	if (posMin!=n)
	{
		temp = nodi[n];
		nodi[n] = nodi[posMin];
		nodi[posMin] = temp;
		minHeapify(nodi,posMin,heapSize);
		//minHeapify(nodi,(posMin-1)/2,heapSize);
		//tolto migliorato minHeap
	}
}
struct nodoHeap estraiMin(struct nodoHeap nodi[],int* heapSize)
{
	struct nodoHeap min; 
	if (*heapSize<1)
	{
			return min;
	}
	min = nodi[0];
	if(*heapSize==1)
	{
		*heapSize = *heapSize -1;
	}
	else
	{
		nodi[0] = nodi[*heapSize-1];
		*heapSize = *heapSize -1;
		minHeapify(nodi,0,*heapSize);
	}
	
	return min;	
}


void swap(struct nodoHeap **a,struct nodoHeap **b)
{
	struct nodoHeap *temp = *a;
	*a = *b;
	*b = temp;
}
void inserisci(struct nodoHeap *nodi[],int *heapSize,unsigned int dist,int vertex)
{

	struct nodoHeap* key = malloc(sizeof(struct nodoHeap*));
	key->distanza = dist;
	key->vertice = vertex;
	
	
	*heapSize = *heapSize+1;
	nodi[*heapSize-1] = key;
	int i = *heapSize-1;
	int parent = (i-1)/2;
	
	while ((i>0) &&(nodi[parent]->distanza > nodi[i]->distanza))
	{
		swap(&(nodi[parent]),&(nodi[i]));
		parent = (i-1)/2;
	}
	
}
void modificaValoreNodoHeap(struct nodoHeap nodi[],int nomeNodo,int nDist,int heapSize) 
{
	int i = 0;
	int n;
	bool esci = false;
	for(i = 0;((i<heapSize)&&(esci==false));i++)
	{
		if((nodi[i]).vertice == nomeNodo)
		{
			nodi[i].distanza = nDist;
			esci = true;
		}
	}
	for (n = heapSize / 2 - 1; n >= 0; n--)
			minHeapify(nodi,n,heapSize); 
}
void creaNodo(lista *l,int nome,unsigned int peso)
{
	struct nodo *nuovoNodo;
	nuovoNodo = malloc(sizeof(struct nodo));
	nuovoNodo->nomeNodo  = nome;
	nuovoNodo->peso = peso;
	nuovoNodo->next= *l;
	*l = nuovoNodo;
}

int diventaInt(char *c)
{
	int valore=0;
	for(; (*c != '\0') && (*c >= '0') && (*c <= '9'); c++)
	{
                    valore = valore*10 + *c - '0';
    }
    return valore;
}



void creaLista(int n,lista *l,int i) {
	
	lista cur = (*l);
	int j=0,c=0,f=0;
	unsigned int b=0;
  	char s[10000]; 	
  	char copy[10000];
	if(fgets(s,10000,stdin)!=NULL)
	{
		while(f<n)
		{
			if((s[j]!=',')&&(s[j]!='\0'))
	    	{
	    		copy[c] = s[j];
	    		c++;
			}
			else
			{
				if(c>0)
				{
					copy[c] = '\0';
					b = diventaInt(copy);						
					if(i==0)
					{
						creaNodo(&(*l),f,b);	
					}
					else
					{
						cur->nomeNodo = f;
						cur->peso = b;	
						cur = cur->next;			
					}		
					c = 0;
					b = 0;
				}
				f++;	
			}	
		j++;
		}
	}
}
void swapNodoRankHeap(struct nodoRankHeap* a,struct nodoRankHeap* b)
{
	struct nodoRankHeap temp = *a;
	*a=*b;
	*b = temp;
}
void maxHeapify(struct nodoRankHeap *topk,int size,int n)
{
	struct nodoRankHeap temp;
	int posMax;
	int l = (2*n)+1;
	int r = (2*n) +2;
	if((l<size) && (topk[l].distanza>topk[n].distanza))
	{
		posMax = l;
	}
	else
	{
		posMax = n;
	}
	if((r<size)&&(topk[r].distanza>topk[posMax].distanza))
	{
		posMax = r;
	}
	if (posMax!=n)
	{
		temp.distanza = topk[n].distanza;
		temp.numeroGrafo = topk[n].numeroGrafo;
		topk[n].numeroGrafo = topk[posMax].numeroGrafo;
		topk[n].distanza = topk[posMax].distanza;
		topk[posMax].distanza = temp.distanza;
		topk[posMax].numeroGrafo = temp.numeroGrafo;
		maxHeapify(topk,size,posMax);
	}
}



void inserisciNodoMaxHeap(struct nodoRankHeap *topk,int *size,int dist,int numG,int pos)
{	
	topk[pos].numeroGrafo = numG;
	topk[pos].distanza = dist;
	*size = *size+1;
}
struct nodoRankHeap cancellaMax(struct nodoRankHeap *topk,int *size)
{
	struct nodoRankHeap max;
	max.distanza = topk[0].distanza;
	max.numeroGrafo = topk[0].numeroGrafo;
	/*if (*size<1)
	{
			return max;
	}*/
	//max = topk[0];
	*size = *size -1;
	
	return max;
}
void topK(struct nodoRankHeap topk[],int topkSize,int k)
{
	int c=0,m=0;
	char temp;
	int contaCifre;
	int i = 0;
	char out[4000000];
	int y = 0;
	unsigned int salva = 0;
	if(topkSize>0)
	{
		for(i = 0;i<topkSize-1;i++)
		{
			salva = topk[i].numeroGrafo;
			contaCifre=0;
			while(topk[i].numeroGrafo>0)
			{
				out[y] = (char)(topk[i].numeroGrafo%10)+48;
				y++;	
				topk[i].numeroGrafo = topk[i].numeroGrafo/10;
				contaCifre++;
			}
			if(contaCifre==0)
			{
				out[y] = (char)48;
				y++;	
			}
			if(contaCifre>=2)
			{
				c=y-1; 
				for(m = y-contaCifre;m<c;m++)
				{
					temp = out[m];
					out[m]=out[c];
					out[c] = temp;
					c--;
				}
			}
			out[y] = ' ';
			y++;
			topk[i].numeroGrafo = salva;
		}
		contaCifre=0;
		salva = topk[topkSize-1].numeroGrafo;
		while(topk[topkSize-1].numeroGrafo>0)
		{
			out[y] = (char)(topk[topkSize-1].numeroGrafo%10)+48;
			y++;	
			topk[topkSize-1].numeroGrafo = topk[i].numeroGrafo/10;
			contaCifre++;
		}
		if(contaCifre==0)
		{
			out[y] = (char)48;
			y++;	
		}
		if(contaCifre>=2)
		{	
			c=y-1; 
			for(m = y-contaCifre;m<c;m++)
			{
				temp = out[m];
				out[m]=out[c];
				out[c] = temp;
				c--;
			}
		}
		topk[topkSize-1].numeroGrafo = salva;
		if(topkSize != k)
		{
			out[y] = '\n';
			y++;
		}
	}
	else
	{
		out[y] = '\n';
		y++;
	}
	fputs(out,stdout);
}
int main() 
{
	int n=0, k=0,i=0,c=0;
    char s[256]; 
	char copyN[256];
	char copyK[256];
	int m = 0;
	if(fgets(s,256,stdin)!=NULL)
	{
		while(s[c]!=' ')
		{
			copyN[c] = s[c];
			c++;
		}
		n = diventaInt(copyN);
		
		m = 0;
		c++;
		while(s[c]!='\0')
		{
			copyK[m] = s[c];
			c++;
			m++;
		}
		k = diventaInt(copyK);
	}
	
	lista nodi[n];
	
	lista l = NULL;
	unsigned int somma=0;
	int topkSize=0;
	unsigned int contaGrafo=0;
	struct nodoRankHeap* topk = malloc(k * sizeof(struct nodoRankHeap));
	struct nodoHeap nodiHeap[n];
	int heapSize = 0;
	struct nodoHeap u;
	int nDist;
	unsigned int distanze[n];
	struct nodoRankHeap max;
	
	for (i=0;i<n;i++)
	{	
		nodi[i] = NULL;
	}
	
	
	while(fgets(s,256,stdin)!=NULL)
	{			
		if(strcmp(s,"TopK\n")==0)
		{
			topK(topk,topkSize,k);	
		}
		else
		{		
			for (i=0; i<n; i++) 
			{
				creaLista(n,&nodi[i],contaGrafo);	
	  		}	  			
			nodiHeap[0].distanza = 0;
			nodiHeap[0].vertice = 0;
			distanze[0] = INFINITO;
			for(i = 1;i<n;i++)
			{
				nodiHeap[i].distanza = INFINITO;
				nodiHeap[i].vertice = i;
				distanze[i] = INFINITO;	
			}
			heapSize = n;
			if(nodi[0] !=NULL)
			{		
				while(heapSize>0)
				{
					u = estraiMin(nodiHeap,&heapSize);
					l = nodi[u.vertice];	
					while(l!=NULL)
					{
						nDist = INFINITO;
						if(u.distanza!=INFINITO)
						{
							nDist = u.distanza + l->peso;
						}
						if((nDist<distanze[l->nomeNodo])&&(l->nomeNodo!= u.vertice)&&(l->peso!=0)&&(u.distanza!=INFINITO))
						{
							modificaValoreNodoHeap(nodiHeap,l->nomeNodo,nDist,heapSize);
							distanze[l->nomeNodo] = nDist;	
						}
						l = l->next;
					}
				}		
			}
		somma = 0;
		
		for(i = 1;i<n;i++)
		{						
			if(distanze[i]!=INFINITO)
			{
				somma += distanze[i];
			}
		}
		// lenght è un topk?
		if(contaGrafo<k-1)
		{
			inserisciNodoMaxHeap(topk,&topkSize,somma,contaGrafo,topkSize);
		}
		else
		{
			if(contaGrafo == k-1)
			{
				inserisciNodoMaxHeap(topk,&topkSize,somma,contaGrafo,topkSize);
				for (m = topkSize / 2 - 1; m >= 0; m--)
				{
						maxHeapify(topk,topkSize,m);	
				}
			}
			else
			{
				max = cancellaMax(topk,&topkSize);
				if(max.distanza>somma)
				{
					inserisciNodoMaxHeap(topk,&topkSize,somma,contaGrafo,0);	
				}
				else
				{
					inserisciNodoMaxHeap(topk,&topkSize,max.distanza,max.numeroGrafo,0);
				}
				maxHeapify(topk,topkSize,0);	
			}
		}	
		contaGrafo++;	
		}
	}
}
