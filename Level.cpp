#include "Level.hpp"

Level::Level(const SDL_Point pos, const int windowW, const int windowH,
             const int rC, const int cC, const int rS, const int cS,
             AssetManager* aManager, SDL_Texture* texture,
             const BrickFactory& brickFactory,
             std::vector<std::string> bricksLayout, SDL_FPoint scale)

    :   position_m{pos}, rowCount_m{rC}, columnCount_m{cC},
        rowSpacing_m{rS}, columnSpacing_m{cS}, bricksDestroyed_m{0},
        paused_m{false}, victory_m{false}, defeat_m{false},
        assetManager_m{aManager}, sprite_m{texture, scale},
        bricksLayout_m{bricksLayout}
{
    std::cout << "[Level] Constructor entered with following values:\n";
    std::cout << "\tpos.x/y = " << pos.x << "/" << pos.y << "\n";
    std::cout << "\twindow.w/h = " << windowW << "/" << windowH << "\n";
    std::cout << "\trowCount = " << rC << "\n";
    std::cout << "\tcolumnCount = " << cC << "\n";
    std::cout << "\trowSpacing = " << rS << "\n";
    std::cout << "\tcolumnSpacing = " << cS << "\n";
    if (aManager != nullptr) std::cout << "\taManager != nullptr\n";
    else std::cout << "\taManager == nullptr\n";
    if (texture != nullptr) std::cout << "\ttexture != nullptr\n";
    else std::cout << "\ttexture == nullptr\n";
    std::cout << "\tscale.x/y = " << scale.x << "/" << scale.y << "\n";
    std::cout << "\tbricksLayout.size() = " << bricksLayout.size() << "\n";
    
    // Game Objects !
    
    float brickAreaWidth = windowW - position_m.x;
    float brickAreaHeight = windowH * 0.8f;
    
    SDL_Point playerPos;
    playerPos.x = position_m.x + brickAreaWidth*0.45f;
    playerPos.y = windowH - 25;
    SDL_Point ballPos{playerPos.x + 30, playerPos.y - 25};
    int playerSpeed{8}, ballSpeed{10};
    int playerHp{3};
    
    renderer_m = assetManager_m->getRenderer();
    font_m = assetManager_m->getFont();
    
    SDL_Texture* pTexture = nullptr;
    
    pTexture = assetManager_m->getTexture("defaultPlayer");    
    player_m = new Player(playerPos, playerSpeed, playerHp, pTexture);

    pTexture = assetManager_m->getTexture("defaultBall");
    ball_m = new Ball(ballPos, ballSpeed, pTexture);

    SDL_FPoint wallHorizontalScale{windowW / 640.0f, 1};
    SDL_FPoint wallVerticalScale{1, windowH / 640.0f};
    pTexture = assetManager_m->getTexture("defaultWallV");
    walls_m[0] = new Wall{SDL_Point{position_m.x - 25, position_m.y},
                          pTexture, wallVerticalScale, "wallW"};
    walls_m[1] = new Wall{SDL_Point{windowW, position_m.y}, pTexture, wallVerticalScale, "wallE"};
    pTexture = assetManager_m->getTexture("defaultWallH");
    walls_m[2] = new Wall{SDL_Point{0, -25}, pTexture, wallHorizontalScale, "wallN"};
    walls_m[3] = new Wall{SDL_Point{0, windowH}, pTexture, wallHorizontalScale, "wallS"};
        
    float brickWidth = ( brickAreaWidth - (columnCount_m-1)*(columnSpacing_m/20) ) / columnCount_m;
    float brickHeight = ( brickAreaHeight - (rowCount_m-1)*(rowSpacing_m/20) ) / rowCount_m;
    
    SDL_FPoint brickScale{brickWidth / 20, brickHeight / 20};
    
    for (int i = 0; i < rowCount_m; i++)
        for (int j = 0; j < columnCount_m; j++) {
            SDL_Point spacing{columnSpacing_m / 20, rowSpacing_m / 20};
            if (i == 0 || i == rC) spacing.y = 0;
            if (j == 0 || j == cC) spacing.x = 0;
            
            SDL_Point brickPos{ position_m.x + j*brickWidth + j*spacing.x,
                                position_m.y + i*brickHeight + i*spacing.y };
            
            int currentIndex = i*columnCount_m + j;
            if (currentIndex >= bricksLayout_m.size()) break;
            std::string id = bricksLayout_m.at( i*columnCount_m + j );

            bricks_m.push_back( brickFactory.spawnBrickFromTemplate(id, brickPos, brickScale) );
            //bricks_m.push_back( new Brick{brPos, 1, pTexture, brScale} );
    }
    
    // GUI !
    SDL_Point guiScorePos{10, 30};
    SDL_Point guiLivesPos{10, 100};
    SDL_Rect guiStatusBannerRect;
    guiStatusBannerRect.x = position_m.x;
    guiStatusBannerRect.y = windowH * 0.5f;
    guiStatusBannerRect.w = brickAreaWidth;
    guiStatusBannerRect.h = 200;

    guiScore_m = new Text(renderer_m, font_m, guiScorePos);
    guiScore_m->text(player_m->score());
    guiLives_m = new Text(renderer_m, font_m, guiLivesPos);
    guiLives_m->text(player_m->lives());
    guiPaused_m = new Banner(renderer_m, font_m, guiStatusBannerRect);
    guiPaused_m->text("Press P to unpause!");
    guiDefeat_m = new Banner(renderer_m, font_m, guiStatusBannerRect);
    guiDefeat_m->text("You are out of lives! Thanks for playing!");
    guiVictory_m = new Banner(renderer_m, font_m, guiStatusBannerRect);
    guiVictory_m->text("You won the level !");
}
Level::~Level() {
    delete player_m;
    delete ball_m;
    for(auto& b : bricks_m) delete b;
    for(auto& w : walls_m) delete w;
    delete guiScore_m;
    delete guiLives_m;
    delete guiPaused_m;
    delete guiDefeat_m;
    delete guiVictory_m;
}

