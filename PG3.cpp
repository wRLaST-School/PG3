#include <iostream>
#include <list>
#include <vector>

using namespace std;

//std::stringが使えないのでvector<char>に変換する関数
vector<char> ToVecChar(const char* str) {
    vector<char> result;
    for (int i = 0; str[i] != '\0'; i++) {
        result.push_back(str[i]);
    };

    return result;
}

//list<vector<char>>の中身を全て出力
void PrintAll(list<vector<char>> list) {
    for (auto itr = list.begin(); itr != list.end(); itr++) {
        for (auto itr2 = itr->begin(); itr2 != itr->end(); itr2++) {
            cout << *itr2;
        }
        cout << endl;
    }
}

//文字列同士の比較(==は使わなかったので!=だけ)
bool operator!=(vector<char> a, vector<char> b) {
    if (a.size() != b.size()) {
        return true;
    }

    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return true;
        }
    }

    return false;
}

int main()
{
    list<vector<char>> stations {
        ToVecChar("Tokyo"),
        ToVecChar("Kanda"),
        ToVecChar("Akihabara"),
        ToVecChar("Okachimachi"),
        ToVecChar("Ueno"),
        ToVecChar("Uguisudani"),
        ToVecChar("Nippori"),
        ToVecChar("Tabata"),
        ToVecChar("Komagome"),
        ToVecChar("Sugamo"),
        ToVecChar("Otsuka"),
        ToVecChar("Ikebukuro"),
        ToVecChar("Mejiro"),
        ToVecChar("Takadanobaba"),
        ToVecChar("Shin-Okubo"),
        ToVecChar("Shinjuku"),
        ToVecChar("Yoyogi"),
        ToVecChar("Harajuku"),
        ToVecChar("Shibuya"),
        ToVecChar("Ebisu"),
        ToVecChar("Meguro"),
        ToVecChar("Gotanda"),
        ToVecChar("Osaki"),
        ToVecChar("Shinagawa"),
        ToVecChar("Tamachi"),
        ToVecChar("Hamamatsucho"),
        ToVecChar("Shimbashi"),
        ToVecChar("Yurakucho"),
    };

    cout << "Yamanote Line" << endl << endl;
    cout << "1970" << endl;

    PrintAll(stations);
    cout << endl;

    //西日暮里を挿入
    auto itr = stations.begin();
    for (; *itr != ToVecChar("Tabata"); itr++){};
    itr = stations.insert(itr, ToVecChar("Nishi-Nippori"));

    cout << "2019" << endl;
    PrintAll(stations);
    cout << endl;
    
    //高輪ゲートウェイを挿入
    itr = stations.begin();
    for (; *itr != ToVecChar("Tamachi"); itr++) {};
    itr = stations.insert(itr, ToVecChar("Takanawa-Gateway"));

    cout << "2022" << endl;
    PrintAll(stations);

    getchar();
}