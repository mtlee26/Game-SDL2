#include "Game_Utils.h"

void RenderBackground(double& offsetSpeed, BaseObject& Background, SDL_Renderer* renderer)
{
    offsetSpeed += 2;
    if(offsetSpeed > Background.getHeight()){
        offsetSpeed = 0;
    }
    Background.Render(renderer, 0, offsetSpeed, NULL);
    Background.Render(renderer, 0, offsetSpeed - Background.getHeight(), NULL);
}


void CreateEnemy(vector<Enemy*>& enemy, SDL_Renderer* screen)
{
    int random = rand() % 30;
    if(random == 1){
        Enemy* enemy_ = new Enemy(rand()%2);
        Bullet* e_bullet = new Bullet();
        enemy_->InitEnemyBullet(e_bullet, screen);
        enemy.push_back(enemy_);
    }
}

void CheckEnemy(SDL_Renderer* screen, MainObject& player, vector<Enemy*>& enemy, Mix_Chunk* sound, bool& play_music, int& player_score)
{
    vector<Bullet*> p_bullet = player.get_bullet_list();
    for(int b = 0; b < p_bullet.size(); b++)
    {
        Bullet* pbullet = p_bullet.at(b);
        if(pbullet != nullptr)
        {
            SDL_Rect bRect;
            bRect = pbullet->getRect();
            for(int e = 0; e < enemy.size(); e++)
            {
                Enemy* enemy_ = enemy.at(e);
                if(enemy_ != nullptr)
                {
                    SDL_Rect tRect;
                    tRect = enemy_->getRect();
                    if(CheckCollision(tRect, bRect))
                    {
                        if(play_music)
                            Mix_PlayChannel(-1, sound, 0);
                        if(player.get_bullet_type() == round_bullet){
                            enemy_->decrease_health();
                        }
                        else if(player.get_bullet_type() == laze_bullet){
                            enemy_->decrease_health();
                            enemy_->decrease_health();
                        }
                        player.RemoveBullet(b);
                        if(enemy_->is_dead()){
                            if(enemy_->get_type() == RED_ENEMY) player_score += 10;
                            else if(enemy_->get_type() == GREEN_ENEMY) player_score += 20;
                            enemy.erase(enemy.begin() + e);
                            enemy_->Free();
                        }
                    }
                }
            }
        }
    }
}

void CheckBoss(SDL_Renderer* screen, MainObject& player, vector<Boss*>& boss, Mix_Chunk* sound, bool& play_music, int& player_score)
{
    vector<Bullet*> p_bullet = player.get_bullet_list();
    for(int b = 0; b < p_bullet.size(); b++)
    {
        Bullet* pbullet = p_bullet.at(b);
        if(pbullet != nullptr)
        {
            SDL_Rect bRect;
            bRect = pbullet->getRect();
            for(int e = 0; e < boss.size(); e++)
            {
                Boss* boss_ = boss.at(e);
                if(boss_ != nullptr && !boss_->is_dead())
                {
                    SDL_Rect tRect;
                    tRect = boss_->getRect();
                    if(CheckCollision(tRect, bRect))
                    {
                        if(play_music)
                            Mix_PlayChannel(-1, sound, 0);
                        if(player.get_bullet_type() == round_bullet){
                            boss_->decrease_health();
                        }
                        else if(player.get_bullet_type() == laze_bullet){
                            boss_->decrease_health();
                            boss_->decrease_health();
                        }
                        player.RemoveBullet(b);
                        if(boss_->is_dead()){
                            player_score += 50;
                            boss_->set_isDead(true);
                        }
                    }
                }
            }
        }
    }
}

Game::Game()
{
    is_quit = false;
    is_play = false;
    is_quit_menu = false;
    play_music = true;
    is_paused = false;

}

Game::~Game()
{
    menu.Free();
    help.Free();
    playButton.Free();
    helpButton.Free();
    backButton.Free();
    exitButton.Free();
    PlayAgain.Free();
    Exit.Free();

}

