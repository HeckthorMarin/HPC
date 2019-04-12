#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arguments {
	int *args;
	int result;
};

class Matrix {
	
	public:
		
	static int size[2];
	static int **mat;
	static int **matTwo;
	static int **newMat;
	static pthread_t *mainThreads;
	static pthread_t **threads;
	
	Matrix(){}
	
	Matrix(int rows, int cols, bool fillThis = true){
		// Suposing that rows and cols are the same
		size[0] = rows;
		size[1] = cols;
		
		//printf("saise %d %d", size[0], size[1]);

        mat = new int*[rows];
        newMat = new int *[rows];
        matTwo = new int *[rows];
        mainThreads = new pthread_t [rows*cols];
        threads = new pthread_t *[rows*cols];
        
        for(int i=0; i<rows; i++){
            mat[i] = new int[cols];
            newMat[i] = new int[cols];
            matTwo[i] = new int[cols];
            for(int j=0; j<cols; j++){
				threads[i*cols+j] = new pthread_t[rows];
			}
        }

		if(fillThis) fill();
	}
	
	void fill(){
		for (int i = 0; i < size[0]; i++){
			for(int j = 0; j < size[1]; j++){
				mat[i][j] = rand() % 10;
				matTwo[i][j] = rand() % 10;
			}
		}
	};

    void show(){
        printf("Hola somos las matrices %d x %d \n", size[0], size[1]);
        for (int i = 0; i < size[0]; i++){
			for(int j = 0; j < size[1]; j++){
                printf(" %d \t", mat[i][j]);
			}
			printf("\t\t");
			for(int j = 0; j < size[1]; j++){
                printf(" %d \t", matTwo[i][j]);
			}
			printf("\t\t");
			for(int j = 0; j < size[1]; j++){
                printf(" %d \t", newMat[i][j]);
			}
            printf("\n");
		}
		
    }

	Matrix operator * (Matrix mat2){
		
		if(size[1] != mat2.size[0]) throw "matrices can't be multiplied, matrices' dimension is wrong !";
		
		struct arguments myargs[size[0]*size[1]];
		
		for (int i = 0; i < size[0]; i++){
			for(int j = 0; j < size[1]; j++){
				myargs[i*size[0]+j].args = new int[2];
				myargs[i*size[0]+j].args[0] = i;
				myargs[i*size[0]+j].args[1] = j;
				pthread_create(&mainThreads[ i * size[0] + j ], NULL, add, (void *)&myargs[i*size[0]+j]);
			}
		}
		
		pthread_join(mainThreads[size[0] * size[1] -1 ], NULL);
		
		return convert();
	}
	
	static void *multiply(void *args){
		//args = [i, j, k], result = a_ik * b_kj 
		
		struct arguments *myargs;
		myargs = (struct arguments *) args;
		myargs->result = mat[myargs->args[0]][myargs->args[2]] * matTwo[myargs->args[2]][myargs->args[1]];
		pthread_exit(NULL);
	}
	
	static void *add(void *args){
		//args = [i, j], result = NULL
		// I'm going to set the value into newMat
		int k, res = 0;
		
		struct arguments *incomingargs;
		incomingargs = (struct arguments *) args;
		
		struct arguments *myargs;
		myargs = new struct arguments [size[1]];
		
		for(k=0; k<size[1]; k++){
			myargs[k].args = new int [3];
			myargs[k].args[0] = incomingargs->args[0];
			myargs[k].args[1] = incomingargs->args[1];
			myargs[k].args[2] = k;
			pthread_create(&threads[ myargs[k].args[0] * size[1] + myargs[k].args[1] ][k], NULL, multiply, (void *)&myargs[k]);
		}
		
		for(k = 0; k < size[1]; k++){
			pthread_join(threads[ myargs[k].args[0] * size[1] + myargs[k].args[1] ][k], NULL);
			res += myargs[k].result;
		}
		newMat[ myargs[0].args[0]][ myargs[0].args[1]] = res;
		
		pthread_exit(NULL);
	}
	
	Matrix convert(){
		Matrix temp;
		//temp.mat = newMat;
		//temp.size[0] = size[0];
		//temp.size[1] = size[1];
		return temp;
	}
};

int Matrix::size[2] = {0,0};
int ** Matrix::mat = new int*[0];
int ** Matrix::matTwo = new int*[0];
int ** Matrix::newMat = new int*[0];
pthread_t * Matrix::mainThreads = new pthread_t[0];
pthread_t ** Matrix::threads = new pthread_t*[0];

int main(){
	int N;
	
	scanf("%d", &N);
	Matrix A(N,N);
	Matrix B(N,N);
	//A.fill();
	//B.fill();

	Matrix C;
	C = A * B;
	C.show();


	return 0;
}
