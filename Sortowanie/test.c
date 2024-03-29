#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TEST 1

#define DATE_FMT "%02d.%02d.%04d"
#define DATE_FMT_OUT(D) (D).day, (D).month, (D).year
#define DATE_FMT_IN(D) &(D).day, &(D).month, &(D).year
typedef struct {
    int day; 
    int month; 
    int year;
} Date;

/////////////////////////////////////////////////////////////////
// 8.1 funkcja bsearch2

#define FOOD_MAX  30   // max. liczba artykułów
#define ART_MAX   15   // max. długość nazwy artykułu +1
#define RECORD_MAX 40  // max. długość rekordu (linii) w pliku

typedef struct {
    char art[ART_MAX+1]; // for NUL otherwise wasted byte (padding)
    float price;
    float amount;
    Date valid_date;
} Food;

typedef int (*ComparFp)(const void *, const void *);

void *bsearch2(const void *key, void *base, size_t nitems, size_t size, ComparFp compar, char *result) {
	char *blk = base;
	int i = nitems / 2;
	int p = 0;
	for (;;)
	{
		printf("bs: %d[%d]\n", i, nitems);
		void *elem = blk+(i*size);
		float cmp = compar(key, elem);
        printf(" CMP: %f\n",cmp);
		if (cmp == 0)
		{
			printf("bs: found at %d\n", i);
			*result = 1;
			return elem;
		}
		printf("bs: cmp %d\n", cmp);
		int n = (i + (cmp > 0 ? nitems : 0)) / 2;
		if (n == i)
		{
			printf("bs: not found\n");
			*result = 0;
			return elem;
		}
		i = n;
	}
}

int cmp_date(const void *a, const void *b)
{
	const Date *pa = a;
	const Date *pb = b;

	// does not need to return the number of days correctly, just need to include the 'influence' months and years
	unsigned long long da = pa->year * 31 * 12 + pa->month * 31 + pa->day;
	unsigned long long db = pb->year * 31 * 12 + pb->month * 31 + pb->day;

	return da - db;
}

void add_days(Date *d, int days)
{
	int month_days = 0;
	while (days > 0)
	{
		if (d->month != 2) month_days = d->month % 2 ? 30 : 31;
		else month_days = d->year % 4 ? 28 : 29;
		
		if (month_days >= days)
		{
			d->month++;
			if (d->month == 12) 
			{
				d->month = 0;
				d->year++;
			}
			days -= month_days;
		}
		else if (month_days >= days + d->day)
		{
			d->month++;
			if (d->month == 12) 
			{
				d->month = 0;
				d->year++;
			}
			d->day = days - (month_days - d->day);
			days = 0;
		}
		else
		{
			d->day += days;
			days = 0;
		}
	}
}

void print_art(Food *p, size_t n, char *art) {
	for (size_t i = 0; i < n; i++)
	{
		if (!strncmp(p->art, art, ART_MAX + 1))
			printf("%s %.2f %.2f " DATE_FMT "\n", p->art, p->price, p->amount, DATE_FMT_OUT(p->valid_date));
		p++;
	}
}

Food* add_record(Food *tab, size_t tab_size, int *np, ComparFp compar, Food *new) {
	char found;
	Food *food = bsearch2(new, tab, *np, sizeof(Food), compar, &found);
	if (found) 
	{
		printf("found %s\n",food->art);
		food->amount += new->amount;
		printf("amount now %f\n", food->amount);
	}
	else
	{
		if (*np + 1 >= tab_size) return NULL;
		for (Food *c = tab + *np; c >= food; c--)
		memcpy(c+1, c, sizeof(Food));
		memcpy(food, new, sizeof(Food));
		(*np)++;
	}

	return food;
}





int cmp_food_art(const void *a, const void *b)
{
	const Food *pa = a;
	const Food *pb = b;
	
    printf("-------------\n");
    printf("1: %s %d %f 2: %s %d %f \n",pa->art,pa->amount,pa->price,pb->art,pb->amount,pb->price);
    printf("%f \n",pa->price - pb->price);

    printf("-------------\n");
    
    int art_cmp = strncmp(pa->art, pb->art, ART_MAX + 1);
	printf("%s %s -> %d\n", pa->art, pb->art, art_cmp);
	if (art_cmp) return 1;
	printf("cmpfood: art ok\n");
	float price_cmp = pa->price - pb->price;
	if (price_cmp) return 1;
	printf("cmpfood: price ok\n");
	return cmp_date(&pa->valid_date, &pb->valid_date);
}