void Game::Init(SDL_Renderer* screen)
{
    PlayButton.setRect(PLAY_XPOS, PLAY_YPOS, BUTTON_WIDTH, BUTTON_HEIGHT);
    HelpButton.setRect(HELP_XPOS, HELP_YPOS, BUTTON_WIDTH, BUTTON_HEIGHT);
    BackButton.setRect(BACK_XPOS, BACK_YPOS, BACK_BUTTON_WIDTH, BACK_BUTTON_HEIGHT);
    ExitButton.setRect(EXIT_XPOS1, EXIT_YPOS1, BUTTON_WIDTH, BUTTON_HEIGHT);

    ButtonClip[0].x = 0;
    ButtonClip[0].y = 0;
    ButtonClip[0].w = BUTTON_WIDTH;
    ButtonClip[0].h = BUTTON_HEIGHT;

    ButtonClip[1].x = BUTTON_WIDTH;
    ButtonClip[1].y = 0;
    ButtonClip[1].w = BUTTON_WIDTH;
    ButtonClip[1].h = BUTTON_HEIGHT;

    BackButtonClip[0].x = 0;
    BackButtonClip[0].y = 0;
    BackButtonClip[0].w = BACK_BUTTON_WIDTH;
    BackButtonClip[0].h = BACK_BUTTON_HEIGHT;

    BackButtonClip[1].x = BACK_BUTTON_WIDTH;
    BackButtonClip[1].y = 0;
    BackButtonClip[1].w = BACK_BUTTON_WIDTH;
    BackButtonClip[1].h = BACK_BUTTON_HEIGHT;

    menu.loadIMG("IMG/Menu/menu.png", screen);
    help.loadIMG("IMG/Menu/instruction.png", screen);
    playButton.loadIMG("IMG/Menu/play1.png", screen);
    helpButton.loadIMG("IMG/Menu/help1.png", screen);
    backButton.loadIMG("IMG/Menu/back.png", screen);
    exitButton.loadIMG("IMG/Menu/exit1.png", screen);
    pause.loadIMG("IMG/Menu/pause.png", screen);

}

void Game::handlePlayButton(SDL_Event e, Mix_Chunk* click)
{
    if(e.type == SDL_QUIT)
    {
        is_quit_menu = true;
    }
    if(PlayButton.isInside(e))
    {
        switch(e.type)
        {
        case SDL_MOUSEMOTION:
            PlayButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            Mix_PlayChannel(-1, click, 0);
            is_play = true;
            is_quit_menu = true;
            PlayButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        }
    }
    else{
        PlayButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}

void Game::handleHelpButton(SDL_Renderer* screen, SDL_Event e, Mix_Chunk* click)
{
    if(HelpButton.isInside(e))
    {
        switch(e.type)
        {
        case SDL_MOUSEMOTION:
            HelpButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            Mix_PlayChannel(-1, click, 0);
            HelpButton.currentSprite = BUTTON_MOUSE_OVER;
            bool is_back = false;
            while(!is_back)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        is_back = true;
                        is_quit_menu = true;
                        break;
                    }
                    else if(BackButton.isInside(e))
                    {
                        switch(e.type)
                        {
                        case SDL_MOUSEMOTION:
                            BackButton.currentSprite = BUTTON_MOUSE_OVER;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            Mix_PlayChannel(-1, click, 0);
                            BackButton.currentSprite = BUTTON_MOUSE_OVER;
                            is_back = true;
                            break;
                        }
                    }
                    else{
                        BackButton.currentSprite = BUTTON_MOUSE_OUT;
                    }
                }
                help.Render(screen, 0, 0, NULL);
                SDL_Rect* clip = &BackButtonClip[BackButton.currentSprite];
                backButton.Render(screen, BACK_XPOS, BACK_YPOS, clip);
                SDL_RenderPresent(screen);
            }
            break;
        }
    }
    else{
        HelpButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}

void Game::handlePlayAgain(SDL_Event e, Mix_Chunk* click)
{
    if(PlayAgain.isInside(e))
    {
        switch(e.type)
        {
        case SDL_MOUSEMOTION:
            PlayAgain.set_color(Text::RED_TEXT);
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_play = true;
            is_quit = false;
            is_quit_menu = true;
            Mix_PlayChannel(-1, click, 0);
            PlayAgain.set_color(Text::RED_TEXT);
            break;
        }
    }
    else{
        PlayAgain.set_color(Text::WHITE_TEXT);
    }
}


