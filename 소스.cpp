#include<Bangtal.h>
#pragma comment(lib,"bangtal.lib")
#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;

SceneID scene1;
ObjectID startButton, endButton;
ObjectID p00, p01, p02, p03, p10, p11, p12, p13, p20, p21, p22, p23, p30, p31, p32, p33;
bool bp00, bp01, bp02, bp03, bp10, bp11, bp12, bp13, bp20, bp21, bp22, bp23, bp30, bp31, bp32, bp33;
TimerID timer1;

int boardx[4][4] =
{
 {0,150,300,450},
 {0,150,300,450},
 {0,150,300,450},
 {0,150,300,450}
};

int boardy[4][4] =
{
 {450, 450, 450,450},
 {300,300,300,300},
 {150,150,150,150},
 {0,0,0,0}
};

ObjectID board[4][4] =
{
 {p00, p01, p02,p03},
 {p10, p11,p12,p13},
 {p20,p21,p22,p23},
 {p30,p31,p32,p33}
};
bool bboard[4][4] =
{
 {bp00, bp01, bp02,bp03},
 {bp10, bp11,bp12,bp13},
 {bp20,bp21,bp22,bp23},
 {bp30,bp31,bp32,bp33}
};


ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y, bool shown, bool isblank)
{
    ObjectID object = createObject(name, image);
    locateObject(object, scene, x, y);
    if (shown == true)
    {
        showObject(object);
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (isblank == true && board[i][j] == bboard[i][j])
                bboard[i][j] = true;
        }
    }
    return object;
}
void restart()
{



    setObjectImage(startButton, "restart.png");
    showObject(startButton);


}
void f(ObjectID m, ObjectID n, int x, int y)
{



    ObjectID temp = m;
    m = n;
    m = temp;
}
void mix(void)
{
    int x, y;
    int isexist[16][2]
    {
    {10,10},
    {10,10},
    {10,10},
    {10,10},
    {10,10},
    {10,10},
    {10,10},
    {10,10},
    {10,10},
    {10,10},
    {10,10},
    {10,10},
    {10,10},
    {10,10},
    {10,10},
    {10,10}
    };
    int m = 0;


    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            x = rand() % 4;
            y = rand() % 4;


            for (int k = 0; k < 16; k++)
            {
                for (; isexist[k][0] == x && isexist[k][1] == y;)
                {
                    x = rand() % 4;
                    y = rand() % 4;
                    k = -1;
                }

            }
            ObjectID ob = board[x][y];
            ObjectID temp = board[i][j];


            locateObject(board[i][j], scene1, boardx[x][y], boardy[x][y]);
            locateObject(ob, scene1, boardx[i][j], boardy[i][j]);
            board[i][j] = board[x][y];
            board[x][y] = temp;

            if (bboard[i][j] == true)
            {
                bboard[i][j] = false;
                bboard[x][y] = true;
            }
            else if (bboard[x][y] == true)
            {
                bboard[i][j] = true;
                bboard[x][y] = false;
            }


            isexist[m][0] = x;
            isexist[m][1] = y;
            m++;

        }
    }

}


