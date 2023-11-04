#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
	int day;
	int month;
	int year;
} Date;

// 1 bsearch2

#define FOOD_MAX 30	  // max. number of goods
#define ART_MAX 15	  // max. length of name's name + 1
#define RECORD_MAX 40 // max. line length

typedef struct
{
	char name[20];
	float price;
	int amount;
	Date valid_date;
} Food;

typedef int (*ComparFp)(const void *, const void *);

// compare dates
int cmp_date3(const void *d1, const void *d2)
{

	const Date *date1 = d1;
	const Date *date2 = d2;
	unsigned long long a = date1->year * 12 * 31 + date1->month * 31 + date1->day;
	unsigned long long b = date2->year * 12 * 31 + date2->month * 31 + date2->day;
	return a - b;
}


int cmp_date(const void *d1, const void *d2)
{
	Date *date1 = (Date *)d1;
	Date *date2 = (Date *)d2;

	if (date1->year < date2->year)
		return -1;
	if (date1->year < date2->year)
		return 1;
	if (date1->month < date2->month)
		return -1;
	if (date1->month > date2->month)
		return 1;
	if (date1->day < date2->day)
		return 1;
	if (date1->day > date2->day)
		return -1;
	return 0;
}

int cmp_date2(const void *d1, const void *d2)
{
	Date *date1 = (Date *)d1;
	Date *date2 = (Date *)d2;

	if (date1->year < date2->year)
		return -1;
	if (date1->year < date2->year)
		return 1;
	if (date1->month < date2->month)
		return -1;
	if (date1->month > date2->month)
		return 1;
	if (date1->day < date2->day)
		return 1;
	if (date1->day > date2->day)
		return -1;
	return 0;
}

// compare foods
int cmp2(const void *a, const void *b)
{
	const Food *pa = a;
	const Food *pb = b;

	int art_cmp = strncmp(pa->name, pb->name, ART_MAX + 1);
	if (art_cmp)
		return 1;
	float price_cmp = pa->price - pb->price;
	if (price_cmp)
		return 1;
	return cmp_date(&pa->valid_date, &pb->valid_date);
}

int cmp(const void *a, const void *b) {

    Food *prod1 = (Food*)a;
    Food *prod2 = (Food*)b;
    int comparison = strcmp(prod1->name, prod2->name);

    if (comparison < 0) return -1;
    if (comparison > 0) return 1;
    if (prod1->price < prod2->price) return -1;
    if (prod1->price > prod2->price) return 1;
    return cmp_date(&prod1->valid_date, &prod2->valid_date);

}


// bsearch returning address where to insert new element
void *bsearch2(const void *key, void *base, size_t nmemb, size_t size, ComparFp compar, char *result)
{
	char *blk = base;
	int i = nmemb / 2;
	int p = 0;
	for (;;)
	{

		void *elem = blk + (i * size);
		int cmp = compar(key, elem);

		if (cmp == 0)
		{
			*result = 1;
			return elem;
		}

		int n = (i + (cmp > 0 ? nmemb : 0)) / 2;
		if (n == i)
		{
			*result = 0;
			return elem;
		}
		i = n;
	}
}

// print goods of given name
void print_art(Food *p, int n, char *art)
{
    for (int i = 0; i < n; i++)
        if (strcmp(p[i].name, art) == 0)
            printf("%.2f %.2d %02d.%02d.%d\n", p[i].price, p[i].amount, p[i].valid_date.day, p[i].valid_date.month, p[i].valid_date.year);
}

// add record to table if absent
int add_record(Food *tab, int np, ComparFp compar, Food *new) {
    for (int i = 0; i < np; i++){
        int comparison = strcmp(tab[i].name, new->name);
        if (comparison == 0){
            comparison = compar(&tab[i], new);
            if (comparison == 0){
                tab[i].amount = tab[i].amount + new->amount;
                return -1;
            }
        }
    }
    tab[np] = *new;
    return 1;
}

// read no lines of data
// calls add_record if sorted = 1 and just adds element if sorted = 0
int read_goods(Food *tab, int no, FILE *stream) {
    int count = 0;
    for (int i = 0; i < no; i++){
        Food prod;
        fscanf(stream, "%s %f %d %d.%d.%d", prod.name, &prod.price, &prod.amount, &prod.valid_date.day, &prod.valid_date.month, &prod.valid_date.year);
        int res = add_record(tab, count, cmp, &prod);
        if (res > 0) count++;
    }
    return count;
}

int cmp_qs(const void *a, const void *b)
{
	Food *fa = (Food *)a, *fb = (Food *)b;
	return cmp_date(&fa->valid_date, &fb->valid_date);
}

