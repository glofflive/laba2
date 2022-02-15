#include <iostream>
#include <string>
#include <math.h>
#include <Windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const char ukrAlpLw[] = { 'а','б','в','г','ґ','д','е','є','ж','з','и','і','ї','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ь','ю','я','_' };

    /*середньостатичні частоти букв*/ double AverRate[34]{ 0.064,0.013,0.046,0.013,0.0001,0.027,0.042,0.005,0.007,0.020 ,0.055,0.044,0.010,0.009,0.033 ,0.027,0.029,0.068,0.086,0.025,0.043,0.037,0.045,0.027,0.003,0.011,0.010,0.011,0.005,0.004,0.016,0.008,0.019,0.138 };

    /*ймовірнісні характеристики українського алфавіту*/ double probChar[34]{ 0 };
    int i;
    int j;
    int l = 0;
    for (i = 0;i < 34;i++)
    {
        probChar[i] = log2(AverRate[i]);
    }
    /*частотні характеристики криптограми*/ int letterRate[34]{ 0 };

    string key;
    int keyLength = 5;


    //Створення тексту
    string txt;
    cout << "Текст: ";
    getline(cin, txt);
    //string key;
    //cout << "Ключ: ";
    //getline(cin, key);

    string tempTxt = "";
    int iteration; //ітерація //i*5+iteration
    int probKey[5]{ 0 };
    const char keyLetter[] = { 'а','б','в','г','ґ','д','е','є','ж','з','и','і','ї','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ь','ю','я','_' };
    for (iteration = 0; iteration < keyLength; iteration++)
    {
        j = 0;
        for (i = 0;i <= txt.length();i++)
        {
            if (i == iteration)
            {
                tempTxt += txt[i];
                j++;
            }
            else if (i == iteration + (5 * j))
            {
                tempTxt += txt[i];
                j++;
            }

        }
        j = 0;
        //Підрахування частоти символів
        for (i = 0;i < tempTxt.length();i++)
        {
            while (tempTxt[i] != ukrAlpLw[j])
                j++;
            letterRate[j] += 1;
            j = 0;
        }


        /*логарифмічна функція правдоподібності*/ double func[34]{ 0 };
        /*ключ*/ int key[34]{ 0 };
       
        double temp = 0;
        double max;
        
        for (i = 0;i < 34;i++)
        {
            key[i] = i;
        }
        for (i = 0;i < 34;i++)
        {
            for (j = 0;j < 34;j++)
            {
                temp = (letterRate[(j + i) % 34] * probChar[j]) + temp;
            }
            func[i] = temp;
            if (i == 0) {
                max = func[i];
                probKey[iteration] = i;
            }
            else if (func[i] > max)
            {
                max = func[i];
                probKey[iteration] = i;
            }
            temp = 0;
            cout << i << ' ' << func[i] << '\n';
        }
        cout << "Probable key #" << iteration + 1 << " is:" << probKey[iteration] << " aka " << keyLetter[probKey[iteration]] << '\n';


        for (i = 0;i < tempTxt.length();++i)
        {
            temp = tempTxt[i];

            while (temp != ukrAlpLw[l])
                l++;

            if (l - probKey[iteration] >= 0)
                temp = ukrAlpLw[l - probKey[iteration]];
            else temp = ukrAlpLw[l - probKey[iteration] + 34];
            l = 0;

            tempTxt[i] = temp;
        }

        for (i = 0;i < tempTxt.length();i++)
            txt[i + iteration + (5 * i - i)] = tempTxt[i];

        memset(letterRate, 0, sizeof(letterRate));
        tempTxt = "";
    }
    cout << "Ключ:";
    for (i=0;i<5;i++)
        cout << keyLetter[probKey[i]];
    
    cout<<'\n' << "deciphered:" << txt << endl;
}