void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
    if (object == startButton)
    {
        hideObject(startButton);
        restart();
        mix();
        setTimer(timer1, 10000.0f);
        showTimer(timer1);
        startTimer(timer1);


    }
    else if (object == endButton)
    {
        cout << (10000 - getTimer(timer1)) << ("초 걸렸습니다");
        endGame();
    }




    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {

            if (object == board[i][j] && bboard[i][j] != true)
            {
                if (bboard[i + 1][j] == true)
                {
                    ObjectID temp = board[i][j];

                    locateObject(board[i + 1][j], scene1, boardx[i][j], boardy[i][j]);
                    locateObject(temp, scene1, boardx[i + 1][j], boardy[i + 1][j]);
                    board[i][j] = board[i + 1][j];
                    board[i + 1][j] = temp;
                    bboard[i][j] = true;
                    bboard[i + 1][j] = false;
                    goto EXIT;




                }

                else if (bboard[i - 1][j] == true)

                {
                    ObjectID temp = board[i][j];
                    locateObject(board[i - 1][j], scene1, boardx[i][j], boardy[i][j]);
                    locateObject(temp, scene1, boardx[i - 1][j], boardy[i - 1][j]);


                    board[i][j] = board[i - 1][j];
                    board[i - 1][j] = temp;
                    bboard[i][j] = true;
                    bboard[i - 1][j] = false;
                    goto EXIT;
                }

                else if (bboard[i][j + 1] == true)
                {
                    ObjectID temp = board[i][j];
                    locateObject(board[i][j + 1], scene1, boardx[i][j], boardy[i][j]);
                    locateObject(temp, scene1, boardx[i][j + 1], boardy[i][j + 1]);

                    board[i][j] = board[i][j + 1];
                    board[i][j + 1] = temp;
                    bboard[i][j] = true;
                    bboard[i][j + 1] = false;
                    goto EXIT;

                }

                else if (bboard[i][j - 1] == true)
                {
                    ObjectID temp = board[i][j];
                    locateObject(board[i][j - 1], scene1, boardx[i][j], boardy[i][j]);
                    locateObject(temp, scene1, boardx[i][j - 1], boardy[i][j - 1]);

                    board[i][j] = board[i][j - 1];
                    board[i][j - 1] = temp;
                    bboard[i][j] = true;
                    bboard[i][j - 1] = false;
                    goto EXIT;
                }

            }

        }

    }
EXIT:
    {

    }

}
void timerCallback(TimerID timer)
{

    if (timer == timer1)
    {
        showMessage("시간 초과 다시 시작하시오");

    }



}


int main(void)
{

    setMouseCallback(mouseCallback);
    setTimerCallback(timerCallback);
    srand((unsigned int)time(NULL));

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            bboard[i][j] = false;
        }
    }
    timer1 = createTimer(10000.0f);
    scene1 = createScene("scene1", "배경.jpg");
    board[0][0] = createObject("p00", "1.png", scene1, boardx[0][0], boardy[0][0], true, false);
    board[0][1] = createObject("p01", "2.png", scene1, boardx[0][1], boardy[0][1], true, false);
    board[0][2] = createObject("p02", "3.png", scene1, boardx[0][2], boardy[0][2], true, false);
    board[0][3] = createObject("p03", "4.png", scene1, boardx[0][3], boardy[0][3], true, false);
    board[1][0] = createObject("p10", "5.png", scene1, boardx[1][0], boardy[1][0], true, false);
    board[1][1] = createObject("p11", "6.png", scene1, boardx[1][1], boardy[1][1], true, false);
    board[1][2] = createObject("p12", "7.png", scene1, boardx[1][2], boardy[1][2], true, false);
    board[1][3] = createObject("p13", "8.png", scene1, boardx[1][3], boardy[1][3], true, false);
    board[2][0] = createObject("p20", "9.png", scene1, boardx[2][0], boardy[2][0], true, false);
    board[2][1] = createObject("p21", "10.png", scene1, boardx[2][1], boardy[2][1], true, false);
    board[2][2] = createObject("p22", "11.png", scene1, boardx[2][2], boardy[2][2], true, false);
    board[2][3] = createObject("p23", "12.png", scene1, boardx[2][3], boardy[2][3], true, false);
    board[3][0] = createObject("p30", "13.png", scene1, boardx[3][0], boardy[3][0], true, false);
    board[3][1] = createObject("p31", "14.png", scene1, boardx[3][1], boardy[3][1], true, false);
    board[3][2] = createObject("p32", "15.png", scene1, boardx[3][2], boardy[3][2], true, false);
    board[3][3] = createObject("blank", "16.png", scene1, boardx[3][3], boardy[3][3], false, true);
    startButton = createObject("startButton", "start.png", scene1, 900, 300, true, false);
    endButton = createObject("endButton", "end.png", scene1, 900, 500, true, false);

    startGame(scene1);
}