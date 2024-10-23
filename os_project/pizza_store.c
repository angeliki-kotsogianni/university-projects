#include "p3220103-p3220172-pizza.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t mutex_phones, mutex_cooks, mutex_ovens, mutex_deliverers, mutex_stats; // ta aparaitita mutexes
pthread_cond_t cond_phones, cond_cooks, cond_ovens, cond_deliverers, cond_stats; // ta aparaitita condition variables

int available_phones = Ntel, available_cooks = Ncook, available_ovens = Noven, available_deliverers = Ndeliverer;

// gia thn ektiposi sto telos
int total_sales = 0, successful_orders = 0, failed_orders = 0;
int sold_margarita = 0, sold_pepperoni = 0, sold_special = 0;
int n_customers_completed = 0;
int n_customers;
int total_time = 0;
int max = -1;
int total_cold_time = 0;
int max_cold = -1;

void *process_order(void *arg) { // h diadikasia ths kathe paraggelias
    int oid = *((int *) arg);
    int rc;
    time_t start_prep, end_prep, end_delivery, start_cold; // gia tous xronous pou tha ektiposoume

    rc = pthread_mutex_lock(&mutex_phones);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(arg);
	}
    while (available_phones <= 0) {
        rc = pthread_cond_wait(&cond_phones, &mutex_phones);
        if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
			pthread_exit(arg);
		}
    }
    available_phones--;
    rc = pthread_mutex_unlock(&mutex_phones);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(arg);
	}
	
	start_prep = time(NULL); // ksekinaei na etimazetai
    sleep(rand() % (Torderhigh - Torderlow + 1) + Torderlow); // o xronos ths kathe paraggelias

    int n_pizzas = rand() % (Norderhigh - Norderlow + 1) + Norderlow; // tixaia epilogi arithmwn pitsas
    int *pizzas = malloc(n_pizzas * sizeof(int));

    for (int i = 0; i < n_pizzas; i++) { // eidos kathe pitsas
        double prob = (double) rand() / RAND_MAX;
        if (prob < Pm) {
            pizzas[i] = Cm;
        } else if (prob < Pm + Pp) {
            pizzas[i] = Cp;
        } else {
            pizzas[i] = Cs;
        }
    }
    
    n_customers_completed++;

    sleep(rand() % (Tpaymenthigh - Tpaymentlow + 1) + Tpaymentlow); // h diadikasia ths pliromis
    
    if ((double) rand() / RAND_MAX < Pfail) { // an failed
        printf("Η παραγγελία με αριθμό %d απέτυχε.\n", oid);
        rc = pthread_mutex_lock(&mutex_phones);
        if (rc != 0) {	
			printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
			pthread_exit(arg);
		}
        available_phones++;
        rc = pthread_cond_signal(&cond_phones);
        if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
			pthread_exit(arg);
		}
        rc = pthread_mutex_unlock(&mutex_phones);
        if (rc != 0) {	
			printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
			pthread_exit(arg);
		}
        failed_orders++;
        return NULL;
    }

    printf("Η παραγγελία με αριθμό %d καταχωρήθηκε.\n", oid); // an completed
    successful_orders++;
    
    for (int i = 0; i < n_pizzas; i++) {
    	if (pizzas[i] == Cm){
    		sold_margarita++;
    		total_sales += Cm;
    	} else if (pizzas[i] == Cp){
    		sold_pepperoni++;
    		total_sales += Cp;
    	} else {
    		sold_special++;
    		total_sales += Cs;
    	}
    } 

    rc = pthread_mutex_lock(&mutex_phones); // afu oloklirothike h tilefoniki paraggelia kane lock ton mutex wste na afksisei tus tilefonites
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(arg);
	}
    available_phones++;
    rc = pthread_cond_signal(&cond_phones);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
		pthread_exit(arg);
	}
    rc = pthread_mutex_unlock(&mutex_phones);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(arg);
	}

    // proetimasia paraggelias
    rc = pthread_mutex_lock(&mutex_cooks);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(arg);
	}
    while (available_cooks <= 0) {
        rc = pthread_cond_wait(&cond_cooks, &mutex_cooks);
        if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
			pthread_exit(arg);
		}
    }
    available_cooks--;
    rc = pthread_mutex_unlock(&mutex_cooks);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(arg);
	}

    sleep(n_pizzas * Tprep); // oso etimazodai oi pitses

    rc = pthread_mutex_lock(&mutex_ovens);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(arg);
	}
	
    while (available_ovens < n_pizzas) { // wste na psithun oles taftoxrona
        rc = pthread_cond_wait(&cond_ovens, &mutex_ovens);
        if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
			pthread_exit(arg);
		}
    }
    
    available_ovens -= n_pizzas;
    rc = pthread_mutex_unlock(&mutex_ovens); // valame tis pitses ara unlock ton mutex twn fournwn
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(arg);
	}
	
	rc = pthread_mutex_lock(&mutex_cooks); // afu valame tis pitses lock to mutex twn cooks wste na afksithei to availability tous
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(arg);
	}
    available_cooks++;
    rc = pthread_cond_signal(&cond_cooks);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
		pthread_exit(arg);
	}
    rc = pthread_mutex_unlock(&mutex_cooks);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(arg);
	}

    sleep(Tbake); // gia osi ora psinodai
    start_cold = time(NULL);

    rc = pthread_mutex_lock(&mutex_deliverers); // afu psithikan ora gia to paketarisma kai thn paradosi
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(arg);
	}
    while (available_deliverers <= 0) {
        rc = pthread_cond_wait(&cond_deliverers, &mutex_deliverers);
        if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
			pthread_exit(arg);
		}
    }
    available_deliverers--;
    rc = pthread_mutex_unlock(&mutex_deliverers);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(arg);
	}
	
	sleep(Tpack * n_pizzas); // paketarisma
	end_prep = time(NULL); // telos proetimasias
	double prep_time = difftime(end_prep, start_prep);
	printf("Η παραγγελία με αριθμό %d ετοιμάστηκε σε %.2f λεπτά.\n", oid, prep_time);
	
	rc = pthread_mutex_lock(&mutex_ovens); // afu paketaristhkan lock to mutex twn fournwn wste na afksithei to availability tous
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(arg);
	}
    available_ovens += n_pizzas;
    rc = pthread_cond_broadcast(&cond_ovens);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_broadcast() is %d\n", rc);
		pthread_exit(arg);
	}
    rc = pthread_mutex_unlock(&mutex_ovens);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(arg);
	}
	
    sleep(rand() % (Tdelhigh - Tdellow + 1)); // paradosi
    
    end_delivery = time(NULL);
    double cold_time = difftime(end_delivery, start_cold); 
    double delivery_time = difftime(end_delivery, start_prep); 
    printf("Η παραγγελία με αριθμό %d παραδόθηκε σε %.2f λεπτά.\n", oid, delivery_time);
    total_time += delivery_time; // sinolikos xronos kriomatos
    total_cold_time += cold_time; // sinolikos xronos eksipiretisis
    
    if (delivery_time > max){
    	max = delivery_time;
    }
    
    if (cold_time > max_cold){
    	max_cold = cold_time;
    }
    
    
    
    sleep(rand() % (Tdelhigh - Tdellow + 1)); // epistrofi

    rc = pthread_mutex_lock(&mutex_deliverers); // epestrepse o dianomeas ara lock to mutex twn dianomewn wste na afksithei to availability tous
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(arg);
	}
    available_deliverers++;
    rc = pthread_cond_signal(&cond_deliverers);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
		pthread_exit(arg);
	}
    rc = pthread_mutex_unlock(&mutex_deliverers);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(arg);
	}

    free(pizzas); // telos me th  paraggelia ara apeleftherosi mnimis
    pthread_exit(arg);
}

