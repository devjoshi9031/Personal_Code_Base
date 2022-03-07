targets = mutex semaphore prod_cons
FLAGS = -o
EXTRA_FLAGS = -lpthread

all: $(targets)


mutex: main_mutex.c
	gcc $(FLAGS) $@ $^ $(EXTRA_FLAGS)

semaphore: main_semaphore.c
	gcc $(FLAGS) $@ $^ $(EXTRA_FLAGS)

prod_cons: producer_consumer.c
	gcc $(FLAGS) $@ $^ $(EXTRA_FLAGS)

clean:
	rm -rf $(targets)