void Level::update() {
    // Prvo ažuriramo objekte.
    if (paused_m) return;

    player_m->update();
    ball_m->update();
    for (auto& b : bricks_m) b->update();
    for (auto& w : walls_m) w->update();
    
    // Zatim radim 'collision detection'
    const CircleCollider& ballCollider{ball_m->collider()};
    const RectCollider& playerCollider{player_m->collider()};

    for (auto& w : walls_m) {
        const CollisionInformation infoB{ ballCollider.isColliding(w->collider()) };
        if (infoB.isColliding) {
            ball_m->onHit(infoB);
            if (infoB.collidedWith == "wallS") reset();
        }
        const CollisionInformation infoP{ playerCollider.isColliding(w->collider()) };
        if (infoP.isColliding) {
            player_m->onHit(infoP);
        }
    }
    for (auto& b : bricks_m) {
        const CollisionInformation info{ ballCollider.isColliding(b->collider()) };
        if (info.isColliding) {
            ball_m->onHit(info);
            player_m->addScore(b->onHit());
            ++bricksDestroyed_m;
            guiScore_m->text(player_m->score());
        }
    }
    const CollisionInformation info{ ballCollider.isColliding(playerCollider) };
    if (info.isColliding)
        ball_m->onHit(info);
    
    if (bricksDestroyed_m >= bricks_m.size()) { victory_m = true; pause(); }
}
void Level::render() {
    sprite_m.render(renderer_m, position_m);
    for (auto& b : bricks_m) b->render(renderer_m);
    for (auto& w : walls_m) w->render(renderer_m);
    player_m->render(renderer_m);
    ball_m->render(renderer_m);
    guiScore_m->render();
    guiLives_m->render();
    if (defeat_m) guiDefeat_m->render();
    else if (victory_m) guiVictory_m->render();
    else if (paused_m) guiPaused_m->render();
}
void Level::reset() {
    // Ovo se zove na gubitku života !
    ball_m->reset();
    player_m->reset();
    guiLives_m->text(player_m->lives());
    if (player_m->outOfLives()) defeat_m = true;
    pause();
}
void Level::pause() {
    if (levelOver()) { paused_m = true; return; }
    paused_m = !paused_m;
}
bool Level::victory() const {return victory_m;}
bool Level::levelOver() const {
    if (defeat_m || victory_m) return true;
    return false;
}
