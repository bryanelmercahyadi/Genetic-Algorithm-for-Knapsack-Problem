#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<time.h>
#include<stdlib.h>
using namespace std;

struct Item {
	int _number;
	int _value;
	string _nama_barang;
	int _weight;
	
} _item[12];

struct population {
	Item _item[12];
	int _weight;
	int _fitness;
	int _count;
	int _co;
}_population[256];

int getFitness(Item _item[]) {
	int temp = 0;
	for (int i = 0; i < 12; i++)
	{
		temp += _item[i]._value;
	}
	return temp;
}

int getWeight(Item _item[]) {
	int temp = 0;
	for (int i = 0; i < 12; i++)
	{
		temp += _item[i]._weight;
	}
	return temp;
}

bool cek(population pop,int cap) {
	bool cek = true;
	int temp = 0;
	temp = pop._fitness;
	if (temp > cap)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int reduceFitness(population pop, int cap) {
	int temp = pop._weight;
	int fit = pop._fitness;
	int co = temp - cap;
	int mult = co * 5;
	fit -= mult;
	return fit;
}




bool cekrandom(population _pop, int rand, Item _item[]) {
	for (int i = 0; i < _pop._count; i++)
	{
		if (_pop._item[i]._number== _item[rand]._number)
		{
			return true;
		}
	}
	return false;
}

void displaytabel(Item item[]) {
	for (int i = 0; i < 12; i++)
	{
		cout << "No : " << item[i]._number << endl;
		cout << "Item Name : " << item[i]._nama_barang << endl;
		cout << "Item Weight : " << item[i]._weight << endl;
		cout << "Item Value : " << item[i]._value << endl;
		cout << "-----------------------------------------------------------" << endl;
	}

}
void displaytabel(population pop[]) {
	cout << "-------------- LIST POPULASI ------------------------------" << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << "-------------- POPULASI KE- "; cout<<i + 1<<" -----------------------------" << endl;
		for (int j = 0; j < pop[i]._count; j++)
		{
			cout << "No : " << pop[i]._item[j]._number << endl;
			cout << "Item Name : " << pop[i]._item[j]._nama_barang << endl;
			cout << "Item Weight : " << pop[i]._item[j]._weight << endl;
			cout << "Item Value : " << pop[i]._item[j]._value << endl;
			cout << "-----------------------------------------------------------" << endl;
		}
		cout << "-------------- WEIGHT POPULASI KE "; cout << i + 1 << " = " << pop[i]._weight << " ------------------" << endl;
		cout << "-------------- FITNES POPULASI KE "; cout << i + 1 <<" = " <<pop[i]._fitness << " ------------------" << endl;
	}

}

void displaytabel(population _pop) {
	for (int i = 0; i < _pop._count; i++)
	{
		cout << "No : " << _pop._item[i]._number << endl;
		cout << "Item Name : " << _pop._item[i]._nama_barang << endl;
		cout << "Item Weight : " << _pop._item[i]._weight << endl;
		cout << "Item Value : " << _pop._item[i]._value << endl;
		cout << "-----------------------------------------------------------" << endl;
	}
	cout << "-------------- WEIGHT POPULASI : "; cout << _pop._weight << "  ----------------------" << endl;
	cout << "-------------- FITNES POPULASI : "; cout << _pop._fitness << " ----------------------" << endl;
}



void bubble_sort(Item item[],int co) {

	for (int i = 1; i < co; i++) {
		for (int j = co - 1; j >= i; j--) {
			if (item[j]._value > item[j - 1]._value) {
				Item temp;
				temp._number = item[j - 1]._number;
				temp._nama_barang = item[j - 1]._nama_barang;
				temp._weight = item[j - 1]._weight;
				temp._value = item[j - 1]._value;
				item[j - 1] = item[j];
				item[j]._number = temp._number;
				item[j]._nama_barang = temp._nama_barang;
				item[j]._value = temp._value;
				item[j]._weight = temp._weight;
			}
		}
	}
	cout << endl;
}
void bubble_sort(population item[], int co) {

	for (int i = 1; i < co; i++) {
		for (int j = co - 1; j >= i; j--) {
			if (item[j]._fitness > item[j - 1]._fitness) {

				population temp;
				temp._count = item[j - 1]._count;
				temp._fitness = item[j - 1]._fitness;
				for (int k = 0; k < item[j]._count; k++)
				{
					temp._item[k] = item[j - 1]._item[k];
				}
				temp._weight = item[j - 1]._weight;
				item[j - 1] = item[j];
				item[j]._count = temp._count;
				for (int k = 0; k < item[j]._count; k++)
				{
					item[j]._item[k] = temp._item[k];
				}
				item[j]._fitness = temp._fitness;
				item[j]._weight = temp._weight;
			}
		}
	}
	cout << endl;
}
population reproduce(population _x, population _y) {
	population _child;
	int _min;
	if (_x._count>_y._count)
	{
		_min = _y._count;
	}
	else
	{
		_min = _x._count;
	}
	int _random = rand() % (_min - 1) + 1;
	_child = _x;
	for (int i = 0; i < _y._count; i++)
	{
		for (int j = 0; j < _random; j++)
		{
			if (_y._item[i]._number == _child._item[j]._number) {
				Item _temp;
				_temp._number = _item[i]._number;
				_temp._nama_barang = _item[i]._nama_barang;
				_temp._weight = _item[i]._weight;
				_temp._value = _item[i]._value;
				_item[i] = _item[j];
				_item[j] = _temp;
			}
		}
		_child._item[i] = _y._item[i];
	}
	return _child;
}


