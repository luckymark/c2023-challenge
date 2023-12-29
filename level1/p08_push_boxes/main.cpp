#include <cstdio>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <unistd.h>
#include <vector>
using namespace std;

/*      GameMaps.txt
T  #################,
#          @      *#,
# # ####   ##### ###,
  # ###  #    ## ###,
  @ ### ### # ## ###,
  #     ### #   ##M#,
# # ### ###   # ##E#,
#          *### ##O#,
### ########### ##W#,
###      #Meow#     ,
####################%
T  ######  #########,
#         @#     *##,
# # # ##   # ### ###,
# #  @           ###,
# # ### ##  # ##   #,
# #     ### #   ##M#,
# # ### ###   # ##E#,
#           ### ##O#,
# # ########### ##W#,
#       *#Meow#    *,
####################%
T  ###    ##########,
#     @    #     *##,
# # ####   # ### ###,
###              ###,
#*# ### ##  # ##   #,
# #    @### #     M#,
# # ### ###   ####E#,
#           ######O#,
# # ########### ##W ,
#        #Meow#*    ,
####################

*/


vector<vector<string>> MapData;
vector<string> map;

vector<string> stringSplit(const string& strIn, char delim) {
    char* str = const_cast<char*>(strIn.c_str());
    string s;
    s.append(1, delim);
    vector<string> elems;
    char* splitted = strtok(str, s.c_str());
    while (splitted != NULL) {
        elems.push_back(string(splitted));
        splitted = strtok(NULL, s.c_str());
    }
    return elems;
}

string CachePath="GameProgress.txt";
string DataPath="GameMaps.txt";
int MapIndex=0;

int main()
{
    system("chcp 65001");
    CONSOLE_CURSOR_INFO c={1,0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&c);
    printf("使用 w s a d控制人物T移动 将'@'扔进垃圾桶'*'处\r\n");
    system("pause");

    //读取上一次游戏进度..
    ifstream is(CachePath);
    if(is.good()){
        fstream fs;
        fs.open(CachePath, ios::in);
        if (fs.is_open()) {
            string buffer;
            while(getline(fs, buffer)) {
                vector scores=stringSplit(buffer,'|');
                if(scores.size()>0)
                if(atoi(scores[1].c_str())!=0)
                    MapIndex=atoi(scores[0].c_str())+1;
            }
        }
    }

    //Load GameData
    fstream fi;
    fi.open(DataPath, ios::in);
    if (fi.is_open()) {
        string buffer;
        string data;
        while (getline(fi, buffer))
            data+=buffer;
        vector dt= stringSplit(data,'%');
        for(int i=0;i<dt.size();i++){
            MapData.push_back(stringSplit(dt[i],','));
        }
        if(MapIndex>=MapData.size()){
            cout<<"再来一局?\r\n"<<endl;
            system("pause");
            MapIndex=0;
        }
        map= MapData[MapIndex];
    }
for(;;) {
    SetConsoleTitle(("当前关卡:" + to_string(MapIndex+1)).c_str());
    system("cls");
    for (int i = 0; i <= 10; i++)
        cout << map[i] << endl;
    int x = 0, y = 0, count = 0, step = 0;
    bool ThrowMyself = false;
    for (;;) {
        char input = getch();
        step++;
        switch (input) {
            case 'w':
                if (x == 0)break;
                if (map[x - 1][y] != '#') {
                    map[x][y] = ' ';
                    if (map[x - 1][y] == '@' && map[x - 2][y] == ' ')
                        map[x - 2][y] = '@';
                    else if (map[x - 1][y] == '@' && map[x - 2][y] == '*') {
                        map[x - 2][y] = ' ';
                        map[x - 1][y] = ' ';
                        count++;
                    } else if (map[x - 1][y] == '*') {
                        ThrowMyself = true;
                        map[x - 1][y] = 'T';
                        break;
                    }
                    map[x - 1][y] = 'T';
                    x -= 1;
                }
                break;
            case 's':
                if (x == 10)break;
                if (map[x + 1][y] != '#') {
                    map[x][y] = ' ';
                    if (map[x + 1][y] == '@' && map[x + 2][y] == ' ')
                        map[x + 2][y] = '@';
                    else if (map[x + 1][y] == '@' && map[x + 2][y] == '*') {
                        map[x + 2][y] = ' ';
                        map[x + 1][y] = ' ';
                        count++;
                    } else if (map[x + 1][y] == '*') {
                        ThrowMyself = true;
                        map[x + 1][y] = 'T';
                        break;
                    }
                    map[x + 1][y] = 'T';
                    x += 1;
                }
                break;
            case 'a':
                if (y == 0)break;
                if (map[x][y - 1] != '#') {
                    map[x][y] = ' ';
                    if (map[x][y - 1] == '@' && map[x][y - 2] == ' ')
                        map[x][y - 2] = '@';
                    else if (map[x][y - 1] == '@' && map[x][y - 2] == '*') {
                        map[x][y - 2] = ' ';
                        map[x][y - 1] = ' ';
                        count++;
                    } else if (map[x][y - 1] == '*') {
                        ThrowMyself = true;
                        map[x][y - 1] = 'T';
                        break;
                    }
                    map[x][y - 1] = 'T';
                    y -= 1;
                }
                break;
            case 'd':
                if (y == 20)break;
                if (map[x][y + 1] != '#') {
                    map[x][y] = ' ';
                    if (map[x][y + 1] == '@' && map[x][y + 2] == ' ')
                        map[x][y + 2] = '@';
                    else if (map[x][y + 1] == '@' && map[x][y + 2] == '*') {
                        map[x][y + 2] = ' ';
                        map[x][y + 1] = ' ';
                        count++;
                    } else if (map[x][y + 1] == '*') {
                        ThrowMyself = true;
                        map[x][y + 1] = 'T';
                        break;
                    }
                    map[x][y + 1] = 'T';
                    y += 1;
                }
                break;
        }
        system("cls");
        for (int i = 0; i <= 10; i++)
            cout << map[i] << endl;
        if (ThrowMyself)
            break;
        if (count == 2)
            break;
    }

    printf(ThrowMyself ? "you threw yourself into the rubbish bin!\r\n" : "you win!\r\n");
    int score = ThrowMyself ? 0 : count * 50 - step;
    printf("You walked %d steps & got %d score.\r\n", step, score);

    ofstream os;
    os.open(CachePath, ios::app);
    if (!os.is_open())
        cout << "Filed to create game data.\r\n" << endl;
    else {
        os << to_string(MapIndex) + '|' + to_string(score)+"\n" <<endl;
        os.close();
    }

    if(count == 2) {
        if (MapIndex + 1 < MapData.size()) {
            MapIndex++;
            map = MapData[MapIndex];
            cout << "Enter to next session.\r\n" << endl;
        } else if (MapIndex + 1 == MapData.size()) {
            cout << "Excellent!\r\n" << endl;
            system("pause");
            break;
        }
    }else map = MapData[MapIndex];

    system("pause");
    }
    return 0;
}