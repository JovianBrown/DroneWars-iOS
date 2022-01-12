//
//  playstate.cpp
//  DroneWarsV3
//
//  Created by mac on 2021/12/14.
//  Copyright © 2021 Jovian. All rights reserved.
//

#include "playstate.hpp"
#include "pausestate.hpp"
#define DEAD_ZONE 3200

PlayState PlayState::m_PlayState;


void PlayState::init(SDL_Renderer* renderer,int wW, int wH)
{
    if(levelTimer==NULL)
    {
        levelTimer = new Timer;
    }
    playRenderer = renderer;
    //////// Level Stuff///////////////

    windowWidth=wW;
    windowHeight=wH;
    levelHeight= windowHeight;
    levelH = &levelHeight;
 
    virtualJoystick = new VirtualJoystick(playRenderer,windowWidth,windowHeight);
 
    ////// Audio stuff //////
    
    playMusic("actionmusicfordw.wav", SDL_MIX_MAXVOLUME/2);
    
    //////////////////Notifications below  /////
    shieldAlert.setImage("shieldalert.png", renderer);
    shieldAlert.setSource(0, 0, 400, 100);
    shieldAlert.setDestination(0, 0, 100, 25);
    
    hullAlert.setImage("hullalert.png", renderer);
    hullAlert.setSource(0, 0, 400, 100);
    hullAlert.setDestination(0, 100, 100, 25);
    
    /////////////// notifications end /////
    ////////// End Level stuff//////////

    
    ////////// Init Other Entities /////////
    asteroid.setImage("asteroidspritesheetsmall.png", playRenderer);
    asteroid.setSource(0, 0, 150, 150);
    asteroidIdle = asteroid.createCycle(8, 3, 0, 0, 150, 150, 30, true, false, false);
    asteroidExplode = asteroid.createCycle(8, 3, 0, 3, 150, 150, 10, false, false,false);
    //////////// End Init Other Entities ///////// Like asteroids ////
    hud.initHud(playRenderer, windowWidth, windowHeight);
    /////////////// Load ITEMS//////////
    energyPulse.init(playRenderer, ENERGY_PULSE);
    preciousMetal.init(playRenderer,PRECIOUS_METAL);
    rareElement.init(playRenderer, RARE_ELEMENT);

    
    ///////////////Load Items End//////////
    

    printf("PlayState Init Successful\n");
    
    /////////// Enemy stuff (testing Below)  //////////
 
 
   // updatePlayerStats();
}
void PlayState::loadLevel(int levelNumber)
{
    /// Load appropriate level file based on player's levelNumber
    int level = levelNumber;
    std::string s_level = std::to_string(level);
    std::string levelName = "level";
    std::string extension = ".txt";
    std::string line;
    std::string concatenated = levelName+s_level+extension;
    std::ifstream levelFile (concatenated);
    std::cout<<"-- "<<concatenated<<" info: "<<std::endl;
    if (levelFile.is_open())
    {
        while ( getline (levelFile,line) )
        {
            levelInfo.push_back(line);
            std::cout << line << '\n';
        }
        levelFile.close();
        

        levelTimer= new Timer;
        levelTimer->setDuration(stoi(levelInfo[0])); //entry 0 is level timer length in milliseconds
        levelTimer->setTimerActive(true);

        if(stoi(levelInfo[1])>0)   //asteroid bool yes
        {
            asteroidTimer.setDuration(stoi(levelInfo[2])); //3rd line in level file should have duration for asteroid timer
            asteroidTimer.setTimerActive(true);
            
           
        }
        
        int numberOfBgTextures = stoi(levelInfo[3]); //shuld contain number of bg textures
        int startTextureRow=4;
        int startTextureSpeedRow=startTextureRow+numberOfBgTextures;
        for(int i = 0;i<numberOfBgTextures;i++)
        {
            Background bg;
            texturePaths.push_back(levelInfo[startTextureRow+i]);
            std::cout<<"Pushed Back Background texture: "<<levelInfo[startTextureRow+i]<<std::endl;
            bg.setImage(texturePaths[i],playRenderer);
            bg.setSource(0, 0, 1024, windowHeight);
            bg.setDestination(0, 0, 1024, 1024);
            backgrounds.push_back(bg);
        }
        for(int i = 0; i<numberOfBgTextures;i++)
        {
            backgrounds[i].setSpeed(stoi(levelInfo[startTextureSpeedRow+i]));
        }
        int hasEnemyDrones = numberOfBgTextures*2+startTextureRow;
        if(stoi(levelInfo[hasEnemyDrones])>0)
        {
            /// need to init enemyDrone here
            enemyDrone = EnemyDrone();
            
            enemyDrone.init(stoi(levelInfo[hasEnemyDrones+1]), playRenderer);
        }
        

    }
    else std::cout << "Unable to open level!"<<std::endl;

    
    
}
void PlayState::spawnItem(int x, int y)
{
    cout<<"Spawned Item "<<endl;
    if(items.size()>50)
    {
        items.erase(items.begin(),items.begin()+30);

    }
    int randomItem = randomInt(0, 9);
    if(randomItem<3)
    {
        rareElement.setActive(true);
        rareElement.setDestination(x, y, 100, 100);
        items.push_back(rareElement);
    }
    if(randomItem>=3 && randomItem <= 6)
    {
        preciousMetal.setActive(true);
        preciousMetal.setDestination(x, y, 100, 100);
        items.push_back(preciousMetal);
    }
    if(randomItem>6)
    {
        energyPulse.setActive(true);
        energyPulse.setDestination(x, y, 100, 100);
        items.push_back(energyPulse);
        
    }
}
void PlayState::spawnEnemy()
{
    
}

