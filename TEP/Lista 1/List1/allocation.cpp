#include <iostream>
#include "allocation.h"

using namespace std;

void Allocation::v_alloc_table_fill_34(int iSize) {
	if (iSize < 1)
		cout << "Niepoprawny rozmiar tablicy!" << endl;
	else {
		int* tableToAllocate = new int[iSize];

		for (int i = 0; i < iSize; i++) {
			tableToAllocate[i] = 34;
		}

		for (int i = 0; i < iSize; i++) {
			cout << i + 1 << ". " << tableToAllocate[i] << endl;
		}

		delete[] tableToAllocate;
	}
}

bool Allocation::b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY) { // w miejsce ??? wstawiamy potrójny wskaŸnik, nastêpnie w argumencie przekazujemy adres adresu tablicy (adresów)
	if (iSizeX < 1 || iSizeY < 1) {
		cout << "Niepoprawna wielkoœæ tablicy!" << endl;
		return false;
	} 
	else {
		*piTable = new int*[iSizeX];
		for (int x = 0; x < iSizeX; x++) {
			(*piTable)[x] = new int[iSizeY];
		}
		return true;
	}
}

bool Allocation::b_dealloc_table_2_dim(int*** piTable, int iSizeX) { //nie jest potrzebny parametr iSizeY
	if (iSizeX < 1) {
		return false;
	}
	else {
		for (int x = 0; x < iSizeX; x++) {
			delete (*piTable)[x];
		}
		delete* piTable;
		return true;
	}
}

int main() {
	Allocation::v_alloc_table_fill_34(10);
	Allocation::v_alloc_table_fill_34(0);

	int** pi_table;
	if (Allocation::b_alloc_table_2_dim(&pi_table, 5, 3))
		cout << "Zaalokowano tablice!" << endl;
	else
		cout << "Nie zaalokowano tablicy!" << endl;

	if (Allocation::b_dealloc_table_2_dim(&pi_table, 5))
		cout << "Zdealokowano tablice!" << endl;
	else
		cout << "Nie zdeealokowano tablicy!" << endl;
	return 0;
}