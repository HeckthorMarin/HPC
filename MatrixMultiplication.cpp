#include <stdio.h>
#include <stdlib.h>

class Matrix {
	
	public:
		
	int size[2];
	int **mat;
	
	Matrix(int rows, int cols){
		size[0] = rows;
		size[1] = cols;

        mat = new int*[rows];
        for(int i=0; i<rows; i++){
            mat[i] = new int[cols];
        }	
	}
	
	void fill(){
		for (int i = 0; i < size[0]; i++)
		{
			for(int j = 0; j < size[1]; j++){
				mat[i][j] = rand() % 10;
			}
		}
	};

    void show(){
        printf("Hola soy la matriz %d x %d \n", size[0], size[1]);
        for (int i = 0; i < size[0]; i++)
		{
			for(int j = 0; j < size[1]; j++){
                printf(" %d \t", mat[i][j]);
			}
            printf("\n");
		}
    }
};

int main(){
	Matrix mymat(4,7);
    mymat.fill();
    mymat.show();
    
	return 0;
}
