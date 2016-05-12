#include <iostream>
#include <ctime>
#include <cstdlib>

int * x;
int comp; 


void swap(int & a, int & b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int randint(int a, int b) {
	return a + (rand() % (b - a + 1));
}

void quicksort(int a, int b) {
	if (a >= b) return;
	int p = randint(a,b); // pivot
	swap(x[a], x[p]);
	int m = a;
	int i;
	// in-place partition:
	for (i = a+1; i <= b; i++) {
		comp++;
		if (x[i] < x[a])
			swap(x[++m], x[i]);
	}
	swap(x[a],x[m]);
	quicksort(a, m-1);
	quicksort(m+1, b);
}

 float c(int n) {
       if (n <= 1) return 0;
       float sum = 0.0;
       for (int m=1; m <= n; m++)
         sum += n-1 + c(m-1) + c(n-m);
       return sum / n;
}

int qc(int n){
	
	if(n>=1){
 
	
	int p = randint(0,n);
	return n-1 + qc(n-p) + qc(p-1);
}}

#define NN 1000
int num = 1000; 
int qcc;

int main(int argc, char *argv[]) {
	for(int i=1 ; i<= num; i++){
	
	srand(time(0));

	// change the following code
	x = new int[NN];
	for (int i=0; i<NN; ++i) {
		x[i] = rand() % NN;
	}
	
		 qcc = qcc + qc(1000);
		
		quicksort(0, NN-1);}
	// for (int i=0; i<NN; ++i) {
	// 	std::cout << x[i] << " ";
	// }
	std::cout << (comp/num) << std::endl;
	std::cout << std::endl;
	std::cout << qcc/num << std::endl;

	

	delete[] x;
	return 0;
}