void PlayState::spawnAsteroid()
{
    if(asteroids.size()>=100)
    {
        asteroids.erase(asteroids.begin(),asteroids.begin()+70);
        std::cout<<"cleared asteroid stack, asteroids size: "<<asteroids.size()<<std::endl;
        
    }
    int randomMass = randomInt(1, 100);
    int randomRotation = randomInt(1,180);
    int randomSpeed = randomInt(1,currentLevel+2)+3;
    int randomX = randomInt(10,windowWidth-10);;
    asteroid.setMass(randomMass);
    if(randomMass< 33 && randomMass > 0)
    {

        asteroid.setDestination(randomX, 0, 33, 33);
        asteroid.setHps(10);
        asteroid.setHasZvelocity(true);
        asteroid.setZvelocity(1);
        

    }
    if(randomMass<= 66 && randomMass>=33)
    {
        asteroid.setDestination(randomX, 0, 66, 66);
        asteroid.setHps(30);
        asteroid.setHasZvelocity(false);

    }
    if(randomMass>66 && randomMass<=100)
    {
        asteroid.setDestination(randomX, 0, 100, 100);
        asteroid.setHps(55);
        asteroid.setHasZvelocity(false);
    }
  //  randomX = randomInt(asteroid.getDestination().w,windowWidth-asteroid.getDestination().w);
    asteroid.setActive(true);
    asteroid.setRotationAngle(randomRotation);
    asteroid.setYAcc(randomSpeed);
    asteroid.setXAcc(0);

    asteroids.push_back(asteroid);
    
}
void PlayState::spawnFragment(Entity asteroid)
{
    if(asteroids.size()>=100)
    {
        asteroids.erase(asteroids.begin(),asteroids.begin()+70);
        std::cout<<"cleared asteroid stack, asteroids size: "<<asteroids.size()<<std::endl;
        
    }
    int randomMass = randomInt(1,20);
    int randomRotation = randomInt(1,180);
    int randomSpeed = (randomInt(1,10))+5;
    asteroid.setMass(randomMass);
    
    asteroid.setDestination(asteroid.getDestination().x, asteroid.getDestination().y, 10, 10);
    asteroid.setHps(5);
   
    asteroid.setActive(true);
    asteroid.setRotationAngle(randomRotation);
    asteroid.setYAcc(randomSpeed);
    asteroid.setXAcc(randomSpeed);

    asteroids.push_back(asteroid);
    
}

