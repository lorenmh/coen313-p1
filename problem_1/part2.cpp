// Immanuel Amirtharaj

#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>



using namespace std;

#define SIZE 1000000000L

char large_array[SIZE];

static struct timeval start_time;
static struct timeval end_time;


// https://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html
int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}


double get_diff(struct timeval elapsed) {
	cout << elapsed.tv_sec << endl;
	cout << elapsed.tv_usec << endl;
	float elapsed_ms = ((elapsed.tv_sec * 1000.0) + (elapsed.tv_usec / 1000.0));
	// float elapsed_seconds = elapsed_ms / 1000.0;
	return elapsed_ms;

}


void init_array() {
	srand(time(NULL));

	for (int i = 0; i < SIZE; i++) {
		large_array[i] = (char) (rand() % 256);
	}
	cout << "Finished initializing array" << endl;
}

// Takes in an integer of size in BYTES
void run_experiment(int guess_size) {

	// because indexed from 0 to n-1
	int first_pos = guess_size - 1;
	int second_pos = guess_size;

	clock_t start, end;


	start = clock();
	//gettimeofday(&start_time, NULL);

	// Brings the cache line into memory
	int first = large_array[first_pos];
	end = clock();
	gettimeofday(&end_time, NULL);

	//struct timeval elapsed;
	//timeval_subtract(&elapsed, &end_time, &start_time);

	//double time_for_first = get_diff(elapsed);
	double time_for_first = ((double) (end - start)) / CLOCKS_PER_SEC;


	//gettimeofday(&start_time, NULL);
	start = clock();
	// Access last element
	int last = large_array[second_pos];
	
	//gettimeofday(&end_time, NULL);
	end = clock();

	//timeval_subtract(&elapsed, &end_time, &start_time);

	//double time_for_last = get_diff(elapsed);

	double time_for_last = ((double) (end - start)) / CLOCKS_PER_SEC;


	cout << "\n\n" << endl;
	cout << "RESULTS FOR GUESS SIZE OF " << guess_size << endl;
	cout << "The time for " << first_pos << " is " << time_for_first << endl;
	cout << "The time for " << second_pos << " is " << time_for_last << endl;

	if (time_for_last < time_for_first) {
		//cout << "This is probably on the same cache line" << endl;
	}
	else {
		cout << "This is probably on a different cache line" << endl;
	}

}

int main(int argc,m char* argv) {

	init_array();

	for (int i = 4; i < 11; i++) {
		int guess_size = pow(2, i);
		run_experiment(guess_size);
		//init_array();
	}


	return 0;
}