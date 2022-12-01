#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include "List.h"

using namespace std;
using namespace Sp;

enum class State
{
    MENU,
    OUTPUT,
    INSERT,
    EDIT,
    DEL,
    SORT
};

int main()
{
    string str;
    List<string> strList;
    strList.PushBack("Banana");
    strList.PushBack("Apple");
    strList.PushBack("Orange");

    State state = State::MENU;

    bool hasDrew[3] = {};
    string input;

    while (true)
    {
        if (state == State::MENU || (int)state > (int)State::SORT)
        {
            system("cls");

            cout << "[要素の操作]" << endl;
            cout << "1.要素の表示" << endl;
            cout << "2.要素の挿入" << endl;
            cout << "3.要素の編集" << endl;
            cout << "4.要素の削除" << endl;
            cout << "5.要素の並び替え(オプション)" << endl;
            cout << endl;
            cout << "-------------------------------" << endl;
            cout << "操作を選択してください" << endl;
            cin >> input;
            state = (State)stoi(input);
        }

        if (state == State::OUTPUT)
        {
            //要素の表示
            if (!hasDrew[0])
            {
                system("cls");

                input = "0";
                cout << "[要素の表示]" << endl;
                cout << "1.要素の一覧表示" << endl;
                cout << "2.順番を指定して要素を表示" << endl;
                cout << "9.要素操作に戻る" << endl;
                cout << endl << "操作を選択してください。" << endl;
                cin >> input;
                hasDrew[0] = true;
            }

            //要素の一覧表示
            if (stoi(input) == 1 && !hasDrew[1])
            {
                system("cls");
                cout << "[要素の一覧表示]" << endl;
                cout << "要素一覧: {" << endl;

                int i = 0;
                strList.ForEach([&](auto& str) {
                    cout << i << " : " << str << endl;
                    i++;
                });

                cout << "}" << endl << endl;

                cout << "要素数: " << strList.Size() << endl;

                cout << endl << "-------------------------------" << endl;
                cout << "1.要素の表示に戻る" << endl;
                cout << "2.要素の操作に戻る" << endl;

                cin >> input;

                hasDrew[1] = true;
            }

            //順番を指定して要素を表示
            if (stoi(input) == 2 && !hasDrew[2])
            {
                system("cls");
                cout <<"[順番を指定して要素を表示]" << endl;
                cout <<"表示したい要素の順番を指定してください。" << endl;

                cin >> input;
                cout << endl << input << " : " << strList[stoi(input)] << endl;

                cout << endl << "-------------------------------" << endl;
                cout << "1.要素の表示に戻る" << endl;
                cout << "2.要素の操作に戻る" << endl;

                cin >>input;

                hasDrew[2] = true;
            }

            if (stoi(input) == 1)
            {
                hasDrew[0] = false;
                hasDrew[1] = false;
                hasDrew[2] = false;
            }

            // 要素操作に戻る
            if (stoi(input) == 9 || stoi(input) == 2)
            {
                hasDrew[0] = 0;
                hasDrew[1] = 0;
                hasDrew[2] = 0;
                state = State::MENU;
            }
        }

        // 要素の挿入
        if (state == State::INSERT)
        {
            if (hasDrew[0] == 0)
            {
                system("cls");
                cout << "[リスト要素の挿入]" << endl;
                cout << "要素を追加する場所を指定してください。" << endl;
                cout << "最後尾に追加する場合は何も入力しないでください。" << endl;
                cin >> input; // TODO: 入力なしを検知

                cout << "追加する要素の値を入力してください。" << endl;
                cin >> str;

                if (false /*入力なしの場合*/)
                {
                    strList.PushBack(str);
                    cout << "要素\"" << str << "\"が最後尾に挿入されました。" << endl;
                }
                else
                {
                    strList.Insert(stoi(input), str);
                    cout << "要素\"" << str << "\"が" << input << "番目に挿入されました。" << endl;
                }

                cout << "9.要素操作に戻る" << endl;
                cin >> input;
                hasDrew[0] = 1;
            }

            if (stoi(input) == 9)
            {
                hasDrew[0] = 0;
                state = State::MENU;
            }
        }

        if (state == State::EDIT)
        {
            cout << "要素の編集" << endl;
        }

        if (state == State::DEL)
        {
            cout << "要素の削除" << endl;
        }

        if (state == State::SORT)
        {
            cout << "要素の並び替え" << endl;
        }
    }

    return 0;
}