//Побитовая(поразрядная сортировка)
#include "iostream"

using namespace std;

void sort(int* mas, int N,int maxCharge, int maxNumber)
{
	int** matr;
	matr = new int*[maxNumber]; //Буфер матрица со значениями, сюда мы будем записывать числа поочередной, в зависимости от их разряда
	for (int i = 0; i < maxNumber; i++) 
	{
		matr[i] = new int[N];
	}
	int* dop_mas; // Так как нам нужно проследить вывод определенного количества чисел, количество чисел определенного разряда будем записывать в дополнительный массив
	dop_mas = new int[maxNumber];

	for (int i = 0; i < maxCharge; i++) //Циклом проходим по максимальному числу цифр в максимальном числе (максимальный разряд чисел массива)
	{
		for (int j = 0; j < maxNumber; j++) //Матрицу занулять не будем, так как будем пользоваться подмассивом с количество чисел (dop_mas), который при каждом проходе будем занулять
			dop_mas[j] = 0;
		for (int j = 0; j < N; j++) //Записываем значения в матрицу в зависимости от того какая цифра в i-том разряде числа
		{
			int b = mas[j] / (pow(10, i));//Цифра в i-ом разряде
			b = b % maxNumber;// С++ ругается если оставить выражение как: b = (mas[j] / (pow(10, i)))%si ,так как не может знать заранее получится ли ответ целочисленным
			matr[b][dop_mas[b]] = mas[j];
			dop_mas[b]++;
		}
		for (int j = 0, n = 0; j < maxNumber; j++) // Из матрицы с поразрядно осортированными числами начинаем вытаскивать числа обратно в массив
			for (int k = 0; k < dop_mas[j]; k++) 
			{
				mas[n] = matr[j][k];
				n = n + 1;
			}
	}

	//Освобождаем память
	for (int i = 0; i < maxNumber; i++)
		delete[]matr[i];
	delete[]matr;
	delete[] dop_mas;
}
int findCharge(int temp) //Возвращает разряд числа
{
	int tmp = temp, charge = 1;
	while (tmp > 1) 
	{
		tmp = tmp / 10;
		charge++;
	}
	return charge;
}

int findNumber(int temp) //Возвращает максимальная цифра
{
	int tmp = temp, maxNumber = 0;
	do
	{
		if ((tmp % 10) > maxNumber)
			maxNumber = tmp % 10;
		tmp = tmp / 10;
	} while (tmp > 1);
	return maxNumber;
}

int main()
{
	int N, maxCharge = 1, maxNumber = 1;//Минимальное число разрядов = 1(по умолчанию)
	cout << "N = ";
	cin >> N;
	int* mas;
	mas = new int[N];
	for (int i = 0; i < N; i++) {
		cout << "mas[" << i + 1 << "] = ";
		cin >> mas[i];
		int tmp = findCharge(mas[i]);
		if (tmp > maxCharge)//максимальный разряд запоминаем
			maxCharge = tmp;
		tmp = findNumber(mas[i]);
		if (tmp > maxNumber)//максимальный разряд запоминаем
			maxNumber = tmp;
	}
	sort(mas, N, maxCharge, maxNumber);
	cout << "Massiv: ";
	for (int i = 0; i < N; i++)
		cout << mas[i] << " ";
	delete[] mas;
}