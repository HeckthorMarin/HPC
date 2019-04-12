#include <stdio.h>
#include <stdlib.h>

class Matrix {
	
	public:
		
	static int size[2];
	static int **mat;
	static int **matTwo;
	static int **newMat;
	
	Matrix(){}
	
	Matrix(int rows, int cols, bool fillThis = true){
		// Suposing that rows and cols are the same
		size[0] = rows;
		size[1] = cols;
		

        mat = new int*[rows];
        newMat = new int *[rows];
        matTwo = new int *[rows];
        
        for(int i=0; i<rows; i++){
            mat[i] = new int[cols];
            newMat[i] = new int[cols];
            matTwo[i] = new int[cols];
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
		
		
		for (int i = 0; i < size[0]; i++){
			for(int j = 0; j < size[1]; j++){
				int res = 0;
				for(int k = 0; k < size[1]; k++){
					res += mat[i][k] * matTwo[k][j];
				}
				newMat[i][j] = res; 
			}
		}
		
		return convert();
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
