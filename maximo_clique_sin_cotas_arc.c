#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max_n 50
int           optSize;
unsigned long optClique[50];
char*         maximo_s;
unsigned long ColorClass[50];
int           max=0;
int           opt_clique[200];
int           clique_m[200];
unsigned long uno = 1L;
struct grafica
{
    int Nodo;
    unsigned long conexiones[50];
};
void binario(unsigned long num)
{
    unsigned long aux;
    if (num == 0)
        return;

    aux=num % 2;
    num=num / 2;
    binario(num);
    printf("%ld", aux);
}

void backtrack(int n, int l, struct grafica gr[], unsigned long C[], unsigned long N[], unsigned long b[], int c, int div, int s_k)
{
    int           k=1, i=0, v=0, e=0, s=0, m=0, n_ver, j=0, mc=0;
    unsigned long C_aux[div], C1_aux[div], C0[div], b_aux[div], C1[div];
    unsigned long N_aux[div];
    int           maximal=0;
    int           no_max=0;
    char*         aux, * auxi;
    int           cardinalidad=0;
    for (i=0; i < div; i++)
    {
        C1[i]=0;
        /*si la interseccion es igual a cero, existe interseccion*/
        if ((b[i] & gr[l].conexiones[i] & C[i]) != 0)
        {
            C1[i]    =b[i] & gr[l].conexiones[i] & C[i];
            C1_aux[i]=C1[i];
        }
    }
    m=0;
    //printf("\ns_k %d\n",s_k);
    if (s_k > optSize)
    {
        optSize=s_k;
        for (mc=0; mc < c; mc++)
            opt_clique[mc]=clique_m[mc];
        //printf("\n %d %s  \n",s_k,erior);
        max=c;
    }
    m=0;
    char* nuevo="";
    for (i=0; i < div; i++) {
        C0[i]   =(unsigned long)pow(2, n_ver);
        b_aux[i]=(C0[i] - 1);
        if (i == 0)
        {
            b_aux[i]=b_aux[i] << 1;
            b_aux[i]=b_aux[i] & (C0[i] - 1);
        }
    }
    for (i=0; i < div; i++)
    {
        if (i < div - 1)
            n_ver=4;
        else
            n_ver=n % 4;
        C0[i]    =(unsigned long)pow(2, n_ver);
        C1_aux[i]=C1[i];
        C_aux[i] =0;
        b_aux[i] =(C0[i] - 1);
        if (i == 0)
        {
            b_aux[i]=b_aux[i] << 1;
            b_aux[i]=b_aux[i] & (C0[i] - 1);
        }
        printf("_n_ver_%d _i_%d_", n_ver, i);
        /*binario(C0[i]-1);
           /* printf("_B _");
           binario(b_aux[i]);*/
        m=0;
        while (m <= n_ver)
        {
            /*printf(" i:%d c1",i);
               binario(C1_aux[i]);*/
            if (C1_aux[i] & uno)
            {
                clique_m[c]=m + (i * 4);
                printf("\n");
                for (mc=0; mc < c + 1; mc++)
                    printf("%d ", clique_m[mc]);
                backtrack(n, (m + (i * 4)), gr, C1, N_aux, b_aux, c + 1, div, c + 1);
            }
            C1_aux[i]=C1_aux[i] >> 1;
            b_aux[i] =b_aux[i] << 1;
            b_aux[i] =b_aux[i] & (C0[i] - 1);
            /*printf("_B _");
               binario(b_aux[i]);*/
            m++;
        }
    }
}