void PlayState::playerFire()
{
 
        playSound("fire.wav", SDL_MIX_MAXVOLUME/3);
        playersBullet.setActive(true);
        playersBullet.setDestination((player->getDestination().x+(player->getDestination().w/2)-(playersBullet.getDestination().w/2)), player->getDestination().y+(player->getDestination().h/2), playersBullet.getDestination().w, playersBullet.getDestination().h);
        playersBullets.push_back(playersBullet);
        if(playersBullets.size()>100)
        {
            playersBullets.clear();
        }
}
void PlayState::enemyFire()
{
    
    playSound("fire.wav", SDL_MIX_MAXVOLUME/3);
    
    enemysBullet.setActive(true);
    enemysBullet.setDestination((enemyDrone.getDestination().x+(enemyDrone.getDestination().w/2)-(enemysBullet.getDestination().w/2)), enemyDrone.getDestination().y+(enemyDrone.getDestination().h/2), enemysBullet.getDestination().w, enemysBullet.getDestination().h);
    enemysBullets.push_back(enemysBullet);
    if(enemysBullets.size()>100)
    {
        enemysBullets.clear();
    }
}
void PlayState::loadPlayer(Player* p) //should be called from either MenuState or DockState
{
   // Loadgame loadGame;
   // std::vector<string> playerStats = loadGame.getPlayerStats();
    player = p;
    player->init(playRenderer); // loads sprite sheets for player animation
    //int totalrows, int totalcolumns,int startingrow,int startingcolumn,int w, int h, int speed, bool repeat, bool reversed, bool stopOnFinal
    playerIdle = player->createCycle(1,1,0,0,150,150,30,true,false,false); //id0
    playerReady = player->createCycle(8,3,0,0,150,150,30,false,false,true);//id1
    playerReadyReversed = player->createCycle(8,3,0,0,150,150,30,0,true,true); //id2
    playerShield = player->createCycle(8, 2, 0, 3, 150, 150, 30, false, false, false); //id3
    player->setCurrentAnimation(playerIdle);
    player->setSource(0, 0, 150, 150);
    player->setDestination(300, 700, 150, 150);
    
    loadLevel(player->getLevel());
    ////players bullet needs to use info from loadPlayer to determine what is the current weapon
     playersBullet.init(player->getCurrentWeapon(), playRenderer); //0 is for SMALL_BLUE_LASER 1 is for WIDE_BLUE_LASER
    defaultAcc = player->getDefaultAcc();
    updatePlayerStats(); //Call this at the beginning of the game once to define all the floats and stuff
    enemysBullet.init(1,playRenderer);  // 0 for small blaster 1 for bolt blaster
    
}
void PlayState::pause()
{
    printf("PlayState Paused\n");
    pauseAudio();
}

void PlayState::resume()
{
    printf("PlayState Resumed\n");
    unpauseAudio();
}

void PlayState::handleEvents(Game* game)
{
    if(virtualJoystick->getSelection()==1)
    {
        if(player->isReady())
        {
            playerFire();
          //  SDL_Delay(1);
           // virtualJoystick->setSelection(0);
        }
    }
    if(virtualJoystick->getSelection()==2)
    {
        if(!player->isReady())
        {
            player->resetAnimation();
            player->setGettingReady(true);
            player->setCurrentAnimation(playerReady);
            //virtualJoystick->setSelection(0);
            
        }
        else
        {
            player->resetAnimation();
            
            player->setCurrentAnimation(playerReadyReversed);
            //virtualJoystick->setSelection(0);
            
        }
    }
/*    if(virtualJoystick->getDirection()==1)
    {
        player->applyForce(player->getDefaultAcc(),WEST);
        
    }
    if(virtualJoystick->getDirection()==2)
    {
        player->applyForce(player->getDefaultAcc(),EAST);
        
    }
    if(virtualJoystick->getDirection()==3)
    {
        player->applyForce(player->getDefaultAcc(),NORTH);
        
    }
    if(virtualJoystick->getDirection()==4)
    {
        player->applyForce(player->getDefaultAcc(),SOUTH);
        
    } */
    if(virtualJoystick->getSelection()==3)
    {
        player->applyForce(player->getDefaultAcc(),WEST);
        
    }
    if(virtualJoystick->getSelection()==4)
    {
        player->applyForce(player->getDefaultAcc(),EAST);
        
    }
    if(virtualJoystick->getSelection()==5)
    {
        player->applyForce(player->getDefaultAcc(),NORTH);
        
    }
    if(virtualJoystick->getSelection()==6)
    {
        player->applyForce(player->getDefaultAcc(),SOUTH);
        
    }
/*    SDL_Event event;
    
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            
            case SDL_QUIT:
                game->quit();
                break;
                
    
        }
    } */
    
}
void PlayState::draw(Object &object,int rotationAngle)
{
    SDL_Rect destination = object.getDestination();
    SDL_Rect source = object.getSource();
    SDL_RenderCopyEx(playRenderer,object.getTexture(),&source,&destination,rotationAngle,NULL,SDL_FLIP_NONE);
}

