// "Copyright [2023] <Truong-Thinh Huynh>"

#include <string>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#pragma once

class Checkers: public sf::Drawable {
 public:
  // Default Constructor
  Checkers();

  // Destructor
  virtual ~Checkers();

  // Loaders
  void loadTexture();
  void loadSprite();
  void loadBlackKing();
  void loadRedKing();

  // Updaters
  void updateSprite();

  // Clearors
  void clearCheckersGrid();
  void clearPossibleMovePos();
  void clearSprite();

  // Deletors
  void deleteBlackPawnPiece();
  void deleteBlackKingPiece();
  void deleteRedPawnPiece();
  void deleteRedKingPiece();

  // Mutators
  void setCheckersGrid(std::vector<std::string>);
  void setBackgroundGrid(std::vector<std::string>);
  void setBlackPawnPiece(sf::Sprite);
  void setBlackKingPiece(sf::Sprite);
  void setRedPawnPiece(sf::Sprite);
  void setRedKingPiece(sf::Sprite);
  void setSelectedPiecePosX(int);
  void setSelectedPiecePosY(int);
  void setWhichPlayer(bool);
  void setPossibleMovePosX(std::vector<int>);
  void setPossibleMovePosY(std::vector<int>);

  // Accessors
  std::vector<std::string> getCheckersGrid() const;
  std::vector<std::string> getBackgroundGrid() const;
  std::vector<sf::Sprite> getBlackPawnPieces() const;
  std::vector<sf::Sprite> getBlackKingPieces() const;
  std::vector<sf::Sprite> getRedPawnPieces() const;
  std::vector<sf::Sprite> getRedKingPieces() const;
  int getSelectedPiecePosX() const;
  int getSelectedPiecePosY() const;
  bool getWhichPlayer() const;
  std::vector<int> getPossibleMovePosX() const;
  std::vector<int> getPossibleMovePosY() const;

 private:
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

  // Textures
  sf::Texture redPawn;
  sf::Texture redKing;
  sf::Texture blackPawn;
  sf::Texture blackKing;
  sf::Texture frame;

  std::vector<std::string> checkersGrid;
  std::vector<std::string> backgroundGrid;
  std::vector<sf::Sprite> blackPawnPieces;
  std::vector<sf::Sprite> blackKingPieces;
  std::vector<sf::Sprite> redPawnPieces;
  std::vector<sf::Sprite> redKingPieces;

  // X and Y Pos. of selected piece.
  int selectedPiecePosX;
  int selectedPiecePosY;

  std::vector<int> possibleMovePosX;
  std::vector<int> possibleMovePosY;

  // 0 for Black and 1 for Red
  bool whichPlayer;
};

// Debugging
std::ostream& operator<< (std::ostream&, Checkers&);