int main()
{
    int           n, i=0, vertice=0, j=0, l=0, k=0, num_con, div=0, v=0, div_ver=0, n_ver=0, c=0, mc=0;
    unsigned long conexion=0, num_b;
    optSize=0;
    printf("\n********************CLIQUES***********************\n");
    FILE* inputf;
    inputf = fopen("/Users/irving/Documents/tmp/Cliques/Cliques/graph.txt", "r");
    if (inputf == NULL)
        printf("NO archivo \n");

    char caracter[5000];
    char cadena[4];

    c          =0;
    caracter[c]=fgetc(inputf);
    while (v == 0)
    {
        c++;
        caracter[c]=fgetc(inputf);
        if (c > 4)
            if (caracter[c] == 'e' && caracter[c - 1] == 'g' && caracter[c - 2] == 'd' && caracter[c - 3] == 'e')
            {
                c++;
                caracter[c]=fgetc(inputf); //el espacio
                caracter[c]=fgetc(inputf); //el primer dígito del número
                i          =0;
                while (caracter[c] != ' ')
                {
                    cadena[i]  =caracter[c];//toma cada uno de los dígitos
                    caracter[c]=fgetc(inputf);
                    i++;
                }
                v=atoi(cadena);
            }
    }
    printf("Número de vértices:");
    scanf("%d", &v);
    div=(v + 4) / 4;
    n  =v % 4;
    unsigned long  b[div], C0[div], C1[div], N[div];
    struct grafica nueva_g[v];
    for (i=0; i < v; i++)
        for (k=0; k < div; k++)
            nueva_g[i].conexiones[k]=0;

    caracter[c]=fgetc(inputf);//cualquier caracter
    while (feof(inputf) == 0)
    {
        while (caracter[c] != 'e' && feof(inputf) == 0) { //encuentra la letra e
            caracter[c]=fgetc(inputf);
        }
        caracter[c]=fgetc(inputf); //el espacio
        //Para tomar el primer vértice
        caracter[c]=fgetc(inputf); //el primer dígito del número
        for (k=0; k < 4; k++)      //limpio mi cadena
            cadena[k]=' ';
        i=0;
        while (caracter[c] != ' ' && feof(inputf) == 0)
        {
            cadena[i]  =caracter[c];
            caracter[c]=fgetc(inputf);
            i++;
        }
        i=atoi(cadena);
        for (k=0; k < 4; k++) //limpio mi cadena
            cadena[k]=' ';
        //Para tomar el segundo vértice
        caracter[c]=fgetc(inputf); //el primer dígito del número
        j          =0;
        while (caracter[c] != '\n' && feof(inputf) == 0)
        {
            cadena[j]  =caracter[c];
            caracter[c]=fgetc(inputf);
            j++;
        }
        j=atoi(cadena);
        // printf("\n i %d, j %d ",i,j);
        if (!(i == 0 && j == 0))
        {
            nueva_g[i].Nodo=i;
            nueva_g[j].Nodo=j;
            div_ver        =(j) / 4;
            n_ver          =j % 4;
            for (k=0; k < div; k++)
                if (k == div_ver)
                    nueva_g[i].conexiones[div_ver]=nueva_g[i].conexiones[div_ver] | ((1L) << n_ver);
            div_ver=(i) / 4;
            n_ver  =i % 4;

            //printf("\nn_ver: %d div_ver %d i %d ",n_ver,div_ver,i);
            //  binario(nueva_g[i].conexiones[div_ver]);
            for (k=0; k < div; k++)
                if (k == div_ver)
                    nueva_g[j].conexiones[div_ver]=nueva_g[j].conexiones[div_ver] | ((1L) << n_ver);

            // printf("\nj %d  ",j);
            // binario(nueva_g[j].conexiones[div_ver]);
        }
        caracter[c]=fgetc(inputf);
    }


    fclose(inputf);
    for (i=0; i < v; i++)
    {
        printf(" Conexiones %d:", i);
        for (k=div - 1; k >= 0; k--)
            binario(nueva_g[i].conexiones[k]);
    }
    for (i=0; i < div - 1; i++)
    {
        C0[i]=(unsigned long)(pow(2, 4) - 1);
        N[i] =(unsigned long)(pow(2, 4) - 1);
        b[i] =(unsigned long)(pow(2, 4) - 1);
    }
    C0[i]=(unsigned long)(pow(2, n) - 1);
    N[i] =(unsigned long)(pow(2, n) - 1);
    b[i] =(unsigned long)(pow(2, n) - 1);
    while (l < v)
    {
        i          =l / 4;
        b[i]       =b[i] << 1;
        b[i]       =b[i] & C0[i];
        clique_m[0]=l;
        backtrack(v, l, nueva_g, C0, N, b, 1, div, 0);
        l++;
    }
    printf("\nmaximo clique:");
    for (mc=0; mc < max; mc++)
        printf("%d ", opt_clique[mc]);
    printf("\nTamaño de maximo clique : %d\n", max);
}
