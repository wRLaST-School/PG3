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

    //bool hasDrew[3] = {};
    string input;

    while (true)
    {
        if (state == State::MENU || (int)state > (int)State::SORT)
        {
            if (strList.Size())
            {
                system("cls");

                cout << "[要素の操作]" << endl;
                cout << "1.要素の表示" << endl;
                cout << "2.要素の挿入" << endl;
                cout << "3.要素の編集" << endl;
                cout << "4.要素の削除" << endl;
                cout << "5.要素のクリア" << endl;
                cout << endl;
                cout << "-------------------------------" << endl;
                cout << "操作を選択してください" << endl;
                do {
                    cin >> input;
                    try {
                        stoi(input);
                    }
                    catch (std::invalid_argument) {
                        input = "-256";
                    }
                } while (stoi(input) > 4 && stoi(input) < 1);
                state = (State)stoi(input);
            }
            else
            {
                system("cls");

                cout << "[要素の操作]" << endl;
                cout << "1.要素の表示" << endl;
                cout << "2.要素の挿入" << endl;
                cout << endl;
                cout << "-------------------------------" << endl;
                cout << "操作を選択してください" << endl;
                do {
                    cin >> input;
                    try {
                        stoi(input);
                    }
                    catch (std::invalid_argument) {
                        input = "-256";
                    }
                } while (stoi(input) > 2 && stoi(input) < 1);
                state = (State)stoi(input);
            }
        }

        if (state == State::OUTPUT)
        {
            //要素の表示
            system("cls");

            input = "0";
            cout << "[要素の表示]" << endl;
            cout << "1.要素の一覧表示" << endl;
            cout << "2.順番を指定して要素を表示" << endl;
            cout << "9.要素操作に戻る" << endl;
            cout << endl << "操作を選択してください。" << endl;
            do {
                cin >> input;
                try {
                    stoi(input);
                }
                catch (std::invalid_argument) {
                    input = "-256";
                }
            } while (stoi(input) != 1 && stoi(input) != 2 && stoi(input) != 9);

            //要素の一覧表示
            if (stoi(input) == 1)
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
                cout << "9.要素の操作に戻る" << endl;

                do {
                    cin >> input;
                    try {
                        stoi(input);
                    }
                    catch (std::invalid_argument) {
                        input = "-256";
                    }
                } while (stoi(input) != 1 && stoi(input) != 9);

            }

            //順番を指定して要素を表示
            if (stoi(input) == 2)
            {
                system("cls");
                cout <<"[順番を指定して要素を表示]" << endl;
                cout <<"表示したい要素の順番を指定してください。" << endl;

                cin >> input;
                cout << endl << input << " : " << strList[stoi(input)] << endl;

                cout << endl << "-------------------------------" << endl;
                cout << "1.要素の表示に戻る" << endl;
                cout << "9.要素の操作に戻る" << endl;

                do {
                    cin >> input;
                    try {
                        stoi(input);
                    }
                    catch (std::invalid_argument) {
                        input = "-256";
                    }
                } while (stoi(input) != 1 && stoi(input) != 9);
            }

            // 要素操作に戻る
            if (stoi(input) == 9)
            {
                state = State::MENU;
            }
        }

        // 要素の挿入
        if (state == State::INSERT)
        {
            system("cls");
            cout << "[リスト要素の挿入]" << endl;
            cout << "要素を追加する場所を指定してください。" << endl;
            cout << "最後尾に追加する場合は何も入力しないでください。" << endl;

            cin.clear();
            cin.ignore(1024, '\n');
            getline(cin, input); // TODO: 入力なしを検知

            cout << "追加する要素を入力してください。" << endl;
            cin >> str;

            if (input == string(""))
            {
                strList.PushBack(str);
                cout << "要素\"" << str << "\"が最後尾に挿入されました。" << endl;
            }
            else
            {
                strList.Insert(stoi(input), str);
                cout << "要素\"" << str << "\"が" << input << "番目に挿入されました。" << endl;
            }

            cout << "9:要素操作に戻る" << endl;
            do {
                cin >> input;
                try {
                    stoi(input);
                }
                catch (std::invalid_argument) {
                    input = "-256";
                }
            } while (stoi(input) != 9);
           
            if (stoi(input) == 9)
            {
                state = State::MENU;
            }
        }

        if (state == State::EDIT)
        {
            system("cls");
            cout << "[リスト要素の編集]" << endl;
            cout << "要素を編集する場所を指定してください。" << endl;

            cin.clear();
            cin.ignore(1024, '\n');
            getline(cin, input);

            if (stoi(input) >= strList.Size() || stoi(input) < 0)
            {
                cout << input << "番目の要素が見つかりませんでした。" << endl;
            }
            else {
                cout << "編集後の要素を入力してください。" << endl;
                cin >> str;

                strList[stoi(input)] = str;
                cout << "要素\"" << input << "\"が" << str << "に変更されました。" << endl;
            }

            cout << "9:要素操作に戻る" << endl;
            do {
                cin >> input;
                try {
                    stoi(input);
                }
                catch (std::invalid_argument) {
                    input = "-256";
                }
            } while (stoi(input) != 9);

            if (stoi(input) == 9)
            {
                state = State::MENU;
            }
        }

        if (state == State::DEL)
        {
            system("cls");
            cout << "[リスト要素の削除]" << endl;
            cout << "要素を削除する場所を指定してください。" << endl;

            cin >> input;

            if (stoi(input) >= strList.Size() || stoi(input) < 0)
            {
                cout << input << "番目の要素が見つかりませんでした。" << endl;
            }
            else
            {

                auto itr = strList.Begin();
                for (int i = 0; i < stoi(input); i++)
                {
                    itr++;
                }
                strList.Erase(itr);
                cout << input << "番目の要素が削除されました。" << endl;
            }

            cout << "9:要素操作に戻る" << endl;
            do {
                cin >> input;
                try {
                    stoi(input);
                }
                catch (std::invalid_argument) {
                    input = "-256";
                }
            } while (stoi(input) != 9);

            if (stoi(input) == 9)
            {
                state = State::MENU;
            }
        }

        if (state == State::SORT)
        {
            system("cls");
            cout << "[リスト要素のクリア]" << endl;
            cout << "1:要素をすべて削除" << endl;
            cout << "9:要素を削除せずに戻る" << endl;

            do {
                cin >> input;
                try {
                    stoi(input);
                }
                catch (std::invalid_argument) {
                    input = "-256";
                }
            } while (stoi(input) != 9 && stoi(input) != 1);

            if (stoi(input) == 1)
            {
                strList.Clear();
                cout << input << "すべての要素が削除されました。" << endl;

                cout << "9:要素操作に戻る" << endl;
                do {
                    cin >> input;
                    try {
                        stoi(input);
                    }
                    catch (std::invalid_argument) {
                        input = "-256";
                    }
                } while (stoi(input) != 9);
            }

            if (stoi(input) == 9)
            {
                state = State::MENU;
            }

        }
    }

    return 0;
}