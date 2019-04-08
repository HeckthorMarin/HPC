#include <stdio.h>
#include <stdlib.h>

class Matrix {
	
	public:
		
	int size[2];
	int **mat;
	
	Matrix(int rows, int cols, bool fillThis = true){
		size[0] = rows;
		size[1] = cols;

        mat = new int*[rows];
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
};

int main(){
	Matrix A(2,2);
	Matrix B(2,2);
	//A.fill();
	//B.fill();

	Matrix C = A * B;
	A.show();
	B.show();
	C.show();


	return 0;
}