void *parent_thread(void *arg) { // to arxiko nima
    pthread_t stats_thread;
    int rc;
    
    // ta Ncust nimata
    pthread_t *threads = malloc(n_customers * sizeof(pthread_t));
    if (threads == NULL) {
        printf("Not enough memory");
        pthread_exit(arg);
    }
    for (int i = 0; i < n_customers; i++) {
        int *customer_id = malloc(sizeof(int));
        if (customer_id == NULL) {
            printf("Not enough memory");
            pthread_exit(arg);
        }
        *customer_id = i + 1;
        if (pthread_create(&threads[i], NULL, process_order, customer_id) != 0) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            pthread_exit(arg);
        }
    }
    
    // perimenodas ta customer threads na teliosun
    for (int i = 0; i < n_customers; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // afu teliosan oi paraggelies ektiposi twn statistikwn
    rc = pthread_mutex_lock(&mutex_stats);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(arg);
	}
    while (n_customers_completed < n_customers) {
        rc = pthread_cond_wait(&cond_stats, &mutex_stats);
        if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
			pthread_exit(arg);
		}
    }
    rc = pthread_mutex_unlock(&mutex_stats);
    if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(arg);
	}

    printf("Συνολικές πωλήσεις: %d\n", total_sales);
    printf("Επιτυχημένες παραγγελίες: %d, Αποτυχημένες παραγγελίες: %d\n", successful_orders, failed_orders);
    printf("Πωλήθηκαν:\n%d Μαργαρίτες\n%d Πεπερόνι\n%d Σπέσιαλ\n", sold_margarita, sold_pepperoni, sold_special);
    double avg_time = total_time / successful_orders;
    printf("Μέσος χρόνος εξυπηρέτησης: %.2f\n", avg_time);
    printf("Μέγιστος χρόνος εξυπηρέτησης: %d\n", max);
    double avg_cold_time = total_cold_time / successful_orders;
	printf("Μέσος χρόνος κρυώματος: %.2f\n", avg_cold_time);
    printf("Μέγιστος χρόνος κρυώματος: %d\n", max_cold);
    
    free(threads);
    pthread_exit(arg);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <number of customers> <random seed>\n", argv[0]);
        return 1;
    }
	
    n_customers = atoi(argv[1]);
    srand(atoi(argv[2]));

	int rc;
	
    // arxikopoihsh mutexes kai cond
    pthread_mutex_init(&mutex_phones, NULL);
    pthread_cond_init(&cond_phones, NULL);
    pthread_mutex_init(&mutex_cooks, NULL);
    pthread_cond_init(&cond_cooks, NULL);
    pthread_mutex_init(&mutex_ovens, NULL);
    pthread_cond_init(&cond_ovens, NULL);
    pthread_mutex_init(&mutex_deliverers, NULL);
    pthread_cond_init(&cond_deliverers, NULL);
    pthread_mutex_init(&mutex_stats, NULL);
    pthread_cond_init(&cond_stats, NULL);
    
    pthread_t parent_thread_id;
    rc = pthread_create(&parent_thread_id, NULL, parent_thread, NULL);
    if (rc != 0) {
    		printf("ERROR: return code from pthread_create() is %d\n", rc);
       		exit(-1);
	}

	pthread_join(parent_thread_id, NULL);
    // cleanup
    rc = pthread_mutex_destroy(&mutex_phones);
    if (rc != 0) {
		printf("ERROR: return code from pthread_mutex_destroy() is %d\n", rc);
		exit(-1);		
	}

    rc = pthread_cond_destroy(&cond_phones);
    if (rc != 0) {
		printf("ERROR: return code from pthread_cond_destroy() is %d\n", rc);
		exit(-1);		
	}
	
    rc = pthread_mutex_destroy(&mutex_cooks);
    if (rc != 0) {
		printf("ERROR: return code from pthread_mutex_destroy() is %d\n", rc);
		exit(-1);		
	}

    rc = pthread_cond_destroy(&cond_cooks);
    if (rc != 0) {
		printf("ERROR: return code from pthread_cond_destroy() is %d\n", rc);
		exit(-1);		
	}
    rc = pthread_mutex_destroy(&mutex_ovens);
    if (rc != 0) {
		printf("ERROR: return code from pthread_mutex_destroy() is %d\n", rc);
		exit(-1);		
	}

    rc = pthread_cond_destroy(&cond_ovens);
    if (rc != 0) {
		printf("ERROR: return code from pthread_cond_destroy() is %d\n", rc);
		exit(-1);		
	}
    rc = pthread_mutex_destroy(&mutex_deliverers);
    if (rc != 0) {
		printf("ERROR: return code from pthread_mutex_destroy() is %d\n", rc);
		exit(-1);		
	}

    rc = pthread_cond_destroy(&cond_deliverers);
    if (rc != 0) {
		printf("ERROR: return code from pthread_cond_destroy() is %d\n", rc);
		exit(-1);		
	}
    return 1;
}
