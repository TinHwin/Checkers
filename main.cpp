// "Copyright [2023] <Truong-Thinh Huynh>"

#include <iostream>
#include <algorithm>

#include "Checkers.hpp"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
  Checkers checkers;

  sf::RenderWindow window(sf::VideoMode(10 * 64, 10 * 64), "Checkers");

  std::vector<std::string> checkersGrid;

  // Set up starting checkers
  for (int i = 0; i < 10; i++) {  // Column
    std::string checkersRow;

    for (int j = 0; j < 10; j++) {  // Row
      if (i == 0 || i == 9) { checkersRow.push_back('*');
      } else if (j == 0 || j == 9) { checkersRow.push_back('*');
      } else {
        if (i == 1 || i == 3) {
          if (j % 2 == 0) { checkersRow.push_back('b');
          } else { checkersRow.push_back('.');
          }
        } else if (i == 2) {
          if (j % 2 == 1) { checkersRow.push_back('b');
          } else { checkersRow.push_back('.');
          }
        } else if (i == 6 || i == 8) {
          if (j % 2 == 1) { checkersRow.push_back('r');
          } else { checkersRow.push_back('.');
          }
        } else if (i == 7) {
          if (j % 2 == 0) { checkersRow.push_back('r');
          } else { checkersRow.push_back('.'); }
        } else { checkersRow.push_back('.'); }
      }
    }

    checkersGrid.push_back(checkersRow); checkersRow.clear();
  }

  checkers.setCheckersGrid(checkersGrid); checkers.loadSprite();

  sf::Font font;

  if (!font.loadFromFile("./Aller_Rg.ttf")) {
    std::cerr << "Aller_Rg.ttf failed to load." << std::endl;
  }

  // Setting up the text displaying the turn of which player.
  sf::Text text; text.setFont(font); text.setCharacterSize(32);
  text.setFillColor(sf::Color::White);
  text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
  text.setPosition(window.getSize().x / 2.f, 32); text.setString("Player Black Turn.");

  bool isMove = true; bool isWon = false;
  bool lOBlackPieces = false; bool lORedPieces = false;

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) { window.close(); }

      if ((event.type == sf::Event::MouseButtonPressed) && (isWon == false)) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2i mousePos = sf::Mouse::getPosition(window);

          int mousePosX = mousePos.x / 64; int mousePosY = mousePos.y / 64;

          // Let the pieces move after being selected
          if (isMove == false) {
            if (checkers.getWhichPlayer() == false) {
              int currPosX = checkers.getSelectedPiecePosX() / 64;
              int currPosY = checkers.getSelectedPiecePosY() / 64;

              std::vector<std::string> checkersGrid = checkers.getCheckersGrid();

              char checkBP = checkersGrid.at(currPosY)[currPosX];

              if (mousePosY == (currPosY + 1)) {
                if (mousePosX == (currPosX - 1)) {
                  std::string cGRow = checkersGrid.at(currPosY + 1);

                  if (cGRow[currPosX - 1] == '.') {
                    std::string newCurrCGRow = checkersGrid[currPosY];
                    std::string newCGRow = cGRow;

                    newCurrCGRow[currPosX] = '.';

                    if (((currPosY + 1) == 8) && (checkBP == 'b')) {
                      checkers.deleteBlackPawnPiece();
                      checkers.loadBlackKing();

                      newCGRow[currPosX - 1] = 'B';
                    } else if (((currPosY + 1) != 8) && (checkBP == 'b')) {
                      newCGRow[currPosX - 1] = 'b';
                    } else {
                      newCGRow[currPosX - 1] = 'B';
                    }

                    std::vector<std::string> newCG = checkersGrid;

                    newCG[currPosY] = newCurrCGRow; newCG[currPosY + 1] = newCGRow;

                    checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                    checkers.updateSprite(); checkers.setWhichPlayer(true);

                    isMove = true;
                  }
                } else if (mousePosX ==  (currPosX + 1)) {
                  std::string cGRow = checkersGrid.at(currPosY + 1);

                  if (cGRow[currPosX + 1] == '.') {
                    std::string newCurrCGRow = checkersGrid[currPosY];
                    std::string newCGRow = cGRow;

                    newCurrCGRow[currPosX] = '.';

                    if (((currPosY + 1) == 8) && (checkBP == 'b')) {
                      checkers.deleteBlackPawnPiece(); checkers.loadBlackKing();

                      newCGRow[currPosX + 1] = 'B';
                    } else if (((currPosY + 1) != 8) && (checkBP == 'b')) {
                      newCGRow[currPosX + 1] = 'b';
                    } else {
                      newCGRow[currPosX + 1] = 'B';
                    }

                    std::vector<std::string> newCG = checkersGrid;

                    newCG[currPosY] = newCurrCGRow; newCG[currPosY + 1] = newCGRow;

                    checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                    checkers.updateSprite(); checkers.setWhichPlayer(true);

                    isMove = true;
                  }
                }
              } else if (mousePosY == (currPosY + 2)) {
                if (mousePosX == (currPosX - 2)) {
                  std::string cGRowOne = checkersGrid.at(currPosY + 1);
                  std::string cGrowTwo = checkersGrid.at(currPosY + 2);

                  if (cGrowTwo[currPosX - 2] == '.') {
                    if ((cGRowOne[currPosX - 1] == 'r') || (cGRowOne[currPosX - 1] == 'R')) {
                      std::string newCurrCGRow = checkersGrid[currPosY];
                      std::string newCGRowOne = cGRowOne; std::string newCGRowTwo = cGrowTwo;

                      newCurrCGRow[currPosX] = '.'; newCGRowOne[currPosX - 1] = '.';

                      if (((currPosY + 2) == 8) && (checkBP == 'b')) {
                        checkers.deleteBlackPawnPiece(); checkers.loadBlackKing();

                        newCGRowTwo[currPosX - 2] = 'B';
                      } else if (((currPosY + 2) != 8) && (checkBP == 'b')) {
                        newCGRowTwo[currPosX - 2] = 'b';
                      } else {
                        newCGRowTwo[currPosX - 2] = 'B';
                      }

                      std::vector<std::string> newCG = checkersGrid;

                      newCG[currPosY] = newCurrCGRow; newCG[currPosY + 1] = newCGRowOne;
                      newCG[currPosY + 2] = newCGRowTwo;

                      checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                      checkers.updateSprite(); checkers.setWhichPlayer(true);

                      if (cGRowOne[currPosX - 1] == 'r') {
                        checkers.deleteRedPawnPiece();
                      } else {
                        checkers.deleteRedKingPiece();
                      }

                      isMove = true;
                    }
                  }
                } else if (mousePosX == (currPosX + 2)) {
                  std::string cGRowOne = checkersGrid.at(currPosY + 1);
                  std::string cGrowTwo = checkersGrid.at(currPosY + 2);

                  if (cGrowTwo[currPosX + 2] == '.') {
                    if ((cGRowOne[currPosX + 1] == 'r') || (cGRowOne[currPosX + 1] == 'R')) {
                      std::string newCurrCGRow = checkersGrid[currPosY];
                      std::string newCGRowOne = cGRowOne; std::string newCGRowTwo = cGrowTwo;

                      newCurrCGRow[currPosX] = '.'; newCGRowOne[currPosX + 1] = '.';

                      if (((currPosY + 2) == 8) && (checkBP == 'b')) {
                        checkers.deleteBlackPawnPiece(); checkers.loadBlackKing();

                        newCGRowTwo[currPosX + 2] = 'B';
                      } else if (((currPosY + 2) != 8) && (checkBP == 'b')) {
                        newCGRowTwo[currPosX + 2] = 'b';
                      } else {
                        newCGRowTwo[currPosX + 2] = 'B';
                      }

                      std::vector<std::string> newCG = checkersGrid;

                      newCG[currPosY] = newCurrCGRow; newCG[currPosY + 1] = newCGRowOne;
                      newCG[currPosY + 2] = newCGRowTwo;

                      checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                      checkers.updateSprite(); checkers.setWhichPlayer(true);

                      if (cGRowOne[currPosX + 1] == 'r') {
                        checkers.deleteRedPawnPiece();
                      } else {
                        checkers.deleteRedKingPiece();
                      }

                      isMove = true;
                    }
                  }
                }
              } else if ((mousePosY == (currPosY - 1)) && (checkBP == 'B')) {
                if (mousePosX == (currPosX - 1)) {
                  std::string cGRow = checkersGrid.at(currPosY - 1);

                  if (cGRow[currPosX - 1] == '.') {
                    std::string newCurrCGRow = checkersGrid[currPosY];
                    std::string newCGRow = cGRow;

                    newCurrCGRow[currPosX] = '.'; newCGRow[currPosX - 1] = 'B';

                    std::vector<std::string> newCG = checkersGrid;

                    newCG[currPosY] = newCurrCGRow; newCG[currPosY - 1] = newCGRow;

                    checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                    checkers.updateSprite(); checkers.setWhichPlayer(true);

                    isMove = true;
                  }
                } else if (mousePosX ==  (currPosX + 1)) {
                  std::string cGRow = checkersGrid.at(currPosY - 1);

                  if (cGRow[currPosX + 1] == '.') {
                    std::string newCurrCGRow = checkersGrid[currPosY];
                    std::string newCGRow = cGRow;

                    newCurrCGRow[currPosX] = '.'; newCGRow[currPosX + 1] = 'B';

                    std::vector<std::string> newCG = checkersGrid;

                    newCG[currPosY] = newCurrCGRow; newCG[currPosY - 1] = newCGRow;

                    checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                    checkers.updateSprite(); checkers.setWhichPlayer(true);

                    isMove = true;
                  }
                }
              } else if ((mousePosY == (currPosY - 2)) && (checkBP == 'B')) {
                if (mousePosX == (currPosX - 2)) {
                  std::string cGRowOne = checkersGrid.at(currPosY - 1);
                  std::string cGrowTwo = checkersGrid.at(currPosY - 2);

                  if (cGrowTwo[currPosX - 2] == '.') {
                    if ((cGRowOne[currPosX - 1] == 'r') || (cGRowOne[currPosX - 1] == 'R')) {
                      std::string newCurrCGRow = checkersGrid[currPosY];
                      std::string newCGRowOne = cGRowOne; std::string newCGRowTwo = cGrowTwo;

                      newCurrCGRow[currPosX] = '.'; newCGRowOne[currPosX - 1] = '.';
                      newCGRowTwo[currPosX - 2] = 'B';

                      std::vector<std::string> newCG = checkersGrid;

                      newCG[currPosY] = newCurrCGRow; newCG[currPosY - 1] = newCGRowOne;
                      newCG[currPosY - 2] = newCGRowTwo;

                      checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                      checkers.updateSprite(); checkers.setWhichPlayer(true);

                      if (cGRowOne[currPosX - 1] == 'r') {
                        checkers.deleteRedPawnPiece();
                      } else {
                        checkers.deleteRedKingPiece();
                      }

                      isMove = true;
                    }
                  }
                } else if (mousePosX == (currPosX + 2)) {
                  std::string cGRowOne = checkersGrid.at(currPosY - 1);
                  std::string cGrowTwo = checkersGrid.at(currPosY - 2);

                  if (cGrowTwo[currPosX + 2] == '.') {
                    if ((cGRowOne[currPosX + 1] == 'r') || (cGRowOne[currPosX + 1] == 'R')) {
                      std::string newCurrCGRow = checkersGrid[currPosY];
                      std::string newCGRowOne = cGRowOne; std::string newCGRowTwo = cGrowTwo;

                      newCurrCGRow[currPosX] = '.'; newCGRowOne[currPosX + 1] = '.';
                      newCGRowTwo[currPosX + 2] = 'B';

                      std::vector<std::string> newCG = checkersGrid;

                      newCG[currPosY] = newCurrCGRow; newCG[currPosY - 1] = newCGRowOne;
                      newCG[currPosY - 2] = newCGRowTwo;

                      checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                      checkers.updateSprite(); checkers.setWhichPlayer(true);

                      if (cGRowOne[currPosX + 1] == 'r') {
                        checkers.deleteRedPawnPiece();
                      } else {
                        checkers.deleteRedKingPiece();
                      }

                      isMove = true;
                    }
                  }
                }
              }
            } else {
              int currPosX = checkers.getSelectedPiecePosX() / 64;
              int currPosY = checkers.getSelectedPiecePosY() / 64;

              std::vector<std::string> checkersGrid = checkers.getCheckersGrid();

              char checkBP = checkersGrid.at(currPosY)[currPosX];

              if (mousePosY == (currPosY - 1)) {
                if (mousePosX == (currPosX - 1)) {
                  std::string cGRow = checkersGrid.at(currPosY - 1);

                  if (cGRow[currPosX - 1] == '.') {
                    std::string newCurrCGRow = checkersGrid[currPosY];
                    std::string newCGRow = cGRow;

                    newCurrCGRow[currPosX] = '.';

                    if (((currPosY - 1) == 1) && (checkBP == 'r')) {
                      checkers.deleteRedPawnPiece(); checkers.loadRedKing();

                      newCGRow[currPosX - 1] = 'R';
                    } else if (((currPosY - 1) != 1) && (checkBP == 'r')) {
                      newCGRow[currPosX - 1] = 'r';
                    } else {
                      newCGRow[currPosX - 1] = 'R';
                    }

                    std::vector<std::string> newCG = checkersGrid;

                    newCG[currPosY] = newCurrCGRow; newCG[currPosY - 1] = newCGRow;

                    checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                    checkers.updateSprite(); checkers.setWhichPlayer(false); isMove = true;
                  }
                } else if (mousePosX == (currPosX + 1)) {
                  std::string cGRow = checkersGrid.at(currPosY - 1);

                  if (cGRow[currPosX + 1] == '.') {
                    std::string newCurrCGRow = checkersGrid[currPosY];
                    std::string newCGRow = cGRow;

                    newCurrCGRow[currPosX] = '.';

                    if (((currPosY - 1) == 1) && (checkBP == 'r')) {
                      checkers.deleteRedPawnPiece(); checkers.loadRedKing();

                      newCGRow[currPosX + 1] = 'R';
                    } else if (((currPosY - 1) != 1) && (checkBP == 'r')) {
                      newCGRow[currPosX + 1] = 'r';
                    } else {
                      newCGRow[currPosX + 1] = 'R';
                    }

                    std::vector<std::string> newCG = checkersGrid;

                    newCG[currPosY] = newCurrCGRow; newCG[currPosY - 1] = newCGRow;

                    checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                    checkers.updateSprite(); checkers.setWhichPlayer(false);

                    isMove = true;
                  }
                }
              } else if (mousePosY == (currPosY - 2)) {
                if (mousePosX == (currPosX - 2)) {
                  std::string cGRowOne = checkersGrid.at(currPosY - 1);
                  std::string cGrowTwo = checkersGrid.at(currPosY - 2);

                  if (cGrowTwo[currPosX - 2] == '.') {
                    if ((cGRowOne[currPosX - 1] == 'b') || (cGRowOne[currPosX - 1] == 'B')) {
                      std::string newCurrCGRow = checkersGrid[currPosY];
                      std::string newCGRowOne = cGRowOne; std::string newCGRowTwo = cGrowTwo;

                      newCurrCGRow[currPosX] = '.'; newCGRowOne[currPosX - 1] = '.';

                      if (((currPosY - 2) == 1) && (checkBP = 'r')) {
                        checkers.deleteRedPawnPiece(); checkers.loadRedKing();

                        newCGRowTwo[currPosX - 2] = 'R';
                      } else if (((currPosY - 2) != 1) && (checkBP = 'r')) {
                        newCGRowTwo[currPosX - 2] = 'r';
                      } else {
                        newCGRowTwo[currPosX - 2] = 'R';
                      }

                      std::vector<std::string> newCG = checkersGrid;

                      newCG[currPosY] = newCurrCGRow; newCG[currPosY - 1] = newCGRowOne;
                      newCG[currPosY - 2] = newCGRowTwo;

                      checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                      checkers.updateSprite(); checkers.setWhichPlayer(false);

                      if (cGRowOne[currPosX - 1] == 'b') {
                        checkers.deleteBlackPawnPiece();
                      } else {
                        checkers.deleteBlackKingPiece();
                      }

                      isMove = true;
                    }
                  }
                } else if (mousePosX == (currPosX + 2)) {
                  std::string cGRowOne = checkersGrid.at(currPosY - 1);
                  std::string cGrowTwo = checkersGrid.at(currPosY - 2);

                  if (cGrowTwo[currPosX + 2] == '.') {
                    if ((cGRowOne[currPosX + 1] == 'b') || (cGRowOne[currPosX + 1] == 'B')) {
                      std::string newCurrCGRow = checkersGrid[currPosY];
                      std::string newCGRowOne = cGRowOne; std::string newCGRowTwo = cGrowTwo;

                      newCurrCGRow[currPosX] = '.'; newCGRowOne[currPosX + 1] = '.';

                      if (((currPosY - 2) == 1) && (checkBP == 'r')) {
                        checkers.deleteRedPawnPiece(); checkers.loadRedKing();

                        newCGRowTwo[currPosX + 2] = 'R';
                      } else if (((currPosY - 2) != 1) && (checkBP == 'r')) {
                        newCGRowTwo[currPosX + 2] = 'r';
                      } else {
                        newCGRowTwo[currPosX + 2] = 'R';
                      }

                      std::vector<std::string> newCG = checkersGrid;

                      newCG[currPosY] = newCurrCGRow; newCG[currPosY - 1] = newCGRowOne;
                      newCG[currPosY - 2] = newCGRowTwo;

                      checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                      checkers.updateSprite(); checkers.setWhichPlayer(false);

                      if (cGRowOne[currPosX + 1] == 'b') {
                        checkers.deleteBlackPawnPiece();
                      } else {
                        checkers.deleteBlackKingPiece();
                      }

                      isMove = true;
                    }
                  }
                }
              } else if ((mousePosY == (currPosY + 1)) && (checkBP == 'R')) {
                if (mousePosX == (currPosX - 1)) {
                  std::string cGRow = checkersGrid.at(currPosY + 1);

                  if (cGRow[currPosX - 1] == '.') {
                    std::string newCurrCGRow = checkersGrid[currPosY];
                    std::string newCGRow = cGRow;

                    newCurrCGRow[currPosX] = '.'; newCGRow[currPosX - 1] = 'R';

                    std::vector<std::string> newCG = checkersGrid;

                    newCG[currPosY] = newCurrCGRow; newCG[currPosY + 1] = newCGRow;

                    checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                    checkers.updateSprite(); checkers.setWhichPlayer(false);

                    isMove = true;
                  }
                } else if (mousePosX ==  (currPosX + 1)) {
                  std::string cGRow = checkersGrid.at(currPosY + 1);

                  if (cGRow[currPosX + 1] == '.') {
                    std::string newCurrCGRow = checkersGrid[currPosY];
                    std::string newCGRow = cGRow;

                    newCurrCGRow[currPosX] = '.'; newCGRow[currPosX + 1] = 'R';

                    std::vector<std::string> newCG = checkersGrid;

                    newCG[currPosY] = newCurrCGRow; newCG[currPosY + 1] = newCGRow;

                    checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                    checkers.updateSprite(); checkers.setWhichPlayer(false); isMove = true;
                  }
                }
              } else if ((mousePosY == (currPosY + 2)) && (checkBP == 'R')) {
                if (mousePosX == (currPosX - 2)) {
                  std::string cGRowOne = checkersGrid.at(currPosY + 1);
                  std::string cGrowTwo = checkersGrid.at(currPosY + 2);

                  if (cGrowTwo[currPosX - 2] == '.') {
                    if ((cGRowOne[currPosX - 1] == 'b') || (cGRowOne[currPosX - 1] == 'B')) {
                      std::string newCurrCGRow = checkersGrid[currPosY];
                      std::string newCGRowOne = cGRowOne; std::string newCGRowTwo = cGrowTwo;

                      newCurrCGRow[currPosX] = '.'; newCGRowOne[currPosX - 1] = '.';
                      newCGRowTwo[currPosX - 2] = 'R';

                      std::vector<std::string> newCG = checkersGrid;

                      newCG[currPosY] = newCurrCGRow; newCG[currPosY - 1] = newCGRowOne;
                      newCG[currPosY - 2] = newCGRowTwo;

                      checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                      checkers.updateSprite(); checkers.setWhichPlayer(false);

                      if (cGRowOne[currPosX - 1] == 'r') {
                        checkers.deleteBlackPawnPiece();
                      } else {
                        checkers.deleteBlackKingPiece();
                      }

                      isMove = true;
                    }
                  }
                } else if (mousePosX == (currPosX + 2)) {
                  std::string cGRowOne = checkersGrid.at(currPosY + 1);
                  std::string cGrowTwo = checkersGrid.at(currPosY + 2);

                  if (cGrowTwo[currPosX + 2] == '.') {
                    if ((cGRowOne[currPosX + 1] == 'b') || (cGRowOne[currPosX + 1] == 'B')) {
                      std::string newCurrCGRow = checkersGrid[currPosY];
                      std::string newCGRowOne = cGRowOne; std::string newCGRowTwo = cGrowTwo;

                      newCurrCGRow[currPosX] = '.'; newCGRowOne[currPosX + 1] = '.';
                      newCGRowTwo[currPosX + 2] = 'R';

                      std::vector<std::string> newCG = checkersGrid;

                      newCG[currPosY] = newCurrCGRow; newCG[currPosY + 1] = newCGRowOne;
                      newCG[currPosY + 2] = newCGRowTwo;

                      checkers.clearCheckersGrid(); checkers.setCheckersGrid(newCG);
                      checkers.updateSprite(); checkers.setWhichPlayer(false);

                      if (cGRowOne[currPosX + 1] == 'r') {
                        checkers.deleteBlackPawnPiece();
                      } else {
                        checkers.deleteBlackKingPiece();
                      }

                      isMove = true;
                    }
                  }
                }
              }
            }
          } else {
            if (checkers.getWhichPlayer() == false) {
              std::vector<sf::Sprite> blackPawnPieces = checkers.getBlackPawnPieces();

              for (size_t i = 0; i < blackPawnPieces.size(); i++) {
                bool lhsX = mousePos.x >= blackPawnPieces[i].getPosition().x;
                bool rhsX = mousePos.x <= blackPawnPieces[i].getPosition().x + 64;

                if (lhsX && rhsX) {
                  bool lhsY = mousePos.y >= blackPawnPieces[i].getPosition().y;
                  bool rhsY = mousePos.y <= blackPawnPieces[i].getPosition().y + 64;

                  if (lhsY && rhsY) {
                    checkers.setSelectedPiecePosX(blackPawnPieces[i].getPosition().x);
                    checkers.setSelectedPiecePosY(blackPawnPieces[i].getPosition().y);

                    isMove = false;
                  }
                }
              }

              std::vector<sf::Sprite> blackKingPieces = checkers.getBlackKingPieces();

              for (size_t i = 0; i < blackKingPieces.size(); i++) {
                bool lhsX = mousePos.x >= blackKingPieces[i].getPosition().x;
                bool rhsX = mousePos.x <= blackKingPieces[i].getPosition().x + 64;

                if (lhsX && rhsX) {
                  bool lhsY = mousePos.y >= blackKingPieces[i].getPosition().y;
                  bool rhsY = mousePos.y <= blackKingPieces[i].getPosition().y + 64;

                  if (lhsY && rhsY) {
                    checkers.setSelectedPiecePosX(blackKingPieces[i].getPosition().x);
                    checkers.setSelectedPiecePosY(blackKingPieces[i].getPosition().y);

                    isMove = false;
                  }
                }
              }
            } else {
              std::vector<sf::Sprite> redPawnPieces = checkers.getRedPawnPieces();

              for (size_t i = 0; i < redPawnPieces.size(); i++) {
                bool lhsX = mousePos.x >= redPawnPieces[i].getPosition().x;
                bool rhsX = mousePos.x <= redPawnPieces[i].getPosition().x + 64;

                if (lhsX && rhsX) {
                  bool lhsY = mousePos.y >= redPawnPieces[i].getPosition().y;
                  bool rhsY = mousePos.y <= redPawnPieces[i].getPosition().y + 64;

                  if (lhsY && rhsY) {
                    checkers.setSelectedPiecePosX(redPawnPieces[i].getPosition().x);
                    checkers.setSelectedPiecePosY(redPawnPieces[i].getPosition().y);

                    isMove = false;
                  }
                }
              }

              std::vector<sf::Sprite> redKingPieces = checkers.getRedKingPieces();

              for (size_t i = 0; i < redKingPieces.size(); i++) {
                bool lhsX = mousePos.x >= redKingPieces[i].getPosition().x;
                bool rhsX = mousePos.x <= redKingPieces[i].getPosition().x + 64;

                if (lhsX && rhsX) {
                  bool lhsY = mousePos.y >= redKingPieces[i].getPosition().y;
                  bool rhsY = mousePos.y <= redKingPieces[i].getPosition().y + 64;

                  if (lhsY && rhsY) {
                    checkers.setSelectedPiecePosX(redKingPieces[i].getPosition().x);
                    checkers.setSelectedPiecePosY(redKingPieces[i].getPosition().y);

                    isMove = false;
                  }
                }
              }
            }
          }
        }
      }
    }

    text.setFont(font); text.setCharacterSize(32); text.setFillColor(sf::Color::White);
    text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
    text.setPosition(window.getSize().x / 2.f, 32);

    std::vector<std::string> checkersGridTemp = checkers.getCheckersGrid();

    for (size_t i = 0; i < checkersGridTemp.size(); i++) {
      std::string checkersGridRowTemp = checkersGridTemp[i];

      // Use algorithm function any_of and parameter lambda to determine if a player win or not
      if (std::any_of(checkersGridRowTemp.begin(), checkersGridRowTemp.end(), [](char i)
      { return i == 'b' || i == 'B'; })) { lOBlackPieces = true;
      }

      if (std::any_of(checkersGridRowTemp.begin(), checkersGridRowTemp.end(), [](char i)
      { return i == 'r' || i == 'R'; })) {  lORedPieces = true;
      }

      /*
      for (size_t j = 0; j < checkersGridRowTemp.size(); j++) {
        if (checkersGridRowTemp[j] == 'b' || checkersGridRowTemp[j] == 'B') {
          lOBlackPieces = true;
        } else if (checkersGridRowTemp[j] == 'r' || checkersGridRowTemp[j] == 'R') {
          lORedPieces = true;
        }
      }
      */
    }

    // If neither player win, then switch player
    if (lOBlackPieces == false) {
      text.setString("Player Red Win."); isWon = true;
    } else if (lORedPieces == false) {
      text.setString("Player Black Win."); isWon = true;
    }

    lOBlackPieces = false; lORedPieces = false;

    if ((checkers.getWhichPlayer() == false) && (isWon == false)) {
      text.setString("Player Black Turn.");
    } else if ((checkers.getWhichPlayer() == true) && (isWon == false)) {
      text.setString("Player Red Turn.");
    }

    window.clear(); window.draw(checkers); window.draw(text); window.display();
  }

  return 0;
}