void PlayState::checkBorders(Entity &object)
{
    if(object.getDestination().x>(windowWidth-object.getDestination().w))
    {
        object.setDestination(windowWidth-object.getDestination().w, object.getDestination().y, object.getDestination().w, object.getDestination().h);
        object.setXAcc(-1.0);
    }
    if(object.getDestination().y>(windowHeight-object.getDestination().h))
    {
        object.setDestination(object.getDestination().x, windowHeight-object.getDestination().h, object.getDestination().w, object.getDestination().h);
        object.setYAcc(0.0);
        
    }
    if(object.getDestination().y <= 0)
    {
        object.setDestination(object.getDestination().x, 0, object.getDestination().w, object.getDestination().h);
        object.setYAcc(1.0);
    }
    if(object.getDestination().x <= 0)
    {
        object.setDestination(0, object.getDestination().y, object.getDestination().w, object.getDestination().h);
        object.setXAcc(1.0);
        
    }
}


bool PlayState::checkCollision(SDL_Rect rectA, SDL_Rect rectB)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = rectA.x;
    rightA = rectA.x + rectA.w;
    topA = rectA.y;
    bottomA = rectA.y + rectA.h;
    
    //Calculate the sides of rect B
    leftB = rectB.x;
    rightB = rectB.x + rectB.w;
    topB = rectB.y;
    bottomB = rectB.y + rectB.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}
