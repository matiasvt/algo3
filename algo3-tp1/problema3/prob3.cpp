#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <cstdio>
#include <utility>
using namespace std;


/* Funciones Auxiliares */

int nuevoHazard2(int subset);
int hazardOfSubset(int subset);
void llenarHazards();
void resolver(int i);
pair<bool, int> nuevoHazard(int productoi, int camion);

/* Variables Globales */

const int maxN = 20;
int hazard2[1 << maxN];
int n, M, temp, nuevoHz; 
int primerCamionVacio, mejorHastaAhora;
vector<int> resTemp, res, hazardCamion, productosEnCamion;
vector< vector<int> > hazards;

/* El main del programa que resuelve */

int main(){

	/* de dónde leemos la entrada y adónde ponemos el output */
	
	freopen("input.in","r",stdin); 
	freopen("output.out","w",stdout); 
    
    /* Para cada entrada que nos pasan, resuelvo el problema */
	while(cin >> n >> M) {
		
		/* inicializo la matriz de hazards */
		vector<int> v1(n, 0);
		hazards.resize(n); fill(hazards.begin(), hazards.end(), v1);
		
		/* lleno la matriz de hazards según el los hazards de esta instancia */
		for(int i=0; i<n-1; i++) {
			for(int j=i+1; j<n; j++) {
				cin >> temp;
				hazards[i][j] = temp;
				hazards[j][i] = temp;
			}
		}
		
		/* Inicializo las variables globales que van a ser modificadas en el backtracking */
		primerCamionVacio = 0; mejorHastaAhora = n;
		hazardCamion.resize(n); fill(hazardCamion.begin(), hazardCamion.end(), 0);
		productosEnCamion.resize(n); 
		fill(productosEnCamion.begin(), productosEnCamion.end(), 0);
		resTemp.resize(n); fill(resTemp.begin(), resTemp.end(), -1);
		
		/* Precalculo el hazard total que genera cada subconjunto de productos */
		llenarHazards();
		
		/* Resuelvo el problema con backtracking */
		resolver(0);
		
		/* Devuelvo el resultado */
		cout << mejorHastaAhora << " ";
		for(int i=0; i<n; i++) { cout << res[i] << " ";}
		cout << endl;
	}
	
    return 0;
}

/* La funcion recursiva "resolver", que hace el backtracking */

void resolver(int i) {
    
    if(i == n) { return; }
		
    int primerCamionVacioTemp = primerCamionVacio;
    
          for(int j=0; j<=primerCamionVacioTemp; j++) {
                
                pair<bool, int> sePuedeAgregar = nuevoHazard(i,j);
                int hazardViejo = hazardCamion[j];
                
                if(sePuedeAgregar.first) {
          
                    resTemp[i] = j;
                    productosEnCamion[j] += (1<<i);
                    hazardCamion[j] = sePuedeAgregar.second;
                    
                    if(j == primerCamionVacioTemp) {
							primerCamionVacio++; 
					}
                    
                    resolver(i+1);
                    
                    if(i + 1 == n) {
						  if(primerCamionVacio <= mejorHastaAhora) {
							  
								mejorHastaAhora = primerCamionVacio;
								res = resTemp;
						  }
					}

                    productosEnCamion[j] -= (1<<i);
                    hazardCamion[j] = hazardViejo; 

					if(j == primerCamionVacioTemp) { primerCamionVacio--; }
                } 

          }
          return;
}

/* Funciones Auxiliares */

/* Devuelve el hazard total que genera el subconjunto "subset" de productos */
int nuevoHazard2(int subset){
	return hazard2[subset];
}

/* Devuelve, para cierto subconjunto "subset" de productos, el hazard que generan entre todos */
int hazardOfSubset(int subset){
	int res = 0;
	for(int i = 0; i < n; i++) if((subset & (1 << i)) != 0)
		for(int j = i + 1; j < n; j++) if((subset & (1 << j)) != 0)
				res += hazards[i][j];
	return res;
}

/* Recorremos todos los posibles subconjuntos de productos y junto con la funcion hazardOfSubset 
 * llenamos el arreglo hazard2, que contiene el hazard total que genera cada subconjunto de productos */
void llenarHazards(){
	for(int subset = 0; subset < (1 << n); subset++)
		hazard2[subset] = hazardOfSubset(subset);
}

/* analizamos cuál es el hazard total que generaría agregar el producto productoi en el camion camionj 
 * y devolvemos un par, que dice si era posible agregar el producto al camión, y cuánto hazard hubiera generado */
pair<bool, int> nuevoHazard(int productoi, int camionj) {

	nuevoHz = hazard2[productosEnCamion[camionj] | (1 << productoi)];
	pair<bool, int> res = make_pair((nuevoHz<M), nuevoHz);
    return res;
}
