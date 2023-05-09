#include "MainObject.h"

MainObject::MainObject()
{
    frame = 0;
    width_frame = WIDTH_MAIN_OBJECT;
    height_frame = HEIGHT_MAIN_OBJECT;
    xpos = (SCREEN_WIDTH - WIDTH_MAIN_OBJECT)/2;
    ypos = SCREEN_HEIGHT - HEIGHT_MAIN_OBJECT;
    x_val = 0;
    y_val = 0;
    bullet_type = round_bullet;
    status = CENTER;
    isDead = false;
    isDelete = false;
    exp_frame = 0;
}

MainObject::~MainObject()
{}

void MainObject::Show(SDL_Renderer* screen)
{
    Free();
//    if(isDead){
//        loadIMG("IMG/exp11.png",screen);
//        SDL_Rect tmp = {exp_frame * (GetRect().w / 10), 0, GetRect().w / 10, GetRect().h};
//        Render(screen, xpos-5, ypos - 10, &tmp);
//        exp_frame++;
//        if(exp_frame > 10) isDelete = true;
//    }
    //else{
        if(status == CENTER)
            loadIMG("IMG/player.png", screen);
        else if(status == LEFT)
            loadIMG("IMG/player_left.png", screen);
        else
            loadIMG("IMG/player_right.png", screen);

        rect_.x = xpos;
        rect_.y = ypos;

        SDL_Rect clip = {frame * (GetRect().w / MAIN_FRAME), 0, GetRect().w/MAIN_FRAME, GetRect().h};
        SDL_Rect destR = {rect_.x, rect_.y, rect_.w/MAIN_FRAME, rect_.h};
        SDL_RenderCopy(screen, object, &clip, &destR);
        frame++;
        if(frame >= MAIN_FRAME) frame = 0;
    //}
}

SDL_Rect MainObject::getRect()
{
    SDL_Rect m_rect;
    m_rect.x = xpos;
    m_rect.y = ypos;
    m_rect.w = GetRect().w / MAIN_FRAME;
    m_rect.h = GetRect().h;
    return m_rect;
}

void MainObject::HandleInput(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* g_gun, bool& playMusic)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            status = RIGHT;
            break;
        case SDLK_LEFT:
            status = LEFT;
            break;
        case SDLK_UP:
            status = CENTER;
            break;
        default:
            break;
        }
    }

    if(events.type == SDL_MOUSEMOTION){
        int xm, ym;
        SDL_GetMouseState(&xm, &ym);
        xpos = xm;
        ypos = ym;
    }

    if(events.type == SDL_MOUSEBUTTONDOWN)
    {
        if(events.button.button == SDL_BUTTON_LEFT)
        {
            Bullet* p_bullet = new Bullet();
            if(bullet_type == round_bullet)
                p_bullet->loadIMG("IMG/Main_Bullet.png", screen);
            else if(bullet_type == laze_bullet)
                p_bullet->loadIMG("IMG/laze_bullet.png", screen);
            if(playMusic) Mix_PlayChannel(-1, g_gun, 0);
            if(status == CENTER){
                p_bullet->setX (this->rect_.x + rect_.w/(2*MAIN_FRAME));
                p_bullet->setY (this->rect_.y);
                p_bullet->set_x_val(0);
;               p_bullet->set_y_val(-MAIN_BULLET_SPEED);

            }
            else if(status == LEFT){
                p_bullet->setX (this->rect_.x);
                p_bullet->setY (this->rect_.y);
                p_bullet->set_x_val(-10);
                p_bullet->set_y_val(-MAIN_BULLET_SPEED);
            }
            else{
                p_bullet->setX (this->rect_.x + rect_.w/MAIN_FRAME);
                p_bullet->setY (this->rect_.y);
                p_bullet->set_x_val(10);
                p_bullet->set_y_val(-MAIN_BULLET_SPEED);
            }
            p_bullet->set_is_move(true);
            p_bullet_list.push_back(p_bullet);
        }
    }
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
    for(int i = 0; i < p_bullet_list.size(); i++)
    {
        Bullet* p_bullet = p_bullet_list.at(i);
        if(p_bullet != nullptr)
        {
            if(p_bullet->get_is_move())
            {
                p_bullet->HandleMove();
                p_bullet->Render(des, p_bullet->getX(), p_bullet->getY(), NULL);
            }
            else
            {
                p_bullet_list.erase(p_bullet_list.begin()+i);
                if(p_bullet != nullptr)
                {
                    delete p_bullet;
                    p_bullet = nullptr;
                }
            }
        }
    }
}