int cmp_food_date(const void *a, const void *b)
{
	const Food *pa = a;
	const Food *pb = b;
	return cmp_date(&pa->valid_date, &pb->valid_date);
}

int read_stream(Food *tab, size_t size, int no, FILE *stream) {
	Food c;
	int cnt = 0;
	int elems_read;
	for (int i = 0; i < no && i < size; i++)
	{
		elems_read = fscanf(stream, "%15s %f %f " DATE_FMT, c.art, &c.price, &c.amount, DATE_FMT_IN(c.valid_date));
		if (elems_read < 6) return cnt;
		printf("rs: art %s\n", c.art);
		add_record(tab, size, &cnt, cmp_food_art, &c);
	}

	return cnt;
}

int read_stream0(Food *tab, size_t size, int no, FILE *stream) {
	Food c;
	int cnt = 0;
	int elems_read;
	for (int i = 0; i < no && i < size; i++)
	{	
		elems_read = fscanf(stream, "%15s %f %f " DATE_FMT, c.art, &c.price, &c.amount, DATE_FMT_IN(c.valid_date));
		if (elems_read < 6) return cnt;
		printf("rs: art %s\n", c.art);
		memcpy(tab+i, &c, sizeof(Food));	
	}

	return cnt;
}

float value(Food *food_tab, size_t n, Date curr_date, int anticip) {
	add_days(&curr_date, anticip);

	qsort(food_tab, n, sizeof(Food), cmp_food_date);

	float sum = 0;
	// bsearch here
	return sum;
}

/////////////////////////////////////////////////////////////////
// 8.3 Sukcesja

#define CHILD_MAX  20   // maksymalna liczba przesuwanej w tablicy grupy osób (elementów tablicy)

enum Sex {F, M};
enum BOOL {no, yes};

struct Bit_data {
    enum Sex sex:1;
    enum BOOL pretendent:1;   // =no - nie pretenduje (panuje albo nie żyje) ale jest w zbiorze dla spójności relacji.
};

typedef struct {
    char *name;
    struct Bit_data bits;
    Date born;
    char *parent;
} Person;

typedef struct {
    char *par_name;
    int index;
} Parent;    // strukturę można rozbudować o pole liczby dzieci

const Date primo_date = { 28, 10, 2011 }; // Data zmiany kolejności sukcesji

int fill_indices_tab(Parent *idx_tab, Person *pers_tab, int size) {
	return 0;
}

void persons_shiftings(Person *person_tab, int size, Parent *idx_tab, int no_parents) {
}

int cleaning(Person *person_tab, int n) {
	return 0;
}

void print_person(const Person *p) {
    printf("%s\n", p->name);
}

void print_persons(const Person *person_tab, int n) {
    for(int i=1; i<=n; ++i, ++person_tab) printf("%2d %12s %s\n", i, person_tab->name, person_tab->parent);
    return;
}

int create_list(Person *person_tab, int n) {
	return 0;
}

////////////////////////////////////////////////////////////////