void PlayState::shouldUpdateHUD(bool b)
{
    updateHUD = b;
}
void PlayState::updatePlayerStats()
{
  //  std::cout<<"Updated player Stats for HUD"<<std::endl;
    hullIntegrity = ((float)player->getHps()/(float)player->getMaxHps()) * 100;
    if(hullIntegrity<0.5)
    {
        shouldDiplayHullAlert=true;
    }
  //  hI =  to_string(hullIntegrity);
  //  hullIntegrityString =const_cast<char*>(hI.c_str());
   // rareElementsString = const_cast<char*>(player->getRareElements()).c_str());
   // rareElementsString = const_cast<char*>(str.c_str());
  //  rareElementsString = std::to_string(player->getRareElements()).c_str();
  //  preciousMetalsString = std::to_string(player->getPreciousMetals()).c_str();
    
 /*   preciousMetalsString = std::to_string(player->getPreciousMetals()).c_str();
    shieldString = std::to_string(player->getShield()).c_str();
    levelString =std::to_string(player->getLevel()).c_str();
    scoreString = std::to_string(player->getScore()).c_str(); */
    shouldUpdateHUD(false);
}
void PlayState::drawBackground(Background &background)
{
    SDL_Rect destination = background.getDestination();
    SDL_Rect source = background.getSource();  //need to set this as a constant
    SDL_Rect destination2;
    destination2.h=destination.h;
    destination2.w=destination.w;
    destination2.x=destination.x;
    destination2.y=destination.y-1024;
    SDL_Rect source2 = background.getSource();
    SDL_RenderCopyEx(playRenderer,background.getTexture(),&source,&destination,0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopyEx(playRenderer,background.getTexture(),&source2,&destination2,0,NULL,SDL_FLIP_NONE);
    
}
void PlayState::update(Game* game)
{
    
    if(!game->isPaused())
    {
        levelTimer->update();
        if(!levelTimer->isActive())
        {
            player->setCurrentLevel(player->getLevel()+1);
            Savegame sg(player);
            std::cout<<"level over you win ! yay"<<std::endl;
            
            game->changeState(DockState::instance());
            // break;
        }
        
        if(enemyDrone.isActive())
        {
            if(enemyDrone.getHps()<1)
            {
                enemyDrone.setCurrentAnimation(1);
             //   enemyDrone.setActive(false);
            }
         //   checkBorders(ufoDrone);
            enemyDrone.update(player->getDestination().x,player->getDestination().y);
            if(enemyDrone.getShouldFire() && !enemyFireTimer.isActive() )
            {
              //  ufoDrone.
                enemyFireTimer.setStartTime(SDL_GetTicks());
                enemyFireTimer.setTimerActive(true);
                enemyFireTimer.setDuration(500);
                enemyFire();
            }
            enemyDrone.animate();
        }
        
        ////// Begin Virtual Joystick Stuff///////////
        virtualJoystick->update();
        
        if(virtualJoystick->getSelection()==1)
        {
            if(player->isReady())
            {
                playerFire();
                virtualJoystick->setSelection(0);
            }
        }
        if(virtualJoystick->getSelection()==2)
        {
            if(!player->isReady())
            {
                player->resetAnimation();
                player->setGettingReady(true);
                player->setCurrentAnimation(playerReady);
                virtualJoystick->setSelection(0);
                
            }
            else
            {
                player->resetAnimation();
                
                player->setCurrentAnimation(playerReadyReversed);
                virtualJoystick->setSelection(0);
                
            }
        }
        if(virtualJoystick->getSelection()==3)
        {
            player->applyForce(player->getDefaultAcc(),WEST);
            
        }
        if(virtualJoystick->getSelection()==4)
        {
            player->applyForce(player->getDefaultAcc(),EAST);
            
        }
        if(virtualJoystick->getSelection()==5)
        {
            player->applyForce(player->getDefaultAcc(),NORTH);
            
        }
        if(virtualJoystick->getSelection()==6)
        {
            player->applyForce(player->getDefaultAcc(),SOUTH);
            
        }
        ////////////////// End virtual Joystick stuff/////////////
        for(Background &b: backgrounds)
        {
            b.update(*levelH);
        }
        player->update();
        if(player->isActive())
        {
            if(player->getHps()<1)
            {
                player->setActive(false);
                std::cout<<"You lose!"<<std::endl;
                game->changeState(MenuState::instance());
                SDL_Delay(1000);
            }
            player->animatePlayer();
            if(updateHUD==true )
            {
                updatePlayerStats();
            }
        }
        asteroidTimer.update();
        if(!asteroidTimer.isActive())
        {
            spawnAsteroid();
            asteroidTimer.setStartTime(SDL_GetTicks());
            asteroidTimer.setTimerActive(true);
            
        }
        enemyFireTimer.update();
        
        for(Projectile &p: playersBullets)
        {
            if(p.isActive())
            {
                p.update();

                if(p.getDestination().y<0)
                {
                    p.setActive(false);
                }
                for(Entity &a: asteroids)  //check collisions between asteroids and projectiles
                {
                    if(checkCollision(p.getDestination(), a.getDestination()) && a.isActive())
                    {
                        p.setActive(false);
                        a.setHps(a.getHps()-p.getDamage());
                        a.setYAcc(a.getYAcc()-1);
                    }
                }
                if(enemyDrone.isActive() && checkCollision(p.getDestination(), enemyDrone.getDestination()))
                {
                    enemyDrone.setHps(enemyDrone.getHps()-p.getDamage());
                    p.setActive(false);
                    
                }
            }
        }
        for(Entity &a: asteroids)
        {
            if(a.isActive())
            {
                a.update();
                a.animate();
                if(a.getHps()<1 && !a.didJustCollide())
                {
                    player->setScore(player->getScore()+10);
                    playSound("asteroidexplode.wav", SDL_MIX_MAXVOLUME);
                    a.setJustCollided(true);  ///prevents the sound FX from being played more than once
                    a.setCurrentAnimation(asteroidExplode);
                    if(a.getMass()>30)
                    {
                       spawnFragment(a);

                    }
                    if(a.getMass()>75)
                    {
                        spawnItem(a.getDestination().x, a.getDestination().y);
                    }
                    shouldUpdateHUD(true);
                }
                if(a.getDestination().y>windowHeight)
                {
                    a.setActive(false);
                }
                if(checkCollision(a.getDestination(), player->getDestination()) && !a.didJustCollide())
                {
                    int mass = player->getMass();

                    int playerYAccelleration = (mass*player->getYAcc())+(a.getMass()*(a.getYAcc()));
                    int playerYSpeed = playerYAccelleration/mass;
                    int playerXAccelleration =(mass*player->getXAcc())+(a.getMass()*(a.getXAcc()));
                    int playerXSpeed = playerXAccelleration/mass;
                    
                    player->setYAcc(playerYSpeed);
                    player->setXAcc(playerXSpeed);
                    playSound("asteroidexplode.wav", SDL_MIX_MAXVOLUME);

                    if(player->getHps()<(player->getMaxHps()/4))
                    {
                        playSound("alert.wav", SDL_MIX_MAXVOLUME);

                    }
                    if(player->getHps()<1)
                    {
                        playSound("alert.wav", SDL_MIX_MAXVOLUME);
                        std::cout<<"You lose!"<<std::endl;
                        game->changeState(MenuState::instance());
                        SDL_Delay(1000);
                        //player->setActive(false);
                        
                    }
                    int asteroidYAcceleration = (player->getMass()*player->getYAcc())+(a.getMass()*(a.getYAcc()));
                    int asteroidYSpeed = asteroidYAcceleration/a.getMass();
                    
                    int asteroidXAcceleration = (player->getMass()*player->getXAcc())+(a.getMass()*(a.getXAcc()));
                    int asteroidXSpeed = asteroidXAcceleration/a.getMass();
                    a.setYAcc(asteroidYSpeed);
                    a.setXAcc(asteroidXSpeed);
                    a.setJustCollided(true);
                    a.setCurrentAnimation(asteroidExplode);
                    if(player->getShield()>0)
                    {
                        player->setShield(player->getShield()-a.getMass());
                        player->setCurrentAnimation(playerShield);
                        
                    }
                    if(player->getShield()<player->getMaxShield()/2)
                    {
                        shouldDiplayShieldAlert=true;
                    }
                    if(player->getShield()<1)
                    {
                        player->setHps(player->getHps()-a.getMass());
                    }
                    shouldUpdateHUD(true);
                    return;
                }
            }
        }
        //// Update Items  /////
        for(Item &i : items)
        {
            if(i.getActive())
            {
                i.update();
                if(checkCollision(i.getDestination(), player->getDestination()))
                {
                    i.setActive(false);
                    i.causeEffect(player);
                    shouldUpdateHUD(true);
                }
            }
        }
        ///// Update Items End/////
        for(EnemyProjectile &p: enemysBullets)
        {
            if(p.isActive())
            {
                p.update();
                if(checkCollision(p.getDestination(), player->getDestination()))
                {
                    if(player->getShield()>0)
                    {
                        player->setShield(player->getShield()-p.getDamage());
                        player->setCurrentAnimation(playerShield);
                        p.setActive(false);

                    }
                    if(player->getShield()<1)
                    {
                        player->setHps(player->getHps()-p.getDamage());
                        p.setActive(false);

                    }
                    if(p.getDestination().y > windowHeight )
                    {
                        p.setActive(false);
                    }
                }
            }
        }
        checkBorders(*player);   //make sure player doesnt leave screen
    }
}
void PlayState::render(Game* game)
{

    SDL_SetRenderDrawColor(playRenderer, 0, 0, 0, 255);
    SDL_RenderClear(playRenderer);
 
    for(Background &b: backgrounds)
    {
        drawBackground(b); 
    }
    draw(*player,0);
    if(enemyDrone.isActive())
    {
        draw(enemyDrone,0);
    }
    for(Entity &a: asteroids)
    {
        if(a.isActive())
        {
            draw(a,a.getRotationAngle());
        }
    }

    for(Item &i: items)
    {
        if(i.getActive())
        {
            draw(i,0);
        }
    }
    for(Projectile &p: playersBullets)
    {
        if(p.isActive())
        {
            draw(p,0);
        }
    }
    for(EnemyProjectile &p: enemysBullets)
    {
        if(p.isActive())
        {
            draw(p,0);
        }
    }
/////// Hud stuff below is significantly slowing down my program
    if(levelTimer->isActive())
    {
        draw(hud,0);
        hud.drawText(playRenderer, "Hull integrity (%): ", hud.getDestination().x+20, hud.getDestination().y+10, 255, 255, 255);
        hud.drawText(playRenderer, std::to_string(hullIntegrity).c_str(), hud.getDestination().x+160, hud.getDestination().y+10, 255, 255, 255);
      //  hud.drawText(playRenderer, std::to_string(hI).to_str(), hud.getDestination().x+160, hud.getDestination().y+10, 255, 255, 255);
        hud.drawText(playRenderer, "Rare elements (kg): ", hud.getDestination().x+20, hud.getDestination().y+25, 255, 255, 255);
        hud.drawText(playRenderer, std::to_string(player->getRareElements()).c_str(), hud.getDestination().x+160, hud.getDestination().y+25, 255, 255, 255);
//         hud.drawText(playRenderer, rareElementsString, hud.getDestination().x+160, hud.getDestination().y+25, 255, 255, 255);
        hud.drawText(playRenderer, "Metal Alloy (kg): ", hud.getDestination().x+20, hud.getDestination().y+40, 255, 255, 255);
        hud.drawText(playRenderer,std::to_string(player->getPreciousMetals()).c_str(), hud.getDestination().x+160, hud.getDestination().y+40, 255, 255, 255);
        
        hud.drawText(playRenderer, "Shield: ", hud.getDestination().x+20, hud.getDestination().y+55, 255, 255, 255);
     //   hud.drawText(playRenderer,shieldString,hud.getDestination().x+160,hud.getDestination().y+55,255,255,255);
     
        hud.drawText(playRenderer, "Level: ", hud.getDestination().x+20, hud.getDestination().y+70, 255, 255, 255);
    //    hud.drawText(playRenderer, levelString, hud.getDestination().x+160, hud.getDestination().y+70, 255, 255, 255);
        hud.drawText(playRenderer, "Score: ", hud.getDestination().x+20, hud.getDestination().y+85, 255, 255, 255);
     //   hud.drawText(playRenderer,scoreString,hud.getDestination().x+160,hud.getDestination().y+85,255,255,255);
     //     hud.drawText(playRenderer, "ETA: ", hud.getDestination().x+20, hud.getDestination().y+100, 255, 255, 255);
       //   hud.drawText(playRenderer, std::to_string(levelTimer->getTimeLeft()).c_str(), hud.getDestination().x+160, hud.getDestination().y+100, 255, 255, 255);
        virtualJoystick->draw();
    }
    if(shouldDiplayShieldAlert==true)
    {
        draw(shieldAlert,0);

    }
    if(shouldDiplayHullAlert==true)
    {
        draw(hullAlert,0);
    }
    SDL_RenderPresent(playRenderer);

}
void PlayState::clean()
{
   
    levelTimer=nullptr;
    /* clear all vectors below */
    for(Projectile &p: playersBullets)
    {
        if(p.isActive())
        {
            p.setActive(false);
        }
    }
   
    for(Entity &a: asteroids)
    {
        if(a.isActive())
        {
            a.setActive(false);
        }
    }
    asteroidTimer.setTimerActive(false);
    for(Item &i: items)
    {
        if(i.getActive())
        {
            i.setActive(false);
        }
    }
    playersBullets.clear();
    shouldUpdateHUD(false);
    shouldDiplayHullAlert=false;
    shouldDiplayShieldAlert=false;
    asteroids.clear();
    items.clear();
    if(levelTimer!=NULL)
    {
        delete levelTimer;
    }
    levelInfo.clear();
    texturePaths.clear();
    /* clear all vectors finished  */
    virtualJoystick->~VirtualJoystick();
//    delete virtualJoystick;
    for(Background &b: backgrounds)
    {
        SDL_DestroyTexture(b.getTexture());
    }
    backgrounds.clear();
    player->setActive(false);
   // delete player;
    SDL_DestroyTexture(player->getTexture());
    SDL_DestroyTexture(rareElement.getTexture());
    SDL_DestroyTexture(preciousMetal.getTexture());
    SDL_DestroyTexture(energyPulse.getTexture());
    SDL_DestroyTexture(playersBullet.getTexture());
    SDL_DestroyTexture(asteroid.getTexture());
    SDL_DestroyTexture(enemyDrone.getTexture());
    printf("PlayState Clean Successful\n");
}