void MainObject::Check()
{
    xpos += x_val;
    ypos += y_val;

    if(xpos < 0)
    {
        xpos = 0;
    }
    else if(xpos + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
    {
        xpos = SCREEN_WIDTH - WIDTH_MAIN_OBJECT;
    }

    if(ypos < 0)
    {
        ypos = 0;
    }
    else if(ypos > SCREEN_HEIGHT - HEIGHT_MAIN_OBJECT){
        ypos = SCREEN_HEIGHT - HEIGHT_MAIN_OBJECT;
    }
}

void MainObject::ChecktoEnemy(vector<Enemy*>& enemy, Heart& heart, Mix_Chunk* sound, bool& playMusic)
{
    if(!isDead){
    SDL_Rect pRect = getRect();
    for(int i = 0; i < enemy.size(); i++)
    {
        Enemy* threat = enemy.at(i);
        if(threat != nullptr)
        {
            SDL_Rect tRect = threat->getRect();
            bool check_1 = CheckCollision(tRect, pRect);
            if(check_1)
            {
                if(playMusic)  Mix_PlayChannel(-1, sound, 0);
                enemy.erase(enemy.begin()+i);
                threat->Free();
                heart.Decrease();
                cout << "enemy" << endl;
                cout << tRect.x << ' ' << tRect.y << ' ' << tRect.w  << ' ' << tRect.h << endl;
                cout << pRect.x << ' ' << pRect.y << ' ' << pRect.w  << ' ' << pRect.h << endl;
                if(heart.getHeart() == 0){
                    isDead = true;
                    break;
                }
            }
        }
        vector <Bullet*> e_bullet = threat->get_bullet_list();
        for(int eb = 0; eb < e_bullet.size(); eb++)
        {
            Bullet* ebullet = e_bullet.at(eb);
            SDL_Rect ebRect;
            ebRect = ebullet->getRect();
            bool check_2= CheckCollision(ebRect, pRect);
            if(check_2)
            {
                if(playMusic){
                    Mix_PlayChannel(-1, sound, 0);
                }
                threat->ResetBullet(eb);
                heart.Decrease();
                cout << "bullet" << endl;
                if(heart.getHeart() == 0){
                    isDead = true;
                    break;
                }
            }
        }
    }
    }
}

void MainObject::ChecktoBoss(vector<Boss*>& boss, Heart& heart, Mix_Chunk* sound, bool& playMusic)
{
    SDL_Rect pRect = getRect();
    for(int i = 0; i < boss.size(); i++)
    {
        Boss* boss_ = boss.at(i);
        if(boss_ != nullptr)
        {
            SDL_Rect tRect = boss_->getRect();
            bool check_1 = CheckCollision(pRect, tRect);
            if(check_1)
            {
                if(playMusic)  Mix_PlayChannel(-1, sound, 0);
                boss.erase(boss.begin()+i);
                boss_->Free();
                heart.Decrease();
                cout << 1 << endl;
                if(heart.getHeart() == 0){
                    isDead = true;
                    break;
                }
            }
        }
        vector <Bullet*> b_bullet = boss_->get_bullet_list();
        for(int b = 0; b < b_bullet.size(); b++)
        {
            Bullet* bullet = b_bullet.at(b);
            SDL_Rect bRect;
            bRect = bullet->getRect();
            bool check_2= CheckCollision(bRect, pRect);
            if(check_2)
            {
                if(playMusic){
                    Mix_PlayChannel(-1, sound, 0);
                }
                boss_->ResetBullet(b);
                heart.Decrease();
                if(heart.getHeart() == 0){
                    isDead = true;
                    break;
                }
            }
        }
    }
}


void MainObject::RemoveBullet(const int idx)
{
    int size = p_bullet_list.size();
    if(size > 0 && idx < size)
    {
        Bullet* p_bullet = p_bullet_list.at(idx);
        p_bullet_list.erase(p_bullet_list.begin()+idx);
        if(p_bullet)
        {
            delete p_bullet;
            p_bullet = nullptr;
        }
    }
}

void MainObject::CheckSupport(vector<Support*> sp, Heart& heart,
                              Mix_Chunk* sound, bool& play_music)
{
    SDL_Rect pRect = getRect();
    for(int i = 0; i < sp.size(); i++)
    {
        SDL_Rect sRect = sp[i]->getRect();
        if(sp[i]->get_type() == bullet_change)
        {
            if(CheckCollision(pRect, sRect))
            {
                if(play_music)
                    Mix_PlayChannel(-1, sound, 0);
                sp[i]->Free();
                sp.erase(sp.begin()+i);
                bullet_type = laze_bullet;
            }
        }
        else if(sp[i]->get_type() == heart_plus)
        {
            if(CheckCollision(pRect, sRect))
            {
                if(play_music)
                    Mix_PlayChannel(-1, sound, 0);
                sp[i]->Free();
                sp.erase(sp.begin()+i);
                heart.Increase();
            }
        }
    }
}




