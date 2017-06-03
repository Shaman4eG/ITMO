#include <stdio.h>

/*
void tri(int* p_p_array2)
{
    printf("p_p_array2 = %p\n", p_p_array2);
    printf("&p_p_array2 = %p\n", &p_p_array2);
    printf("*p_p_array2 = %p\n", *p_p_array2);
    //printf("**p_p_array2 = %p\n", **p_p_array2);
    printf("&*p_p_array2 = %p\n\n", &*p_p_array2);
    short i = 4;
    for (i; i >= 0; i--)
    {
        p_p_array2[i] = 3;
        printf("p_p_array2[%i]  = %i\n", i, p_p_array2[i]);
    }
    //int a = 1;
    //*p_p_array2 = a;
    //printf("\n&a = %p\n", &a);
    printf("\np_p_array2 = %p\n", p_p_array2);
    printf("&p_p_array2 = %p\n", &p_p_array2);
    printf("*p_p_array2 = %p\n", *p_p_array2);
    //printf("**p_p_array2 = %p\n", **p_p_array2);
    printf("&*p_p_array2 = %p\n", &*p_p_array2);
}
*/

int main()
{
    //–¿«Ã≈–€ “»œŒ¬
    /*
    char qa;
    short ws;
    int ed;
    long rf;
    long long tg;
    float yh;
    double uj;
    printf("char      = %i\n", sizeof(qa));
    printf("short     = %i\n", sizeof(ws));
    printf("int       = %i\n", sizeof(ed));
    printf("long      = %i\n", sizeof(rf));
    printf("long long = %i\n", sizeof(tg));
    printf("float     = %i\n", sizeof(yh));
    printf("double    = %i\n", sizeof(uj));
    */


    //—“–” “”–¿
    /*
    struct memes
    {
        int Vova;
        int dcp;
    };
    struct memes kek;
    scanf("%i", &kek.Vova);
    kek.dcp = 2;
    printf("\nVova = %i\n", kek.Vova);
    printf("dcp = %i\n", kek.dcp);
    */


    //” ¿«¿“≈À» Õ¿ ” ¿«¿“≈À» Õ¿ ” ¿«¿“≈À»
    /*
    int *lel;
    int rer = 1;
    int tro = 2;
    lel = &rer;
    int **p_lel = &lel;
    int ***p_p_lel = &p_lel;
    printf("&p_lel     = %p\n", &p_lel);
    printf("p_p_lel    = %p\n", p_p_lel);
    printf("*p_p_lel   = %p\n", *p_p_lel);
    printf("**p_p_lel  = %p\n", **p_p_lel);
    printf("***p_p_lel = %p\n\n", ***p_p_lel);
    int *plel = &lel;
    printf("&rer       = %p\n", &rer);
    printf("lel        = %p\n", lel);
    printf("&lel       = %p\n", &lel);
    printf("plel       = %p\n", plel);
    printf("*plel      = %p\n", *plel);
    printf("p_lel      = %p\n", p_lel);
    printf("*p_lel     = %p\n", *p_lel);
    printf("**p_lel    = %p\n\n", **p_lel);
    *p_lel = &tro;
    printf("&tro       = %p\n", &tro);
    printf("p_lel      = %p\n", p_lel);
    printf("*p_lel     = %p\n", *p_lel);
    printf("**p_lel    = %p\n\n", **p_lel);
    **p_lel = &tro;
    printf("p_lel      = %p\n", p_lel);
    printf("*p_lel     = %p\n", *p_lel);
    printf("**p_lel    = %p\n\n", **p_lel);

    int *lal;
    lal = *p_lel;
    printf("*lal    = %p\n", *lal);
    int m;
    m = *lal;
    printf("m       = %p\n", m);
    //p_lel = &rer;
    printf("*lel    = %p\n", *lel);
    */


    //¿ƒ–≈—Õ¿ﬂ ¿–»‘Ã≈“» ¿
    /*
    int tap[5] = {1,2,3,4,5};
    int *pol = &tap;
    printf("&tap    = %p\n", &tap);
    printf("&tap[2] = %p\n", &tap[2]);
    printf("&pol    = %p\n", &pol);
    printf("pol     = %p\n", pol);
    printf("*pol    = %i\n\n", *pol);
    pol += 2;
    printf("pol     = %p\n", pol);
    printf("*pol    = %i\n\n", *pol);
    *pol = *pol - 1;
    printf("pol     = %p\n", pol);
    printf("*pol    = %i\n", *pol);
    printf("tap[2]  = %i\n\n", tap[2]);
    *pol++;
    printf("pol     = %p\n", pol);
    printf("*pol    = %i\n\n", *pol);
    *pol += 2;
    printf("pol     = %p\n", pol);
    printf("*pol    = %i\n\n", *pol);

    int sen = 10;
    int *port = &sen;
    printf("&sen    = %p\n", &sen);
    sen = *port - *pol;
    port = &tap[0];
    printf("pol     = %p\n", pol);
    printf("port    = %p\n", port);
    printf("sen = *port - *pol = %i\n", sen);
    sen = pol - port;
    printf("sen =  pol  - port = %i\n\n", sen);

    int a_ok = 42; //ÔÓÒÚÓ ÔÂÂÏÂÌÌ‡ˇ
    int *p_a = &a_ok; //ÒÒ˚ÎÍ‡ Ì‡ a
    int *p_a2 = p_a + 5; //p_a2 ÒÒ˚Î‡ÂÚÒˇ Ì‡ p_a + 5*sizeof(int)
    printf("p_a > p_a2  -> %i\n", p_a > p_a2); //‚˚‚Ó‰: 0
    printf("p_a < p_a2  -> %i\n", p_a < p_a2); //‚˚‚Ó‰: 1
    printf("p_a == p_a2 -> %i\n", p_a == p_a2); //‚˚‚Ó‰: 0
    printf("p_a != p_a2 -> %i\n\n", p_a != p_a2); //‚˚‚Ó‰: 1

    void *rek = 3;
    int *lock = (int*)rek;
    int lom = 5;
    int rok;
    rok = (int*)rek;
    rek = &lom;
    printf("&lom = %p\n", &lom);
    printf("rek  = %p\n", rek);
    printf("rok  = %i\n", rok);
    printf("lock = %i\n", lock);
    */


    //—“–Œ »
    /*
    char kach[6];
    int i;
    for (i = 0; i < 10; i++)
    {
        if (kach[i] == '\0')
                printf("\ngg\n");
        else
            printf("%c", kach[i]);
    }
    //printf("\n%c", kach[3]);
    printf("\n%i", strlen(kach));
    */

    //UNSIGNED INT —“–¿ÕÕŒ—“»
    /*
    unsigned int a;
    scanf("%i", &a);
    printf("a = %i", a);
    */

    /*
    int *p_array2;
    int b = 0;
    int *q;

    float c = 1.1;
    double d = 12.4;
    q = &b;
    p_array2 = &b;

    printf("\n*p  =  %p\n", *p_array2);
    printf("p   =  %p\n", p_array2);
    printf("&b  =  %p\n", &b);
    //printf("b i = %i\n", b);
    printf("b p =  %p\n", b);
    //printf("c = %p\n", c);
    //printf("d = %p\n", d);
    printf("&p  =  %p\n", &p_array2);
    printf("&*p =  %p\n", (&*p_array2));

    //ƒ»Õ¿Ã»◊≈— Œ≈ ¬€ƒ≈À≈Õ»≈ œ¿Ãﬂ“»
    int arraySize = 5;
    if ((p_array2 = (int*) malloc(arraySize*sizeof(int))) == NULL)
    {
        printf("Unable to allocate memory.\n");
        getchar();
        exit(1);
    }

    printf("\n*p  =  %p\n", *p_array2);
    printf("p   =  %p\n", p_array2);
    printf("&*p =  %p\n", (&*p_array2));

    short i = 0;
    //for (i; i < arraySize; i++)
   // {
       // printf("\np_array2[%d] = %i", i, i);
        //p_array2[i] = i;
      //  printf("\nADRESS p_array2[%d] = %p", i, &p_array2[i]);
    //}
    printf("\n\n");

    tri(p_array2);

    printf("\n*p  =  %i\n", *p_array2);
    */
    return 0;
}