int main(void)
{
    // Wszyscy potomkowie Jerzego VI (w kolejności przypadkowej):
    Person person_tab[33]={
    {"Charles III",M,no,14,11,1948,"Elizabeth II"},
    {"Anne",F,yes,15,8,1950,"Elizabeth II"},
    {"Andrew",M,yes,19,2,1960,"Elizabeth II"},
    {"Edward",M,yes,10,3,1964,"Elizabeth II"},
    {"David",M,yes,3,11,1961,"Margaret"},
    {"Sarah",F,yes,1,5,1964,"Margaret"},
    {"William",M,yes,21,6,1982,"Charles III"},
    {"Henry",M,yes,15,9,1984,"Charles III"},
    {"Peter",M,yes,15,11,1977,"Anne"},
    {"Zara",F,yes,15,5,1981,"Anne"},
    {"Beatrice",F,yes,8,8,1988,"Andrew"},
    {"Eugenie",F,yes,23,3,1990,"Andrew"},
    {"James",M,yes,17,12,2007,"Edward"},
    {"Louise",F,yes,8,11,2003,"Edward"},
    {"Charles",M,yes,1,7,1999,"David"},
    {"Margarita",F,yes,14,5,2002,"David"},
    {"Samuel",M,yes,28,7,1996,"Sarah"},
    {"Arthur",M,yes,6,5,2019,"Sarah"},
    {"Georg",M,yes,22,7,2013,"William"},
    {"George VI",M,no,14,12,1895,NULL},
    {"Charlotte",F,yes,22,5,2015,"William"},
    {"Louis",M,yes,23,4,2018,"William"},
    {"Archie",M,yes,6,5,2019,"Henry"},
    {"Lilibet",F,yes,4,6,2021,"Henry"},
    {"Savannah",F,yes,29,12,2010,"Peter"},
    {"Isla",F,yes,29,3,2012,"Peter"},
    {"Mia",F,yes,17,1,2014,"Zara"},
    {"Lena",F,yes,18,6,2018,"Zara"},
    {"Elizabeth II",F,no,21,4,1925,"George VI"},
    {"Margaret",F,no,21,8,1930,"George VI"},
    {"Lucas",M,yes,21,3,2021,"Zara"},
    {"Sienna",F,yes,18,9,2021,"Beatrice"},
    {"August",M,yes,9,2,2021,"Eugenie"}
    };
    
    printf("%d\n",sizeof(Food));

    int to_do, no;
    size_t size, n;
    Food food_tab[FOOD_MAX];
    

    char buff[ART_MAX];
    FILE *file;
    if(TEST) printf("Wpisz nr zadania (1 - 3) ");
    scanf("%d", &to_do);

    switch (to_do) {
    case 1:  // bsearch2
        if (TEST) printf("Wpisz liczbe linii danych: ");
        scanf("%d",&no); getchar();
        if(TEST) file = stdin;
        else {
            scanf("%s",buff);
            file = fopen(buff,"r");
//            file = fopen("foods0.txt","r");
            if(file==NULL) { printf("Error 1\n"); break; }
        }
        if (TEST) printf("W %d liniach wpisuj dane: nazwa cena ilosc dd mm yyyy: \n",no);
        n = read_stream(food_tab,FOOD_MAX,no,file);
        if (TEST) printf("Wpisz nazwe artykulu: ");
        scanf("%s",buff);
        print_art(food_tab,n,buff);
        break;
    case 2: // proste sortowanie struktur
        if (TEST) printf("Wpisz liczbe linii danych: ");
        scanf("%d",&no); getchar();
        if(TEST) file = stdin;
        else {
            scanf("%s",buff);
            file = fopen(buff,"r");
//            file = fopen("foods0.txt","r");
            if(file==NULL) { printf("Error 1\n"); break; }
        }
        if (TEST) printf("W %d liniach wpisuj dane: nazwa cena ilosc dd mm yyyy: \n",no);
        n = read_stream0(food_tab,FOOD_MAX,no,file);
        Date curr_date;
        int anticip;
        if (TEST) printf("Wpisz date odniesienia dd mm yyyy: ");
        scanf("%d %d %d",&curr_date.day,&curr_date.month,&curr_date.year);
        if (TEST) printf("Wpisz roznice dni: ");
        scanf("%d",&anticip);
        printf("%.2f\n",value(food_tab,n,curr_date,anticip));
        break;
    case 3: // sukcesja
        if(TEST==1) printf("Wpisz pozycję w kolejce (liczona od 1): ");
        scanf("%d",&no);
    	int no_persons = sizeof(person_tab) / sizeof(Person);
        no_persons = create_list(person_tab,no_persons);
        if(TEST) print_persons(person_tab,no_persons);
        else print_person(person_tab+no-1);
        break;
    default:
        printf("NOTHING TO DO FOR %d\n", to_do);
    }
    return 0;
}