#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arguments {
	int *args;
};

class Matrix {
	
	public:
		
	int size[2];
	int **mat;
	pthread_t *threads;
	
	Matrix(int rows, int cols, bool fillThis = true){
		size[0] = rows;
		size[1] = cols;

        mat = new int*[rows];
        threads = new pthread_t[rows];
        for(int i=0; i<rows; i++){
            mat[i] = new int[cols];
        }

		if(fillThis) fill();
	}
	
	void fill(){
		for (int i = 0; i < size[0]; i++){
			for(int j = 0; j < size[1]; j++){
				mat[i][j] = rand() % 10;
			}
		}
	};

    void show(){
        printf("Hola soy la matriz %d x %d \n", size[0], size[1]);
        for (int i = 0; i < size[0]; i++){
			for(int j = 0; j < size[1]; j++){
                printf(" %d \t", mat[i][j]);
			}
            printf("\n");
		}
    }

	Matrix operator * (Matrix mat2){
		
		if(size[1] != mat2.size[0]) throw "matrices can't be multiplied, matrices' dimension is wrong !";
		
		Matrix temp(size[0],mat2.size[1], false);
		for (int i = 0; i < temp.size[0]; i++){
			for(int j = 0; j < temp.size[1]; j++){
				int res = 0;
				for(int k = 0; k < size[1]; k++){
					res += mat[i][k] * mat2.mat[k][j];
				}
				temp.mat[i][j] = res; 
			}
		}
		return temp;
	}
	
	void *mutiply(void *args){
		//args = [i, j, k]
		
		//struct arguments *myargs;
		//myargs = (struct arguments *) args;
		//int value = mat[myargs->args[0]][myargs->args[2]] * mat[myargs->args[2]][myargs->args[1]];
		//return (void *) value;
		pthread_exit(NULL);
	}
};

int main(){
	int N;
	
	scanf("%d", &N);
	Matrix A(N,N);
	Matrix B(N,N);
	//A.fill();
	//B.fill();

	Matrix C = A * B;
	A.show();
	B.show();
	C.show();


	return 0;
}
