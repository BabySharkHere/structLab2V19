// Не орграф, потому что дороги не могут быть ориентированы в 1 сторону!
// Матрица весов! Задаётся: 1000 - недостижимая вершина, -1 - главная диагональ, положительные значения - дороги!
// В программе выбирать вершины A и B от 0 до n-1, где n - максимальное значение.
// Топливо и расход - целочисленные положительные! 

/*19. Имеются n городов. Некоторые из них соединены дорогами известной
длины. Хватит ли дальнобойщику, выезжающему из города А, топлива, чтобы
доехать до города В, если в баке х л бензина, а расход у л на 100 км.А, В, х и у
вводятся с клавиатуры*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct loadFile {
    int n;
    int m;
    int** defaultMass;
    int A;
    int B;
    int x;
    double y;
    int longOfRoad;

    ~loadFile() {
        for (int i = 0; i < n; i++)
            delete[] defaultMass[i];

        delete[] defaultMass;
    }

    void fileFindAndLoad() {
        ifstream file("test3neor.txt");
        if (!file) {
            cout << "Ошибка открытия файла!" << endl;
            exit(0);
        }

        int count = 0; //число чисел в файле
        int temp;

        while (!file.eof())
        {
            file >> temp;
            count++;
        }

        file.seekg(0, ios::beg);
        file.clear();

        int count_space = 0; //кол-во пробелов в файле
        char symbol;

        while (!file.eof())
        {
            file.get(symbol);
            if (symbol == ' ') count_space++;
            if (symbol == '\n') break;
        }

        file.seekg(0, ios::beg);
        file.clear();

        n = count / (count_space + 1); //число строк
        m = count_space + 1; //число столбцов

        defaultMass = new int* [n];

        for (int i = 0; i < n; i++) {
            defaultMass[i] = new int[m];
        }

        //считываем матрицу

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                file >> defaultMass[i][j];
        }
        file.close();
    }

    void pushdefaultMass() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                cout << "[" << i << "][" << j << "] " << defaultMass[i][j] << "\t";
            cout << endl;
        }
    }

    void choice() {
        cout << "Выберите вершину А" << endl;
        cin >> A;
        cout << "Выберите вершину B" << endl;
        cin >> B;

        cout << "Вершина А: " << *defaultMass[A] << endl;
        cout << "Вершина B: " << *defaultMass[B] << endl;

        cout << "Введите количество топлива в баке у водителя" << endl;
        cin >> x;
        cout << "Введите расход топлива автомобилем на 100км" << endl;
        cin >> y;

        cout << "Количество топлива в баке у водителя: " << x << endl;
        cout << "Расход топлива автомобилем на 100км: " << y << endl;
    }

    void Dijkstra()
    {
        int* distance = new int[n];
        int count, index, i, u, m = A;
        bool* visited = new bool[n];
        for (i = 0; i < n; i++)
        {
            distance[i] = INT_MAX;
            visited[i] = false;
        }
        distance[A] = 0;
        for (count = 0; count < n - 1; count++)
        {
            int min = INT_MAX;
            for (i = 0; i < n; i++)
                if (!visited[i] && distance[i] <= min)
                {
                    min = distance[i]; index = i;
                }
            u = index;
            visited[u] = true;
            for (i = 0; i < n; i++)
                if (!visited[i] && defaultMass[u][i] && distance[u] != INT_MAX &&
                    distance[u] + defaultMass[u][i] < distance[i])
                    distance[i] = distance[u] + defaultMass[u][i];
        }
        cout << "Стоимость пути из вершины A до вершины B:" << endl;
        
        if (distance[i] != INT_MAX) {
            cout << m << " -> " << B << " = " << distance[B] << endl;
            longOfRoad = distance[B];
        }
        else {
            cout << m << " -> " << B << " = " << "Маршрут недоступен" << endl;
            exit(0);
        }
    }

    void fuelN() {
        double needFuel;
        double fuelVSroad;
        int tmp;
        int temp;

        needFuel = y / 100;
        fuelVSroad = needFuel * longOfRoad;
        /*cout << "fuelVSroad: " << fuelVSroad << endl;
        cout << "longOfRoad: " << longOfRoad << endl;
        cout << "neddFuel: " << needFuel << endl;*/
        if (fuelVSroad < x) {
            cout << "Дальнобойщику хватит бензина, чтобы добраться из города А в город В" << endl;
        }
        else if (fuelVSroad == x) {
            cout << "Дальнобойщику хватит топлива, чтобы добраться из города А в город В" << endl;
        }
        else {
            cout << "У дальнобойщика не хватит топлива, чтобы добраться из города А в город В" << endl;
            exit(0);
        }

    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    loadFile a;

    a.fileFindAndLoad();
    a.pushdefaultMass();
    a.choice();
    a.Dijkstra();
    a.fuelN();

    return 0;
}