void Game::handleExitButton(SDL_Event e, Mix_Chunk* click)
{
    if(ExitButton.isInside(e))
    {
        switch(e.type)
        {
        case SDL_MOUSEMOTION:
            ExitButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            Mix_PlayChannel(-1, click, 0);
            SDL_Delay(100);
            is_quit = true;
            is_play = false;
            is_quit_menu = true;
            ExitButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        }
    }
    else{
        ExitButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}

void Game::handleExit(SDL_Event e, Mix_Chunk* click)
{
    if(Exit.isInside(e))
    {
        switch(e.type)
        {
        case SDL_MOUSEMOTION:
            Exit.set_color(Text::RED_TEXT);
            break;
        case SDL_MOUSEBUTTONDOWN:
            Mix_PlayChannel(-1, click, 0);
            Exit.set_color(Text::RED_TEXT);
            //SDL_Delay(100);
            is_quit = true;
            is_play = false;
            break;
        }
    }
    else{
        Exit.set_color(Text::WHITE_TEXT);
    }
}


void Game::HandleEvent(SDL_Renderer* screen, SDL_Event e, Mix_Chunk* click)
{
    handlePlayButton(e, click);
    handleHelpButton(screen, e, click);
    handleExitButton(e, click);
}

void Game::RenderMenu(SDL_Renderer* screen)
{
    menu.Render(screen, 0, 0, NULL);

    SDL_Rect* play_clip = &ButtonClip[PlayButton.currentSprite];
    playButton.Render(screen, PLAY_XPOS, PLAY_YPOS, play_clip);

    SDL_Rect* help_clip = &ButtonClip[HelpButton.currentSprite];
    helpButton.Render(screen, HELP_XPOS, HELP_YPOS, help_clip);

    SDL_Rect* exit_clip = &ButtonClip[ExitButton.currentSprite];
    exitButton.Render(screen, EXIT_XPOS1, EXIT_YPOS1, exit_clip);

    SDL_RenderPresent(screen);
}

void Game::handlePause(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
            if(Mix_PausedMusic() == 1) Mix_ResumeMusic();
            else{
                Mix_PauseMusic();
                //play_music = false;
            }
            break;
        default:
            break;
        }
    }
    else if(e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
            is_paused = ! is_paused;
            break;
        default:
            break;
        }
    }
    if(is_paused) play_music = false;
    else play_music = true;

}

void Game::RenderPause(SDL_Renderer* screen)
{
    if(is_paused){
        pause.Render(screen, 160, 200, NULL);
        SDL_RenderPresent(screen);
    }
}

string Game::GetHighScoreFromFile(string path)
{
	ifstream ifs;
	string highscore;

	ifs.open(path);
	if(ifs.is_open()){
        ifs >> highscore;
        return highscore;
	}
}

void Game::UpdateHighScore(string path, const int& score)
{
    string HighScore = GetHighScoreFromFile(path);
    int high_score = stoi(HighScore);

    ofstream ofs;
    ofs.open(path, std::ios::out);
    if(score > high_score){
        high_score = score;
    }
    string newHighScore = to_string(high_score);
    ofs << newHighScore;
}

void Game::handleEndGame(SDL_Renderer* screen, SDL_Event e, Mix_Chunk* click, TTF_Font* font, const int& player_score)
{
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            is_play = false;
            is_quit = true;
            break;
        }
        handlePlayAgain(e, click);
        handleExit(e, click);
    }

    PlayAgain.set_text("PLAY AGAIN");
    PlayAgain.SetRect(PLAYAGAIN_XPOS, PLAYAGAIN_YPOS);
    PlayAgain.loadFromRenderedText(font, screen);
    PlayAgain.Show(screen);

    Exit.set_text("EXIT");
    Exit.SetRect(EXIT_XPOS2, EXIT_YPOS2);
    Exit.loadFromRenderedText(font, screen);
    Exit.Show(screen);

    SDL_RenderPresent(screen);
}

void Game::FreeMenu()
{
    menu.Free();
    help.Free();
    playButton.Free();
    helpButton.Free();
    backButton.Free();
    exitButton.Free();
}










