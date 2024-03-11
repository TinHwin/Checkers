// "Copyright [2023] <Truong-Thinh Huynh>"

#include <iostream>
#include <vector>

#include "Checkers.hpp"

Checkers::Checkers() {
  selectedPiecePosX = 0;
  selectedPiecePosY = 0;
  whichPlayer = false;

  this->loadTexture();
}

Checkers::~Checkers() {}

void Checkers::loadTexture() {
  if (!redPawn.loadFromFile("./redpawn.png")) {
    std::cerr << "redPawn's texture failed to load." << std::endl;
  }

  if (!redKing.loadFromFile("./redking.png")) {
    std::cerr << "redKing's texture failed to load." << std::endl;
  }

  if (!blackPawn.loadFromFile("./blackpawn.png")) {
    std::cerr << "blackPawn's texture failed to load." << std::endl;
  }

  if (!blackKing.loadFromFile("./blackking.png")) {
    std::cerr << "blackKing's texture failed to load." << std::endl;
  }

  if (!frame.loadFromFile("./frame.png")) {
    std::cerr << "frame's texture failed to load." << std::endl;
  }
}

void Checkers::loadSprite() {
  for (size_t i = 0; i < checkersGrid.size(); i++) {
    std::string checkersRow = checkersGrid[i];

    for (size_t j = 0; j < checkersRow.size(); j++) {
      if (checkersRow[j] == 'b') {
        sf::Sprite blackPawnSprite;
        blackPawnSprite.setTexture(blackPawn);
        blackPawnSprite.setPosition(j * 64, i * 64);

        blackPawnPieces.push_back(blackPawnSprite);
      } else if (checkersRow[j] == 'r') {
        sf::Sprite redPawnSprite;
        redPawnSprite.setTexture(redPawn);
        redPawnSprite.setPosition(j * 64, i * 64);

        redPawnPieces.push_back(redPawnSprite);
      } else if (checkersRow[j] == 'B') {
        sf::Sprite blackKingSprite;
        blackKingSprite.setTexture(blackKing);
        blackKingSprite.setPosition(j * 64, i * 64);

        blackKingPieces.push_back(blackKingSprite);
      } else if (checkersRow[j] == 'R') {
        sf::Sprite redKingSprite;
        redKingSprite.setTexture(redKing);
        redKingSprite.setPosition(j * 64, i * 64);

        redKingPieces.push_back(redKingSprite);
      }
    }

    checkersRow.clear();
  }
}

void Checkers::loadBlackKing() {
  sf::Sprite blackKingSprite;

  blackKingSprite.setTexture(blackKing);
  blackKingPieces.push_back(blackKingSprite);
}

void Checkers::loadRedKing() {
  sf::Sprite redKingSprite;

  redKingSprite.setTexture(redKing);
  redKingPieces.push_back(redKingSprite);
}

void Checkers::updateSprite() {
  int bPPIndex = 0;
  int rPPIndex = 0;
  int bKPIdex = 0;
  int rKPIdex = 0;

  for (size_t i = 0; i < checkersGrid.size(); i++) {
    std::string checkersGridRow = checkersGrid.at(i);

    for (size_t j = 0; j < checkersGridRow.size(); j++) {
      if (checkersGridRow[j] == 'b') {
        blackPawnPieces.at(bPPIndex).setPosition(j * 64, i * 64);

        bPPIndex++;
      } else if (checkersGridRow[j] == 'r') {
        redPawnPieces.at(rPPIndex).setPosition(j * 64, i * 64);

        rPPIndex++;
      } else if (checkersGridRow[j] == 'B') {
        blackKingPieces.at(bKPIdex).setPosition(j * 64, i * 64);

        bKPIdex++;
      } else if (checkersGridRow[j] == 'R') {
        redKingPieces.at(rKPIdex).setPosition(j * 64, i * 64);

        rKPIdex++;
      }
    }
  }
}

void Checkers::clearCheckersGrid() {
  checkersGrid.clear();
}

void Checkers::clearPossibleMovePos() {
  possibleMovePosX.clear();
  possibleMovePosY.clear();
}

void Checkers::clearSprite() {
  blackPawnPieces.clear();
  blackKingPieces.clear();
  redPawnPieces.clear();
  redKingPieces.clear();
}

void Checkers::deleteBlackPawnPiece() {
  blackPawnPieces.pop_back();
}

void Checkers::deleteBlackKingPiece() {
  blackKingPieces.pop_back();
}

void Checkers::deleteRedPawnPiece() {
  redPawnPieces.pop_back();
}

void Checkers::deleteRedKingPiece() {
  redKingPieces.pop_back();
}

void Checkers::setCheckersGrid(std::vector<std::string> inCheckersGrid) {
  checkersGrid = inCheckersGrid;
}

void Checkers::setBackgroundGrid(std::vector<std::string> inBackgroundGrid) {
  backgroundGrid = inBackgroundGrid;
}

void Checkers::setBlackPawnPiece(sf::Sprite inBlackPawnPiece) {
  blackPawnPieces.push_back(inBlackPawnPiece);
}

