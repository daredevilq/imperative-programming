
//a):
typedef struct {
    char vehicle_ID[15];
    unsigned int places : 3;
    unsigned int driving_wheels : 3;
    unsigned int towbar : 1;
} Car_data;

typedef union {
    Car_data cs;
    Truck_data ts;
} veh_union;

typedef struct {
    char owner[30]; 
    Date valid_date;
    enum Vehicle_type v_type;
    veh_union vehicle_data;
} Vehicle;


int cmp(const Date *d1, const Date *d2) {
    if (d1->y < d2->y) return -1;
    if (d1->y > d2->y) return 1;
    if (d1->m < d2->m) return -1;
    if (d1->m > d2->m) return 1;
    if (d1->d < d2->d) return -1;
    if (d1->d > d2->d) return 1;

    return 0;
}



int delayed(const Vehicle *tv, int size, const Date *base_date, char ***pdelayed_owners) {

    int counter = 0;
    int index = 0;

    for(int i = 0; i < size; i++) {
        if(cmp(&(tv[i].valid_date), base_date) < 0) {
            counter++;
        }}

 
    *pdelayed_owners = malloc(counter * sizeof(char*));


    for(int i = 0; i < size; i++) {
        if(cmp(&tv[i].valid_date, base_date) < 0) {
            (*pdelayed_owners)[index] = tv[i].owner;
            index++;
            }
        }
   
    return counter;
}

void print_owners(const char **t_owners, size_t size) {

    int end = (int)size;

    for(int i = 0; i < end; i++) {
        printf("%s ", t_owners[i]); // potrzebna biblioteka #include <stdio.h>
    }
}

Vehicle *create_vehicle(void) {
    Vehicle *new_vehicle = malloc(sizeof(Vehicle));
    

    new->valid_date.d = 1;
    new->valid_date.m = 1;
    new->valid_date.y = 1970;
    new->v_type = v_ndef;
    new->owner = NULL;
    return new;
}



void print_v_data(const Vehicle *v) {
    if (v->v_type == car) {
        if  (v->vehicle_data.cs.towbar)
        {
            char str[] = "TAK";
        }
        else{
            char str[] = "NIE";
        }
    
        printf("Car: ID: %s, miejsc: %d, naped na: %d kola, hak: %s\n", v->vehicle_data.cs.vehicle_ID,
            v->vehicle_data.cs.places,
            v->vehicle_data.cs.driving_wheels,
            str)


    } else if (v->v_type == truck) { // zakladam ze wypisujemy tez truck, ew jesli nie trzeba to 
                                    // zostawiamy  if (v->v_type == car) ...
        printf("Truck: load: %f, axes: %d, trailer_mass: %d", 
            v->vehicle_data.ts.load,
            v->vehicle_data.ts.axes,
            v->vehicle_data.ts.trailer_mass);
    }
}

int cmp_date(Date d1, Date d2) {

    if (d1.y != d2.y) {
        return d1.y - d2.y;
    }
    if (d1.m != d2.m) {
        return d1.m - d2.m;
    }
    return d1.d - d2.d;
}


int date_comparator(const void *a, const void *b) {
    Vehicle *v1 = (Vehicle *)a;
    Vehicle *v2 = (Vehicle *)b;
    return cmp_date(v1->valid_date, v2->valid_date);
}

