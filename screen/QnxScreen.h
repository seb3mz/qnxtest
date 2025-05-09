#ifndef __QNX_SCREEN_H__
#define __QNX_SCREEN_H__

class QNXScreen
{
public:
    QNXScreen();
    ~QNXScreen();

    void init();
    void deinit();
    void setResolution(int width, int height);
    void getResolution(int &width, int &height);
    void setBrightness(int level);
    int getBrightness();
};

#endif // __QNX_SCREEN_H__