void Checkers::setBlackKingPiece(sf::Sprite inBlackKingPiece) {
  blackKingPieces.push_back(inBlackKingPiece);
}

void Checkers::setRedPawnPiece(sf::Sprite inRedPawnPiece) {
  redPawnPieces.push_back(inRedPawnPiece);
}

void Checkers::setRedKingPiece(sf::Sprite inRedKingPiece) {
  redKingPieces.push_back(inRedKingPiece);
}

void Checkers::setSelectedPiecePosX(int inSelectedPiecePosX) {
  selectedPiecePosX = inSelectedPiecePosX;
}

void Checkers::setSelectedPiecePosY(int inSelectedPiecePosY) {
  selectedPiecePosY = inSelectedPiecePosY;
}

void Checkers::setWhichPlayer(bool inWhichPlayer) {
  whichPlayer = inWhichPlayer;
}

void Checkers::setPossibleMovePosX(std::vector<int> inPossibleMovePosX) {
  possibleMovePosX = inPossibleMovePosX;
}

void Checkers::setPossibleMovePosY(std::vector<int> inPossibleMovePosY) {
  possibleMovePosY = inPossibleMovePosY;
}

std::vector<std::string> Checkers::getCheckersGrid() const {
  return checkersGrid;
}

std::vector<std::string> Checkers::getBackgroundGrid() const {
  return backgroundGrid;
}

std::vector<sf::Sprite> Checkers::getBlackPawnPieces() const {
  return blackPawnPieces;
}

std::vector<sf::Sprite> Checkers::getBlackKingPieces() const {
  return blackKingPieces;
}

std::vector<sf::Sprite> Checkers::getRedPawnPieces() const {
  return redPawnPieces;
}

std::vector<sf::Sprite> Checkers::getRedKingPieces() const {
  return redKingPieces;
}

int Checkers::getSelectedPiecePosX() const {
  return selectedPiecePosX;
}

int Checkers::getSelectedPiecePosY() const {
  return selectedPiecePosY;
}

bool Checkers::getWhichPlayer() const {
  return whichPlayer;
}

std::vector<int> Checkers::getPossibleMovePosX() const {
  return possibleMovePosX;
}

std::vector<int> Checkers::getPossibleMovePosY() const {
  return possibleMovePosY;
}

void Checkers::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (int i = 0; i < 10; i++) {  // Column
    for (int j = 0; j < 10; j++) {  // Row
      if (i == 0 || i == 9) {
        sf::Sprite frameSprite;
        frameSprite.setTexture(frame);
        frameSprite.setPosition(j * 64, i * 64);
        frameSprite.setColor(sf::Color::Red);

        if (j % 2 == 1) {
          frameSprite.setTextureRect(sf::IntRect(64, 0, -64, 64));
        }

        target.draw(frameSprite);
      } else if (j == 0 || j == 9) {
        sf::Sprite frameSprite;
        frameSprite.setTexture(frame);
        frameSprite.setPosition(j * 64, i * 64);
        frameSprite.setColor(sf::Color::Red);

        if (j == 9) {
          frameSprite.setTextureRect(sf::IntRect(64, 0, -64, 64));
        }

        target.draw(frameSprite);
      } else {
        sf::RectangleShape tile;
        tile.setSize(sf::Vector2f(64.f, 64.f));
        tile.setPosition(sf::Vector2f(j * 64, i * 64));

        bool selectedTile = false;

        if (selectedPiecePosX == tile.getPosition().x) {
          if (selectedPiecePosY == tile.getPosition().y) {
            selectedTile = true;
          }
        }

        if (j % 2 == 1) {
          if ((i % 2 == 1) && (selectedTile != true)) {
            tile.setFillColor(sf::Color::Red);
          } else {
            tile.setFillColor(sf::Color::Black);
          }
        } else {
          if ((i % 2 == 0) && (selectedTile != true)) {
            tile.setFillColor(sf::Color::Red);
          } else {
            tile.setFillColor(sf::Color::Black);
          }
        }

        // Highlight the selected piece.
        if (selectedTile == true) {
          tile.setFillColor(sf::Color::Yellow);
        }

        target.draw(tile);
      }
    }
  }

  for (size_t i = 0; i < blackPawnPieces.size(); i++) {
    target.draw(blackPawnPieces[i]);
  }

  for (size_t i = 0; i < redPawnPieces.size(); i++) {
    target.draw(redPawnPieces[i]);
  }

  for (size_t i = 0; i < blackKingPieces.size(); i++) {
    target.draw(blackKingPieces[i]);
  }

  for (size_t i = 0; i < redKingPieces.size(); i++) {
    target.draw(redKingPieces[i]);
  }
}

std::ostream& operator<< (std::ostream& out, Checkers& inCheckers) {
  std::vector<std::string> checkersGridTemp =  inCheckers.getCheckersGrid();

  for (size_t i = 0; i < checkersGridTemp.size(); i++) {
    std::string checkersRowTemp = checkersGridTemp[i];

    for (size_t j = 0; j < checkersRowTemp.size(); j++) {
      out << checkersRowTemp[j];
    }

    checkersRowTemp.clear();

    out << std::endl;
  }

  out << std::endl;

  return out;
}