int cmp_bs(const void *a, const void *b)
{
	Date *pd = (Date *)a;
	Food *fb = (Food *)b;
	return cmp_date(pd, &fb->valid_date);
}
time_t dateToSeconds(int year, int month, int day) {
    struct tm date = {0};
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;

    return mktime(&date);
}
// finds the value of goods due on 'curr_date'
float value2(Food *food_tab, size_t n, Date curr_date, int days)
{
	float value_of_lost_products = 0;
	int sum_days_current_date = 0;

	sum_days_current_date = curr_date.year * 12 * 31 + curr_date.month * 12 + curr_date.day + days;

	for (int i = 0; i < n; i++)
	{
		int sum_days_of_product = 0;
		sum_days_of_product = food_tab[i].valid_date.year * 12 * 31 + food_tab[i].valid_date.month * 12 + food_tab[i].valid_date.day;

		if (sum_days_of_product <= sum_days_current_date)
		{
			value_of_lost_products += food_tab[i].amount * food_tab[i].price;
		}
	}

	return value_of_lost_products;
}

float value(Food *food_tab, size_t n, Date curr_date, int days) {

    time_t to_add_seconds = days*86400;
    time_t curr_seconds = dateToSeconds(curr_date.year, curr_date.month, curr_date.day);

    float lost_value = 0;
    int i = 0;
    while (i < n){
        time_t date_seconds = dateToSeconds(food_tab[i].valid_date.year, food_tab[i].valid_date.month, food_tab[i].valid_date.day);
        if (date_seconds == curr_seconds + to_add_seconds){
            lost_value = lost_value + food_tab[i].amount*food_tab[i].price;
        }
        i++;
    }
    return lost_value;
}


/////////////////////////////////////////////////////////////////
// 3 Succession

#define CHILD_MAX 20

enum Sex
{
	F,
	M
};
enum BOOL
{
	no,
	yes
};

struct Bit_data
{
	enum Sex sex : 1;
	enum BOOL in_line : 1;
};

typedef struct
{
	char *name;
	struct Bit_data bits;
	Date born;
	char *parent;
} Person;

typedef struct
{
	char *par_name;
	int index;
	int no_children;
} Parent;

const Date primo_date = {28, 10, 2011}; // new succession act

int cmp_primo(Person *person1, Person *person2)
{
	if (person1->bits.sex == person2->bits.sex)
		return 0;
	if (person1->bits.sex == F && cmp_date2(&person1->born, &primo_date) > 0)
		return 0;
	if (person2->bits.sex == F && cmp_date2(&person2->born, &primo_date) > 0)
		return 0;
	return person2->bits.sex - person1->bits.sex;
}

// compare persons
int cmp_person(const void *a, const void *b)
{
	const Person *p1 = (Person *)a;
	const Person *p2 = (Person *)b;

	if (p1->parent == NULL)
	{
		return -1;
	}
	else if (p2->parent == NULL)
	{
		return 1;
	}

	if (p1->parent == NULL)
	{
		return -1;
	}
	else if (p2->parent == NULL)
	{
		return 1;
	}

	int parent = strcmp(p1->parent, p2->parent);
	if (parent < 0)
	{
		return -1;
	}
	else if (parent > 0)
	{
		return 1;
	}
	else
	{
		int born_date = cmp_date2(&p1->born, &p2->born);
		if (cmp_date2(&p1->born, &primo_date) < 0 && cmp_date2(&p2->born, &primo_date) < 0)
		{
			if ((p1->bits.sex == 'M') && (p2->bits.sex == 'F'))
			{
				return -1;
			}
			else if ((p1->bits.sex == 'F') && (p2->bits.sex == 'M'))
			{
				return 1;
			}
		}
		if (born_date < 0)
		{
			return -1;
		}
		else if (born_date > 0)
		{
			return 1;
		}
		else
		{
			if (p1->bits.sex > p2->bits.sex)
			{
				return 1;
			}
			else if (p1->bits.sex < p2->bits.sex)
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
	}
}

int fill_indices_tab(Parent *idx_tab, Person *pers_tab, int size)
{
	int no_parents = 0;
	for (int i = 0; i < size; i++)
	{
		idx_tab[i].par_name = pers_tab[i].name;
	}
	for (int i = 0; i < size; i++)
	{
		idx_tab[i].index = 0;
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pers_tab[j].parent == idx_tab[i].par_name)
			{
				idx_tab[i].index = j;
				break;
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		int start = idx_tab[i].index;
		int cnt = 0;
		for (int j = start; j < size; j++)
		{
			if (pers_tab[j].parent == pers_tab[i].name)
			{
				cnt += 1;
			}
			else
			{
				break;
			}
		}
		idx_tab[i].no_children = cnt;
	}
	for (int i = 0; i < size; i++)
	{
		if (idx_tab[i].no_children > 0)
		{
			no_parents += 1;
		}
	}
	return no_parents;
}

void persons_shifts(Person *person_tab, int size, Parent *idx_tab, int no_parents)
{
	for (int i = 0; i < size; i++)
	{
		if (idx_tab[i].no_children > 0)
		{
			Person *arr = malloc((idx_tab[i].no_children) * sizeof(Person));
			memmove(arr, &person_tab[idx_tab[i].index], (idx_tab[i].no_children) * sizeof(Person));
			int amount = idx_tab[i].index - i - 1;
			int where = idx_tab[i].index - amount + idx_tab[i].no_children;
			memmove(&person_tab[where], &person_tab[i + 1], amount * sizeof(Person));
			memmove(&person_tab[i + 1], arr, idx_tab[i].no_children * sizeof(Person));
			free(arr);
			no_parents = fill_indices_tab(idx_tab, person_tab, size);
		}
	}
}

int cleaning(Person *person_tab, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (person_tab[i].bits.in_line == no)
		{
			memmove(&person_tab[i], &person_tab[i + 1], (n - (i + 1)) * sizeof(Person));
			n -= 1;
			i -= 1;
		}
	}
	return n;
}

