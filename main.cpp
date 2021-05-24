//POP_2018_12_21_projekt_1_Włódarczak_Wojciech_EIT_6_175900 CodeBlocks 17.12
#include <iostream>
#include <cstdlib>
using namespace std;
//Struktura obiektów na planszy (gracz, paczki, miejsca na paczki)
struct object
{
    char sign;
    int x;
    int y;
};
//Funkcja rysująca baner
void drawBaner(void)
{
    cout << "  _|_|_|            _|                  _|                          " << endl;
    cout << "_|          _|_|    _|  _|      _|_|    _|_|_|      _|_|_|  _|_|_|  " << endl;
    cout << "  _|_|    _|    _|  _|_|      _|    _|  _|    _|  _|    _|  _|    _|" << endl;
    cout << "      _|  _|    _|  _|  _|    _|    _|  _|    _|  _|    _|  _|    _|" << endl;
    cout << "_|_|_|      _|_|    _|    _|    _|_|    _|_|_|      _|_|_|  _|    _|" << endl;
    cout << "Autor: Wojciech W\210\242darczak" << endl;
    cout << "Wszelkie Prawa Zastrzerzone" << endl;
    cout << endl;
    cout << endl;
}
//Funkcja wypisująca zasady
void showRules(void)
{
    cout << "Zasady:" << endl;
    cout << "Sokoban - gra polega na poruszaniu si\251 robotnikiem po magazynie. W magazynie" << endl;
    cout << "znajduj\245 si\251 paczki i miejsca, gdzie paczki powinny sta\206. Robotnik mo\276e" << endl;
    cout << "pcha\206 paczki, przy czym mo\276e pcha\206 tylko jedn\245 paczk\251 na raz. Ani paczka," << endl;
    cout << "ani robotnik nie mog\245 wyj\230\206 poza obr\251b magazynu. Gracz wygrywa, gdy wszystkie" << endl;
    cout << "paczki b\251d\245 na oznaczonych miejscach." << endl;
    cout << endl;
    cout << "Symbolika:" << endl;
    cout << "R - Robotnik(Gracz)" << endl;
    cout << "X - Paczka" << endl;
    cout << "O - Miejsce na paczk\251" << endl;
    cout << endl;
    cout << "Sterowanie:" << endl;
    cout << "w - G\242ra" << endl;
    cout << "s - D\242\210" << endl;
    cout << "a - Lewo" << endl;
    cout << "d - Prawo" << endl;
    cout << "q - Wyj\230cie" << endl;
    cout << "? - Pomoc" << endl << endl;
    system("pause");
    system("cls");
}
//Funkcja rysująca planszę
void drawLevel(char **tab,const int width,const int height)
{
    for(int y=0;y<height;y++,cout << endl)
    {
        for(int x=0;x<width;x++)
        {
            cout<< tab[y][x];
        }
    }
    cout << endl;
    cout << endl;
}
//Funkcja odpowiedzialna za zwracanie odpowiednich wymiarów dla dwuwymiarowej tablicy w zależności od wyboru poziomu
int resizeT(char sign, int level)
{
    if(level==1)
    {
        if(sign=='h')return 8;
        else if(sign=='w')return 12;
    }
    if(level==2)
    {
        if(sign=='h')return 17;
        else if(sign=='w')return 17;
    }
    if(level==3)
    {
        if(sign=='h')return 18;
        else if(sign=='w')return 24;
    }
}
//Funkcje odpowiedzialne za poruszanie się graczem
//Uwzględnione zostały przypadki kiedy gracz będzie chciał wyjść poza zakres planszy (na wszelki wypadek)
//Uniemożliwienie graczowi popychanie dwóch paczek na raz
//Kolizje gracza oraz paczek ze ścianami
void moveUp(object &p, char **tab, object *b,int q, int w, int h)
{
    if(p.y > 0)
    {
        if(tab[p.y-1][p.x] == ' ' || tab[p.y-1][p.x] == 'O' || tab[p.y-1][p.x] == 'X')
        {
            if(tab[p.y-1][p.x] == 'X')
            {
                if(tab[p.y-2][p.x] == ' ' || tab[p.y-2][p.x] == 'O')
                {
                    int i = 0;
                    while(i<q)
                    {
                        if(b[i].x == p.x && b[i].y == p.y-1)
                        {
                            b[i].y -= 1;
                            i = q;
                        }
                        i++;
                    }
                    p.y -= 1;
                }
            }
            else p.y -= 1;
        }
    }
}
void moveDown(object &p, char **tab, object *b,int q, int w, int h)
{
    if(p.y < h-1)
    {
        if(tab[p.y+1][p.x] == ' ' || tab[p.y+1][p.x] == 'O' || tab[p.y+1][p.x] == 'X' )
        {
            if(tab[p.y+1][p.x] == 'X')
            {
                if(tab[p.y+2][p.x] == ' ' || tab[p.y+2][p.x] == 'O')
                {
                    int i = 0;
                    while(i<q)
                    {
                        if(b[i].x == p.x && b[i].y == p.y+1)
                        {
                            b[i].y += 1;
                            i = q;
                        }
                        i++;
                    }
                    p.y += 1;
                }
            }
            else p.y += 1;
        }
    }
}
void moveLeft(object &p, char **tab, object *b,int q, int w, int h)
{
    if(p.x > 0)
    {
        if(tab[p.y][p.x-1] == ' ' || tab[p.y][p.x-1] == 'O' || tab[p.y][p.x-1] == 'X' )
        {
            if(tab[p.y][p.x-1] == 'X')
            {
                if(tab[p.y][p.x-2] == ' ' || tab[p.y][p.x-2] == 'O')
                {
                    int i = 0;
                    while(i<q)
                    {
                        if(b[i].x == p.x-1 && b[i].y == p.y)
                        {
                            b[i].x -= 1;
                            i = q;
                        }
                        i++;
                    }
                    p.x -= 1;
                }
            }
            else p.x -= 1;
        }
    }
}
void moveRight(object &p, char **tab, object *b,int q, int w, int h)
{
    if(p.x < w-1)
    {
        if(tab[p.y][p.x+1] == ' ' || tab[p.y][p.x+1] == 'O' || tab[p.y][p.x+1] == 'X' )
        {
            if(tab[p.y][p.x+1] == 'X')
            {
                if(tab[p.y][p.x+2] == ' ' || tab[p.y][p.x+2] == 'O')
                {
                    int i = 0;
                    while(i<q)
                    {
                        if(b[i].x == p.x+1 && b[i].y == p.y)
                        {
                            b[i].x += 1;
                            i = q;
                        }
                        i++;
                    }
                    p.x += 1;
                }
            }
            else p.x += 1;
        }
    }
}
//Funkcja odpowiedzialna za zwrócenie ilości istniejących paczek oraz równej ilości miejsc na paczki
int quantityPlaces(int level)
{
    if(level==1)return 1;
    else if(level==2) return 3;
    else if(level==3) return 11;
}
//Funkcja wyświetlająca informacje o wygranej
void writeWin(int level)
{
    cout << "Gratulacje! wygra\210e\230 poziom " <<level<<"!"<<endl<<endl;
    system("pause");
    system("cls");
}
//Funkcja zliczająca ile paczek znajduje się na odpowiednich miejscach
int checkPlaces(object boxes[], object places[], int quantity)
{
    int counter = 0;
    for(int i=0; i<quantity;i++)
    {
        int j=0;
        while(j<quantity)
        {
            if(places[i].x==boxes[j].x && places[i].y ==boxes[j].y)
            {
                counter++;
            }
            j++;
        }
    }
    return counter;
}
//Funkcje odpowiedzialne za nadanie dwuwymiarowej tablicy dynamicznej odpowiedniego rozmieszczenia ścian, gracza, paczek oraz miejsc na paczki
void map1(char **tab,const int height,const int width,char w[])
{
    char tmp[8][12] = {{ ' ', ' ', ' ', ' ',w[0],w[4],w[1], ' ', ' ', ' ', ' ','\0'},
                       { ' ', ' ', ' ',w[0],w[3], ' ',w[2],w[4],w[4],w[4],w[1],'\0'},
                       {w[0],w[4],w[4],w[3], ' ', ' ', ' ', ' ', ' ', 'O',w[5],'\0'},
                       {w[5], 'R', ' ', ' ', ' ', 'X',w[0],w[4],w[1], ' ',w[5],'\0'},
                       {w[2],w[4],w[4],w[4],w[1], ' ',w[5], ' ',w[5], ' ',w[5],'\0'},
                       { ' ', ' ', ' ', ' ',w[5], ' ',w[2],w[4],w[3], ' ',w[5],'\0'},
                       { ' ', ' ', ' ', ' ',w[5], ' ', ' ', ' ', ' ', ' ',w[5],'\0'},
                       { ' ', ' ', ' ', ' ',w[2],w[4],w[4],w[4],w[4],w[4],w[3],'\0'}};
    for(int i=0;i<height;i++)
    {
        for(int j=0; j<width; j++)tab[i][j]=tmp[i][j];
    }
}
void map2(char **tab,const int height,const int width,char w[])
{
    char tmp[17][17] = {{ ' ',w[0],w[4],w[1], ' ', ' ', ' ',w[0],w[4],w[1], ' ',w[0],w[4],w[4],w[1], ' ','\0'},
                        {w[0],w[3], ' ',w[2],w[4],w[1],w[0],w[3], ' ',w[2],w[4],w[3], ' ', ' ',w[2],w[1],'\0'},
                        {w[5], ' ', ' ', 'O', 'O',w[5],w[5], ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',w[5],'\0'},
                        {w[5], ' ', ' ',w[0],w[4],w[3],w[5], ' ', ' ',w[0],w[4],w[4],w[1], ' ',w[0],w[3],'\0'},
                        {w[2],w[1], ' ',w[5], ' ', ' ',w[2],w[1], ' ',w[5], ' ', ' ',w[5], ' ',w[5], ' ','\0'},
                        { ' ',w[5], ' ',w[5], ' ', ' ', ' ',w[5], ' ',w[5], ' ', ' ',w[5], ' ',w[5], ' ','\0'},
                        { ' ',w[5], ' ',w[5], ' ', ' ', ' ',w[5], ' ',w[5], ' ', ' ',w[5], ' ',w[5], ' ','\0'},
                        { ' ',w[5], ' ',w[5], ' ', ' ', ' ',w[5], ' ',w[5], ' ', ' ',w[5], ' ',w[5], ' ','\0'},
                        { ' ',w[5], ' ',w[2],w[1], ' ', ' ',w[5], ' ',w[5], ' ', ' ',w[5], ' ',w[2],w[1],'\0'},
                        {w[0],w[3], ' ', ' ',w[2],w[4],w[4],w[3], ' ',w[2],w[4],w[4],w[3], ' ', ' ',w[5],'\0'},
                        {w[5], ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', 'X', ' ', ' ', ' ', ' ', ' ',w[5],'\0'},
                        {w[2],w[1], ' ', ' ',w[0],w[4],w[4],w[1], ' ',w[0],w[4],w[4],w[4],w[4],w[4],w[3],'\0'},
                        { ' ',w[5], ' ',w[0],w[3], ' ', ' ',w[5], ' ',w[5], ' ', ' ', ' ', ' ', ' ', ' ','\0'},
                        { ' ',w[5], ' ',w[5], ' ', ' ', ' ',w[5], ' ',w[2],w[4],w[1], ' ', ' ', ' ', ' ','\0'},
                        { ' ',w[5], 'O',w[5], ' ', ' ', ' ',w[5], ' ', 'X', ' ',w[5], ' ', ' ', ' ', ' ','\0'},
                        { ' ',w[5], ' ',w[5], ' ', ' ', ' ',w[5], 'R', ' ', ' ',w[5], ' ', ' ', ' ', ' ','\0'},
                        { ' ',w[2],w[4],w[3], ' ', ' ', ' ',w[2],w[4],w[4],w[4],w[3], ' ', ' ', ' ', ' ','\0'}};
    for(int i=0;i<height;i++)
    {
        for(int j=0; j<width; j++)tab[i][j]=tmp[i][j];
    }
}
void map3(char **tab,const int height,const int width,char w[])
{
    char tmp[18][24] = {{ ' ',w[0],w[4],w[4],w[4],w[4],w[4],w[4],w[1], ' ',w[0],w[4],w[4],w[4],w[4],w[4],w[4],w[1], ' ',w[0],w[4],w[4],w[1],'\0'},
                        { ' ',w[5], ' ', ' ', ' ', ' ', ' ', ' ',w[5], ' ',w[5], ' ', ' ', ' ', ' ', ' ', ' ',w[2],w[4],w[3], ' ', ' ',w[5],'\0'},
                        { ' ',w[5], ' ',w[0],w[4],w[1], ' ', 'X',w[5], ' ',w[5], ' ',w[0],w[4],w[4],w[1], 'X', 'O', ' ', ' ', 'X', ' ',w[5],'\0'},
                        { ' ',w[5], 'X',w[5], ' ',w[5], ' ', ' ',w[2],w[1],w[5], ' ',w[5], ' ', ' ',w[5], ' ',w[0],w[1], ' ', ' ', ' ',w[5],'\0'},
                        { ' ',w[5], ' ',w[5],w[0],w[3], ' ', 'X', ' ',w[2],w[3], ' ',w[2],w[4],w[1],w[5], ' ',w[5],w[2],w[4],w[4],w[4],w[3],'\0'},
                        { ' ',w[5], ' ',w[5],w[5], 'O', ' ', 'X', ' ', ' ', ' ', ' ', 'O', ' ',w[5],w[5], ' ',w[5], ' ', ' ', ' ', ' ', ' ','\0'},
                        {w[0],w[3], ' ',w[5],w[2],w[4],w[1], ' ',w[0],w[4],w[1], ' ',w[0],w[4],w[3],w[5], ' ',w[2],w[1], ' ', ' ', ' ', ' ','\0'},
                        {w[5], ' ', ' ',w[2],w[4],w[4],w[3], 'X',w[2],w[4],w[3], ' ',w[5],w[0],w[4],w[3], ' ', ' ',w[2],w[4],w[4],w[1], ' ','\0'},
                        {w[5], ' ', ' ', ' ', 'O', ' ', 'O', ' ', ' ', ' ', ' ', ' ',w[5],w[5], ' ', 'O', ' ', ' ', ' ', ' ', ' ',w[5], ' ','\0'},
                        {w[2],w[1], ' ',w[0],w[4],w[4],w[1], ' ',w[0],w[4],w[4],w[4],w[3],w[2],w[4],w[4],w[4],w[4],w[4],w[1], ' ',w[5], ' ','\0'},
                        { ' ',w[2],w[4],w[3], ' ', ' ',w[5], ' ',w[5], ' ', ' ', ' ', ' ',w[0],w[4],w[4],w[1], ' ', ' ',w[5], ' ',w[5], ' ','\0'},
                        { ' ', ' ',w[0],w[4],w[4],w[1],w[5], ' ',w[5], ' ', ' ', ' ', ' ',w[5], ' ', ' ',w[2],w[4],w[1],w[5], 'X',w[2],w[1],'\0'},
                        {w[0],w[4],w[3], ' ', ' ',w[2],w[3], ' ',w[2],w[4],w[4],w[4],w[4],w[3], 'X', ' ', 'X', ' ',w[2],w[3], ' ', ' ',w[5],'\0'},
                        {w[5], ' ', 'X', ' ', ' ', ' ', 'O', 'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',w[0],w[3],'\0'},
                        {w[5], ' ', ' ', ' ',w[0],w[4],w[1], ' ',w[0],w[4],w[1], ' ',w[0],w[4],w[1], ' ',w[0],w[4],w[4],w[1], 'O',w[5], ' ','\0'},
                        {w[2],w[4],w[1], 'O',w[2],w[4],w[3], ' ',w[5], ' ',w[5], ' ',w[5], ' ',w[5], 'O',w[5], ' ', ' ',w[5], ' ',w[5], ' ','\0'},
                        { ' ', ' ',w[5], ' ', ' ', ' ', ' ', ' ',w[5], ' ',w[5], 'R',w[5], ' ',w[5], ' ',w[5], ' ', ' ',w[2],w[4],w[3], ' ','\0'},
                        { ' ', ' ',w[2],w[4],w[4],w[4],w[4],w[4],w[3], ' ',w[2],w[4],w[3], ' ',w[2],w[4],w[3], ' ', ' ', ' ', ' ', ' ', ' ','\0'}};
    for(int i=0;i<height;i++)
    {
        for(int j=0; j<width; j++)tab[i][j]=tmp[i][j];
    }
}
//Funkcja przydzielająca startowe współrzędne graczowi, paczkom oraz miejscom na paczki
void assignCoordinates(char **tab, object &player, object *places, object *boxes, int height, int width)
{
    int ip = 0;
    int ib = 0;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(tab[i][j] == 'R')
            {
                player.sign=tab[i][j];
                player.x = j;
                player.y = i;
            }
            if(tab[i][j] == 'O')
            {
                places[ip].sign=tab[i][j];
                places[ip].x = j;
                places[ip].y = i;
                ip++;
            }
            if(tab[i][j] == 'X')
            {
                boxes[ib].sign=tab[i][j];
                boxes[ib].x = j;
                boxes[ib].y = i;
                ib++;
            }
        }
    }
}
//Funkcja odpowiedzialna za upewnienie się czy gracz na pewno chce opuścić aktualną rozgrywkę
bool exitFromLevel()
{
    char action;
    cout << "Czy na pewno chcesz wyj\230\206? Je\230li tak, wpisz \"T\" lub \"t\" a je\230li nie, wpisz cokolwiek innego i zatwierd\253: ";
    cin >> action;
    system("cls");
    if(action == 'T' || action == 't')return false;
    return true;
}
void game(int level)
{   //Rodzaje ścian
    char walls[]={char(201),char(187),char(200),char(188),char(205),char(186)};
    //Wywołanie funkcji która w zależności od wybranego poziomu dobierze tablicy odpowiednie wymiary;
    const int height=resizeT('h',level);
    const int width=resizeT('w',level);
    //Tworzenie dwuwymiarowej tablicy dynamicznej dla wybranej mapy
    char ** tab = new char *[height];
    for(int i=0;i<height;i++)tab[i] = new char[width];
    //Tworzenie gracza
    object player;
    //Ilość miejsc na paczki w zależności od wybranego poziomu (ilość miejsc na paczki zawsze jest równa ilości paczek)
    const int quantity = quantityPlaces(level);
    //Tworzenie tablic przechowujących parametry miejsc na paczki oraz paczek
    object places[quantity];
    object boxes[quantity];
    //Tworzenie wybranego poziomu
    if(level==1)map1(tab, height, width+1, walls);
    else if(level==2)map2(tab, height, width+1, walls);
    else if(level==3)map3(tab, height, width+1, walls);
    //Wywołanie funkcji przydzielającej odpowiednie koordynaty graczowi, miejscom na paczki oraz paczkom
    assignCoordinates(tab, player, places, boxes, height, width);
    //Warunek działania pętli
    bool running = true;
    //Akcja, którą będzie podejmował gracz
    char action;
    //Zmienna przechowująca informację czy gracz podjął właściwą akcję
    bool correctOption=true;
    //Pętla główna
    while (running)
    {
        //Wywołanie funkcji rysującej mapę
        drawLevel(tab,width, height);
        if(correctOption)cout << "Wybierz akcj\251 i zatwierd\253: ";
        else
        {
            cout << "Wybierz poprawn\245 akcj\251 i zatwierd\253: ";
            correctOption = true;
        }
        cin >> action;
        system("cls");
        //Sprawdzanie czy gracz podjął akcję wywołującą poruszanie
        if(action =='w' || action=='s' || action =='a' || action =='d')
        {
            tab[player.y][player.x]=' ';
            //Wywołanie funkcji wywołujących poruszanie się w odpowiednim kierunku
            if(action=='w')moveUp(player, tab, boxes, quantity, width, height);
            else if(action=='s')moveDown(player, tab, boxes, quantity, width, height);
            else if(action=='a')moveLeft(player, tab, boxes, quantity, width, height);
            else moveRight(player, tab, boxes, quantity, width, height);
            //Aktualizacja widoczności miejsca na paczki na mapie
            for(int i = 0; i < quantity; i++)tab[places[i].y][places[i].x]=places[i].sign;
            //Aktualizacja widoczności paczek na mapie
            for(int i = 0; i<quantity;i++)tab[boxes[i].y][boxes[i].x]=boxes[i].sign;
            //Aktualizacha widoczności gracza na mapie
            tab[player.y][player.x] = player.sign;
            //Wywołanie funkcji sprawdzającej czy ilość paczek na odpowiednich miejscach jest równa ilości istniejących paczek
            if(checkPlaces(boxes, places, quantity)==quantity)
            {
                drawLevel(tab, width, height);
                //Wywołanie funkcji odpowiedzialnej za wyświetlenie informacji o wygranej
                writeWin(level);
                running = false;
            }
        }
        else if(action == '?')showRules();
        else if(action == 'q')
        {
            drawLevel(tab,width, height);
            //Wywołanie funkcji odpowiedzialnej za wyjście z aktualnej rozgrywki
            running = exitFromLevel();
        }
        else correctOption = false;
    }
    //Uusuwanie dwuwymiarowej tablicy dynamicznej
    for(int i=0;i<height;i++)delete [] tab[i];
    delete [] tab;
}
//Wybór poziomów
void showLevels(void)
{
    bool running=true;
    char option;
    bool correctOption=true;
    while(running){
        drawBaner();
        cout << "  Dost\251pne poziomy:" << endl;
        cout << "(    1.Poziom 1    )" << endl;
        cout << "(    2.Poziom 2    )" << endl;
        cout << "(    3.Poziom 3    )" << endl;
        cout << "(    4.Cofnij      )" << endl;
        cout << endl;
        cout << endl;
        if(correctOption)cout << "Wybierz opcj\251 i zatwierd\253: ";
        else
        {
            cout << "Wybierz poprawn\245 opcj\251 i zatwierd\253: ";
            correctOption=true;
        }
        cin >> option;
        system("cls");
        //Wybór wartości od 1 do 3 skutkuje wywołaniem funkcji odpowiedzialnej za mechanikę gry z parametrem
        //decydującym o poziomie, który wybrał gracz
        if(option=='1' || option=='2'|| option=='3')game(int(option)-48);
        //Cofnięcie się do poprzedniego menu
        else if(option=='4')running=false;
        else correctOption = false;
    }
}
//Menu Główne
void showMenu(void)
{
    bool running=true;
    char option;
    bool correctOption=true;
    while(running){
        drawBaner();
        cout << "   Menu G\210\242wne:" << endl;
        cout << "(    1.Zagraj    )" << endl;
        cout << "(    2.Zasady    )" << endl;
        cout << "(    3.Koniec    )" << endl;
        cout << endl;
        cout << endl;
        if(correctOption)cout << "Wybierz opcj\251 i zatwierd\253: ";
        else
        {
            cout << "Wybierz poprawn\245 opcj\251 i zatwierd\253: ";
            correctOption=true;
        }
        cin >> option;
        system("cls");
        //Wywołanie funkcji odpowiedzialnej za wyświetlenie dostępnych poziomów
        if(option=='1')showLevels();
        //Wywołanie funkcji odpowiedzialnej za wyświetlenie zasad
        else if(option=='2')showRules();
        else if(option=='3')running=false;
        else correctOption = false;
    }
}
int main()
{
    //Wywołanie funkcji odpowiedzialnej za wyświetlenie menu
    showMenu();
    return 0;
}
