#include <iostream>
#include <screen/screen.h>
using namespace std;

int main()
{

    //Create a Screen context.
    screen_context_t screen_ctx;
    int ret = screen_create_context(&screen_ctx, SCREEN_APPLICATION_CONTEXT/* SCREEN_WINDOW_MANAGER_CONTEXT | SCREEN_BUFFER_PROVIDER_CONTEXT*/);
    if(0 != ret){
        cout << "创建 context 失败" << endl;
        return -1;
    }

    //获取屏幕数量
    int ndisplays = 0;
    screen_get_context_property_iv(screen_ctx, SCREEN_PROPERTY_DISPLAY_COUNT, &ndisplays);
    cout << "number_display = " << ndisplays << endl;

    screen_display_t *screen_dlist = (screen_display_t*)calloc(ndisplays,sizeof(screen_display_t));
    if(screen_dlist == NULL){ 
        cout <<  "calloc failed. ndisplays:" << ndisplays << endl;
        return -1;
    }
    (void)screen_get_context_property_pv(screen_ctx,SCREEN_PROPERTY_DISPLAYS,(void **)screen_dlist);

    int curId = 0;
    for(int i = 0; i < ndisplays; ++i) 
    {
        screen_get_display_property_iv(screen_dlist[i], SCREEN_PROPERTY_ID, &curId);
        cout << "curId = " << curId << endl;
    }
    
    //Create a render target.
    screen_window_t screen_win;
    ret = screen_create_window(&screen_win, screen_ctx);
    if(0 != ret){
        cout << "创建 window 失败" << endl;
        return -1;
    }

    //Set the appropriate properties of your render target.
    screen_set_window_property_pv(screen_win,SCREEN_PROPERTY_DISPLAY,(void**)&(screen_dlist[3]));
    int usage = SCREEN_USAGE_OPENGL_ES2;
    if (0 != screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_USAGE, &usage)) {
        cout << "screen_set_window_property_iv(SCREEN_PROPERTY_USAGE) failed" << endl;
        return -1;
    }
    
    int format = SCREEN_FORMAT_RGBX8888;
    //AVM_Int format = SCREEN_FORMAT_RGBA8888;
    if (0 != screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_FORMAT, &format)){
        cout << "screen_set_window_property_iv(SCREEN_PROPERTY_FORMAT) failed" << endl;
        return -1;
    }

    int winsize[2] = {1280, 720};
    if (0 != screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_SIZE, winsize)) 
    {
        cout << "screen_set_window_property_iv(SCREEN_PROPERTY_SIZE) failed" << endl;
        return -1;
    }

    int winpos[2] = {0, 0};
    if (0 != screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_POSITION, winpos))
    {
        cout << "screen_set_window_property_iv(SCREEN_PROPERTY_POSITION) failed" << endl;
        return -1;
    }

    int interval = 1;
    if (0 != screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_SWAP_INTERVAL, &interval))
    {
        cout << "screen_set_window_property_iv(SCREEN_PROPERTY_SWAP_INTERVAL) failed" << endl;
        return -1;
    }

    int layer = 1000;
    if(0 != screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_ZORDER, &layer))
    {
        cout << "screen_set_window_property_iv(SCREEN_PROPERTY_ZORDER) failed" << endl;
        return -1;
    }

    int windowSensitivity = (SCREEN_SENSITIVITY_MASK_STOP);
    if(0 != screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_SENSITIVITY, &windowSensitivity))
    {
        cout << "screen_set_window_property_iv(SCREEN_PROPERTY_SENSITIVITY) failed" << endl;
        return -1;
    }
    //Create buffer(s) for your render target.
    int nbuffers = 2;
    if (0 != screen_create_window_buffers(screen_win, nbuffers)) 
    {
        cout << "screen_create_window_buffers failed" << endl;
        return -1;
    }
    int visible = true;
    screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_VISIBLE, &visible);
    //Render to your target.
    while (1) 
    {
        //处理触摸事件
        screen_event_t  mEvent;
        static const int event_time_out = 8000;
        int val = 0;
        while (!screen_get_event(screen_ctx, mEvent, event_time_out)) 
        {
            (void)screen_get_event_property_iv(mEvent, SCREEN_PROPERTY_TYPE, &val);

            if (SCREEN_EVENT_NONE == val) 
            {
                cout << "none event" << endl;
                break;
            }

            switch (val) 
            {
                case SCREEN_EVENT_CREATE:
                    {
                        cout << "SCREEN_EVENT_CREATE" << endl;
                    }
                    break;
                case SCREEN_EVENT_CLOSE:
                    {
                        cout << "SCREEN_EVENT_CLOSE" << endl;
                    }
                    break;
                case SCREEN_EVENT_MTOUCH_MOVE:
                case SCREEN_EVENT_MTOUCH_PRETOUCH:
                case SCREEN_EVENT_MTOUCH_RELEASE:
                case SCREEN_EVENT_MTOUCH_TOUCH:
                    {
                        cout << "SCREEN_EVENT_MTOUCH_XXX TODO" << endl;
                    }
                    break;
                case SCREEN_EVENT_POINTER: // mouse event
                {
                    int val_h, val_v;
                    int btns = 0;
                    int pos[2] = {0, 0};
                    (void)screen_get_event_property_iv(mEvent, SCREEN_PROPERTY_MOUSE_HORIZONTAL_WHEEL, &val_h);
                    (void)screen_get_event_property_iv(mEvent, SCREEN_PROPERTY_MOUSE_WHEEL, &val_v);
                    (void)(void)screen_get_event_property_iv(mEvent, SCREEN_PROPERTY_BUTTONS, &btns);
                    (void)screen_get_event_property_iv(mEvent, SCREEN_PROPERTY_POSITION, pos);
                    static bool s_btn_down = false;
                    if (btns & SCREEN_LEFT_MOUSE_BUTTON) 
                    {
                        if (!s_btn_down) 
                        {
                            s_btn_down = true;
                            cout << "SCREEN_EVENT_POINTER: val_h:" << val_h << ", val_v:"<<val_v << "btn:" << btns << "pos:" << pos[0] << ","<< pos[1];
                            //mDownEvent(pos[0], pos[1]);

                        }
                        else 
                        {
                            cout << "SCREEN_EVENT_POINTER: val_h:" << val_h << ", val_v:"<<val_v << "btn:" << btns << "pos:" << pos[0] << ","<< pos[1];
                            //mMoveEvent(pos[0], pos[1]);
                        }
                    }
                    else 
                    {
                        if (s_btn_down) 
                        {
                            s_btn_down = false;
                            cout << "SCREEN_EVENT_POINTER: val_h:" << val_h << ", val_v:"<<val_v << "btn:" << btns << "pos:" << pos[0] << ","<< pos[1];
                            //mUpEvent(pos[0], pos[1]);
                        }
                    }
                }
                break;
                case SCREEN_EVENT_KEYBOARD:
                    {
                        cout << "SCREEN_EVENT_KEYBOARD: " << endl;
                    }
                    break;
                default:
                    break;
            }
        }

        //Post your image.
        screen_buffer_t screen_buf[2];
        screen_get_window_property_pv(screen_win, SCREEN_PROPERTY_RENDER_BUFFERS, (void **)screen_buf);
        unsigned int win_background[] = { SCREEN_BLIT_COLOR, 0xffffff00, SCREEN_BLIT_END };
        screen_fill(screen_ctx, screen_buf[0], (const int*)win_background);
        screen_post_window(screen_win, screen_buf[0], 0, NULL, 0);
     }
    //Post your image.
    //Handle Screen events.
    

    cout << "Hello, QNX!" << endl;
    return 0;
}