void mutate(population _pop, Item _item[]) {
	int prob = rand() % 100;
	if (prob < 10)
	{
		int ind = rand() % _pop._count;
		int tempindex = rand() % 12;
		while (cekrandom(_pop, tempindex, _item) == true)
		{
			tempindex = rand() % 12;

		}
		_pop._item[ind] = _item[tempindex];
		
		
		
	}
}

population random_selection(population _pop[]) {
	population _best;
	int arr[6];
	int total = 0;
	for (int i = 0; i < 6; i++)
	{
		total += _pop[i]._fitness - 1;
		arr[i] = total;

	}
	int temprand = rand() % total;
	for (int i = 0; i < 6; i++)
	{
		if (arr[i] >= temprand)
		{
			_best = _pop[i];
			break;
		}
	}
	return _best;
}
 
population Genetic_Algorithm(population _pop[],Item _item[]) {
	population _new[256];
	population _hasil;
	int _copopulation = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			population _x, _y, _child1, _child2;
			_x = random_selection(_pop);
			_y = random_selection(_pop);
			_child1 = reproduce(_x, _y);
			_child2 = reproduce(_y, _x);
			mutate(_child1, _item);
			mutate(_child2, _item);
			_new[_copopulation] = _child1;
			_copopulation++;
			_new[_copopulation] = _child2;
			_copopulation++;

		}
		for (int i = 0; i < 6; i++)
		{
			_new[_copopulation] = _pop[i];
			_copopulation++;
		}
		bubble_sort(_new, _copopulation);
		for (int i = 0; i < 6; i++)
		{
			_pop[i] = _new[i];
		}
	}
	
	bubble_sort(_pop,_pop->_co);
	_hasil = _pop[0];
	return _hasil;
}

int main() {
	srand(time(0));
	int _cap = 20;
	population _hasil;
	_item[0]._number = 1;
	_item[0]._nama_barang = "Bug Repellent";
	_item[0]._weight = 2;
	_item[0]._value = 12;
	_item[1]._number = 2;
	_item[1]._nama_barang = "Tent";
	_item[1]._weight = 11;
	_item[1]._value = 20;
	_item[2]._number = 3;
	_item[2]._nama_barang = "Stove";
	_item[2]._weight = 4;
	_item[2]._value = 5;
	_item[3]._number = 4;
	_item[3]._nama_barang = "Clothes";
	_item[3]._weight = 5;
	_item[3]._value = 11;
	_item[4]._number = 5;
	_item[4]._nama_barang = "Dried Foods";
	_item[4]._weight = 3;
	_item[4]._value = 50;
	_item[5]._number = 6;
	_item[5]._nama_barang = "First Aid Kit";
	_item[5]._weight = 3;
	_item[5]._value = 15;
	_item[6]._number = 7;
	_item[6]._nama_barang = "Flash Light";
	_item[6]._weight = 2;
	_item[6]._value = 6;
	_item[7]._number = 8;
	_item[7]._nama_barang = "Novel";
	_item[7]._weight = 2;
	_item[7]._value = 4;
	_item[8]._number = 9;
	_item[8]._nama_barang = "Rain Gear";
	_item[8]._weight = 2;
	_item[8]._value = 5;
	_item[9]._number = 10;
	_item[9]._nama_barang = "Sleeping Bag";
	_item[9]._weight = 3;
	_item[9]._value = 25;
	_item[10]._number = 11;
	_item[10]._nama_barang = "Water FIlter";
	_item[10]._weight = 1;
	_item[10]._value = 30;
	_item[11]._number = 12;
	_item[11]._nama_barang = "Lantern";
	_item[11]._weight = 7;
	_item[11]._value = 10;
	for (int i = 0; i < 6; i++)
	{	
		int j = 0;
		int _weightco = 0;
		
		while (_weightco < _cap-1)
		{
			
			int tempco = rand() % 12;
			if (cekrandom(_population[i],tempco,_item) == false)
			{
				_population[i]._item[j]._number = _item[tempco]._number;
				_population[i]._item[j]._nama_barang = _item[tempco]._nama_barang;
				_population[i]._item[j]._weight = _item[tempco]._weight;
				_population[i]._item[j]._value = _item[tempco]._value;
				int _tmpweight = _population[i]._item[j]._weight;
				_weightco += _tmpweight;
				j++;
				_population[i]._count++;
				
			}
			
		}
		
		int _fittnesco = getFitness(_population[i]._item);
		_population[i]._fitness = _fittnesco;
		_population[i]._weight = _weightco;
		if (_weightco > _cap)
		{
			_population[i]._fitness=reduceFitness(_population[i], _cap);
		}
		_population->_co++;
		
	}
	_hasil = Genetic_Algorithm(_population, _item);
	cout << "---------------------- Hasil ------------------------------" << endl;
	displaytabel(_hasil);
	cout << "-----------------------------------------------------------" << endl;
	return 0;
}