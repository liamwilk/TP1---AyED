#include <iostream>
#include <fstream>

using namespace std;

void mostrar(string v[], int dim) //Muestra el vector de tipo string
{
    for (int i = 0; i < dim; ++i)
        cout << "v[" << i << "]= " << v[i] << endl;
}

void mostrar(int v[], int dim) //Muestra el vector de tipo entero
{
    for (int i = 0; i < dim; i++)
        cout << "v [" << i << "] = " << v[i] << endl; 
}

void mostrarmat(float m[][5], int dfil) //Muestra la matriz
{
    const int dcol {5};
 
    for (int i = 0; i < dfil; ++i) {
        for (int j = 0; j < dcol; ++j)
            cout << m[i][j] << '\t';
        cout << endl;
    }
 
}

int mayorvector (int v[], int dim) //Muestra el vector mayor
{
	int imax = v[0];
	for (int i = 1; i < dim; i++)
		if (v[i] > v[imax])
			imax = i;
	return imax;
}

void sortdouble (int v[], int dimv, float m[][5], int cliente)// Ordena la matriz
{
    int i, pos, imax;
    for (pos = 0; pos < dimv - 1; pos ++){
        imax = pos;
        for ( i = pos + 1; i < dimv; i++){
            if (m[cliente][i] < m[cliente][imax]){
                imax = i;
            }
        }
        swap(v[imax], v[pos]);
    }
}

void lista_peso (string clientes[], string productos[], int dcliente, int dprod, float peso[][5], int prod_clientes []) //Utilizada en el punto 1
{
    
    string clave;

    for (int i = 0; i < dcliente; i++){

        for (int j = 0; j < dprod; j++){

            if (peso[i][j] > 13000){
                clave += (productos[j] + ", ");
                prod_clientes[i]++;
            }
        }
        cout << "\n" << clientes[i] <<": " << clave << endl;
        clave = "";
    }
}

void lista_km (string clientes[], string productos[], int dcliente, int dprod, float distancia[][5], int cliente) //Utilizada en el punto 2
{

    int v[] {0, 1, 2, 3, 4};
    sortdouble(v, dprod, distancia, cliente);

    /*for (int i = 0; i < dprod; i++){
        cout << vecpos[i];
    }*/ //Opcional, muestra vector.

    cout << endl << clientes[cliente] << ": " << endl;

    for (int j = 0; j < dprod; j++){
        cout << "       " << productos[v[j]] << ": " << distancia[cliente][v[j]] << endl;
    }
}


int main()
{
    const int dcliente {8}; //Código de clientes
    const int dprod {5}; //Cantidad de tipo de productos

    float peso[dcliente][dprod]{}; //Peso total
    float distancia[dcliente][dprod]{}; //Distancia x cliente y tipo de producto
    int prod_clientes [dcliente]{};
    int entregas[dcliente][dprod]{}; //Entregas

    string clientes[dcliente]; //Nombre de clientes
    string productos[dprod]; //Nombre de productos

    //Carga de nombres
    ifstream archilec;
    archilec.open("Nombres.txt");
    if (!archilec){
        cout << "Error al abrir el archivo de Nombres" << endl;
        return 1;
    }
    {for (int i = 0; i < dcliente && archilec >> clientes[i]; i++);
    for (int j = 0; j < dprod && archilec >> productos[j]; j++);}
        mostrar(clientes, dcliente);
        cout << "\n============================\n" << endl;
        mostrar(productos, dprod);
        archilec.close();


    //Carga de productos
    archilec.open("Datos.txt");
    if(!archilec){
        cout << "Error al abrir el archivo de Datos" << endl;
        return 1;
    }

    int icliente, iprod;
    float ipeso, idist;

    while(archilec >> icliente >> iprod >> ipeso >> idist){
        entregas[icliente][iprod]++;
        peso[icliente][iprod] += ipeso;
        distancia[icliente][iprod] += idist;
    }
    archilec.close();

    cout << "\n=========================================\n" << endl;

    //Punto 1
    cout << "Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados:" << endl;
    lista_peso(clientes, productos, dcliente, dprod, peso, prod_clientes);

    cout << "\n=========================================\n" << endl;

    //Punto 2
    cout << "Listado de Km recorridos por tipo de producto (ascendente):" << endl;
    int mayor = mayorvector(prod_clientes, dcliente);
    lista_km(clientes, productos, dcliente, dprod, distancia, mayor);

    cout << "\n=========================================\n" << endl;

    //Punto 3
   
    int prodclient[dprod]{};

    for (int j = 0; j < dprod; j++){
        prodclient[j] = distancia[mayor][j];
    }
    int mayorprod = mayorvector(prodclient, dprod);
    int sum = 0;
    for (int i = 0; i < dcliente; i++){
        sum += entregas[i][mayorprod];
    }
    cout << "Cantidad de entregas para el tipo de producto " << productos[mayorprod] << ": " << sum << endl;

    return 0;
}