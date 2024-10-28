#pragma once
namespace chess {
	class Piece {
	public:
		//constructor
		Piece( std::pair<char, int> pos, char name ) {
			if (bValid( pos )) {
				this->name = name;
				this->position = pos;
				if (isupper( name ))
					this->color = 'w';
				else
					this->color = 'b';
			}
		}
		//
		//----------------------------------------------------

		virtual bool __fastcall CreateMove( std::pair<char, int> pos ) {
			if (bValid( pos )) {
				this->name = name;
				this->position = pos;
				return true;
			}
			else {
				return false;
			}
		};
		//----------------------------------------------------

		virtual bool __fastcall bValid( std::pair<char, int> pos ) const {
			char p = pos.first;
			int y = pos.second;
			return (p >= 'a' && p <= 'h' && y >= 1 && y <= 8); // not outbound
		}
		//--------------------------------------------------------------------------------------------------------

		bool __fastcall eat( std::shared_ptr<Piece>& p ) {
			if (p == nullptr) return false;
			this->position = p->position;
			p.reset();
			return true;
		}
		//--------------------------------------------------------------------------------------------------------

		char name, color;
		std::pair<char, int> position;
		sf::Sprite sprite;
	};
	//  Pawn (Peão)
	class Pawn : public chess::Piece {
	public:
		Pawn( std::pair<char, int> pos, char name ) : Piece( pos, name ) {
		}

		// this funct progress the pawn
		//---------------------------------------------------------
		bool __fastcall promote( char type ) {
			if (std::find( pieces.begin(), pieces.end(), type ) == pieces.end()) return false;
			if (!((this->position.second == 8 && this->color == 'w') || (this->position.second == 1 && this->color == 'b'))) return false;

			this->name = type;
			return true;
		}
		//---------------------------------------------------------
		bool __fastcall bValid( std::pair<char, int> nPos ) const override {
			//if (Gamestatus == 1) return true;

			if (!Piece::bValid( nPos )) return false;

			int direction = (color == 'w') ? 1 : -1; // up or down
			int startY = (color == 'w') ? 2 : 7;

			if (nPos.first == position.first) {
				if (nPos.second == position.second + direction) return true; // 1 casa
				if (position.second == startY && nPos.second == position.second + 2 * direction) return true; // 2 casas
			}

			if (abs( nPos.first - position.first ) == 1 && nPos.second == position.second + direction) {
				return true;
			}
			return false;
		}
		//---------------------------------------------------------

		bool __fastcall CreateMove( std::pair<char, int> nPos ) override {
			if (bValid( nPos )) {
				this->position = nPos;
				return true;
			}
			if (isupper( this->name ))
				this->color = 'w';
			else
				this->color = 'b';
			return false;
		}
	};

	//  Knight (Cavaleiro)
	class Knight : public chess::Piece {
	public:
		Knight( std::pair<char, int> pos, char name ) : Piece( pos, name ) {
		}
		bool __fastcall bValid( std::pair<char, int> nPos ) const override {
			if (!Piece::bValid( nPos )) return false;
			int dx = std::abs( nPos.first - this->position.first );
			int dy = std::abs( nPos.second - this->position.second );

			return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
		}

		//---------------------------------------------------------

		bool __fastcall CreateMove( std::pair<char, int> nPos ) override {
			if (bValid( nPos )) {
				this->position = nPos;
				return true;
			}
			if (isupper( this->name ))
				this->color = 'w';
			else
				this->color = 'b';
			return false;
		}
	};

	//  Rook (Torre)
	class Rook : public chess::Piece {
	public:
		Rook( std::pair<char, int> pos, char name ) : Piece( pos, name ) {
		}

		//---------------------------------------------------------
		bool __fastcall bValid( std::pair<char, int> nPos ) const override {
			if (!Piece::bValid( nPos )) return false;
			return (nPos.first == this->position.first || nPos.second == this->position.second);
		}

		//---------------------------------------------------------
		bool __fastcall CreateMove( std::pair<char, int> nPos ) override {
			if (bValid( nPos )) {
				this->position = nPos;
				return true;
			}
			if (isupper( this->name ))
				this->color = 'w';
			else
				this->color = 'b';
			return false;
		}
	};

	//  Bishop (Bispo)
	class Bishop : public chess::Piece {
	public:
		Bishop( std::pair<char, int> pos, char name ) : Piece( pos, name ) {
		}

		//---------------------------------------------------------
		bool __fastcall bValid( std::pair<char, int> nPos ) const override {
			if (!Piece::bValid( nPos )) return false;
			return (std::abs( nPos.first - this->position.first ) == std::abs( nPos.second - this->position.second ));
		}

		//---------------------------------------------------------
		bool __fastcall CreateMove( std::pair<char, int> nPos ) override {
			if (bValid( nPos )) {
				this->position = nPos;
				return true;
			}
			if (isupper( this->name ))
				this->color = 'w';
			else
				this->color = 'b';
			return false;
		}
	};

	//  Queen (Rainha)
	class Queen : public chess::Piece {
	public:
		Queen( std::pair<char, int> pos, char name ) : Piece( pos, name ) {
		}

		//---------------------------------------------------------
		bool __fastcall bValid( std::pair<char, int> nPos ) const override {
			if (!Piece::bValid( nPos )) return false;
			return (nPos.first == this->position.first || nPos.second == this->position.second ||
				std::abs( nPos.first - this->position.first ) == std::abs( nPos.second - this->position.second ));
		}

		//---------------------------------------------------------
		bool __fastcall CreateMove( std::pair<char, int> nPos ) override {
			if (bValid( nPos )) {
				this->position = nPos;
				return true;
			}
			if (isupper( this->name ))
				this->color = 'w';
			else
				this->color = 'b';
			return false;
		}
	};

	// King (Rei)
	class King : public chess::Piece {
	public:
		King( std::pair<char, int> pos, char name ) : Piece( pos, name ) {
		}

		//---------------------------------------------------------
		bool __fastcall bValid( std::pair<char, int> nPos ) const override {
			if (!Piece::bValid( nPos )) return false;
			int dx = std::abs( nPos.first - this->position.first );
			int dy = std::abs( nPos.second - this->position.second );
			return (dx <= 1 && dy <= 1);
		}

		//---------------------------------------------------------
		bool __fastcall CreateMove( std::pair<char, int> nPos ) override {
			if (bValid( nPos )) {
				this->position = nPos;
				return true;
			}
			if (isupper( this->name ))
				this->color = 'w';
			else
				this->color = 'b';
			return false;
		}
	};
}