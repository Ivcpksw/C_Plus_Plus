// Local_Data_Smoothing.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
    Турчак Л.И., Плотников П.В. - Основы ЧМ [2003] - стр. 70 (моя работа)

    Задача: Локальное сглаживание данных

    Опытные данные содержат случайные ошибки, что является причиной разброса этих данных
    Целесообразно провести их сглаживание для получения более плавного характера исследуемой зависимости
*/

#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    int i,
        m, // Период
        k, // Сглаживание
        z1, // Подсчёт кол-во данных в Х
        z2; // Подсчёт кол-во данных в Y

    double x[1000], // Диапазон принимаемых значений
           y[1000], // Диапазон принимаемых значений
           N1, N2,  // Для преобразования
           Yi,
           sum = 0,
           kv,
           ex;

    // Чтение данных с файла
    string path_X = "LDS_X.txt";
    string path_Y = "LDS_Y.txt";
    string path_Yi = "LDS_Yi.txt";

    ofstream fin_yi;
    ifstream fin_x;
    ifstream fin_y;

    fin_x.open(path_X);
    fin_y.open(path_Y);

    if (!fin_x.is_open())
    {
        cout << "Ошибка открытия файла!" << endl;
        return 0;
    }
    else
    {
        cout << "Файл открыт!" << endl << endl;
        cout << "Ваши данные в файле LDS_X.txt: " << endl;

        string str;
        while (!fin_x.eof())
        {
            str = "";
            getline(fin_x, str);
            cout << str << endl;
        }
    }
    fin_x.close();
    cout << endl;
    system("pause");
    system("cls");

    if (!fin_y.is_open())
    {
        cout << "Ошибка открытия файла!" << endl;
        return 0;
    }
    else
    {
        cout << "Файл открыт!" << endl << endl;
        cout << "Ваши данные в файле LDS_Y.txt: " << endl;

        string str;
        while (!fin_y.eof())
        {
            str = "";
            getline(fin_y, str);
            cout << str << endl;
        }
    }
    fin_y.close();
    cout << endl;
    system("pause");
    system("cls");
    
    // Преобразование строки в число и в массив
    fin_x.open(path_X);
    fin_y.open(path_Y);

    if (!fin_x.is_open() && !fin_y.is_open())
    {
        cout << "Ошибка открытия файла!" << endl;
        return 0;
    }
    else
    {
        z1 = 0;
        while (fin_x >> N1)
        {
            x[z1++] = N1;
        }

        z2 = 0;
        while (fin_y >> N2)
        {
            y[z2++] = N2;
        }
    }
    if (z1 != z2)
    {
        cout << "Неравное КОЛ-ВО данных! (x != y)" << endl;
        return 0;
    }
    if (z1 < 10 || z2 < 10)
    {
        cout << "Минимальное КОЛ-ВО данных должно быть НЕ МЕНЬШЕ 10!" << endl;
        return 0;
    }

    fin_x.close();
    fin_y.close();
    
    /* 
        Сделать выбор между:
            m1 = k2, k4, k6
            m3 = k4, k6, k8
            m5 = k6, k8
    */

    cout << "Выберите m из чисел 1, 3, 5: "; cin >> m;
    
    fin_yi.open(path_Yi, ofstream::app);
    switch (m)
    {
        case 1:
            cout << "Вы выбрали m = 1" << endl << endl;
            cout << "Выберите k из чисел 2, 4, 6: "; cin >> k;
            
            switch (k)
            {
                case 2:
                    cout << "Вы выбрали k = 2" << endl << endl;

                    cout << "X" << '\t' << '\t' << "Y" << '\t' << '\t' << "Yi" << '\t' << '\t' << "(Y-Yi)^2" << endl << endl;

                    for (i = 0; i < z1; i++)
                    {
                        char ve = '-'; // Value Error (погрешность значения)

                        if (i == 0)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;

                            Yi = (y[i] + y[i + 1] + y[i + 2]) / 3;
                            kv = pow(y[i + 1], 2) - (2 * y[i + 1] * Yi) + pow(Yi, 2);

                            sum += kv;
                            i++;
                        }
                        if (i == z1 - 1)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            break;
                        }
                        cout << fixed << setprecision(2);
                        cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                        fin_yi << Yi;
                        fin_yi << '\n';

                        Yi = 0;
                        kv = 0;

                        Yi = (y[i] + y[i + 1] + y[i + 2]) / 3;
                        kv = pow(y[i + 1], 2) - (2 * y[i + 1] * Yi) + pow(Yi, 2);

                        if (i+2 != z1)
                        {
                            sum += kv;
                        }
                    }
                    ex = sqrt(sum / m); //или на 3.  Делим на период (m)?. Уточнить, m - это период или степень многочлена?
                    cout << endl;

                    if (ex > 0)
                    {
                        cout << "Погрешность = " << ex << endl;
                        break;
                    }
                    else
                    {
                        cout << "Значение под корнем не может быть меньше 0" << endl;
                        break;
                    }
                    ////////////////////////////////////////////////////////////
                case 4:
                    cout << "Вы выбрали k = 4" << endl << endl;

                    cout << "X" << '\t' << '\t' << "Y" << '\t' << '\t' << "Yi" << '\t' << '\t' << "(Y-Yi)^2" << endl << endl;

                    for (i = 0; i < z1; i++)
                    {
                        char ve = '-'; // Value Error (погрешность значения)

                        if (i == 0 || i == 1)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;

                            if (i == 1)
                            {
                                Yi = (y[i - 1] + y[i] + y[i + 1] + y[i + 2] + y[i + 3]) / 5;
                                kv = pow(y[i + 1], 2) - (2 * y[i + 1] * Yi) + pow(Yi, 2);

                                sum += kv;
                            }
                            continue;
                        }
                        if (i == z1 - 1 || i == z1 - 2)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            if (i == z1 - 1)
                            {
                                break;
                            }
                        }
                        if (i != z1 - 2)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                            fin_yi << Yi;
                            fin_yi << '\n';
                        }

                        Yi = 0;
                        kv = 0;

                        Yi = (y[i - 1] + y[i] + y[i + 1] + y[i + 2] + y[i + 3]) / 5;
                        kv = pow(y[i + 1], 2) - (2 * y[i + 1] * Yi) + pow(Yi, 2);

                        if (i + 3 != z1 && i + 3 != z1 + 1)
                        {
                            sum += kv;
                        }
                    }
                    ex = sqrt(sum / m); // или 5
                    cout << endl;

                    if (ex > 0)
                    {
                        cout << "Погрешность = " << ex << endl;
                        break;
                    }
                    else
                    {
                        cout << "Значение под корнем не может быть меньше 0" << endl;
                        break;
                    }
                    ////////////////////////////////////////////////////////////
                case 6:
                    cout << "Вы выбрали k = 6" << endl << endl;

                    cout << "X" << '\t' << '\t' << "Y" << '\t' << '\t' << "Yi" << '\t' << '\t' << "(Y-Yi)^2" << endl << endl;

                    for (i = 0; i < z1; i++)
                    {
                        char ve = '-'; // Value Error (погрешность значения)

                        if (i == 0 || i == 1 || i == 2 || i == 3)
                        {
                            if (i == 3)
                            {
                                Yi = (y[i - 3] + y[i - 2] + y[i - 1] + y[i] + y[i + 1] + y[i + 2] + y[i + 3]) / 7;
                                kv = pow(y[i], 2) - (2 * y[i] * Yi) + pow(Yi, 2);

                                sum += kv;

                                cout << fixed << setprecision(2);
                                cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                                fin_yi << Yi;
                                fin_yi << '\n';

                                continue;
                            }
                            else
                            {
                                cout << fixed << setprecision(2);
                                cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            }
                            continue;
                        }
                        if (i == z1 - 1 || i == z1 - 2 || i == z1 - 3)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            if (i == z1 - 1)
                            {
                                break;
                            }
                        }

                        Yi = 0;
                        kv = 0;

                        Yi = (y[i - 3] + y[i - 2] + y[i - 1] + y[i] + y[i + 1] + y[i + 2] + y[i + 3]) / 7;
                        kv = pow(y[i], 2) - (2 * y[i] * Yi) + pow(Yi, 2);

                        if (i != z1 - 3 && i != z1 - 2 && i != z1 - 1)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                            fin_yi << Yi;
                            fin_yi << '\n';
                        }

                        if (i + 3 != z1 && i + 3 != z1 + 1)
                        {
                            sum += kv;
                        }
                    }
                    ex = sqrt(sum / m); // или на 7
                    cout << endl;

                    if (ex > 0)
                    {
                        cout << "Погрешность = " << ex << endl;
                        break;
                    }
                    else
                    {
                        cout << "Значение под корнем не может быть меньше 0" << endl;
                        break;
                    }
                    break;

                default:
                    cout << "Выберите k из предоставленных чисел!" << endl;
                    break;
            }
            break;

        case 3:
            cout << "Вы выбрали m = 3" << endl << endl;
            cout << "Выберите k из чисел 4, 6, 8: "; cin >> k;

            switch (k)
            {
                case 4:
                    cout << "Вы выбрали k = 4" << endl << endl;

                    cout << "X" << '\t' << '\t' << "Y" << '\t' << '\t' << "Yi" << '\t' << '\t' << "(Y-Yi)^2" << endl << endl;

                    for (i = 0; i < z1; i++)
                    {
                        char ve = '-'; // Value Error (погрешность значения)

                        if (i == 0 || i == 1)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;

                            if (i == 1)
                            {
                                Yi = (-3*(y[i - 1]) + 12*(y[i]) + 17*(y[i + 1]) + 12*(y[i + 2]) + (-3*(y[i + 3]))) / 35;
                                kv = pow(y[i + 1], 2) - (2 * y[i + 1] * Yi) + pow(Yi, 2);

                                sum += kv;
                            }
                            continue;
                        }
                        if (i == z1 - 1 || i == z1 - 2)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            if (i == z1 - 1)
                            {
                                break;
                            }
                        }
                        if (i != z1 - 2)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                            fin_yi << Yi;
                            fin_yi << '\n';
                        }

                        Yi = 0;
                        kv = 0;

                        Yi = (-3 * (y[i - 1]) + 12 * (y[i]) + 17 * (y[i + 1]) + 12 * (y[i + 2]) + (-3 * (y[i + 3]))) / 35;
                        kv = pow(y[i + 1], 2) - (2 * y[i + 1] * Yi) + pow(Yi, 2);

                        if (i + 3 != z1 && i + 3 != z1 + 1)
                        {
                            sum += kv;
                        }
                    }
                    ex = sqrt(sum / m); // или на 35
                    cout << endl;

                    if (ex > 0)
                    {
                        cout << "Погрешность = " << ex << endl;
                        break;
                    }
                    else
                    {
                        cout << "Значение под корнем не может быть меньше 0" << endl;
                        break;
                    }
                    ////////////////////////////////////////////////////////////
                case 6:
                    cout << "Вы выбрали k = 6" << endl << endl;

                    cout << "X" << '\t' << '\t' << "Y" << '\t' << '\t' << "Yi" << '\t' << '\t' << "(Y-Yi)^2" << endl << endl;

                    for (i = 0; i < z1; i++)
                    {
                        char ve = '-'; // Value Error (погрешность значения)

                        if (i == 0 || i == 1 || i == 2 || i == 3)
                        {
                            if (i == 3)
                            {
                                Yi = (-2 * (y[i - 3]) + 3 * (y[i - 2]) + 6 * (y[i - 1]) + 7 * (y[i]) + 6 * (y[i + 1]) + 3 * (y[i + 2]) + (-2 * (y[i + 3]))) / 21;
                                kv = pow(y[i], 2) - (2 * y[i] * Yi) + pow(Yi, 2);

                                sum += kv;

                                cout << fixed << setprecision(2);
                                cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                                fin_yi << Yi;
                                fin_yi << '\n';

                                continue;
                            }
                            else
                            {
                                cout << fixed << setprecision(2);
                                cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            }
                            continue;
                        }
                        if (i == z1 - 1 || i == z1 - 2 || i == z1 - 3)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            if (i == z1 - 1)
                            {
                                break;
                            }
                        }

                        Yi = 0;
                        kv = 0;

                        Yi = (-2 * (y[i - 3]) + 3 * (y[i - 2]) + 6 * (y[i - 1]) + 7 * (y[i]) + 6 * (y[i + 1]) + 3 * (y[i + 2]) + (-2 * (y[i + 3]))) / 21;
                        kv = pow(y[i], 2) - (2 * y[i] * Yi) + pow(Yi, 2);

                        if (i != z1 - 3 && i != z1 - 2 && i != z1 - 1)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                            fin_yi << Yi;
                            fin_yi << '\n';
                        }
                         
                        if (i + 3 != z1 && i + 3 != z1 + 1)
                        {
                            sum += kv;
                        }
                    }
                    ex = sqrt(sum / m); // или на 21
                    cout << endl;

                    if (ex > 0)
                    {
                        cout << "Погрешность = " << ex << endl;
                        break;
                    }
                    else
                    {
                        cout << "Значение под корнем не может быть меньше 0" << endl;
                        break;
                    }
                    break;
                    ////////////////////////////////////////////////////////////
                case 8:
                    cout << "Вы выбрали k = 8" << endl << endl;

                    cout << "X" << '\t' << '\t' << "Y" << '\t' << '\t' << "Yi" << '\t' << '\t' << "(Y-Yi)^2" << endl << endl;


                    for (i = 0; i < z1; i++)
                    {
                        char ve = '-'; // Value Error (погрешность значения)

                        if (i == 0 || i == 1 || i == 2 || i == 3 || i == 4)
                        {
                            if (i == 4)
                            {
                                Yi = (-21 * (y[i - 4]) + 14 * (y[i - 3]) + 39 * (y[i - 2]) + 54 * (y[i - 1]) + 59 * (y[i]) + 54 * (y[i + 1]) + 39 * (y[i + 2]) + 14 * (y[i + 3]) - 21 * (y[i + 4])) / 231;
                                kv = pow(y[i], 2) - (2 * y[i] * Yi) + pow(Yi, 2);

                                sum += kv;

                                cout << fixed << setprecision(2);
                                cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                                fin_yi << Yi;
                                fin_yi << '\n';

                                continue;
                            }
                            else
                            {
                                cout << fixed << setprecision(2);
                                cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            }
                            continue;
                        }
                        if (i == z1 - 1 || i == z1 - 2 || i == z1 - 3 || i == z1 - 4)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            if (i == z1 - 1)
                            {
                                break;
                            }
                        }

                        Yi = 0;
                        kv = 0;

                        Yi = (-21 * (y[i - 4]) + 14 * (y[i - 3]) + 39 * (y[i - 2]) + 54 * (y[i - 1]) + 59 * (y[i]) + 54 * (y[i + 1]) + 39 * (y[i + 2]) + 14 * (y[i + 3]) - 21 * (y[i + 4])) / 231;
                        kv = pow(y[i], 2) - (2 * y[i] * Yi) + pow(Yi, 2);

                        if (i != z1 - 4 && i != z1 - 3 && i != z1 - 2 && i != z1 - 1)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                            fin_yi << Yi;
                            fin_yi << '\n';
                        }

                        if (i + 3 != z1 && i + 3 != z1 + 1 && i + 3 != z1 + 2 && i + 4 != z1)
                        {
                            sum += kv;
                        }
                    }
                    ex = sqrt(sum / m); // или на 231
                    cout << endl;

                    if (ex > 0)
                    {
                        cout << "Погрешность = " << ex << endl;
                        break;
                    }
                    else
                    {
                        cout << "Значение под корнем не может быть меньше 0" << endl;
                        break;
                    }
                    break;

                default: 
                    cout << "Выберите k из предоставленных чисел!" << endl;
                    break;
            }
            break;

        case 5:
            cout << "Вы выбрали m = 5" << endl << endl;
            cout << "Выберите k из чисел 6, 8: "; cin >> k;

            switch (k)
            {
                case 6:
                    cout << "Вы выбрали k = 6" << endl << endl;

                    cout << "X" << '\t' << '\t' << "Y" << '\t' << '\t' << "Yi" << '\t' << '\t' << "(Y-Yi)^2" << endl << endl;

                    for (i = 0; i < z1; i++)
                    {
                        char ve = '-'; // Value Error (погрешность значения)

                        if (i == 0 || i == 1 || i == 2 || i == 3)
                        {
                            if (i == 3)
                            {
                                Yi = (5 * (y[i - 3]) - 30 * (y[i - 2]) + 75 * (y[i - 1]) + 131 * (y[i]) + 75 * (y[i + 1]) - 30 * (y[i + 2]) + 5 * (y[i + 3])) / 231;
                                kv = pow(y[i], 2) - (2 * y[i] * Yi) + pow(Yi, 2);

                                sum += kv;

                                cout << fixed << setprecision(2);
                                cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                                fin_yi << Yi;
                                fin_yi << '\n';

                                continue;
                            }
                            else
                            {
                                cout << fixed << setprecision(2);
                                cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            }
                            continue;
                        }
                        if (i == z1 - 1 || i == z1 - 2 || i == z1 - 3)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            if (i == z1 - 1)
                            {
                                break;
                            }
                        }

                        Yi = 0;
                        kv = 0;

                        Yi = (5 * (y[i - 3]) - 30 * (y[i - 2]) + 75 * (y[i - 1]) + 131 * (y[i]) + 75 * (y[i + 1]) - 30 * (y[i + 2]) + 5 * (y[i + 3])) / 231;
                        kv = pow(y[i], 2) - (2 * y[i] * Yi) + pow(Yi, 2);

                        if (i != z1 - 3 && i != z1 - 2 && i != z1 - 1)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                            fin_yi << Yi;
                            fin_yi << '\n';
                        }

                        if (i + 3 != z1 && i + 3 != z1 + 1)
                        {
                            sum += kv;
                        }
                    }
                    ex = sqrt(sum / m); // или на 231
                    cout << endl;

                    if (ex > 0)
                    {
                        cout << "Погрешность = " << ex << endl;
                        break;
                    }
                    else
                    {
                        cout << "Значение под корнем не может быть меньше 0" << endl;
                        break;
                    }
                    break;
                    ////////////////////////////////////////////////////////////
                case 8:
                    cout << "Вы выбрали k = 8" << endl << endl;

                    cout << "X" << '\t' << '\t' << "Y" << '\t' << '\t' << "Yi" << '\t' << '\t' << "(Y-Yi)^2" << endl << endl;


                    for (i = 0; i < z1; i++)
                    {
                        char ve = '-'; // Value Error (погрешность значения)

                        if (i == 0 || i == 1 || i == 2 || i == 3 || i == 4)
                        {
                            if (i == 4)
                            {
                                Yi = (15 * (y[i - 4]) - 55 * (y[i - 3]) + 30 * (y[i - 2]) + 135 * (y[i - 1]) + 179 * (y[i]) + 135 * (y[i + 1]) + 30 * (y[i + 2]) - 55 * (y[i + 3]) + 15 * (y[i + 4])) / 429;
                                kv = pow(y[i], 2) - (2 * y[i] * Yi) + pow(Yi, 2);

                                sum += kv;

                                cout << fixed << setprecision(2);
                                cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                                fin_yi << Yi;
                                fin_yi << '\n';

                                continue;
                            }
                            else
                            {
                                cout << fixed << setprecision(2);
                                cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            }
                            continue;
                        }
                        if (i == z1 - 1 || i == z1 - 2 || i == z1 - 3 || i == z1 - 4)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << ve << '\t' << '\t' << ve << endl;
                            if (i == z1 - 1)
                            {
                                break;
                            }
                        }

                        Yi = 0;
                        kv = 0;

                        Yi = (15 * (y[i - 4]) - 55 * (y[i - 3]) + 30 * (y[i - 2]) + 135 * (y[i - 1]) + 179 * (y[i]) + 135 * (y[i + 1]) + 30 * (y[i + 2]) - 55 * (y[i + 3]) + 15 * (y[i + 4])) / 429;
                        kv = pow(y[i], 2) - (2 * y[i] * Yi) + pow(Yi, 2);

                        if (i != z1 - 4 && i != z1 - 3 && i != z1 - 2 && i != z1 - 1)
                        {
                            cout << fixed << setprecision(2);
                            cout << x[i] << '\t' << '\t' << y[i] << '\t' << '\t' << Yi << '\t' << '\t' << kv << endl;

                            fin_yi << Yi;
                            fin_yi << '\n';
                        }

                        if (i + 3 != z1 && i + 3 != z1 + 1 && i + 3 != z1 + 2 && i + 4 != z1)
                        {
                            sum += kv;
                        }
                    }
                    ex = sqrt(sum / m); // или на 429
                    cout << endl;

                    if (ex > 0)
                    {
                        cout << "Погрешность = " << ex << endl;
                        break;
                    }
                    else
                    {
                        cout << "Значение под корнем не может быть меньше 0" << endl;
                        break;
                    }
                    break;

                default:
                    cout << "Выберите k из предоставленных чисел!" << endl;
                    break;
            }
            break;

        default:
            cout << "Выберите m из предоставленных чисел!" << endl;
            break;

    }
    fin_yi.close();
}