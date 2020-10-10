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
    SDL_Point playerPos{position_m.x + 200, position_m.y + 740};
    SDL_Point ballPos{playerPos.x, playerPos.y - 100};
    int playerSpeed{8}, ballSpeed{10};
    int playerHp{3};
    
    renderer_m = assetManager_m->getRenderer();
    font_m = assetManager_m->getFont();
    
    // Game Objects !
    SDL_Texture* pTexture = nullptr;
    
    pTexture = assetManager_m->getTexture("defaultPlayer");    
    player_m = new Player(playerPos, playerSpeed, playerHp, pTexture);

    pTexture = assetManager_m->getTexture("defaultBall");
    ball_m = new Ball(ballPos, ballSpeed, pTexture);

    SDL_FPoint wallHorizontalScale{windowW / 640.0f, 1};
    SDL_FPoint wallVerticalScale{1, windowH / 640.0f};
    pTexture = assetManager_m->getTexture("defaultWallV");
    walls_m[0] = new Wall{SDL_Point{position_m.x -25, 0}, pTexture, wallVerticalScale, "wallW"};
    walls_m[1] = new Wall{SDL_Point{windowW, 0}, pTexture, wallVerticalScale, "wallE"};
    pTexture = assetManager_m->getTexture("defaultWallH");
    walls_m[2] = new Wall{SDL_Point{0, -25}, pTexture, wallHorizontalScale, "wallN"};
    walls_m[3] = new Wall{SDL_Point{0, windowH}, pTexture, wallHorizontalScale, "wallS"};
    
    // spawn bricks !
    // TODO: Znati dimenzije brick-a ? -> SDL_Point brDim{}
    float levelBrickAreaWidth = windowW - position_m.x;
    float levelBrickAreaHeight = windowH * 0.8f;
    
    float brickWidth = (levelBrickAreaWidth - (columnCount_m - 1) * (columnSpacing_m / 20) )
                      / columnCount_m;
    float brickHeight = (levelBrickAreaHeight - (rowCount_m - 1) * (rowSpacing_m / 20) ) / rowCount_m;
    
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
    SDL_Point guiLevelNamePos{10, 230};
    SDL_Point guiScorePos{10, 30};
    SDL_Point guiLivesPos{10, 100};
    SDL_Point guiStatusPos{windowW*0.5, windowH*0.5};
    // TTF_SizeText(ttf, "Hello World", &w, &h); // Za nove retke .
    guiLevelName_m = new Text(renderer_m, font_m, guiLevelNamePos, "Level Name !");
    guiScore_m = new Text(renderer_m, font_m, guiScorePos, player_m->score());
    guiLives_m = new Text(renderer_m, font_m, guiLivesPos, player_m->lives());
    guiPaused_m = new Text(renderer_m, font_m, guiStatusPos, "Game Paused!");
    guiDefeat_m = new Text(renderer_m, font_m, guiStatusPos,
                           "You are out of lives! Thanks for playing!");
    guiVictory_m = new Text(renderer_m, font_m, guiStatusPos, "You won the level !");
}
Level::~Level() {
    delete player_m;
    delete ball_m;
    for(auto& b : bricks_m) delete b;
    for(auto& w : walls_m) delete w;
    delete guiLevelName_m;
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
            guiScore_m->text(player_m->score(), renderer_m, font_m);
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
    guiLevelName_m->render(renderer_m);
    guiScore_m->render(renderer_m);
    guiLives_m->render(renderer_m);
    if (defeat_m) guiDefeat_m->render(renderer_m);
    else if (victory_m) guiVictory_m->render(renderer_m);
    else if (paused_m) guiPaused_m->render(renderer_m);
}
void Level::reset() {
    // Ovo se zove na gubitku života !
    ball_m->reset();
    player_m->reset();
    guiLives_m->text(player_m->lives(), renderer_m, font_m);
    if (player_m->outOfLives()) { defeat_m = true; pause(); }
    // Cigle ne resetiram na gubitku života !
    // Score ne resetiram na gubitku života !
}
void Level::pause() {
    if (defeat_m || victory_m) { paused_m = true; return; }
    paused_m = !paused_m;
}
