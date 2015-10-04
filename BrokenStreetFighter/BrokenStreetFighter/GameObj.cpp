// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// GameObj.cpp

#include "GameObj.h"

GameObj::GameObj(){
	SetTexture();
	scaleSet = false;
}

GameObj::~GameObj(){

}

void GameObj::SetTexture(){
	//sf::Texture texture;
	if (!playertexture.loadFromFile("bin/AGDSjam_spritesheet.png")){
		std::cout << "Failed to Load Player Spritesheet" << std::endl;
	}
	if (!playertextureFlipped.loadFromFile("bin/AGDSjam_spritesheet_Flipped.png")){
		std::cout << "Failed to Load Player Spritesheet" << std::endl;
	}
	if (!backgroundtexture.loadFromFile("bin/AGDSbackground.png")){
		std::cout << "Failed to Load Player Spritesheet" << std::endl;
	}
	if (!player1_healthbarBTex.loadFromFile("bin/AGDSjam_player1bar.png")){
		std::cout << "Failed to Load Player Spritesheet" << std::endl;
	}
	if (!player2_healthbarBTex.loadFromFile("bin/AGDSjam_player2bar.png")){
		std::cout << "Failed to Load Player Spritesheet" << std::endl;
	}
	currentAnimation = &idleAni;
	SetAnimations(&playertexture);
}

void GameObj::PlayerTex(){
	SetAnimations(&playertexture);
	needFlipped = false;
}

void GameObj::PlayerTexFlipped(){
	SetAnimations(&playertextureFlipped);
	needFlipped = false;
}

void GameObj::SetUpSprite(){
	//AnimatedSprite animatedSprite();
	animatedSprite.setFrameTime(sf::seconds(0.1));
	if(!scaleSet) {
		animatedSprite.scale(6, 6);
		
		scaleSet = true;
	}
	animatedSprite.pause();
	animatedSprite.setLooped(true);
	animatedSprite.setPosition(Position);
	
}

void GameObj::SetAnimations(sf::Texture* texture){
	
	//WALK FORWARDS (well roll but you know what i mean)//
	walkFowardAni.setSpriteSheet(*texture);
	walkFowardAni.addFrame(sf::IntRect(0, 52, 52, 52));
	walkFowardAni.addFrame(sf::IntRect(52, 52, 52, 52));
	walkFowardAni.addFrame(sf::IntRect(104, 52, 52, 52));
	walkFowardAni.addFrame(sf::IntRect(156, 52, 52, 52));

	//WALK BACKWARDS//
	walkBackwardsAni.setSpriteSheet(*texture);
	walkBackwardsAni.addFrame(sf::IntRect(0, 104, 52, 52));
	walkBackwardsAni.addFrame(sf::IntRect(52, 104, 52, 52));
	walkBackwardsAni.addFrame(sf::IntRect(104, 104, 52, 52));
	walkBackwardsAni.addFrame(sf::IntRect(156, 104, 52, 52));

	//IDLE (lazy git)//
	idleAni.setSpriteSheet(*texture);
	idleAni.addFrame(sf::IntRect(0, 0, 52, 52));
	idleAni.addFrame(sf::IntRect(52, 0, 52, 52));
	idleAni.addFrame(sf::IntRect(104, 0, 52, 52));
	idleAni.addFrame(sf::IntRect(156, 0, 52, 52));
	idleAni.addFrame(sf::IntRect(208, 0, 52, 52));
	idleAni.addFrame(sf::IntRect(260, 0, 52, 52));

	//FALCON PUNCH//
	hardPunchAni.setSpriteSheet(*texture);
	hardPunchAni.addFrame(sf::IntRect(0, 156, 52, 52));
	hardPunchAni.addFrame(sf::IntRect(52, 156, 52, 52));
	hardPunchAni.addFrame(sf::IntRect(104, 156, 52, 52));
	hardPunchAni.addFrame(sf::IntRect(156, 156, 52, 52));
	hardPunchAni.addFrame(sf::IntRect(208, 156, 52, 52));
	hardPunchAni.addFrame(sf::IntRect(260, 156, 52, 52));

	//WIMPY PUNCH//
	lightPunchAni.setSpriteSheet(*texture);
	lightPunchAni.addFrame(sf::IntRect(0, 208, 52, 52));
	lightPunchAni.addFrame(sf::IntRect(52, 208, 52, 52));
	lightPunchAni.addFrame(sf::IntRect(104, 208, 52, 52));
	lightPunchAni.addFrame(sf::IntRect(156, 208, 52, 52));
	lightPunchAni.addFrame(sf::IntRect(208, 208, 52, 52));
	
	//DEATH!!!!!!!!!!!!!!!!!!!!!!!!!!// (enough ! for you dean? ;) 
	deathAni.setSpriteSheet(*texture);
	deathAni.addFrame(sf::IntRect(0, 260, 52, 52));
	deathAni.addFrame(sf::IntRect(52, 260, 52, 52));
	deathAni.addFrame(sf::IntRect(104, 260, 52, 52));
	deathAni.addFrame(sf::IntRect(156, 260, 52, 52));
	deathAni.addFrame(sf::IntRect(208, 260, 52, 52));
	deathAni.addFrame(sf::IntRect(260, 260, 52, 52));
	deathAni.addFrame(sf::IntRect(0, 312, 52, 52));
	deathAni.addFrame(sf::IntRect(52, 312, 52, 52));
	deathAni.addFrame(sf::IntRect(104, 312, 52, 52));
	deathAni.addFrame(sf::IntRect(156, 312, 52, 52));
	deathAni.addFrame(sf::IntRect(208, 312, 52, 52));
	deathAni.addFrame(sf::IntRect(260, 312, 52, 52));
	deathAni.addFrame(sf::IntRect(0, 364, 52, 52));
	deathAni.addFrame(sf::IntRect(52, 364, 52, 52));
	deathAni.addFrame(sf::IntRect(104, 364, 52, 52));
	
	


	animatedSprite.setAnimation(*currentAnimation);
}

void GameObj::SetupStaticSprite(sf::Vector2f Position){
	background.setTexture(backgroundtexture);
	background.scale(9.5, 8.6);

	player1_healthbarB.setTexture(player1_healthbarBTex);
	player1_healthbarB.scale(9.5, 8.6);

	player2_healthbarB.setTexture(player2_healthbarBTex);
	player2_healthbarB.setPosition(932,0);
	player2_healthbarB.scale(9.5, 8.6);
	

}