void print_person(const Person *p)
{
	printf("%s\n", p->name);
}

int create_list(Person *person_tab, int n)
{
	qsort(person_tab, n, sizeof(Person), cmp_person);
	Parent id_tab[33];
	int num_par = 0;
	num_par = fill_indices_tab(id_tab, person_tab, n);
	persons_shifts(person_tab, n, id_tab, num_par);
	int num_per = 0;
	num_per = cleaning(person_tab, n);
	return num_per;
}

int main(void)
{
	Person person_tab[] = {
		{"Charles III", {M, no}, {14, 11, 1948}, "Elizabeth II"},
		{"Anne", {F, yes}, {15, 8, 1950}, "Elizabeth II"},
		{"Andrew", {M, yes}, {19, 2, 1960}, "Elizabeth II"},
		{"Edward", {M, yes}, {10, 3, 1964}, "Elizabeth II"},
		{"David", {M, yes}, {3, 11, 1961}, "Margaret"},
		{"Sarah", {F, yes}, {1, 5, 1964}, "Margaret"},
		{"William", {M, yes}, {21, 6, 1982}, "Charles III"},
		{"Henry", {M, yes}, {15, 9, 1984}, "Charles III"},
		{"Peter", {M, yes}, {15, 11, 1977}, "Anne"},
		{"Zara", {F, yes}, {15, 5, 1981}, "Anne"},
		{"Beatrice", {F, yes}, {8, 8, 1988}, "Andrew"},
		{"Eugenie", {F, yes}, {23, 3, 1990}, "Andrew"},
		{"James", {M, yes}, {17, 12, 2007}, "Edward"},
		{"Louise", {F, yes}, {8, 11, 2003}, "Edward"},
		{"Charles", {M, yes}, {1, 7, 1999}, "David"},
		{"Margarita", {F, yes}, {14, 5, 2002}, "David"},
		{"Samuel", {M, yes}, {28, 7, 1996}, "Sarah"},
		{"Arthur", {M, yes}, {6, 5, 2019}, "Sarah"},
		{"George", {M, yes}, {22, 7, 2013}, "William"},
		{"George VI", {M, no}, {14, 12, 1895}, NULL},
		{"Charlotte", {F, yes}, {2, 5, 2015}, "William"},
		{"Louis", {M, yes}, {23, 4, 2018}, "William"},
		{"Archie", {M, yes}, {6, 5, 2019}, "Henry"},
		{"Lilibet", {F, yes}, {4, 6, 2021}, "Henry"},
		{"Savannah", {F, yes}, {29, 12, 2010}, "Peter"},
		{"Isla", {F, yes}, {29, 3, 2012}, "Peter"},
		{"Mia", {F, yes}, {17, 1, 2014}, "Zara"},
		{"Lena", {F, yes}, {18, 6, 2018}, "Zara"},
		{"Elizabeth II", {F, no}, {21, 4, 1925}, "George VI"},
		{"Margaret", {F, no}, {21, 8, 1930}, "George VI"},
		{"Lucas", {M, yes}, {21, 3, 2021}, "Zara"},
		{"Sienna", {F, yes}, {18, 9, 2021}, "Beatrice"},
		{"August", {M, yes}, {9, 2, 2021}, "Eugenie"}};

	int to_do, no;
	int n;
	Food food_tab[FOOD_MAX];
	char buff[ART_MAX];
	fgets(buff, ART_MAX, stdin);
	sscanf(buff, "%d", &to_do);

	switch (to_do)
	{
	case 1: // bsearch2
		fgets(buff, ART_MAX, stdin);
		sscanf(buff, "%d", &no);
		n = read_goods(food_tab, no, stdin);
		scanf("%s", buff);
		qsort(food_tab, n, sizeof(Food), cmp);
		print_art(food_tab, n, buff);
		break;
	case 2: // qsort
		fgets(buff, ART_MAX, stdin);
		sscanf(buff, "%d", &no);
		n = read_goods(food_tab, no, stdin);
		Date curr_date;
		int days;
		scanf("%d %d %d", &curr_date.day, &curr_date.month, &curr_date.year);
		scanf("%d", &days);
		printf("%.2f\n", value(food_tab, (size_t)n, curr_date, days));
		break;
	case 3: // succession
		scanf("%d", &no);
		int no_persons = sizeof(person_tab) / sizeof(Person);
		create_list(person_tab, no_persons);
		print_person(person_tab + no - 1);
		break;
	default:
		printf("NOTHING TO DO FOR %d\n", to_do);
	}
	return 0;
}
