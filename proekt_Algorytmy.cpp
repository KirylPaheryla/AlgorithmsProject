#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

int PartitionElementuSkrajnego(int tab[], int start, int stop)
{
    int pivot = tab[stop];
    int j = start;
    for(int i = start; i < stop; i++)
        if(tab[i] <= pivot) swap(tab[i], tab[j++]);
    swap(tab[stop], tab[j]);
    return j;
}

int PartitionPseudolosowy(int tab[], int start, int stop)
{
    int los = rand() % (stop - start + 1) + start;
    swap(tab[los], tab[stop]);
    int pivot = tab[stop];
    int j = start;
    for(int i = start; i < stop; i++)
        if(tab[i] <= pivot) swap(tab[i], tab[j++]);
    swap(tab[stop], tab[j]);
    return j;
}

int WyborMedianyZ3elementow(int tab[], int start, int stop)
{
    int middle = (start + stop) / 2;
    if (tab[middle] < tab[start])
        swap(tab[start], tab[middle]);
    if (tab[stop] < tab[start])
        swap(tab[start], tab[stop]);
    if (tab[stop] < tab[middle])
        swap(tab[middle], tab[stop]);
    return middle;
}

int PartitionWyborMedianyZ3elementow(int tab[], int start, int stop)
{
    int mediana = WyborMedianyZ3elementow(tab, start, stop);
    swap(tab[mediana], tab[stop]);
    int pivot = tab[stop];
    int j = start;
    for(int i = start; i < stop; i++)
        if(tab[i] <= pivot)
            swap(tab[i], tab[j++]);
    swap(tab[stop], tab[j]);
    return j;
}

int InsertSort(int tab[], int temptab[], int rozm)
{
    for(int i = 1; i < rozm; i++)
    {
        int temp = temptab[i];
        int j = i - 1;
        while(j >= 0 && tab[temp] < tab[temptab[j]])
        {
            temptab[j+1] = temptab[j];
            j--;
        }
        temptab[j+1] = temp;
    }
    if(rozm = 5) return temptab[2];
    if(rozm = 7) return temptab[3];
}

int WyborMedianyZ5elementow(int tab[], int start, int stop)
{
    int *temptab = new int[5];
    temptab[0] = start; temptab[1] = stop;
    for(int i = 2; i < 5; i++)
        temptab[i] = rand() % (stop - start + 1) + start;
    InsertSort(tab, temptab, 5);

}

int PartitionWyborMedianyZ5elementow(int tab[], int start, int stop)
{
    int median = WyborMedianyZ5elementow(tab, start, stop);
    swap(tab[median], tab[stop]);

    int pivot = tab[stop];
    int j = start;
    for(int i = start; i < stop; i++)
    {
        if(tab[i] <= pivot)
            swap(tab[i], tab[j++]);
    }
    swap(tab[stop], tab[j]);
    return j;
}

int WyborMedianyZ7elementow(int tab[], int start, int stop)
{
    int *temptab = new int[7];
    temptab[0] = start; temptab[1] = stop;
    for(int i = 2; i < 7; i++)
        temptab[i] = rand() % (stop - start + 1) + start;
    InsertSort(tab, temptab, 7);

}

int PartitionWyborMedianyZ7elementow(int tab[], int start, int stop)
{
    int median = WyborMedianyZ7elementow(tab, start, stop);
    swap(tab[median], tab[stop]);

    int pivot = tab[stop];
    int j = start;
    for(int i = start; i < stop; i++)
    {
        if(tab[i] <= pivot)
            swap(tab[i], tab[j++]);
    }
    swap(tab[stop], tab[j]);
    return j;
}

void QuickSort(int tab[], int start, int stop)
{
    if(start >= stop) return;
//    int index = PartitionElementuSkrajnego(tab, start, stop);
//    int index = PartitionPseudolosowy(tab, start, stop);
//    int index = PartitionWyborMedianyZ3elementow(tab, start, stop);
//    int index = PartitionWyborMedianyZ5elementow(tab, start, stop);
    int index = PartitionWyborMedianyZ7elementow(tab, start, stop);
    QuickSort(tab, start, index-1);
    QuickSort(tab, index+1, stop);
}

int main()
{
    for(int rozm = 10000; rozm <= 1000000; rozm += 10000)
    {
        int *tab = new int[rozm];
//        for(int i = 0; i < rozm; i++) tab[i] = rand() + rozm;
//        for(int i = 0; i < rozm; i++) tab[i] = rand() % (101);
        for(int i = 0; i < rozm; i++) tab[i] = i;
        auto begin = std::chrono::steady_clock::now();
        QuickSort(tab, 0, rozm-1);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        ofstream out("czas.txt", ios_base::app);
        out << elapsed_ms.count() << endl;
        out.close();
    }
    return 0;
}
