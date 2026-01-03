#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define HAIR_STYLISTS 2
#define MAKEUP_ARTIST 1
#define NUM_CUSTOMERS 6

int available_hairstylist = HAIR_STYLISTS;
int available_makeupartist = MAKEUP_ARTIST;

// pthread_mutex_t book_mutex;   // mutex lock for critical section

pthread_mutex_t hairstylist_mutex;   // mutex lock for critical section
pthread_mutex_t makeupartist_mutex;   // mutex lock for critical section

void* book_service(void* arg) {
    int customer_id = *((int*)arg);

    // pthread_mutex_lock(&book_mutex);   // lock before accessing shared data
    if(service==0)
    {
        pthread_mutex_lock(&hairstylist_mutex);
            //Hair Stylist Logic
        if (available_hairstylist > 0) {
        int stylist = available_hairstylist;
        usleep(rand() % 50000); 
        available_hairstylist--;
        printf("Customer %d booked stylist #%d \n", customer_id, stylist);
        }
          pthread_mutex_unlock(&hairstylist_mutex); // unlock after critical section
    }
    elseif(service==1)
    {
        pthread_mutex_lock(&makeupartist_mutex);
            //makeupstylist Logic
        if (available_makeupstylist > 0) {
        int stylist = available_makeupstylist;
        usleep(rand() % 50000); 
        available_makeupstylist--;
        printf("Customer %d booked stylist #%d \n", customer_id, stylist);
        }
          pthread_mutex_unlock(&makeupartist_mutex); // unlock after critical section
    }


else {
        printf("Customer %d tried to book, but stylist are Busy \n", customer_id);
    }


    //Makeup Artist Logic
    if (available_makeupartist > 0) {
        int artist = available_makeupartist;
        usleep(rand() % 50000); 
        available_makeupartist--;
        printf("Customer %d booked artist #%d \n", customer_id, artist);
        
    } else {
        printf("Customer %d tried to book, but artist are Busy \n", customer_id);
    }




 
    return NULL;
}


int main() {
    pthread_t customers[NUM_CUSTOMERS];
    int customer_ids[NUM_CUSTOMERS];
    srand(time(NULL));
    // pthread_mutex_init(&book_mutex, NULL);
    pthread_mutex_init(&hairstylist_mutex, NULL);
    pthread_mutex_init(&makeupartist_mutex, NULL);


    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        customer_ids[i] = i + 1;
        pthread_create(&customers[i], NULL, book_service, &customer_ids[i]);
    }

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }

    pthread_mutex_destroy(&book_mutex);

    printf("\nAll bookings processed.");
    return 0;
}