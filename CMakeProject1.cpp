#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include <cstdint>
#include <cmath>
#include <vector>
#include <random>
#include <string>

enum class GameState{Intro, MainMenu, RobotMenu, ShopMenu};

int main()
{
    GameState gameState = GameState::Intro;
    MainMenu mainMenu;
    Dialogue dialogueBox;
    RobotMenu robotMenuBiped;
    RobotMenu robotMenuQuadruple;
    RobotMenu robotMenuWheels;
    ShopMenu shopMenu;


    //WINDOW 
    sf::RenderWindow window(sf::VideoMode({ 800,800 }), "Curch of Machinery");
    window.setFramerateLimit(60);

    //BACKGROUND
    sf::Texture cathedralTexture; //Texture loads the complete 400×80 PNG.
    bool textureLoaded = cathedralTexture.loadFromFile("assets/cathedral.png");
    if (!textureLoaded)
    {
        return 1;
    }
    cathedralTexture.setSmooth(false); //keeps the pixels sharp.
    sf::Sprite cathedralSprite(cathedralTexture);//sprite draws the object using the texture
    cathedralSprite.setTextureRect(sf::IntRect({ 0,0 }, { 80,80 })); //selects the first 80×80 frame.
    // 0 , 0 -> satrt from coordinate x and y = 0;
   //80 , 80 ->width and height of each frame is 80px/80px
    cathedralSprite.setScale({ 10.f, 10.f });

    //BACKGROUND ANIMATION
    int currentFrame = 0;
    const int frameCount = 6;
    const int frameWidth = 80;
    sf::Clock animationClock;
    const sf::Time frameDuration = sf::milliseconds(150);

    //FONT
    sf::Font gameFont;
    if (!gameFont.openFromFile("assets/game-font.ttf")) {
        return 1;
    }
    gameFont.setSmooth(false);

    //TITLE
    sf::Text cathedralTitle(gameFont, U"Saint Hierl\u00E4nd Cathedral", 29);
    cathedralTitle.setFillColor(sf::Color::White);
    const sf::FloatRect titleBounds = cathedralTitle.getLocalBounds();
    cathedralTitle.setOrigin({
        titleBounds.position.x + titleBounds.size.x / 2.f,  //we set the x-origin in the middle of the word
        titleBounds.position.y + titleBounds.size.y / 2.f //Text starts at x = 4 , Text width = 300 => Center = 4 + 300 / 2 = 154
        });
    cathedralTitle.setPosition({ 400.f, 330.f });

    //PARAGRAPH 1
    sf::Text paragraphOne(
        gameFont, U"Willkommen, frommer Gl\u00E4ubiger\n"
        U"des Gottes des Dampfes und\n"
        U"der Maschinen.", 26);
    paragraphOne.setOutlineThickness(1.5f);
    const sf::FloatRect paragraphOneBounds = paragraphOne.getLocalBounds();
    paragraphOne.setOrigin({
        paragraphOneBounds.position.x + paragraphOneBounds.size.x / 2.f,
        paragraphOneBounds.position.y + paragraphOneBounds.size.y / 2.f
        });

    //PARAGRAPH TIME LOGIC
    sf::Clock welcomeClock; //we start counting seconds
    const float paragraphDuration = 1.5f;
    const float pauseBetweenParagraphs = 0.2f;


    //PARAGRAPH 2
    sf::Text paragraphTwo(gameFont,
        U"Dank deines unersch\u00FCtterlichen\n"
        U"Glaubens an Gott wurdest du\n"
        U"auserw\u00E4hlt, unserem Beyonder\n"
        U"Team beizutreten: ", 25);
    paragraphTwo.setOutlineThickness(1.5f);
    const sf::FloatRect paragraphTwoBounds = paragraphTwo.getLocalBounds();
    paragraphTwo.setOrigin({
        paragraphTwoBounds.position.x + paragraphTwoBounds.size.x / 2.f,
        paragraphTwoBounds.position.y + paragraphTwoBounds.size.y / 2.f
        });
    const float paragraphTwoStartTime = paragraphDuration + pauseBetweenParagraphs;

    //PARAGRAPH 3 THE
    const std::string theText = "THE MACHINERY";
    std::vector<sf::Text> theLetters;
    theLetters.reserve(theText.size());
    for (const char character : theText) {
        theLetters.emplace_back(gameFont, sf::String(character), 25);
        theLetters.back().setOutlineThickness(1.5f);
    }
    const float paragraphTheStartTime = paragraphTwoStartTime + paragraphDuration + pauseBetweenParagraphs;
    std::vector <float> theYOffsets(theLetters.size(), 0.f);
    sf::Text theLayout(gameFont, sf::String(theText), 25);

    //PARAGRAPH 3 MACHINERY
    const std::string machineryText = "HIVEMIND!";
    std::vector <sf::Text> machineryLetters;

    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::uniform_int_distribution<int> randomYOffset(-3, 3);
    sf::Clock shakeClock;
    const sf::Time shakeInterval = sf::milliseconds(80);
    sf::Text machineryLayout(gameFont, sf::String(machineryText), 25);


    machineryLetters.reserve(machineryText.size()); //Reserve enough memory for as many objects as there are characters in machineryText.
    for (const char character : machineryText) { //normal for loop iteration for every letter of machineryText
        machineryLetters.emplace_back(gameFont, sf::String(character), 25); //emplace_back: pushes a new character to the back of the vector
        //sf::String(character) ->converts the normal C++ char into a text type that SFML understands.
        machineryLetters.back().setOutlineThickness(1.5f); //back() accesses the last object in the vector—the letter we just created.
    }
    std::vector <float> machineryYOffsets(machineryLetters.size(), 0.f); //baisically, we make a vector: 0.f, 0.f, .. with the size of machineryLetters.size(). later these values will be random -2.f, 1.f, 0.f, -1.f etc.. creting the shaking effect     

    //DECISION
    sf::RectangleShape decisionBackground({ 175.f, 100.f });
    const float decisionStartTime = paragraphTheStartTime + paragraphDuration + pauseBetweenParagraphs;
    sf::Text acceptText(gameFont, U"> ANNEHMEN", 26);
    sf::Text declineText(gameFont, U" ABLEHNEN", 26);
    acceptText.setOutlineThickness(1.5f);
    declineText.setOutlineThickness(1.5f);
    int selectedOption = 0; // 0 = ACCEPT, 1 = DECLINE
    bool decisionConfirmed = false;

    //Chest
    sf::Texture chestTexture;
    bool chestTextureLoaded = chestTexture.loadFromFile("assets/Chest.png");
    if (!chestTextureLoaded) {
        return 1;
    };
    chestTexture.setSmooth(false);
    sf::Sprite chestSprite(chestTexture);
    chestSprite.setTextureRect(sf::IntRect({ 0,0 }, { 80,80 }));
    chestSprite.setScale({ 10.f, 10.f });                             

    const int chestFrameCount = 6;
    const int chestFrameWidth = 80;
    int chestCurrentFrame = 0;
    bool chestAnimationStarted = false;
    sf::Time chestFrameDuration = sf::milliseconds(120);
    sf::Clock chestAnimationClock;

    //Dialogue 1
    const std::string dialogue1Text = "   Als offizielles Mitglied unseres Teams haben Sie\neinen Roboter als Assistenten erhalten. Passe ihn nach\nIhr Wünschen an oder kaufe neue Teile.";
    std::vector <sf::Text> dialogue1Letters;
    sf::Clock dialogueLetterClock;
    const sf::Time dialogueLetterInterval = sf::milliseconds(33.3);
    sf::Text dialogue1Layout(gameFont, sf::String(dialogue1Text), 25);

    dialogue1Letters.reserve(dialogue1Text.size());
    for (const char character : dialogue1Text) {
        dialogue1Letters.emplace_back(gameFont, sf::String(character), 25);
        dialogue1Letters.back().setOutlineThickness(1.5f);
    }
    std::size_t visibleLetters = 0;
    bool dialogue1Started = false;

    //DIALOGUE 2
    bool continuationAvailable = false;
    bool continuationConfirmed = false;
    const std::string dialogue2Text = "   Wenn Sie bereit sind, lass uns eine Mission starten!";
    std::vector <sf::Text> dialogue2letters;
    sf::Text dialogue2Layout(gameFont, sf::String(dialogue2Text), 25);
    dialogue2letters.reserve(dialogue2Text.size());
    for (const char character : dialogue2Text) {
        dialogue2letters.emplace_back(gameFont, sf::String(character), 25);
        dialogue2letters.back().setOutlineThickness(1.5f);
    }
    int visible2Letters = 0;
    bool continuation2Available = false;
    bool continuation2Confirmed = false;

    //ARROW
    sf::Texture arrowTexture;
    sf::Time animationTime = sf::milliseconds(200);
    sf::Clock AnimationClock;
    bool arrowtextureLoaded = arrowTexture.loadFromFile("assets/arrow.png");
    if (!arrowtextureLoaded)
    {
        return 1;
    }
    arrowTexture.setSmooth(false);
    sf::Sprite arrowSprite(arrowTexture);
    arrowSprite.setTextureRect(sf::IntRect({ 0,0 }, { 800,800 }));
    int arrowcurrentFrame = 0;

    //RobotMenu
    const float optionX = 485.f;
    const float optionWidth = 295.f;
    const sf::FloatRect robotClickArea(
        { 50.f, 50.f },      // x and y position
        { 310.f, 520.f }     // width and height
    );
    const sf::FloatRect shopClickArea(
        { 400.f, 50.f },
        { 350.f, 520.f }
    );
    const sf::FloatRect returnClickArea(
        { 15.f, 15.f },
        { 100.f, 105.f }
    );
    const sf::FloatRect robotQuadrupleArea(
        { optionX, 45.f },
        { optionWidth, 195.f }
    );
    const sf::FloatRect robotWheelsArea(
        { optionX, 250.f },
        { optionWidth, 195.f }
    );
    const sf::FloatRect robotBipedArea(
        { optionX, 455.f },
        { optionWidth, 185.f }
    );
    int customizationDecision = 1;

    //GAMEPLAY
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) { //This checks the window’s event queue. Events are things that happen to the window

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                const bool decisionAvailable = welcomeClock.getElapsedTime().asSeconds() >= decisionStartTime;
                if (decisionAvailable && !decisionConfirmed) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Up || keyPressed->scancode == sf::Keyboard::Scancode::W) {
                        selectedOption = 0;
                    }
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Down || keyPressed->scancode == sf::Keyboard::Scancode::S) {
                        selectedOption = 1;
                    }
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                        decisionConfirmed = true;
                        if (selectedOption == 0) {
                            chestCurrentFrame = 0;
                            chestAnimationStarted = true;
                            chestSprite.setTextureRect(sf::IntRect({ 0,0 }, { 80,80 }));
                            chestAnimationClock.restart();
                        }
                        else if (selectedOption == 1) {
                            return 1;
                        }
                    }
                }
                if (!continuationConfirmed && continuationAvailable) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                        continuationConfirmed = true;
                    }
                }
                if (!continuation2Confirmed && continuation2Available) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                        continuation2Confirmed = true;
                    }
                }
                if (gameState == GameState::ShopMenu || gameState == GameState::RobotMenu){
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                        gameState = GameState::MainMenu;
                }
            }
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    const sf::Vector2f mousePosition = window.mapPixelToCoords(mousePressed->position);
                    if (gameState == GameState::MainMenu && continuation2Confirmed) {
                        if (robotClickArea.contains(mousePosition)) {
                            gameState = GameState::RobotMenu;
                        }
                        else if (shopClickArea.contains(mousePosition)) {
                            gameState = GameState::ShopMenu;
                        }
                    }
                    if (gameState == GameState::ShopMenu || gameState == GameState::RobotMenu) {
                        if (returnClickArea.contains(mousePosition)) {
                            gameState = GameState::MainMenu;
                        }
                        if (robotQuadrupleArea.contains(mousePosition)) {
                            customizationDecision = 1;
                        }
                       if (robotBipedArea.contains(mousePosition)) {
                           customizationDecision = 2;

                       }
                       if (robotWheelsArea.contains(mousePosition)) {
                           customizationDecision = 3;
                       }
                    }

                }
            }
        }
        //BACKGROUND ANIMATION
        if (animationClock.getElapsedTime() >= frameDuration) {
            currentFrame = (currentFrame + 1) % frameCount;
            cathedralSprite.setTextureRect(sf::IntRect({ currentFrame * frameWidth, 0 }, { 80 , 80 }));
            animationClock.restart();
        }

        //PARAGRAPH ONE DURATION
        const float welcomeElapsed = welcomeClock.getElapsedTime().asSeconds(); //we transform the clock-seconds into float-seconds

        //PARAGRAPH ONE ANIMATION 
        float paragraphOneProgress = welcomeElapsed / paragraphDuration; //second 0: paragraphOneProgress = 0 /2.5 = 0;
        //second 1.25: 1.25 / 2.5f = 0.5
      //second 2.5: 2.5 / 2.5f = 1;
     //1)calculates how far the 2.5-second animation has progressed.
    //2)the progress is between 0(no progress) and 1(has finished);
        if (paragraphOneProgress > 1.f) paragraphOneProgress = 1.f; //makes sure we dont exceed 1;
        const float paragraphOneY = 370.f + 39.f * paragraphOneProgress;
        const auto paragraphOneAplha = static_cast<std::uint8_t>(225.f * paragraphOneProgress); //makes it gradually less transparent
        paragraphOne.setOutlineColor(sf::Color(0, 0, 0, paragraphOneAplha));
     
   paragraphOne.setPosition({ 400.f, paragraphOneY });
        paragraphOne.setFillColor(sf::Color(255, 255, 255, paragraphOneAplha));

        //PARAGRAPH 2 ANIMATION
        float paragraphTwoProgress = (welcomeElapsed - paragraphTwoStartTime) / paragraphDuration;
        if (paragraphTwoProgress < 0.f) {
            paragraphTwoProgress = 0.f;
        }
        if (paragraphTwoProgress > 1.f) {
            paragraphTwoProgress = 1.f;
        }
        const float paragraphTwoY = 470.f + 39.f * paragraphTwoProgress;
        const auto paragraphTwoAlpha = static_cast<std::uint8_t>(225.f * paragraphTwoProgress);
        paragraphTwo.setOutlineColor(sf::Color(0, 0, 0, paragraphTwoAlpha));
        paragraphTwo.setPosition({ 400.f , paragraphTwoY });
        paragraphTwo.setFillColor(sf::Color(255, 255, 255, paragraphTwoAlpha));

        //PARAGRAPH 3 ANIMATION
        float paragraphTheProgress = (welcomeElapsed - paragraphTheStartTime) / paragraphDuration;
        if (paragraphTheProgress < 0.f) {
            paragraphTheProgress = 0.f;
        }
        if (paragraphTheProgress > 1.f) {
            paragraphTheProgress = 1.f;
        }
        if (paragraphTheProgress > 0.f && shakeClock.getElapsedTime() >= shakeInterval) {
            for (float& YOffset : theYOffsets) { //without &: Give me a copy of the values, but dont change the original vector (bad, cus we actually want all values to change)
                //with &: Give me direct access to the actual values
                YOffset = static_cast<float>(randomYOffset(randomGenerator)); //randomYOffset(-3, 3): create INT values between -3,3
                //randomYOffset(randomGenerator): create RANDOM, FLOAT values between -3,3

            }
            for (float& YOffset : machineryYOffsets) {
                YOffset = static_cast<float>(randomYOffset(randomGenerator));
            }
            shakeClock.restart();
        }
        const auto paragraphThreeAlpha = static_cast<std::uint8_t>(225.f * paragraphTheProgress);
        const sf::Vector2f paragraphTwoEndPosition = paragraphTwo.findCharacterPos(paragraphTwo.getString().getSize()); //sf::Vector2f returns a vector(position_x, position_y)
        //paragraphTwo.getString() returns paragraphTwo as a string (originally it was declared as sf::Text)
        //paragraphTwo.getString().getSize() retuens the size of the string;
        //findCharacterPos()returns the x and y coordinate of the last letter of the string(paragraph2 text)
        theLayout.setPosition(paragraphTwoEndPosition);
        for (std::size_t i = 0; i < theLetters.size(); i++) {
            const sf::Vector2f naturalPosition = theLayout.findCharacterPos(i);
            theLetters[i].setPosition({ naturalPosition.x , naturalPosition.y + theYOffsets[i] * paragraphTheProgress });
            theLetters[i].setFillColor(sf::Color(255, 255, 255, paragraphThreeAlpha));
            theLetters[i].setOutlineColor(sf::Color(0, 0, 0, paragraphThreeAlpha));
        }
        const float paragraphMachineryStartX = paragraphTwo.findCharacterPos(0).x; //sf::Text returns each letter, their position(both x and y coordinate)
        //since weknow exactly which letter(index) we want we just use .findcaharacterposition(index).x or .y
        //if we dont know the exact end position we use .getString().getSize();
        const float machineryY = paragraphTwoEndPosition.y + gameFont.getLineSpacing(27);
        machineryLayout.setPosition({ paragraphMachineryStartX, machineryY });
        for (std::size_t i = 0; i < machineryLetters.size(); i++) {
            const sf::Vector2f naturalPosition = machineryLayout.findCharacterPos(i);
            machineryLetters[i].setPosition({ naturalPosition.x ,naturalPosition.y + machineryYOffsets[i] * paragraphTheProgress });
            machineryLetters[i].setFillColor(sf::Color(255, 255, 255, paragraphThreeAlpha));
            machineryLetters[i].setOutlineColor(sf::Color(0, 0, 0, paragraphThreeAlpha));
        }

        //DECISION ANIMATION
        float decisionProgress = (welcomeElapsed - decisionStartTime) / 0.5f;
        if (decisionProgress < 0.f)
        {
            decisionProgress = 0.f;
        }

        if (decisionProgress > 1.f)
        {
            decisionProgress = 1.f;
        }
        const auto backgroundAlpha = static_cast<std::uint8_t>(100.f * decisionProgress);
        decisionBackground.setFillColor(sf::Color(0, 0, 0, backgroundAlpha));
        const auto decisionAlpha = static_cast<std::uint8_t>(225.f * decisionProgress);
        const float decisionFirstY = machineryY + gameFont.getLineSpacing(25) + 10.f;
        const sf::Color selectedColor(255, 215, 90, decisionAlpha);
        const sf::Color normalColor(255, 255, 255, decisionAlpha);
        acceptText.setPosition({ 550.f, decisionFirstY });
        declineText.setPosition({ 550.f,decisionFirstY + gameFont.getLineSpacing(25) });
        decisionBackground.setPosition({ 530.f,decisionFirstY - 22.f });
        if (selectedOption == 0) {
            acceptText.setString(U"> ANNEHMEN");
            declineText.setString(U"  ABLEHNEN");
            acceptText.setFillColor(selectedColor);
            declineText.setFillColor(normalColor);
        }
        else {
            acceptText.setString(U"  ANNEHMEN");
            declineText.setString(U"> ABLEHNEN");
            acceptText.setFillColor(normalColor);
            declineText.setFillColor(selectedColor);
        }
        acceptText.setOutlineColor(sf::Color(0, 0, 0, decisionAlpha));
        declineText.setOutlineColor(sf::Color(0, 0, 0, decisionAlpha));

        //CHEST ANIMATION
        const bool chestFrameTimePassed = chestAnimationClock.getElapsedTime() >= chestFrameDuration;

        if (gameState == GameState::Intro && chestAnimationStarted && chestFrameTimePassed) {
            if (chestCurrentFrame < chestFrameCount - 1) {
                chestCurrentFrame++;
                chestSprite.setTextureRect(sf::IntRect({ chestCurrentFrame * chestFrameWidth,0 }, { 80,80 }));
                chestAnimationClock.restart();
            }
            else {
                gameState = GameState::MainMenu;
                dialogue1Started = true;
            }
        }

        //Dialgoue 1 ANIMATION
        if (dialogue1Started && visibleLetters < dialogue1Letters.size() && dialogueLetterClock.getElapsedTime() >= dialogueLetterInterval)
        {
            visibleLetters++;
            dialogueLetterClock.restart();
        }
   
        dialogue1Layout.setPosition({ 110.f, 668.f });
        for (std::size_t i = 0; i < dialogue1Letters.size(); i++) {
            const sf::Vector2f dialogue1naturalPosition = dialogue1Layout.findCharacterPos(i);
            dialogue1Letters[i].setPosition({ dialogue1naturalPosition.x , dialogue1naturalPosition.y});
            dialogue1Letters[i].setFillColor(sf::Color(255, 255, 255));
            dialogue1Letters[i].setOutlineColor(sf::Color(0, 0, 0));
        }

        if (visibleLetters == dialogue1Letters.size() - 1) {
            continuationAvailable = true;
        }

        //ARROW ANIMATION
        if (AnimationClock.getElapsedTime() >= animationTime) {
            arrowcurrentFrame = (arrowcurrentFrame + 1) % 2;
            arrowSprite.setTextureRect(sf::IntRect({ arrowcurrentFrame * 800, 0 }, { 800,800 }));
            AnimationClock.restart();
        }

        //Dialogue 2 ANIMATION
        if (continuationConfirmed && visible2Letters < dialogue2letters.size() && dialogueLetterClock.getElapsedTime() >= dialogueLetterInterval) {
            visible2Letters++;
            dialogueLetterClock.restart();
        }
        dialogue2Layout.setPosition({ 110.f, 668.f });
        for (std::size_t i = 0; i < dialogue2letters.size(); i++) {
            const sf::Vector2f dialogue2NaturalPosition = dialogue2Layout.findCharacterPos(i);
            dialogue2letters[i].setPosition({ dialogue2NaturalPosition.x , dialogue2NaturalPosition.y });
            dialogue2letters[i].setFillColor(sf::Color(255, 255, 255));
            dialogue2letters[i].setOutlineColor(sf::Color(0, 0, 0));
        }
        if (visible2Letters == dialogue2letters.size() - 1) {
            continuation2Available = true;
        }

        //RobotMenu Animation
        
        

        //DISPLAY
        window.clear(sf::Color::Black); //otherwise, if its open, we have a black screen;

        if (gameState == GameState::Intro) {
            window.draw(cathedralSprite);
            window.draw(cathedralTitle);
            window.draw(paragraphOne);
            window.draw(paragraphTwo);
            for (const auto& letter : theLetters) {
                window.draw(letter);
            }
            for (const auto& letter : machineryLetters) {
                window.draw(letter);
            }
            window.draw(decisionBackground);
            if (chestAnimationStarted) {
                window.draw(chestSprite);
            }
            else {
                window.draw(acceptText);
                window.draw(declineText);
            }
        }
        else if (gameState == GameState::MainMenu) {
            mainMenu.draw(window);
            dialogueBox.draw(window);
            if (!continuationConfirmed) {
                for (std::size_t i = 0; i < visibleLetters; i++) {
                    window.draw(dialogue1Letters[i]);
                }
                if (continuationAvailable) {
                    window.draw(arrowSprite);
                }
            }
            else {
                for (std::size_t i = 0; i < visible2Letters; i++) {
                    window.draw(dialogue2letters[i]);
                }
                if (continuation2Available) {
                    window.draw(arrowSprite);
                    if (continuation2Confirmed) {
                        mainMenu.draw(window);
                    }
                }
            }
        }
                
        else if (gameState == GameState::RobotMenu) {
            if(customizationDecision==1)
                robotMenuQuadruple.drawQuadruple(window);
            if(customizationDecision==2)
                robotMenuBiped.drawBiped(window);
            if(customizationDecision==3)
                robotMenuWheels.drawWheels(window);
        }
        else if (gameState == GameState::ShopMenu) {
            shopMenu.draw(window);
        }
        window.display();  
    }
       
}
